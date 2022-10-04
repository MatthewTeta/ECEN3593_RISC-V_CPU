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
 *  \date   Dec 18, 2020
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INTERFACE_BASE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INTERFACE_BASE_H_

#include "simulator/resources/csr_ahb_initiator_interface.h"
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
 *  \class  codasip::resources::CacheBlockInterfaceBase
 *  \brief  Common base for I and D cache block interfaces.
 *  \tparam CParams Cache slave interface configuration.
 *  \tparam RParams Cache control and status registers configuration.
 */
template<class CParams, class RParams>
class CacheBlockInterfaceBase
  : public AhbLiteInitiatorInterface<typename CParams::slave_interface_t::mixin_base>
{
public:
    /// Payload type.
    typedef Payload<typename CParams::data_type> PayloadType;

    CacheBlockInterfaceBase(typename CParams::slave_interface_t& slave_interface,
        CacheRegisters<RParams>& registers);

    /**
     *  \copydoc codasip::resources::Interface::blocking_cb
     */
    void blocking_cb(PayloadType& p) override;
    /**
     *  \copydoc codasip::resources::Interface::transport_cb
     */
    void transport_cb(PayloadType& p, const Phase phase) override;

    /**
     *  \brief  Returns whether the cache is busy or not.
     */
    bool IsCacheBusy() const
    {
        return m_CacheSlaveInterface.IsBusy();
    };
    /**
     *  \brief  Stores the given cache line to cache (useful for unit tests).
     *  \param  cacheLine   A cache line that is to be saved.
     *  \param  set A set in which the cache line should be stored.
     *  \param  index   An index under which the cache line should be stored.
     *  \param  tag A cache line tag.
     *  \param  dirts   A flag for setting the saved cache line dirty.
     */
    void SaveCacheLine(const typename CParams::slave_interface_t::CLine& cacheLine,
        const Index set,
        const typename CParams::slave_interface_t::LineIndex index,
        const typename CParams::slave_interface_t::Tag tag,
        const bool dirty)
    {
        m_CacheSlaveInterface.SaveCacheLineIntoCache(cacheLine, set, index, tag);
        if (dirty)
        {
            m_CacheSlaveInterface.SetDirty(set, index);
        }
    }
    /**
     *  \brief  Reset cache slave interface (reset request logic).
     */
    void Reset();

protected:
    typedef AhbLiteInitiatorInterface<typename CParams::slave_interface_t::mixin_base> InterfaceBaseType;

    /// Enumeration of possible states.
    enum State
    {
        OKAY_READY,
        OKAY_WAIT,
        ERROR_WAIT,
        ERROR_READY
    };

    /**
     *  \brief  Processes address phase.
     *  \param  p   Request payload.
     */
    virtual void DoRequest(PayloadType& p);
    /**
     *  \brief  Processes data phase.
     *  \param  p   Request payload.
     */
    virtual void DoResponse(PayloadType& p);
    /**
     *  \brief  Sets m_NextState according to AHB response and ready state.
     *  \param  response    AHB response code used to set the m_NextState.
     *  \param  ready       AHB ready code used to set the m_NextState.
     */
    void UpdateNextState(const AHBResponseCode, const AHBReadyCode);
    /**
     *  \brief  Sets AHB payload ready and response according to the m_NextState.
     *  \param  p   Payload that is to be updated.
     */
    void UpdatePayload(PayloadType& p) const;

    State m_State, m_NextState;
    typename CParams::slave_interface_t& m_CacheSlaveInterface;
    CacheRegisters<RParams>& m_Registers;
    CacheBlockInterfaceBuffer<typename CParams::data_type> m_Buffer;
};

template<class CParams, class RParams>
CacheBlockInterfaceBase<CParams, RParams>::CacheBlockInterfaceBase(
    typename CParams::slave_interface_t& slave_interface,
    CacheRegisters<RParams>& registers)
  : InterfaceBaseType(slave_interface.get_signature(), slave_interface.GetUid())
  , m_State(OKAY_READY)
  , m_NextState(OKAY_READY)
  , m_CacheSlaveInterface(slave_interface)
  , m_Registers(registers)
  , m_Buffer()
{
    m_CacheSlaveInterface.SetCacheRegistersInterface(&m_Registers);
}

template<class CParams, class RParams>
void CacheBlockInterfaceBase<CParams, RParams>::Reset()
{
    m_Buffer.Reset();
    m_State = OKAY_WAIT;
    m_NextState = OKAY_READY;
}

template<class CParams, class RParams>
void CacheBlockInterfaceBase<CParams, RParams>::blocking_cb(PayloadType& p)
{
    DEBUG_OUTPUT("CacheBlockInterfaceBase | BLOCKING | payload data = " << p.PrintAhbLite());
    if (p.get_bc() == 0)
    {
        return;
    }
    p.set_data(InterfaceBaseType::MaskAndShiftData(p.get_data(), p.get_address(), p.get_bc()));
    m_CacheSlaveInterface.blocking(p);
    const auto shift = this->get_amba_shift(
        this->get_offset(p.get_address(), InterfaceBaseType::SUBBLOCKS),
        p.get_bc());
    p.set_data(p.get_data() << shift);
    DEBUG_OUTPUT("CacheBlockInterfaceBase | BLOCKING | payload data = " << p.PrintAhbLite());
}

template<class CParams, class RParams>
void CacheBlockInterfaceBase<CParams, RParams>::transport_cb(PayloadType& p, const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            DoRequest(p);
            break;
        case CP_PHS_DATA:
            DoResponse(p);
            break;
        default:
            break;
    }
}

template<class CParams, class RParams>
void CacheBlockInterfaceBase<CParams, RParams>::DoRequest(PayloadType& p)
{
    DEBUG_OUTPUT("CacheBlockInterfaceBase | DoRequest START");
    DEBUG_OUTPUT(p.PrintAhbLite());
    m_Buffer.InsertRequestOnClockCycle(p, !p.is_ahb_hprot_cacheable());
    DEBUG_OUTPUT("CacheBlockInterfaceBase | DoRequest END");
}

template<class CParams, class RParams>
void CacheBlockInterfaceBase<CParams, RParams>::DoResponse(PayloadType& p)
{
    DEBUG_OUTPUT("CacheBlockInterfaceBase | DATA PHASE");
    switch (m_State)
    {
        case OKAY_READY:
        case OKAY_WAIT:
        case ERROR_READY:
            if (m_Buffer.IsRequestAccepted())
            {
                if (!m_Buffer.GetRequest().is_error())
                {
                    m_Buffer.GetRequest().set_data(p.get_data());
                    m_CacheSlaveInterface.transport(m_Buffer.GetRequest(), CP_PHS_DATA);
                    this->UpdateNextState(m_Buffer.GetRequest().get_ahb_hresp(),
                        m_Buffer.GetRequest().get_ahb_hready());
                }
                else
                {
                    m_NextState = ERROR_WAIT;
                }
                // If the m_NextState is OKAY_READY i.e. the request was finished on device
                // mark it as FINISHED else leave it as ACCEPTED.
                if (m_NextState == OKAY_READY || m_NextState == ERROR_WAIT)
                {
                    m_Buffer.MarkRequestFinished();
                }
                else
                {
                    m_Buffer.MarkRequestAccepted();
                }
                p = m_Buffer.GetRequest();
            }
            else
            {
                if (m_State == ERROR_READY && m_NextState == ERROR_READY)
                {
                    m_NextState = OKAY_READY;
                }
            }
            break;
        case ERROR_WAIT:
            // these state changed has to be done in clock cycle
            m_NextState = ERROR_READY;
            break;
    }
    // Update payload ready and response of payload according to m_NextState
    this->UpdatePayload(p);
    // when we are not returning valid data we set payload data to 0
    if (m_NextState != OKAY_READY)
    {
        p.set_data(0);
    }
}

template<class CParams, class RParams>
void CacheBlockInterfaceBase<CParams, RParams>::UpdateNextState(const AHBResponseCode response,
    const AHBReadyCode ready)
{
    if (response == CP_AHB_OKAY)
    {
        if (ready == CP_AHB_READY)
        {
            DEBUG_OUTPUT("CacheBlockInterfaceBase | UpdateNextState | OKAY READY");
            m_NextState = OKAY_READY;
        }
        else
        {
            DEBUG_OUTPUT("CacheBlockInterfaceBase | UpdateNextState |  OKAY WAIT");
            m_NextState = OKAY_WAIT;
        }
    }
    else
    {
        DEBUG_OUTPUT("CacheBlockInterfaceBase | UpdateNextState | ERROR WAIT");
        m_NextState = ERROR_WAIT;
    }
}

template<class CParams, class RParams>
void CacheBlockInterfaceBase<CParams, RParams>::UpdatePayload(PayloadType& p) const
{
    switch (m_NextState)
    {
        case OKAY_READY:
            DEBUG_OUTPUT("CacheBlockInterfaceBase | UpdatePayload | OKAY READY");
            p.set_ahb_hresp(CP_AHB_OKAY);
            p.set_ahb_hready(CP_AHB_READY);
            break;
        case OKAY_WAIT:
            DEBUG_OUTPUT("CacheBlockInterfaceBase | UpdatePayload | OKAY WAIT");
            p.set_ahb_hresp(CP_AHB_OKAY);
            p.set_ahb_hready(CP_AHB_WAIT);
            break;
        case ERROR_READY:
            DEBUG_OUTPUT("CacheBlockInterfaceBase | UpdatePayload | ERROR READY");
            p.set_ahb_hresp(CP_AHB_ERROR);
            p.set_ahb_hready(CP_AHB_READY);
            break;
        case ERROR_WAIT:
            DEBUG_OUTPUT("CacheBlockInterfaceBase | UpdatePayload | ERROR WAIT");
            p.set_ahb_hresp(CP_AHB_ERROR);
            p.set_ahb_hready(CP_AHB_WAIT);
            break;
    }
}

#ifdef DEBUG_OUTPUT
#    undef DEBUG_OUTPUT
#endif

}   // namespace resources
}   // namespace codasip
#endif   // SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_INTERFACE_BASE_H_
