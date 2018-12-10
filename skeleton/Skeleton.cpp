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

        void handleLoop(Loop *L) {
            errs() << "Iterated \n";
            for (Loop *SL : L->getSubLoops()) {
                handleLoop(SL);
            }
        }

        virtual bool runOnFunction(Function &F) {
            errs() << "Entering Function " << F.getName() + "\n\n";

            errs() << "Function " << F.getName () + "{\n";
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            for(LoopInfo::iterator i = LI.begin(), e = LI.end(); i!=e; ++i) {
                handleLoop(*i);
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