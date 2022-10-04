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
 *  \date   2017-08-04
 *  \brief  Definition of the class codasip::resources::AhbBus.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AHB_BUS_H_
#define SIMULATOR_RESOURCES_CSR_AHB_BUS_H_

#include "simulator/resources/csr_ahb_initiator_interface.h"
#include "simulator/resources/csr_ahb_pac.h"
#include "simulator/resources/csr_ahb_target_interface.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_sentinel.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AhbBus
 *  \brief  Implements bus interconnect for AMBA 3 AHB-Lite bus protocol.
 *  \}
 */
template<class _BusCore>
class AhbBus : public _BusCore, public Sentinel
{
public:
    /// \brief  Import slave interface typedef from the base class
    typedef typename _BusCore::SlaveInterface SlaveInterface;
    /// \brief  Import payload type from the slave interface
    typedef typename SlaveInterface::payload_type payload_type;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    template<typename... Args>
    AhbBus(const std::string& name, const Uid uid, Args&&... args);
    /**
     *  \brief  Reset bus (reset request logic)
     */
    void reset();
    /**
     *  \brief  Move one clock cycle further.
     */
    void clock_cycle();
    /**
     *  \brief  Interface callback for the master routing the transaction to the
     *          appropriate slave.
     *  \param  p source transaction payload
     *  \param  uid bus master identifier initiating the transaction
     */
    void blocking_cb(payload_type& p, const Uid uid);
    /**
     *  \copydoc blocking_cb()
     *  \param  phase transport phase identifier
     */
    void transport_cb(payload_type& p, const Phase phase, const Uid uid);

private:
    /**
     *  \class AhbBus::DefaultSlave
     *  \brief Respond to OOR requests, use 2 cycle error response.
     */
    class DefaultSlave
    {
    public:
        /**
         *  \brief  Default constructor, initialize default outputs.
         */
        DefaultSlave();
        /**
         *  \brief  Handle address phase by checking HTRANS, when asserted
         *          perform 2 cycle error response.
         *  \param  p source payload.
         */
        void DoAddrPhase(const payload_type& p);
        /**
         *  \brief  Handle data phase, store internal attributes to the payload.
         *  \param  p source payload to update
         */
        void DoDataPhase(payload_type& p);
        /**
         *  \brief  Move one clock cycle further.
         */
        void clock_cycle();

    private:
        /// pending request
        bool m_Request;
        /// ready -> busy -> ready
        AHBReadyCode m_Status;
        /// idle -> error -> error -> idle
        AHBResponseCode m_Response;
    };

    void DoAddrPhase(payload_type&, const Uid);
    void DoDataPhase(payload_type&, const Uid);
    void LogOOR(const codasip_address_t);

