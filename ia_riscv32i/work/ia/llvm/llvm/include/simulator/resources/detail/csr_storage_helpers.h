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
 *  \author Martin Moracek
 *  \date   Feb 23, 2016
 *  \brief  Common helpers for MemoryStorage and StorageSentinel
 */

#ifndef SIMULATOR_RESOURCES_CSR_STORAGE_HELPERS_H_
#define SIMULATOR_RESOURCES_CSR_STORAGE_HELPERS_H_

#include "simulator/resources/csr_helpers.h"

#include <limits>

namespace codasip {
namespace resources {
namespace detail {

/**
 *  \{
 *  \brief Truncates the given \p address using the fastest approach based on the alignment
 *  \tparam ADDR_BITS address bitwidth
 *  \tparam SIZE storage size
 *  \param  size storage size
 *
 *  \note These two functions differ only in what is evaluated at compile time vs runtime.
 *        They are culmped together so that they don't get out of sync easily.
 */
template<codasip_address_t SIZE, Index ADDR_BITS>
inline codasip_address_t TruncateAddress(const codasip_address_t address)
{
    // fix the maximum address
    return IsPowerOfTwo(SIZE)
        // aligned
        ? ((address << (sizeof(codasip_address_t) * CHAR_BIT - ADDR_BITS)) >>
              (sizeof(codasip_address_t) * CHAR_BIT - ADDR_BITS))
        // base size
        : address % SIZE;
}

template<Index ADDR_BITS>
inline codasip_address_t
TruncateAddress(const codasip_address_t address, const codasip_address_t size)
{
    // fix the maximum address
    return IsPowerOfTwo(size)
        // aligned
        ? ((address << (sizeof(codasip_address_t) * CHAR_BIT - ADDR_BITS)) >>
              (sizeof(codasip_address_t) * CHAR_BIT - ADDR_BITS))
        // base size
        : address % size;
}
/** \} */

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif
