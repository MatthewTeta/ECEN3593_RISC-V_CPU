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

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_STORAGE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_STORAGE_H_

#include "simulator/resources/csr_cache_registers_interface.h"
#include "simulator/resources/csr_helpers.h"

#include <map>
#include <vector>

namespace codasip {
namespace resources {

/**
 *  \class  codasip::resources::CacheRegistersStorage
 *  \brief  Stores control and status registers data.
 *  \tparam RParams Cache control and status registers configuration.
 */
template<class RParams>
class CacheRegistersStorage : public RParams
{
public:
    /// Type of data stored in registers.
    typedef typename RParams::DataType DataType;
    CacheRegistersStorage(typename RParams::ISlaveInterface& instructionCacheSlaveInterface,
        typename RParams::DSlaveInterface& dataCacheSlaveInterface,
        const codasip_address_t baseAddress,
        const Index iSize,
        const Index dSize,
        const Index iNumWays,
        const Index dNumWays,
        const Index iLineSize,
        const Index dLineSize);
    /**
     *  \brief  Given register address, it retrieves data from register.
     *  \param  address Address of a register from which the data should be loaded.
     *  \return Register value.
     */
    DataType Load(codasip_address_t address);
    /**
     *  \brief  Given address of writable register, it writes a value to the register.
     *  \param  address Address of a register to which the data should be stored.
     *  \param  value   Value to be stored.
     */
    void Store(const DataType value, codasip_address_t address);
    /**
     *  \brief  Base address getter
     */
    codasip_address_t GetBaseAddress() const
    {
        return m_BaseAddress;
    }
    /**
     *  \brief  I cache size getter
     */
    Index GetISize() const
    {
        return m_RegData[I_SIZE];
    }
    /**
     *  \brief  D cache size getter
     */
    Index GetDSize() const
    {
        return m_RegData[D_SIZE];
    }
    /**
     *  \brief  I numways getter
     */
    Index GetIWays() const
    {
        return m_RegData[I_WAYS];
    }
    /**
     *  \brief  D numways getter
     */
    Index GetDWays() const
    {
        return m_RegData[D_WAYS];
    }
    /**
     *  \brief  I line size getter
     */
    Index GetILineSize() const
    {
        return m_RegData[I_LINESIZE];
    }
    /**
     *  \brief  D line size getter
     */
    Index GetDLineSize() const
    {
        return m_RegData[D_LINESIZE];
    }
    /**
     *  \brief  registers end address getter
     */
    codasip_address_t GetEndAddress() const
    {
        return m_EndAddress;
    }
    /**
     *  \brief  Start address of cache operation section getter
     */
    codasip_address_t GetCacheOperationStartAddress() const
    {
        return m_cacheOperationsStartAddress;
    }

protected:
    /**
     *  \brief  Decides whether given address is operation register address.
     */
    bool IsCacheOperationAddress(const codasip_address_t address) const
    {
        return IsICacheOperationAddress(address) || IsDCacheOperationAddress(address);
    }
    /**
     *  \brief  Decides whether given address is I cahce operation register address.
     */
    bool IsICacheOperationAddress(const codasip_address_t address) const
    {
        return IsRegisterAddress(address) && m_RegAddToNameMap.at(address) >= I_INVALIDATE_ADDRESS &&
            m_RegAddToNameMap.at(address) <= I_INVALIDATE_ALL;
    }
    /**
     *  \brief  Decides whether given address is D cache operation register address.
     */
    bool IsDCacheOperationAddress(const codasip_address_t address) const
    {
        return IsRegisterAddress(address) && m_RegAddToNameMap.at(address) >= D_INVALIDATE_ADDRESS &&
            m_RegAddToNameMap.at(address) <= D_FLUSH_ALL;
    }
    /**
     *  \brief  Returns cache operation mapped to given register address.
     */
    CacheOperation GetCacheOperation(const codasip_address_t address) const
    {
        DEBUG_CONDITION(IsCacheOperationAddress(address));
        return m_RegNameToCacheOpMap.at(m_RegAddToNameMap.at(address));
    }
    /**
     *  \brief  Decides whether given address is cache info and counters register address.
     */
    bool IsCacheInfoAndCountersAddress(const codasip_address_t address) const
    {
        return IsRegisterAddress(address) && m_RegAddToNameMap.at(address) >= I_D_TYPE &&
            m_RegAddToNameMap.at(address) <= D_MEM_ERRORS;
    }
    /**
     *  \brief  Decides whether given address is clear counters register address.
     */
    bool IsCacheClearCountersAddress(const codasip_address_t address) const
    {
        return IsRegisterAddress(address) && m_RegAddToNameMap.at(address) == I_D_CLEAR_COUNTERS;
    }
    /**
     *  \brief  Move one clock cycle further.
     */
    void ClockCycle();
    /**
     *  \brief  Resets the data in registers.
     */
    void Reset();
    /**
     *  \brief  Returns write-through flag.
     */
    bool GetWriteThroughFlag() const
    {
        return static_cast<bool>(m_RegData[D_WRITE_THROUGH]);
    }
    /**
     *  \brief  Clears all counters.
     */
    void ClearCounters();

private:
    /// Word size in bytes.
    const Index BYTES_PER_WORD = RParams::BYTES_PER_WORD;
    /**
     *  \brief Enumeration of cache types.
     */
    enum CACHE_TYPE
    {
        NONE = 0,
        D_CACHE = 1,
        I_CACHE = 2,
        I_D_CACHE = 3
    };
    /**
     *  \brief  Enumeration of all registers.
     */
    enum REGISTER_NAME
    {
        I_D_TYPE = 0,   // has to start with 0 so the last enum _NUM_REGISTERS holds the correct value
        I_D_VERSION,
        I_SIZE,
        I_WAYS,
        I_LINESIZE,
        D_SIZE,
        D_WAYS,
        D_LINESIZE,
        I_HITS,
        I_MISSES,
        D_HITS,
        D_MISSES,
        I_MEM_ERRORS,
        D_MEM_ERRORS,
        D_WRITE_THROUGH,
        I_INVALIDATE_ADDRESS,
        I_INVALIDATE_LINE,
        I_INVALIDATE_ALL,
        D_INVALIDATE_ADDRESS,
        D_INVALIDATE_LINE,
        D_INVALIDATE_ALL,
        D_FLUSH_ADDRESS,
        D_FLUSH_LINE,
        D_FLUSH_ALL,
        I_D_CLEAR_COUNTERS,
        _NUM_REGISTERS   // not a register name, it is a helper that holds the number of registers,
                         // has to be last in enum
    };
    /**
     *  \brief  Maps an address to register name.
     *
     *  key =>  register address.
     *  value   =>  name of the register.
     */
    typedef std::map<codasip_address_t, REGISTER_NAME> RegisterAddressToRegisterNameMap;
    /**
     *  \brief  Maps a register name to cache operation.
     *
     *  key =>  register name.
     *  value   =>  cache operation.
     */
    typedef std::map<REGISTER_NAME, CacheOperation> RegisterNameToCacheOperationMap;
    void InitRegisterAddressToRegisterNameMap();
    void InitRegisterNameToCacheOperationMap();
    void InitReadableRegistersData();
    bool IsWritable(const REGISTER_NAME) const;
    bool IsReadable(const REGISTER_NAME) const;
    bool IsRegisterAddress(const codasip_address_t address) const;
    void UpdateCounters();
    /// Maps register address to its name.
    RegisterAddressToRegisterNameMap m_RegAddToNameMap;
    /// Maps register name to cache operation.
    RegisterNameToCacheOperationMap m_RegNameToCacheOpMap;
    /// Contains data for each register.
    std::vector<DataType> m_RegData;
    /// Provides access to I cache counters, settings and operations.
    typename RParams::ISlaveInterface& m_InstructionCacheSlaveInterface;
    /// Provides access to D cache counters, settings and operations.
    typename RParams::DSlaveInterface& m_DataCacheSlaveInterface;
    /// Base address.
    const codasip_address_t m_BaseAddress;
    /// End address.
    const codasip_address_t m_EndAddress;
    /// interface needs this
    const codasip_address_t m_cacheOperationsStartAddress;

