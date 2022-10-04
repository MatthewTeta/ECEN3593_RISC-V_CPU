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
 *  \author Pavel Richtarik
 *  \date   Oct 11, 2017
 *  \brief  Definition of the class codasip::resources::TargetInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_TARGET_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_TARGET_INTERFACE_H_

#include "simulator/resources/csr_latency_interface.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::TargetInterface
 *  \brief  Base target interface for memory slave interfaces with separated
 *          address and data phase and optionally RW flag.
 *  \}
 */
template<class T, class M, class A, class R>
class TargetInterface : public LatencyInterface<T, M>, protected R
{
public:
    /// \brief  Concrete payload type used by this class
    typedef Payload<typename T::data_type> PayloadType;
    /// \brief  Interface base class
    typedef LatencyInterface<T, M> InterfaceBaseType;

    /// Number of bytes in word
    static const Index SUBBLOCKS = T::WORD_BITS / T::BYTE_BITS;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    TargetInterface(const std::string& name, const Uid uid, M* module = nullptr);

protected:
    void set_pending_rd_request(const bool);
    void set_pending_rd_request_latency(const unsigned);
    void set_pending_wr_request(const PayloadType&);
    void clock_cycle(const uint8_t newReady, const Phase phase);
    void reset(const uint8_t newReady);
    bool has_pending_wr_request_to_handle() const;
    const PayloadType& get_pending_wr_request_to_handle() const;

private:
    bool has_pending_rd_request() const;
    bool has_pending_wr_request() const;
    void handle_pending_wr_request(const uint8_t, const Phase);

    /// Info that the current request is read (needed for RAW hazard handling)
    bool m_ReadRequest;
    /// Current read latency
    unsigned m_ReadRequestLatency;
    /// Write request
    PayloadType m_OfRpD;
    PayloadType m_OfRpQ;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
inline TargetInterface<T, M, A, R>::TargetInterface(const std::string& name, const Uid uid, M* module)
  : InterfaceBaseType(name, uid, module)
  , m_ReadRequest(false)
  , m_ReadRequestLatency(0)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE void TargetInterface<T, M, A, R>::set_pending_rd_request(const bool set)
{
    m_ReadRequest = set;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE void TargetInterface<T, M, A, R>::set_pending_rd_request_latency(const unsigned latency)
{
    m_ReadRequestLatency = latency;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE void TargetInterface<T, M, A, R>::set_pending_wr_request(const PayloadType& p)
{
    m_OfRpD = p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE bool TargetInterface<T, M, A, R>::has_pending_rd_request() const
{
    return A::IS_READABLE && m_ReadRequest;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE bool TargetInterface<T, M, A, R>::has_pending_wr_request() const
{
    return A::IS_WRITABLE && m_OfRpD.get_command() == CP_CMD_WRITE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE bool TargetInterface<T, M, A, R>::has_pending_wr_request_to_handle() const
{
    return A::IS_WRITABLE && m_OfRpQ.get_command() == CP_CMD_WRITE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE const typename TargetInterface<T, M, A, R>::PayloadType&
TargetInterface<T, M, A, R>::get_pending_wr_request_to_handle() const
{
    return m_OfRpQ;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE void
TargetInterface<T, M, A, R>::handle_pending_wr_request(const uint8_t newQReady, const Phase phase)
{
    if (m_OfRpQ.get_command() == CP_CMD_WRITE)
    {
        InterfaceBaseType::transport_cb(m_OfRpQ, phase);
        m_OfRpQ.reset(newQReady);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE void TargetInterface<T, M, A, R>::clock_cycle(const uint8_t newReady, const Phase phase)
{
    // write data
    handle_pending_wr_request(newReady, phase);

    // write needs to be done in the following clock cycle
    PayloadType wp;
    R::DataPhase(wp);
    if (!wp.is_error() && has_pending_wr_request())
    {
        // flip-flop write request
        m_OfRpQ = m_OfRpD;
        m_OfRpD.reset(newReady);

        // solve RAW hazard in the case of BRAM and RW interface
        if (A::IS_READABLE && A::IS_WRITABLE && has_pending_rd_request() && m_ReadRequestLatency == 1)
        {
            // stall only valid requests
            if (!R::m_AddressPhasePayload.is_error())
            {
                R::Stall();
                m_ReadRequest = false;
            }
        }
    }
    R::clock_cycle(wp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class R>
RES_INLINE void TargetInterface<T, M, A, R>::reset(const uint8_t newReady)
{
    m_OfRpD.reset(newReady);
    m_OfRpQ.reset(newReady);
    R::reset();
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_TARGET_INTERFACE_H_
