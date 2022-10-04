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
 *  \author Jiri Bartak
 *  \date   Mar 8, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_H_

#include "simulator/resources/csr_cache_master_interface.h"
#include "simulator/resources/csr_cache_request.h"
#include "simulator/resources/csr_cache_storage.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/simbase/simulator_resources.h"

#include <cmath>
#include <deque>
#include <queue>
#include <vector>

//#define _DEBUG_CACHE
#define CACHE_INLINE inline

namespace codasip {
namespace resources {
/**
 *  \class  codasip::resources::Cache
 *  \brief  Software implementation of cache. The organization is constructed as one or more
 *          direct-mapped caches (performance reasons).
 *  \tparam _Params Parameters.
 */
template<class _Params>
class Cache : public Sentinel, public CacheStorage<_Params>, public _Params
{
public:
    /// Word length in bits.
    static const Index CACHE_DATA_BITS = _Params::WORD_BIT_WIDTH;
    /// Number of bits per byte.
    static const Index BYTE_BITS = _Params::LAU_BIT_WIDTH;
    /// Number of bytes per word.
    static const Index BYTES_PER_WORD = CACHE_DATA_BITS / BYTE_BITS;
    /// Target data bit width.
    static const Index TARGET_DATA_BITS = _Params::TARGET_WORD_BIT_WIDTH;
    /// Target bytes per word.
    static const Index TARGET_BYTES_PER_WORD = TARGET_DATA_BITS / BYTE_BITS;
    /// Burst mode enabled.
    static const bool BURST_ENABLED = _Params::BURST_ENABLED;

    /// Data type of connected target.
    typedef typename _Params::target_payload_t TData;
    /// Data type of the interface.
    typedef typename _Params::data_type Data;
    /// \copydoc codasip::resources::CacheStorage::LineIndex
    typedef codasip_address_t LineIndex;
    /// Master interface type - connect to the upper level memory.
    typedef CacheMasterInterface<typename _Params::master_interface_t, _Params::IS_WRITABLE> MasterInterface;
    /// Slave interface type - connected to the ASIP.
    typedef typename _Params::slave_interface_t SlaveIntreface;
    /// Container type for eviction data.
    typedef std::deque<TData> TargetDataAxi4;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    Cache(const std::string& name, const Uid uid, const Index size, const Index numWays, const Index lineSize);
    /**
     *  \brief  Reset cache (reset request logic).
     */
    void reset();
    /**
     *  \brief  Move one clock cycle further.
     */
    void clock_cycle();
    /**
     *  \brief  Sets the m_IA flag of cache slave interface.
     */
    void set_ia();
    /**
     *  \brief  Debug read for debugger or profiler.
     */
    Data dread(const codasip_address_t addr, const Index sbc = BYTES_PER_WORD);
    /**
     *  \brief  Debug write for debugger or profiler.
     */
    void dwrite(const Data data, const codasip_address_t addr, const Index sbc = BYTES_PER_WORD);
    /**
     *  \brief  Sets internal variable m_TargetInterfaceUsed to true to prevent any communication
     *          with Target.
     */
    void SetInterfaceUsed(const bool strong = true);
    /**
     *  \brief  Determines whether communication with Target is available or not.
     *  \return m_TargetInterfaceUsed value.
     */
    bool TargetUsed(const bool strong = false);
    /**
     *  \brief  Informs whether or not there is line eviction in progress.
     *  \return True when line evict is in progress.
     */
    bool EvictRunning() const;
    /**
     *  \brief  (AHB3-LITE) Returns whether the error occured during the cache line eviction.
     */
    bool HasEvictionErrorOccuredAhb() const
    {
        return m_EvictionErrorFlag;
    }
    /**
     *  \brief  Pushes cache word into eviction line.
     *  \param  data    Data to be pushed.
     */
    void PushEvictWord(const Data data);
    /**
     *  \brief  Eviction address mutator.
     *  \param  addr    New eviction address.
     */
    void SetEvictAddr(const codasip_address_t addr);
    /**
     *  \brief  Sets protection mode that should be used for eviction.
     *  \param  hprot   Protection mode.
     */
    void SetEvictHprot(const uint8_t hprot);
    /**
     *  \brief  Sets master lock code that should be used for eviction.
     *  \param  hmastlock   Master lock code.
     */
    void SetEvictHmastlock(const uint8_t hmastlock);
    /**
     *  \brief  (AXI4-LITE) Starts the cache line eviction.
     */
    void StartEvictionAxi4Lite();
    /**
     *  \brief  (AXI4) Starts the cache line eviction.
     */
    void StartEvictionAxi4();
    /**
     *  \brief  (AHB3-LITE) Starts the cache line eviction.
     */
    void StartEvictionAhb();
    /**
     *  \brief  Read line address mutator.
     *  \param  addr    New read line address.
     */
    void SetLineFillAddr(codasip_address_t addr);
    /**
     *  \brief  Returns line fill address.
     */
    codasip_address_t GetLineFillAddr() const;
    /**
     *  \brief  Sets protection mode that should be used for line read.
     *  \param  hprot   Protection mode.
     */
    void SetLineFillHprot(const uint8_t hprot);
    /**
     *  \brief  Sets master lock code that should be used for line read.
     *  \param  hmastlock   Master lock code.
     */
    void SetLineFillHmastlock(const uint8_t hmastlock);
    /**
     *  \brief  (AXI4) Line fill burst type mutator.
     *  \param  burstType   New line fill burst type.
     */
    void SetLineFillBurstType(const AXIBurstType burstType);
    /**
     *  \brief  (AXI4) Line fill addresses mutator.
     *  \param  addresses   A vector of line fill addresses.
     */
    void SetLineFillAddresses(const std::deque<codasip_address_t>& addresses);
    /**
     *  \brief  (AXI4) Line fill burst lengths mutator.
     *  \param  burstLength A vector of burst lengths.
     */
    void SetLineFillBurstLengths(const std::deque<uint8_t>& burstLengths);
    /**
     *  \brief  (AXI4-LITE) Starts the cache line fill.
     */
    void StartLineFillAxi4Lite();
    /**
     *  \brief  (AXI4) Starts the cache line fill.
     */
    void StartLineFillAxi4();
    /**
     *  \brief  Skips one more cycle.
     *
     *  Increases m_SkipCycle member, that is used to store the number of cycles which should be
     *  skipped.
     */
    void IncreaseLatency();
    /**
     *  \{
     *  \brief  (IA) Provide IA and debug access to master interface.
     *  \param data Data that is written or read.
     *  \param addr Location of data.
     *  \param bc   Number of bytes to be processed.
     */
    void TargetDread(TData& data, const codasip_address_t addr, const Index bc);
    TData TargetDread(const codasip_address_t addr, const Index bc);
    void TargetDwrite(const TData data, const codasip_address_t addr, const Index bc);
    void TargetLoad(const TData data, const codasip_address_t addr, const Index bc);

