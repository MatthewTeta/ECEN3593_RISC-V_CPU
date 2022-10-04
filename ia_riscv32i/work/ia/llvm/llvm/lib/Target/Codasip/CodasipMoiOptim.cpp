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


// This pass is run before register allocation and performs a local optimisation
// which replaces certain sequences of instructions into MOIs.

// Note: this is still in a prototype phase

#define DEBUG_TYPE "moi-optim"

#include "Codasip.h"
#include "CodasipTargetMachine.h"

#include "codasip/Target/CodasipBaseMoiOptim.h"

using namespace llvm;

namespace {
// MOI peephole optimizer
struct MoiOptim: public BaseMoiOptim
{
  MoiOptim(CodasipTargetMachine &tm);
  static char ID;
};
}

char MoiOptim::ID;

MoiOptim::MoiOptim(CodasipTargetMachine &tm)
: BaseMoiOptim(tm,tm.getInstrInfo(),ID)
{
  // init data
  Mois.reserve(0);
  
  // for convenience and optimisation
  
}

// create the pass
FunctionPass* llvm::createCodasipMoiOptimPass(CodasipTargetMachine &tm)
{
  return new MoiOptim(tm);
}
