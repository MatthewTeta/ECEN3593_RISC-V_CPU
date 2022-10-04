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
 *  \date   Nov 7, 2017
 *  \brief  Definition of the class codasip::resources::AxiRequest.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_REQUEST_H_
#define SIMULATOR_RESOURCES_CSR_AXI_REQUEST_H_

#include "simulator/resources/csr_request_fsm.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiRequest
 *  \brief  Request within the AMBA AXI4-Lite and AXI4 protocol.
 *  \}
 */
template<class T>
class AxiRequest : public RequestFSM
{
public:
    /// \brief  Concrete payload type used by this class
    typedef Payload<T> PayloadType;

    /**
     *  \brief Default constructor resets to default state.
     */
    AxiRequest()
    {
        reset();
    }
    /**
     *  \brief  Reset payload structures and FSM.
     */
    void reset()
    {
        m_AddressPhasePayload.reset(CP_AXI_READY);
        m_DataPhasePayload.reset(CP_AXI_READY);
        RequestFSM::Reset();
    }
    /**
     *  \brief  Specialized handling of the address phase. Updates AxREADY
     *          information in given payload structure.
     *  \param  latency Latency of the operation (read/write/...)
     *  \param  p transaction parameters (operation, address, size, ...),
     *          status field gets updated.
     */
    RES_INLINE void AddressPhase(const Index latency, PayloadType& p)
    {
        // write response must be collected before any other transaction is allowed
        if (!RequestFSM::IsBusy())
        {
            p.set_axi_ready(CP_AXI_READY);
            RequestFSM::Request(latency);
            // forward data directly to the data phase (only for WRITE !!!)
            if (p.get_axi_valid() == CP_AXI_VALID && (p.get_command() == CP_CMD_WRITE) &&
                (latency == 0))
            {
                m_DataPhasePayload = p;
            }
            else
            {   // store request parameters for later usage in the data phase
                m_AddressPhasePayload = p;
            }
        }
        else
        {
            p.set_axi_ready(CP_AXI_WAIT);
        }
    }
    /**
     *  \brief  Check currently running transaction in data phase. Always updates
     *          status (READY) and response (RESP) outputs. Based on the
     *          state of the operation and presence of errors during address
     *          phase other attributes may be modified as well. For active and
     *          valid request restores data from the address phase.
     *  \param  p transaction properties to be updated
     */
    RES_INLINE void DataPhase(PayloadType& p) const
    {
        if (RequestFSM::IsFinished())
        {   // restore necessary informations from address phase
            p = m_DataPhasePayload;
            p.set_axi_ready(CP_AXI_READY);
        }
        else if (RequestFSM::IsBusy())
        {   // BUSY, restore response indicating possible error
            p.set_axi_resp(m_DataPhasePayload.get_axi_resp());
            p.set_axi_ready(CP_AXI_WAIT);
        }
        else
        {   // IDLE: for safety invalidate source informations, may be misleading
            // containing invalid command, ...
            p.reset(CP_AXI_READY);
        }
    }
    /**
     *  \brief  Move one clock cycle further
     */
    RES_INLINE bool clock_cycle()
    {
        if (m_AddressPhasePayload.get_command() != CP_CMD_NONE)
        {
            m_DataPhasePayload = m_AddressPhasePayload;
            m_AddressPhasePayload.reset(CP_AXI_READY);
        }
        if (m_DataPhasePayload.get_command() != CP_CMD_NONE && !IsBusy())
        {
            m_DataPhasePayload.reset(CP_AXI_READY);
        }
        // return whether this is a lucky clock cycle
        return RequestFSM::ClockCycle();
    }

    /// source transaction information used for address phase
    PayloadType m_AddressPhasePayload;
    /// source transaction information used for data phase
    PayloadType m_DataPhasePayload;
};

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AXI_REQUEST_H_
