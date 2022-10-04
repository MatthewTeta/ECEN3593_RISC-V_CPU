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
 *  \date   2017-11-13
 *  \brief  Definition of the class codasip::resources::AxiLiteBus.
 */

#ifndef SIMULATORS_RESOURCES_CSR_AXI_LITE_BUS_H_
#define SIMULATORS_RESOURCES_CSR_AXI_LITE_BUS_H_

#include "simulator/resources/csr_axi_lite_initiator_interface.h"
#include "simulator/resources/csr_axi_lite_pac.h"
#include "simulator/resources/csr_axi_lite_target_interface.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_sentinel.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiLiteBus
 *  \brief  Implements bus interconnect for AMBA AXI4-Lite bus protocol.
 *  \}
 */
template<class _BusCore>
class AxiLiteBus : public _BusCore, public Sentinel
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
    AxiLiteBus(const std::string& name, const Uid uid, Args&&... args);
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
     *  \class  AxiLiteBus::DefaultSlave
     *  \brief  Respond to OOR requests
     */
    class DefaultSlave
    {
    public:
        DefaultSlave();
        void phs_address(payload_type& p);
        void phs_data_read(payload_type& p);
        void phs_data_write(payload_type& p);
        void phs_response_write(payload_type& p);

    private:
        AXIResponseCode m_Response;
        Command m_Command;
    };

    void phs_address_read(payload_type& p, const Phase);
    void phs_address_write(payload_type& p, const Phase);
    void phs_data_read(payload_type& p, const Phase);
    void phs_data_write(payload_type& p, const Phase);
    void phs_response_write(payload_type& p);
    payload_type* get_write_response();
    void LogOOR(const codasip_address_t);

    /// Slave in read request
    SlaveInterface* m_HandledSlaveRequestRead;
    /// Slave in write request
    SlaveInterface* m_HandledSlaveRequestWrite;
    /// Slave in response write
    SlaveInterface* m_HandledSlaveResponseWrite;
    /// Default slave (for decoder error response)
    DefaultSlave m_DefaultSlave;
    /// Write response produced in the current cock cycle
    payload_type m_ResponseWriteProduced;
    /// Old write response waiting to be read by master
    payload_type m_ResponseWritePending;
    /// Write response has been read by master
    bool m_ResponseWriteConsumed;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
