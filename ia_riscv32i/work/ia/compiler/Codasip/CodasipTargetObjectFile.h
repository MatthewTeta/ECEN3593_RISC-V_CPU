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


#ifndef CODASIPTARGETOBJECTFILE_H
#define CODASIPTARGETOBJECTFILE_H

#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

/// Codasip uses this mainly for its data section definition.
class CodasipTargetObjectFile : public TargetLoweringObjectFileELF
{
  // TargetLoweringObjectFileELF ignores -fPIC and the UsesLabelDifference
  // setting. Grandparent class uses it correctly, so: this to be true when
  // -fPIC is in place.
  //
  // However, TargetLoweringObjectFileELF says:
  //   We can always create relative relocations, so use another section
  //   that can be marked non-executable.
  //     return false;
  //
  // so we should really just create relative relocations?
  // Consider this a temporary hack. If you're seeing this comment later than
  // 2017, consider it just a hack.
  bool shouldPutJumpTableInFunctionSection(bool UsesLabelDifference, const Function &F) const;
};

}

#endif
