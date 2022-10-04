/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip s.r.o.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the property of
 * Codasip s.r.o. and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and proprietary to
 * Codasip s.r.o. and are protected by trade secret and copyright law.  In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Pavel Najman
 *  \date   Oct 23, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_INTERFACE_H_

#include "simulator/resources/csr_helpers.h"

namespace codasip {
namespace resources {

//#define DEBUG_OUTPUT_ENABLE
#ifdef DEBUG_OUTPUT_ENABLE
#    define DEBUG_OUTPUT(x) std::cout << x << std::endl
#else
#    define DEBUG_OUTPUT(x)
#endif

/**
 *  \class  codasip::resources::CacheRegistersInterface
 *  \brief  Cache registers' interface used by CacheInterface class.
 */
class CacheRegistersInterface
{
public:
    virtual ~CacheRegistersInterface() = default;
    /**
     *  \brief  Returns whether the D cache write through is enabled.
     */
    virtual bool IsWriteThroughEnabled() const = 0;
    virtual bool GetRequestFlag() const = 0;
    virtual bool IsICacheOperationAddress(const codasip_address_t) const = 0;
    virtual bool IsDCacheOperationAddress(const codasip_address_t) const = 0;
    virtual CacheOperation GetCacheOperation(const codasip_address_t) const = 0;
};

#ifdef DEBUG_OUTPUT
#    undef DEBUG_OUTPUT
#endif

}   // namespace resources
}   // namespace codasip
#endif   // SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_INTERFACE_H_
