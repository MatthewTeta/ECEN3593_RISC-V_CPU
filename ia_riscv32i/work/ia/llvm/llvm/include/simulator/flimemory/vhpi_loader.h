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
 *  \date   3. 6. 2016
 *  \brief  Definition of the class codasip::foreign::vhpi::Loader.
 */

#ifndef FLIMEMORY_VHPI_LOADER_H_
#define FLIMEMORY_VHPI_LOADER_H_

#include "simulator/flimemory/foreign_common.h"
#include "simulator/flimemory/vhpi_common.h"
#include "utility/check_condition.h"

namespace codasip {
namespace foreign {
namespace vhpi {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  Storage
 *  \brief  Provides simple wrapper for VHDL array/RAM signal/variable. Stores
 *          basic informations about the storage and provides method which
 *          should be used to store prepared value into the array.
 *  \}
 */
class Storage : public ForeignStorage, protected VhpiAddressAccessor
{
public:
    /// local shortcut to target API
    typedef vhpiValueT ValueType;
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
 *  \brief  Represents simple wrapper around VHDL array signals/variables and
 *          provides interface to write data into the storage. The loader uses
 *          native format(vhpiEnumVecVal) to write into VHDL signals/variables.
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
     *  \brief  Deallocates internally allocated space for value.
     */
    ~Loader();
    /**
     *  \brief  Write one byte of data into given storage index.
     *  \param  data source data to write in binary format/radix. The value
     *          should not contains any prefixes (like 0b).
     *  \param  addr index to the storage.
     */
    void Write(const std::string& data, const codasip_address_t addr) override;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline Storage::Storage(HandleType ram,
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
    vhpi_put_value(GetAddrHandle(addr), &m_Value, vhpiDeposit);
}

////////////////////////////////////////////////////////////////////////////////
inline Loader::Loader(HandleType ram,
    const std::string& id,
    const codasip_address_t size,
    const codasip_address_t bitWidth)
  : Storage(ram, id, size, bitWidth)
{
    // find out native format
    m_Value.format = vhpiObjTypeVal;
    m_Value.bufSize = 0;
    m_Value.value.str = NULL;
    vhpi_get_value(GetAddrHandle(0), &m_Value);

    switch (m_Value.format)
    {
        case vhpiEnumVal:
            break;
        case vhpiEnumVecVal:
            m_Value.bufSize = bitWidth * sizeof(vhpiEnumT);
            CODASIP_GET_VALUE_NUM_ELEMS(m_Value) = bitWidth;
            CODASIP_GET_VALUE_ENUMVS(m_Value) = new vhpiEnumT[bitWidth];
            break;
        default:
            THROW_ERROR() << "Unsupported VHPI value format: " << m_Value.format;
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
inline Loader::~Loader()
{
    switch (m_Value.format)
    {
        case vhpiEnumVal:
            break;
        case vhpiEnumVecVal:
            delete[] CODASIP_GET_VALUE_ENUMVS(m_Value);
            m_Value.bufSize = 0;
            CODASIP_GET_VALUE_ENUMVS(m_Value) = NULL;
            break;
        default:
            std::cerr << "Unsupported VHPI value format: " << m_Value.format;
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
inline void Loader::Write(const std::string& data, const codasip_address_t addr)
{
    if (m_Value.format == vhpiEnumVecVal)
    {
        const unsigned size = GetBitWidth();
        for (unsigned ii = 0; ii < size; ++ii)
        {
            CODASIP_GET_VALUE_ENUMVS(m_Value)[ii] = (data[ii] == '0') ? vhpi0 : vhpi1;
        }
    }
    else
    {
        CODASIP_GET_VALUE_ENUM(m_Value) = (data[0] == '0') ? vhpi0 : vhpi1;
    }
    Store(addr);
}

}   // namespace vhpi
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_VHPI_LOADER_H_
