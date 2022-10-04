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
 *  \date   Feb 22, 2016
 *  \brief  Definition of the class codasip::resources::AccessChecker.
 */

#ifndef SIMULATOR_RESOURCES_CSR_ACCESS_CHECKER_H_
#define SIMULATOR_RESOURCES_CSR_ACCESS_CHECKER_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"   // Logging

#include <array>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  AccessChecker
 *  \brief  Helps to detect multiple access to resources in CA mode. Most of the
 *          time the resources can be written only once, similarly CodAL
 *          interface can be accesses once per phase.
 *  \}
 */
template<class T>
class AccessChecker : public T
{
public:
    using typename T::data_type;
    using typename T::param_type;
    using typename T::payload_type;
    /**
     * \copydoc Sentinel::Sentinel
     */
    AccessChecker(const std::string& name, const Uid uid);
    /**
     * \{
     * \copydoc VariableStorage::read
     */
    data_type read(const codasip_address_t addr = 0) const;
    /**
     * \}
     * \{
     * \copydoc VariableStorage::write
     */
    void write(param_type data, const codasip_address_t addr = 0);
    /**
     * \copydoc PayloadSentinel::transport
     */
    void transport(payload_type& p, const Phase phase);
    /**
     * \{
     * \brief Reset counters
     */
    void reset();
    void clock_cycle();
    /**
     * \}
     * \brief Enable or disable
     * \param checkerLevel Variable with the level
     */
    void set_checker_level(const Index& checkerLevel);
    /**
     * \brief Set maximum of reads and writes in one clock cycle
     * \param read Maximum for reads (0 is unlimited)
     * \param read Maximum for writes (0 is unlimited)
     */
    void set_max(const Index read, const Index write);

private:
    static const unsigned WRITE_MAX = 1;
    static const unsigned TRANSPORT_MAX = 1;

    bool is_enabled() const;
    void log_read(const Index cnt) const;
    void log_write(const Index cnt) const;
    void log_transport(const Phase phase) const;

    /// Count of read access in current cycle
    Index m_ReadMax;
    /// Count of write access in current cycle
    Index m_WriteMax;
    /// Count of read access in current cycle
    mutable Index m_Read;
    /// Count of write access in current cycle
    mutable Index m_Write;
    /// Count of request access in current cycle
    mutable std::array<Index, CP_PHS_RESPONSE_WRITE + 1> m_Transport;
    /// local variable protecting accesses
    const Index* m_CheckerLevel;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline AccessChecker<T>::AccessChecker(const std::string& name, const Uid uid)
  : T(name, uid)
  , m_ReadMax(0)
  , m_WriteMax(WRITE_MAX)
  , m_Read(0)
  , m_Write(0)
  , m_Transport()
  , m_CheckerLevel(NULL)
{
    m_Transport.fill(0u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename T::data_type AccessChecker<T>::read(const codasip_address_t addr) const
{
    // check if checker is enabled
    if (is_enabled())
    {
        if (m_ReadMax && ++m_Read > m_ReadMax)
        {
            log_read(m_Read);
        }
    }
    return T::read(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AccessChecker<T>::write(param_type data, const codasip_address_t addr)
{
    // check if checker is enabled
    if (is_enabled())
    {
        if (m_WriteMax && ++m_Write > m_WriteMax)
        {
            log_write(m_Write);
        }
    }
    T::write(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AccessChecker<T>::transport(payload_type& p, const Phase phase)
{
    if (is_enabled())
    {
        if (++m_Transport[phase] > TRANSPORT_MAX)
        {
            log_transport(phase);
        }
    }
    return T::transport(p, phase);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AccessChecker<T>::reset()
{
    m_Read = 0;
    m_Write = 0;
    m_Transport.fill(0u);
    T::reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AccessChecker<T>::clock_cycle()
{
    m_Read = 0;
    m_Write = 0;
    m_Transport.fill(0u);
    T::clock_cycle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AccessChecker<T>::set_checker_level(const Index& checkerLevel)
{
    m_CheckerLevel = &checkerLevel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AccessChecker<T>::set_max(const Index read, const Index write)
{
    m_ReadMax = read;
    m_WriteMax = write;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE bool AccessChecker<T>::is_enabled() const
{
    return m_CheckerLevel != NULL && (*m_CheckerLevel) == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AccessChecker<T>::log_read(const Index cnt) const
{
    RES_LOG(LOG_TYPE_WARNING, 0)
        << "'" << this->get_signature() << "' has been read multiple times "
        << "in one clock. Read count: " << cnt << ". Allowed count:" << m_ReadMax;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AccessChecker<T>::log_write(const Index cnt) const
{
    RES_LOG(LOG_TYPE_WARNING, 0)
        << "'" << this->get_signature() << "' has been written multiple times "
        << "in one clock. Write count: " << cnt << ". Allowed count:" << m_WriteMax;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AccessChecker<T>::log_transport(const Phase phase) const
{
    std::string phaseSignature;
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            phaseSignature = "CP_PHS_ADDRESS";
            break;
        case CP_PHS_DATA:
            phaseSignature = "CP_PHS_DATA";
            break;
        case CP_PHS_DATA_READ:
            phaseSignature = "CP_PHS_DATA_READ";
            break;
        case CP_PHS_DATA_WRITE:
            phaseSignature = "CP_PHS_DATA_WRITE";
            break;
        case CP_PHS_ADDRESS_READ:
            phaseSignature = "CP_PHS_ADDRESS_READ";
            break;
        case CP_PHS_ADDRESS_WRITE:
            phaseSignature = "CP_PHS_ADDRESS_WRITE";
            break;
        case CP_PHS_RESPONSE_WRITE:
            phaseSignature = "CP_PHS_RESPONSE_WRITE";
            break;
    }
    RES_LOG(LOG_TYPE_WARNING, 0)
        << "transport phase " << phaseSignature << " on interface '" << this->get_signature()
        << "' has been called multiple times "
        << "in one clock. Count: " << m_Transport[phase] << ". Allowed count:" << TRANSPORT_MAX;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_ACCESS_CHECKER_H_
