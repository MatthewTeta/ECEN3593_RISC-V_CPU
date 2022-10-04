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
 *  \author Karel Vorechovksy
 *  \date   2020-9-17
 *  \brief  Helpers for memory parameter validation
 */

#ifndef SIMULATOR_RESOURCES_CSR_MEMORY_HELPERS_H_
#define SIMULATOR_RESOURCES_CSR_MEMORY_HELPERS_H_

#include "common/toolstypes.h"
#include "simulator/resources/csr_helpers.h"

namespace codasip {
namespace resources {
namespace detail {

//  Threshold for std::unordered_map as memory storage
extern codasip_address_t g_OneGibi;

/**
 *  \brief  Checks if memory size if a multiple of two
 *  \param  size memory size in bytes
 */
bool IsMemorySizeInvalid(const codasip_address_t size);

/**
 *  \brief  Return message with invalid value and expression with it if any
 *  \param  componentName name of the calling component
 *  \param  size memory size
 *  \param  sizeExpression associated size expression
 */
std::string MakeMemorySizeErrorMessage(const std::string& componentName,
    const codasip_address_t size,
    const char* const sizeExpression);

/**
 *  \brief  Return true if the memory size > one gibibyte
 *  \param  size  desired memory size
 */
bool UseSparseMemory(const codasip_address_t size);

/**
 *  \brief  Helper for LinearMemory initialization
 *  \param size  desired memory size
 */
codasip_address_t GetLinearMemoryInitSize(const codasip_address_t size);

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   //  SIMULATOR_RESOURCES_CSR_MEMORY_HELPERS_H_
