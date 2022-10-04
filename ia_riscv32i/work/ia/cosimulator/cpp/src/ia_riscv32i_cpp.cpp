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
 * \author  Codasip (c) source generator
 * \version 9.1.1-1255
 */
#include "ia_riscv32i_cpp.h"

namespace codasip {
namespace simulator {
namespace ia_riscv32i {

Wrapper::Wrapper(const char* name, const char* codal_parameters)
 :  Foreign(name, codal_parameters)
{

}
void Wrapper::if_fetch_blocking_cb(ForeignPayload& fp)
{
    // Complete this method
    fp.SetData(0);
}
void Wrapper::ldst_blocking_cb(ForeignPayload& fp)
{
    // Complete this method
    fp.SetData(0);
}
} // namespace ia_riscv32i
} // namespace simulator
} // namespace codasip