    const Index m_iSize;
    const Index m_dSize;
    const Index m_iNumWays;
    const Index m_dNumWays;
    const Index m_iLineSize;
    const Index m_dLineSize;
};

template<class RParams>
CacheRegistersStorage<RParams>::CacheRegistersStorage(
    typename RParams::ISlaveInterface& instructionCacheSlaveInterface,
    typename RParams::DSlaveInterface& dataCacheSlaveInterface,
    const codasip_address_t baseAddress,
    const Index iSize,
    const Index dSize,
    const Index iNumWays,
    const Index dNumWays,
    const Index iLineSize,
    const Index dLineSize)
  : m_RegData(_NUM_REGISTERS, 0)
  , m_InstructionCacheSlaveInterface(instructionCacheSlaveInterface)
  , m_DataCacheSlaveInterface(dataCacheSlaveInterface)
  , m_BaseAddress(baseAddress)
  , m_EndAddress(baseAddress + (0x80 * BYTES_PER_WORD) - 1)
  , m_cacheOperationsStartAddress(baseAddress + (0x50 * BYTES_PER_WORD))
  , m_iSize(iSize)
  , m_dSize(dSize)
  , m_iNumWays(iNumWays)
  , m_dNumWays(dNumWays)
  , m_iLineSize(iLineSize)
  , m_dLineSize(dLineSize)
{
    InitRegisterAddressToRegisterNameMap();
    InitRegisterNameToCacheOperationMap();
    InitReadableRegistersData();
}
/**
 *  \brief  Initializes m_RegAddToNameMap member variable.
 *  \param  baseAddress Base address.
 */
template<class RParams>
void CacheRegistersStorage<RParams>::InitRegisterAddressToRegisterNameMap()
{
    const codasip_address_t CACHE_INFO_START_ADDRESS = m_BaseAddress;
    const codasip_address_t CACHE_COUNTERS_START_ADDRESS = m_BaseAddress + (0x20 * BYTES_PER_WORD);
    const codasip_address_t CACHE_SETTINGS_START_ADDRESS = m_BaseAddress + (0x30 * BYTES_PER_WORD);
    const codasip_address_t CACHE_CLEAR_COUNTERS_ADDRESS = m_BaseAddress + (0x70 * BYTES_PER_WORD);

    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 0 * BYTES_PER_WORD] = I_D_TYPE;
    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 1 * BYTES_PER_WORD] = I_D_VERSION;
    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 2 * BYTES_PER_WORD] = I_SIZE;
    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 3 * BYTES_PER_WORD] = I_WAYS;
    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 4 * BYTES_PER_WORD] = I_LINESIZE;
    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 5 * BYTES_PER_WORD] = D_SIZE;
    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 6 * BYTES_PER_WORD] = D_WAYS;
    m_RegAddToNameMap[CACHE_INFO_START_ADDRESS + 7 * BYTES_PER_WORD] = D_LINESIZE;
    m_RegAddToNameMap[CACHE_COUNTERS_START_ADDRESS + 0 * BYTES_PER_WORD] = I_HITS;
    m_RegAddToNameMap[CACHE_COUNTERS_START_ADDRESS + 1 * BYTES_PER_WORD] = I_MISSES;
    m_RegAddToNameMap[CACHE_COUNTERS_START_ADDRESS + 2 * BYTES_PER_WORD] = D_HITS;
    m_RegAddToNameMap[CACHE_COUNTERS_START_ADDRESS + 3 * BYTES_PER_WORD] = D_MISSES;
    m_RegAddToNameMap[CACHE_COUNTERS_START_ADDRESS + 4 * BYTES_PER_WORD] = I_MEM_ERRORS;
    m_RegAddToNameMap[CACHE_COUNTERS_START_ADDRESS + 5 * BYTES_PER_WORD] = D_MEM_ERRORS;
    m_RegAddToNameMap[CACHE_SETTINGS_START_ADDRESS + 0 * BYTES_PER_WORD] = D_WRITE_THROUGH;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 0 * BYTES_PER_WORD] = I_INVALIDATE_ADDRESS;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 1 * BYTES_PER_WORD] = I_INVALIDATE_LINE;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 2 * BYTES_PER_WORD] = I_INVALIDATE_ALL;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 3 * BYTES_PER_WORD] = D_INVALIDATE_ADDRESS;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 4 * BYTES_PER_WORD] = D_INVALIDATE_LINE;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 5 * BYTES_PER_WORD] = D_INVALIDATE_ALL;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 6 * BYTES_PER_WORD] = D_FLUSH_ADDRESS;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 7 * BYTES_PER_WORD] = D_FLUSH_LINE;
    m_RegAddToNameMap[m_cacheOperationsStartAddress + 8 * BYTES_PER_WORD] = D_FLUSH_ALL;
    m_RegAddToNameMap[CACHE_CLEAR_COUNTERS_ADDRESS] = I_D_CLEAR_COUNTERS;
}
/**
 *  \brief  Initializes m_RegNameToCacheOpmap member variable.
 */
