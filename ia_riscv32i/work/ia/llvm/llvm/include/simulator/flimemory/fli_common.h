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
 *  \author Potesil Josef
 *  \date   29. 10. 2014
 *  \brief  Definitions of functions implementing common functionality using FLI
 *          API.
 */

#ifndef FLIMEMORY_FLI_COMMON_H_
#define FLIMEMORY_FLI_COMMON_H_

#include "simulator/flimemory/vpi_common.h"
#include "utility/check_condition.h"

#include <exception>
#include <functional>
#include <mti.h>
#include <string>

namespace codasip {
namespace foreign {
namespace fli {

/// bit values FLI including metavalues
enum : char
{
    STD_LOGIC_U = 0,
    STD_LOGIC_X,
    STD_LOGIC_0,
    STD_LOGIC_1,
    STD_LOGIC_Z,
    STD_LOGIC_W,
    STD_LOGIC_L,
    STD_LOGIC_H,
    STD_LOGIC_D
};

/**
 *  \internal
 *  \brief  Checks whether given argument represents valid memory handle and
 *          return pointer to the first element of the array.
 *  \param  ram actual argument handle
 *  \param  hdl source HDL path to given handle
 *  \param  prefix error message prefix
 *  \param  getObjType function object used to detect object type
 *  \param  getObjSubelements function object used to access first array element
 */
template<typename Array, typename TypeFunc, typename SubelemFunc>
inline Array* DoCheckArrayTypeAttributes(Array ram,
    const std::string& hdl,
    const std::string& prefix,
    TypeFunc&& getObjType,
    SubelemFunc&& getObjSubelements)
{
    CHECK_CONDITION(ram) << prefix << vpi::ERR_NULL_HANDLE_I << hdl << vpi::ERR_NULL_HANDLE_II;
    auto typeId = getObjType(ram);
    CHECK_CONDITION(mti_GetTypeKind(typeId) == MTI_TYPE_ARRAY)
        << prefix << "Handle to '" << hdl
        << "' must be a register/memory array, got:" << mti_GetTypeKind(typeId);
    CHECK_CONDITION(mti_TickLength(typeId) > 0)
        << prefix << "Failed to determine array size of '" << hdl << "'.";
    auto first = getObjSubelements(ram, NULL);
    try
    {   // must be logic (vector)
        CHECK_CONDITION(first &&
            ((mti_GetTypeKind(getObjType(first[0])) == MTI_TYPE_ARRAY) ||
                (mti_GetTypeKind(getObjType(first[0])) == MTI_TYPE_ENUM)))
            << prefix << "Failed to determine bit range of one array element of '" << hdl << "'.";
    }
    catch (std::exception&)
    {
        mti_VsimFree(first);
        first = nullptr;
        throw;
    }
    return first;
}

/**
 *  \{
 *  \internal
 *  \brief  Checks whether given argument represents valid memory handle and
 *          return pointer to the first element of the array.
 *  \param  ram actual argument handle
 *  \param  hdl source HDL path to given handle
 *  \param  prefix error message prefix
 */
inline mtiSignalIdT* CheckArrayAttributes(mtiSignalIdT ram,
    const std::string& hdl,
    const std::string& prefix = std::string())
{
    return DoCheckArrayTypeAttributes(ram,
        hdl,
        prefix,
        std::ptr_fun(mti_GetSignalType),
        std::ptr_fun(mti_GetSignalSubelements));
}
inline mtiVariableIdT* CheckArrayAttributes(mtiVariableIdT ram,
    const std::string& hdl,
    const std::string& prefix = std::string())
{
    return DoCheckArrayTypeAttributes(ram,
        hdl,
        prefix,
        std::ptr_fun(mti_GetVarType),
        std::ptr_fun(mti_GetVarSubelements));
}

/**
 *  \}
 *  \brief  Checks the Verilog HDL path and creates full hierarchical path.
 *          Removes leading "$root.".
 *  \param  hdl source Verilog HDL path
 */
inline std::string CheckFullHierPath(const std::string& hdl)
{
    return '.' + vpi::CheckFullHierPath(hdl);
}

}   // namespace fli
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_FLI_COMMON_H_
