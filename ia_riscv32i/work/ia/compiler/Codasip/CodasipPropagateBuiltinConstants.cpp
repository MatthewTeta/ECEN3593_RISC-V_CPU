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


#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"

#include "Codasip.h"
#include "CodasipGenISelLowering.h"
#include "CodasipGenInstrInfo.h"
#include "CodasipTargetMachine.h"

#include <map>
#include <vector>

using namespace llvm;

namespace {

// propagate constants to builtins that need them
struct PropagateBuiltinConstants: public FunctionPass
{
  static char ID;

  PropagateBuiltinConstants(CodasipTargetMachine& tm): FunctionPass(ID), CTM(tm) {}

  llvm::StringRef getPassName() const override {return "Propagate builtin constants";}

  bool handleCodasipBuiltin(IntrinsicInst *II);
  ConstantInt *getConstantForValue(Value *V, bool &sign);

  bool runOnFunction(Function &F) override
  {
    bool Changed = false;
    for (BasicBlock &BB : F)
    {
      for (Instruction &I : BB)
      {
        if (IntrinsicInst *II = dyn_cast<IntrinsicInst>(&I))
        {
          if (IsCodasipIntrin(II->getIntrinsicID()))
          {
            Changed |= handleCodasipBuiltin(II);
          }
        }
      }
    }
    return Changed;
  }
  
  const CodasipTargetMachine &CTM;
};

}

char PropagateBuiltinConstants::ID;

// make sure operands that need to be constants really are
bool PropagateBuiltinConstants::handleCodasipBuiltin(IntrinsicInst *II)
{
  bool Changed = false;
  // our internal subcode
  ConstantInt *CI = cast<ConstantInt>(II->getArgOperand(0));
  // info about the inputs of the instruction
  auto info = CTM.getInstrInfo()->GetBuiltinInfo(CI->getLimitedValue());
  // transfer to argument indexes
  std::vector<unsigned> imms;
  imms.reserve(info.InputInfo2.size());
  for (unsigned i=0; i<info.InputInfo2.size(); ++i)
  {
    if (info.InputInfo2[i]) {
      imms.push_back(i+1);
    }
  }
  // process
  for (auto arg: imms)
  {
    Value *argOp = II->getArgOperand(arg);
    bool sign = false;
    // if it's already constant then there's nothing to do
    if (isa<ConstantInt>(argOp)) continue;
    // find the constant
    ConstantInt *CI = getConstantForValue(argOp, sign);
    // if constant wasn't found then there's nothing to do
    if (!CI) continue;
    // add cast to a legal type (no need to cast to the actual arg type)
    CastInst *CII = CastInst::CreateIntegerCast(CI,
             IntegerType::getInt32Ty(II->getContext()),
             sign, "", II);
    // set new value of the operand
    II->setArgOperand(arg, CII);
    Changed = true;
  }
  return Changed;
}

// find constant value for the given operand
ConstantInt *PropagateBuiltinConstants::getConstantForValue(Value *V, bool &sign)
{
  if (ConstantInt *CI = dyn_cast<ConstantInt>(V))
  {
    // it is constant
    return CI;
  }
  if (Instruction *I = dyn_cast<Instruction>(V))
  {
    switch (I->getOpcode())
    {
      case Instruction::Store:
        // check stored value
        return getConstantForValue(cast<StoreInst>(I)->getValueOperand(), sign);
      case Instruction::Load:
        // argument could be constant indirectly (store -> load)
        for (auto use : cast<LoadInst>(I)->getPointerOperand()->users())
        {
          if (StoreInst *SI = dyn_cast<StoreInst>(use))
          {
            return getConstantForValue(SI, sign);
          }
        }
        break;
      case Instruction::ZExt:
        sign = false;
        // check zero-extended value
        return getConstantForValue(cast<ZExtInst>(I)->getOperand(0), sign);
      case Instruction::SExt:
        sign = true;
        // check sign-extended value
        return getConstantForValue(cast<SExtInst>(I)->getOperand(0), sign);
    }
  }
  // constant not found
  return nullptr;
}

FunctionPass* llvm::createCodasipPropagateBuiltinConstantsPass(CodasipTargetMachine& tm)
{
  return new PropagateBuiltinConstants(tm);
}
