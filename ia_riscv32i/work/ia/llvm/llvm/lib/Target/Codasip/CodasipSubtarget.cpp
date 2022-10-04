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


#include "CodasipSubtarget.h"
#include "CodasipTargetMachine.h"
#include "Codasip.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

#define DEBUG_TYPE "codasip-subtarget"

#define GET_SUBTARGETINFO_CTOR
#define GET_SUBTARGETINFO_TARGET_DESC
#include "CodasipGenSubtargetInfo.inc"

CodasipSubtarget::CodasipSubtarget(const Triple &TT, StringRef FS, CodasipTargetMachine &TM)
: CodasipGenSubtargetInfo(TT, "codasip", FS), InstrInfo(TM)

, FrameInfo(TM), TSInfo(TM), InstrItins(getInstrItineraryForCPU("codasip"))

{
  // add features enabled by default
  std::string fs("");
  fs += FS;
  // parse it
  ParseSubtargetFeatures("codasip", fs);
  
  // legalities are dependent on subtarget features
  // note: make_unique not allowed in llvm
  TLInfo = std::unique_ptr<CodasipTargetLowering>(new CodasipTargetLowering(TM));
  
}

CodasipSubtarget::~CodasipSubtarget() {}



// always on (unless vliw)
#define POST_RA_ALWAYS_ON 1

bool CodasipSubtarget::enablePostRAScheduler() const
{
  
  if (POST_RA_ALWAYS_ON) return true;
  return TargetSubtargetInfo::enablePostRAScheduler();
  
}


