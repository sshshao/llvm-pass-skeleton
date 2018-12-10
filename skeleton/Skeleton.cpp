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

                        //BFS
                        std::list<BasicBlock*> queue;
                        std::unordered_set<BasicBlock*> visited;

                        queue.push_back(tail);
                        while (!queue.empty()) {
                            BasicBlock *current = queue.front();

                            inBBCnt++;
                            for (BasicBlock::iterator BI = current->begin(); BI != current->end(); ++BI) {
                                inInstCnt++;
                            }

                            if(current != head) {
                                for (BasicBlock *Pred: predecessors(current)) {
                                    if(visited.count(Pred) == 0) {
                                        queue.push_back(Pred);
                                    }
                                }
                            }

                            visited.insert(current);
                            queue.pop_front();
                        }

                        //errs() << "Loop " << loopCnt << ": BasicBlock " << block.second 
                        //    << " goes back to Block " << map.at(Succ) << "\n";
                        //errs() << "\t " << inBBCnt << " basic blocks; " << inInstCnt << " instructions\n";

                        loopHeadMap[loopCnt] = head;
                        loopTailMap[tail] = loopCnt;
                        loopCnt++;
                    }
                }
            }

            for (std::pair<BasicBlock*, int> loopCur : loopTailMap) {
                BasicBlock *tail = loopCur.first;
                BasicBlock *head = loopHeadMap.at(loopCur.second);

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
                            //errs() << "Loop " << loopTailMap.at(current) << " is nested within loop " << loopCur.second << "\n";

                            bool isHeadPerfect = false;
                            bool isTailPerfect = false;
                            BasicBlock *innerTail = current;
                            BasicBlock *innerHead = loopHeadMap.at(loopTailMap.at(innerTail));

                            for (BasicBlock *Succ : successors(head)) {
                                for(BasicBlock *SuccL2: successors(Succ)) {
                                    if(SuccL2 == innerHead) {
                                        isHeadPerfect = true;
                                    }
                                }
                            }
                            for (BasicBlock *Pred : predecessors(tail)) {
                                if(Pred == innerTail) {
                                    isTailPerfect = true;
                                }
                            }
                            if(isHeadPerfect && isTailPerfect) {
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