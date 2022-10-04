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
 *  \author Albert Miko
 *  \date   Aug 8, 2017
 *  \brief  Definition of the class codasip::resources::AhbLiteRequest.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AHB_REQUEST_H_
#define SIMULATOR_RESOURCES_CSR_AHB_REQUEST_H_

#include "simulator/resources/csr_request_fsm.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AhbLiteRequest
 *  \brief  Request within the AMBA 3 AHB-Lite protocol.
 *  \}
 */
template<class T>
class AhbLiteRequest : public RequestFSM
{
public:
    /// \brief  Concrete payload type used by this class
    typedef Payload<T> PayloadType;

    /**
     *  \brief Default constructor resets to default state.
     */
    AhbLiteRequest()
    {
        reset();
    }
    /**
     *  \brief  Reset payload structures and FSM.
     */
    void reset()
    {
        m_AddressPhasePayload.reset(CP_AHB_READY);
        m_DataPhasePayload.reset(CP_AHB_READY);
        RequestFSM::Reset();
    }
    /**
     *  \brief  Specialized handling of the address phase. Updates status
     *          information in given payload structure.
     *  \param  latency Latency of the operation (read/write/...)
     *  \param  p transaction parameters (operation, address, size, ...),
     *          status field gets updated.
     */
    RES_INLINE void AddressPhase(const Index latency, PayloadType& p)
    {
        if (!RequestFSM::IsBusy())
        {   // store request parameters for later usage in the data phase
            RequestFSM::Request(latency);
            m_AddressPhasePayload = p;
        }
    }
    /**
     *  \brief  Check currently running transaction in data phase. Always updates
     *          status (HREADY) and response (HRESP) outputs. Based on the
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
            p.set_ahb_hready(CP_AHB_READY);
        }
        else if (RequestFSM::IsBusy())
        {   // BUSY, restore response indicating possible error
            // two-cycle error response
            p.set_ahb_hready(CP_AHB_WAIT);
            p.set_ahb_hresp(m_DataPhasePayload.get_ahb_hresp());
        }
        else
        {   // IDLE: for safety invalidate source informations, may be misleading
            // containing invalid command, ...
            p.reset(CP_AHB_READY);
            p.set_ahb_hresp(CP_AHB_OKAY);
        }
    }
    /**
     *  \brief  Move one clock cycle further
     *  \param  p transaction properties will be updated if there is a currently
     *          running operation and the transfer is ready to finish
     */
    RES_INLINE bool clock_cycle(PayloadType& p)
    {
        if (m_AddressPhasePayload.is_ahb_active_transfer())
        {
            m_DataPhasePayload = m_AddressPhasePayload;
            m_AddressPhasePayload.reset(CP_AHB_READY);
        }
        if (m_DataPhasePayload.is_ahb_active_transfer() && !IsBusy())
        {
            p = m_DataPhasePayload;
            m_DataPhasePayload.reset(CP_AHB_READY);
        }
        // return whether this is a lucky clock cycle
        return RequestFSM::ClockCycle();
    }

    /// source transaction informations used for address phase
    PayloadType m_AddressPhasePayload;
    /// source transaction informations used for data phase
    PayloadType m_DataPhasePayload;
};

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AHB_REQUEST_H_
