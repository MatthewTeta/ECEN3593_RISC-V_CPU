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
#ifndef CODASIPDEBUNDLEFUNCTIONGEN_1_H_
#define CODASIPDEBUNDLEFUNCTIONGEN_1_H_

#include <cstdio>
#include <cstdarg>

#include "common/codasip_integer.h"

namespace llvm {

/**
 *  \class  CodasipDebundleFunctionGen
 */
class CodasipDebundleFunctionGen  {
public:
    typedef struct s_dummy
    {
        int FIXME;
    } dummy;
    template<int BITS>
    struct debundle
    {
        codasip::Integer<BITS, false> value;
        uint32_t input_size;
    };
    /**
     *  \brief  Run
     */
    bool Run(codasip::MaxUint& value, uint64_t& inputSize);
private:
    void codasip_print(const char * fmt, ...);
    void codasip_info(const int type, const char * fmt, ...);
    void codasip_warning(const int type, const char * fmt, ...);
    void codasip_error(const int type, const char * fmt, ...);
    void codasip_fatal(const int rc, const char * fmt, ...);
    void codasip_assert(const bool conditition, const char * fmt, ...);
};
} // namespace llvm

#endif // CODASIPDEBUNDLEFUNCTIONGEN_1_H_
