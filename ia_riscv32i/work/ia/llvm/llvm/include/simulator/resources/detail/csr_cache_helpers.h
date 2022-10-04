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

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_HELPERS_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_HELPERS_H_

#include "common/toolstypes.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/detail/csr_memory_helpers.h"

#include <string>
#include <tuple>

namespace codasip {
namespace resources {
namespace detail {

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Declaration
//
///////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Return true if the cache parameters are invalid and do not meet the requirement
 *          of (size % lineSize) % numWays == 0
 *  \param  size cache size
 *  \param  lineSize cache line size
 *  \param  numWays cache num ways
 */
bool AreCacheParametersInvalid(const codasip_address_t size, const Index lineSize, const Index numWays);
/**
 *  \brief  Return error message explaining, that base address is not multiple of two
 *  \param  componentName name of the calling component
 *  \param  address faulty base address
 *  \param  expression associated expression
 */
std::string MakeBaseAddressErrorMessage(const std::string& componentName,
    const codasip_address_t address,
    const char* const expression);
/**
 *  \brief  Return error message explaining the requirement of (size % lineSize) % numWays == 0
 *          for cache parameters
 *  \param  componentName calling component name
 *  \param  size cache size
 *  \param  sizeExpression associated expression if any
 *  \param  lineSize cache line size
 *  \param  lineSizeExpression associated expression
 *  \param  numWays cache num ways
 *  \param  numWaysExpression associated expression
 */
std::string MakeLineSizeNotAlignedErrorMessage(const std::string& componentName,
    const codasip_address_t size,
    const char* const sizeExpression,
    const Index lineSize,
    const char* const lineSizeExpression,
    const Index numWays,
    const char* const numWaysExpression);

/**
 *  \brief Helper class to access the cache parameters represented as tuple elements
 *         containing the Either T or ValueWithExpression<T>
 *
 *         GetValue returns either native datatype for the value, or codasip_integer with length
 *         based on the type of codal parameter
 *
 *         GetExpression return const char* for the first most expression representing the value
 *         or nullptr if the value was compile time constant without parameter
 */
struct CacheRuntimeParametersGetter
{
    template<typename Parameters>
    static auto
    GetBaseAddress(const Parameters& parameters) -> decltype(GetValue(std::get<0>(parameters)));

    template<typename Parameters>
    static auto GetBaseAddressExpression(const Parameters& parameters)
        -> decltype(GetValueExpression(std::get<0>(parameters)));

    template<typename Parameters>
    static auto GetISize(const Parameters& parameters) -> decltype(GetValue(std::get<1>(parameters)));

    template<typename Parameters>
    static auto GetISizeExpression(const Parameters& parameters)
        -> decltype(GetValueExpression(std::get<1>(parameters)));

    template<typename Parameters>
    static auto GetDSize(const Parameters& parameters) -> decltype(GetValue(std::get<2>(parameters)));

    template<typename Parameters>
    static auto GetDSizeExpression(const Parameters& parameters)
        -> decltype(GetValueExpression(std::get<2>(parameters)));

    template<typename Parameters>
    static auto
    GetINumWays(const Parameters& parameters) -> decltype(GetValue(std::get<3>(parameters)));

    template<typename Parameters>
    static auto GetINumWaysExpression(const Parameters& parameters)
        -> decltype(GetValueExpression(std::get<3>(parameters)));

    template<typename Parameters>
    static auto
    GetDNumWays(const Parameters& parameters) -> decltype(GetValue(std::get<4>(parameters)));

    template<typename Parameters>
    static auto GetDNumWaysExpression(const Parameters& parameters)
        -> decltype(GetValueExpression(std::get<4>(parameters)));

    template<typename Parameters>
    static auto
    GetILineSize(const Parameters& parameters) -> decltype(GetValue(std::get<5>(parameters)));

    template<typename Parameters>
    static auto GetILineSizeExpression(const Parameters& parameters)
        -> decltype(GetValueExpression(std::get<5>(parameters)));

    template<typename Parameters>
    static auto
    GetDLineSize(const Parameters& parameters) -> decltype(GetValue(std::get<6>(parameters)));

