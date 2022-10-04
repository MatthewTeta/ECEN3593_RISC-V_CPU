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
 *  \date   2. 11. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INCLUDE_LLDB_CODASIP_RESOURCE_H_
#define INCLUDE_LLDB_CODASIP_RESOURCE_H_

// C Includes
// C++ Includes
#include <string>
// Other libraries and framework includes
// Project includes
#include "lldb/lldb-enumerations.h"
#include "lldb/lldb-private.h"
//#include "lldb/lldb-types.h"
#include "lldb/Codasip/Defines.h"
#include "lldb/Utility/RegisterValue.h"
#include "lldb/Target/ExecutionContextScope.h"
#include "lldb/Utility/DataExtractor.h"
#include "lldb/Utility/Status.h"
#include "lldb/Utility/StreamString.h"

namespace lldb_private {
namespace process_gdb_remote {
class GDBRemoteCommunicationClient;
}   // namespace lldb_private::process_gdb_remote
}   // namespace lldb_private

namespace codasip {

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  Resource
 *  \brief  Information about resource.
 */
class Resource
{
public:
    /**
     *  \{
     *  \brief  Constructors
     */
    Resource();
    Resource(
        const std::string& name,
        const uint32_t dwarf,
        const uint32_t uid,
        const uint32_t bitWidth,
        const lldb::Encoding encoding,
        const lldb::Format format,
        const std::string& set,
        const std::string& messageText,
        const std::string& description);
    /**
     *  \}
     *  \{
     *  \brief  Destructor
     */
    virtual ~Resource()
    {}
    /**
     *  \}
     *  \{
     *  \brief  Getter
     */
    const std::string& GetName() const;
    uint32_t GetDwarf() const;
    uint32_t GetUid() const;
    virtual uint32_t GetBitWidth() const;
    uint32_t GetByteSize() const;
    lldb::Encoding GetEncoding() const;
    lldb::Format GetFormat() const;
    const std::string& GetSet() const;
    const std::string& GetMessageText() const;
    const std::string& GetDescription() const;
    virtual bool IsValid() const;
    // Operators
    bool operator==(const Resource& other) const;
    /// \}

    /**
     *  \brief  Create resource context of given resource.
     *          Caller is expected to free the memory afterwards.
     *          Cannot be abstract because it is needed in ValueObjectResource.
     *  \param[in]  context Execution context
     */
    virtual ResourceContext* CreateResourceContext(
        const lldb_private::ExecutionContext& context) const;

private:
    /// Resource name
    std::string m_Name;
    /// DWARF identifier
    uint32_t m_Dwarf;
    /// Codasip uid
    uint32_t m_Uid;
    /// Bit-width
    uint32_t m_BitWidth;
    /// Encoding
    lldb::Encoding m_Encoding;
    /// Print format
    lldb::Format m_Format;
    /// Resource set
    std::string m_Set;
    /// Message text (e.g., "port", "signal" ...)
    std::string m_MessageText;
    /// Resource description for IDE
    std::string m_Description;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \class  ResourceSet
 *  \brief  Represents set of resources.
 */
class ResourceSet
{
public:
    /// \brief Constructor
    ResourceSet(const std::string& name);
    /**
     *  \{
     *  \brief  Getter
     */
    const std::string& GetName() const;
    size_t GetResourceCount() const;
    size_t GetResourceDwarf(unsigned index) const;
    /**
     *  \}
     *  \brief  Setter
     */
    void AddResourceDwarf(uint32_t resourceDwarf);

    /// Resource set name
    const std::string m_Name;
    /// Resources, represented by their DWARF identifiers
    llvm::SmallVector<uint32_t, 8> m_Resources;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ResourceValue : public lldb_private::RegisterValue
{
using lldb_private::RegisterValue::RegisterValue;

public:
    lldb_private::Status SetValueFromData(
        const Resource& resource, lldb_private::DataExtractor& src);
    lldb_private::Status SetValueFromString(
        const Resource& resource, llvm::StringRef valueStr);

    bool Dump(
        lldb_private::Stream* s,
        const Resource& resource,
        bool prefixWithName,
        lldb::Format format,
        uint32_t portNameRightAlignAt) const;

private:
    static lldb_private::RegisterInfo GetRegisterInfo(const Resource& resource);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ResourceContext : public std::enable_shared_from_this<ResourceContext>,
    public lldb_private::ExecutionContextScope
{
public:
    ResourceContext(lldb_private::Thread& thread, const lldb::offset_t byteSize);

    bool WriteResource(const ResourceValue& value, const Resource& resource);
    bool ReadResource(ResourceValue& value, const Resource& resource);

    lldb::TargetSP CalculateTarget() override;
    lldb::ProcessSP CalculateProcess() override;
    lldb::ThreadSP CalculateThread() override;
    lldb::StackFrameSP CalculateStackFrame() override;
    void CalculateExecutionContext(lldb_private::ExecutionContext& context) override;

    /// \brief  Get byte size of the resource data.
    uint64_t GetByteSize() const;
    /**
     *  \brief  Get resource of given DWARF index.
     *  \param[in]  dwarf Resource DWARF index
     */
    virtual const Resource* GetResource(uint32_t dwarf) const = 0;
    /**
     *  \brief  Get resource of given id.
     *  \param[in]  id Resource identifier
     */
    virtual const Resource* GetResource(const std::string& id, const lldb::addr_t addr = 0u) const = 0;
    /// \brief  Get count of resource sets.
    virtual uint32_t GetResourceSetCount() const = 0;
    /**
     *  \brief  Get resource set of given index.
     *  \param[in]  index Resource set index
     */
    virtual ResourceSet* GetResourceSet(uint32_t index) const = 0;
    bool IsPortResourceContext() const;
    bool IsSignalResourceContext() const;

private:
    lldb_private::process_gdb_remote::GDBRemoteCommunicationClient* GetGdbClient() const;
    bool PrivateSetResourceValue(
        lldb_private::DataExtractor& port, llvm::ArrayRef<uint8_t>& data, const Resource& resource);

    /// Thread
    lldb_private::Thread& m_Thread;
    /// Resource data, has process byte order
    lldb_private::DataExtractor m_ResourceData;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const std::string& Resource::GetName() const
{
    return m_Name;
}

inline uint32_t Resource::GetDwarf() const
{
    return m_Dwarf;
}

inline uint32_t Resource::GetUid() const
{
    return m_Uid;
}

inline uint32_t Resource::GetBitWidth() const
{
    return m_BitWidth;
}

inline uint32_t Resource::GetByteSize() const
{
    return (GetBitWidth() + 7) / 8;
}

inline lldb::Encoding Resource::GetEncoding() const
{
    return m_Encoding;
}

inline lldb::Format Resource::GetFormat() const
{
    return m_Format;
}

inline const std::string& Resource::GetSet() const
{
    return m_Set;
}

inline const std::string& Resource::GetMessageText() const
{
    return m_MessageText;
}

inline const std::string& Resource::GetDescription() const
{
    return m_Description;
}

inline bool Resource::operator==(const Resource& other) const
{
    return m_Uid == other.GetUid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const std::string& ResourceSet::GetName() const
{
    return m_Name;
}

inline size_t ResourceSet::GetResourceCount() const
{
    return m_Resources.size();
}

inline void ResourceSet::AddResourceDwarf(uint32_t resourceDwarf)
{
    m_Resources.push_back(resourceDwarf);
}

}   // namespace codasip

#endif  // INCLUDE_LLDB_CODASIP_RESOURCE_H_
