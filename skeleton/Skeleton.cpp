#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <llvm/Analysis/LoopInfo.h>
#include "llvm/IR/Dominators.h"

using namespace llvm;

namespace {
    struct SkeletonPass : public FunctionPass {
        static char ID;
        SkeletonPass() : FunctionPass(ID) {}

        /*
        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesCFG();
            AU.addRequired<LoopInfoWrapperPass>();
        }

        void handleLoop(Loop *L) {
            errs() << "Iterated \n";
            for (Loop *SL : L->getSubLoops()) {
                handleLoop(SL);
            }
        }
        */

        virtual bool runOnFunction(Function &F) {
            errs() << "Function " << F.getName() + "\n";

            DominatorTree *DT = &getAnalysis<DominatorTreeWrapperPass>(F).getDomTree();
            /*
            for (auto node = GraphTraits<DominatorTree *>::nodes_begin(DT); node != GraphTraits<DominatorTree*>::nodes_end(DT); ++node) {
                BasicBlock *BB = node->getBlock();
                errs
                // whatever you want to do with BB
                if (BranchInst *bi = dyn_cast<BranchInst>(BB->getTerminator())) {
                    Value *loopCond = bi->getCondition();
                    //errs() << "Loop condition " << loopCond->getName() + "\n";
                }
            }
            */

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