template<class RParams>
void CacheRegistersStorage<RParams>::InitRegisterNameToCacheOperationMap()
{
    m_RegNameToCacheOpMap[I_INVALIDATE_ADDRESS] = OP_I_INVALIDATE_ADDRESS;
    m_RegNameToCacheOpMap[I_INVALIDATE_LINE] = OP_I_INVALIDATE_LINE;
    m_RegNameToCacheOpMap[I_INVALIDATE_ALL] = OP_I_INVALIDATE_ALL;
    m_RegNameToCacheOpMap[D_INVALIDATE_ADDRESS] = OP_D_INVALIDATE_ADDRESS;
    m_RegNameToCacheOpMap[D_INVALIDATE_LINE] = OP_D_INVALIDATE_LINE;
    m_RegNameToCacheOpMap[D_INVALIDATE_ALL] = OP_D_INVALIDATE_ALL;
    m_RegNameToCacheOpMap[D_FLUSH_ADDRESS] = OP_D_FLUSH_ADDRESS;
    m_RegNameToCacheOpMap[D_FLUSH_LINE] = OP_D_FLUSH_LINE;
    m_RegNameToCacheOpMap[D_FLUSH_ALL] = OP_D_FLUSH_ALL;
}
/**
 *  \brief  Initializes readable register data.
 */