    void TargetWrite(const TData data,
        const codasip_address_t addr,
        const Index bc,
        const uint8_t hprot,
        const uint8_t hmastlock);

    template<typename Resp>
    TData TargetRead(const codasip_address_t addr,
        const Index bc,
        Resp& resp,
        const uint8_t hprot,
        const uint8_t hmastlock);
    template<typename Resp>
    void TargetWrite(const TData data,
        const codasip_address_t addr,
        const Index bc,
        Resp& resp,
        const uint8_t hprot,
        const uint8_t hmastlock);
    template<typename Resp>
    void TargetNonCacheableWrite(const TData data,
        const codasip_address_t addr,
        const Index bc,
        Resp& resp,
        const uint8_t hprot,
        const uint8_t hmastlock);

    using TDataResponsePair = std::pair<TData, AXIResponseCode>;
    TDataResponsePair
    TargetRead(const codasip_address_t addr, const Index bc, const uint8_t hprot, const uint8_t hmastlock);
    TDataResponsePair TargetNonCacheableRead(const codasip_address_t addr,
        const Index bc,
        const uint8_t hprot,
        const uint8_t hmastlock);
    /**
     *  \}
     *  \brief  (IA) Returns AHB response code for last request on master interface.
     */
    AHBResponseCode TargetLastAHBResponseCode() const;
    /**
     *  \brief  (IA) Returns AHB ready code for last request on master interface.
     */
    AHBReadyCode TargetLastAHBReadyCode() const;
    /**
     *  \brief  (CA) Invokes address phase processing on master interface.
     *  \param type Type of command.
     *  \param addr Address to be processed.
     *  \param sbi  Byte index of processed data.
     *  \param sbc  Number of bytes to process.
     *  \return Ready code of master interface that tells us whether the request was accepted or
     *          not.
     */
    AHBReadyCode TargetRequest(const Command type,
        const codasip_address_t addr,
        const Index sbi,
        const Index sbc,
        const uint8_t hprot,
        const uint8_t hmastlock);
    /**
     *  \brief  (CA)    Invokes address phase processing on master interface.
     *  \param  p   Request payload.
     *  \return Ready code of master interface that tells us whether the request was accepted or not.
     */
    AHBReadyCode TargetRequest(Payload<TData>& p);
    /**
     *  \brief  (CA) Request in the error-response cycle.
     */
    void TargetErrRequest(const Command type,
        const codasip_address_t addr,
        const Index sbi,
        const Index sbc,
        const uint8_t hprot,
        const uint8_t hmastlock);
    /**
     *  \brief  Invokes read command data phase on master interface.
     *  \param  ready   Master interface ready code.
     *  \param  resp    Master interface response code.
     *  \param  data    Data that is read.
     */
    void TargetReadData(AHBReadyCode& ready, AHBResponseCode& resp, TData& data);
    /**
     *  \brief  Invokes write command data phase on master interface.
     *  \param  ready   Master interface ready code.
     *  \param  resp    Master interface response code.
     *  \param  data    Data to be written.
     */
    void TargetWriteData(AHBReadyCode& ready, AHBResponseCode& resp, const TData data);
    /**
     *  \brief  Invokes write command data phase on master interface.
     *  \param  payload Payload containing data to be written.
     */
    void TargetWriteData(Payload<TData>& p);
    /**
     *  \brief  Return enumeration code for the write response phase.
     */
    void TargetWriteResponse(AHBReadyCode& ready, AHBResponseCode& resp);
    /**
     *  \brief  Starts burst on master interface.
     *  \copydetails    codasip::resources::CacheMasterInterface::StartBurst
     */
    void TargetStartBurst(const AHBBurstMode mode);
    /**
     *  \brief  Starts burst on master interface.
     *  \copydetails    codasip::resources::CacheMasterInterface::StartBurst
     */
    void
    TargetStartBurst(const AXIBurstType type, const codasip_address_t address, const uint8_t length);
    /**
     *  \brief  Stops burst on master interface.
     */
    void TargetStopBurst();
    /**
     *  \brief  Decides whether given command is valid for this type of cache.
     *  \param  cmd Examined command.
     *  \return True if command is valid, false otherwise.
     */
    static bool IsValidCommand(const Command cmd);
    /**
     *  \brief  Returns number of errors on cache master interface.
     */
    Counter GetMemoryErrorCount() const
    {
        return this->GetMasterInterface().GetMemoryErrorCount();
    }
    /**
     *  \brief  Resets memory error counter of cache master interface.
     */
    void ResetMemoryErrorCount()
    {
        this->GetMasterInterface().ResetMemoryErrorCount();
    }
    /**
     *  \brief  Evicts a cache line in the eviction buffer.
     *  \return Clear eviction buffer flag.
     */
    bool EvictCacheLine();
    /**
     *  \brief  Clears the eviction buffer.
     */
    void ClearEvictionBuffer()
    {
        m_EvictLine.clear();
    }
    /**
     *  \brief  (AXI4-LITE) Returns the number of target words filled so far.
     */
    size_t GetNumTargetWordsFilledAxi() const
    {
        return m_LineFillDataAxi4.size();
    }
    /**
     *  \brief  (AXI4-LITE) Returns the number of cache words filled so far.
     */
    size_t GetNumCacheWordsFilledAxi() const
    {
        return (GetNumTargetWordsFilledAxi() * TARGET_BYTES_PER_WORD) / BYTES_PER_WORD;
    }
    /**
     *  \brief  (AXI4-LITE) Return the target word data filled so far.
     */
    const TargetDataAxi4& GetLineFillDataAxi() const
    {
        return m_LineFillDataAxi4;
    }
    /**
     *  \brief  (AXI4-LITE) Sets the filled target word data.
     *  \param  begin   Iterator to the begining of the source data.
     *  \param  end Iterator to the end of the source data.
     */
    template<typename IteratorType>
    void AssignLineFillDataAxi(IteratorType begin, IteratorType end)
    {
        m_LineFillDataAxi4.assign(begin, end);
    }
    /**
     *  \brief  (AXI4-LITE) Returns whether the error occured during line fill.
     */
    bool HasLineFillErrorOccuredAxi() const
    {
        return m_LineFillErrorAxi4;
    }
    /**
     *  \brief  (AXI4, AXI4-LITE) Returns whether the line fill has finished or not.
     */
    bool HasLineFillFinishedAxi4() const
    {
        return m_LineFillFinishedAxi4;
    }
    /**
     *  \brief  Returns the address of the first word of the cache line that contains given address.
     *  \param  address Address of a cache line word.
     */
    codasip_address_t GetCacheLineStartAddress(const codasip_address_t address) const;
    /**
     *  \brief  (AXI4, AXI4-LITE) Starts cache line fill.
     */
    bool CanStartLineFillAxi4(const codasip_address_t address) const;
    /**
     *  \brief  (AXI4) Sets an eviction delay.
     *  \param  delay   Number of delay cycles.
     */
    void SetEvictionDelayAxi4(const Counter delay);
#ifdef _DEBUG_CACHE
    std::vector<std::string> type_s;
#endif
private:
    /// Number of cache words in one target word.
    static const Index CACHE_WORDS_PER_TARGET_WORD = TARGET_DATA_BITS / CACHE_DATA_BITS;
    /// Endianness around cache.
    static const Endianness ENDIANNESS = static_cast<Endianness>(_Params::ENDIANNESS);
    /// DCache flag.
    static const bool IS_DCACHE = _Params::IS_WRITABLE && _Params::IS_READABLE;

