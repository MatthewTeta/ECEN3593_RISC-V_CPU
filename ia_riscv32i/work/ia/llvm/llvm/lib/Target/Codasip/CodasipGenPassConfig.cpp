/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2022 Codasip s.r.o.
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file
 * \date    2022-09-10
 * \author  Codasip (c) C compiler backend generator
 * \version 9.1.1-1255
 * \brief   Source for compiler backend
 * \project ia_riscv32i.ia
 * \note          Codasip Studio version: 9.1.1-1255
 *                Licensee: Lockular Limited  (C60_2111_2104)
 *                Project: ia_riscv32i.ia
 *                Date: 2022-09-10 04:29:16
 *                Copyright (C) 2022 Codasip s.r.o.
 */


#include "CodasipGenPassConfig.h"
#include "codasip/Passes.h"
#include "llvm/Support/CommandLine.h"

extern bool __codasip_pass_disable__;

using namespace llvm;
extern cl::opt<bool> EnableHWLoops;

cl::opt<bool> DisableSuperBlock("disable-superblock",
                                cl::desc("Disable Superblock Scheduling"),
                                
                                cl::init(true));
                                


// Register DAG2DAG pass.
bool CodasipGenPassConfig::addInstSelector()
{
  CodasipTargetMachine &tm = getCodasipTargetMachine();
  addPass(createCodasipISelDag(tm));
  if (tm.OL>=CodeGenOpt::Default) {
    addPass(createCodasipSmallerInstructionsPass(tm,OnlyEmul));
  }
  return false;
}

// post-isel
void CodasipGenPassConfig::addMachinePasses()
{
  CodasipTargetMachine &tm = getCodasipTargetMachine();
  // code-size optim, only emulations, no jumps
  if (tm.OL>=CodeGenOpt::Default) {
    addPass(createCodasipLoadStoreMapAnalysisPass());
    addPass(createCodasipPreRAPeepholePass(tm));
  }
  TargetPassConfig::addMachinePasses();
}

bool CodasipGenPassConfig::addSuperBlockPreRegAlloc()
{
  CodasipTargetMachine &tm = getCodasipTargetMachine();
  if (tm.OL>=CodeGenOpt::Default) {
    if (!__codasip_pass_disable__) {
     if (!DisableSuperBlock) {
      addPass(createSuperBlockScheduler());
      return true;
     }
    }
  }
  return false;
}

void CodasipGenPassConfig::addPreRegAlloc()
{
  CodasipTargetMachine &tm = getCodasipTargetMachine();
  if (tm.OL>=CodeGenOpt::Default)
  {
    addPass(createCodasipMoiOptimPass(tm));
    addPass(createCodasipLoadStoreMapAnalysisPass());
    addPass(createCodasipPreRAPeepholePass(tm));
  }
  addPass(createCodasipInlineAsmRegPairsPass(tm));
  addPass(createCodasipInlineAsmFastRegAlloc(tm));
}

// note: this isn't called if -O0
void CodasipGenPassConfig::addMachineLateOptimization()
{
  CodasipTargetMachine &tm = getTM<CodasipTargetMachine>();
  // this method is called only when optimization level is not -O0
  // first execute default LLVM passes
  TargetPassConfig::addMachineLateOptimization();
  if (tm.OL>=CodeGenOpt::Default)
  {
    // code-size optim, normal instructions + jumps if lt info
    addPass(createCodasipSmallerInstructionsPass(tm,LtoJump));
  }
}

void CodasipGenPassConfig::addPreSched2()
{
  if (getOptLevel() != CodeGenOpt::None)
  {
    
  }
}

void CodasipGenPassConfig::addPreEmitPass()
{
  CodasipTargetMachine& tm = getCodasipTargetMachine();
  // note: this is actully third pass of dummy expansion
  addPass(createCodasipCallCompletionPass(tm));
  // code-size optim, no jump instructions
  if (tm.OL>=CodeGenOpt::Default) {
    // must be after CodasipCallCompletionPass
    addPass(createCodasipPostRAPeepholePass(tm));
    // code-size optim only normal instructions, no jumps
    addPass(createCodasipSmallerInstructionsPass(tm,NormalInst));
    // finalize hwloops
    if (EnableHWLoops)
      addPass(createHardwareLoopsFinalizerPass());
  }
  // sequences, vliw, simple nops
  
  addPass(createCodasipMipsDelaySlotFillerPass());
  addPass(createCodasipNoopAdderPass(tm));
  
  // jumps
  addPass(createCodasipJumpLengthCheckerPass(tm));
  
  // code-size optim only jump instructions
  if (tm.OL>=CodeGenOpt::Default) {
    
    addPass(createCodasipDoubleJumpPass(tm));
    
    addPass(createCodasipSmallerInstructionsPass(tm,OnlyJump));
  }
  
  // note: and this is actually fourth dummy expansion, dummies can be inserted even after the third one
  addPass(createCodasipCallCompletionPass(tm));
  // this must be last
  addPass(createCodasipCfiAdder(tm));
}

void CodasipGenPassConfig::addPreEmitPass2() {
  CodasipTargetMachine& tm = getCodasipTargetMachine();
  // A final call expansion, for the purposes of newly outlined functions:
  addPass(createCodasipCallCompletionPass(tm));
  // Fixes cfi directives, which are used in DWARF EH and LLDB
  // For example fixes cases when unwind resume is generated after epilogue of function
  addPass(createCFIInstrInserter());
}

// IR manipulation pass

namespace {
class CodasipPreISel: public ModulePass
{
  CodasipTargetMachine &TM;
public:
  static char ID;
  explicit CodasipPreISel(CodasipTargetMachine &tm): ModulePass(ID), TM(tm) {}

  virtual bool runOnModule(Module &M);

  StringRef getPassName() const {
    return "CodasipPreISel";
  }
};
}

char CodasipPreISel::ID = 0;

bool CodasipPreISel::runOnModule(Module &M)
{
  const CodasipTargetLowering *TL = TM.getTargetLowering();
  const DataLayout &td = TM.getDataLayout();
  bool changed = false;
  // check weird types
  for (Module::iterator MI=M.begin(); MI!=M.end(); ++MI)
  {
    for (Function::iterator FI=MI->begin(); FI!=MI->end(); ++FI)
    {
      for (BasicBlock::iterator BI=FI->begin(); BI!=FI->end(); ++BI)
      {
        // check va_args
        if (BI->getOpcode() == Instruction::VAArg)
        {
          Type* t = BI->getType();
          // try to get EVT
          EVT et = TL->getValueType(td,t,true);
          // check
          if (et.isSimple() && et==MVT::Other) {
            errs() << "There's an invalid type in va_arg. This isn't allowed. Edit your application.\n";
            exit(1);
          }
        }
      }
    }
  }
  return changed;
}

// Add the pass defined above
bool CodasipGenPassConfig::addPreISel()
{
  CodasipTargetMachine& tm = getCodasipTargetMachine();
  addPass(new CodasipPreISel(tm));
  addPass(createCodasipPropagateBuiltinConstantsPass(tm));
  if (EnableHWLoops) {
    if (tm.OL>=CodeGenOpt::Default)
      addPass(createHardwareLoopsPass());
    else
      errs() << "Warning: Hardware Loops are disabled due to low optimization "
                "level. To enable, compile with -O2 or higher.\n";
  }
  return TargetPassConfig::addPreISel();
}

