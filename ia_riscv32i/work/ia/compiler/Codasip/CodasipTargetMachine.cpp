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


#include "CodasipTargetMachine.h"

#include "MCTargetDesc/CodasipMCAsmInfo.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Support/raw_ostream.h"

#include "Codasip.h"
#include "CodasipCustPassConfig.h"
#include "CodasipTargetTransformInfo.h"

static const char* DataLayouts[] = {"e-p:32:32:32-S64-a:0:32-v8:8:8-i8:8:8-v16:16:16-i16:16:16-f16:16:16-v32:32:32-i32:32:32-f32:32:32-v64:32:32-i64:32:32-f64:32:32-v128:32:32-i128:32:32-f128:32:32-v256:32:32-i256:32:32-v512:32:32-i512:32:32-v1024:32:32-i1024:32:32-v2048:32:32-i2048:32:32-n32", "e-p:32:32:32-S64-a:0:32-v8:8:8-i8:8:8-v16:16:16-i16:16:16-f16:16:16-v32:32:32-i32:32:32-f32:32:32-v64:32:32-i64:32:32-f64:32:32-v128:32:32-i128:32:32-f128:32:32-v256:32:32-i256:32:32-v512:32:32-i512:32:32-v1024:32:32-i1024:32:32-v2048:32:32-i2048:32:32-n32", "E-p:32:32:32-S64-a:0:32-v8:8:8-i8:8:8-v16:16:16-i16:16:16-f16:16:16-v32:32:32-i32:32:32-f32:32:32-v64:32:32-i64:32:32-f64:32:32-v128:32:32-i128:32:32-f128:32:32-v256:32:32-i256:32:32-v512:32:32-i512:32:32-v1024:32:32-i1024:32:32-v2048:32:32-i2048:32:32-n32"};

extern bool __codasip_pass_disable__;

using namespace llvm;

static cl::opt<unsigned> ConfigIndex("config-index", cl::Hidden, cl::init(0));

// called from llc::main
extern "C" void LLVMInitializeCodasipTarget() {
  RegisterTargetMachine<CodasipTargetMachine> X(TheCodasipTarget);
  __codasip_pass_disable__ = false;
}

inline Reloc::Model getRelocModel(Optional<Reloc::Model> RM) {
  return RM.hasValue()? RM.getValue(): Reloc::Static;
}

inline CodeModel::Model getCodeModel(Optional<CodeModel::Model> CM) {
  return CM.hasValue()? CM.getValue(): CodeModel::Small;
}

// note: data defined here will be (in an encapsulated way) used by constructors of other objects
// note: the CPU parameter is not used, usage replaced by "codasip"
// note: a prefix with features enabled by default is added to FS in subtarget
CodasipTargetMachine::CodasipTargetMachine(const Target &T,
                                           const Triple &TT,
                                           StringRef /*CPU*/,
                                           StringRef FS,
                                           const TargetOptions &Options,
                                           Optional<Reloc::Model> RM,
                                           Optional<CodeModel::Model> CM,
                                           CodeGenOpt::Level OL_, bool JIT)
: LLVMTargetMachine(T, DataLayouts[ConfigIndex], TT, "codasip", FS, Options, ::getRelocModel(RM), ::getCodeModel(CM), OL_),
  OL(OL_),
  Subtarget(TT,FS,*this)
{
  initAsmInfo();
  assert(getOptLevel()==OL);
  assert(ConfigIndex<3);
  
  setMachineOutliner(true);
  setSupportsDefaultOutlining(true);
  
}

TargetPassConfig* CodasipTargetMachine::createPassConfig(PassManagerBase &PM)
{
  return new CodasipPassConfig(*this,PM);
}

TargetTransformInfo
CodasipTargetMachine::getTargetTransformInfo(const Function &F)
{
  return TargetTransformInfo(CodasipTTIImpl(this, F));
}

// Auxiliary functions

unsigned llvm::GetSpace4Vt(EVT vt)
{
  unsigned addressSpace = 0;
  switch (vt.getSimpleVT().SimpleTy)
  {
    
    default: ;
  }
  return addressSpace;
}

unsigned llvm::GetSpace4Rc(const llvm::TargetRegisterClass *RC)
{
  unsigned addressSpace = 0;
  
  return addressSpace;
}
