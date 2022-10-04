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
 *  \date   Oct 23, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_H_

#include "simulator/resources/csr_access_checker.h"
#include "simulator/resources/csr_address_checker.h"
#include "simulator/resources/csr_ahb_pac.h"
#include "simulator/resources/csr_cache_registers_interface.h"
#include "simulator/resources/csr_cache_registers_storage.h"
#include "simulator/resources/csr_cache_registers_target_interface.h"
#include "simulator/resources/csr_payload_sentinel.h"

namespace codasip {
namespace resources {

//#define DEBUG_OUTPUT_ENABLE
#ifdef DEBUG_OUTPUT_ENABLE
#    define DEBUG_OUTPUT(x) std::cout << x << std::endl
#else
#    define DEBUG_OUTPUT(x)
#endif

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::CacheRegistersParams
 *  \brief  Groups configuration about the instruction and data caches for the
 *          control and status registers.
 *  \tparam IParams Instruction cache configuration.
 *  \tparam DParams Data cache configuration.
 *  \tparam _BASE_ADDRESS Base address where the CSR is located (in the address space).
 *  \}
 */
template<class IParams, class DParams>
class CacheRegistersParams
{
public:
    /// Instruction cache configuration.
    typedef IParams ICacheParams;
    /// Data cache configuration.
    typedef DParams DCacheParams;
    /// Register value data type.
    typedef typename DParams::data_type DataType;
    /// Instruction cache slave interface type.
    typedef typename IParams::slave_interface_t ISlaveInterface;
    /// Data cache slave interface type.
    typedef typename DParams::slave_interface_t DSlaveInterface;
    class A
    {
    public:
        enum
        {
            IS_READABLE = true,
            IS_WRITABLE = true
        };
    };
    /// Enumeration of cache parameters.
    enum : codasip_address_t
    {
        VERSION = 4,
        BYTES_PER_WORD = DParams::BYTES_PER_WORD,
        I_IS_ENABLED = IParams::IS_ENABLED,
        D_IS_ENABLED = DParams::IS_ENABLED,
        D_WRITE_THROUGH = 0,
    };
    static Index GetLatencyRead(const Uid = 0, const Index = 0)
    {
        return 1;
    }
    static Index GetLatencyWrite(const Uid = 0, const Index = 0)
    {
        return 1;
    }

    static Index GetLatencySizeRead(const Uid = 0)
    {
        return 1;
    }
    static Index GetLatencySizeWrite(const Uid = 0)
    {
        return 1;
    }
};
/**
 *  \class  codasip::resources::CacheRegisters
 *  \brief  Represents cache control and status registers.
 *  \tparam RParams Cache control and status registers configuration.
 */
template<class RParams>
class CacheRegisters : public CacheRegistersInterface, public CacheRegistersStorage<RParams>
{
public:
    /**
     *  \brief  Constructs CacheRegisters object.
     */
    CacheRegisters(typename RParams::ISlaveInterface& instructionCacheSlaveInterface,
        typename RParams::DSlaveInterface& dataCacheSlaveInterface,
        const codasip_address_t baseAddress,
        const Index iSize,
        const Index dSize,
        const Index iNumWays,
        const Index dNumWays,
        const Index dLineSize,
        const Index iLineSize);
    /**
     *  \brief  Reset cache registers (reset request logic).
     */
    void Reset();
    /**
     *  \brief  Move one clock cycle further.
     */
    void ClockCycle();
    /**
     *  \brief  Decides whether given address lies in the addressable region of registers.
     *  \param  address Memory address that is checked.
     *  \return True if given address is in the addressable region of registers, false otherwise.
     */
    bool IsRegisterRegionAddress(const codasip_address_t address) const;
    /// \copydoc    codasip::resources::CacheRegistersInterface::IsWriteThroughEnabled
    bool IsWriteThroughEnabled() const override;
    /// \copydoc    codasip::resources::CacheRegistersStorage::IsICacheOperationAddress
    bool IsICacheOperationAddress(const codasip_address_t address) const override;
    /// \copydoc    codasip::resources::CacheRegistersStorage::IsDCacheOperationAddress
    bool IsDCacheOperationAddress(const codasip_address_t address) const override;
    /// \copydoc    codasip::resources::CacheRegistersStorage::GetCacheOperation
    CacheOperation GetCacheOperation(const codasip_address_t address) const override;
    /// \copydoc    codasip::resources::Interface::blocking_cb
    void blocking_cb(Payload<typename RParams::DataType>& p, const Uid);
    /// \copydoc    codasip::resources::Interface::transport_cb
    void transport_cb(Payload<typename RParams::DataType>& p, const Phase phase, const Uid);
    /// Instruction cache slave interface accessor.
    typename RParams::ISlaveInterface& GetICacheSlaveInterface()
    {
        return m_InstructionCacheSlaveInterface;
    }
    /// Instruction cache slave interface accessor.
    typename RParams::DSlaveInterface& GetDCacheSlaveInterface()
    {
        return m_DataCacheSlaveInterface;
    }
    /// PayloadSentinel alias used as a template parameter for registers target interface.
    typedef PayloadSentinel<typename RParams::DCacheParams::data_type,
        RParams::DCacheParams::BYTE_BIT_WIDTH,
        RParams::DCacheParams::ADDR_BIT_WIDTH,
        codasip::resources::Endianness(RParams::DCacheParams::ENDIANNESS),
        AhbPac>
        PayloadSentinelType;
    /// AccessChecker alias used as a template parameter for register target interface.
    typedef AccessChecker<AddressChecker<PayloadSentinelType>> AccessCheckerType;
    CacheRegistersTargetInterface<AccessCheckerType, CacheRegisters, typename RParams::A> interface;

