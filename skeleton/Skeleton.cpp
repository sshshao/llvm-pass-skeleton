#include <bits/stdc++.h>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/Dominators.h"

using namespace llvm;

namespace {
    struct SkeletonPass : public FunctionPass {
        static char ID;
        SkeletonPass() : FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F) {
            errs() << "Entering Function " << F.getName() + "\n";

            int bbCnt = 0;
            int loopCnt = 0;
            std::unordered_map<BasicBlock*, int> map;
            llvm::DominatorTree::DominatorTree(F) dTree;
            DomTreeNodeBase<NodeT> *root = dTree.getRootNode();	

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

            for (BasicBlock *BB = nodes.begid(); BB != nodes.end(); ++BB) {
                for (BasicBlock *Pred : predecessors(BB)) {
                    if (properlyDominates(Pred, BB)) {
                        errs() << "Loop " << loopCnt << "\t";
                        errs() << "Loop detected: BasicBlock " << map.at(BB) << " goes back to Node" << map.at(Pred) << "\n";

                        loopCnt++;
                    }
                }
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
