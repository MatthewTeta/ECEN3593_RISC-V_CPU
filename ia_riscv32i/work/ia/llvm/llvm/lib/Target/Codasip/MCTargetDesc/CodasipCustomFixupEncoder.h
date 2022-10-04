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
 * \author  Codasip (c) Assembler generator
 * \version 9.1.1-1255
 * \brief   Source for assembler
 * \project MI11ia_riscv32i
 */
#ifndef CODASIPCUSTOMFIXUPENCODER_2_H_
#define CODASIPCUSTOMFIXUPENCODER_2_H_

#include "CodasipCustomFixupEncoderGen.h"

namespace llvm {

/**
 *  \class  CodasipCustomFixupEncoder
 *  \brief  This class provides a way how to override generated fixups with custom ones, mainly RISC-V fixups.
 */
class CodasipCustomFixupEncoder : public CodasipCustomFixupEncoderGen
 {
public:
    /**
     *  \brief  CodasipCustomFixupEncoder
     */
    CodasipCustomFixupEncoder(MCContext& Ctx);
    /**
     *  \brief  ~CodasipCustomFixupEncoder
     */
    ~CodasipCustomFixupEncoder();
};
} // namespace llvm

#endif // CODASIPCUSTOMFIXUPENCODER_2_H_
