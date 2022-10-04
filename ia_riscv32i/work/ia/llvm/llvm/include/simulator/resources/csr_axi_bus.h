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
 *  \author Kamil Michl
 *  \date   Sep 24 2021
 *  \brief  Definition of the class codasip::resources::AxiBus.
 */

#ifndef SIMULATORS_RESOURCES_CSR_AXI_BUS_H_
#define SIMULATORS_RESOURCES_CSR_AXI_BUS_H_

#include "simulator/resources/csr_axi_initiator_interface.h"
#include "simulator/resources/csr_axi_pac.h"
#include "simulator/resources/csr_axi_target_interface.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_sentinel.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiBus
 *  \brief  Implements bus interconnect for AMBA AXI4 bus protocol.
 *  \}
 */
template<class _BusCore>
class AxiBus : public _BusCore, public Sentinel
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
    AxiBus(const std::string& name, const Uid uid, Args&&... args);
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
     *  \class  AxiBus::DefaultSlave
     *  \brief  Respond to OOR requests
     */
    class DefaultSlave
    {
    public:
        void reset();
        void PhsAddressRead(payload_type& p);
        void PhsDataRead(payload_type& p);
        void PhsAddressWrite(payload_type& p);
        void PhsDataWrite(payload_type& p);
        void PhsResponseWrite(payload_type& p);

    private:
        bool m_WriteDone = true;
        unsigned m_ResponseCountWrite = 0;
        unsigned m_ResponseCountRead = 0;
        uint8_t m_ReadId = 0;
        uint8_t m_WriteId = 0;
    };

    void PhsAddressRead(payload_type& p, const Phase);
    void PhsDataRead(payload_type& p, const Phase);
    void PhsAddressWrite(payload_type& p, const Phase);
    void PhsDataWrite(payload_type& p, const Phase);
    void PhsResponseWrite(payload_type& p);
    payload_type* GetWriteResponse();
    void LogOOR(const codasip_address_t);
    void UpdateBlockingErrorPayload(payload_type& p);

    /// Slave in read request
    SlaveInterface* m_HandledSlaveRequestRead = nullptr;
    /// Slave in write request
    SlaveInterface* m_HandledSlaveRequestWrite = nullptr;
    /// Slave in response write
    SlaveInterface* m_HandledSlaveResponseWrite = nullptr;
    /// Default slave (for decoder error response)
    DefaultSlave m_DefaultSlave;
    /// Write response produced in the current cock cycle
    payload_type m_ResponseWriteProduced;
    /// Old write response waiting to be read by master
    payload_type m_ResponseWritePending;
    /// Write response has been read by master
    bool m_ResponseWriteConsumed = false;

    /// Length of current blocking burst
    unsigned m_BlockingLength = 0;
    /// True if current blocking burst is write (false if read)
    bool m_BlockingBurstWrite = false;
    /// True if current blocking burst is handled by the default slave (OOR error)
    bool m_BlockingError = false;
    /// Pointer to a slave used by current blocking burst
    SlaveInterface* m_LastSlave = nullptr;
    bool m_WriteOOR = false;
    bool m_ReadOOR = false;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