    template<typename Parameters>
    static auto GetDLineSizeExpression(const Parameters& parameters)
        -> decltype(GetValueExpression(std::get<6>(parameters)));
};

/**
 *  \brief  Check the passed tuple containing the cache parameters and throw exception if the parameters
 *          are invalid
 *  \param  enabled is cache enabled
 *  \param  componentName name of the calling component
 *  \param  parameters tuple with parameters to check
 */
template<bool ENABLED, typename CacheRuntimeParameters>
void VerifyICacheParameters(const std::string& componentName, CacheRuntimeParameters& parameters);
/**
 *  \brief  Check the passed tuple containing the cache parameters and throw exception if the parameters
 *          are invalid
 *  \param  enabled is cache enabled
 *  \param  componentName name of the calling component
 *  \param  parameters tuple with parameters to check
 */
template<bool ENABLED, typename CacheRuntimeParameters>
void VerifyDCacheParameters(const std::string& componentName, CacheRuntimeParameters& parameters);
/**
 *  \brief  Check the passed tuple containing the parameters for both caches and base address
 *          perform the check only on caches that are enabled
 *  \param  componentName name of the calling component
 *  \param  parameters tuple containing cache parameters for both blocks
 */
template<typename IParams, typename DParams, typename CacheRuntimeParameters>
void VerifyCacheBlockRuntimeParameters(const std::string& componentName,
    const CacheRuntimeParameters& parameters);

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Definition
//
///////////////////////////////////////////////////////////////////////////////////////////////////
template<bool ENABLED, typename CacheRuntimeParameters>
void VerifyICacheParameters(const std::string& componentName, CacheRuntimeParameters& parameters)
{
    if (ENABLED)
    {
        typedef CacheRuntimeParametersGetter cp;
        const auto size = cp::GetISize(parameters);
        const auto lineSize = cp::GetILineSize(parameters);
        const auto numWays = cp::GetINumWays(parameters);

        if (IsMemorySizeInvalid(size))
        {
            throw std::runtime_error{detail::MakeMemorySizeErrorMessage(componentName,
                GetValue(cp::GetISize(parameters)),
                GetValueExpression(cp::GetISizeExpression(parameters)))};
        }
        if (AreCacheParametersInvalid(size, lineSize, numWays))
        {
            throw std::runtime_error{detail::MakeLineSizeNotAlignedErrorMessage(componentName,
                size,
                cp::GetISizeExpression(parameters),
                lineSize,
                cp::GetILineSizeExpression(parameters),
                numWays,
                cp::GetINumWaysExpression(parameters))};
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<bool ENABLED, typename CacheRuntimeParameters>
auto VerifyDCacheParameters(const std::string& componentName, CacheRuntimeParameters& parameters)
    -> void
{
    if (ENABLED)
    {
        typedef CacheRuntimeParametersGetter cp;
        const auto size = cp::GetDSize(parameters);
        const auto lineSize = cp::GetDLineSize(parameters);
        const auto numWays = cp::GetDNumWays(parameters);

        if (IsMemorySizeInvalid(size))
        {
            throw std::runtime_error{MakeMemorySizeErrorMessage(componentName,
                GetValue(cp::GetDSize(parameters)),
                GetValueExpression(cp::GetDSizeExpression(parameters)))};
        }
        if (AreCacheParametersInvalid(size, lineSize, numWays))
        {
            throw std::runtime_error{MakeLineSizeNotAlignedErrorMessage(componentName,
                size,
                cp::GetDSizeExpression(parameters),
                lineSize,
                cp::GetDLineSizeExpression(parameters),
                numWays,
                cp::GetDNumWaysExpression(parameters))};
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename IParams, typename DParams, typename CacheRuntimeParameters>
void VerifyCacheBlockRuntimeParameters(const std::string& componentName,
    const CacheRuntimeParameters& parameters)
{
    typedef CacheRuntimeParametersGetter cp;
    if ((cp::GetBaseAddress(parameters) % 2) != 0)
    {
        throw std::runtime_error{MakeBaseAddressErrorMessage(componentName,
            cp::GetBaseAddress(parameters),
            cp::GetBaseAddressExpression(parameters))};
    }
    VerifyICacheParameters<IParams::IS_ENABLED>(componentName + "program cache", parameters);
    VerifyDCacheParameters<DParams::IS_ENABLED>(componentName + "data cache", parameters);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetBaseAddress(const Parameters& parameters)
    -> decltype(GetValue(std::get<0>(parameters)))
{
    return GetValue(std::get<0>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetBaseAddressExpression(const Parameters& parameters)
    -> decltype(GetValueExpression(std::get<0>(parameters)))
{
    return GetValueExpression(std::get<0>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetISize(const Parameters& parameters)
    -> decltype(GetValue(std::get<1>(parameters)))
{
    return GetValue(std::get<1>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetISizeExpression(const Parameters& parameters)
    -> decltype(GetValueExpression(std::get<1>(parameters)))
{
    return GetValueExpression(std::get<1>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetDSize(const Parameters& parameters)
    -> decltype(GetValue(std::get<2>(parameters)))
{
    return GetValue(std::get<2>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetDSizeExpression(const Parameters& parameters)
    -> decltype(GetValueExpression(std::get<2>(parameters)))
{
    return GetValueExpression(std::get<2>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetINumWays(const Parameters& parameters)
    -> decltype(GetValue(std::get<3>(parameters)))
{
    return GetValue(std::get<3>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetINumWaysExpression(const Parameters& parameters)
    -> decltype(GetValueExpression(std::get<3>(parameters)))
{
    return GetValueExpression(std::get<3>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetDNumWays(const Parameters& parameters)
    -> decltype(GetValue(std::get<4>(parameters)))
{
    return GetValue(std::get<4>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetDNumWaysExpression(const Parameters& parameters)
    -> decltype(GetValueExpression(std::get<4>(parameters)))
{
    return GetValueExpression(std::get<4>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetILineSize(const Parameters& parameters)
    -> decltype(GetValue(std::get<5>(parameters)))
{
    return GetValue(std::get<5>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetILineSizeExpression(const Parameters& parameters)
    -> decltype(GetValueExpression(std::get<5>(parameters)))
{
    return GetValueExpression(std::get<5>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetDLineSize(const Parameters& parameters)
    -> decltype(GetValue(std::get<6>(parameters)))
{
    return GetValue(std::get<6>(parameters));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Parameters>
auto CacheRuntimeParametersGetter::GetDLineSizeExpression(const Parameters& parameters)
    -> decltype(GetValueExpression(std::get<6>(parameters)))
{
    return GetValueExpression(std::get<6>(parameters));
}

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   //  SIMULATOR_RESOURCES_CSR_CACHE_HELPERS_H_
