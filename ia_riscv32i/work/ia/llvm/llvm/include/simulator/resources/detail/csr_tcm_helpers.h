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
 *  \brief  Helpers for parameters
 */

#ifndef SIMULATOR_RESOURCES_CSR_TCM_HELPERS_H_
#define SIMULATOR_RESOURCES_CSR_TCM_HELPERS_H_

#include <sstream>
#include <stdexcept>

namespace codasip {
namespace resources {
namespace detail {

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Declaration
//
///////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Return error message indicating invalid combination of base address and memory size
 *          is not aligned
 *  \param  componentName Name of the TCM component
 *  \param  baseAddress TCM parameter `base`
 *  \param  memorySize TCM parameter `size`
 */
template<typename T, typename U = T>
std::string MakeTcmParametersErrorMessage(const std::string& componentName,
    const T& baseAddress,
    const U& memorySize);

/**
 *  \brief  Check that base address is aligned to memory size, otherwise throw
 *  \param  componentName Name of the TCM component
 *  \param  baseAddress TCM parameter `base`
 *  \param  memorySize TCM parameter `size`
 */
template<typename T, typename U = T>
void VerifyTcmRuntimeParameters(const std::string& componentName,
    const T& baseAddress,
    const U& memorySize);

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Definition
//
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U = T>
std::string
MakeTcmParametersErrorMessage(const std::string& componentName, const T& baseAddress, const U& memorySize)
{
    std::ostringstream out;
    codasip::simulator::PrintHeader(codasip::simulator::LOG_TYPE_FATAL, 0, out);
    out << "Component: " << componentName
        << ", was initialized with invalid base address and memory size combination, base address "
           "must be aligned to size"
        << std::endl
        << "base address value: " << GetValue(baseAddress) << std::endl
        << "memory size value: " << GetValue(memorySize) << "." << std::endl;
    if (GetValueExpression(baseAddress))
    {
        codasip::simulator::PrintHeader(codasip::simulator::LOG_TYPE_FATAL, 0, out);
        out << "Expression resulting in base address value: " << GetValueExpression(baseAddress)
            << std::endl;
    }
    if (GetValueExpression(memorySize))
    {
        codasip::simulator::PrintHeader(codasip::simulator::LOG_TYPE_FATAL, 0, out);
        out << "Expression resulting in memorySize value: " << GetValueExpression(baseAddress)
            << std::endl;
    }
    return out.str();
}

template<typename T, typename U = T>
void VerifyTcmRuntimeParameters(const std::string& componentName, const T& baseAddress, const U& memorySize)
{
    if ((GetValue(memorySize) == 0) || (GetValue(baseAddress) % GetValue(memorySize) != 0))
    {
        throw std::runtime_error
            {detail::MakeTcmParametersErrorMessage(componentName, baseAddress, memorySize)};
    }
}
}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   //  SIMULATOR_RESOURCES_CSR_TCM_HELPERS_H_