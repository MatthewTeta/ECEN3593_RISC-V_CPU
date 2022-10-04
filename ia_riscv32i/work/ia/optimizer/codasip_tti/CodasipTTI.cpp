/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2020 Codasip s.r.o.
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 * 
 * \file CodasipTTI.cpp
 * \author
 * \date
 * \brief The interface of CodasipTTI shared library.
 */

#include "llvm_CodasipTTIImpl.h"
#include "llvm/Analysis/TargetTransformInfo.h"

using namespace llvm;

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif

extern "C" EXPORT_API
TargetTransformInfo TTIConstructor(const TargetMachine* TM, const Function& F) {
  return TargetTransformInfo(CodasipTTIImpl(TM, F));
}
