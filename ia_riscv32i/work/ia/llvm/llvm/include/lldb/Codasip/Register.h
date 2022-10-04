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
 *  \date   Nov 6, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_LLDB_CODASIP_REGISTER_H_
#define INCLUDE_LLDB_CODASIP_REGISTER_H_

// Project includes
#include "lldb/Codasip/Resource.h"

namespace codasip {

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  Register
 *  \brief  Information about register.
 */
class Register : public Resource
{
public:
    /**
     *  \{
     *  \brief Constructor
     */
    Register(
        // resource generic
        const std::string& name,
        const uint32_t dwarf,
        const uint32_t uid,
        const uint32_t bitWidth,
        const lldb::Encoding encoding,
        const lldb::Format format,
        const std::string& set,
        const std::string& description,
        // register specific
        const uint32_t gcc,
        const uint32_t offset,
        const std::string& generic,
        const bool arch,
        const std::string& pipeline);
    /**
     *  \}
     *  \{
     *  \brief Getter
     */
    uint32_t GetGcc() const;
    uint32_t GetOffset() const;
    const std::string& GetGeneric() const;
    const std::string& GetPipeline() const;
    bool IsArch() const;
    /// \}

private:
    /// Gcc index
    uint32_t m_Gcc;
    /// Gcc index
    uint32_t m_Offset;
    /// Port direction
    const std::string m_Generic;
    /// info whether the register is architectural or not
    bool m_IsArch;
    /// Pipeline assignment
    const std::string m_Pipeline;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Register::GetGcc() const
{
    return m_Gcc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t Register::GetOffset() const
{
    return m_Offset;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const std::string& Register::GetGeneric() const
{
    return m_Generic;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Register::IsArch() const
{
    return m_IsArch;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const std::string& Register::GetPipeline() const
{
    return m_Pipeline;
}

}   // namespace codasip



#endif  // INCLUDE_LLDB_CODASIP_REGISTER_H_
