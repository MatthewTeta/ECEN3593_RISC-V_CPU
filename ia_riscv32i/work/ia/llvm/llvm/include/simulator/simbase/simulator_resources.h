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
 * Codasip s.r.o. and are protected by trade secret and copyright law. In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Petr Hons
 *  \date   6. 10. 2015
 *  \brief  Declaration/Implementation of the class
 */

#ifndef _SIMULATOR_RESOURCES_H_
#define _SIMULATOR_RESOURCES_H_

#include "common/codasip_integer.h"                // MaxInt
#include "simulator/simbase/codasip_interface.h"   // Address
#include "simulator/simbase/simulator_path.h"      // Path
#include "utility/enumutils.h"

#include <string>
#include <type_traits>   // std::enable_if
#include <utility>       // std::forward
#include <vector>

namespace codasip {
namespace simulator {
// forward
class SimulatorPrivateInterface;
class ComponentBase;

/**
 * \brief Universal numeric ID for resources in single ASIP or level simulator instance.
 */
typedef uint16_t Uid;
/// Invalid UID
static const Uid INVALID_UID = Uid(-1);

/// All resource types described in class \ref ResourceInfo
CODASIP_ENUM_DEFAULT(Type,
    UNKNOWN,
    /// Unknown resource type
    UNKNOWN,

    // ASIP only resources
    /// Register resource
    REGISTER,
    /// Port resource
    PORT,
    /// Signal resource
    SIGNAL,
    /// Address space
    ADDRESS_SPACE,

    /// Interface
    INTERFACE,
    /// Cache
    CACHE,
    /// Arbiter
    ARBITER,
    /// Tcm
    TCM,
    /// Memory
    MEMORY,
    /// ASIP
    ASIP,
    /// User component
    COMPONENT,
    /// Module or instance
    NAMESPACE)

/**
 * \class ResourceInfo
 * \brief Basic class for all simulator resources description classes.
 */
class ResourceInfo
{
public:
    ResourceInfo()
      : m_Parent(nullptr){};
    /**
     * \brief Disable copy
     */
    ResourceInfo(const ResourceInfo&) = delete;
    ResourceInfo& operator=(const ResourceInfo&) = delete;
    /**
     * \brief Virtual destructor
     */
    virtual ~ResourceInfo() {}
    /**
     * \brief Return type of resource
     */
    virtual Type GetType() const = 0;
    /**
     * \brief Return Unique ID of resource
     */
    virtual Uid GetUid() const = 0;
    /**
     * \brief Return path of resource. If the resource has a parent, the path contains the parent
     *        path and the resource name. Otherwise (top level) the path is the resource name.
     */
    const char* GetPath() const
    {
        // lazy load on the first request (after all parents have been resolved)
        if (m_Path.empty())
        {
            m_Path = GetParent() ? std::string(GetParent()->GetPath()) + "." + GetName() : GetName();
        }
        return m_Path.c_str();
    };
    /**
     * \brief Return name of resource
     */
    virtual const std::string& GetName() const = 0;
    /**
     * \brief Return parent of the resource
     */
    const ResourceInfo* GetParent() const
    {
        return m_Parent;
    }
    /**
     * \brief Returns bitwidth of resource, if current object is MEMORY or INTERFACE,
     *        it returns size of a word
     */
    virtual unsigned GetBitWidth() const
    {
        return 0;
    }
    /**
     * \brief Return true if this resource is addressable
     */
    virtual bool IsAddressable() const
    {
        return false;
    }
    /**
     * \brief Set parent of the resource
     */
    void SetParent(ResourceInfo& parent)
    {
        m_Parent = &parent;
    }
    /**
     * \brief Accept this resource info to be used by visitor
     */
    template<class Visitor, class Hack = SimulatorPrivateInterface, class... Args>
    void Accept(Visitor&& visitor, Args&&... args) const;

private:
    /// Parent resource info
    ResourceInfo* m_Parent;
    // Resource path
    mutable std::string m_Path;
};

/**
 *  \class  RegisterInfo
 *  \brief  Describes simulator register and register files
 */
class RegisterInfo : public ResourceInfo
{
public:
    /**
     * \copydoc ResourceInfo::GetType
     */
    Type GetType() const override
    {
        return REGISTER;
    }
    /**
     * \brief Returns if register is architectural
     */
    virtual bool IsArchitectural() const = 0;
    /**
     * \brief Returns name of pipeline stage this register
     */
    virtual const std::string& GetPipelineStage() const = 0;
    /**
     * \brief Returns size of register file or 0 for single register.
     */
    virtual unsigned GetSize() const
    {
        return 0;
    }
};

/**
 *  \class  SignalInfo
 *  \brief  Describes simulator signal
 */
class SignalInfo : public ResourceInfo
{
public:
    /**
     * \copydoc ResourceInfo::GetType
     */
    Type GetType() const override
    {
        return SIGNAL;
    }
};

/**
 *  \class  PortInfo
 *  \brief  Describes simulator signal
 */
class PortInfo : public ResourceInfo
{
public:
    CODASIP_ENUM_CLASS_STR(PortDirection,
        /// INPUT PORT
        (IN, "in"),
        /// OUTPUT PORT
        (OUT, "out"),
        /// BIDIRECTIONAL PORT
        (INOUT, "inout"),
        /// UNKNOWN
        (UNDEF, "undefined"));