template<class RParams>
void CacheRegistersStorage<RParams>::InitReadableRegistersData()
{
    m_RegData[I_D_TYPE] = 0;
    if (RParams::D_IS_ENABLED)
    {
        m_RegData[I_D_TYPE] += D_CACHE;
        m_RegData[D_SIZE] = m_dSize;
        m_RegData[D_WAYS] = m_dNumWays;
        m_RegData[D_LINESIZE] = m_dLineSize;
        m_RegData[D_WRITE_THROUGH] = RParams::D_WRITE_THROUGH;
    }
    else
    {
        m_RegData[D_WRITE_THROUGH] = 0;
    }
    if (RParams::I_IS_ENABLED)
    {
        m_RegData[I_D_TYPE] += I_CACHE;
        m_RegData[I_SIZE] = m_iSize;
        m_RegData[I_WAYS] = m_iNumWays;
        m_RegData[I_LINESIZE] = m_iLineSize;
    }
    m_RegData[I_D_VERSION] = RParams::VERSION;
    ClearCounters();
}
/**
 *  \brief  Decides whether the given register is writable.
 */
template<class RParams>
bool CacheRegistersStorage<RParams>::IsWritable(const REGISTER_NAME reg) const
{
    // To decide whether register is writable, we first enumerate all writable register (according
    // to specification) and then return whether the given register is present in this enumeration
    // or not.
    static const std::vector<REGISTER_NAME> writableRegisters = {D_WRITE_THROUGH,
        I_INVALIDATE_ADDRESS,
        I_INVALIDATE_LINE,
        I_INVALIDATE_ALL,
        D_INVALIDATE_ADDRESS,
        D_INVALIDATE_LINE,
        D_INVALIDATE_ALL,
        D_FLUSH_ADDRESS,
        D_FLUSH_LINE,
        D_FLUSH_ALL,
        I_D_CLEAR_COUNTERS};
    return std::find(writableRegisters.cbegin(), writableRegisters.cend(), reg) !=
        writableRegisters.cend();
}
/**
 *  \brief  Decides whether the given register is readable.
 */
