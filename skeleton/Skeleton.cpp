#include <bits/stdc++.h>
#include <list>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/ADT/APFloat.h"

using namespace llvm;

namespace {
    struct SkeletonPass : public FunctionPass {
        static char ID;
        SkeletonPass() : FunctionPass(ID) {}

        bool isPerfectlyNested(BasicBlock *OuterHead, BasicBlock *OuterTail, 
            BasicBlock *InnerHead, BasicBlock *InnerTail) {
            BasicBlock *InnerPreHead = nullptr;
            int innerPreHeadCtr = 0;

            for (BasicBlock *Pred : predecessors(InnerHead)) {
                innerPreHeadCtr++;
                if(Pred != InnerTail) {
                    InnerPreHead = Pred;
                }
            }

            errs() << innerPreHeadCtr << "\n";

            if (innerPreHeadCtr != 2)
                return false;

            for (BasicBlock *Succ : successors(OuterHead)) {
                if (Succ != InnerHead) {
                    errs() << "Checkpoint 1\n";
                }
                if (Succ != InnerPreHead) {
                    errs() << "Checkpoint 2\n";
                }
                if (Succ != OuterTail) {
                    errs() << "Checkpoint 3\n";
                }
                if (Succ != InnerHead && Succ != InnerPreHead && Succ != OuterTail) {
                    errs() << "false 1 \n";
                    return false;
                }
            }
            for (BasicBlock *Succ : successors(InnerTail)) {
                if (Succ != OuterTail) {
                    errs() << "false 2 \n";
                    return false;
                }
            }

            return true;
        }

        virtual bool runOnFunction(Function &F) {
            errs() << "Entering Function " << F.getName() + "\n";

            int bbCnt = 0;
            int loopCnt = 0;
            std::unordered_map<BasicBlock*, int> map;
            auto* dTree = new DominatorTree(F);
            DomTreeNodeBase<BasicBlock> *root = dTree->getRootNode();

            for (Function::iterator I = F.begin(); I != F.end(); ++I) {
                BasicBlock *BB = &(*I);
                map[BB] = bbCnt;
                bbCnt++;
            }

            std::unordered_map<int, BasicBlock*> loopHeadMap;
            std::unordered_map<BasicBlock*, int> loopTailMap;
            for (std::pair<BasicBlock*, int> block : map) {
                for (BasicBlock *Succ : successors(block.first)) {
                    //Check if successor dominants block
                    if (dTree->properlyDominates(Succ, block.first)) {
                        //Count enclosing basicblocks and instructions
                        int inBBCnt = 1;
                        int inInstCnt = 0;
                        BasicBlock* head = Succ;
                        BasicBlock* tail = block.first;

                        loopHeadMap[loopCnt] = head;
                        loopTailMap[tail] = loopCnt;
                        loopCnt++;
                    }
                }
            }

            for (std::pair<BasicBlock*, int> loopCur : loopTailMap) {
                BasicBlock *head = loopHeadMap.at(loopCur.second);
                BasicBlock *tail = loopCur.first;

                //BFS
                std::list<BasicBlock*> queue;
                std::unordered_set<BasicBlock*> visited;

                queue.push_back(tail);
                visited.insert(tail);
                while (!queue.empty()) {
                    BasicBlock *current = queue.front();
                    if(current != head) {
                        if(current != tail && loopTailMap.count(current) == 1) {
                            //Check is perfectly nested loop or not
                            errs() << "Loop " << loopTailMap.at(current) << " is nested within loop " << loopCur.second << "\n";

                            BasicBlock *innerTail = current;
                            BasicBlock *innerHead = loopHeadMap.at(loopTailMap.at(innerTail));

                            if(isPerfectlyNested(head, tail, innerHead, innerTail)) {
                                errs() << "Loop " << loopTailMap.at(innerTail) << " is perfectly nested within loop " << loopCur.second << "\n";
                            }
                        }
                        
                        for (BasicBlock *Pred: predecessors(current)) {
                            if(visited.count(Pred) == 0) {
                                queue.push_back(Pred);
                                visited.insert(current);
                            }
                        }
                    }
                    queue.pop_front();
                }
            }

            delete dTree;
            errs() << "Exiting Function " << F.getName() + "\n\n";
            return false;
        }
    };
} // namespace

char SkeletonPass::ID = 0;

static void registerSkeletonPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
    PM.add(new SkeletonPass());
}

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerSkeletonPass);