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

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_DATA_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_DATA_INTERFACE_H_

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

template<class RParams, typename Enable = void>
class DCacheBlockInterface;

/**
 *  \class  codasip::resources::DCacheBlockInterface
 *  \brief  Data cache slave interface.
 *  \tparam RParams Cache control and status registers configuration.
 */
template<class RParams>
class DCacheBlockInterface<RParams, typename std::enable_if<!RParams::DCacheParams::IS_ENABLED>::type>
  : public CacheBlockInterfaceBase<typename RParams::DCacheParams, RParams>
{
public:
    typedef typename RParams::DCacheParams DParams;
    typedef CacheBlockInterfaceBase<DParams, RParams> BaseType;
    using typename BaseType::PayloadType;

    DCacheBlockInterface(CacheRegisters<RParams>& registers,
        typename DParams::slave_interface_t& slave_interface,
        typename DParams::master_interface_t& master_interface)
      : BaseType(slave_interface, registers)
      , m_CacheMasterInterface(master_interface)
    {}

    /**
     *  \brief  Move one clock cycle further.
     */
    void ClockCycle()
    {
        DEBUG_OUTPUT("DCacheBlockInterface | CLOCK CYCLE.");
        static const std::vector<std::string> stateNames = {"OKAY_READY",
            "OKAY_WAIT",
            "ERROR_WAIT",
            "ERROR_READY"};
        DEBUG_OUTPUT("DCacheBlockInterface | Change state from " << stateNames[m_State] << " to "
                                                                 << stateNames[m_NextState]);
        m_State = m_NextState;
        m_NextState = OKAY_READY;
        // During the ADDRESS phase, the incoming request was scheduled for insertion. We insert the request
        // if we are ready else we cancel the insertion.
        if (m_State != OKAY_READY && m_State != ERROR_READY)
        {
            m_Buffer.CancelRequestInsertion();
        }
        m_Buffer.ClockCycle();
        if (m_Registers.IsRegisterRegionAddress(m_Buffer.GetRequest().get_address()) &&
            m_Buffer.IsRequestInserted())
        {
            if (m_Registers.IsCacheOperationAddress(m_Buffer.GetRequest().get_address()))
            {   // process cache operation request
                this->check_payload(m_Buffer.GetRequest(), false, true, true);
                if ((m_Buffer.GetRequest().is_error() ||
                        !m_Registers.interface.IsMaxBc(m_Buffer.GetRequest().get_bc())) &&
                    (m_State == OKAY_READY || m_State == ERROR_READY))
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request error.");
                    m_NextState = ERROR_WAIT;
                    m_Buffer.MarkRequestFinished();
                }
                else if (m_Registers.IsICacheOperationAddress(m_Buffer.GetRequest().get_address()) &&
                    m_Buffer.GetRequest().get_command() == CP_CMD_WRITE)
                {   // when D cache is disabled only I cache operations are processed
                    if (m_Registers.GetICacheSlaveInterface().DoCacheOperationAddressCA(
                            m_Buffer.GetRequest().get_address(),
                            m_Buffer.GetRequest().get_ahb_hprot(),
                            m_Buffer.GetRequest().get_ahb_hmastlock()))
                    {   //  cache is not busy and is able to accept the request
                        m_Buffer.MarkRequestAccepted();
                    }
                    else
                    {
                        m_NextState = OKAY_WAIT;
                    }
                }
                else
                {   // read cache operations or D cache operations with disabled D cache are ignored
                    m_Buffer.MarkRequestFinished();
                }
            }
            else
            {   //  process register request
                DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request sent to registers.");
                m_Registers.interface.transport(m_Buffer.GetRequest(), CP_PHS_ADDRESS);
                if (m_Buffer.GetRequest().get_ahb_hready() == CP_AHB_READY)
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request was accepted.");
                    m_Buffer.MarkRequestAccepted();
                }
                else
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request was not "
                                 "accepted.");
                    m_NextState = OKAY_WAIT;
                }
            }
        }
        // Handles also I and D cache clock cycles
        m_Registers.ClockCycle();
        DEBUG_OUTPUT(
            "DCacheBlockInterface | ADDRESS PHASE | NextState " << stateNames[m_NextState] << ".");
    }
    /**
     *  \brief  Resets cache and registers.
     */
    void Reset()
    {
        BaseType::Reset();
        m_Registers.Reset();
    }
    /**
     *  \brief       Debug read for debugger or profiler from cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::dread
     */
    typename DParams::data_type
    dread(const codasip_address_t addr, const Index sbc = DParams::BYTES_PER_WORD)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            return m_CacheMasterInterface.dread(addr, sbc);
        }
        return m_Registers.interface.dread(addr, sbc);
    }
    template<class Resp>
    typename DParams::data_type dread(const codasip_address_t addr, const Index sbc, Resp& resp)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            return m_CacheMasterInterface.dread(addr, sbc, resp);
        }
        return m_Registers.interface.dread(addr, sbc, resp);
    }
    /**
     *  \{
     *  \brief   Read data from cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::read
     */
    typename DParams::data_type
    read(const codasip_address_t addr, const Index sbc = DParams::BYTES_PER_WORD)
    {
        AHBResponseCode resp = CP_AHB_OKAY;
        auto rdata = read(addr, sbc, resp);
        if (resp != CP_AHB_OKAY)
        {
            this->DoAbortSimulation();
        }
        return rdata;
    }
    template<class Resp>
    typename DParams::data_type read(const codasip_address_t addr,
        const Index sbc,
        Resp& resp,
        const uint8_t hprot = CP_AHB_DATA_ACCESS | CP_AHB_PRIVILEGED,
        const uint8_t hmastlock = CP_AHB_UNLOCK)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            return m_CacheMasterInterface.read(addr, sbc, resp, hprot, hmastlock);
        }
        return m_Registers.interface.read(addr, sbc, resp);
    }
    /**
     *  \}
     *  \brief       Debug write for debugger or profiler.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::dwrite
     */
    void dwrite(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc = DParams::BYTES_PER_WORD)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            m_CacheMasterInterface.dwrite(data, addr, sbc);
        }
        else if (m_Registers.IsICacheOperationAddress(addr))
        {
            m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(data, addr);
        }
        else
        {
            m_Registers.interface.dwrite(data, addr, sbc);
        }
    }
    /**
     *  \}
     *  \brief   Write data to cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::read
     */
    void write(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc = DParams::BYTES_PER_WORD)
    {
        AHBResponseCode resp = CP_AHB_OKAY;
        write(data, addr, sbc, resp);
        if (resp != CP_AHB_OKAY)
        {
            this->DoAbortSimulation();
        }
    }
    template<class Resp>
    void write(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc,
        Resp& resp,
        const uint8_t hprot = CP_AHB_DATA_ACCESS | CP_AHB_PRIVILEGED,
        const uint8_t hmastlock = CP_AHB_UNLOCK)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            m_CacheMasterInterface.write(data, addr, sbc, resp, hprot, hmastlock);
        }
        else if (m_Registers.IsICacheOperationAddress(addr))
        {
            detail::ResourceAccess::Write(resp, CP_AHB_OKAY);
            if (!m_Registers.interface.IsMaxBc(sbc))
            {
                detail::ResourceAccess::Write(resp, CP_AHB_ERROR);
            }
            else
            {
                m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(data, addr);
            }
        }
        else
        {
            m_Registers.interface.write(data, addr, sbc, resp);
        }
    }
    /**
     *  \}
     *  \brief       Debug load to cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::load
     */
    void load(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc = DParams::BYTES_PER_WORD)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            m_CacheMasterInterface.load(data, addr, sbc);
        }
        else if (m_Registers.IsICacheOperationAddress(addr))
        {
            m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(data, addr);
        }
        else
        {
            m_Registers.interface.load(data, addr, sbc);
        }
    }
    /**
     *  \{
     *  \brief  Required interface for simulator state dumper (cached data have
     *          to be flushed before dumping simulator state and then dump).
     */
    void invalidate_all()
    {
        this->dwrite(1, m_Registers.GetCacheOperationStartAddress() + (2 * RParams::BYTES_PER_WORD));
        this->dwrite(1, m_Registers.GetCacheOperationStartAddress() + (5 * RParams::BYTES_PER_WORD));
    }
    void flush_all()
    {
        this->dwrite(1, m_Registers.GetCacheOperationStartAddress() + (8 * RParams::BYTES_PER_WORD));
    }
    /** \} */

    /**
     * \brief codasip::resources::CacheRegistersStorage::GetBaseAddress
     */
    codasip_address_t GetBaseAddress() const
    {
        return m_Registers.GetBaseAddress();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetISize
     */
    typename DParams::data_type GetISize() const
    {
        return m_Registers.GetISize();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetDSize
     */
    typename DParams::data_type GetDSize() const
    {
        return m_Registers.GetDSize();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetIWays
     */
    typename DParams::data_type GetIWays() const
    {
        return m_Registers.GetIWays();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetDWays
     */
    typename DParams::data_type GetDWays() const
    {
        return m_Registers.GetDWays();
    }
    /**
     * \copydoc    codasip::resources::Interface::blocking_cb
     */
    void blocking_cb(PayloadType& p) override
    {
        if (!m_Registers.IsRegisterRegionAddress(p.get_address()))
        {
            m_CacheMasterInterface.blocking(p);
        }
        else if (m_Registers.IsICacheOperationAddress(p.get_address()))
        {
            this->check_payload(p, false, true, true);
            if (!m_Registers.interface.IsMaxBc(p.get_bc()))
            {
                p.set_ahb_hresp(CP_AHB_ERROR);
            }
            else
            {
                m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(p.get_data(), p.get_address());
            }
        }
        else
        {
            m_Registers.interface.blocking(p);
        }
    }

protected:
    /**
     * \copydoc codasip::resources::CacheBlockInterfaceBase::DoResponse
     */
    void DoResponse(PayloadType& p) override
    {
        DEBUG_OUTPUT("DCacheBlockInterface | DATA PHASE START");
        DEBUG_OUTPUT(p.PrintAhbLite());
        if (!m_Registers.IsRegisterRegionAddress(m_Buffer.GetRequest().get_address()))
        {
            DEBUG_OUTPUT("Memory address.");
            switch (m_State)
            {
                case OKAY_READY:
                case OKAY_WAIT:
                case ERROR_READY:
                    DEBUG_OUTPUT("Request sent to memory.");
                    m_CacheMasterInterface.transport(p, CP_PHS_DATA);
                    this->UpdateNextState(p.get_ahb_hresp(), p.get_ahb_hready());
                    if (m_NextState == OKAY_READY || m_NextState == ERROR_WAIT)
                    {
                        m_Buffer.MarkRequestFinished();
                    }
                    break;
                case ERROR_WAIT:
                    p.set_data(0);
                    m_NextState = ERROR_READY;
                    break;
            }
            this->UpdatePayload(p);
        }
        else if (m_Registers.IsCacheOperationAddress(m_Buffer.GetRequest().get_address()))
        {
            DEBUG_OUTPUT("Cache operation address.");
            switch (m_State)
            {
                case OKAY_READY:
                case OKAY_WAIT:
                case ERROR_READY:
                    if (m_Buffer.IsRequestAccepted())
                    {
                        if (m_Registers.GetICacheSlaveInterface().DoCacheOperationDataCA(p.get_data(),
                                m_Buffer.GetRequest().get_ahb_hprot(),
                                m_Buffer.GetRequest().get_ahb_hmastlock()))
                        {
                            m_Buffer.MarkRequestFinished();
                        }
                        else
                        {
                            m_NextState = OKAY_WAIT;
                        }
                    }
                    break;
                case ERROR_WAIT:
                    p.set_data(0);
                    m_NextState = ERROR_READY;
                    break;
            }
            this->UpdatePayload(p);
        }
        else
        {
            DEBUG_OUTPUT("Register region address.");
            switch (m_State)
            {
                case OKAY_READY:
                case OKAY_WAIT:
                case ERROR_READY:
                    if (m_Buffer.IsRequestAccepted())
                    {
                        DEBUG_OUTPUT("Request sent to registers.");

                        m_Buffer.GetRequest().set_data(p.get_data());
                        m_Registers.interface.transport(m_Buffer.GetRequest(), CP_PHS_DATA);
                        this->UpdateNextState(m_Buffer.GetRequest().get_ahb_hresp(),
                            m_Buffer.GetRequest().get_ahb_hready());
                        if (m_NextState == OKAY_READY || m_NextState == ERROR_WAIT)
                        {
                            m_Buffer.MarkRequestFinished();
                        }
                        p = m_Buffer.GetRequest();
                    }
                    else
                    {
                        p.set_data(0);
                    }
                    break;
                case ERROR_WAIT:
                    m_NextState = ERROR_READY;
                    break;
            }
            this->UpdatePayload(p);
        }
        DEBUG_OUTPUT("DCacheBlockInterface | DATA PHASE END");
    }

    /**
     * \copydoc codasip::resources::CacheBlockInterfaceBase::DoRequest
     */
    void DoRequest(PayloadType& p) override
    {
        DEBUG_OUTPUT("DCacheBlockInterface | DoRequest START");
        DEBUG_OUTPUT(p.PrintAhbLite());
        BaseType::DoRequest(p);
        if (!m_Registers.IsRegisterRegionAddress(p.get_address()))
        {
            if (!(m_Registers.IsRegisterRegionAddress(m_Buffer.GetRequest().get_address()) &&
                m_NextState == OKAY_WAIT))
            {
                if (p.is_ahb_active_transfer())
                {
                    m_CacheMasterInterface.transport(p, CP_PHS_ADDRESS);
                }
            }
        }
        DEBUG_OUTPUT("DCacheBlockInterface | DoRequest END");
    }

private:
    using BaseType::ERROR_READY;
    using BaseType::ERROR_WAIT;
    using BaseType::m_Buffer;
    using BaseType::m_NextState;
    using BaseType::m_Registers;
    using BaseType::m_State;
    using BaseType::OKAY_READY;
    using BaseType::OKAY_WAIT;
    typename DParams::master_interface_t& m_CacheMasterInterface;
};

/**
 *  \class  codasip::resources::DCacheBlockInterface
 *  \brief  Data cache slave interface.
 *  \tparam RParams Cache control and status registers configuration.
 */
template<class RParams>
class DCacheBlockInterface<RParams, typename std::enable_if<RParams::DCacheParams::IS_ENABLED>::type>
  : public CacheBlockInterfaceBase<typename RParams::DCacheParams, RParams>
{
public:
    typedef typename RParams::DCacheParams DParams;
    typedef CacheBlockInterfaceBase<DParams, RParams> BaseType;
    using typename BaseType::PayloadType;

    DCacheBlockInterface(CacheRegisters<RParams>& registers,
        typename DParams::slave_interface_t& slave_interface,
        typename DParams::master_interface_t& master_interface)
      : BaseType(slave_interface, registers)
      , m_CacheMasterInterface(master_interface)
    {}

    /**
     *  \brief  Move one clock cycle further.
     */
    void ClockCycle()
    {
        DEBUG_OUTPUT("DCacheBlockInterface | CLOCK CYCLE.");
        static const std::vector<std::string> stateNames = {"OKAY_READY",
            "OKAY_WAIT",
            "ERROR_WAIT",
            "ERROR_READY"};
        DEBUG_OUTPUT("DCacheBlockInterface | Change state from " << stateNames[m_State] << " to "
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
        if (m_Registers.IsRegisterRegionAddress(m_Buffer.GetRequest().get_address()) &&
            m_Buffer.IsRequestInserted())
        {
            if (m_Registers.IsCacheOperationAddress(m_Buffer.GetRequest().get_address()))
            {   // process cache operation request
                this->check_payload(m_Buffer.GetRequest(), false, true, true);
                if ((m_Buffer.GetRequest().is_error() ||
                        !m_Registers.interface.IsMaxBc(m_Buffer.GetRequest().get_bc())) &&
                    (m_State == OKAY_READY || m_State == ERROR_READY))
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request error.");
                    m_NextState = ERROR_WAIT;
                    m_Buffer.MarkRequestFinished();
                }
                else if (m_Buffer.GetRequest().get_command() == CP_CMD_WRITE)
                {   // process only write requests
                    if (m_Registers.IsICacheOperationAddress(m_Buffer.GetRequest().get_address()))
                    {   // process I cache operation
                        if (m_Registers.GetICacheSlaveInterface().DoCacheOperationAddressCA(
                                m_Buffer.GetRequest().get_address(),
                                m_Buffer.GetRequest().get_ahb_hprot(),
                                m_Buffer.GetRequest().get_ahb_hmastlock()))
                        {   //  cache is not busy and is able to accept the request
                            m_Buffer.MarkRequestAccepted();
                        }
                        else
                        {
                            m_NextState = OKAY_WAIT;
                        }
                    }
                    else
                    {   // process D cache operation
                        if (m_Registers.GetDCacheSlaveInterface().DoCacheOperationAddressCA(
                                m_Buffer.GetRequest().get_address(),
                                m_Buffer.GetRequest().get_ahb_hprot(),
                                m_Buffer.GetRequest().get_ahb_hmastlock()))
                        {   //  cache is not busy and is able to accept the request
                            m_Buffer.MarkRequestAccepted();
                        }
                        else
                        {
                            m_NextState = OKAY_WAIT;
                        }
                    }
                }
                else
                {
                    m_Buffer.MarkRequestFinished();
                }
            }
            else
            {
                DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request sent to registers.");
                m_Registers.interface.transport(m_Buffer.GetRequest(), CP_PHS_ADDRESS);
                if (m_Buffer.GetRequest().get_ahb_hready() == CP_AHB_READY)
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request was accepted.");
                    m_Buffer.MarkRequestAccepted();
                }
                else
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request was not "
                                 "accepted.");
                    m_NextState = OKAY_WAIT;
                }
            }
        }
        else
        {
            if (m_Buffer.IsRequestInserted())
            {
                this->check_payload(m_Buffer.GetRequest(), false, true, true);
                if (m_Buffer.GetRequest().is_error() &&
                    (m_State == OKAY_READY || m_State == ERROR_READY))
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request error.");
                    m_NextState = ERROR_WAIT;
                    m_Buffer.MarkRequestAccepted();
                }
                else
                {
                    DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request sent to cache.");
                    this->m_CacheSlaveInterface.transport(m_Buffer.GetRequest(), CP_PHS_ADDRESS);
                    if (m_Buffer.GetRequest().get_ahb_hready() == CP_AHB_READY)
                    {
                        DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request was "
                                     "accepted.");
                        m_Buffer.MarkRequestAccepted();
                    }
                    else
                    {
                        DEBUG_OUTPUT("DCacheBlockInterface | ADDRESS PHASE | Request was not "
                                     "accepted.");
                        m_NextState = OKAY_WAIT;
                    }
                }
            }
        }
        // Handles also I and D cache clock cycles
        m_Registers.ClockCycle();
        DEBUG_OUTPUT(
            "DCacheBlockInterface | ADDRESS PHASE | NextState " << stateNames[m_NextState] << ".");
    }
    /**
     *  \brief  Resets cache and registers.
     */
    void Reset()
    {
        BaseType::Reset();
        m_Registers.Reset();
    }
    /**
     *  \brief       Debug read for debugger or profiler from cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::dread
     */
    typename DParams::data_type
    dread(const codasip_address_t addr, const Index sbc = DParams::BYTES_PER_WORD)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            return BaseType::dread(addr, sbc);
        }
        return m_Registers.interface.dread(addr, sbc);
    }
    template<class Resp>
    typename DParams::data_type dread(const codasip_address_t addr, const Index sbc, Resp& resp)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            return BaseType::dread(addr, sbc, resp);
        }
        return m_Registers.interface.dread(addr, sbc, resp);
    }
    /**
     *  \{
     *  \brief   Read data from cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::read
     */
    typename DParams::data_type
    read(const codasip_address_t addr, const Index sbc = DParams::BYTES_PER_WORD)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            return BaseType::read(addr, sbc);
        }
        return m_Registers.interface.read(addr, sbc);
    }
    template<class Resp>
    typename DParams::data_type read(const codasip_address_t addr,
        const Index sbc,
        Resp& resp,
        const uint8_t hprot = CP_AHB_DATA_ACCESS | CP_AHB_PRIVILEGED,
        const uint8_t hmastlock = CP_AHB_UNLOCK)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            return BaseType::read(addr, sbc, resp, hprot, hmastlock);
        }
        return m_Registers.interface.read(addr, sbc, resp);
    }
    /**
     *  \}
     *  \brief       Debug write for debugger or profiler.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::dwrite
     */
    void dwrite(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc = DParams::BYTES_PER_WORD)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            BaseType::dwrite(data, addr, sbc);
        }
        else if (m_Registers.IsICacheOperationAddress(addr))
        {
            m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(data, addr);
        }
        else if (m_Registers.IsDCacheOperationAddress(addr))
        {
            m_Registers.GetDCacheSlaveInterface().DoCacheOperationIA(data,
                addr,
                CP_AHB_DATA_ACCESS | CP_AHB_PRIVILEGED,
                CP_AHB_UNLOCK);
        }
        else
        {
            m_Registers.interface.dwrite(data, addr, sbc);
        }
    }
    /**
     *  \}
     *  \brief   Write data to cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::read
     */
    void write(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc = DParams::BYTES_PER_WORD)
    {
        AHBResponseCode resp = CP_AHB_OKAY;
        write(data, addr, sbc, resp);
        if (resp != CP_AHB_OKAY)
        {
            this->DoAbortSimulation();
        }
    }

    template<class Resp>
    void write(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc,
        Resp& resp,
        const uint8_t hprot = CP_AHB_DATA_ACCESS | CP_AHB_PRIVILEGED,
        const uint8_t hmastlock = CP_AHB_UNLOCK)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            BaseType::write(data, addr, sbc, resp, hprot, hmastlock);
        }
        else if (m_Registers.IsCacheOperationAddress(addr))
        {
            detail::ResourceAccess::Write(resp, CP_AHB_OKAY);
            if (!m_Registers.interface.IsMaxBc(sbc))
            {
                detail::ResourceAccess::Write(resp, CP_AHB_ERROR);
            }
            else if (m_Registers.IsICacheOperationAddress(addr))
            {
                m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(data, addr);
            }
            else if (m_Registers.IsDCacheOperationAddress(addr))
            {
                m_Registers.GetDCacheSlaveInterface().DoCacheOperationIA(data,
                    addr,
                    CP_AHB_DATA_ACCESS | CP_AHB_PRIVILEGED,
                    hmastlock);
            }
        }
        else
        {
            m_Registers.interface.write(data, addr, sbc, resp);
        }
    }
    /**
     *  \}
     *  \brief       Debug load to cache or registers.
     *  \copydetails codasip::resources::AhbLiteInitiatorInterface::load
     */
    void load(const typename DParams::data_type data,
        const codasip_address_t addr,
        const Index sbc = DParams::BYTES_PER_WORD)
    {
        if (!m_Registers.IsRegisterRegionAddress(addr))
        {
            BaseType::load(data, addr, sbc);
        }
        else if (m_Registers.IsICacheOperationAddress(addr))
        {
            m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(data, addr);
        }
        else if (m_Registers.IsDCacheOperationAddress(addr))
        {
            m_Registers.GetDCacheSlaveInterface().DoCacheOperationIA(data,
                addr,
                CP_AHB_DATA_ACCESS | CP_AHB_PRIVILEGED,
                CP_AHB_UNLOCK);
        }
        else
        {
            m_Registers.interface.load(data, addr, sbc);
        }
    }
    /**
     *  \{
     *  \brief  Required interface for simulator state dumper (cached data have
     *          to be flushed before dumping simulator state and then dump).
     */
    void invalidate_all()
    {
        this->dwrite(1, m_Registers.GetCacheOperationStartAddress() + (2 * RParams::BYTES_PER_WORD));
        this->dwrite(1, m_Registers.GetCacheOperationStartAddress() + (5 * RParams::BYTES_PER_WORD));
    }

    void flush_all()
    {
        this->dwrite(1, m_Registers.GetCacheOperationStartAddress() + (8 * RParams::BYTES_PER_WORD));
    }
    /** \} */

    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetBaseAddress
     */
    codasip_address_t GetBaseAddress() const
    {
        return m_Registers.GetBaseAddress();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetISize
     */
    typename DParams::data_type GetISize() const
    {
        return m_Registers.GetISize();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetDSize
     */
    typename DParams::data_type GetDSize() const
    {
        return m_Registers.GetDSize();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetIWays
     */
    typename DParams::data_type GetIWays() const
    {
        return m_Registers.GetIWays();
    }
    /**
     * \copydoc codasip::resources::CacheRegistersStorage::GetDWays
     */
    typename DParams::data_type GetDWays() const
    {
        return m_Registers.GetDWays();
    }

    /**
     * \copydoc    codasip::resources::Interface::blocking_cb
     */
    void blocking_cb(PayloadType& p) override
    {
        DEBUG_OUTPUT("DCacheBlockInterface | BLOCKING CB START");
        if (!m_Registers.IsRegisterRegionAddress(p.get_address()))
        {
            BaseType::blocking_cb(p);
        }
        else if (m_Registers.IsCacheOperationAddress(p.get_address()))
        {
            this->check_payload(p, false, true, true);
            if (!m_Registers.interface.IsMaxBc(p.get_bc()))
            {
                p.set_ahb_hresp(CP_AHB_ERROR);
            }
            else if (m_Registers.IsICacheOperationAddress(p.get_address()))
            {
                // I cache does not need hprot or hmastlock as it performs only invalidate operations
                // and thus its operations do not use master interface
                m_Registers.GetICacheSlaveInterface().DoCacheOperationIA(p.get_data(), p.get_address());
            }
            else if (m_Registers.IsDCacheOperationAddress(p.get_address()))
            {
                m_Registers.GetDCacheSlaveInterface().DoCacheOperationIA(p.get_data(),
                    p.get_address(),
                    p.get_ahb_hprot(),
                    p.get_ahb_hmastlock());
            }
        }
        else
        {
            m_Registers.interface.blocking(p);
        }
        DEBUG_OUTPUT("DCacheBlockInterface | BLOCKING CB END");
    }

protected:
    /**
     * \copydoc codasip::resources::CacheBlockInterfaceBase::DoResponse
     */
    void DoResponse(PayloadType& p) override
    {
        m_Registers.GetDCacheSlaveInterface().SetHxData(p.get_data());
        DEBUG_OUTPUT("DCacheBlockInterface | DATA PHASE");
        if (!m_Registers.IsRegisterRegionAddress(m_Buffer.GetRequest().get_address()))
        {
            BaseType::DoResponse(p);
        }
        else if (m_Registers.IsCacheOperationAddress(m_Buffer.GetRequest().get_address()))
        {
            DEBUG_OUTPUT("DCacheBlockInterface | DATA PHASE | CACHE OPERATION ADDRESS");
            switch (m_State)
            {
                case OKAY_READY:
                case OKAY_WAIT:
                case ERROR_READY:
                    if (m_Buffer.IsRequestInserted())
                    {
                        DEBUG_OUTPUT("DCacheBlockInterface | DATA PHASE | CACHE OPERATION ADDRESS "
                                     "| INSERTED REQUEST");
                        if (m_Registers.IsICacheOperationAddress(m_Buffer.GetRequest().get_address()))
                        {
                            m_Registers.GetICacheSlaveInterface().SetCacheOperationData(p.get_data());
                        }
                        else if (m_Registers.IsDCacheOperationAddress(
                                     m_Buffer.GetRequest().get_address()))
                        {
                            m_Registers.GetDCacheSlaveInterface().SetCacheOperationData(p.get_data());
                        }
                    }
                    if (m_Buffer.IsRequestAccepted())
                    {
                        DEBUG_OUTPUT("DCacheBlockInterface | DATA PHASE | CACHE OPERATION ADDRESS "
                                     "| ACCEPTED REQUEST");
                        if (m_Registers.IsICacheOperationAddress(m_Buffer.GetRequest().get_address()) &&
                            m_Registers.GetICacheSlaveInterface().DoCacheOperationDataCA(p.get_data(),
                                m_Buffer.GetRequest().get_ahb_hprot(),
                                m_Buffer.GetRequest().get_ahb_hmastlock()))
                        {
                            m_Buffer.MarkRequestFinished();
                        }
                        else if (m_Registers.IsDCacheOperationAddress(
                                     m_Buffer.GetRequest().get_address()) &&
                            m_Registers.GetDCacheSlaveInterface().DoCacheOperationDataCA(p.get_data(),
                                m_Buffer.GetRequest().get_ahb_hprot(),
                                m_Buffer.GetRequest().get_ahb_hmastlock()))
                        {
                            m_Buffer.MarkRequestFinished();
                        }
                        else
                        {
                            m_NextState = OKAY_WAIT;
                        }
                    }
                    break;
                case ERROR_WAIT:
                    p.set_data(0);
                    m_NextState = ERROR_READY;
                    break;
            }
            this->UpdatePayload(p);
        }
        else
        {
            switch (m_State)
            {
                case OKAY_READY:
                case OKAY_WAIT:
                case ERROR_READY:
                    if (m_Buffer.IsRequestAccepted())
                    {
                        m_Buffer.GetRequest().set_data(p.get_data());
                        DEBUG_OUTPUT("DCacheBlockInterface | DATA PHASE | Request sent to "
                                     "registers.");
                        m_Registers.interface.transport(m_Buffer.GetRequest(), CP_PHS_DATA);
                        this->UpdateNextState(m_Buffer.GetRequest().get_ahb_hresp(),
                            m_Buffer.GetRequest().get_ahb_hready());
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
                    break;
                case ERROR_WAIT:
                    m_NextState = ERROR_READY;
                    break;
            }
            // Update payload ready and response of payload according to m_NextState
            this->UpdatePayload(p);
        }
        // when we are not returning valid data we set payload data to 0
        if (!p.is_ahb_active_transfer() || m_NextState != OKAY_READY)
        {
            p.set_data(0);
        }
    }

private:
    using BaseType::ERROR_READY;
    using BaseType::ERROR_WAIT;
    using BaseType::m_Buffer;
    using BaseType::m_NextState;
    using BaseType::m_Registers;
    using BaseType::m_State;
    using BaseType::OKAY_READY;
    using BaseType::OKAY_WAIT;

    typename DParams::master_interface_t& m_CacheMasterInterface;
};

#ifdef DEBUG_OUTPUT
#    undef DEBUG_OUTPUT
#endif

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_DATA_INTERFACE_H_