    PortInfo(const PortDirection& dir = UNDEF)
      : m_direction(dir)
    {}
    /**
     * \copydoc ResourceInfo::GetType
     */
    Type GetType() const override
    {
        return PORT;
    }
    /**
     * \brief Set port direction
     */
    void SetDirection(const PortDirection& dir)
    {
        m_direction = dir;
    }
    /**
     * \brief Returns port direction
     */
    PortDirection GetDirection() const
    {
        return m_direction;
    }
    /**
     * \brief Returns string representation of port direction
     */
    std::string GetDirectionStr() const
    {
        return m_direction.ToStr();
    }

private:
    /// holds the direction of port
    PortDirection m_direction;
};

/**
 *  \class  AddressableInfo
 *  \brief  Basic class for all resources that are accessed by address
 */
class AddressableInfo : public ResourceInfo
{
public:
    /**
     * \brief Returns LAU of interface / memory
     */
    virtual unsigned GetLAU() const = 0;
    /**
     * \brief Returns bit width of address
     */
    virtual unsigned GetAddrBitWidth() const = 0;
    /**
     * \brief Returns true if current resource is using big endianness, false for little
     */
    virtual bool IsBig() const = 0;
    /**
     * \copydoc ResourceInfo::IsAddressable
     */
    bool IsAddressable() const override
    {
        return true;
    }
};

/**
 *  \class  InterfaceInfo
 *  \brief  Describes simulator interface
 */
class InterfaceInfo : public AddressableInfo
{
public:
    typedef enum
    {
        FLAG_R = 1,
        FLAG_W = 1 << 1,
        FLAG_RW = FLAG_R | FLAG_W
    } Flag;
    /// Container type storing data alignment in bytes
    typedef std::vector<unsigned> DataAlignment;

    /**
     * \copydoc ResourceInfo::GetType
     */
    Type GetType() const override
    {
        return INTERFACE;
    }
    /**
     * \brief  Return flag of the interface
     */
    virtual Flag GetFlag() const = 0;
    /**
     *  \brief  Return allowed data alignment in bytes.
     */
    virtual const DataAlignment& GetDataAlignment() const = 0;
    /**
     * \brief Return true if given interface is readable
     */
    bool IsRead() const
    {
        return (GetFlag() & FLAG_R) != 0;
    }
    /**
     * \brief Return true if given interface is writable
     */
    bool IsWrite() const
    {
        return (GetFlag() & FLAG_W) != 0;
    }
};

/**
 *  \class  AddressSpaceInfo
 *  \brief  Describes simulator address space. Address spaces are not implemented as resources
 *          in simulator, but are implemented as functions. Therefore this class stores
 *          all attributes directly.
 */
class AddressSpaceInfo : public AddressableInfo
{
public:
    /// Type of namespace derived from type of information which can hold.
    typedef enum
    {   /// Address space can hold both program and data.
        AS_ALL,
        /// Address space can hold only program (executable data).
        AS_PROGRAM,
        /// Address space can hold only data.
        AS_DATA
    } AsType;

    AddressSpaceInfo(const Uid uid,
        const std::string& name,
        const AsType type,
        const unsigned bitWidth,
        const unsigned addrBits,
        const unsigned lau,
        const bool big,
        const bool isVirtual = false);
    /**
     * \copydoc ResourceInfo::GetType
     */
    Type GetType() const override
    {
        return ADDRESS_SPACE;
    }

