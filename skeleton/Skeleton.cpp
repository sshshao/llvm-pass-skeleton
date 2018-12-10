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
#include <llvm/Analysis/LoopInfo.h>

using namespace llvm;

namespace {
    struct SkeletonPass : public FunctionPass {
        static char ID;
        SkeletonPass() : FunctionPass(ID) {}

        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesCFG();
            AU.addRequired<LoopInfoWrapperPass>();
        }

        void handleLoop(Loop *L, std::list<oop*> loopsList) {
            loopsList.push_back(L);

            for (Loop *SL : L->getSubLoops()) {
                handleLoop(SL);
            }
        }

        bool isPerfectlyNested(Loop* OuterLoop, Loop* InnerLoop) {
            BasicBlock *OuterLoopHeader = OuterLoop->getHeader();
            BasicBlock *OuterLoopLatch = OuterLoop->getLoopLatch();
            BasicBlock *InnerLoopPreHeader = InnerLoop->getLoopPreheader();

            for (BasicBlock *Succ: successors(OuterLoopHeader)) {
                if (Succ != InnerLoop->getLoopPreheader() && 
                    Succ != OuterLoop->getLoopLatch()) {
                    return false;
                }
            }

            return true;
        }

        virtual bool runOnFunction(Function &F) {
            errs() << "Entering Function " << F.getName() + "\n";

            std::list<Loop*> loopsList;

            //Get all loops
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            for (LoopInfo::iterator i = LI.begin(), e = LI.end(); i!=e; ++i) {
                handleLoop(*i, loopsList);
            }

            //Check each pair of loops and identify perfectly nested loops
            int i1 = 0;
            for (std::list<Loop*>::iterator it1 = loopsList.begin(); it1 != loopsList.end(); it1++) {
                int i2 = 0;
                for (std::list<Loop*>::iterator it2 = it1+1; it2 != loopsList.end(); it2++) {
                    if (isPerfectlyNested(*it1, *it2)) {
                        errs() << "Loop " << i2 << " is perfectly nested by " << i1 << "\n";
                    }
                    i2++;
                }
                i1++;
            }

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