    /// Replacement policy type.
    typedef typename _Params::replacement_policy_t ReplacementPolicy;
    /// Container type of cacheline.
    typedef typename std::vector<Data> CLine;
    /// Container type for eviction addresses.
    typedef std::queue<codasip_address_t> TargetAddressesAxi;
    /// Container type for AXI4 burst lengths.
    typedef std::queue<uint8_t> BurstLengthContainer;
    /// Container type for AXI4 burst data.
    typedef std::queue<std::queue<TData>> BurstDataContainer;

    void ResetInterfaceUsed();

    void PrepareEvictionAddressesAxi4Lite();
    void PrepareEvictionDataAxi4Lite();
    bool EvictCacheLineAxi4Lite();
    AHBReadyCode HandleEvictAddressPhaseAxi4Lite();
    AHBReadyCode HandleEvictDataPhaseAxi4Lite();
    AHBReadyCode HandleEvictResponsePhaseAxi4Lite();

    void PrepareEvictionBurstAddressesAxi4();
    void PrepareEvictionBurstLengthsAxi4();
    void PrepareEvictionBurstDataAxi4();
    Payload<TData> PrepareEvictionPayloadAxi4();
    bool EvictCacheLineAxi4();
    AHBReadyCode HandleEvictAddressPhaseAxi4();
    AHBReadyCode HandleEvictDataPhaseAxi4();
    AHBReadyCode HandleEvictResponsePhaseAxi4();

    bool EvictCacheLineAhb();
    void HandleEvictAddressPhaseAhb();
    bool HandleEvictDataPhaseAhb();
    void HandleEvictErrorAhb();

    TData GetEvictWord(const LineIndex);
    /// Target usage lock.
    bool m_TargetInterfaceUsed = false;
    bool m_StrongLock = false;
    /// Eviction buffer.
    CLine m_EvictLine;
    /// Eviction tag.
    codasip_address_t m_EvictAddr = 0;
    /// Eviction protection mode.
    uint8_t m_EvictHprot = 0;
    /// Eviction master lock code.
    uint8_t m_EvictHmastlock = 0;
    /// Eviction offset for (write) address phase.
    LineIndex m_EvictOffsetPhaseAddrAhb = 0;
    /// Eviction offset for (write) data phase.
    LineIndex m_EvictOffsetPhaseDataAhb = 0;
    /// Skip eviction Cycle.
    unsigned char m_SkipCycle = 0;
    bool m_EvictionErrorFlag = false;

    TargetAddressesAxi m_EvictAddressesAxi;
    TargetDataAxi4 m_EvictDataAxi;
    Counter m_EvictResponsesAxi = 0;

    BurstLengthContainer m_EvictionBurstLengths = {};
    BurstDataContainer m_EvictionBurstData = {};

    /// Line fill address.
    codasip_address_t m_LineFillAddr = 0;
    /// Line fill protection mode.
    uint8_t m_LineFillHprot = CP_AHB_PROT_DEFAULT;
    /// Line fill master lock code.
    uint8_t m_LineFillHmastlock = CP_AHB_UNLOCK;

    void ResetLineFillAxi4Lite();
    void PrepareLineFillAddressesAxi4Lite();
    void LineFillAxi4Lite();
    bool HandleLineFillAddressPhaseAxi4Lite();
    bool HandleLineFillAddressPhaseAxi4();
    bool HandleLineFillDataPhaseAxi4();

    void ResetLineFillAxi4();
    void LineFillAxi4();

    void ResetEvictionAxi4();

    TargetAddressesAxi m_LineFillAddressesAxi4;
    TargetDataAxi4 m_LineFillDataAxi4;
    Counter m_LineFillResponsesExpectedAxi4 = 0;
    Counter m_LineFillResponsesReceivedAxi4 = 0;
    bool m_LineFillErrorAxi4 = false;
    bool m_LineFillFinishedAxi4 = true;

    AXIBurstType m_LineFillBurstType = CP_AXI_BURST_INCR;
    BurstLengthContainer m_LineFillBurstLengths = {};

    Counter m_EvictionResponsesExpectedAxi4 = 0;
    Counter m_EvictionResponsesReceivedAxi4 = 0;

