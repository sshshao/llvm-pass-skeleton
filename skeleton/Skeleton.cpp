#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
using namespace llvm;

namespace {
    struct SkeletonPass : public FunctionPass {
        static char ID;
        SkeletonPass() : FunctionPass(ID) {}

        void getAnalysisUsage(AnalysisUsage &AU) const override {
            AU.setPreservesCFG();
            AU.addRequired<LoopInfoWrapperPass>();
        }

        virtual bool runOnFunction(Function &F) {
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            for(LoopInfo::iterator i = LI.begin(), e = LI.end(); i!=e; ++i) {
                BlocksInLoop (*i,0);
            }

            errs() << "Function " << F.getName () + "{\n";
            for(Function::iterator b = F.begin(), be = F.end(); b != be; ++b) {
                for(LoopInfo::iterator L = LI.begin(), e = LI.end(); L!=e; ++L) {
                    if(L->contains(&*b)) {
                        break; // Skip those BB that belong to a loop.
                    }       
                }  
                for(BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; i ++) {
                    if(isa<CallInst>(&(*i)) || isa<InvokeInst>(&(*i))) {
                        errs()<<"Call "<< cast<CallInst>(&(*i))->getCalledFunction()->getName() << "\n"; 
                    }
                }
            }

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