template<typename... Args>
inline AxiLiteBus<_BusCore>::AxiLiteBus(const std::string& name, const Uid uid, Args&&... args)
  : _BusCore(name.substr(0, name.find_last_of('.')), std::forward<Args>(args)...)
  , Sentinel(name, uid)
  , m_HandledSlaveRequestRead(nullptr)
  , m_HandledSlaveRequestWrite(nullptr)
  , m_HandledSlaveResponseWrite(nullptr)
  , m_ResponseWriteConsumed(false)
{
    m_ResponseWriteProduced.reset(CP_AXI_READY);
    m_ResponseWritePending.reset(CP_AXI_READY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::reset()
{
    _BusCore::Reset();
    m_HandledSlaveRequestRead = nullptr;
    m_HandledSlaveRequestWrite = nullptr;
    m_HandledSlaveResponseWrite = nullptr;
    m_ResponseWriteProduced.reset(CP_AXI_READY);
    m_ResponseWritePending.reset(CP_AXI_READY);
    m_ResponseWriteConsumed = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::clock_cycle()
{
    _BusCore::ClockCycle();

    // consume the oldest write response
    if (m_ResponseWriteConsumed)
    {
        // get the oldest valid response
        auto* pResponse = get_write_response();
        if (pResponse)
        {
            pResponse->set_axi_valid(CP_AXI_INVALID);
        }
        m_ResponseWriteConsumed = false;
    }

    // produced -> pending
    if (m_ResponseWriteProduced.get_axi_valid() && !m_ResponseWritePending.get_axi_valid())
    {
        // m_ResponseWritePending = m_ResponseWriteProduced;
        m_ResponseWritePending.set_axi_resp(m_ResponseWriteProduced.get_axi_resp());
        m_ResponseWritePending.set_axi_valid(CP_AXI_VALID);
        m_ResponseWriteProduced.set_axi_valid(CP_AXI_INVALID);
    }

    // check for the pending write response (only if m_ResponseWriteProduced is empty/invalid)
    if (m_HandledSlaveResponseWrite && !m_ResponseWriteProduced.get_axi_valid())
    {
        m_HandledSlaveResponseWrite->transport(m_ResponseWriteProduced, CP_PHS_RESPONSE_WRITE);
        // response is valid
        if (m_ResponseWriteProduced.get_axi_valid())
        {
            m_HandledSlaveResponseWrite = nullptr;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::blocking_cb(payload_type& p, const Uid)
{
    const bool load = p.get_command() == CP_CMD_LOAD;
    const codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;
    typename _BusCore::SlaveInterface* slave = nullptr;

    this->GetSlaveInterface(oAddr, nAddr, slave, load);
    if (slave == nullptr)
    {   // do not throw, just log and store error
        LogOOR(oAddr);
        p.set_axi_resp(CP_AXI_DECERR);
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
inline void AxiLiteBus<_BusCore>::transport_cb(payload_type& p, const Phase phase, const Uid)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS_READ:
            phs_address_read(p, phase);
            break;
        case CP_PHS_ADDRESS_WRITE:
            phs_address_write(p, phase);
            break;
        case CP_PHS_DATA_READ:
            phs_data_read(p, phase);
            break;
        case CP_PHS_DATA_WRITE:
            phs_data_write(p, phase);
            break;
        case CP_PHS_RESPONSE_WRITE:
            phs_response_write(p);
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline AxiLiteBus<_BusCore>::DefaultSlave::DefaultSlave()
  : m_Response(CP_AXI_OKAY)
  , m_Command(CP_CMD_NONE)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::DefaultSlave::phs_address(payload_type& p)
{
    m_Response = (p.get_axi_valid() == CP_AXI_VALID) ? CP_AXI_DECERR : CP_AXI_OKAY;
    m_Command = p.get_command();
    p.set_axi_ready(CP_AXI_READY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::DefaultSlave::phs_data_read(payload_type& p)
{
    p.set_axi_resp(m_Response);
    p.set_axi_valid((m_Command != CP_CMD_NONE) ? CP_AXI_VALID : CP_AXI_INVALID);
    m_Response = CP_AXI_OKAY;
    m_Command = CP_CMD_NONE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::DefaultSlave::phs_data_write(payload_type& p)
{
    p.set_axi_resp(m_Response);
    p.set_axi_ready(CP_AXI_READY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::DefaultSlave::phs_response_write(payload_type& p)
{
    p.set_axi_resp(m_Response);
    p.set_axi_valid(CP_AXI_VALID);
    m_Response = CP_AXI_OKAY;
    m_Command = CP_CMD_NONE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::phs_address_read(payload_type& p, const Phase phase)
{
    // not finished yet
    if (m_HandledSlaveRequestRead != nullptr)
    {
        p.set_axi_ready(CP_AXI_WAIT);
        return;
    }
    // check that there is a slave
    const bool load = p.get_command() == CP_CMD_LOAD;
    codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;
    SlaveInterface* pSlave = nullptr;
    this->GetSlaveInterface(oAddr, nAddr, pSlave, load);

    // no interface found, route to the default
    if (pSlave == nullptr)
    {
        m_DefaultSlave.phs_address(p);
    }
    else
    {
        // do the communication
        p.set_address(nAddr);
        pSlave->transport(p, phase);
        p.set_address(oAddr);
        // is accepted, then
        if (p.get_axi_valid() == CP_AXI_VALID && p.get_axi_ready() == CP_AXI_READY)
        {
            m_HandledSlaveRequestRead = pSlave;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::phs_address_write(payload_type& p, const Phase phase)
{
    // not finished yet or the old write response has not been collected by the master
    if (m_HandledSlaveRequestWrite != nullptr ||
        (m_ResponseWritePending.get_axi_valid() && m_ResponseWriteProduced.get_axi_valid()))
    {
        p.set_axi_ready(CP_AXI_WAIT);
        return;
    }
    // check that there is a slave
    const bool load = p.get_command() == CP_CMD_LOAD;
    codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;
    SlaveInterface* pSlave = nullptr;
    this->GetSlaveInterface(oAddr, nAddr, pSlave, load);

    // no interface found, route to the default
    if (pSlave == nullptr)
    {
        m_DefaultSlave.phs_address(p);
    }
    // do not allow a different slave if another slave is waiting for a write response
    else if (m_HandledSlaveResponseWrite && pSlave != m_HandledSlaveResponseWrite)
    {
        p.set_axi_ready(CP_AXI_WAIT);
    }
    else
    {
        // do the communication
        p.set_address(nAddr);
        pSlave->transport(p, phase);
        p.set_address(oAddr);
        // is accepted, then
        if (p.get_axi_valid() == CP_AXI_VALID && p.get_axi_ready() == CP_AXI_READY)
        {
            m_HandledSlaveRequestWrite = pSlave;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::phs_data_read(payload_type& p, const Phase phase)
{
    // first check the default interface for OOR request
    m_DefaultSlave.phs_data_read(p);
    if (p.is_error())
    {
        return;
    }

    // no request is running and no error from default slave -> idle transaction
    if (m_HandledSlaveRequestRead == nullptr)
    {
        p.set_axi_valid(CP_AXI_INVALID);
        return;
    }

    // finish it
    const auto wasReady = p.get_axi_ready();
    m_HandledSlaveRequestRead->transport(p, phase);

    // check if the read data is valid
    if (p.get_axi_valid() == CP_AXI_VALID && wasReady == CP_AXI_READY)
    {
        m_HandledSlaveRequestRead = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::phs_data_write(payload_type& p, const Phase phase)
{
    // first check the default interface for OOR request
    m_DefaultSlave.phs_data_write(p);
    if (p.is_error())
    {
        return;
    }

    // no request is running and no error from default slave -> idle transaction
    if (m_HandledSlaveRequestWrite == nullptr)
    {
        p.set_axi_ready(CP_AXI_WAIT);
        return;
    }

    // finish it
    m_HandledSlaveRequestWrite->transport(p, phase);

    // check if the write data has been accepted
    if (p.get_axi_valid() == CP_AXI_VALID && p.get_axi_ready() == CP_AXI_READY)
    {
        m_HandledSlaveResponseWrite = m_HandledSlaveRequestWrite;
        m_HandledSlaveRequestWrite = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiLiteBus<_BusCore>::phs_response_write(payload_type& p)
{
    // first check the default interface for OOR request
    m_DefaultSlave.phs_response_write(p);
    if (p.is_error())
    {
        return;
    }

    // get the oldest write response
    auto* pResponse = get_write_response();
    if (pResponse)
    {
        p.set_axi_resp(pResponse->get_axi_resp());
        p.set_axi_valid(CP_AXI_VALID);

        if (p.get_axi_ready() == CP_AXI_READY)
        {
            // invalidate the response
            m_ResponseWriteConsumed = true;
        }
    }
    else
    {
        p.set_axi_valid(CP_AXI_INVALID);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline typename AxiLiteBus<_BusCore>::payload_type* AxiLiteBus<_BusCore>::get_write_response()
{
    // get the oldest response (either the pending one, or the newly produced one)
    return m_ResponseWritePending.get_axi_valid() ? &m_ResponseWritePending
        : m_ResponseWriteProduced.get_axi_valid() ? &m_ResponseWriteProduced
                                                  : nullptr;
}

/**
 *  \brief  Log error message describing no slave selection (out-of-range).
 *  \param  addr requested address causing the error
 */
template<class _BusCore>
void AxiLiteBus<_BusCore>::LogOOR(const codasip_address_t addr)
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature()
                               << "': no slave selected at address: 0x" << std::hex << addr;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATORS_RESOURCES_CSR_AXI_LITE_BUS_H_
