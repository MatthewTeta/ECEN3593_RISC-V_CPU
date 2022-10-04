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
#include "CodasipDebundleFunctionGen.h"

#include "utility/codasip_log.h"

namespace llvm {

bool CodasipDebundleFunctionGen::Run(codasip::MaxUint& value, uint64_t& inputSize)
{
    /*switch (ISA_SWITCH)
    {
        case DSM_CORE_CLASS_NAME::CODASIP_SWITCH_VALUE_MI13default_start:
        {*/
            return true;
        /*}
        default:
        {
            THROW_ERROR() << "Debundling: Unknown instruction set.\n";
        }
    }*/
}
/**
 *  \brief  codasip_print
 */
void CodasipDebundleFunctionGen::codasip_print(const char * fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
}
/**
 *  \brief  codasip_info
 */
void CodasipDebundleFunctionGen::codasip_info(const int type, const char * fmt, ...)
{
    codasip_print("info: ");
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
    printf("\n");
}
/**
 *  \brief  codasip_warning
 */
void CodasipDebundleFunctionGen::codasip_warning(const int type, const char * fmt, ...)
{
    codasip_print("warning: ");
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
    printf("\n");
}
/**
 *  \brief  codasip_error
 */
void CodasipDebundleFunctionGen::codasip_error(const int type, const char * fmt, ...)
{
    codasip_print("error: ");
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
    printf("\n");
}
/**
 *  \brief  codasip_fatal
 */
void CodasipDebundleFunctionGen::codasip_fatal(const int rc, const char * fmt, ...)
{

}
/**
 *  \brief  codasip_assert
 */
void CodasipDebundleFunctionGen::codasip_assert(const bool conditition, const char * fmt, ...)
{

}
} // namespace llvm