template<typename... Args>
inline AxiBus<_BusCore>::AxiBus(const std::string& name, const Uid uid, Args&&... args)
  : _BusCore(name.substr(0, name.find_last_of('.')), std::forward<Args>(args)...)
  , Sentinel(name, uid)
{
    m_ResponseWriteProduced.reset(CP_AXI_READY);
    m_ResponseWritePending.reset(CP_AXI_READY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::reset()
{
    _BusCore::Reset();
    m_HandledSlaveRequestRead = nullptr;
    m_HandledSlaveRequestWrite = nullptr;
    m_HandledSlaveResponseWrite = nullptr;
    m_ResponseWriteProduced.reset(CP_AXI_READY);
    m_ResponseWritePending.reset(CP_AXI_READY);
    m_DefaultSlave.reset();
    m_ResponseWriteConsumed = false;
    m_WriteOOR = false;
    m_ReadOOR = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::clock_cycle()
{
    _BusCore::ClockCycle();

    // consume the oldest write response
    if (m_ResponseWriteConsumed)
    {
        // get the oldest valid response
        auto* pResponse = GetWriteResponse();
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
        m_ResponseWritePending.set_axi_id(m_ResponseWriteProduced.get_axi_id());
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
inline void AxiBus<_BusCore>::blocking_cb(payload_type& p, const Uid)
{
    // handle subsequent transaction in burst that has OOR error
    if (m_BlockingError)
    {
        if (m_BlockingLength > 0)
        {
            m_BlockingLength--;
        }
        if (m_BlockingLength == 0)
        {
            m_BlockingError = false;
        }
        UpdateBlockingErrorPayload(p);
    }

    // handle subsequent transaction in burst without error
    else if (m_BlockingLength > 0)
    {
        m_LastSlave->blocking(p);
        m_BlockingLength--;
    }

    // handle new burst
    else if (m_BlockingLength == 0)
    {
        m_BlockingLength = p.get_axi_len();
        const codasip_address_t oAddr = p.get_address();
        codasip_address_t nAddr = 0;
        this->GetSlaveInterface(oAddr, nAddr, m_LastSlave, p.get_command() == CP_CMD_LOAD);

        // handle OOR error response to first transaction
        if (m_LastSlave == nullptr)
        {
            // do not throw, just log and store error
            RES_LOG(LOG_TYPE_ERROR, 0)
                << "'" << this->get_signature() << "': no slave selected at address: 0x" << std::hex
                << oAddr << std::dec;
            // Mark payload as error and determine, how many subsequent payloads must be handled in the burst
            m_BlockingError = m_BlockingLength != 0;
            m_BlockingBurstWrite = p.get_command() == CP_CMD_WRITE ||
                p.get_command() == CP_CMD_DWRITE || p.get_command() == CP_CMD_LOAD;
            UpdateBlockingErrorPayload(p);
        }

        // handle normal response to first transaction (send it to slave)
        else
        {
            p.set_address(nAddr);
            m_LastSlave->blocking(p);
            p.set_address(oAddr);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::transport_cb(payload_type& p, const Phase phase, const Uid)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS_READ:
            PhsAddressRead(p, phase);
            break;
        case CP_PHS_ADDRESS_WRITE:
            PhsAddressWrite(p, phase);
            break;
        case CP_PHS_DATA_READ:
            PhsDataRead(p, phase);
            break;
        case CP_PHS_DATA_WRITE:
            PhsDataWrite(p, phase);
            break;
        case CP_PHS_RESPONSE_WRITE:
            PhsResponseWrite(p);
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::DefaultSlave::reset()
{
    m_ResponseCountRead = 0;
    m_ResponseCountWrite = 0;
    m_WriteDone = true;
    m_ReadId = 0;
    m_WriteId = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::DefaultSlave::PhsAddressRead(payload_type& p)
{
    if (m_ResponseCountRead == 0)
    {
        if (p.get_axi_valid() == CP_AXI_VALID)
        {
            m_ReadId = p.get_axi_id();
            m_ResponseCountRead = p.get_axi_len() + 1;
        }
        p.set_axi_ready(CP_AXI_READY);
    }
    else
    {
        p.set_axi_ready(CP_AXI_WAIT);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::DefaultSlave::PhsDataRead(payload_type& p)
{
    if (m_ResponseCountRead != 0)
    {
        p.set_axi_last((m_ResponseCountRead == 1) ? CP_AXI_LAST : CP_AXI_NOT_LAST);
        p.set_axi_valid(CP_AXI_VALID);
        p.set_axi_resp(CP_AXI_DECERR);
        p.set_axi_id(m_ReadId);
        if (p.get_axi_ready() == CP_AXI_READY)
        {
            m_ResponseCountRead--;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::DefaultSlave::PhsAddressWrite(payload_type& p)
{
    if (m_WriteDone)
    {
        if (p.get_axi_valid() == CP_AXI_VALID)
        {
            m_WriteDone = false;
            m_ResponseCountWrite = p.get_axi_len() + 1;
            m_WriteId = p.get_axi_id();
        }
        p.set_axi_ready(CP_AXI_READY);
    }
    else
    {
        p.set_axi_ready(CP_AXI_WAIT);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::DefaultSlave::PhsDataWrite(payload_type& p)
{
    if (m_ResponseCountWrite != 0)
    {
        p.set_axi_ready(CP_AXI_READY);
        if (p.get_axi_valid() == CP_AXI_VALID)
        {
            m_ResponseCountWrite--;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::DefaultSlave::PhsResponseWrite(payload_type& p)
{
    if (!m_WriteDone && m_ResponseCountWrite == 0 && p.get_axi_ready())
    {
        p.set_axi_valid(CP_AXI_VALID);
        p.set_axi_resp(CP_AXI_DECERR);
        p.set_axi_id(m_WriteId);
        m_WriteDone = true;
    }
    else
    {
        p.set_axi_valid(CP_AXI_INVALID);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::PhsAddressRead(payload_type& p, const Phase phase)
{
    // not finished yet
    if (m_HandledSlaveRequestRead != nullptr || m_ReadOOR)
    {
        p.set_axi_ready(CP_AXI_WAIT);
        return;
    }
    // check that there is a slave
    codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;
    SlaveInterface* pSlave = nullptr;
    this->GetSlaveInterface(oAddr, nAddr, pSlave, p.get_command() == CP_CMD_LOAD);

    // no interface found, route to the default
    if (pSlave == nullptr)
    {
        m_DefaultSlave.PhsAddressRead(p);
        m_ReadOOR = true;
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
inline void AxiBus<_BusCore>::PhsDataRead(payload_type& p, const Phase phase)
{
    // invalid is the default response if not specificaly set to valid afterwards
    p.set_axi_valid(CP_AXI_INVALID);
    // response must be reset, so the transaction will have error response
    //   only if default interface explicitly sets it
    p.set_axi_resp(CP_AXI_OKAY);

    if (m_ReadOOR)
    {
        // first check the default interface for OOR request
        m_DefaultSlave.PhsDataRead(p);
        m_ReadOOR = p.get_axi_last() != CP_AXI_LAST;
        return;
    }

    // no request is running and no error from default slave -> idle transaction
    if (m_HandledSlaveRequestRead == nullptr)
    {
        return;
    }

    // finish it
    const auto wasReady = p.get_axi_ready();
    m_HandledSlaveRequestRead->transport(p, phase);

    // check if the read data is valid
    if (p.get_axi_valid() == CP_AXI_VALID && wasReady == CP_AXI_READY && p.get_axi_last() == CP_AXI_LAST)
    {
        m_HandledSlaveRequestRead = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::PhsAddressWrite(payload_type& p, const Phase phase)
{
    // not finished yet or the old write response has not been collected by the master
    if (m_WriteOOR || m_HandledSlaveRequestWrite != nullptr || m_HandledSlaveResponseWrite != nullptr ||
        (m_ResponseWritePending.get_axi_valid() && m_ResponseWriteProduced.get_axi_valid()))
    {
        p.set_axi_ready(CP_AXI_WAIT);
        return;
    }

    // check that there is a slave
    codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;
    SlaveInterface* pSlave = nullptr;
    this->GetSlaveInterface(oAddr, nAddr, pSlave, p.get_command() == CP_CMD_LOAD);

    // no interface found, route to the default
    if (pSlave == nullptr)
    {
        m_DefaultSlave.PhsAddressWrite(p);
        m_WriteOOR = p.get_axi_valid() == CP_AXI_VALID;
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
inline void AxiBus<_BusCore>::PhsDataWrite(payload_type& p, const Phase phase)
{
    // wait is the default response if not specificaly set to ready afterwards
    p.set_axi_ready(CP_AXI_WAIT);

    if (m_WriteOOR)
    {
        // first process the default interface in case the data belongs to a OOR request
        m_DefaultSlave.PhsDataWrite(p);
        return;
    }

    // no request is running and no error from default slave -> idle transaction
    if (m_HandledSlaveRequestWrite == nullptr)
    {
        return;
    }

    // finish it
    m_HandledSlaveRequestWrite->transport(p, phase);

    // check if the write data has been accepted
    if (p.get_axi_valid() == CP_AXI_VALID && p.get_axi_ready() == CP_AXI_READY &&
        p.get_axi_last() == CP_AXI_LAST)
    {
        m_HandledSlaveResponseWrite = m_HandledSlaveRequestWrite;
        m_HandledSlaveRequestWrite = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline void AxiBus<_BusCore>::PhsResponseWrite(payload_type& p)
{
    // invalid is the default response if not specificaly set to valid afterwards
    p.set_axi_valid(CP_AXI_INVALID);
    // response must be reset, so the transaction will have error response
    //   only if default interface explicitly sets it
    p.set_axi_resp(CP_AXI_OKAY);

    // get the oldest write response
    auto* pResponse = GetWriteResponse();

    if (pResponse)
    {
        p.set_axi_id(pResponse->get_axi_id());
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
        // first check the default interface for OOR request
        if (m_WriteOOR)
        {
            m_DefaultSlave.PhsResponseWrite(p);
            m_WriteOOR = !p.is_error();
            return;
        }
        p.set_axi_valid(CP_AXI_INVALID);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
inline typename AxiBus<_BusCore>::payload_type* AxiBus<_BusCore>::GetWriteResponse()
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
void AxiBus<_BusCore>::LogOOR(const codasip_address_t addr)
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature()
                               << "': no slave selected at address: 0x" << std::hex << addr;
}

/**
 * \brief Updates the blocking payload with error repsonse, last signal and phases
 * \param p Payload to be updated
 */
template<class _BusCore>
void AxiBus<_BusCore>::UpdateBlockingErrorPayload(payload_type& p)
{
    // every payload is an error and data phase
    p.set_axi_resp(CP_AXI_DECERR);
    p.set_axi_data_phase();

    // last payload in burst has special handling
    if (m_BlockingLength == 0)
    {
        // response phase is set in write transactions
        if (m_BlockingBurstWrite)
        {
            if (p.get_axi_last() == CP_AXI_NOT_LAST)
            {
                RES_LOG(LOG_TYPE_ERROR, 0)
                    << "'" << this->get_signature()
                    << "': last signal not set in the last transaction of the burst";
                throw exceptions::BasicError("Aborted simulation, fatal error when accessing "
                                             "'" +
                    this->get_signature() + "': protocol broken");
            }
            p.set_axi_response_phase();
        }
        // last signal is set in read transactions
        else
        {
            p.set_axi_last(CP_AXI_LAST);
        }
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATORS_RESOURCES_CSR_AXI_BUS_H_
