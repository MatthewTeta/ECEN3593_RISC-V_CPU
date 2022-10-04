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
 *  \date   Oct 29, 2012
 *  \brief  Definition of the class codasip::resources::RequestFSM.
 */

#ifndef SIMULATOR_RESOURCES_CSR_REQUEST_FSM_H_
#define SIMULATOR_RESOURCES_CSR_REQUEST_FSM_H_

#include "simulator/resources/csr_helpers.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::RequestFSM
 *  \brief  Basic class for request read and write things. It contains only state
 *          automaton.
 *  \}
 */
class RequestFSM
{
public:
    /**
     *  \brief  Default constructor, FSM is reset to default state.
     */
    RequestFSM()
    {
        Reset();
    }
    /**
     *  \brief  Reset FSM to default state.
     */
    void Reset()
    {
        m_Request = -1;
        m_Finished = false;
    }
    /**
     *  \brief  Signalizes error, so, finish the request in the following clock
     *          cycles.
     *  \param  delay number of clock cycles when the transaction should be finished
     */
    void Error(const int delay)
    {
        if (delay == 0)
        {
            m_Request = -1;
            m_Finished = true;
        }
        else
        {
            m_Request = delay;
        }
    }
    /**
     *  \brief  Move one clock cycle further
     */
    RES_INLINE bool ClockCycle()
    {
        // the next clock cycle, the read will succeed
        register bool finished = (m_Request == 1);
        if (m_Request >= 0)
        {
            m_Request--;
        }
        m_Finished = finished;
        return finished;
    }
    /**
     *  \brief  Handle request. It returns BUSY, if the request cannot be
     *          accepted, otherwise stores given latency and returns READY.
     *  \param  latency Latency of the request
     */
    RES_INLINE void Request(const int latency)
    {
        if (IsBusy())
        {
            return;
        }
        // if the latency is 0, we are ready immediately
        m_Request = latency;
        if (!latency)
        {
            m_Finished = true;
        }
    }
    /**
     *  \brief Return true, if there is any request running.
     */
    RES_INLINE bool IsBusy() const
    {
        return m_Request > 0;
    }
    /**
     *  \brief Return true, if data phase is finishing transaction.
     */
    RES_INLINE bool IsFinished() const
    {
        return m_Finished;
    }
    /**
     * \brief Return true if no request is running or finished in the current clock cycle.
     */
    RES_INLINE bool IsIdle() const
    {
        return !IsBusy() && !m_Finished;
    }
    /**
     *  \brief  Stall request
     */
    RES_INLINE void Stall()
    {
        m_Finished = false;
        ++m_Request;
    }

private:
    /// Counter holding info about process of request
    int m_Request;
    /// guard, it is set when the request succeeds
    bool m_Finished;
};

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_REQUEST_FSM_H_
