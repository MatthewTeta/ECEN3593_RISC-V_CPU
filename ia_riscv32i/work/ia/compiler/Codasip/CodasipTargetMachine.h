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


#ifndef CODASIPTARGETMACHINE_H
#define CODASIPTARGETMACHINE_H

#include "CodasipSubtarget.h"
#include "CodasipTargetObjectFile.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class CodasipTargetMachine: public LLVMTargetMachine
{
public:
  /// Constructor.
  CodasipTargetMachine(const Target &T,
                       const Triple &TT,
                       StringRef CPU,
                       StringRef FS,
                       const TargetOptions &Options,
                       Optional<Reloc::Model> RM,
                       Optional<CodeModel::Model> CM,
                       CodeGenOpt::Level OL, bool JIT);
  // Access methods.
  const CodasipSubtarget* getSubtargetImpl(const Function&) const override {return &Subtarget;}
  const CodasipSubtarget* getSubtargetImpl() const {return &Subtarget;}
  const CodasipInstrInfo* getInstrInfo() const {return static_cast<const CodasipInstrInfo*>(Subtarget.getInstrInfo());}
  const CodasipFrameLowering* getFrameLowering() const {return Subtarget.getFrameLowering();}
  const CodasipTargetLowering* getTargetLowering() const {return Subtarget.getTargetLowering();}
  const TargetRegisterInfo* getRegisterInfo() const {return Subtarget.getRegisterInfo();}
  const InstrItineraryData* getInstrItineraryData() const {return Subtarget.getInstrItineraryData();}
  bool hasCodasipCFI() const override {return true;}
  const CodasipSelectionDAGInfo* getSelectionDAGInfo() const {return Subtarget.getSelectionDAGInfo();}
  TargetLoweringObjectFile* getObjFileLowering() const override {return &ObjectLowering;}
  TargetTransformInfo getTargetTransformInfo(const Function &F) override;
  // passes
  TargetPassConfig* createPassConfig(PassManagerBase &PM) override;
  
  /** Copy of the optimalisation level.
   * Deprecated, use getOptLevel(). */
  const CodeGenOpt::Level OL;
  
private:
  CodasipSubtarget Subtarget;
  mutable CodasipTargetObjectFile ObjectLowering;
};

// These two need to be global
/// Get an appropriate address space for the given type.
unsigned GetSpace4Vt(EVT vt);
/// The same for register classes.
unsigned GetSpace4Rc(const TargetRegisterClass *RC);

}

#endif