    AsType GetAddressSpaceType() const;
    /**
     *  \brief Return true if given address space is virtual = created from VonNeuman
     *         interfaces writing data or instruction
     */
    bool IsVirtual() const;

    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override;
    /// \copydoc ResourceInfo::GetUid
    const std::string& GetName() const override;
    /// \copydoc ResourceInfo::GetUid
    unsigned GetBitWidth() const override;
    /// \copydoc AddressableInfo::GetUid
    unsigned GetLAU() const override;
    /// \copydoc AddressableInfo::GetUid
    unsigned GetAddrBitWidth() const override;
    /// \copydoc AddressableInfo::GetUid
    bool IsBig() const override;

private:
    Uid m_Uid;
    std::string m_Name;
    AsType m_AsType;
    unsigned m_WordBits;
    unsigned m_AddrBits;
    unsigned m_Lau;
    bool m_Big;
    bool m_Virtual;
};

/**
 *  \class  MemoryInfo
 *  \brief  Describes simulator memory
 */
class MemoryInfo : public AddressableInfo
{
public:
    /**
     * \copydoc ResourceInfo::GetType
     */
    Type GetType() const override
    {
        return MEMORY;
    }
    /**
     * \brief Returns size of memory in LAU
     */
    virtual Address GetSize() const = 0;
};

/**
 *  \class  ResourceLocation
 *  \brief  Describes single resource and the container it resides in. Both these information
 *          are needed to read or write to the resource.
 */
class ResourceAccess
{
public:
    /**
     * \brief  Constructor of invalid access
     */
    ResourceAccess();
    /**
     * \brief  Constructor
     */
    explicit ResourceAccess(ComponentBase& base, const ResourceInfo* info = nullptr);
    /**
     * \brief  Return true if this object describes valid container
     */
    bool IsValid() const;
    /**
     * \brief  Return true if this object describes both container and resource
     */
    bool IsResource() const;
    /**
     * \copydoc IsResource
     */
    explicit operator bool() const
    {
        return IsResource();
    }
    /**
     * \brief  Return container the resource resides in. Valid only if IsValid() returns true.
     */
    ComponentBase& GetContainer();
    /**
     * \brief  Return information about the resource. Valid only if IsValid() returns true.
     */
    const ResourceInfo* GetInfo() const;

    /// \copydoc ComponentBase::ResourceRead
    MaxInt ResourceRead(const Address addr = 0);
    /// \copydoc ComponentBase::ResourceRead
    MaxInt ResourceRead(const Address addr, const unsigned bc);
    /// \copydoc ComponentBase::ResourceWrite
    void ResourceWrite(const MaxInt& data, const Address addr = 0);
    /// \copydoc ComponentBase::ResourceWrite
    void ResourceWrite(const MaxInt& data, const Address addr, const unsigned bc);

private:
    ComponentBase* m_Base;
    const ResourceInfo* m_Info;
};

/**
 * \class  NamespaceInterface
 * \brief  Describes a namespace for the resource names. Can be ASIP, Component, or plain Namespace
 *         representing a module or an event.
 */
class NamespaceInterface : public ResourceInfo
{
public:
    /**
     * \brief  Construct
     * \param  component Component/ASIP in which the namespace resides
     */
    NamespaceInterface(ComponentBase& component);
    /**
     * \brief  Destruct
     */
    virtual ~NamespaceInterface();
    /**
     * \brief  Find a child namespace
     * \param  name Namespace name
     */
    NamespaceInterface* FindNamespace(const std::string& name) const;
    /**
     * \brief  Find an existing child namespace or create a new one
     * \param  name Namespace name
     */
    NamespaceInterface& GetNamespace(const std::string& name);
    /**
     * \brief  Return resource by namespace path (s0.s1.ev.ev1.res). If not found, NULL is returned.
     */
    virtual const ResourceInfo* GetResourceInfo(const Path& path) const;
    virtual ResourceInfo* GetResourceInfo(const Path& path);
    /**
     * \brief  Insert a resource into the namespace
     * \param  res Resource
     */
    void Insert(ResourceInfo& res);

private:
    typedef std::map<std::string, NamespaceInterface*> NamespacesContainer;
    typedef std::map<std::string, ResourceInfo*> ResourcesContainer;

    /// Nested namespaces
    NamespacesContainer m_Namespaces;
    /// Nested resources
    ResourcesContainer m_Resources;
    /// Component the namespace resides in
    ComponentBase& m_Component;
};

/**
 * \class ComponentBase
 * \brief Contains description of all child resources of component (ASIP, user component,
 *        etc.). Also stores extra information when describing ASIP (mostly default address spaces
 *        and program counter).
 *        Index in vector is UID of given resource (for faster lookup)
 */
class ComponentBase : public NamespaceInterface
{
public:
    using NamespaceInterface::GetResourceInfo;

