#include <bits/stdc++.h>
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

        void getLoopStat(auto* dTree, BasicBlock *head, BasicBlock *tail) {

        }

        virtual bool runOnFunction(Function &F) {
            errs() << "Entering Function " << F.getName() + "\n";

            int bbCnt = 0;
            int loopCnt = 0;
            std::unordered_map<BasicBlock*, int> map;
            auto* dTree = new DominatorTree(F);
            DomTreeNodeBase<BasicBlock> *root = dTree->getRootNode();	

            for (Function::iterator I = F.begin(); I != F.end(); I++) {
                BasicBlock *BB = &(*I);
                map[BB] = bbCnt;
                bbCnt++;

                /*
                int instCnt = 0;
                for (BasicBlock::iterator BI = BB.begin(), BE = BB.end(); BI != BE; ++BI) {
                    Instruction &Inst = *BI;
                    errs() << "Instruction " << Inst.getOpcodeName() << "\n";
                    instCnt++;
                }
                */
            }
            errs() << bbCnt << " BasicBlocks detected\n";

            for (std::pair<BasicBlock*, int> block : map) {
                for (BasicBlock *Succ : successors(block.first)) {
                    //Check if successor dominants block
                    if (dTree->properlyDominates(Succ, block.first)) {
                        //Count enclosing basicblocks and instructions
                        int inBBCnt = 0;
                        int inInstCnt = 0;
                        BasicBlock* head = Succ;
                        BasicBlock* tail = block.first;

                        SmallVector<BasicBlock *, 0> descendants;
                        dTree->getDescendants(head, descendants);
                        for (BasicBlock::iterator *inBBIter = descendants.begin(); inBBIter != descendants.end(); ++inBBIter) {
                            BasicBlock *inBB = &(*inBBIter);
                            if(dTree->dominates(inBB, tail)) {
                                inBBCnt++;
                                for (BasicBlock::iterator BI = inBB.begin(); BI != inBB.end(); ++BI) {
                                    inInstCnt++;
                                }
                            }
                        }

                        errs() << "Loop " << loopCnt << ": BasicBlock " << block.second 
                            << " goes back to Block " << map.at(Succ) << "\n";
                        errs() << "\t " << inBBCnt << " basic blocks; " << inInstCnt << " instructions\n";

                        loopCnt++;
                    }
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