    bool GetRequestFlag() const
    {
        return m_RequestFlag;
    }

    /// \copydoc    codasip::resources::CacheRegistersStorage::IsCacheOperationAddress
    using CacheRegistersStorage<RParams>::IsCacheOperationAddress;

private:
    static bool
    IsAddressInRegion(const codasip_address_t, const codasip_address_t, const codasip_address_t);
    void DoRequest(Payload<typename RParams::DataType>&);
    void DoResponse(Payload<typename RParams::DataType>&);
    /// Provides access to I cache counters, settings and operations.
    typename RParams::ISlaveInterface& m_InstructionCacheSlaveInterface;
    /// Provides access to D cache counters, settings and operations.
    typename RParams::DSlaveInterface& m_DataCacheSlaveInterface;
    bool m_RequestFlag;
    bool m_ClearRequestFlag;
};
template<class RParams>
CacheRegisters<RParams>::CacheRegisters(typename RParams::ISlaveInterface& instructionCacheSlaveInterface,
    typename RParams::DSlaveInterface& dataCacheSlaveInterface,
    const codasip_address_t baseAddress,
    const Index iSize,
    const Index dSize,
    const Index iNumWays,
    const Index dNumWays,
    const Index dLineSize,
    const Index iLineSize)
  : CacheRegistersStorage<RParams>(instructionCacheSlaveInterface,
        dataCacheSlaveInterface,
        baseAddress,
        iSize,
        dSize,
        iNumWays,
        dNumWays,
        dLineSize,
        iLineSize)
  , interface("r_if", 0, static_cast<CacheRegisters*>(this))
  , m_InstructionCacheSlaveInterface(instructionCacheSlaveInterface)
  , m_DataCacheSlaveInterface(dataCacheSlaveInterface)
  , m_RequestFlag(false)
  , m_ClearRequestFlag(false)
{}
template<class RParams>
void CacheRegisters<RParams>::Reset()
{
    interface.reset();
    m_RequestFlag = false;
    m_ClearRequestFlag = false;
    CacheRegistersStorage<RParams>::Reset();
}
template<class RParams>
void CacheRegisters<RParams>::ClockCycle()
{
    if (m_ClearRequestFlag)
    {
        m_RequestFlag = false;
        m_ClearRequestFlag = false;
    }
    if (m_RequestFlag)
    {
        m_ClearRequestFlag = true;
    }
    CacheRegistersStorage<RParams>::ClockCycle();
    interface.clock_cycle();

    m_InstructionCacheSlaveInterface.CacheClockCycle();
    m_DataCacheSlaveInterface.CacheClockCycle();
}
template<class RParams>
bool CacheRegisters<RParams>::IsRegisterRegionAddress(const codasip_address_t address) const
{
    return IsAddressInRegion(address, this->GetBaseAddress(), this->GetEndAddress());
}
template<class RParams>
bool CacheRegisters<RParams>::IsWriteThroughEnabled() const
{
    return this->GetWriteThroughFlag();
}
template<class RParams>
bool CacheRegisters<RParams>::IsICacheOperationAddress(const codasip_address_t address) const
{
    return CacheRegistersStorage<RParams>::IsICacheOperationAddress(address);
}
template<class RParams>
bool CacheRegisters<RParams>::IsDCacheOperationAddress(const codasip_address_t address) const
{
    return CacheRegistersStorage<RParams>::IsDCacheOperationAddress(address);
}
template<class RParams>
CacheOperation CacheRegisters<RParams>::GetCacheOperation(const codasip_address_t address) const
{
    return CacheRegistersStorage<RParams>::GetCacheOperation(address);
}
/**
 *  \brief  Decides whether the address lies in specified region.
 *  \param  address Address whose location is examined.
 *  \param  regionStart Start of the address region.
 *  \param  regionEnd   End of the address region.
 *  \return True if the address lies between two addresses, false otherwise.
 */
template<class RParams>
bool CacheRegisters<RParams>::IsAddressInRegion(const codasip_address_t address,
    const codasip_address_t regionStart,
    const codasip_address_t regionEnd)
{
    return (address >= regionStart && address <= regionEnd);
}
template<class RParams>
void CacheRegisters<RParams>::blocking_cb(Payload<typename RParams::DataType>& p, const Uid)
{
    switch (p.get_command())
    {
        case CP_CMD_WRITE:
        case CP_CMD_DWRITE:
        case CP_CMD_LOAD:
            this->Store(p.get_data(), p.get_address());
            if (this->IsCacheClearCountersAddress(p.get_address()))
            {
                this->ClearCounters();
            }
            break;
        case CP_CMD_DREAD:
        case CP_CMD_READ:
            p.set_data(this->Load(p.get_address()));
            // fall through
        default:
            p.set_ahb_hready(CP_AHB_READY);
            p.set_ahb_hresp(CP_AHB_OKAY);
            break;
    }
}
template<class RParams>
void CacheRegisters<RParams>::transport_cb(Payload<typename RParams::DataType>& p,
    const Phase phase,
    const Uid)
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
/**
 *  \brief  Processes transport address phase.
 *  \param  p   Payload that is to be processed.
 */
template<class RParams>
void CacheRegisters<RParams>::DoRequest(Payload<typename RParams::DataType>& p)
{
    DEBUG_OUTPUT("CACHE REGISTERS | ADDRESS PHASE START");
    DEBUG_OUTPUT(p.PrintAhbLite());
    if (p.get_command() != CP_CMD_WRITE)
    {
        return;
    }
    if (this->IsCacheClearCountersAddress(p.get_address()))
    {
        this->ClearCounters();
    }
    DEBUG_OUTPUT("CACHE REGISTERS | ADDRESS PHASE END");
}
/**
 *  \brief  Processes transport data phase.
 *  \param  p   Payload that is to be processed.
 */
template<class RParams>
void CacheRegisters<RParams>::DoResponse(Payload<typename RParams::DataType>& p)
{
    DEBUG_OUTPUT("CACHE REGISTERS | DATA PHASE START");
    DEBUG_OUTPUT(p.PrintAhbLite());
    switch (p.get_command())
    {
        case CP_CMD_WRITE:
        case CP_CMD_DWRITE:
        case CP_CMD_LOAD:
            this->Store(p.get_data(), p.get_address());
            m_RequestFlag = true;
            m_ClearRequestFlag = false;
            break;
        case CP_CMD_DREAD:
        case CP_CMD_READ:
            p.set_data(this->Load(p.get_address()));
            break;
        default:
            break;
    }
    p.set_ahb_hready(CP_AHB_READY);
    p.set_ahb_hresp(CP_AHB_OKAY);
    DEBUG_OUTPUT("CACHE REGISTERS | DATA PHASE END");
}

#ifdef DEBUG_OUTPUT
#    undef DEBUG_OUTPUT
#endif

}   // namespace resources
}   // namespace codasip
#endif   // SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_H_