    /**
     * \brief Constructor. Set this component in the namespace.
     */
    ComponentBase()
      : NamespaceInterface(*this){};
    /**
     *  \brief  Read resource. If the resource is addressable then address must be provided
     *          and entire word is read (memory, interface, address space).
     *  \param  resource UID of resource
     *  \param  addr Address (default 0)
     */
    virtual MaxInt ResourceRead(const Uid, const Address = 0)
    {
        return 0;
    }
    /**
     *  \brief  Read addressable resource using subblocks. Not addressable resources
     *          (ports, signals, etc.) cannot be read using this method.
     *  \param  resource UID of resource
     *  \param  addr Address
     *  \param  bc byte count
     */
    virtual MaxInt ResourceRead(const Uid, const Address, const unsigned)
    {
        return 0;
    }
    /**
     *  \brief  Write value to given resource. If the resource is addressable then address must be
     *          provided and entire word is written (memory, interface, address space).
     *  \param  resource UID of resource
     *  \param  data Data to be written.
     *  \param  addr Address (default 0).
     */
    virtual void ResourceWrite(const Uid, const MaxInt&, const Address = 0) {}
    /**
     *  \brief  Write value to given addressable resource using subblocks. Not addressable resources
     *          (ports, signals, etc.) cannot be written to using this method.
     *  \param  resource UID of resource
     *  \param  data Data to be written.
     *  \param  addr Address.
     *  \param  bc byte count.
     */
    virtual void ResourceWrite(const Uid, const MaxInt&, const Address, const unsigned) {}
    /**
     *  \{
     *  \brief  Get simulator instance or NULL if not ASIP.
     */
    SimulatorPrivateInterface* GetSimulator();
    const SimulatorPrivateInterface* GetSimulator() const;
    /**
     *  \}
     *  \brief  Insert info into container. Return true if info was inserted and not present already.
     *          False is returned when given object under the UID is already inserted into container
     */
    bool Register(ResourceInfo& info);
    /**
     * \brief Call Insert(info) only if given type is derived from ResourceInfo
     * \{
     */
    template<class T>
    typename std::enable_if<std::is_base_of<ResourceInfo, typename std::decay<T>::type>::value, bool>::type
    TryInsert(T& info)
    {
        Insert(info);
        return true;
    }
    template<class T>
    typename std::enable_if<!std::is_base_of<ResourceInfo, typename std::decay<T>::type>::value, bool>::type
    TryInsert(T&)
    {
        return false;
    }
    /**
     * \}
     */
    /**
     * \brief  Return resource by UID. If not found, NULL is returned.
     */
    const ResourceInfo* GetResourceInfo(const Uid uid) const;
    ResourceInfo* GetResourceInfo(const Uid uid);
    /**
     * \}
     * \brief  Return count of resources.
     */
    Uid GetResourcesCount() const;
    /**
     * \brief Recursively find resource by the path and return object describing access to the
     *        resource. If given resource is container, only description of container is returned
     *        (\see ResourceAccess).
     * \param[in]  path Path to resource
     * \return Object describing access of the resource
     */
    ResourceAccess FindResource(const char* path);

private:
    /// Container to store resource info, they are owned by the container. Index is UID of resource
    typedef std::vector<ResourceInfo*> ResourcesContainer;

    /// Container owning all resource information
    ResourcesContainer m_Resources;
};

/**
 * \class  Namespace
 * \brief  Namespace for resources representing a module, event or event instance.
 */
class Namespace : public NamespaceInterface
{
public:
    /**
     * \brief  Construct
     * \param  name         Namespace name
     * \param  component    Component in which the namespace resides
     */
    Namespace(const std::string& name, ComponentBase& component)
      : NamespaceInterface(component)
      , m_Name(name)
    {}

    /// \copydoc ResourceInfo::GetType
    Type GetType() const override
    {
        return NAMESPACE;
    }
    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override
    {
        return INVALID_UID;
    }
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override
    {
        return m_Name;
    }

private:
    std::string m_Name;
};

/**
 *  \brief  Contains description of user components. All components that derives from this class
 *          can be processed by debugger and its resource can be read from / written to.
 */
class Component : public ComponentBase
{
public:
    typedef std::vector<std::string> Arguments;

