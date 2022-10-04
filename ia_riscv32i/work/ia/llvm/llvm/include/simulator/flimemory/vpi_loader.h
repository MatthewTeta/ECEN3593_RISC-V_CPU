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
 *  \brief  Definition of the class codasip::foreign::vpi::Loader.
 */

#ifndef FLIMEMORY_VPI_LOADER_H_
#define FLIMEMORY_VPI_LOADER_H_

#include "simulator/flimemory/foreign_common.h"
#include "simulator/flimemory/vpi_common.h"

#include <cstdlib>
#include <limits>

namespace codasip {
namespace foreign {
namespace vpi {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  codasip::foreign::vpi::Storage
 *  \brief  Provides simple wrapper for Verilog register or RAM variables.
 *          Stores basic informations about the storage.
 *  \}
 */
class Storage : public ForeignStorage, protected VpiAddressAccessor
{
public:
    /// local shortcut to target API
    typedef t_vpi_value ValueType;
    /**
     *  \copydoc ForeignStorage()
     *  \param  ram VPI handle to ram storage
     */
    Storage(HandleType ram,
        const std::string& id,
        const codasip_address_t size,
        const codasip_address_t bitWidth);

protected:
    /**
     *  \brief  Store prepared value into the array.
     *  \param  addr array address
     */
    void Store(const codasip_address_t addr);

    /// local variable used to write data using the VPI API
    ValueType m_Value;
};

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  Loader
 *  \brief  Represents simple wrapper around Verilog RAM variable and provides
 *          interface to write data into the storage. The loader uses binary
 *          string format to write into Verilog signals/registers.
 *  \}
 */
class Loader : public Storage
{
public:
    /**
     *  \copydoc Storage()
     */
    Loader(HandleType ram,
        const std::string& id,
        const codasip_address_t size,
        const codasip_address_t bitWidth);
    /**
     *  \brief  Write one byte of data into given storage index.
     *  \param  data source data to write in binary format/radix. The value
     *          should not contains any prefixes (like 0b).
     *  \param  addr index to the storage.
     */
    void Write(const std::string& data, const codasip_address_t addr);
};

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  FastLoader
 *  \brief  Represents simple wrapper around Verilog RAM variable and provides
 *          interface to write data into the storage with small bit-width and
 *          fast string to int conversion.
 *  \}
 */
class FastLoader : public Storage
{
public:
    enum : unsigned
    {   /// specify bit-width this loader is able to write into single array element
        MAX_BIT_WIDTH = std::numeric_limits<PLI_INT32>::digits + std::numeric_limits<PLI_INT32>::is_signed
    };
    /**
     *  \copydoc Storage()
     */
    FastLoader(HandleType ram,
        const std::string& id,
        const codasip_address_t size,
        const codasip_address_t bitWidth);
    /**
     *  \copydoc Loader::Write()
     */
    void Write(const std::string& data, const codasip_address_t addr);
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline Storage::Storage(vpiHandle ram,
    const std::string& id,
    const codasip_address_t size,
    const codasip_address_t bitWidth)
  : ForeignStorage(id, size, bitWidth)
{
    InitRam(ram);
}

////////////////////////////////////////////////////////////////////////////////
inline void Storage::Store(const codasip_address_t addr)
{
    vpi_put_value(GetAddrHandle(addr), &m_Value, NULL, vpiNoDelay);
}

////////////////////////////////////////////////////////////////////////////////
inline Loader::Loader(HandleType ram,
    const std::string& id,
    const codasip_address_t size,
    const codasip_address_t bitWidth)
  : Storage(ram, id, size, bitWidth)
{
    m_Value.format = vpiBinStrVal;
}

////////////////////////////////////////////////////////////////////////////////
inline void Loader::Write(const std::string& data, const codasip_address_t addr)
{
    m_Value.value.str = const_cast<PLI_BYTE8*>(data.c_str());
    Store(addr);
}

////////////////////////////////////////////////////////////////////////////////
inline FastLoader::FastLoader(HandleType ram,
    const std::string& id,
    const codasip_address_t size,
    const codasip_address_t bitWidth)
  : Storage(ram, id, size, bitWidth)
{
    m_Value.format = vpiIntVal;
}

////////////////////////////////////////////////////////////////////////////////
inline void FastLoader::Write(const std::string& data, const codasip_address_t addr)
{
    m_Value.value.integer = strtoul(data.c_str(), NULL, 2);
    Store(addr);
}

}   // namespace vpi
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_VPI_LOADER_H_
