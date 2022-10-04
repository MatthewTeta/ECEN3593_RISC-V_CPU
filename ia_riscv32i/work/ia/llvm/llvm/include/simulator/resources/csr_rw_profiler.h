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
 *  \author Zdenek Prikryl
 *  \date   Feb 23, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_RW_PROFILER_H_
#define SIMULATOR_RESOURCES_CSR_RW_PROFILER_H_

#include "common/toolstypes.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_storage_sentinel.h"

#include <type_traits>
#include <unordered_map>

namespace codasip {
namespace resources {
namespace detail {

/**
 *  \brief  Selects "optimal" underlying container holding counters used by the
 *          profiler statistics. Small arrays (2^20 items) use array for fast
 *          access, bigger arrays use sparse hash map.
 */
template<unsigned ADDR_BITS>
using Counters = std::unordered_map<typename TypeSelector<ADDR_BITS, false>::type, Counter>;

}   // namespace detail

template<class T, bool A = (T::SIZE != 1)>
class RwProfilerBase;

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \brief  Generic case used for arrays - SIZE > 1
 *  \}
 */
template<class T>
class RwProfilerBase<T, true> : public T
{
public:
    /// Counters of the read/write accesses
    typedef detail::Counters<T::ADDR_BITS> Counters;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    RwProfilerBase(const std::string& name, const Uid uid);
    /**
     *  \brief  Reset counters
     */
    void reset();
    /**
     *  \brief  Universal function for getting statistics
     */
    Counter stat(const profiler::AccessType at) const;
    Counter stat(const profiler::AccessType at, const codasip_address_t addr) const;
    /**
     *  \brief  Return raw data, usefull for profiler
     */
    const Counters& get_counter(const profiler::AccessType at) const;

protected:
    void check_read(const codasip_address_t addr = 0) const;
    void inc_read(const codasip_address_t addr = 0) const;
    void inc_write(const codasip_address_t addr = 0) const;

    /// Counters of the read accesses
    mutable Counters m_Read;
    /// Counters of the write accesses
    mutable Counters m_Write;

private:
    void log_uninitialized(const codasip_address_t addr) const;
};

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \brief  Specialization for SIZE == 1 (no map)
 *  \}
 */
template<class T>
class RwProfilerBase<T, false> : public T
{
public:
    /// Counters of the read/write accesses
    typedef detail::Counters<T::ADDR_BITS> Counters;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    RwProfilerBase(const std::string& name, const Uid uid);
    /**
     *  \brief  Reset counters
     */
    void reset();
    /**
     *  \brief  Universal function for getting statistics
     */
    Counter stat(const profiler::AccessType at, const codasip_address_t addr = 0) const;
    /**
     *  \brief  Return raw data, useful for profiler
     */
    const Counters& get_counter(const profiler::AccessType at) const;

protected:
    void check_read(const codasip_address_t addr = 0) const;
    void inc_read(const codasip_address_t addr = 0) const;
    void inc_write(const codasip_address_t addr = 0) const;

    /// Counters of the read accesses
    mutable Counter m_Read;
    /// Counters of the write accesses
    mutable Counter m_Write;
    /// Counters - [0] is filled with the requested counter and iterator is returned when
    /// get_counter is called
    mutable Counters m_Counters;

private:
    void log_uninitialized() const;
};

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  RwProfiler
 *  \brief  Profiler that counts read/write accesses
 *  \}
 */
template<class T>
class RwProfiler : public RwProfilerBase<T>
{
public:
    using typename T::data_type;
    using typename T::elem_param_type;
    using typename T::elem_type;
    using typename T::param_type;
    using typename T::payload_type;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    RwProfiler(const std::string& name, const Uid uid);
    /**
     *  \copydoc VariableStorage::read
     */
    data_type read(const codasip_address_t addr = 0) const;
    /**
     *  \copydoc VariableStorage::extract
     */
    elem_type extract(const codasip_address_t addr = 0) const;
    /**
     *  \copydoc VariableStorage::write
     */
    void write(param_type data, const codasip_address_t addr = 0);
    /**
     *  \copydoc VariableStorage::insert
     */
    void insert(elem_param_type data, const codasip_address_t addr);
    /**
     * \brief Return number of reads
     */
    Counter get_read() const;
    Counter get_read(const codasip_address_t addr) const;
    /**
     * \brief Return number of writes
     */
    Counter get_write() const;
    Counter get_write(const codasip_address_t addr) const;
    /**
     *  \copydoc PayloadSentinel::blocking
     */
    void blocking(payload_type& p);
    /**
     *  \copydoc PayloadSentinel::transport
     */
    void transport(payload_type& p, const Phase phase);
    /**
     * \brief Enables or disables read checking mechanism
     */
    void set_check_read(const bool check);
    /**
     * \brief If set, then the write is added when clock cycle is performed
     */
    void set_dff_mode(const bool dffMode);
    /**
     *  \copydoc DffStorage::stall
     */
    void stall();
    /**
     *  \copydoc DffStorage::gated
     */
    void gated();
    /**
     *  \copydoc DffStorage::clock_cycle
     */
    void clock_cycle();
    /**
     *  \copydoc DffStorage::reset
     */
    void reset();

private:
    /// Container for write addresses
    typedef std::vector<codasip_address_t> Addresses;