    Component(const std::string& name, const Uid uid)
      : m_Uid(uid)
      , m_Name(name)
    {
        auto pos = m_Name.rfind('.');
        if (pos != std::string::npos)
        {
            m_Name = m_Name.substr(pos + 1);
        }
    }
    /// \copydoc ResourceInfo::GetType
    Type GetType() const override
    {
        return COMPONENT;
    }
    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override
    {
        return m_Uid;
    }
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override
    {
        return m_Name;
    }
    /**
     * \brief Called from simulator. Can be overriden in user components to obtain command line args.
     * \param arguments
     * \return True if ok, false on error.
     */
    virtual bool SetArguments(const Arguments&)
    {
        return true;
    }

private:
    Uid m_Uid;
    std::string m_Name;
};

/**
 *  \class  CacheInfo
 *  \brief  Describes simulator cache as a component whose resources has unique uids within asip.
 */
class CacheInfo : public ComponentBase
{
public:
    /**
     *  \brief  Constructor.
     *  \param  name    Cache name.
     *  \param  uid Cache uid.
     */
    CacheInfo(const std::string& name, const Uid uid)
      : m_Uid(uid)
      , m_Name(name)
    {
        auto pos = m_Name.rfind('.');
        if (pos != std::string::npos)
        {
            m_Name = m_Name.substr(pos + 1);
        }
    }
    /// \copydoc ResourceInfo::GetType
    Type GetType() const override
    {
        return CACHE;
    }
    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override
    {
        return m_Uid;
    }
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override
    {
        return m_Name;
    }

private:
    /// Cache uid.
    Uid m_Uid;
    /// Cache name.
    std::string m_Name;
};

/**
 *  \class  ArbiterInfo
 *  \brief  Describes simulator arbiter as a component whose resources has unique uids within asip.
 */
class ArbiterInfo : public ComponentBase
{
public:
    /**
     *  \brief  Constructor.
     *  \param  name    Arbiter name.
     *  \param  uid Arbiter uid.
     */
    ArbiterInfo(const std::string& name, const Uid uid)
      : m_Uid(uid)
      , m_Name(name)
    {
        auto pos = m_Name.rfind('.');
        if (pos != std::string::npos)
        {
            m_Name = m_Name.substr(pos + 1);
        }
    }
    /// \copydoc ResourceInfo::GetType
    Type GetType() const override
    {
        return ARBITER;
    }
    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override
    {
        return m_Uid;
    }
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override
    {
        return m_Name;
    }

private:
    /// Arbiter uid.
    Uid m_Uid;
    /// Arbiter name.
    std::string m_Name;
};

/**
 *  \class  TcmInfo
 *  \brief  Describes simulator Tcm as a component whose resources has unique uids within asip.
 */
class TcmInfo : public ComponentBase
{
public:
    /**
     *  \brief  Constructor.
     *  \param  name    Tcm name.
     *  \param  uid Tcm uid.
     */
    TcmInfo(const std::string& name, const Uid uid)
      : m_Uid(uid)
      , m_Name(name)
    {
        auto pos = m_Name.rfind('.');
        if (pos != std::string::npos)
        {
            m_Name = m_Name.substr(pos + 1);
        }
    }
    /// \copydoc ResourceInfo::GetType
    Type GetType() const override
    {
        return TCM;
    }
    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override
    {
        return m_Uid;
    }
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override
    {
        return m_Name;
    }

private:
    /// Tcm uid.
    Uid m_Uid;
    /// Tcm name.
    std::string m_Name;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Visitor, class Hack, class... Args>
void ResourceInfo::Accept(Visitor&& visitor, Args&&... args) const
{
// NOTE: resolved conflict: dynamic_cast<> from devel, reinterpret_cast<> from 7269-lldb
#define RES_TYPE(e, c)                                                             \
    case e:                                                                        \
        visitor.Visit(dynamic_cast<const c&>(*this), std::forward<Args>(args)...); \
        break

    switch (GetType())
    {
        case NAMESPACE:
        case UNKNOWN:
            break;
            RES_TYPE(REGISTER, RegisterInfo);
            RES_TYPE(PORT, PortInfo);
            RES_TYPE(SIGNAL, SignalInfo);
            RES_TYPE(ADDRESS_SPACE, AddressSpaceInfo);
            RES_TYPE(INTERFACE, InterfaceInfo);
            RES_TYPE(CACHE, CacheInfo);
            RES_TYPE(ARBITER, ArbiterInfo);
            RES_TYPE(TCM, TcmInfo);
            RES_TYPE(MEMORY, MemoryInfo);
            RES_TYPE(ASIP, Hack);
            RES_TYPE(COMPONENT, Component);
    }
#undef RES_TYPE
}

}   // namespace simulator
}   // namespace codasip

#endif   // _SIMULATOR_RESOURCES_H_
