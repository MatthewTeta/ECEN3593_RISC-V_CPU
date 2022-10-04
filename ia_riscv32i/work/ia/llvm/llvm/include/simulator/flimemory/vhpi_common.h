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
 *  \date   27. 7. 2017
 *  \brief  Implementation of commonly used functions and class around VHPI, e.g.
 *          class codasip::foreign::vhpi::AddressAccessor.
 */

#ifndef FLIMEMORY_VHPI_COMMON_H_
#define FLIMEMORY_VHPI_COMMON_H_

#include "simulator/flimemory/foreign_common.h"

#include <vhpi_user.h>

// VCS workarounds
#ifdef VCS

#    include <mhpi_user.h>

#    define vhpiU 0          // uninitialized
#    define vhpiX 1          // unknown
#    define vhpi0 2          // forcing 0
#    define vhpi1 3          // forcing 1
#    define vhpiZ 4          // high impedance
#    define vhpiW 5          // weak unknown
#    define vhpiL 6          // weak 0
#    define vhpiH 7          // weak 1
#    define vhpiDontCare 8   // don't care

// missing constants
#    define vhpiLogicVecVal vhpiEnumVecVal
#    define vhpiDeposit vhpiForce

// members of the vhpiValueT
#    define CODASIP_GET_VALUE_NUM_ELEMS(value_struct) value_struct.numscalars
#    define CODASIP_GET_VALUE_ENUMVS(value_struct) value_struct.value.enums
#    define CODASIP_GET_VALUE_ENUM(value_struct) value_struct.value.enumval

namespace {

/**
 *  \brief  Return VHPI handle to given object. Have to use MHPI because direct
 *          \em vhpi_handle_by_name() does not find the object. The VHPI path
 *          is "obfuscated", for example path:
 *          'top.dut.HDL_DUT_U.mem_as_all_0.storage.subblock0.RAM'
 *          is obfuscated to:
 *          ':\/top/dut/HDL_DUT_U\:MEM_AS_ALL_0:STORAGE:SUBBLOCK0:RAM'
 *  \param  path simple (Verilog) path/name
 *  \param  handle parent scope
 */
inline vhpiHandleT CodasipDoVhpiHandleByName(const char* path, vhpiHandleT handle)
{
    mhpi_initialize('.');
    auto mhpiHandle = mhpi_handle_by_name(const_cast<char*>(path), handle);
    auto vhpiHandle = static_cast<vhpiHandleT>(mhpi_get_vhpi_handle(mhpiHandle));
    mhpi_release_parent_handle(mhpiHandle);
    return vhpiHandle;
}

}   // anonymous namespace

#    define vhpi_handle_by_name(path, scope) CodasipDoVhpiHandleByName(path, scope)

#else
#    define CODASIP_GET_VALUE_NUM_ELEMS(value_struct) value_struct.numElems
#    define CODASIP_GET_VALUE_ENUMVS(value_struct) value_struct.value.enumvs
#    define CODASIP_GET_VALUE_ENUM(value_struct) value_struct.value.enumv
#endif

namespace codasip {
namespace foreign {
namespace vhpi {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  codasip::foreign::vhpi::ArrayIterator
 *  \brief  Wrapper class used to work with ::codasip::foreign::AddressAccessor.
 *  \}
 */
class ArrayIterator
{
public:
    /// local shortcut to target API handle type
    typedef vhpiHandleT HandleType;
    /// local shortcut to target addresses type
    typedef codasip_address_t AddressType;
    /**
     *  \brief  Access array element and move the iterator to the next element.
     *  \param  it source array iterator
     *  \return handle to array element pointed by given iterator
     */
    static HandleType Scan(HandleType it);
    /**
     *  \brief  Release/free previously created handle/object/iterator.
     *  \param  h source handle to release
     */
    static void Release(HandleType h);
    /**
     *  \brief  Create iterator to an array element.
     *  \param  array source array to iterate over
     */
    static HandleType CreateIterator(HandleType array);
    /**
     *  \brief  Return size of given array handle.
     *  \param  array source array
     *  \param  elem handle to single array element
     */
    static AddressType Size(HandleType array, HandleType elem);
};

/// \brief  Provide array address iteration using VHPI
typedef ::codasip::foreign::AddressAccessor<ArrayIterator> VhpiAddressAccessor;

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline ArrayIterator::HandleType ArrayIterator::Scan(HandleType it)
{
    return vhpi_scan(it);
}

////////////////////////////////////////////////////////////////////////////////
inline void ArrayIterator::Release(HandleType h)
{
    vhpi_release_handle(h);
}

////////////////////////////////////////////////////////////////////////////////
inline ArrayIterator::HandleType ArrayIterator::CreateIterator(HandleType array)
{
    return vhpi_iterator(vhpiIndexedNames, array);
}

////////////////////////////////////////////////////////////////////////////////
inline ArrayIterator::AddressType ArrayIterator::Size(HandleType array, HandleType elem)
{
    const auto as = vhpi_get(vhpiSizeP, array);
    const auto es = vhpi_get(vhpiSizeP, elem);
    return as / es;
}

}   // namespace vhpi
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_VHPI_COMMON_H_
