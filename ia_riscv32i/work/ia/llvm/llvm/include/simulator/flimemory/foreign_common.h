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
 *  \date   19. 3. 2014
 *  \brief  Contains common definitions used by foreign (FLI/VPI/VHPI) memory
 *          implementations.
 */

#ifndef _FOREIGN_COMMON_H_
#define _FOREIGN_COMMON_H_

#include "common/toolstypes.h"   // codasip_address_t

#include <limits>
#include <map>
#include <string>

/**
 *  \defgroup FOREIGN_MEMORY Foreign memory library
 *  Implements libraries used load data into RTL memories from executable
 *  programs and read data from RTL memories. The library uses HDL and vendor
 *  specific API to do that. Supported interfaces are:
 *  \li <em>Verilog Procedural Interface (VPI)</em>
 *  \li <em>VHDL Procedural Interface (VHPI)</em>
 *  \li <em>Foreign Language Interface</em> by <em>Mentor Graphics</em>
 */

namespace codasip {
namespace foreign {

/**
 *  \ingroup FOREIGN_MEMORY
 *  \var    BOOTSTRAP_FUNCTION
 *  \brief  Defines name of a bootstrap function used by RTL plugins to
 *          initialize and register additional tasks/functions/callbacks/...
 */
static const char* const BOOTSTRAP_FUNCTION = "codasip_bootstrap";

namespace vpi {
/**
 *  \ingroup FOREIGN_MEMORY
 *  \var    MEMORY_INIT
 *  \brief  Defines function name which should be used to initialize memories
 *          using the VPI.
 */
static const char* const MEMORY_INIT = "$codasip_array_init";
/**
 *  \ingroup FOREIGN_MEMORY
 *  \var    MEMORY_READ
 *  \brief  Defines function name which should be used to read content of memory
 *          objects using the VPI.
 */
static const char* const MEMORY_READ = "$codasip_array_read";

}   // namespace vpi

namespace dpi {
/**
 *  \ingroup FOREIGN_MEMORY
 *  \var    MEMORY_INIT
 *  \brief  Defines function name which should be used to read content of memory
 *          objects using the DPI.
 */
static const char* const MEMORY_INIT = "codasip_dpi_array_init";

}   // namespace dpi

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  ForeignStorage
 *  \brief  Simple wrapper to hold basic informations about register/memory
 *          array storage.
 *  \}
 */
class ForeignStorage
{
public:
    /**
     *  \brief  Store internal attributes for later usage.
     *  \param  id user-friendly memory identifier (full hierarchical path)
     *  \param  size storage size in bytes
     *  \param  bitWidth storage bit-width (equal to the byte bit-width)
     */
    ForeignStorage(const std::string& id, const codasip_address_t size, const uint32_t bitWidth);
    /**
     *  \brief  Destructor
     */
    virtual ~ForeignStorage() {}
    /**
     *  \{
     *  \brief  Disable copy semantic.
     */
    ForeignStorage(const ForeignStorage&) = delete;
    ForeignStorage& operator=(const ForeignStorage&) = delete;
    /**
     *  \}
     *  \brief  Get memory size in bytes.
     */
    codasip_address_t GetSize() const;
    /**
     *  \brief  Return bit-width of the storage, equals to byte bit-width.
     */
    uint32_t GetBitWidth() const;
    /**
     *  \brief  Get user-friendly memory identifier.
     */
    const std::string& GetId() const;
    /**
     *  \brief  Update user-friendly storage identifier.
     *  \param  value new updated identifier
     */
    void SetId(const std::string& value);
    /**
     *  \brief  Writes data into storage, should be overridden in derived storage class.
     *  \param  data Binary data to be loaded into storage (string of '0' and '1')
     *  \param  addr Address where \em data should be stored
     */
    virtual void Write(const std::string& data, const codasip_address_t addr) = 0;

private:
    /// storage size in bytes
    const codasip_address_t m_Size;
    /// storage (byte) bit-width
    const uint32_t m_BitWidth;
    /// user-friendly memory identifier
    std::string m_Id;
};

/**
 *  \addtogroup FOREIGN_MEMORY
 *  \{
 *  \class  AddressAccessor
 *  \brief  Provides cached access to one-dimensional arrays from RTL simulator.
 *          It is designed to be used with VPI/VHPI.
 *  \tparam Implements API specific access, requires following items to be defined:
 *          \li \em CreateIterator() function to create handle to the array iterator
 *          \li \em Scan() function used to return handle to single array element
 *          and move the iterator to the next one
 *          \li \em Release() free previously created iterator
 *          \li \em HandleType member typedef to the handle type
 *  \}
 */
template<class Impl>
class AddressAccessor : private Impl
{
public:
    /// local shortcut to target API handle type
    typedef typename Impl::HandleType HandleType;
    /// local shortcut to target addresses type
    typedef typename Impl::AddressType AddressType;
    /**
     *  \brief  Default constructor.
     */
    AddressAccessor();
    /**
     *  \brief  Deallocates stored iterator if necessary.
     */
    ~AddressAccessor();
    /**
     *  \{
     *  \brief  Disable copy semantic.
     */
    AddressAccessor(const AddressAccessor&) = delete;
    AddressAccessor& operator=(const AddressAccessor&) = delete;
    /**
     *  \}
     *  \brief  Initialize handles for new RAM handle.
     *  \param  ram new updated value
     */
    void InitRam(HandleType ram);
    /**
     *  \brief  Return handle corresponding with given address to stored array.
     *  \param  addr source address
     */
    HandleType GetAddrHandle(const AddressType addr);

private:
    void Init();
    void DeInit();

