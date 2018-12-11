#include <bits/stdc++.h>
#include <list>
#include "llvm/Pass.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Constant.h"
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

        Instruction* getPrevInstruction(Instruction *Inst) {
            BasicBlock::iterator I(Inst);
            if (I == Inst->getParent()->begin())
                return nullptr;
            return &*--I;
        }

        bool isBasicBlockIndependent(BasicBlock *BB1, BasicBlock *BB2) {
            if (BB1 == nullptr || BB2 == nullptr)
                return true;
            
            std::vector<Value*> BB1Vars;
            
            for (BasicBlock::iterator it = BB1->begin(); it != BB1->end(); it++) {
                for (User::op_iterator op_it = it->op_begin(); op_it != it->op_end(); op_it++) {
                    if (!dyn_cast<Constant>(*op_it) &&
                        (isa<Argument>(*op_it) || ((Instruction*)op_it)->getParent() != BB1)) {
                        BB1Vars.push_back(*op_it);
                    }
                }
            }

            for (BasicBlock::iterator it = BB2->begin(); it != BB2->end(); it++) {
                for (User::op_iterator op_it = it->op_begin(); op_it != it->op_end(); op_it++) {
                    if (!dyn_cast<Constant>(*op_it) &&
                        (isa<Argument>(*op_it) || ((Instruction*)op_it)->getParent() != BB2)) {
                        if(std::find(BB1Vars.begin(), BB1Vars.end(), *op_it) != BB1Vars.end()) {
                            return false;
                        } 
                    }
                }
            }

            return true;
        }

        bool isNestedLoopIndependent(Loop* OuterLoop, Loop* InnerLoop) {
            BasicBlock *OuterLoopHeader = OuterLoop->getHeader();
            BasicBlock *InnerLoopPreheader = InnerLoop->getLoopPreheader();
            BasicBlock *InnerLoopHeader = InnerLoop->getHeader();
            BasicBlock *InnerLoopLatch = InnerLoop->getLoopLatch();

            if (isBasicBlockIndependent(OuterLoopHeader, InnerLoopPreheader) &&
                isBasicBlockIndependent(OuterLoopHeader, InnerLoopHeader) &&
                isBasicBlockIndependent(OuterLoopHeader, InnerLoopLatch)) {
                return true;
            }

            return false;
        }

        virtual bool runOnFunction(Function &F) {
            errs() << "Entering Function " << F.getName() + "\n";

            std::list<Loop*> loopsList;

            //Get all loops
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            //ScalarEvolution *SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();

            for (LoopInfo::iterator i = LI.begin(), e = LI.end(); i!=e; ++i) {
                handleLoop(*i, &loopsList);
            }

            //Check each pair of loops and identify perfectly nested loops
            int i1 = 0;
            for (std::list<Loop*>::iterator it1 = loopsList.begin(); it1 != loopsList.end(); it1++) {
                int i2 = i1 + 1;
                for (std::list<Loop*>::iterator it2 = std::next(it1, 1); it2 != loopsList.end(); it2++) {
                    if (isPerfectlyNested(*it1, *it2)) {
                        errs() << "Loop " << i2 << " is perfectly nested by " << i1 << "\n";
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