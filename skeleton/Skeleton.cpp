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
          if(auto *op = dyn_cast<LoadInst>(&I) || 
              auto *op = dyn_cast<StoreInst>(&I) || 
              auto *op = dyn_cast<AtomicCmpXchgInst>(&I) || 
              auto *op = dyn_cast<AtomicRMWInst>(&I)) {
            memAccsInstCnt++;
          }

          if(auto *op = dyn_cast<BranchInst>(&I) || auto *op = dyn_cast<IndirectBrInst>(&I)) {
            branchInstCnt++;
          }

          if(auto *op = dyn_cast<BinaryOperator>(&I)) {
            if(op.getOpcode() == Instruction::Add ||
                op.getOpcode() == Instruction::Sub ||
                op.getOpcode() == Instruction::Mul ||
                op.getOpcode() == Instruction::Shl) {
              arithmInstCnt++;
            } 
          }
        }
      }

      errs() << memAccsInstCnt << " memory access instructions" << "\n";
      errs() << branchInstCnt << " branch and indirect branch instructions" << "\n";
      errs() << arithmInstCnt << " arithmetic instructions" << "\n";

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