    /// handle to source array/RAM
    HandleType m_RamH;
    /// iterator to the source array/RAM
    HandleType m_RamItH;
    /// handle to currently selected array/RAM element
    HandleType m_AddrH;
    /// address of currently selected array/RAM element
    AddressType m_Addr;
    /// highest address to the source array/RAM
    AddressType m_MaxAddr;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class Impl>
inline AddressAccessor<Impl>::AddressAccessor()
  : m_RamH(nullptr)
  , m_RamItH(nullptr)
  , m_AddrH(nullptr)
  , m_Addr(std::numeric_limits<AddressType>::max())
  , m_MaxAddr(std::numeric_limits<AddressType>::max())
{}

////////////////////////////////////////////////////////////////////////////////
template<class Impl>
inline AddressAccessor<Impl>::~AddressAccessor()
{
    DeInit();
}

////////////////////////////////////////////////////////////////////////////////
template<class Impl>
inline typename AddressAccessor<Impl>::HandleType
AddressAccessor<Impl>::GetAddrHandle(const AddressType addr)
{
    if (m_Addr != addr)
    {
        if (m_Addr > addr)
        {   // start from the beginning, release previous iterator
            DeInit();
            Init();
        }
        // move forward
        for (; (m_Addr < addr) && (m_AddrH != nullptr); ++m_Addr)
        {
            m_AddrH = Impl::Scan(m_RamItH);
        }
        if (m_AddrH == nullptr)
        {   // v(h)pi_scan released the iterator, clean it to avoid double
            // release in destructor (DeInit())
            m_RamItH = nullptr;
        }
        else if (addr == m_MaxAddr)
        {   // accessing the last address, expecting no more access
            // release the iterator to avoid false positive warnings about
            // incomplete iterations by Cadence simulators in PLI verbose mode
            DeInit();
        }
    }
    return m_AddrH;
}

////////////////////////////////////////////////////////////////////////////////
template<class Impl>
inline void AddressAccessor<Impl>::InitRam(HandleType ram)
{
    DeInit();
    m_RamH = ram;
    Init();
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Initialize iterator and address handle to point to the first address.
 */
template<class Impl>
inline void AddressAccessor<Impl>::Init()
{
    m_RamItH = Impl::CreateIterator(m_RamH);
    m_AddrH = Impl::Scan(m_RamItH);
    m_Addr = 0;
    m_MaxAddr = Impl::Size(m_RamH, m_AddrH) - 1;
}

/**
 *  \brief  Deallocate stored array iterator.
 */
template<class Impl>
inline void AddressAccessor<Impl>::DeInit()
{
    if (m_RamItH)
    {
        Impl::Release(m_RamItH);
        m_RamItH = nullptr;
    }
}

}   // namespace foreign
}   // namespace codasip

#endif   // _FOREIGN_COMMON_H_
