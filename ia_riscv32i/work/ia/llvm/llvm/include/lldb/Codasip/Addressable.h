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
 *  \author Martin Ministr
 *  \date   11. 12. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_LLDB_CODASIP_ADDRESSABLE_H_
#define INCLUDE_LLDB_CODASIP_ADDRESSABLE_H_

// C Includes
// C++ Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "Resource.h"

namespace codasip {

/**
 *  \class  Addressable
 *  \brief  Info about addressable resource
 */
class Addressable : public Resource
{
public:
    /**
     *  \{
     *  \brief  Constructor
     */
    Addressable()
      : Resource(),
        m_AddressBitWidth(0),
        m_WordBitWidth(0),
        m_ByteBitWidth(0),
        m_Endianness(lldb::eByteOrderInvalid)
    {}
    Addressable(
        // generic resource
        const std::string& name,
        const uint32_t dwarf,
        const uint32_t uid,
        const uint32_t bitWidth,
        const lldb::Encoding encoding,
        const lldb::Format format,
        const std::string& set,
        const std::string& messageText,
        const std::string& description,
        // addressable specific
        const uint32_t addressBitWidth,
        const uint32_t wordBitWidth,
        const uint32_t byteBitWidth,
        const std::string& endianness)
      : Resource(name, dwarf, uid, bitWidth, encoding, format, set, messageText, description),
        m_AddressBitWidth(addressBitWidth),
        m_WordBitWidth(wordBitWidth),
        m_ByteBitWidth(byteBitWidth),
        m_Endianness(lldb::eByteOrderInvalid)
    {
        if (endianness == "little")
        {
            m_Endianness = lldb::eByteOrderLittle;
        }
        else if (endianness == "big")
        {
            m_Endianness = lldb::eByteOrderBig;
        }
    }
    /** \}
     *  \{
     *  \brief  Getter
     */
    uint32_t GetAddressBitWidth() const;
    uint32_t GetWordBitWidth() const;
    uint32_t GetByteBitWidth() const;
    lldb::ByteOrder GetEndianness() const;
    bool IsValid() const override;
    /** \} */

private:
    /// Address bit-width
    uint32_t m_AddressBitWidth;
    /// Word bit-width
    uint32_t m_WordBitWidth;
    /// Byte bit-width
    uint32_t m_ByteBitWidth;
    /// Interface endianness
    lldb::ByteOrder m_Endianness;
};

inline uint32_t Addressable::GetAddressBitWidth() const
{
    return m_AddressBitWidth;
}

inline uint32_t Addressable::GetWordBitWidth() const
{
    return m_WordBitWidth;
}

inline uint32_t Addressable::GetByteBitWidth() const
{
    return m_ByteBitWidth;
}

inline lldb::ByteOrder Addressable::GetEndianness() const
{
    return m_Endianness;
}

inline bool Addressable::IsValid() const
{
    return Resource::IsValid() && m_WordBitWidth && m_ByteBitWidth &&
        m_Endianness != lldb::eByteOrderInvalid;
}

}   // namespace codasip

#endif  // INCLUDE_LLDB_CODASIP_ADDRESSABLE_H_
