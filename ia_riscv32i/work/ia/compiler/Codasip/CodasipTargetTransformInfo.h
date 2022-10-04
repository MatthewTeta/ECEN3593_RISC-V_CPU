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


//===----------------------------------------------------------------------===//
/// \file
/// This file a TargetTransformInfo::Concept conforming object specific to the
/// Codasip target machine. It uses the target's detailed information to
/// provide more precise answers to certain TTI queries, while letting the
/// target independent and default TTI implementations handle the rest.
///
//===----------------------------------------------------------------------===//

#ifndef CODASIPTARGETTRANSFORMINFO_H
#define CODASIPTARGETTRANSFORMINFO_H

#include "Codasip.h"
#include "CodasipTargetMachine.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class CodasipTTIImpl : public BasicTTIImplBase<CodasipTTIImpl> {
  typedef BasicTTIImplBase<CodasipTTIImpl> BaseT;
  typedef TargetTransformInfo TTI;
  friend BaseT;

  const CodasipSubtarget *ST;
  const CodasipTargetLowering *TLI;

  const CodasipSubtarget *getST() const { return ST; }
  const CodasipTargetLowering *getTLI() const { return TLI; }

public:
  explicit CodasipTTIImpl(const CodasipTargetMachine *TM, const Function &F)
      : BaseT(TM, F.getParent()->getDataLayout()), ST(TM->getSubtargetImpl(F)),
        TLI(ST->getTargetLowering()) {}

  // Provide value semantics. MSVC requires that we spell all of these out.
  CodasipTTIImpl(const CodasipTTIImpl &Arg)
      : BaseT(static_cast<const BaseT &>(Arg)), ST(Arg.ST), TLI(Arg.TLI) {}
  CodasipTTIImpl(CodasipTTIImpl &&Arg)
      : BaseT(std::move(static_cast<BaseT &>(Arg))), ST(std::move(Arg.ST)),
        TLI(std::move(Arg.TLI)) {}

  bool isHardwareLoopProfitable(Loop *L, ScalarEvolution &SE,
                                AssumptionCache &AC,
                                TargetLibraryInfo *LibInfo,
                                HardwareLoopInfo &HWLoopInfo);
};

} // end namespace llvm

#endif