    Counter m_EvictionDelay = 0;
};

template<class _Params>
CACHE_INLINE Cache<_Params>::Cache(const std::string& name,
    const Uid uid,
    const Index size,
    const Index numWays,
    const Index lineSize)
  : Sentinel(name, uid)
  , CacheStorage<_Params>(size, numWays, lineSize)
  , _Params(*this)
{
    CacheStorage<_Params>::Reset();
#ifdef _DEBUG_CACHE
    type_s.push_back("CP_CMD_NONE");
    type_s.push_back("CP_CMD_READ");
    type_s.push_back("CP_CMD_WRITE");
#endif
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::reset()
{
    CacheStorage<_Params>::Reset();
    if (MasterInterface::PROTOCOL == CP_PROTOCOL_AXI_LITE)
    {
        ResetLineFillAxi4Lite();
    }
    else if (MasterInterface::PROTOCOL == CP_PROTOCOL_AXI)
    {
        ResetLineFillAxi4();
        ResetEvictionAxi4();
    }
    ClearEvictionBuffer();
    this->GetSlaveInterface().Reset();
    this->GetMasterInterface().Reset();
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::clock_cycle()
{
    bool clear = false;
#ifdef _DEBUG_CACHE
    std::cout << "*====================================================*" << std::endl
              << "|              NEW CYCLE " << this->get_signature() << "                      |"
              << std::endl
              << "*====================================================*" << std::endl;
#endif
    ResetInterfaceUsed();
    if (m_SkipCycle)
    {
        m_SkipCycle--;
        SetInterfaceUsed(false);
    }
    else
    {
        if (EvictRunning())
        {
            clear = EvictCacheLine();
        }
        if (!HasLineFillFinishedAxi4())
        {
            if (MasterInterface::PROTOCOL == CP_PROTOCOL_AXI_LITE)
            {
                LineFillAxi4Lite();
            }
            else if (MasterInterface::PROTOCOL == CP_PROTOCOL_AXI)
            {
                LineFillAxi4();
            }
        }
    }

    this->GetMasterInterface().ClockCycle();
    this->GetSlaveInterface().ClockCycle();

    if (clear)
    {
        ClearEvictionBuffer();
    }
    else
    {
        if (MasterInterface::PROTOCOL == CP_PROTOCOL_AHB_LITE && !EvictRunning())
        {
            m_EvictionErrorFlag = false;
        }
    }
}

template<class _Params>
CACHE_INLINE typename Cache<_Params>::Data
Cache<_Params>::dread(const codasip_address_t addr, const Index sbc)
{
    return this->GetSlaveInterface().dread(addr, sbc);
}

template<class _Params>
CACHE_INLINE void
Cache<_Params>::dwrite(const Data data, const codasip_address_t addr, const Index sbc)
{
    this->GetSlaveInterface().dwrite(data, addr, sbc);
}

/**
 *  \brief  Sets internal variable m_TargetInterfaceUsed to false to enable communication with
 *          Target. Should be called at the begging of every clock cycle.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::ResetInterfaceUsed()
{
    m_TargetInterfaceUsed = false;
    m_StrongLock = false;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetInterfaceUsed(const bool strong)
{
    m_TargetInterfaceUsed = true;
    m_StrongLock = strong;
}

template<class _Params>
CACHE_INLINE bool Cache<_Params>::TargetUsed(const bool strong)
{
    return strong ? m_StrongLock : m_TargetInterfaceUsed;
}

template<class _Params>
CACHE_INLINE bool Cache<_Params>::EvictRunning() const
{
    return !m_EvictLine.empty();
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::PushEvictWord(const Data data)
{
    m_EvictLine.push_back(data);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetEvictAddr(const codasip_address_t addr)
{
    m_EvictAddr = addr;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetEvictHprot(const uint8_t hprot)
{
    m_EvictHprot = hprot;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetEvictHmastlock(const uint8_t hmastlock)
{
    m_EvictHmastlock = hmastlock;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::StartEvictionAxi4Lite()
{
    PrepareEvictionAddressesAxi4Lite();
    PrepareEvictionDataAxi4Lite();
    m_EvictResponsesAxi = 0;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::StartEvictionAxi4()
{
    ResetEvictionAxi4();
    PrepareEvictionBurstLengthsAxi4();
    PrepareEvictionBurstAddressesAxi4();
    PrepareEvictionBurstDataAxi4();
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::StartEvictionAhb()
{
    m_EvictOffsetPhaseAddrAhb = 0;
    m_EvictOffsetPhaseDataAhb = 0;
    m_EvictionErrorFlag = false;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetLineFillAddr(const codasip_address_t addr)
{
    m_LineFillAddr = addr;
}

template<class _Params>
CACHE_INLINE codasip_address_t Cache<_Params>::GetLineFillAddr() const
{
    return m_LineFillAddr;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetLineFillHprot(const uint8_t hprot)
{
    m_LineFillHprot = hprot;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetLineFillHmastlock(const uint8_t hmastlock)
{
    m_LineFillHmastlock = hmastlock;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetLineFillBurstType(const AXIBurstType burstType)
{
    m_LineFillBurstType = burstType;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetLineFillAddresses(const std::deque<codasip_address_t>& addresses)
{
    m_LineFillAddressesAxi4 = TargetAddressesAxi(addresses);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetLineFillBurstLengths(const std::deque<uint8_t>& burstLengths)
{
    m_LineFillBurstLengths = BurstLengthContainer(burstLengths);
}

template<class _Params>
CACHE_INLINE codasip_address_t Cache<_Params>::GetCacheLineStartAddress(
    const codasip_address_t address) const
{
    return address / this->GetLineSize() * this->GetLineSize();
}

template<class _Params>
CACHE_INLINE bool Cache<_Params>::CanStartLineFillAxi4(const codasip_address_t address) const
{
    if ((EvictRunning() && GetCacheLineStartAddress(address) == GetCacheLineStartAddress(m_EvictAddr)) ||
        !HasLineFillFinishedAxi4())
    {
        return false;
    }
    return true;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::SetEvictionDelayAxi4(const Counter delay)
{
    m_EvictionDelay = delay;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::StartLineFillAxi4Lite()
{
    ResetLineFillAxi4Lite();
    PrepareLineFillAddressesAxi4Lite();
    m_LineFillFinishedAxi4 = false;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::StartLineFillAxi4()
{
    ResetLineFillAxi4();
    m_LineFillFinishedAxi4 = false;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::ResetLineFillAxi4Lite()
{
    m_LineFillAddressesAxi4 = TargetAddressesAxi();
    m_LineFillDataAxi4 = TargetDataAxi4();
    m_LineFillResponsesExpectedAxi4 = 0;
    m_LineFillResponsesReceivedAxi4 = 0;
    m_LineFillErrorAxi4 = false;
    m_LineFillFinishedAxi4 = true;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::ResetLineFillAxi4()
{
    m_LineFillDataAxi4 = TargetDataAxi4();
    m_LineFillResponsesExpectedAxi4 = 0;
    m_LineFillResponsesReceivedAxi4 = 0;
    m_LineFillErrorAxi4 = false;
    m_LineFillFinishedAxi4 = true;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::IncreaseLatency()
{
    m_SkipCycle++;
}

template<class _Params>
CACHE_INLINE void
Cache<_Params>::TargetDread(TData& data, const codasip_address_t addr, const Index bc)
{
    data = this->GetMasterInterface().dread(addr, bc);
}

template<class _Params>
CACHE_INLINE typename Cache<_Params>::TData
Cache<_Params>::TargetDread(const codasip_address_t addr, const Index bc)
{
    return this->GetMasterInterface().dread(addr, bc);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::TargetWrite(const TData data,
    const codasip_address_t addr,
    const Index bc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    AHBResponseCode resp = CP_AHB_OKAY;
    this->GetMasterInterface().write(data, addr, bc, resp, hprot, hmastlock);
}

template<class _Params>
template<typename Resp>
CACHE_INLINE typename Cache<_Params>::TData Cache<_Params>::TargetRead(const codasip_address_t addr,
    const Index bc,
    Resp& resp,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    return this->GetMasterInterface().read(addr, bc, resp, hprot, hmastlock);
}

template<class _Params>
template<typename Resp>
CACHE_INLINE void Cache<_Params>::TargetWrite(const TData data,
    const codasip_address_t addr,
    const Index bc,
    Resp& resp,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    this->GetMasterInterface().write(data, addr, bc, resp, hprot, hmastlock);
}

template<class _Params>
template<typename Resp>
CACHE_INLINE void Cache<_Params>::TargetNonCacheableWrite(const TData data,
    const codasip_address_t addr,
    const Index bc,
    Resp& resp,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    TargetWrite(data, addr, bc, resp, hprot, hmastlock);
}

template<class _Params>
CACHE_INLINE void
Cache<_Params>::TargetDwrite(const TData data, const codasip_address_t addr, const Index bc)
{
    this->GetMasterInterface().dwrite(data, addr, bc);
}

template<class _Params>
CACHE_INLINE void
Cache<_Params>::TargetLoad(const TData data, const codasip_address_t addr, const Index bc)
{
    this->GetMasterInterface().load(data, addr, bc);
}

template<class _Params>
CACHE_INLINE typename Cache<_Params>::TDataResponsePair
Cache<_Params>::TargetRead(const codasip_address_t addr,
    const Index bc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    AXIResponseCode resp = CP_AXI_OKAY;
    TData targetData = TargetRead(addr, bc, resp, hprot, hmastlock);
    return {targetData, resp};
}

template<class _Params>
CACHE_INLINE typename Cache<_Params>::TDataResponsePair
Cache<_Params>::TargetNonCacheableRead(const codasip_address_t addr,
    const Index bc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    return TargetRead(addr, bc, hprot, hmastlock);
}

template<class _Params>
CACHE_INLINE AHBResponseCode Cache<_Params>::TargetLastAHBResponseCode() const
{
    return this->GetMasterInterface().GetLastAHBResponseCode();
}

template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::TargetLastAHBReadyCode() const
{
    return this->GetMasterInterface().GetLastAHBReadyCode();
}

template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::TargetRequest(const Command type,
    const codasip_address_t addr,
    const Index sbi,
    const Index sbc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    return this->GetMasterInterface().AddressPhase(type, addr, sbi, sbc, hprot, hmastlock);
}

template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::TargetRequest(Payload<TData>& p)
{
    return this->GetMasterInterface().AddressPhase(p);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::TargetErrRequest(const Command type,
    const codasip_address_t addr,
    const Index sbi,
    const Index sbc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (MasterInterface::PROTOCOL == CP_PROTOCOL_AHB_LITE)
    {
        TargetRequest(type, addr, sbi, sbc, hprot, hmastlock);
    }
}

template<class _Params>
CACHE_INLINE void
Cache<_Params>::TargetReadData(AHBReadyCode& ready, AHBResponseCode& resp, TData& data)
{
    this->GetMasterInterface().DataPhaseRead(ready, resp, data);
}

template<class _Params>
CACHE_INLINE void
Cache<_Params>::TargetWriteData(AHBReadyCode& ready, AHBResponseCode& resp, const TData data)
{
    this->GetMasterInterface().DataPhaseWrite(ready, resp, data);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::TargetWriteData(Payload<TData>& p)
{
    this->GetMasterInterface().DataPhaseWrite(p);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::TargetWriteResponse(AHBReadyCode& ready, AHBResponseCode& resp)
{
    this->GetMasterInterface().DataPhaseWriteResponse(ready, resp);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::TargetStartBurst(const AHBBurstMode mode)
{
    if (BURST_ENABLED)
    {
        this->GetMasterInterface().StartBurst(mode);
    }
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::TargetStartBurst(const AXIBurstType type,
    const codasip_address_t address,
    const uint8_t length)
{
    this->GetMasterInterface().StartBurst(type, address, length);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::TargetStopBurst()
{
    if (BURST_ENABLED || _Params::master_interface_t::PROTOCOL == CP_PROTOCOL_AXI)
    {
        this->GetMasterInterface().StopBurst();
    }
}

template<class _Params>
CACHE_INLINE bool Cache<_Params>::IsValidCommand(const Command cmd)
{
    return cmd == CP_CMD_READ || (IS_DCACHE && cmd == CP_CMD_WRITE);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::set_ia()
{
    this->GetSlaveInterface().SetIa();
}

template<class _Params>
CACHE_INLINE bool Cache<_Params>::EvictCacheLine()
{
#ifdef _DEBUG_CACHE
    std::cout << "Eviction in progress" << std::endl;
#endif
    if (_Params::master_interface_t::PROTOCOL == CP_PROTOCOL_AHB_LITE)
    {
        return EvictCacheLineAhb();
    }
    else if (_Params::master_interface_t::PROTOCOL == CP_PROTOCOL_AXI_LITE)
    {
        return EvictCacheLineAxi4Lite();
    }
    else
    {
        if (m_EvictionDelay)
        {
            m_EvictionDelay--;
            return false;
        }
        return EvictCacheLineAxi4();
    }
}

/**
 *  \brief  (AXI4-LITE) Prepares the addresses for the cache line eviction.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::PrepareEvictionAddressesAxi4Lite()
{
    m_EvictAddressesAxi = TargetAddressesAxi();
    for (LineIndex offset = 0; offset < this->GetLineSize(); offset += TARGET_BYTES_PER_WORD)
    {
        m_EvictAddressesAxi.emplace(m_EvictAddr + offset);
    }
}

/**
 *  \brief  (AXI4-LITE) Prepares the data for the cache line eviction.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::PrepareEvictionDataAxi4Lite()
{
    m_EvictDataAxi = TargetDataAxi4();
    for (LineIndex offset = 0; offset < this->GetLineSize(); offset += TARGET_BYTES_PER_WORD)
    {
        m_EvictDataAxi.emplace_back(GetEvictWord(offset));
    }
}

/**
 *  \brief  (AXI4-LITE) Prepares the addresses for the cache line fill.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::PrepareLineFillAddressesAxi4Lite()
{
    m_LineFillAddressesAxi4 = TargetAddressesAxi();
    codasip_address_t address = m_LineFillAddr;
    for (LineIndex offset = 0; offset < this->GetLineSize(); offset += TARGET_BYTES_PER_WORD)
    {
        m_LineFillAddressesAxi4.emplace(address);
        address += TARGET_BYTES_PER_WORD;
        if (address % this->GetLineSize() == 0)
        {
            address -= this->GetLineSize();
        }
    }
}

/**
 *  \brief  (AHB3-LITE) Handles the address phase of the cache line eviction.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::HandleEvictAddressPhaseAhb()
{
    if (m_EvictOffsetPhaseAddrAhb < this->GetLineSize())
    {
        const auto readyCode = TargetRequest(CP_CMD_WRITE,
            m_EvictAddr + m_EvictOffsetPhaseAddrAhb,
            0,
            TARGET_BYTES_PER_WORD,
            m_EvictHprot,
            m_EvictHmastlock);
        switch (readyCode)
        {
            case CP_AHB_READY:
                m_EvictOffsetPhaseAddrAhb += TARGET_BYTES_PER_WORD;
                break;
            case CP_AHB_WAIT:
                break;
        }
    }
}

/**
 *  \brief  (AHB3-LITE) Handles the data phase of the cache line eviction.
 *  \return True when all cache line words have been successfully sent, false otherwise.
 */
template<class _Params>
CACHE_INLINE bool Cache<_Params>::HandleEvictDataPhaseAhb()
{
    if (m_EvictOffsetPhaseDataAhb < this->GetLineSize() &&
        // AHB like: write data after address is accepted
        m_EvictOffsetPhaseAddrAhb > m_EvictOffsetPhaseDataAhb)
    {
        AHBReadyCode ready;
        AHBResponseCode resp;
        TargetWriteData(ready, resp, GetEvictWord(m_EvictOffsetPhaseDataAhb));
        if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
        {
            m_EvictOffsetPhaseDataAhb += TARGET_BYTES_PER_WORD;
        }
        if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
        {
            m_EvictionErrorFlag = true;
        }
    }
    return m_EvictOffsetPhaseDataAhb >= this->GetLineSize();
}

/**
 *  \brief  (AXI4-LITE) Handles the address phase of the cache line eviction.
 */
template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::HandleEvictAddressPhaseAxi4Lite()
{
    if (!m_EvictAddressesAxi.empty())
    {
        return TargetRequest(CP_CMD_WRITE,
            m_EvictAddressesAxi.front(),
            0,
            TARGET_BYTES_PER_WORD,
            m_EvictHprot,
            m_EvictHmastlock);
    }
    return CP_AHB_WAIT;
}

/**
 *  \brief  (AXI4-LITE) Handles the data phase of the cache line eviction.
 */
template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::HandleEvictDataPhaseAxi4Lite()
{
    if (!m_EvictDataAxi.empty() && m_EvictDataAxi.size() >= m_EvictAddressesAxi.size())
    {
        AHBReadyCode ready = CP_AHB_READY;
        AHBResponseCode resp = CP_AHB_OKAY;
        TargetWriteData(ready, resp, m_EvictDataAxi.front());
        return ready;
    }
    return CP_AHB_WAIT;
}

/**
 *  \brief  (AXI4-LITE) Handles the write response phase of the cache line eviction.
 */
template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::HandleEvictResponsePhaseAxi4Lite()
{
    AHBReadyCode ready = CP_AHB_READY;
    AHBResponseCode resp = CP_AHB_OKAY;
    TargetWriteResponse(ready, resp);
    if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
    {
        m_EvictResponsesAxi++;
        if (m_EvictResponsesAxi * TARGET_BYTES_PER_WORD >= this->GetLineSize())
        {
            return CP_AHB_READY;
        }
    }
    if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
    {
        return CP_AHB_READY;
    }
    return CP_AHB_WAIT;
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::PrepareEvictionBurstAddressesAxi4()
{
    const auto burstLengths = detail::PrepareBurstLengthsAxi4(this->GetTargetWordsPerLine(),
        this->GetAXITargetBurstLength());
    const auto burstAddresses = detail::PrepareBurstAddressesAxi4<TARGET_BYTES_PER_WORD>(m_EvictAddr,
        burstLengths);
    m_EvictAddressesAxi = TargetAddressesAxi(burstAddresses);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::PrepareEvictionBurstLengthsAxi4()
{
    const auto burstLengths = detail::PrepareBurstLengthsAxi4(this->GetTargetWordsPerLine(),
        this->GetAXITargetBurstLength());
    m_EvictionBurstLengths = BurstLengthContainer(burstLengths);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::PrepareEvictionBurstDataAxi4()
{
    const auto burstLengths = detail::PrepareBurstLengthsAxi4(this->GetTargetWordsPerLine(),
        this->GetAXITargetBurstLength());
    const auto targetWords = detail::TransformCacheWordsToTargetWords<TData, ENDIANNESS>(m_EvictLine);

    int j = 0;
    m_EvictionBurstData = {};
    for (const auto& burstLength : burstLengths)
    {
        std::queue<TData> burstData = {};
        for (uint8_t i = 0; i <= burstLength && j < targetWords.size(); ++i, ++j)
        {
            burstData.emplace(targetWords[j]);
        }
        m_EvictionBurstData.emplace(burstData);
    }
}

template<class _Params>
CACHE_INLINE Payload<typename Cache<_Params>::TData> Cache<_Params>::PrepareEvictionPayloadAxi4()
{
    Payload<TData> p;
    p.set_axi_ready(CP_AXI_READY);
    p.set_data(m_EvictionBurstData.front().front());
    p.set_axi_wstrb(-1);
    p.set_axi_last(m_EvictionBurstData.front().size() == 1 ? 1 : 0);
    return p;
}

/**
 *  \brief  Performs one cycle of cache line eviction on AXI4 master interface.
 *  \return Clear eviction buffer flag.
 */
template<class _Params>
CACHE_INLINE bool Cache<_Params>::EvictCacheLineAxi4()
{
    AHBReadyCode responseReady = HandleEvictResponsePhaseAxi4();
    AHBReadyCode addressReady = HandleEvictAddressPhaseAxi4();
    AHBReadyCode dataReady = HandleEvictDataPhaseAxi4();

    if (addressReady == CP_AHB_READY)
    {
        m_EvictionResponsesExpectedAxi4++;
        m_EvictAddressesAxi.pop();
        m_EvictionBurstLengths.pop();
    }
    if (dataReady == CP_AHB_READY)
    {
        m_EvictionBurstData.front().pop();
        if (m_EvictionBurstData.front().empty())
        {
            m_EvictionBurstData.pop();
        }
    }
    if (responseReady == CP_AHB_READY)
    {
        m_EvictionResponsesReceivedAxi4++;
    }
    return m_EvictionResponsesExpectedAxi4 == m_EvictionResponsesReceivedAxi4 &&
        m_EvictionBurstData.empty() && m_EvictAddressesAxi.empty();
}

template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::HandleEvictAddressPhaseAxi4()
{
    if (!m_EvictAddressesAxi.empty())
    {
        TargetStartBurst(CP_AXI_BURST_INCR, m_EvictAddressesAxi.front(), m_EvictionBurstLengths.front());

        return TargetRequest(CP_CMD_WRITE,
            m_EvictAddressesAxi.front(),
            0,
            TARGET_BYTES_PER_WORD,
            m_EvictHprot,
            m_EvictHmastlock);
    }
    return CP_AHB_WAIT;
}

template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::HandleEvictDataPhaseAxi4()
{
    if (!m_EvictionBurstData.empty())
    {
        const auto& currentDataBurst = m_EvictionBurstData.front();
        if (!currentDataBurst.empty())
        {
            auto p = PrepareEvictionPayloadAxi4();
            TargetWriteData(p);
            return p.get_ahb_hready();
        }
    }
    return CP_AHB_WAIT;
}

template<class _Params>
CACHE_INLINE AHBReadyCode Cache<_Params>::HandleEvictResponsePhaseAxi4()
{
    AHBReadyCode ready = CP_AHB_READY;
    AHBResponseCode resp = CP_AHB_OKAY;

    TargetWriteResponse(ready, resp);

    if ((ready == CP_AHB_READY && resp == CP_AHB_OKAY) ||
        (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR))
    {
        return CP_AHB_READY;
    }
    return CP_AHB_WAIT;
}

/**
 *  \brief  (AHB3-LITE) Handles the error during the cache line eviction.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::HandleEvictErrorAhb()
{
    TargetStopBurst();
    TargetErrRequest(CP_CMD_READ, 0, 0, 0, m_EvictHprot, m_EvictHmastlock);
}

/**
 *  \brief  Returns the target word that will be sent to the memory during cache line eviction.
 */
template<class _Params>
CACHE_INLINE typename Cache<_Params>::TData Cache<_Params>::GetEvictWord(const LineIndex offset)
{
    TData word = 0;
    if (BYTES_PER_WORD >= TARGET_BYTES_PER_WORD)
    {
        // Construct target word as cache word subblock.
        Data cacheWord = m_EvictLine.at(offset / BYTES_PER_WORD);
        word = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(&cacheWord,
            0,
            offset % BYTES_PER_WORD,
            TARGET_BYTES_PER_WORD);
    }
    else
    {
        for (int i = 0; i < CACHE_WORDS_PER_TARGET_WORD; i++)
        {
            const TData cWord = m_EvictLine.at(offset / BYTES_PER_WORD + i);
            if (ENDIANNESS == CP_LITTLE_ENDIAN)
            {
                word += (cWord << (i * CACHE_DATA_BITS));
            }
            else
            {
                word = LeftShift(word, CACHE_DATA_BITS);
                word |= cWord;
            }
        }
    }
    return word;
}

/**
 *  \brief  Performs one cycle of cache line eviction on AHB master interface.
 *  \return Clear eviction buffer flag.
 */
template<class _Params>
CACHE_INLINE bool Cache<_Params>::EvictCacheLineAhb()
{
    SetInterfaceUsed(false);
    if (m_EvictionErrorFlag)
    {
        HandleEvictErrorAhb();
        return true;
    }
    // (write) data phase
    if (HandleEvictDataPhaseAhb())
    {
        TargetStopBurst();
        return true;
    }
    // start burst
    if (m_EvictOffsetPhaseAddrAhb == 0)
    {
        TargetStartBurst(this->GetTargetBurstMode());
    }
    // (write) address phase
    HandleEvictAddressPhaseAhb();
    return false;
}

/**
 *  \brief  Performs one cycle of cache line eviction on AXI4-Lite master interface.
 *  \return Clear eviction buffer flag.
 */
template<class _Params>
CACHE_INLINE bool Cache<_Params>::EvictCacheLineAxi4Lite()
{
    SetInterfaceUsed(false);

    AHBReadyCode responseReady = HandleEvictResponsePhaseAxi4Lite();
    AHBReadyCode addressReady = HandleEvictAddressPhaseAxi4Lite();
    AHBReadyCode dataReady = HandleEvictDataPhaseAxi4Lite();

    if (addressReady)
    {
        m_EvictAddressesAxi.pop();
    }
    if (dataReady)
    {
        m_EvictDataAxi.pop_front();
    }

    return responseReady == CP_AHB_READY;
}

/**
 *  \brief  (AXI4-LITE) Performs one cycle of the cache line fill.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::LineFillAxi4Lite()
{
    const auto addressSent = HandleLineFillAddressPhaseAxi4Lite();
    const auto responseReceived = HandleLineFillDataPhaseAxi4();

    if (addressSent)
    {   // if the current address was sent successfully
        if (m_LineFillErrorAxi4)
        {   // if an error occured, we remove all prepared adresses
            // to prevent sending more address requests
            m_LineFillAddressesAxi4 = TargetAddressesAxi();
        }
        else
        {   // if an error did not occured, we remove only the sent address
            m_LineFillAddressesAxi4.pop();
        }
        // increment the number of expected responses
        m_LineFillResponsesExpectedAxi4++;
    }
    else if (m_LineFillErrorAxi4)
    {   // if the current address was not sent succesfully and an error has occured
        if (!m_LineFillAddressesAxi4.empty())
        {
            m_LineFillAddressesAxi4 = TargetAddressesAxi({m_LineFillAddressesAxi4.front()});
        }
    }
    if (responseReceived)
    {   //  if a response was received, we increment the number of received responses
        m_LineFillResponsesReceivedAxi4++;
    }

    //  read line is done when either the whole cache line has been read without an error or
    //  an error has occured and all requests has been sent and all responses for sent requests have been received
    m_LineFillFinishedAxi4 = (m_LineFillDataAxi4.size() == this->GetLineSize() / TARGET_BYTES_PER_WORD) ||
        (m_LineFillAddressesAxi4.empty() &&
            m_LineFillResponsesReceivedAxi4 == m_LineFillResponsesExpectedAxi4 && m_LineFillErrorAxi4);
}

/**
 *  \brief  (AXI4) Performs one cycle of the cache line fill.
 */
template<class _Params>
CACHE_INLINE void Cache<_Params>::LineFillAxi4()
{
    const auto addressSent = HandleLineFillAddressPhaseAxi4();
    const auto responseReceived = HandleLineFillDataPhaseAxi4();

    if (addressSent)
    {   // if the current address was sent successfully
        // increment the number of expected responses
        m_LineFillResponsesExpectedAxi4 += static_cast<Counter>(m_LineFillBurstLengths.front()) + 1;
        if (m_LineFillErrorAxi4)
        {   // if an error occured, we remove all prepared adresses
            // and burst lengths to prevent sending more address requests
            m_LineFillAddressesAxi4 = TargetAddressesAxi();
            m_LineFillBurstLengths = BurstLengthContainer();
        }
        else
        {   // if an error did not occured, we remove only the sent address and burst length
            m_LineFillAddressesAxi4.pop();
            m_LineFillBurstLengths.pop();
        }
    }
    else if (m_LineFillErrorAxi4)
    {   // if the current address was not sent succesfully and an error has occured
        if (!m_LineFillAddressesAxi4.empty())
        {
            m_LineFillAddressesAxi4 = TargetAddressesAxi({m_LineFillAddressesAxi4.front()});
            m_LineFillBurstLengths = BurstLengthContainer({m_LineFillBurstLengths.front()});
        }
    }
    if (responseReceived)
    {   //  if a response was received, we increment the number of received responses
        m_LineFillResponsesReceivedAxi4++;
    }

    //  read line is done when either the whole cache line has been read without an error or
    //  an error has occured and all requests has been sent and all responses for sent requests have been received
    m_LineFillFinishedAxi4 = (m_LineFillDataAxi4.size() == this->GetLineSize() / TARGET_BYTES_PER_WORD) ||
        (m_LineFillAddressesAxi4.empty() && m_LineFillBurstLengths.empty() &&
            m_LineFillResponsesReceivedAxi4 == m_LineFillResponsesExpectedAxi4 && m_LineFillErrorAxi4);
}

template<class _Params>
CACHE_INLINE void Cache<_Params>::ResetEvictionAxi4()
{
    m_EvictionBurstLengths = {};
    m_EvictionBurstData = {};
    m_EvictAddressesAxi = {};
    m_EvictionResponsesExpectedAxi4 = 0;
    m_EvictionResponsesReceivedAxi4 = 0;
    m_EvictionDelay = 0;
}

/**
 *  \brief  (AXI4-Lite) Handles the address phase of the line fill.
 *  \return True when address was sent sucessfully, false otherwise.
 */
template<class _Params>
CACHE_INLINE bool Cache<_Params>::HandleLineFillAddressPhaseAxi4Lite()
{
    if (!m_LineFillAddressesAxi4.empty())
    {   // if we have addresses to send and no error has occured so far,
        // we send another address
        return TargetRequest(CP_CMD_READ,
                   m_LineFillAddressesAxi4.front(),
                   0,
                   TARGET_BYTES_PER_WORD,
                   m_LineFillHprot,
                   m_LineFillHmastlock) == CP_AHB_READY;
    }
    return false;
}

/**
 *  \brief  Handles the address phase of the line fill.
 *  \return True when address was sent sucessfully, false otherwise.
 */
template<class _Params>
CACHE_INLINE bool Cache<_Params>::HandleLineFillAddressPhaseAxi4()
{
    if (!m_LineFillAddressesAxi4.empty())
    {   // if we have addresses to send and no error has occured so far,
        // we send another address
        TargetStartBurst(m_LineFillBurstType,
            m_LineFillAddressesAxi4.front(),
            m_LineFillBurstLengths.front());
        return TargetRequest(CP_CMD_READ,
                   m_LineFillAddressesAxi4.front(),
                   0,
                   TARGET_BYTES_PER_WORD,
                   m_LineFillHprot,
                   m_LineFillHmastlock) == CP_AHB_READY;
    }
    return false;
}

/**
 *  \brief  Handles the data phase of the line fill.
 *  \return True when the response was received, false otherwise.
 */
template<class _Params>
CACHE_INLINE bool Cache<_Params>::HandleLineFillDataPhaseAxi4()
{
    if (m_LineFillDataAxi4.size() < m_LineFillResponsesExpectedAxi4)
    {   //  if we expect data to receive, we send another data request
        AHBReadyCode ready = CP_AHB_READY;
        AHBResponseCode resp = CP_AHB_OKAY;
        TData data = 0;
        TargetReadData(ready, resp, data);
        m_LineFillDataAxi4.emplace_back(data);
        if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
        {
            return true;
        }
        if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
        {   // if an error has occured, we flag it which stops sending more
            // addresses
            m_LineFillErrorAxi4 = true;
            return true;
        }
    }
    return false;
}

}   // namespace resources
}   // namespace codasip
#endif   // SIMULATOR_RESOURCES_CSR_CACHE_H_
