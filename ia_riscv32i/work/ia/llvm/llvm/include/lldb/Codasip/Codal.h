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
 *  \author Albert Miko
 *  \date   2019-06-27
 *  \brief  Declaration of CodalContext.
 */

#ifndef INCLUDE_LLDB_CODASIP_CODAL_CONTEXT_H_
#define INCLUDE_LLDB_CODASIP_CODAL_CONTEXT_H_

// C Includes
// C++ Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "lldb/Codasip/Resource.h"

namespace codasip {

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  CodalVariable
 *  \brief  Information about signal.
 */
class CodalVariable : public Resource
{
public:
    /**
     *  \{
     *  \brief Constructor
     */
    CodalVariable(
        // resource generic
        const std::string& name,
        const uint32_t uid,
        const uint32_t bitWidth,
        const lldb::Encoding encoding,
        const lldb::Encoding vector_element_encoding,
        const size_t vector_size,
        const lldb::Format format,
        const std::string& set,
        const std::string& description,
        const lldb::addr_t scope_start_addr = 0,
        const lldb::addr_t scope_end_addr = UINT64_MAX);

    ResourceContext* CreateResourceContext(
        const lldb_private::ExecutionContext& context) const override;

    /// \return true if variable is defined at \a address
    bool IsValidInScope(lldb::addr_t address) const { return address >= m_scope_start_address && address <= m_scope_end_address; }
    /// \return lowest address where this variable is valid
    lldb::addr_t GetScopeStartAddress() const { return m_scope_start_address; }
    /// \return encoding of elements for vector types
    inline lldb::Encoding GetElementEncoding() const
    {
      return m_vector_element_encoding;
    }
    /// \return vector size for vector
    inline size_t GetVectorSize() const
    {
      return m_vector_size;
    }

private:
    lldb::Encoding m_vector_element_encoding;
    size_t m_vector_size;
    lldb::addr_t m_scope_start_address;
    lldb::addr_t m_scope_end_address;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class CodalContext : public ResourceContext
{
public:
    CodalContext(lldb_private::Thread& thread, const lldb::offset_t byteSize);

    const Resource* GetResource(uint32_t dwarf) const override;
    const Resource* GetResource(const std::string& id, const lldb::addr_t addr) const override;
    uint32_t GetResourceSetCount() const override;
    ResourceSet* GetResourceSet(uint32_t index) const override;

    static const uint32_t CODAL_VAR_DWARF_OFFSET = 3000000000ul;
};

}   // namespace codasip

#endif  // INCLUDE_LLDB_CODASIP_SIGNAL_H_
