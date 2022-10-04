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
#ifndef IA_RISCV32I_CPP_3_H_
#define IA_RISCV32I_CPP_3_H_

/**
 *  \addtogroup COSINT Cosimulator interfaces
 *  \{
 */

/**
 *  \defgroup CPPINT C++ Interface
 *  \section S1 Resources
 *  This section contains lists of available resources.
 *
 *  \subsection SS2 Registers
 *  \li r_pc
 *
 *  \subsection SS3 Register files
 *  \li rf_xpr
 *
 */
/** \} */
#include "ia_riscv32i_foreign.h"

namespace codasip {
namespace simulator {
namespace ia_riscv32i {

/**
 *  \class  Wrapper
 *  \ingroup CPPINT
 */
class Wrapper : public Foreign
 {
public:
    typedef enum {
        CP_PHS_ADDRESS = 0,
        CP_PHS_DATA = 1,
        CP_PHS_DATA_READ = 2,
        CP_PHS_DATA_WRITE = 3,
        CP_PHS_ADDRESS_READ = 4,
        CP_PHS_ADDRESS_WRITE = 5,
        CP_PHS_RESPONSE_WRITE = 6
    }TransportPhaseCode;
    typedef enum {
        CP_CMD_NONE = 0,
        CP_CMD_READ = 2,
        CP_CMD_WRITE = 3,
        CP_CMD_DREAD = 130,
        CP_CMD_DWRITE = 131,
        CP_CMD_LOAD = 195
    }CommandCode;
    typedef enum {
        CP_AHB_WAIT = 0,
        CP_AHB_READY = 1
    }AHBReadyCode;
    typedef enum {
        CP_AHB_OKAY = 0,
        CP_AHB_ERROR = 1
    }AHBResponseCode;
    /**
     *  \brief  Wrapper
     */
    Wrapper(const char* name = "ia_riscv32i", const char* codal_parameters = nullptr);
    /**
     *  \brief  if_fetch_blocking_cb
     */
    virtual void if_fetch_blocking_cb(ForeignPayload& fp);
    /**
     *  \brief  ldst_blocking_cb
     */
    virtual void ldst_blocking_cb(ForeignPayload& fp);
};
} // namespace ia_riscv32i
} // namespace simulator
} // namespace codasip

#endif // IA_RISCV32I_CPP_3_H_
