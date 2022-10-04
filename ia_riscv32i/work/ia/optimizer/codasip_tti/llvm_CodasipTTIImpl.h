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
 * \file
 * \date
 * \author
 * \version
 */
#ifndef LLVM_CODASIPTTIIMPL_1_H_
#define LLVM_CODASIPTTIIMPL_1_H_

#include "llvm_CodasipGenTTIImpl.h"

namespace llvm {

/**
 *  \class  CodasipTTIImpl
 */
class CodasipTTIImpl : public CodasipGenTTIImpl
 {
public:
    /**
     *  \brief  CodasipTTIImpl
     */
    CodasipTTIImpl(const TargetMachine *TM, const Function &F) : CodasipGenTTIImpl(TM, F) {}
};

} // namespace llvm

#endif // LLVM_CODASIPTTIIMPL_1_H_
