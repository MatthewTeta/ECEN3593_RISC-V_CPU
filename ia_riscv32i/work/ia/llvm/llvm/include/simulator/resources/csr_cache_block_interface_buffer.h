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

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INTERFACE_BUFFER_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INTERFACE_BUFFER_H_

namespace codasip {
namespace resources {

//#define DEBUG_OUTPUT_ENABLE
#ifdef DEBUG_OUTPUT_ENABLE
#    define DEBUG_OUTPUT(x) std::cout << x << std::endl
#else
#    define DEBUG_OUTPUT(x)
#endif

/**
 *  \class  codasip::resources::CacheBlockInterfaceBuffer
 *  \brief  Buffer for storing and managing cache slave interface payloads.
 *  \tparam T   Buffered payload template param.
 */
template<class T>
class CacheBlockInterfaceBuffer
{
public:
    CacheBlockInterfaceBuffer();
    /**
         *  \brief  Reset buffer (reset request logic).
         */
    void Reset();
    /**
         *  \brief  Move one clock cycle further.
         */
    void ClockCycle();
    /**
         *  \brief  For active ahb transfer, schedule request insertion to buffer on clock cycle.
         *  \param  p   Request payload that could be inserted into buffer.
         *  \param  nc  Non-cacheable region flag.
         */
    void InsertRequestOnClockCycle(Payload<T>& p, const bool nc);
    /**
         *  \brief  Cancels scheduled request insertion.
         */
    void CancelRequestInsertion();
    /**
         *  \brief  Returns whether the previous request is processed and whether we are able to
         *          insert a new request into buffer.
         */
    bool IsRequestFinished() const
    {
        return m_State == FINISHED;
    }
    /**
         *  \brief  Returns whether the inserted request was accepted by the destination device
         *          (registers/cache).
         */
    bool IsRequestAccepted() const
    {
        return m_State == ACCEPTED;
    }
    /**
         *  \brief  Returns whether the incoming request was inserted into buffer and is waiting to
         *          be accepted by the destination device (cache/registers).
         */
    bool IsRequestInserted() const
    {
        return m_State == INSERTED;
    }
    /**
         *  \brief  Marks inserted request as accepted by destination device.
         */
    void MarkRequestAccepted()
    {
        DEBUG_OUTPUT("CacheBlockInterfaceBuffer | Request ACCEPTED");
        m_State = ACCEPTED;
        m_NextState = ACCEPTED;
    }
    /**
         *  \brief  Marks accepted request as processed and finished.
         */
    void MarkRequestFinished()
    {
        DEBUG_OUTPUT("CacheBlockInterfaceBuffer | Request FINISHED");
        m_State = FINISHED;
        m_NextState = FINISHED;
    }
    /**
         *  \brief  Returns buffered request.
         */
    Payload<T>& GetRequest()
    {
        return m_Payload;
    }
    /**
         *  \brief  Returns true if the buffered request is non-cacheable, false otherwise.
         */
    bool GetNc() const
    {
        return m_Nc;
    }

private:
    /// Enumeration of possible buffer states.
    enum State
    {
        FINISHED,   // request processing is finished on destination device
                    // new request can be inserted
        INSERTED,   // new request is inserted to buffer
        ACCEPTED    // request is being processed on destination device
    };
    State m_State, m_NextState;
    Payload<T> m_Payload, m_NewPayload;
    /// Buffered request non-cacheable flag.
    bool m_Nc;
    /// New request non-cacheable flag.
    bool m_NewNc;
};

template<class T>
CacheBlockInterfaceBuffer<T>::CacheBlockInterfaceBuffer()
  : m_State(FINISHED)
  , m_NextState(FINISHED)
  , m_Nc(false)
  , m_NewNc(false)
{
    m_Payload.reset(1);
    m_NewPayload.reset(1);
}

template<class T>
void CacheBlockInterfaceBuffer<T>::Reset()
{
    m_State = FINISHED;
    m_NextState = FINISHED;
    m_Payload.reset(1);
    m_NewPayload.reset(1);
}

template<class T>
void CacheBlockInterfaceBuffer<T>::InsertRequestOnClockCycle(Payload<T>& p, const bool nc)
{
    DEBUG_OUTPUT("CacheBlockInterfaceBuffer | Request scheduled for insertion.");
    if (!p.is_ahb_active_transfer())
    {
        return;
    }
    m_NextState = INSERTED;
    m_NewPayload = p;
    m_NewNc = nc;
}

template<class T>
void CacheBlockInterfaceBuffer<T>::CancelRequestInsertion()
{
    if (m_NextState == INSERTED)
    {
        DEBUG_OUTPUT("CacheBlockInterfaceBuffer | Request insertion canceled.");
        m_NextState = m_State;
    }
}

template<class T>
void CacheBlockInterfaceBuffer<T>::ClockCycle()
{
    if (m_State == FINISHED && m_NextState == INSERTED)
    {
        DEBUG_OUTPUT("CacheBlockInterfaceBuffer | Request inserted.");
        DEBUG_OUTPUT(m_NewPayload.PrintAhbLite());
        m_Payload = m_NewPayload;
        m_Nc = m_NewNc;
        m_State = m_NextState;
    }
    std::vector<std::string> stateNames = {"FINISHED", "INSERTED", "ACCEPTED"};
    DEBUG_OUTPUT("CacheBlockInterfaceBuffer | REQUEST STATE | " << stateNames[m_State]);
}

#ifdef DEBUG_OUTPUT
#    undef DEBUG_OUTPUT
#endif

}   // namespace resources
}   // namespace codasip
#endif
