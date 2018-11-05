#include <bits/stdc++.h>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <llvm/Analysis/LoopInfo.h>
#include "llvm/IR/CFG.h"

using namespace llvm;

namespace {
    struct SkeletonPass : public FunctionPass {
        static char ID;
        SkeletonPass() : FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F) {
            errs() << "Function " << F.getName() + "\n";

            int bbCnt = 0;
            std::unordered_map<BasicBlock*, int> map;

            for (Function::iterator I = F.begin(); I != F.end(); I++) {
                BasicBlock *BB = &(*I);
                errs() << "BasicBlock " << bbCnt << BB->getName() << "\n";

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

            int loopCnt = 0;
            for (Function::iterator I = F.begin(); I != F.end(); I++) {
                BasicBlock *BB = &(*I);
                int bbIdx = -1;
                std::unordered_map<BasicBlock*, int>::const_iterator mapIter = map.find(BB);

                if(mapIter != map.end()) {
                    bbIdx = mapIter->second;
                }

                for (BasicBlock *Pred : predecessors(BB)) {
                    int predIdx = -1;
                    mapIter = map.find(Pred);
                    if (mapIter != map.end()) {
                        predIdx = mapIter->second;
                    }

                    if(predIdx > bbIdx) {
                        errs() << "Loop " << loopCnt << "\n";
                    }
                }

                loopCnt++;
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
