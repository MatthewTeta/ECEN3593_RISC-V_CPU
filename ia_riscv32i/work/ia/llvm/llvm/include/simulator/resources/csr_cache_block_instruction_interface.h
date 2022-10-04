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
 *  \author Pavel Najman
 *  \date   Oct 25, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INSTRUCTION_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INSTRUCTION_INTERFACE_H_

#include "simulator/resources/csr_ahb_initiator_interface.h"
#include "simulator/resources/csr_cache_block_interface_base.h"
#include "simulator/resources/csr_cache_block_interface_buffer.h"
#include "simulator/resources/csr_cache_interface.h"
#include "simulator/resources/csr_cache_registers.h"
#include "simulator/resources/csr_helpers.h"

namespace codasip {
namespace resources {

//#define DEBUG_OUTPUT_ENABLE
//#define DEBUG_FILE_ENABLE
#if defined(DEBUG_OUTPUT_ENABLE)
#    define DEBUG_OUTPUT(x) std::cout << x << std::endl
#elif defined(DEBUG_FILE_ENABLE)
#    define DEBUG_OUTPUT(x) detail::DebugLogger::Get() << x << std::endl
#else
#    define DEBUG_OUTPUT(x)
#endif

/**
 *  \class  codasip::resources::ICacheBlockInterface
 *  \brief  Instruction cache slave interface.
 *  \tparam RParams Cache control and status registers configuration.
 */
template<class RParams>
class ICacheBlockInterface : public CacheBlockInterfaceBase<typename RParams::ICacheParams, RParams>
{
public:
    typedef typename RParams::ICacheParams Params;
    typedef CacheBlockInterfaceBase<Params, RParams> BaseType;
    using CacheBlockInterfaceBase<Params, RParams>::CacheBlockInterfaceBase;

    /**
     *  \brief  Move one clock cycle further.
     */
    void ClockCycle();

private:
    using BaseType::ERROR_READY;
    using BaseType::ERROR_WAIT;
    using BaseType::m_Buffer;
    using BaseType::m_NextState;
    using BaseType::m_State;
    using BaseType::OKAY_READY;
    using BaseType::OKAY_WAIT;
};

template<class RParams>
void ICacheBlockInterface<RParams>::ClockCycle()
{
    DEBUG_OUTPUT("ICacheBlockInterface | CLOCK CYCLE.");
#ifdef DEBUG_OUTPUT_ENABLE
    static const std::vector<std::string> stateNames = {"OKAY_READY",
        "OKAY_WAIT",
        "ERROR_WAIT",
        "ERROR_READY"};
#endif
    DEBUG_OUTPUT("ICacheBlockInterface | Change state from " << stateNames[m_State] << " to "
                                                             << stateNames[m_NextState]);
    m_State = m_NextState;
    m_NextState = OKAY_READY;
    // During ADDRESS phase the incoming request was scheduled for insertion. We insert the request
    // if we are ready else we cancel the insertion.
    if (m_State != OKAY_READY && m_State != ERROR_READY)
    {
        m_Buffer.CancelRequestInsertion();
    }

    m_Buffer.ClockCycle();
    this->check_payload(m_Buffer.GetRequest(), false, true, false);
    if (m_Buffer.IsRequestInserted())
    {
        if (m_Buffer.GetRequest().is_error() && (m_State == OKAY_READY || m_State == ERROR_READY))
        {
            DEBUG_OUTPUT("ICacheBlockInterface | ADDRESS PHASE | Request error.");
            m_NextState = ERROR_WAIT;
            m_Buffer.MarkRequestAccepted();
            this->m_CacheSlaveInterface.InvalidateLastIndexUsed();
        }
        else
        {
            DEBUG_OUTPUT("ICacheBlockInterface | ADDRESS PHASE | Request sent to cache.");
            this->m_CacheSlaveInterface.SetNc(m_Buffer.GetNc());
            this->m_CacheSlaveInterface.transport(m_Buffer.GetRequest(), CP_PHS_ADDRESS);
            if (m_Buffer.GetRequest().get_ahb_hready() == CP_AHB_READY)
            {
                DEBUG_OUTPUT("ICacheBlockInterface | ADDRESS PHASE | Request was accepted.");
                m_Buffer.MarkRequestAccepted();
            }
            else
            {
                DEBUG_OUTPUT("ICacheBlockInterface | ADDRESS PHASE | Request was not accepted.");
                m_NextState = OKAY_WAIT;
                if (!RParams::D_IS_ENABLED && (m_State == OKAY_READY))
                {
                    this->m_CacheSlaveInterface.CacheOperationNext();
                }
            }
        }
    }
    // Following piece of code prevents cache invalidate operations to take precedence before error
    // state handling.
    // START
    switch (m_State)
    {
        case OKAY_READY:
        case OKAY_WAIT:
            this->m_CacheSlaveInterface.SetErrorState(false);
            break;
        case ERROR_READY:
        case ERROR_WAIT:
            this->m_CacheSlaveInterface.SetErrorState(true);
            break;
    }
    // END
    DEBUG_OUTPUT("ICacheBlockInterface | ADDRESS PHASE | NextState " << stateNames[m_NextState] << ".");
}

#ifdef DEBUG_OUTPUT
#    undef DEBUG_OUTPUT
#endif

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INSTRUCTION_INTERFACE_H_
