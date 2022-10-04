/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip s.r.o.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the
 * property of Codasip s.r.o.
 * Codasip s.r.o. and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and
 * proprietary to
 * Codasip s.r.o. and are protected by trade secret and copyright law.  In
 * addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio
 * product, including this
 * file, may be use, copied, modified, or distributed except in accordance with
 * the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 */

#ifndef INCLUDE_LLDB_CODASIP_PORT_H_
#define INCLUDE_LLDB_CODASIP_PORT_H_

// C Includes
// C++ Includes
//#include <memory>
//#include <string>
// C++ Includes
// Other libraries and framework includes
//#include "llvm/ADT/SmallVector.h"
//#include "lldb/Target/RegisterContext.h"
//#include "lldb/Target/StackFrame.h"
//#include "lldb/Target/Thread.h"

// Project includes
#include "lldb/Codasip/Resource.h"
//#include "lldb/Utility/StringExtractorGDBRemote.h"

namespace codasip {

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  Port
 *  \brief  Information about port.
 */
class Port : public Resource
{
public:
    /**
     *  \{
     *  \brief Constructor
     */
    Port(
        // resource generic
        const std::string& name,
        const uint32_t dwarf,
        const uint32_t uid,
        const uint32_t bitWidth,
        const lldb::Encoding encoding,
        const lldb::Format format,
        const std::string& set,
        const std::string& description,
        // port specific
        const std::string& direction,
        const std::string& type);
    /**
     *  \}
     *  \{
     *  \brief Getter
     */
    const std::string& GetDirection() const;
    const std::string& GetType() const;
    /// \}

    ResourceContext* CreateResourceContext(
        const lldb_private::ExecutionContext& context) const override;

private:
    /// Port direction
    std::string m_Direction;
    /// Port type
    std::string m_Type;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class PortContext : public ResourceContext
{
public:
    PortContext(lldb_private::Thread& thread, const lldb::offset_t byteSize);

    const Resource* GetResource(uint32_t dwarf) const override;
    const Resource* GetResource(const std::string& id, const lldb::addr_t addr = 0u) const override;
    uint32_t GetResourceSetCount() const override;
    ResourceSet* GetResourceSet(uint32_t index) const override;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const std::string& Port::GetDirection() const
{
    return m_Direction;
}

inline const std::string& Port::GetType() const
{
    return m_Type;
}

}   // namespace codasip

#endif // INCLUDE_LLDB_CODASIP_PORT_H_
