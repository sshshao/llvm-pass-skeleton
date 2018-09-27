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

    virtual bool runOnFunction(Function &F) {
      int memAccsInstCnt = 0;
      int branchInstCnt = 0;
      int arithmInstCnt = 0;

      for (auto &B : F) {
        for (auto &I : B) {
          if(dyn_cast<LoadInst>(&I) || 
              dyn_cast<StoreInst>(&I) || 
              dyn_cast<AllocaInst>(&I) ||
              dyn_cast<AtomicCmpXchgInst>(&I) || 
              dyn_cast<AtomicRMWInst>(&I) || 
              dyn_cast<FenceInst>(&I) ||
              dyn_cast<GetElementPtrInst>(&I)) {
            memAccsInstCnt++;
          }

          if(dyn_cast<BranchInst>(&I) || dyn_cast<IndirectBrInst>(&I)) {
            branchInstCnt++;
          }

          if(dyn_cast<BinaryOperator>(&I)) {
            if(op->getOpcode() == Instruction::Add ||
                op->getOpcode() == Instruction::Sub ||
                op->getOpcode() == Instruction::Mul ||
                op->getOpcode() == Instruction::Shl) {
              arithmInstCnt++;
            } 
          }
        }
      }

      errs() << F.getName() << " contains: \n"; 
      errs() << "\t" << memAccsInstCnt << " memory access instructions" << "\n";
      errs() << "\t" << branchInstCnt << " branch and indirect branch instructions" << "\n";
      errs() << "\t" << arithmInstCnt << " arithmetic instructions" << "\n";

      return false;
    }
  };
}

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