    /// slave in address phase
    SlaveInterface* m_HandledSlaveRequest;
    /// slave in data phase
    SlaveInterface* m_HandledSlaveFinish;
    /// slave used when no other slave has been selected
    DefaultSlave m_DefaultSlave;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
template<typename... Args>
inline AhbBus<_BusCore>::AhbBus(const std::string& name, const Uid uid, Args&&... args)
  : _BusCore(name.substr(0, name.find_last_of('.')), std::forward<Args>(args)...)
  , Sentinel(name, uid)
  , m_HandledSlaveRequest(nullptr)
  , m_HandledSlaveFinish(nullptr)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void AhbBus<_BusCore>::reset()
{
    _BusCore::Reset();
    m_HandledSlaveRequest = nullptr;
    m_HandledSlaveFinish = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void AhbBus<_BusCore>::clock_cycle()
{
    _BusCore::ClockCycle();
    m_DefaultSlave.clock_cycle();
    if (m_HandledSlaveRequest != nullptr)
    {
        m_HandledSlaveFinish = m_HandledSlaveRequest;
        m_HandledSlaveRequest = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void AhbBus<_BusCore>::blocking_cb(payload_type& p, const Uid)
{
    const codasip_address_t oAddr = p.get_address();
    const bool load = p.get_command() == CP_CMD_LOAD;
    codasip_address_t nAddr = 0;
    typename _BusCore::SlaveInterface* slave = nullptr;

    this->GetSlaveInterface(oAddr, nAddr, slave, load);
    if (slave == nullptr)
    {   // do not throw, just log and store error
        LogOOR(oAddr);
        p.set_ahb_hresp(CP_AHB_ERROR);
    }
    else
    {
        p.set_address(nAddr);
        slave->blocking(p);
        p.set_address(oAddr);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void AhbBus<_BusCore>::transport_cb(payload_type& p, const Phase phase, const Uid uid)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            DoAddrPhase(p, uid);
            return;
        case CP_PHS_DATA:
            DoDataPhase(p, uid);
            return;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline AhbBus<_BusCore>::DefaultSlave::DefaultSlave()
  : m_Request(false)
  , m_Status(CP_AHB_READY)
  , m_Response(CP_AHB_OKAY)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void AhbBus<_BusCore>::DefaultSlave::DoAddrPhase(const payload_type& p)
{
    m_Request = p.is_ahb_active_transfer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void AhbBus<_BusCore>::DefaultSlave::DoDataPhase(payload_type& p)
{
    p.set_ahb_hready(m_Status);
    p.set_ahb_hresp(m_Response);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void AhbBus<_BusCore>::DefaultSlave::clock_cycle()
{
    // pending request
    if (m_Request)
    {
        // 0 -> 1 error cycle
        if (m_Status == CP_AHB_READY)
        {
            m_Status = CP_AHB_WAIT;
            m_Response = CP_AHB_ERROR;
        }
        // 1 -> 2 error cycle
        else if (m_Status == CP_AHB_WAIT)
        {
            m_Status = CP_AHB_READY;
            m_Request = false;
        }
    }
    else
    {
        // 2 -> - error cycle
        if (m_Response == CP_AHB_ERROR)
        {
            m_Status = CP_AHB_READY;
            m_Response = CP_AHB_OKAY;
        }
    }
}

/**
 *  \brief  Address phase handling. Decodes the address of an incoming transaction
 *          and routes it to target slave. In case the decoding fails for valid
 *          transaction, an error response will be stored for the next 2 data phases.
 *  \param  p source transaction payload
 *  \param  phase transport phase identifier
 */
template<class _BusCore>
inline void AhbBus<_BusCore>::DoAddrPhase(payload_type& p, const Uid)
{
    // not finished yet
    if (m_HandledSlaveRequest != nullptr || m_HandledSlaveFinish != nullptr)
    {
        p.set_ahb_hready(CP_AHB_WAIT);
        return;
    }
    // check that there is a slave
    const bool load = p.get_command() == CP_CMD_LOAD;
    codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;

    m_HandledSlaveRequest = nullptr;
    this->GetSlaveInterface(oAddr, nAddr, m_HandledSlaveRequest, load);

    // no interface found, route to the default
    if (m_HandledSlaveRequest == nullptr)
    {
        m_DefaultSlave.DoAddrPhase(p);
    }
    else
    {
        // do the communication
        p.set_address(nAddr);
        m_HandledSlaveRequest->transport(p, CP_PHS_ADDRESS);
        p.set_address(oAddr);
        // is accepted, then
        if (p.get_ahb_hready() != CP_AHB_READY)
        {
            m_HandledSlaveRequest = nullptr;
        }
    }
}

/**
 *  \brief  Data phase handling. Routes the transaction based on stored slave
 *          selection register to target slave.
 *  \param  p source transaction payload
 *  \param  phase transport phase identifier
 */
template<class _BusCore>
inline void AhbBus<_BusCore>::DoDataPhase(payload_type& p, const Uid)
{
    // first check the default interface for OOR request
    m_DefaultSlave.DoDataPhase(p);
    if (p.is_error())
    {
        return;
    }

    // no request is running
    if (m_HandledSlaveFinish == nullptr)
    {
        p.set_ahb_hready(CP_AHB_READY);
        p.set_ahb_hresp(CP_AHB_OKAY);
        return;
    }
    // finish it
    m_HandledSlaveFinish->transport(p, CP_PHS_DATA);
    // check response, if we should not wait, finish
    if (p.get_ahb_hready() != CP_AHB_WAIT)
    {
        m_HandledSlaveFinish = nullptr;
    }
}

/**
 *  \brief  Log error message describing no slave selection (out-of-range).
 *  \param  addr requested address causing the error
 */
template<class _BusCore>
void AhbBus<_BusCore>::LogOOR(const codasip_address_t addr)
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature()
                               << "': no slave selected at address: 0x" << std::hex << addr;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AHB_BUS_H_
