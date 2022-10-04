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
#ifndef CODASIPASMPARSERHOOKS_4_H_
#define CODASIPASMPARSERHOOKS_4_H_

#include "CodasipAsmParserHooksGen.h"

namespace llvm {

/**
 *  \class  CodasipAsmParserHooks
 *  \brief  This class provides a way how to override generated codasip assembler parser hooks with custom ones, mainly RISC-V hooks.
 */
class CodasipAsmParserHooks : public CodasipAsmParserHooksGen
 {
public:
    /**
     *  \brief  ~CodasipAsmParserHooks
     */
    ~CodasipAsmParserHooks();
};
} // namespace llvm

#endif // CODASIPASMPARSERHOOKS_4_H_