    void handle_payload(payload_type&);
    template<bool IsVector>
    typename std::enable_if<IsVector, elem_type>::type do_extract(const codasip_address_t) const;
    template<bool IsVector>
    typename std::enable_if<!IsVector, elem_type>::type do_extract(const codasip_address_t) const;
    template<bool IsVector>
    typename std::enable_if<IsVector>::type do_insert(elem_param_type, const codasip_address_t);
    template<bool IsVector>
    typename std::enable_if<!IsVector>::type do_insert(elem_param_type, const codasip_address_t);

    /// If true, the read are checked as well
    bool m_CheckRead;
    /// If true, the write is handed on clock_cycle
    bool m_DffMode;
    /// If true, the write is committed on clock_cycle
    bool m_Commit;
    /// Addresses stored for clock_cycle
    Addresses m_Addresses;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    Generic case - SIZE > 1                                     //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline RwProfilerBase<T, true>::RwProfilerBase(const std::string& name, const Uid uid)
  : T(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RwProfilerBase<T, true>::reset()
{
    m_Read.clear();
    m_Write.clear();
    T::reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfilerBase<T, true>::check_read(const codasip_address_t addr) const
{
    if (m_Write[addr] == 0)
    {
        log_uninitialized(addr);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfilerBase<T, true>::inc_read(const codasip_address_t addr) const
{
    ++m_Read[addr];
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfilerBase<T, true>::inc_write(const codasip_address_t addr) const
{
    ++m_Write[addr];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Counter RwProfilerBase<T, true>::stat(const profiler::AccessType at) const
{
    Counter ret = 0;
    for (const auto& it : get_counter(at))
    {
        ret += it.second;
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Counter
RwProfilerBase<T, true>::stat(const profiler::AccessType at, const codasip_address_t addr) const
{
    const codasip_address_t laddr = GetAlignedAddress<T>(
        StorageSentinel<typename T::data_type, T::SIZE>::get_address(addr));

    switch (at)
    {
        case profiler::ACCESS_READ:
            return m_Read[laddr];
        case profiler::ACCESS_WRITE:
            return m_Write[laddr];
        default:
            break;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline const typename RwProfilerBase<T, true>::Counters&
RwProfilerBase<T, true>::get_counter(const profiler::AccessType at) const
{
    switch (at)
    {
        case profiler::ACCESS_READ:
            return m_Read;
        case profiler::ACCESS_WRITE:
            return m_Write;
        default:
            break;
    }
    // silent compilers
    static Counters c;
    return c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RwProfilerBase<T, true>::log_uninitialized(const codasip_address_t addr) const
{
    RES_LOG(LOG_TYPE_WARNING, 0) << "using uninitialized resource: '" << this->get_signature()
                                 << "[" << addr << "]'" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Specialization - SIZE == 1 (no map)                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline RwProfilerBase<T, false>::RwProfilerBase(const std::string& name, const Uid uid)
  : T(name, uid)
  , m_Read(0)
  , m_Write(0)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RwProfilerBase<T, false>::reset()
{
    m_Read = 0;
    m_Write = 0;
    m_Counters.clear();
    T::reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfilerBase<T, false>::check_read(const codasip_address_t) const
{
    if (m_Write == 0)
    {
        log_uninitialized();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfilerBase<T, false>::inc_read(const codasip_address_t) const
{
    ++m_Read;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfilerBase<T, false>::inc_write(const codasip_address_t) const
{
    ++m_Write;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Counter
RwProfilerBase<T, false>::stat(const profiler::AccessType at, const codasip_address_t) const
{
    switch (at)
    {
        case profiler::ACCESS_READ:
            return m_Read;
        case profiler::ACCESS_WRITE:
            return m_Write;
        default:
            break;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline const typename RwProfilerBase<T, false>::Counters&
RwProfilerBase<T, false>::get_counter(const profiler::AccessType at) const
{
    switch (at)
    {
        case profiler::ACCESS_READ:
            m_Counters[0] = m_Read;
            break;
        case profiler::ACCESS_WRITE:
            m_Counters[0] = m_Write;
            break;
        default:
            break;
    }
    return m_Counters;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RwProfilerBase<T, false>::log_uninitialized() const
{
    RES_LOG(LOG_TYPE_WARNING, 0)
        << "using uninitialized resource: '" << this->get_signature() << "'" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Common implementation                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline RwProfiler<T>::RwProfiler(const std::string& name, const Uid uid)
  : RwProfilerBase<T>(name, uid)
  , m_CheckRead(false)
  , m_DffMode(false)
  , m_Commit(true)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename T::data_type RwProfiler<T>::read(const codasip_address_t addr) const
{
    const codasip_address_t laddr = GetAlignedAddress<T>(
        StorageSentinel<data_type, T::SIZE>::get_address(addr));

    if (m_CheckRead)
    {
        this->check_read(laddr);
    }
    this->inc_read(laddr);
    return T::read(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename T::elem_type RwProfiler<T>::extract(const codasip_address_t addr) const
{
    return this->template do_extract<detail::IsCodasipVectorHelper<data_type>::value>(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::write(param_type data, const codasip_address_t addr)
{
    const codasip_address_t laddr = GetAlignedAddress<T>(
        StorageSentinel<data_type, T::SIZE>::get_address(addr));

    if (m_DffMode)
    {
        m_Addresses.push_back(laddr);
    }
    else
    {
        this->inc_write(laddr);
    }
    T::write(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RwProfiler<T>::insert(elem_param_type data, const codasip_address_t addr)
{
    this->template do_insert<detail::IsCodasipVectorHelper<data_type>::value>(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::stall()
{
    m_Commit = false;
    T::stall();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::gated()
{
    m_Commit = false;
    T::gated();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::clock_cycle()
{
    if (m_DffMode)
    {
        if (m_Commit)
        {
            if (m_Addresses.size())
            {
                if (T::SIZE == 1)
                {
                    this->inc_write();
                }
                else
                {
                    for (size_t ii = 0; ii < m_Addresses.size(); ++ii)
                    {
                        this->inc_write(m_Addresses.at(ii));
                    }
                }
            }
        }
        m_Commit = true;
        m_Addresses.clear();
    }
    T::clock_cycle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::reset()
{
    if (m_DffMode)
    {
        m_Addresses.clear();
    }
    RwProfilerBase<T>::reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Counter RwProfiler<T>::get_read() const
{
    return this->stat(profiler::ACCESS_READ);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Counter RwProfiler<T>::get_read(const codasip_address_t addr) const
{
    return this->stat(profiler::ACCESS_READ, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Counter RwProfiler<T>::get_write() const
{
    return this->stat(profiler::ACCESS_WRITE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Counter RwProfiler<T>::get_write(const codasip_address_t addr) const
{
    return this->stat(profiler::ACCESS_WRITE, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::blocking(payload_type& p)
{
    T::blocking(p);
    handle_payload(p);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::transport(payload_type& p, const Phase phase)
{
    T::transport(p, phase);
    switch (phase)
    {
        case CP_PHS_ADDRESS:
        case CP_PHS_ADDRESS_READ:
        case CP_PHS_ADDRESS_WRITE:
            handle_payload(p);
            break;
        case CP_PHS_DATA:
        case CP_PHS_DATA_READ:
        case CP_PHS_DATA_WRITE:
        case CP_PHS_RESPONSE_WRITE:
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void RwProfiler<T>::handle_payload(payload_type& p)
{
    const codasip_address_t laddr = GetAlignedAddress<T>(
        StorageSentinel<data_type, T::SIZE>::get_address(p.get_address()));

    switch (p.get_command())
    {
        case CP_CMD_WRITE:
            this->inc_write(laddr);
            break;
        case CP_CMD_READ:
            if (m_CheckRead)
            {
                this->check_read(laddr);
            }
            this->inc_read(laddr);
            break;
        default:
            break;
    }
}

/**
 *  \brief  Read value of a single element of the vector if the RW profiler wraps
 *          vector data type.
 *  \param  addr element index
 */
template<class T>
template<bool IsVector>
RES_INLINE typename std::enable_if<IsVector, typename T::elem_type>::type
RwProfiler<T>::do_extract(const codasip_address_t addr) const
{
    if (m_CheckRead)
    {
        this->check_read(addr);
    }
    this->inc_read(addr);
    return T::extract(addr);
}

/**
 *  \brief  Do nothing - only for usage with non-vector data types.
 */
template<class T>
template<bool IsVector>
RES_INLINE typename std::enable_if<!IsVector, typename T::elem_type>::type
RwProfiler<T>::do_extract(const codasip_address_t addr) const
{
    return static_cast<elem_type>(0);
}

/**
 *  \brief  Perform insert of a single element into a vector variable if the RW profiler wraps
 *          vector data type.
 *  \param  data value to assign
 *  \param  addr element index
 */
template<class T>
template<bool IsVector>
inline typename std::enable_if<IsVector>::type
RwProfiler<T>::do_insert(elem_param_type data, const codasip_address_t addr)
{
    this->inc_write();
    T::insert(data, addr);
}

/**
 *  \brief  Do nothing - only for usage with non-vector data types.
 */
template<class T>
template<bool IsVector>
inline typename std::enable_if<!IsVector>::type
RwProfiler<T>::do_insert(elem_param_type, const codasip_address_t)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RwProfiler<T>::set_check_read(const bool check)
{
    m_CheckRead = check;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RwProfiler<T>::set_dff_mode(const bool dffMode)
{
    m_DffMode = dffMode;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_RW_PROFILER_H_
