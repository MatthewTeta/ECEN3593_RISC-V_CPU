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
 *  \author zdeny
 *  \date   Apr 9, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_LLDB_CODASIP_ADDRESSSPACE_H_
#define INCLUDE_LLDB_CODASIP_ADDRESSSPACE_H_

// C Includes
// C++ Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "Addressable.h"

namespace codasip {

/**
 *  \class  AddressSpace
 *  \brief  Info about one address space
 */
class AddressSpace : public Addressable
{
public:
    /// Type of the address space
    enum Type
    {
        /// no type is set
        eInvalid,
        /// Program address space
        eCode,
        /// Data address space
        eData,
        /// Data address space
        eCodeAndData,
    };
    /// Container for types that the address space handels. Only explicit types are here
    /// (i.e. types written in CodAL definition)
    typedef std::set<std::string> DataTypes;
    /// Container for registers that holds return variable
    typedef std::vector<uint32_t> FunctionResult;
    /**
     *  \{
     *  \brief  Constructor
     */
    AddressSpace();
    AddressSpace(
        // generic resource
        const std::string& name,
        const uint32_t dwarf,
        const uint32_t uid,
        const uint32_t bitWidth,
        const lldb::Encoding encoding,
        const lldb::Format format,
        const std::string& set,
        const std::string& description,
        // generic addressable
        const uint32_t addressBitWidth,
        const uint32_t wordBitWidth,
        const uint32_t byteBitWidth,
        const std::string& endianness,
        // address space specific
        const std::string& type,
        const bool isDefault,
        const DataTypes& dataTypes,
        const FunctionResult& functionResult);
    /** \} */
    /**
     *  \{
     *  \brief  Getter
     */
    uint32_t GetBitWidth() const override;
    Type GetType() const;
    bool IsDefault() const;
    const DataTypes& GetDataTypes() const;
    const FunctionResult& GeFunctionResult() const;
    bool IsValid() const;
    /** \} */
    /**
     *  \brief  Dump address space info to the given stream.
     */
    void Dump(lldb_private::Stream* s) const;

private:
    /// Type of the address space
    Type m_Type;
    /// Default address space
    bool m_Default;
    /// Handled types
    DataTypes m_DataTypes;
    /// Handled types
    FunctionResult m_FunctionResult;
};

inline AddressSpace::Type AddressSpace::GetType() const
{
    return m_Type;
}

inline bool AddressSpace::IsDefault() const
{
    return m_Default;
}

inline const AddressSpace::DataTypes& AddressSpace::GetDataTypes() const
{
    return m_DataTypes;
}

inline const AddressSpace::FunctionResult& AddressSpace::GeFunctionResult() const
{
    return m_FunctionResult;
}

inline bool AddressSpace::IsValid() const
{
    return Addressable::IsValid() && m_Type != eInvalid;
}

}   // namespace codasip

#endif  // INCLUDE_LLDB_CODASIP_ADDRESSSPACE_H_
