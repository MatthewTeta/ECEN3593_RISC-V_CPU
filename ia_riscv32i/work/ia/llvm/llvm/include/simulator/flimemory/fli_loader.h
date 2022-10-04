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
 *  \brief  Definition of the class codasip::foreign::fli::LoaderSignal and
 *          codasip::foreign::fli::LoaderVariable.
 */

#ifndef FLIMEMORY_FLI_LOADER_H_
#define FLIMEMORY_FLI_LOADER_H_

#include "simulator/flimemory/fli_common.h"
#include "simulator/flimemory/foreign_common.h"

namespace codasip {
namespace foreign {
namespace fli {

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  LoaderSignal
 *  \brief  Provides simple wrapper for program/application loaders to initialize
 *          memory content of a VHDL signals. Uses FLI API to write actual data.
 *          Stores basic informations about the storage.
 *  \}
 */
class LoaderSignal : public ForeignStorage
{
public:
    /**
     *  \copydoc ForeignStorage()
     *  \param  ram handle to ram storage, takes ownership of the pointer
     */
    LoaderSignal(mtiSignalIdT* ram,
        const std::string& id,
        const codasip_address_t size,
        const uint32_t bitWidth);
    /**
     *  \brief  Deallocate stored array pointer.
     */
    ~LoaderSignal();
    /**
     *  \copydoc ForeignStorage::Write()
     */
    void Write(const std::string& data, const codasip_address_t addr) override;

private:
    /// local FLI handle to the register/memory array storage declared as VHDL signal
    mtiSignalIdT* m_Array;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline LoaderSignal::LoaderSignal(mtiSignalIdT* ram,
    const std::string& id,
    const codasip_address_t size,
    const uint32_t bitWidth)
  : ForeignStorage(id, size, bitWidth)
  , m_Array(ram)
{}

////////////////////////////////////////////////////////////////////////////////
inline LoaderSignal::~LoaderSignal()
{
    mti_VsimFree(m_Array);
    m_Array = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
inline void LoaderSignal::Write(const std::string& data, const codasip_address_t addr)
{
    mti_ForceSignal(m_Array[addr], const_cast<char*>(("2#" + data).c_str()), -1, MTI_FORCE_DEPOSIT, -1, -1);
}

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  LoaderVariable
 *  \brief  Provides simple wrapper for program/application loaders to initialize
 *          memory content of a VHDL variables. Uses FLI API to write actual data.
 *          Stores basic informations about the storage.
 *  \}
 */
class LoaderVariable : public ForeignStorage
{
public:
    /// underlying type return by FLI value functions
    typedef char ValueType;
    /**
     *  \copydoc ForeignStorage()
     *  \param  ram handle to ram storage
     */
    LoaderVariable(mtiVariableIdT* ram,
        const std::string& id,
        const codasip_address_t size,
        const uint32_t bitWidth);
    /**
     *  \brief  Destructor, deallocates value properly.
     */
    ~LoaderVariable();
    /**
     *  \copydoc ForeignStorage::Write()
     */
    void Write(const std::string& data, const codasip_address_t addr) override;

private:
    void ConvertValue(const std::string&);

    /// local FLI handle to the register/memory array storage declared as VHDL variable
    mtiVariableIdT* m_Array;
    /// pointer to the value, type depends on the bitwidth of the array element
    ValueType* m_Value;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
inline LoaderVariable::LoaderVariable(mtiVariableIdT* ram,
    const std::string& id,
    const codasip_address_t size,
    const uint32_t bitWidth)
  : ForeignStorage(id, size, bitWidth)
  , m_Array(ram)
  , m_Value(nullptr)
{
    m_Value = new ValueType[bitWidth];
}

////////////////////////////////////////////////////////////////////////////////
inline LoaderVariable::~LoaderVariable()
{
    mti_VsimFree(m_Array);
    delete[] m_Value;
    m_Array = nullptr;
    m_Value = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
inline void LoaderVariable::Write(const std::string& data, const codasip_address_t addr)
{
    ConvertValue(data);
    mti_SetVarValue(m_Array[addr], reinterpret_cast<mtiLongT>(m_Value));
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Convert string value in binary format (without any prefix like 0b)
 *          to the FLI value format and save it into the internal value buffer.
 *  \param  str value represented by a string in binary format
 */
inline void LoaderVariable::ConvertValue(const std::string& str)
{
    for (uint32_t ii = 0; ii < GetBitWidth(); ++ii)
    {
        m_Value[ii] = (str[ii] == '1') ? STD_LOGIC_1 : STD_LOGIC_0;
    }
}

}   // namespace fli
}   // namespace foreign
}   // namespace codasip

#endif   // FLIMEMORY_FLI_LOADER_H_
