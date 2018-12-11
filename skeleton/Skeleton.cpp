#include <bits/stdc++.h>
#include <list>
#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
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

        void handleLoop(Loop *L, std::list<Loop*> *loopsList) {
            loopsList->push_back(L);

            for (Loop *SL : L->getSubLoops()) {
                handleLoop(SL, loopsList);
            }
        }

        BasicBlock* getLoopEnd(Loop *Loop) {
            for (BasicBlock *Succ : successors(Loop->getHeader())) {
                if(!Loop->contains(Succ)) {
                    return Succ;
                }
            }

            return nullptr;
        }

        bool isPerfectlyNested(Loop* OuterLoop, Loop* InnerLoop) {
            BasicBlock *OuterLoopHeader = OuterLoop->getHeader();
            
            for (BasicBlock *Succ : successors(OuterLoopHeader)) {
                if (Succ != InnerLoop->getLoopPreheader() && 
                    Succ != InnerLoop->getHeader() &&
                    Succ != getLoopEnd(OuterLoop)) {
                    return false;
                }
            }

            return true;
        }

        bool isNestedLoopIndependent(Loop* OuterLoop, Loop* InnerLoop) {
            auto *OuterLoopHeaderTerminator = dyn_cast<Instruction>(OuterLoop->getHeader()->getTerminator());
            auto *InnerLoopHeaderTerminator = dyn_cast<Instruction>(InnerLoop->getHeader()->getTerminator());
            BinaryOperator *OuterLoopHeaderInst = dyn_cast<BinaryOperator>(OuterLoopHeaderTerminator->getPrevNonDebugInstruction());
            BinaryOperator *InnerLoopHeaderInst = dyn_cast<BinaryOperator>(InnerLoopHeaderTerminator->getPrevNonDebugInstruction());
            
            Value *OuterInstLhs = OuterLoopHeaderInst->getOperand(0);
            Value *OuterInstRhs = OuterLoopHeaderInst->getOperand(1);
            Value *InnerInstLhs = InnerLoopHeaderInst->getOperand(0);
            Value *InnerInstRhs = InnerLoopHeaderInst->getOperand(1);

            if(OuterInstLhs == InnerInstLhs || OuterInstLhs == InnerInstRhs ||
                OuterInstRhs == InnerInstLhs || OuterInstRhs == InnerInstRhs) {
                return false;
            }

            return true;
        }

        virtual bool runOnFunction(Function &F) {
            errs() << "Entering Function " << F.getName() + "\n";

            std::list<Loop*> loopsList;

            //Get all loops
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            for (LoopInfo::iterator i = LI.begin(), e = LI.end(); i!=e; ++i) {
                handleLoop(*i, &loopsList);
            }

            //Check each pair of loops and identify perfectly nested loops
            int i1 = 0;
            for (std::list<Loop*>::iterator it1 = loopsList.begin(); it1 != loopsList.end(); it1++) {
                int i2 = i1 + 1;
                for (std::list<Loop*>::iterator it2 = std::next(it1, 1); it2 != loopsList.end(); it2++) {
                    if (isPerfectlyNested(*it1, *it2)) {
                        //errs() << "Loop " << i2 << " is perfectly nested by " << i1 << "\n";
                        if(isNestedLoopIndependent(*it1, *it2)) {
                            errs() << "Nested loop pair " << i1 << " and " << i2 << ": index variables are independent\n";
                        } else {
                            errs() << "Nested loop pair " << i1 << " and " << i2 << ": index variables are dependent\n";
                        }
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