template<class RParams>
bool CacheRegistersStorage<RParams>::IsReadable(const REGISTER_NAME reg) const
{
    // To decide whether register is writable, we first enumerate all writable register (according
    // to specification) and then return whether the given register is present in this enumeration
    // or not.
    static const std::vector<REGISTER_NAME> readableRegisters = {
        I_D_TYPE,
        I_D_VERSION,
        I_SIZE,
        I_WAYS,
        I_LINESIZE,
        D_SIZE,
        D_WAYS,
        D_LINESIZE,
        I_HITS,
        I_MISSES,
        D_HITS,
        D_MISSES,
        I_MEM_ERRORS,
        D_MEM_ERRORS,
        D_WRITE_THROUGH,
    };
    return std::find(readableRegisters.cbegin(), readableRegisters.cend(), reg) !=
        readableRegisters.cend();
}
/**
 *  \brief Decides whether the given address is a register address.
 */
template<class RParams>
bool CacheRegistersStorage<RParams>::IsRegisterAddress(const codasip_address_t address) const
{
    return m_RegAddToNameMap.find(address) != m_RegAddToNameMap.end();
}

template<class RParams>
typename CacheRegistersStorage<RParams>::DataType
CacheRegistersStorage<RParams>::Load(codasip_address_t address)
{
    // First we have to check if the given address is a register address.
    // If not, then we return 0 (according to specification).
    // If it is a register address, then we return the content of this register.
    if (!IsRegisterAddress(address) || !IsReadable(m_RegAddToNameMap.at(address)))
    {
        return 0;
    }
    // We have to update counter registers before we read them.
    UpdateCounters();
    return m_RegData.at(m_RegAddToNameMap.at(address));
}

template<class RParams>
void CacheRegistersStorage<RParams>::Store(const DataType value, codasip_address_t address)
{
    // First we have to check if the given address is a register address and if this register is
    // writable.
    // If not, then the write operation has no effect (according to specification).
    // If it is a register address, then we write the given value to it and perform appropriate
    // action.
    auto it = m_RegAddToNameMap.find(address);
    if (it == m_RegAddToNameMap.end() || !IsWritable(it->second))
    {
        return;
    }
    switch (it->second)
    {
        case D_WRITE_THROUGH:
            // if D cache is disabled D_WRITE_THROUGH register is useless and not present on HW
            // so we cannot write into it and its value remains 0
            if (m_RegData.at(I_D_TYPE) == I_CACHE)
            {
                m_RegData.at(it->second) = 0;
            }
            else
            {
                m_RegData.at(it->second) = value & 0x01;
            }
            break;
        default:
            m_RegData.at(it->second) = value;
            break;
    }
}
template<class RParams>
void CacheRegistersStorage<RParams>::ClockCycle()
{
    UpdateCounters();
}
template<class RParams>
void CacheRegistersStorage<RParams>::Reset()
{
    InitReadableRegistersData();
}
template<class RParams>
void CacheRegistersStorage<RParams>::ClearCounters()
{
    m_InstructionCacheSlaveInterface.ClearCounters();
    m_DataCacheSlaveInterface.ClearCounters();
    UpdateCounters();
}
/**
 *  \brief Copies current counter values from interfaces to registers. Should be called in Load
 *         method.
 */
template<class RParams>
void CacheRegistersStorage<RParams>::UpdateCounters()
{
    m_RegData[I_HITS] = m_InstructionCacheSlaveInterface.GetHitCount();
    m_RegData[I_MISSES] = m_InstructionCacheSlaveInterface.GetMissCount();
    m_RegData[D_HITS] = m_DataCacheSlaveInterface.GetHitCount();
    m_RegData[D_MISSES] = m_DataCacheSlaveInterface.GetMissCount();
    m_RegData[I_MEM_ERRORS] = m_InstructionCacheSlaveInterface.GetMemoryErrorCount();
    m_RegData[D_MEM_ERRORS] = m_DataCacheSlaveInterface.GetMemoryErrorCount();
}

}   // namespace resources
}   // namespace codasip
#endif   // SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_STORAGE_H_
