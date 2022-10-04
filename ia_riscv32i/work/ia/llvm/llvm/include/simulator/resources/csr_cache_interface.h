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

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_INTERFACE_H_

#include "simulator/resources/csr_cache.h"
#include "simulator/resources/csr_cache_registers.h"
#include "simulator/resources/csr_cache_request.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/detail/csr_cache_utils.h"
#include "utility/codasiputils.h"

#include <queue>

namespace codasip {
namespace resources {

#define CACHE_INLINE inline

//#define _DEBUG_CACHE_INTERFACE
//#define _DEBUG_CACHE_INTERFACE_F
#ifdef _DEBUG_CACHE_INTERFACE
//#define _PRINT_CLINES
#    ifdef _DEBUG_CACHE_INTERFACE_F
#        define _DEBUG_STREAM detail::DebugLogger::Get()
#    else
#        define _DEBUG_STREAM      \
            std::cout << std::dec; \
            STD_COUT
#    endif
#    define _DEBUG_LINE_OUTPUT(x) _DEBUG_STREAM << x << std::endl
#else
#    define _DEBUG_LINE_OUTPUT(x)
#endif

#define _DEBUG_LINE_OUTPUT_F(x) _DEBUG_LINE_OUTPUT("CacheInterface::" << __FUNCTION__ << ": " << x)

/**
 *  \class  codasip::resources::CacheInterface
 *  \brief  CLB interface of cache. Must be instantiated in generated core class
 *          as interface with specific number.
 *  \tparam T   Interface mixin base.
 *  \tparam M   Interface module type.
 *  \tparam CParams Generated parameters of the cache.
 */
template<class T, class M, class CParams>
class CacheInterface : public AhbLiteInitiatorInterface<T>,
                       public CacheRequest<CParams, M>,
                       private Payload<typename CParams::target_payload_t>
{
public:
    static constexpr int TARGET_BYTES_PER_WORD = CParams::TARGET_WORD_BIT_WIDTH /
        CParams::BYTE_BIT_WIDTH;
    /// \copydoc codasip::resources::CacheStorage::Data
    typedef typename CParams::data_type Data;
    /// Standard type for state.
    typedef unsigned char FSMState;
    /// Line index of entry in cache.
    typedef codasip_address_t LineIndex;
    /// Tag of entry in cache.
    typedef codasip_address_t Tag;
    /// Cache word data type.
    typedef typename CParams::data_type CData;
    /// Word container type.
    template<typename WordDataType>
    using WordContainer = std::vector<WordDataType>;
    /// Container type for cacheline.
    using CLine = WordContainer<CData>;
    /// Type of cache master interface.
    typedef CacheMasterInterface<typename CParams::master_interface_t, CParams::IS_WRITABLE> MasterInterface;
    static const Protocol MASTER_INTERFACE_PROTOCOL = CParams::master_interface_t::PROTOCOL;
    /**
     *  \brief  Create one cache interface with associated storage and inner profiler.
     *  \param  storage Shared storage container with line information, actual data and target
     *          component where data are written during write back phase. The storage can be locked.
     *  \param  innerProfiler Interface for inner profiling.
     *  \param  id Unique identification number of the interface.
     */
    CacheInterface(const std::string& name, const Uid uid, M& cacheCore);
    /**
     *  \brief  Currently do nothing.
     */
    ~CacheInterface();
    /**
     *  \brief  Return true if interface is busy.
     */
    bool IsBusy() const;
    /**
     * \brief   Cache software reset.
     * \copydetails codasip::resources::Cache::reset
     */
    void Reset();
    /**
     * \brief   Cache clock cycle method. Should be called in every step of CA simulation.
     * \copydetails codasip::resources::Cache::clock_cycle()
     */
    void ClockCycle();
    /**
     *  \brief  Invokes Cache clock cycle.
     */
    void CacheClockCycle()
    {
        this->m_Cache.clock_cycle();
    }
    /**
     *  \brief  Sets the m_IA flag.
     */
    void SetIa();
    /// \copydoc    codasip::resources::Interface::blocking_cb
    void blocking_cb(Payload<Data>& p) override;
    /// \copydoc    codasip::resources::Interface::transport_cb
    void transport_cb(Payload<Data>& p, const Phase phase) override;
    /**
     *  \brief  Invalidates last used index.
     */
    void InvalidateLastIndexUsed()
    {
        m_IsLastIndexUsedValid = false;
    }
    //  Required to be public by cache control status registers.
    /**
     *  \brief  Returns cache hit count.
     */
    Counter GetHitCount() const
    {
        return m_HitCounter;
    }
    /**
     *  \brief  Returns cache miss count.
     */
    Counter GetMissCount() const
    {
        return m_MissCounter;
    }
    /**
     *  \brief  Returns number of errors on cache master interface.
     */
    Counter GetMemoryErrorCount() const
    {
        return this->m_Cache.GetMemoryErrorCount();
    }
    /**
     *  \brief  Clears hit, miss cache counters and memory error counters.
     */
    void ClearCounters();
    /**
     *  \brief  Performs CA cache operation.
     *  \param  address   Cache operation address.
     *  \param  hprot   Cache operation protection mode.
     *  \param  hmastlock   Cache operation master lock code.
     *  \returns    True if cache is not busy and able to accept the request, false otherwise.
     */
    bool DoCacheOperationAddressCA(const codasip_address_t address,
        const uint8_t hprot,
        const uint8_t hmastlock);
    /**
     *  \brief  Performs CA cache operation.
     *  \param  data   Cache operation data.
     *  \param  hprot   Cache operation protection mode.
     *  \param  hmastlock   Cache operation master lock code.
     *  \returns    True if cache has finished the cache operation, false otherwise.
     */
    bool
    DoCacheOperationDataCA(const codasip_address_t data, const uint8_t hprot, const uint8_t hmastlock);
    /**
     *  \brief  Performs IA cache operation.
     *  \param  data   Cache operation data.
     *  \param  address Cache operation address.
     *  \param  hprot   Cache operation protection mode.
     *  \param  hmastlock   Cache operation master lock mode.
     */
    void DoCacheOperationIA(const codasip_address_t data,
        const codasip_address_t address,
        const uint8_t hprot = CP_AHB_PRIVILEGED,
        const uint8_t hmastlock = CP_AHB_UNLOCK);
    /**
     *  \brief  (IA) Invalidates cache line.
     */
    void InvalidateAddressIA(const codasip_address_t addr);
    /**
     *  \brief  Sets an interface to cache registers.
     *  \param value A value to be assigned to member variable.
     */
    void SetCacheRegistersInterface(CacheRegistersInterface* value)
    {
        m_RegistersInterface = value;
    }
    /**
     *  \brief  Non-cacheable flag mutator.
     */
    void SetNc(const bool value)
    {
        m_Nc = value;
    }
    /**
     *  \brief  Wrapper around CacheStorage::IsHit with more convenient parameter.
     *          Used only in unittests.
     */
    bool IsHit(const codasip_address_t address) const;
    /**
     *  \brief  Error state flag accessor.
     */
    bool GetErrorState() const
    {
        return m_ErrorState;
    }
    /**
     *  \brief  Error state flag mutator.
     */
    void SetErrorState(const bool value)
    {
        m_ErrorState = value;
    }
    /**
     *  \brief  HxData mutator.
     */
    void SetHxData(const Data value)
    {
        m_HxData = value;
    }
    /**
     *  \brief  Ready code accessor.
     */
    AHBReadyCode ReadyCode() const
    {
        return m_NextReady;
    }
    /**
     *  \brief  Increases next request latency if cache operation and cache request arrives simultaneously.
     */
    void CacheOperationNext()
    {
        if (!IsBusy() && !m_WasHit)
        {
            CacheRequestType::SetLatency(1);
        }
    }
    /**
     *  \brief  (Verification API) Returns the valid bit for the given set and index.
     */
    bool IsValid(const Index index, const Index way) const
    {
        return this->m_Cache.IsValid(way, index);
    }
    /**
     *  \brief  (Verification API) Returns the way of the last stored cache line.
     */
    Index GetLastSavedWay() const
    {
        return m_LastSavedWay;
    }
    /**
     *  \brief  (Verification API) Returns the index of the last stored cache line.
     */
    Index GetLastSavedIndex() const
    {
        return m_LastSavedIndex;
    }
    /**
     *  \brief  (Verification API) Returns the cache line in given set and index.
     */
    CLine GetCacheLine(const Index way, const Index index) const
    {
        return this->m_Cache.GetCacheLine(way, index);
    }
    /**
     *  \brief  (Verification API) Sets new cache line saved flag to false.
     */
    void ResetNewCacheLineSaved()
    {
        m_NewCacheLineSaved = false;
    }
    /**
     *  \brief  (Verification API) Returns new cache line saved flag.
     */
    bool GetNewCacheLineSaved() const
    {
        return m_NewCacheLineSaved;
    }
    /**
     *  \brief  Sets the cache operation data and the cache operation data ready flag.
     *  \param  addr    Cache operation data.
     */
    void SetCacheOperationData(const codasip_address_t addr)
    {
        m_CacheOperationData = addr;
        m_CacheOperationDataReady = true;
    }
    /**
     *  \brief  Returns the number of cache words filled so far during line fill.
     */
    size_t GetNumCacheLineWordsFilled() const
    {
        return (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE
                ? this->m_Cache.GetNumCacheWordsFilledAxi()
                : CacheRequestType::GetCacheLineWordsLoaded());
    }
    /**
     *  \brief  Returns the cache line words that were filled so far during line fill.
     */
    CLine GetCacheLineWordsFilled() const
    {
        if (MASTER_INTERFACE_PROTOCOL != CP_PROTOCOL_AXI_LITE)
        {
            return CacheRequestType::GetCacheLine();
        }
        // AXI4-LITE only
        const auto& targetWordsFilled = this->m_Cache.GetLineFillDataAxi();
        auto cacheWordsFilled = TransformTargetWordsToCacheWords<CLine, TLine>(
            {targetWordsFilled.begin(), targetWordsFilled.end()});
        cacheWordsFilled.resize(this->m_Cache.GetWordsPerLine(), 0);
        UnwrapCacheLine(cacheWordsFilled, this->m_Cache.GetLineFillAddr());
        return cacheWordsFilled;
    }
    /**
     *  \brief  Saves cache line to cache, updates flags, and replacement bits.
     *  \param  cacheLine   Cache line to be saved.
     *  \param  way A set into which the cache line will be saved.
     *  \param  index   An index under which the cache line will be saved.
     *  \param  tag A cache line tag.
     */
    void
    SaveCacheLineIntoCache(const CLine& cacheLine, const Index way, const LineIndex index, const Tag tag);

    /**
     *  \brief  Sets the saved cache line dirty.
     *  \param  way Cache line set.
     *  \param  index Cache line index.
     */
    void SetDirty(const Index way, const LineIndex index);

    /// \copydoc codasip::resources::CacheStorage::GetReplaceWay
    Index GetReplaceWay(const LineIndex index) const;

    /// \brief  Returns the way that will be replaced.
    Index GetReplaceWay() const;

    /// \copydoc codasip::resources::CacheStorage::GetLFSRValue
    uint16_t GetLFSRValue() const;

    /* End of CacheInterface public */
private:
    typedef AhbLiteInitiatorInterface<T> InterfaceBaseType;
    /// \copydoc codasip::resources::Cache::CACHE_DATA_BITS
    static const Index CACHE_DATA_BITS = CParams::WORD_BIT_WIDTH;
    /// Bit-width of target data.
    static const Index TARGET_DATA_BITS = CParams::TARGET_WORD_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::CACHE_ADDR_BITS
    static const Index CACHE_ADDR_BITS = CParams::ADDR_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::IS_DCACHE
    static const bool IS_DCACHE = CParams::IS_WRITABLE && CParams::IS_READABLE;
    /// \copydoc codasip::resources::Cache::IS_ICACHE
    static const bool IS_ICACHE = !CParams::IS_WRITABLE && CParams::IS_READABLE;
    /// \copydoc codasip::resources::Cache::BYTE_BITS
    static const Index BYTE_BITS = CParams::LAU_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::BYTES_PER_WORD
    static const Index BYTES_PER_WORD = CACHE_DATA_BITS / BYTE_BITS;
    /// Number of cache words in one target word.
    static const Index CACHE_WORDS_PER_TARGET_WORD = TARGET_DATA_BITS / CACHE_DATA_BITS;
    /// Number of target words in one cache word.
    static const Index TARGET_WORDS_PER_CACHE_WORD = CACHE_DATA_BITS / TARGET_DATA_BITS;
    /// Endianness around cache.
    static const Endianness ENDIANNESS = static_cast<Endianness>(CParams::ENDIANNESS);
    /// Local shortcut for the base class.
    typedef CacheRequest<CParams, M> CacheRequestType;
    /// Burst mode enabled.
    static const bool BURST_ENABLED = CParams::BURST_ENABLED;
    /// Enumeration of states for requests.
    enum
    {
        STATE_IDLE = 0,
        STATE_RESET,
        STATE_RESET_DONE,
        STATE_NCR_R_FINISH,
        STATE_NCR_REQUEST,
        STATE_NC_READ_DATA,
        STATE_NC_WRITE_DATA,
        STATE_NC_WRITE_RESPONSE,
        STATE_R_CL_REQUEST,
        STATE_R_CL_FINISH,
        STATE_I_ADDR,
        STATE_I_ADDR_DONE,
        STATE_I_LINE,
        STATE_I_LINE_DONE,
        STATE_I_ALL,
        STATE_I_ALL_DONE,
        STATE_NCR_W_FINISH,
        STATE_NCR_W_RESP,
        STATE_NCR_W_DONE,
        STATE_W_HIT,
        STATE_F_ADDR,
        STATE_F_ADDR_DONE,
        STATE_F_LINE,
        STATE_F_LINE_DONE,
        STATE_F_ALL,
        STATE_F_ALL_DONE,
        STATE_R_SKIP_CYCLE,
        STATE_R_SKIP_CYCLE_AXI4,
        STATE_SKIP_CYCLE,
        STATE_SKIP_CYCLE_AXI4,
        STATE_RAM_RESP,
        STATE_R_HIT,
        STATE_R_BUFFER_D,
        STATE_R_BUFFER_D_DELAYED,
        STATE_R_MISS_DONE,
        STATE_R_MISS_ERR,
        STATE_SAVE_LINE,
        STATE_SAVE_LINE_AXI4,
        STATE_W_MISS_DONE,
        STATE_WT_REQUEST,
        STATE_WT_FINISH,
        STATE_WT_RESP,
        STATE_WT_DONE,
        STATE_W_HIT_DELAYED,
        STATE_R_MISS_RESP,
        STATE_R_MISS_ERR_RESP,
        STATE_I_ADDR_REQ,
        STATE_I_LINE_REQ,
        STATE_I_ALL_REQ,
        STATE_F_ADDR_REQ,
        STATE_F_LINE_REQ,
        STATE_F_ALL_REQ,
    };
#ifdef _DEBUG_CACHE_INTERFACE
    std::vector<std::string> m_StateNames;
    Counter m_ClockCycleCounter = 0;
#endif
    /// \copydoc codasip::resources::CacheStorage::SetIndex
    typedef Index SetIndex;
    /// Target word data type.
    typedef typename CParams::target_payload_t TData;

    //  AXI DataTypes IA
    /// Container type for target line.
    using TLine = WordContainer<TData>;
    /// Word-response pair data type.
    template<typename WordDataType>
    using WordResponsePair = std::pair<WordDataType, AXIResponseCode>;
    /// Target word-response pair data type.
    using TargetWordResponsePair = WordResponsePair<TData>;
    /// Word-response pair container data type.
    template<typename WordDataType>
    using WordResponsePairContainer = std::vector<WordResponsePair<WordDataType>>;
    /// Target word-response pair container data type.
    using TargetWordResponsePairContainer = WordResponsePairContainer<TData>;
    /// Cache word-response pair container data type.
    using CacheWordResponsePairContainer = WordResponsePairContainer<CData>;
    using TargetWordsPerCacheWordContainer =
        std::array<TData, TARGET_WORDS_PER_CACHE_WORD == 0 ? 1 : TARGET_WORDS_PER_CACHE_WORD>;
    using CacheWordsPerTargetWordContainer =
        std::array<CData, CACHE_WORDS_PER_TARGET_WORD == 0 ? 1 : CACHE_WORDS_PER_TARGET_WORD>;

    // AXI methods IA
    CacheWordResponsePairContainer
    ReadLineAxi(const codasip_address_t startAddress, const uint8_t, const uint8_t);
    CacheWordResponsePairContainer
    ReadLineUsingWrappingBurst(const codasip_address_t startAddressTargetAligned,
        const uint8_t,
        const uint8_t);
    template<class Container>
    void
    UnwrapCacheLine(Container& cacheLine, const codasip_address_t startAddressTargetAligned) const;
    template<class Container>
    void WrapCacheLine(Container& cacheLine, const codasip_address_t startAddressTargetAligned) const;
    CacheWordResponsePairContainer
    ReadLineUsingIncrementingBurst(const codasip_address_t startAddressTargetAligned,
        const uint8_t,
        const uint8_t);
    CacheWordResponsePairContainer ReadCacheWordsFromTarget(const codasip_address_t,
        const codasip_address_t,
        const uint8_t,
        const uint8_t);
    TargetWordResponsePairContainer
    ReadTargetWords(const codasip_address_t, const Index, const uint8_t, const uint8_t);
    TargetWordResponsePairContainer
    ReadTargetWordsNonCacheable(const codasip_address_t, const Index, const uint8_t, const uint8_t);
    TargetWordResponsePair ReadTargetWordNonCacheable(const Payload<CData>& p);

    template<typename CacheWordContainer, typename TargetWordContainer>
    CacheWordContainer TransformTargetWordsToCacheWords(const TargetWordContainer&) const;
    CacheWordResponsePairContainer
    SplitTargetWordsToCacheWords(const TargetWordResponsePairContainer& targetWords) const;
    CacheWordResponsePairContainer
    ConcatenateTargetWordsToCacheWords(const TargetWordResponsePairContainer& targetWords) const;

    codasip_address_t GetCacheLineStartAddress(const codasip_address_t address) const;
    codasip_address_t GetCacheLineEndAddress(const codasip_address_t address) const;
    Index GetCacheWordCacheLineIndex(const codasip_address_t address) const;
    bool IsOkay(const AXIResponseCode resp) const;
    template<typename WordDataType>
    bool AllOkay(const WordResponsePairContainer<WordDataType>& wordResponsePairs) const;
    template<typename WordDataType>
    WordContainer<WordDataType>
    StripResponses(const WordResponsePairContainer<WordDataType>& wordsWithResponses) const;
    Index WriteCacheLineToCache(const codasip_address_t address,
        const CLine& cacheLine,
        const uint8_t,
        const uint8_t);
    void EvictCacheLineAxi(const Index set, const LineIndex index, const uint8_t, const uint8_t);
    void WriteCacheLineToTarget(const codasip_address_t address,
        const CLine& cacheLine,
        const uint8_t,
        const uint8_t);
    void WriteTargetLine(const codasip_address_t address,
        const TLine& targetLine,
        const uint8_t,
        const uint8_t);
    void WriteTargetLineUsingIncrementingBurst(const codasip_address_t,
        const TLine& targetLine,
        const uint8_t,
        const uint8_t);
    AXIResponseCode WriteTargetWords(const typename TLine::const_iterator&,
        const typename TLine::const_iterator&,
        const codasip_address_t,
        const uint8_t,
        const uint8_t);
    AXIResponseCode WriteTargetWordsNonCacheable(const typename TLine::const_iterator&,
        const typename TLine::const_iterator&,
        const codasip_address_t,
        const uint8_t,
        const uint8_t);
    AXIResponseCode WriteTargetWordNonCacheable(const TData&,
        const codasip_address_t,
        const Index,
        const uint8_t,
        const uint8_t);

    void NonCacheableReadAxi(Payload<CData>&);
    AXIResponseCode NonCacheableWriteAxi(const Payload<CData>&);

    void DwriteTargetWord(const Command, const TData&, const codasip_address_t, const Index);
    void DwriteTargetWords(const Command,
        const typename TLine::const_iterator&,
        const typename TLine::const_iterator&,
        const codasip_address_t);
    void DwriteAxi(const Command, const CData&, const codasip_address_t, const Index);

    TData DreadTargetWord(const codasip_address_t, const Index);
    TLine DreadTargetWords(const codasip_address_t, const Index);
    CData DreadAxi(const codasip_address_t, const Index);

    // AXI4-Lite CA
    CLine SplitTargetWordsToCacheWords(const TLine& targetWords) const;
    CLine ConcatenateTargetWordsToCacheWords(const TLine& targetWords) const;
    template<typename IteratorType>
    CLine ConcatenateTargetWordsToCacheWords(IteratorType begin, IteratorType end) const;

    void DoRequest(Payload<Data>&);
    void DoResponse(Payload<Data>&);
    Data Dread(const Payload<Data>&);
    void Load(const Payload<Data>&);
    void Dwrite(const Payload<Data>&);
    void Read(Payload<Data>&);
    void Write(Payload<Data>&);
    TData GatherTargetWord(const Index, const LineIndex, const LineIndex);
    void Fsm_step();
    AHBResponseCode ReadLine(const codasip_address_t, const uint8_t, const uint8_t);
    void WriteLine(const Index, const codasip_address_t, const uint8_t, const uint8_t);
    SetIndex WriteLoadedLine(const uint8_t, const uint8_t);
    void EvictCacheLine(const codasip_address_t, const uint8_t, const uint8_t);
    Tag GetTagFromAddr(const codasip_address_t) const;
    LineIndex GetIndexFromAddr(const codasip_address_t) const;
    LineIndex GetOffsetFromAddr(const codasip_address_t);
    void PrepareNCRRequest(const Command, const codasip_address_t, const Index, const Index);
    void HandleNonCacheableRequest();
    Payload<TData> PrepareNonCacheableRequestAxi4();
    void HandleNonCacheableRequestAxi4();
    void HandleNonCacheableReadAxi4();
    void HandleNonCacheableNarrowTargetReadAxi4();
    void HandleNonCacheableWriteAxi4();
    void HandleNonCacheableWriteResponseAxi4();
    void HandleNonCacheableReadFinish();
    void HandleNonCacheableWriteFinish();
    void PrepareWriteThroughRequest(const Data, const codasip_address_t, const Index, const Index);
    void DoTargetWriteNCData(AHBReadyCode&, AHBResponseCode&);
    template<class... Args>
    void DoTargetWrite(Args&&...);
    void DoTargetWriteCommand(const Command,
        const Data,
        const codasip_address_t,
        const Index,
        const uint8_t,
        const uint8_t);
    void DoWriteToWiderTarget(const Command,
        const TData,
        const codasip_address_t,
        const Index,
        const uint8_t,
        const uint8_t);
    void DoWriteToNarrowerTarget(const Command,
        const Data,
        const codasip_address_t,
        const Index,
        const uint8_t,
        const uint8_t);
    void PutCacheLineIntoEvictionBuffer(const Index, const LineIndex, const uint8_t, const uint8_t);
    void
    UpdateCacheLineInCache(const Data, const Index, const LineIndex, const LineIndex, const Index, const Index);
    void InvalidateCacheLine(const Index, const LineIndex);
    void PrepareDataWritePayloadsAXI(const Data&);
    /**
     *  \brief  (CA) Invalidates cache line.
     */
    void InvalidateAddressCA(const codasip_address_t addr);
    /**
     *  \brief  (IA) Invalidates cache line in all sets.
     */
    void InvalidateLineIA(const Index index);
    /**
     *  \brief  (CA) Invalidates cache line in all sets.
     */
    void InvalidateLineCA(const Index index);
    /**
     *  \brief  (IA) Invalidates whole cache.
     */
    void InvalidateAllIA();
    /**
     *  \brief  (CA) Invalidates whole cache.
     */
    void InvalidateAllCA();
    /**
     *  \brief  (IA) Flush cache line to master interface. Only effective in Dcache.
     */
    void FlushAddressIA(const codasip_address_t, const uint8_t, const uint8_t);
    /**
     *  \brief  (CA) Flush cache line to master interface. Only effective in Dcache.
     */
    void FlushAddressCA(const codasip_address_t, const uint8_t, const uint8_t);
    /**
     *  \brief  (IA) Flush cache line in all sets to master interface. Only effective in Dcache.
     */
    void FlushLineIA(const Index, const uint8_t, const uint8_t);
    /**
     *  \brief  (CA) Flush cache line in all sets to master interface. Only effective in Dcache.
     */
    void FlushLineCA(const Index, const uint8_t, const uint8_t);
    /**
     *  \brief  (IA) Flush all cache data to master interface. Only effective in Dcache.
     */
    void FlushAllIA(const uint8_t, const uint8_t);
    /**
     *  \brief  (CA) Flush all cache data to master interface. Only effective in Dcache.
     */
    void FlushAllCA(const uint8_t, const uint8_t);
    /// Unique identification number of the interface.
    const int m_Id;
    /// Holds next state of FSM.
    FSMState m_NextState;
    /// State of cache final state machine.
    FSMState m_FSMstate;
    /// Cache response during this clock cycle.
    AHBResponseCode m_NextResponse;
    /// Cache ready during this clock cycle.
    AHBReadyCode m_NextReady;
    /// Prevent response reset.
    bool m_PreventRespReset;
    /// Cache line is loaded in to the eviction buffer in a separate clock cycle.
    bool m_EvictDelay;
    /// IA flag.
    bool m_IA;
    /// Counts cache hits.
    Counter m_HitCounter;
    /// Counts cache misses.
    Counter m_MissCounter;
    /// Stores current request.
    Payload<Data> m_CurrentRequest;
    /// Stores current response.
    Payload<Data> m_CurrentResponse;
    /// Provides access to cache registers.
    CacheRegistersInterface* m_RegistersInterface = nullptr;
    friend class Cache<CParams>;
    /// Error state flag.
    bool m_ErrorState = false;
    /// Last request hit flag.
    bool m_WasHit = false;
    /// Non-cacheable region request flag.
    bool m_Nc = false;
    /// (AXI4-LITE) Enables write data together with address requests for NC and WT writes.
    bool m_WriteDataEnable = false;
    /// (Flush all) Eviction buffer empty flag.
    bool m_EvictionBufferEmpty = true;
    /// (Flush all) Skip set latency.
    bool m_SkipSetLatency = false;
    /// (Flush all) Do not set latency flag.
    bool m_DoNotSetLatency = false;
    /// (Flush all) Counts the number of target used cycles.
    Counter m_NumTargetUsedCycles = 0;
    /// Container type for AXI address write data.
    typedef std::queue<codasip_address_t> AWContainerType;
    /// Queue of non-cacheable address write requests (AXI only).
    AWContainerType m_NCAWQueue;
    /// Data type of AXI data write data.
    typedef std::pair<TData, typename Payload<TData>::write_strobe_type> WContainerDataType;
    /// Container type for AXI data write data.
    typedef std::queue<WContainerDataType> WContainerType;
    /// Queue of non-cacheable data write requests (AXI only).
    WContainerType m_NCWQueue;
    /// Index of last accessed line.
    Index m_LastIndexUsed;
    /// Flags whether the last index used is valid.
    bool m_IsLastIndexUsedValid;
    /// Index of the last stored cache line.
    Index m_LastSavedIndex;
    /// Way of the last stores cache line.
    Index m_LastSavedWay;
    /// (Flush all) Flags whether the penultimate line in flushed set is dirty.
    bool m_PenultimateLineDirty = false;
    /// (Flush all) Flags whether the m_PenultimateLineDirty has been set.
    bool m_PenultimateLineDirtySet = false;
    /// (Flush all) Flags whether the last line in flushed set is dirty.
    bool m_LastLineDirty = false;
    /// Cache operation data.
    codasip_address_t m_CacheOperationData = 0;
    /// Cache operation data ready flag.
    bool m_CacheOperationDataReady = false;
    /// (Verification API) Flags whether new cache line was saved to cache.
    bool m_NewCacheLineSaved;
    /// (Narrow master only) Container for target words that forms a single cache word.
    TargetWordsPerCacheWordContainer m_TargetWords;
    /// (Invalidate address) Contains current HxData value on slave interface.
    Data m_HxData;
    /// (AXI4) Flag for non-cacheable read on narrow target.
    bool m_IsNonCacheableNarrowTargetReadSuccessful = true;
    /// (AXI4) Flag that signifies the first cycle of NC request.
    bool m_FirstCycleOfNonCacheableRequest = false;
    /// Way that should be evicted if eviction is needed.
    Index m_ReplaceWay = 0;
    bool m_IsRequestAccepted = false;
    Payload<Data> m_PostponedRequest;
    bool m_IsRequestPostponed = false;
    /* End of CacheInterface private */
};   // class CacheInterface

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE
CacheInterface<T, M, CParams>::CacheInterface(const std::string& name, const Uid uid, M& cacheCore)
  : AhbLiteInitiatorInterface<T>(name, uid)
  , CacheRequestType(cacheCore)
  , Payload<TData>()
  , m_Id(uid)
  , m_NextState(STATE_IDLE)
  , m_FSMstate(STATE_IDLE)
  , m_NextResponse(CP_AHB_OKAY)
  , m_NextReady(CP_AHB_READY)
  , m_PreventRespReset(false)
  , m_EvictDelay(true)
  , m_IA(false)
  , m_HitCounter(0)
  , m_MissCounter(0)
  , m_LastIndexUsed(0)
  , m_IsLastIndexUsedValid(false)
  , m_LastSavedIndex(0)
  , m_LastSavedWay(0)
  , m_NewCacheLineSaved(false)
{
    DEBUG_CONDITION(this->m_Cache.GetLineSize() >= TARGET_BYTES_PER_WORD);
#ifdef _DEBUG_CACHE_INTERFACE
    m_StateNames.push_back("IDLE");
    m_StateNames.push_back("RESET");
    m_StateNames.push_back("RESET DONE");
    m_StateNames.push_back("Non-cachable region read finish - STATE_NCR_R_FINISH");
    m_StateNames.push_back("Non-cachable region request - STATE_NCR_REQUEST");
    m_StateNames.push_back("Non-cachable region read data AXI4 - STATE_NC_READ_DATA");
    m_StateNames.push_back("Non-cachable region write data AXI4 - STATE_NC_WRITE_DATA");
    m_StateNames.push_back("Non-cachable region write response AXI4 - STATE_NC_WRITE_RESPONSE");
    m_StateNames.push_back("Cache line read request - STATE_R_CL_REQUEST");
    m_StateNames.push_back("Cache line read finish - STATE_R_CL_FINISH");
    m_StateNames.push_back("Cache address invalidate");
    m_StateNames.push_back("Cache address invalidate done");
    m_StateNames.push_back("Cache line invalidate");
    m_StateNames.push_back("Cache line invalidate done");
    m_StateNames.push_back("Invalidate all");
    m_StateNames.push_back("Invalidate all done");
    m_StateNames.push_back("Non-cachable region write finish - STATE_NCR_W_FINISH");
    m_StateNames.push_back("Non-cachable region write response - STATE_NCR_W_RESP");
    m_StateNames.push_back("Non-cachable region write done - STATE_NCR_W_DONE");
    m_StateNames.push_back("Write hit - STATE_W_HIT");
    m_StateNames.push_back("Cache address flush");
    m_StateNames.push_back("Cache address flush done");
    m_StateNames.push_back("Cache line flush");
    m_StateNames.push_back("Cache line flush done");
    m_StateNames.push_back("Flush all");
    m_StateNames.push_back("Flush all done");
    m_StateNames.push_back("Skip read clock.");
    m_StateNames.push_back("Skip read clock. - STATE_R_SKIP_CYCLE_AXI4");
    m_StateNames.push_back("Skip clock.");
    m_StateNames.push_back("Skip clock. - STATE_SKIP_CYCLE_AXI4");
    m_StateNames.push_back("Send RAM response.");
    m_StateNames.push_back("Read request in DCACHE. - STATE_R_HIT");
    m_StateNames.push_back("Read current cache line from cache. - STATE_R_BUFFER_D");
    m_StateNames.push_back("Delay read current cache line from cache. - STATE_R_BUFFER_D_DELAYED");
    m_StateNames.push_back("Read miss done. - STATE_R_MISS_DONE");
    m_StateNames.push_back("Read miss error. - STATE_R_MISS_ERR");
    m_StateNames.push_back("Save cache line into cache. - STATE_SAVE_LINE");
    m_StateNames.push_back("Save cache line into cache. - STATE_SAVE_LINE_AXI4");
    m_StateNames.push_back("Write miss finish. - STATE_W_MISS_DONE");
    m_StateNames.push_back("Write-through request. - STATE_WT_REQUEST");
    m_StateNames.push_back("Write-through finish. - STATE_WT_FINISH");
    m_StateNames.push_back("Write-through response. - STATE_WT_RESP");
    m_StateNames.push_back("Write-through done. - STATE_WT_DONE");
    m_StateNames.push_back("Write hit delayed. - STATE_W_HIT_DELAYED");
    m_StateNames.push_back("Read miss response. - STATE_R_MISS_RESP");
    m_StateNames.push_back("Read miss error response. - STATE_R_MISS_ERR_RESP");
    m_StateNames.push_back("Cache invalidate address operation requested. - STATE_I_ADDR_REQ");
    m_StateNames.push_back("Cache invalidate line operation requested. - STATE_I_LINE_REQ");
    m_StateNames.push_back("Cache invalidate all operation requested. - STATE_I_ALL_REQ");
    m_StateNames.push_back("Cache flush address operation requested. - STATE_F_ADDR_REQ");
    m_StateNames.push_back("Cache flush line operation requested. - STATE_F_LINE_REQ");
    m_StateNames.push_back("Cache flush all operation requested. - STATE_F_ALL_REQ");

    //_DEBUG_LINE_OUTPUT_F((IS_DCACHE ? "DATA CACHE" : "INSTRUCTION CACHE") << " CONFIGURATION");
    //_DEBUG_LINE_OUTPUT_F("NUM WAYS: " << this->m_Cache.GetNumWays());
    //_DEBUG_LINE_OUTPUT_F("LINE SIZE: " << this->m_Cache.GetLineSize());
    //_DEBUG_LINE_OUTPUT_F("CACHE DATA BITS: " << CACHE_DATA_BITS);
    //_DEBUG_LINE_OUTPUT_F("TARGET DATA BITS: " << TARGET_DATA_BITS);
#endif
    m_CurrentRequest.reset(1);
    m_CurrentResponse.reset(1);
    CacheRequestType::Reset();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE CacheInterface<T, M, CParams>::~CacheInterface()
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Method used when flushing cache line and cache word is smaller than target word.
 *  \param  set Number of way.
 *  \param  index   Cacheline number.
 *  \param  offset  Offset within cacheline.
 *  \return Target word composed of several cache words.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::TData
CacheInterface<T, M, CParams>::GatherTargetWord(const Index set,
    const LineIndex index,
    const LineIndex offset)
{
    TData word = 0, cWord = 0;
    for (int i = 0; i < CACHE_WORDS_PER_TARGET_WORD; i++)
    {
        cWord = this->m_Cache.GetData(set, index, offset + i);
        if (ENDIANNESS == CP_LITTLE_ENDIAN)
        {
            word += LeftShift(cWord, i * CACHE_DATA_BITS);
        }
        else
        {
            word = LeftShift(word, CACHE_DATA_BITS);
            word |= cWord;
        }
    }
    return word;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief (IA) Evicts cache line.
 *  \param  address Evicted cache line address.
 *  \param  hprot   Eviction HPROT.
 *  \param  hmastlock   Eviction HMASTLOCK.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::EvictCacheLine(const codasip_address_t address,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const LineIndex index = GetIndexFromAddr(address);
    const Index way = this->m_Cache.GetReplaceWay(index);
    if (this->m_Cache.IsValid(way, index) && this->m_Cache.IsDirty(way, index))
    {
        WriteLine(way, address, hprot, hmastlock);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  (IA) Stores fetched line in the cache.
 *  \param  hprot   HPROT value for the eventual eviction.
 *  \param  hmastlock   HMASTLOCK value for the eventual eviction.
 *  \returns    A cache way in which the fetched line is stored.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::SetIndex
CacheInterface<T, M, CParams>::WriteLoadedLine(const uint8_t hprot, const uint8_t hmastlock)
{
    const LineIndex tag = GetTagFromAddr(CacheRequestType::GetAddr());
    const LineIndex index = GetIndexFromAddr(CacheRequestType::GetAddr());
    const Index way = this->m_Cache.GetReplaceWay(index);

    EvictCacheLine(CacheRequestType::GetAddr(), hprot, hmastlock);
    SaveCacheLineIntoCache(CacheRequestType::GetCacheLine(), way, index, tag);

    if (!m_RegistersInterface->IsWriteThroughEnabled() && CacheRequestType::GetCommand() == CP_CMD_WRITE)
    {
        this->m_Cache.SetDirty(way, index);
    }

    return way;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  (IA) Reads cache line from target and saves it to cache.
 *  \param  addr    Address that caused cache miss.
 *  \param  hprot   HPROT value for the line fill requests.
 *  \param  hmastlock   HMASTLOCK value for the line fill requests.
 */
template<class T, class M, class CParams>
CACHE_INLINE AHBResponseCode CacheInterface<T, M, CParams>::ReadLine(const codasip_address_t addr,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DEBUG_CONDITION(MASTER_INTERFACE_PROTOCOL != CP_PROTOCOL_AXI);

    AHBResponseCode result = CP_AHB_OKAY;
    _DEBUG_LINE_OUTPUT_F("addr = h'" << std::hex << addr << std::dec);
    TData targetData = 0;
    if (BURST_ENABLED && MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
    {
        this->m_Cache.TargetStartBurst(this->m_Cache.GetTargetBurstMode());
    }
    // cache words will be read as sub-blocks of target word, one target word at the time
    if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
    {
        CacheRequestType::SetNCAddr(addr / TARGET_BYTES_PER_WORD * TARGET_BYTES_PER_WORD);
        for (int j = 0; j < this->m_Cache.GetWordsPerLine(); j += CACHE_WORDS_PER_TARGET_WORD)
        {
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE)
            {
                TargetWordResponsePair targetDataResponsePair = this->m_Cache.TargetRead(
                    CacheRequestType::GetNCAddr(),
                    TARGET_BYTES_PER_WORD,
                    hprot,
                    hmastlock);
                if (!IsOkay(targetDataResponsePair.second))
                {
                    return CP_AHB_ERROR;
                }
                targetData = targetDataResponsePair.first;
            }
            else
            {   // AHB3-LITE
                targetData = this->m_Cache.TargetRead(CacheRequestType::GetNCAddr(),
                    TARGET_BYTES_PER_WORD,
                    result,
                    hprot,
                    hmastlock);
                DEBUG_CONDITION(this->m_Cache.TargetLastAHBReadyCode() == CP_AHB_READY);
                if (result != CP_AHB_OKAY)
                {
                    this->m_Cache.TargetStopBurst();
                    return CP_AHB_ERROR;
                }
            }
            for (int i = 0; i < CACHE_WORDS_PER_TARGET_WORD; i++)
            {
                CacheRequestType::PushWord(
                    Unaligned<TData, BYTE_BITS, TARGET_BYTES_PER_WORD>::template read<ENDIANNESS>(
                        &targetData,
                        0,
                        i * BYTES_PER_WORD,
                        BYTES_PER_WORD));
            }
            const auto address = CacheRequestType::GetNCAddr();
            CacheRequestType::NCAddrIncWordWrap();
            if (BURST_ENABLED && this->m_Cache.GetTargetBurstMode() == CP_AHB_INCR &&
                address > CacheRequestType::GetNCAddr())
            {   // if bursts are enable on AHB, the burst mode is incremental, and the next address is lower than current,
                // we have to restart burst
                this->m_Cache.TargetStopBurst();
                this->m_Cache.TargetStartBurst(this->m_Cache.GetTargetBurstMode());
            }
        }
    }
    // target words will be concatenated to form cache word
    else
    {
        CacheRequestType::SetNCAddr(addr);
        for (int j = 0; j < this->m_Cache.GetWordsPerLine(); j++)
        {
            for (int i = 0; i < TARGET_WORDS_PER_CACHE_WORD; i++)
            {
                targetData = this->m_Cache.TargetRead(CacheRequestType::GetNCAddr(),
                    TARGET_BYTES_PER_WORD,
                    result,
                    hprot,
                    hmastlock);
                DEBUG_CONDITION(this->m_Cache.TargetLastAHBReadyCode() == CP_AHB_READY);
                if (result != CP_AHB_OKAY)
                {
                    if (BURST_ENABLED && MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
                    {
                        this->m_Cache.TargetStopBurst();
                    }
                    return CP_AHB_ERROR;
                }
                CacheRequestType::IncCounter();
                CacheRequestType::NCAddrIncWordWrap();
                CacheRequestType::ConcatenateCacheData(targetData);
            }
            CacheRequestType::PushCacheData();
        }
    }
    if (BURST_ENABLED && MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
    {
        this->m_Cache.TargetStopBurst();
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  (AXI) Reads cache line from target.
 *  \param  startAddressCacheAligned    Cache word aligned address that was requested.
 *  \return Read cache line words with their responses.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CacheWordResponsePairContainer
CacheInterface<T, M, CParams>::ReadLineAxi(const codasip_address_t startAddressCacheAligned,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DEBUG_CONDITION(MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI);
    const AXIBurstType burstType = this->m_Cache.GetAXITargetBurstType();
    DEBUG_CONDITION(burstType == CP_AXI_BURST_WRAP || burstType == CP_AXI_BURST_INCR);

    const codasip_address_t startAddressTargetAligned = detail::AlignAddressToWordAddress(
        startAddressCacheAligned,
        TARGET_BYTES_PER_WORD);
    if (burstType == CP_AXI_BURST_WRAP)
    {
        return ReadLineUsingWrappingBurst(startAddressTargetAligned, hprot, hmastlock);
    }
    return ReadLineUsingIncrementingBurst(startAddressTargetAligned, hprot, hmastlock);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Reads cache line using wrapping burst.
 *  \param  startAddressTargetAligned   A target word aligned address.
 *  \returns    A cache word-response pair container.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CacheWordResponsePairContainer
CacheInterface<T, M, CParams>::ReadLineUsingWrappingBurst(
    const codasip_address_t startAddressTargetAligned,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DEBUG_CONDITION(
        this->m_Cache.GetAXITargetBurstLength() == this->m_Cache.GetTargetWordsPerLine() - 1);

    CacheWordResponsePairContainer result = {};
    TargetWordResponsePairContainer targetWords = ReadTargetWords(startAddressTargetAligned,
        this->m_Cache.GetTargetWordsPerLine(),
        hprot,
        hmastlock);
    result = TransformTargetWordsToCacheWords<CacheWordResponsePairContainer>(targetWords);
    UnwrapCacheLine(result, startAddressTargetAligned);
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Reads cache words from target.
 *  \param  startAddressTargetAligned   A target word aligned address of a first target word.
 *  \param  endAddressTargetAligned A target word aligned address of a last target word.
 *  \returns    A cache word-response pair container.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CacheWordResponsePairContainer
CacheInterface<T, M, CParams>::ReadCacheWordsFromTarget(const codasip_address_t startAddressTargetAligned,
    const codasip_address_t endAddressTargetAligned,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const Index numTargetWordsInRange = (endAddressTargetAligned - startAddressTargetAligned) /
        TARGET_BYTES_PER_WORD;
    if (numTargetWordsInRange == 0)
    {
        return {};
    }
    const Index numTargetWordsPerFullBurst = std::min(numTargetWordsInRange,
        static_cast<Index>(this->m_Cache.GetAXITargetBurstLength()) + 1);
    const Index numBursts = static_cast<Index>(
        ceil(numTargetWordsInRange / numTargetWordsPerFullBurst));
    const Index numFullBursts = static_cast<Index>(
        floor(numTargetWordsInRange / numTargetWordsPerFullBurst));
    const Index numShortBursts = numBursts - numFullBursts;
    const Index numTargetWordsPerShortBurst = numTargetWordsInRange -
        (numFullBursts * numTargetWordsPerFullBurst);

    TargetWordResponsePairContainer targetWords = {};
    for (Index i = 0; i < numFullBursts; ++i)
    {
        TargetWordResponsePairContainer tmp = ReadTargetWords(
            startAddressTargetAligned + i * numTargetWordsPerFullBurst * TARGET_BYTES_PER_WORD,
            numTargetWordsPerFullBurst,
            hprot,
            hmastlock);
        targetWords.insert(targetWords.end(), tmp.begin(), tmp.end());
        if (!AllOkay(tmp))
        {
            return TransformTargetWordsToCacheWords<CacheWordResponsePairContainer>(targetWords);
        }
    }

    for (Index i = 0; i < numShortBursts; ++i)
    {
        TargetWordResponsePairContainer tmp = ReadTargetWords(startAddressTargetAligned +
                (numFullBursts * numTargetWordsPerFullBurst + i * numTargetWordsPerShortBurst) *
                    TARGET_BYTES_PER_WORD,
            numTargetWordsPerShortBurst,
            hprot,
            hmastlock);
        targetWords.insert(targetWords.end(), tmp.begin(), tmp.end());
        if (!AllOkay(tmp))
        {
            return TransformTargetWordsToCacheWords<CacheWordResponsePairContainer>(targetWords);
        }
    }

    return TransformTargetWordsToCacheWords<CacheWordResponsePairContainer>(targetWords);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Transforms target word-response pair container to cache word-response pair container.
 *  \param cacheLine    A target word-response pair container.
 *  \returns    A container of cache word-response pair container.
 */
template<class T, class M, class CParams>
template<typename CacheWordContainer, typename TargetWordContainer>
CACHE_INLINE CacheWordContainer CacheInterface<T, M, CParams>::TransformTargetWordsToCacheWords(
    const TargetWordContainer& targetWords) const
{
    if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
    {
        return SplitTargetWordsToCacheWords(targetWords);
    }
    return ConcatenateTargetWordsToCacheWords(targetWords);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Reads words from target.
 *  \param  startAddressTargetAligned   A target word aligned address.
 *  \param  numTargetWords  A number of target words to read.
 *  \returns    A target word-response pair container.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::TargetWordResponsePairContainer
CacheInterface<T, M, CParams>::ReadTargetWords(const codasip_address_t startAddressTargetAligned,
    const Index numTargetWords,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    TargetWordResponsePairContainer result = {};

    DEBUG_CONDITION(numTargetWords - 1 >= 0 && numTargetWords - 1 <= 0xFF);
    this->m_Cache.TargetStartBurst(this->m_Cache.GetAXITargetBurstType(),
        startAddressTargetAligned,
        static_cast<uint8_t>(numTargetWords - 1));
    for (Index i = 0; i < numTargetWords; ++i)
    {
        result.emplace_back(
            this->m_Cache.TargetRead(startAddressTargetAligned, TARGET_BYTES_PER_WORD, hprot, hmastlock));
    }
    this->m_Cache.TargetStopBurst();

    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Reads words from target non cacheable.
 *  \param  startAddressTargetAligned   A target word aligned address.
 *  \param  numTargetWords  A number of target words to read.
 *  \returns    A target word-response pair container.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::TargetWordResponsePairContainer
CacheInterface<T, M, CParams>::ReadTargetWordsNonCacheable(
    const codasip_address_t startAddressTargetAligned,
    const Index numTargetWords,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    TargetWordResponsePairContainer result = {};

    DEBUG_CONDITION(numTargetWords - 1 >= 0 && numTargetWords - 1 <= 0xFF);
    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR,
        startAddressTargetAligned,
        static_cast<uint8_t>(numTargetWords - 1));
    for (Index i = 0; i < numTargetWords; ++i)
    {
        result.emplace_back(this->m_Cache.TargetNonCacheableRead(startAddressTargetAligned,
            TARGET_BYTES_PER_WORD,
            hprot,
            hmastlock));
    }
    this->m_Cache.TargetStopBurst();

    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Splits target words to cache words.
 *  \param  targetWordResponsePairs A target word-response pair container.
 *  \returns    A cache word-response pair container.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CacheWordResponsePairContainer
CacheInterface<T, M, CParams>::SplitTargetWordsToCacheWords(
    const TargetWordResponsePairContainer& targetWordResponsePairs) const
{
    CacheWordResponsePairContainer result = {};
    for (const auto& targetWordResponsePair : targetWordResponsePairs)
    {
        for (Index i = 0; i < CACHE_WORDS_PER_TARGET_WORD; ++i)
        {
            const CData cacheWord =
                Unaligned<TData, BYTE_BITS, TARGET_BYTES_PER_WORD>::template read<ENDIANNESS>(
                    &targetWordResponsePair.first,
                    0,
                    i * BYTES_PER_WORD,
                    BYTES_PER_WORD);
            result.emplace_back(std::make_pair(cacheWord, targetWordResponsePair.second));
        }
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Concatenates target words to cache words.
 *  \param  targetWordResponsePairs A target word-response pair container.
 *  \returns    A cache word-response pair container.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CacheWordResponsePairContainer
CacheInterface<T, M, CParams>::ConcatenateTargetWordsToCacheWords(
    const TargetWordResponsePairContainer& targetWordResponsePairs) const
{
    CacheWordResponsePairContainer result = {};
    for (size_t i = 0; i < targetWordResponsePairs.size(); i += TARGET_WORDS_PER_CACHE_WORD)
    {
        CData cacheWord = 0;
        AXIResponseCode response = CP_AXI_OKAY;
        for (size_t j = 0; j < TARGET_WORDS_PER_CACHE_WORD; ++j)
        {
            CData tmp = targetWordResponsePairs[i + j].first;
            if (ENDIANNESS == CP_LITTLE_ENDIAN)
            {
                cacheWord |= LeftShift(tmp, j * TARGET_DATA_BITS);
            }
            else
            {
                cacheWord |= LeftShift(tmp, CACHE_DATA_BITS - (TARGET_DATA_BITS * (j + 1)));
            }
            response = targetWordResponsePairs[i + j].second != CP_AXI_OKAY ? CP_AXI_SLVERR : response;
        }
        result.emplace_back(std::make_pair(cacheWord, response));
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Unwraps cache line.
 *  \param  cacheLine   A wrapped cache line.
 *  \param  startAddress    An address of a first cache word of a wrapped cache line.
 */
template<class T, class M, class CParams>
template<class Container>
CACHE_INLINE void CacheInterface<T, M, CParams>::UnwrapCacheLine(Container& cacheLine,
    const codasip_address_t startAddress) const
{
    const codasip_address_t cacheLineStartAddress = GetCacheLineStartAddress(startAddress);
    const Index cacheLineStartIndex = this->m_Cache.GetWordsPerLine() -
        ((startAddress - cacheLineStartAddress) / BYTES_PER_WORD);
    std::rotate(cacheLine.begin(), cacheLine.begin() + cacheLineStartIndex, cacheLine.end());
}

template<class T, class M, class CParams>
template<class Container>
CACHE_INLINE void
CacheInterface<T, M, CParams>::WrapCacheLine(Container& cacheLine, const codasip_address_t address) const
{
    const codasip_address_t cacheLineStartAddress = GetCacheLineStartAddress(address);
    const Index cacheLineStartIndex = (address - cacheLineStartAddress) / BYTES_PER_WORD;
    std::rotate(cacheLine.begin(), cacheLine.begin() + cacheLineStartIndex, cacheLine.end());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Returns a start address of a cache line that contains given address.
 *  \param  address An address of a cache line word.
 */
template<class T, class M, class CParams>
CACHE_INLINE codasip_address_t CacheInterface<T, M, CParams>::GetCacheLineStartAddress(
    const codasip_address_t address) const
{
    return this->m_Cache.GetCacheLineStartAddress(address);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Returns an end address of a cache line that contains given address.
 *  \param  address An address of a cache line word.
 */
template<class T, class M, class CParams>
CACHE_INLINE codasip_address_t CacheInterface<T, M, CParams>::GetCacheLineEndAddress(
    const codasip_address_t address) const
{
    return GetCacheLineStartAddress(address) + this->m_Cache.GetLineSize();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Returns an index of a cache word within a cache line.
 *  \param  address An address of a cache word.
 */
template<class T, class M, class CParams>
CACHE_INLINE Index CacheInterface<T, M, CParams>::GetCacheWordCacheLineIndex(
    const codasip_address_t address) const
{
    return (address - GetCacheLineStartAddress(address)) / BYTES_PER_WORD;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Reads cache line using incrementing burst.
 *  \param  startAddressTargetAligned   A target word aligned address.
 *  \returns    A cache word-response pair container.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CacheWordResponsePairContainer
CacheInterface<T, M, CParams>::ReadLineUsingIncrementingBurst(
    const codasip_address_t startAddressTargetAligned,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const codasip_address_t cacheLineEndAddress = GetCacheLineEndAddress(startAddressTargetAligned);
    const codasip_address_t cacheLineStartAddress = GetCacheLineStartAddress(startAddressTargetAligned);

    CacheWordResponsePairContainer tail =
        ReadCacheWordsFromTarget(startAddressTargetAligned, cacheLineEndAddress, hprot, hmastlock);
    CacheWordResponsePairContainer head = ReadCacheWordsFromTarget(cacheLineStartAddress,
        startAddressTargetAligned,
        hprot,
        hmastlock);

    head.insert(head.end(), tail.begin(), tail.end());
    return head;
}
/**
 *  \brief  Decides whether the axi response code indicates success or failure.
 */
template<class T, class M, class CParams>
CACHE_INLINE bool CacheInterface<T, M, CParams>::IsOkay(const AXIResponseCode resp) const
{
    return resp == CP_AXI_OKAY || resp == CP_AXI_EXOKAY;
}
/**
 *  \brief  Decides whether all axi response codes in a given container indicate success or not.
 *  \param  wordResponsePairs   A container of word-response pairs.
 *  \tparam WordDataType    A word data type.
 *  \returns    True if all responses in a container indicate success, false otherwise.
 */
template<class T, class M, class CParams>
template<typename WordDataType>
CACHE_INLINE bool CacheInterface<T, M, CParams>::AllOkay(
    const WordResponsePairContainer<WordDataType>& wordResponsePairs) const
{
    return std::all_of(wordResponsePairs.begin(),
        wordResponsePairs.end(),
        [this](const WordResponsePair<WordDataType>& a)
        {
            return this->IsOkay(a.second);
        });
}
/**
 *  \brief  Transforms a contanier of word-response pairs to a container of words.
 *  \param  wordsWithResponses  A container of word-response pairs.
 *  \returns    A container of words.
 */
template<class T, class M, class CParams>
template<typename WordDataType>
CACHE_INLINE typename CacheInterface<T, M, CParams>::template WordContainer<WordDataType>
CacheInterface<T, M, CParams>::StripResponses(
    const WordResponsePairContainer<WordDataType>& wordsWithResponses) const
{
    WordContainer<WordDataType> result;
    std::transform(wordsWithResponses.begin(),
        wordsWithResponses.end(),
        std::back_inserter(result),
        [](const WordResponsePair<WordDataType>& a)
        {
            return a.first;
        });
    return result;
}
/**
 *  \brief  Writes cache line to cache.
 *  \param  address Cache line address.
 *  \param  cacheLine   Cache line data.
 */
template<class T, class M, class CParams>
CACHE_INLINE Index CacheInterface<T, M, CParams>::WriteCacheLineToCache(const codasip_address_t address,
    const CLine& cacheLine,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const LineIndex index = GetIndexFromAddr(address);
    const Index set = this->m_Cache.GetReplaceWay(index);
    EvictCacheLineAxi(set, index, hprot, hmastlock);
    const Tag tag = GetTagFromAddr(address);
    SaveCacheLineIntoCache(cacheLine, set, index, tag);
    return set;
}
/**
 *  \brief  Evicts cache line from cache.
 *  \param  set A set of evicted cache line.
 *  \param  index   An index of evicted cache line.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::EvictCacheLineAxi(const Index set,
    const LineIndex index,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (!this->m_Cache.IsValid(set, index) || !this->m_Cache.IsDirty(set, index))
    {
        return;
    }
    const Tag tag = this->m_Cache.GetTag(set, index);
    const codasip_address_t address = (tag << this->m_Cache.GetTagShift()) +
        (index << this->m_Cache.GetIndexShift());
    WriteCacheLineToTarget(address, this->m_Cache.GetCacheLine(set, index), hprot, hmastlock);
    this->m_Cache.SetClear(set, index);
}
/**
 *  \brief  Writes cache line to target.
 *  \param address  A target address.
 *  \param  cacheLine   A cache line that is to be written.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::WriteCacheLineToTarget(const codasip_address_t address,
    const CLine& cacheLine,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DEBUG_CONDITION(GetCacheLineStartAddress(address) == address);   // address is cache line aligned
    const auto targetWords = detail::TransformCacheWordsToTargetWords<TData, ENDIANNESS>(cacheLine);
    WriteTargetLine(address, targetWords, hprot, hmastlock);
}
/**
 *  \brief  Writes target line to target.
 *  \param  address A target address.
 *  \param  targetLine  A target line that is to be written.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::WriteTargetLine(const codasip_address_t address,
    const TLine& targetLine,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    return WriteTargetLineUsingIncrementingBurst(address, targetLine, hprot, hmastlock);
}
/**
 *  \brief  Writes target line using incrementing burst.
 *  \param  address A target address.
 *  \param  targetLine  A target line that is to be written.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::WriteTargetLineUsingIncrementingBurst(const codasip_address_t address,
    const TLine& targetLine,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const Index numTargetWords = targetLine.size();
    const Index numTargetWordsPerFullBurst = this->m_Cache.GetAXITargetBurstLength() + 1;
    const Index numBursts = static_cast<Index>(ceil(numTargetWords / numTargetWordsPerFullBurst));
    const Index numFullBursts = static_cast<Index>(floor(numTargetWords / numTargetWordsPerFullBurst));
    const Index numShortBursts = numBursts - numFullBursts;
    const Index numTargetWordsPerShortBurst = numTargetWords -
        (numFullBursts * numTargetWordsPerFullBurst);

    for (Index i = 0; i < numFullBursts; ++i)
    {
        const auto begin = targetLine.cbegin() + i * numTargetWordsPerFullBurst;
        const auto end = begin + numTargetWordsPerFullBurst;
        if (!IsOkay(WriteTargetWords(begin,
                end,
                address + i * numTargetWordsPerFullBurst * TARGET_BYTES_PER_WORD,
                hprot,
                hmastlock)))
        {
            return;
        }
    }

    for (Index i = 0; i < numShortBursts; ++i)
    {
        const auto begin = targetLine.cbegin() + numFullBursts * numTargetWordsPerFullBurst +
            i * numTargetWordsPerShortBurst;
        const auto end = begin + numTargetWordsPerShortBurst;
        if (!IsOkay(WriteTargetWords(begin,
                end,
                (address + numFullBursts * numTargetWordsPerFullBurst + i * numTargetWordsPerShortBurst) *
                    TARGET_BYTES_PER_WORD,
                hprot,
                hmastlock)))
        {
            return;
        }
    }
}
/**
 *  \brief  Writes target words to target.
 *  \param  begin   An iterator pointing to the begining of target words range.
 *  \param  end An iterator poinintg to the end of target words range.
 *  \param  startAddressTargetAligned   Burst address.
 */
template<class T, class M, class CParams>
AXIResponseCode
CacheInterface<T, M, CParams>::WriteTargetWords(const typename TLine::const_iterator& begin,
    const typename TLine::const_iterator& end,
    const codasip_address_t startAddressTargetAligned,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    AXIResponseCode result = CP_AXI_OKAY;

    const size_t numTargetWords = end - begin;
    DEBUG_CONDITION(numTargetWords - 1 >= 0 && numTargetWords - 1 <= 0xFF);
    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR,
        startAddressTargetAligned,
        static_cast<uint8_t>(numTargetWords - 1));
    for (auto i = begin; i < end; ++i)
    {
        this->m_Cache.TargetWrite(*i, startAddressTargetAligned, TARGET_BYTES_PER_WORD, result, hprot, hmastlock);
    }
    this->m_Cache.TargetStopBurst();

    return result;
}
/**
 *  \brief  Writes target words to target non-cacheable.
 *  \param  begin   An iterator pointing to the begining of target words range.
 *  \param  end An iterator poinintg to the end of target words range.
 *  \param  startAddressTargetAligned   Burst address.
 */
template<class T, class M, class CParams>
AXIResponseCode
CacheInterface<T, M, CParams>::WriteTargetWordsNonCacheable(const typename TLine::const_iterator& begin,
    const typename TLine::const_iterator& end,
    const codasip_address_t startAddressTargetAligned,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    AXIResponseCode result = CP_AXI_OKAY;

    const size_t numTargetWords = end - begin;
    DEBUG_CONDITION(numTargetWords - 1 >= 0 && numTargetWords - 1 <= 0xFF);
    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR,
        startAddressTargetAligned,
        static_cast<uint8_t>(numTargetWords - 1));
    for (auto i = begin; i < end; ++i)
    {
        this->m_Cache.TargetNonCacheableWrite(*i,
            startAddressTargetAligned,
            TARGET_BYTES_PER_WORD,
            result,
            hprot,
            hmastlock);
    }
    this->m_Cache.TargetStopBurst();

    return result;
}

template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::TargetWordResponsePair
CacheInterface<T, M, CParams>::ReadTargetWordNonCacheable(const Payload<CData>& p)
{
    TargetWordResponsePair result = {};

    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR, p.get_address(), 0);
    result = this->m_Cache.TargetNonCacheableRead(p.get_address(),
        p.get_bc(),
        p.get_ahb_hprot(),
        p.get_ahb_hmastlock());
    this->m_Cache.TargetStopBurst();

    return result;
}

template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::NonCacheableReadAxi(Payload<CData>& p)
{
    const codasip_address_t address = p.get_address();
    const Index bc = p.get_bc();

    DEBUG_CONDITION(bc <= TARGET_BYTES_PER_WORD || bc % TARGET_BYTES_PER_WORD == 0);
    const Index numTargetWords = bc <= TARGET_BYTES_PER_WORD ? 1 : bc / TARGET_BYTES_PER_WORD;
    if (numTargetWords <= 1)
    {
        TargetWordResponsePair targetWord = ReadTargetWordNonCacheable(p);
        if (IsOkay(targetWord.second))
        {
            p.set_data(static_cast<CData>(targetWord.first));
        }
        else
        {
            p.set_ahb_hresp(CP_AHB_ERROR);
        }
    }
    else
    {
        DEBUG_CONDITION(address % TARGET_BYTES_PER_WORD == 0);   // address is target word aligned
        TargetWordResponsePairContainer targetWords = ReadTargetWordsNonCacheable(address,
            numTargetWords,
            p.get_ahb_hprot(),
            p.get_ahb_hmastlock());
        if (AllOkay(targetWords))
        {
            CData cacheWord = 0;
            for (size_t i = 0; i < targetWords.size(); ++i)
            {
                CacheRequestType::DoConcatenateCacheData(cacheWord, targetWords[i].first, i);
            }
            p.set_data(cacheWord);
        }
        else
        {
            p.set_ahb_hresp(CP_AHB_ERROR);
        }
    }
}

template<class T, class M, class CParams>
AXIResponseCode CacheInterface<T, M, CParams>::WriteTargetWordNonCacheable(const TData& targetWord,
    const codasip_address_t address,
    const Index bc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    AXIResponseCode result = CP_AXI_OKAY;
    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR, address, 0);
    this->m_Cache.TargetNonCacheableWrite(targetWord, address, bc, result, hprot, hmastlock);
    this->m_Cache.TargetStopBurst();

    return result;
}

template<class T, class M, class CParams>
CACHE_INLINE AXIResponseCode CacheInterface<T, M, CParams>::NonCacheableWriteAxi(
    const Payload<CData>& p)
{
    const CData& data = p.get_data();
    const codasip_address_t address = p.get_address();
    const Index bc = p.get_bc();

    DEBUG_CONDITION(bc <= TARGET_BYTES_PER_WORD || bc % TARGET_BYTES_PER_WORD == 0);
    const Index numTargetWords = bc <= TARGET_BYTES_PER_WORD ? 1 : bc / TARGET_BYTES_PER_WORD;
    if (numTargetWords <= 1)
    {
        return WriteTargetWordNonCacheable(data,
            address,
            bc,
            p.get_ahb_hprot() & (~CP_AHB_CACHEABLE),
            p.get_ahb_hmastlock());
    }
    else
    {
        DEBUG_CONDITION(address % TARGET_BYTES_PER_WORD == 0);   // address is target word aligned
        auto targetWords = detail::TransformCacheWordsToTargetWords<TData, ENDIANNESS, CData>({data});
        if (ENDIANNESS == CP_BIG_ENDIAN)
        {
            targetWords = TLine(targetWords.end() - numTargetWords, targetWords.end());
        }
        return WriteTargetWordsNonCacheable(targetWords.begin(),
            targetWords.begin() + numTargetWords,
            address,
            p.get_ahb_hprot() & (~CP_AHB_CACHEABLE),
            p.get_ahb_hmastlock());
    }
}

template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::DwriteTargetWord(const Command cmd,
    const TData& targetWord,
    const codasip_address_t address,
    const Index bc)
{
    DEBUG_CONDITION(cmd == CP_CMD_DWRITE || cmd == CP_CMD_LOAD);
    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR, address, 0);
    if (cmd == CP_CMD_DWRITE)
    {
        this->m_Cache.TargetDwrite(targetWord, address, bc);
    }
    else
    {
        this->m_Cache.TargetLoad(targetWord, address, bc);
    }
    this->m_Cache.TargetStopBurst();
}

template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::DwriteTargetWords(const Command cmd,
    const typename TLine::const_iterator& begin,
    const typename TLine::const_iterator& end,
    const codasip_address_t startAddressTargetAligned)
{
    DEBUG_CONDITION(cmd == CP_CMD_DWRITE || cmd == CP_CMD_LOAD);
    const size_t numTargetWords = end - begin;
    DEBUG_CONDITION(numTargetWords - 1 >= 0 && numTargetWords - 1 <= 0xFF);
    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR,
        startAddressTargetAligned,
        static_cast<uint8_t>(numTargetWords - 1));
    for (auto i = begin; i < end; ++i)
    {
        if (cmd == CP_CMD_DWRITE)
        {
            this->m_Cache.TargetDwrite(*i, startAddressTargetAligned, TARGET_BYTES_PER_WORD);
        }
        else
        {
            this->m_Cache.TargetLoad(*i, startAddressTargetAligned, TARGET_BYTES_PER_WORD);
        }
    }
    this->m_Cache.TargetStopBurst();
}

template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::DwriteAxi(const Command cmd,
    const CData& data,
    const codasip_address_t address,
    const Index bc)
{
    DEBUG_CONDITION(bc <= TARGET_BYTES_PER_WORD || bc % TARGET_BYTES_PER_WORD == 0);
    const Index numTargetWords = bc <= TARGET_BYTES_PER_WORD ? 1 : bc / TARGET_BYTES_PER_WORD;
    if (numTargetWords <= 1)
    {
        DwriteTargetWord(cmd, data, address, bc);
    }
    else
    {
        DEBUG_CONDITION(address % TARGET_BYTES_PER_WORD == 0);   // address is target word aligned
        const auto targetWords = detail::TransformCacheWordsToTargetWords<TData, ENDIANNESS, CData>(
            {data});
        DwriteTargetWords(cmd, targetWords.begin(), targetWords.end(), address);
    }
}

template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::TData
CacheInterface<T, M, CParams>::DreadTargetWord(const codasip_address_t address, const Index bc)
{
    TData result = 0;

    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR, address, 0);
    result = this->m_Cache.TargetDread(address, bc);
    this->m_Cache.TargetStopBurst();

    return result;
}

template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::TLine
CacheInterface<T, M, CParams>::DreadTargetWords(const codasip_address_t address,
    const Index numTargetWords)
{
    TLine result = {};

    DEBUG_CONDITION(numTargetWords - 1 >= 0 && numTargetWords - 1 <= 0xFF);
    this->m_Cache.TargetStartBurst(CP_AXI_BURST_INCR, address, static_cast<uint8_t>(numTargetWords - 1));
    for (Index i = 0; i < numTargetWords; ++i)
    {
        result.emplace_back(this->m_Cache.TargetDread(address, TARGET_BYTES_PER_WORD));
    }
    this->m_Cache.TargetStopBurst();

    return result;
}

template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CData
CacheInterface<T, M, CParams>::DreadAxi(const codasip_address_t address, const Index bc)
{
    DEBUG_CONDITION(bc <= TARGET_BYTES_PER_WORD || bc % TARGET_BYTES_PER_WORD == 0);
    const Index numTargetWords = bc <= TARGET_BYTES_PER_WORD ? 1 : bc / TARGET_BYTES_PER_WORD;
    if (numTargetWords <= 1)
    {
        return static_cast<CData>(DreadTargetWord(address, bc));
    }
    else
    {
        DEBUG_CONDITION(address % TARGET_BYTES_PER_WORD == 0);   // address is target word aligned
        TLine targetWords = DreadTargetWords(address, numTargetWords);
        CData cacheWord = 0;
        for (size_t i = 0; i < targetWords.size(); ++i)
        {
            CacheRequestType::DoConcatenateCacheData(cacheWord, targetWords[i], i);
        }
        return cacheWord;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Writes cacheline into target.
 *  \param  set Cache way that needs to be written.
 *  \param  addr    Address that caused cache miss.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::WriteLine(const Index set,
    const codasip_address_t addr,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    _DEBUG_LINE_OUTPUT_F("set '" << set << ", addr = h'" << std::hex << addr << " )" << std::dec);
    const LineIndex index = GetIndexFromAddr(addr);
    const LineIndex tag = this->m_Cache.GetTag(set, index);
    codasip_address_t cacheLineAddr = (tag << this->m_Cache.GetTagShift()) +
        (index << this->m_Cache.GetIndexShift());
    Data cacheData = 0;
    TData targetData = 0;
    if (BURST_ENABLED)
    {
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
        {
            this->m_Cache.TargetStartBurst(this->m_Cache.GetTargetBurstMode());
        }
    }
    for (int i = 0; i < this->m_Cache.GetWordsPerLine(); i++)
    {
        // cache word wider than target word, writing subblocks of cache word
        if (TARGET_DATA_BITS < CACHE_DATA_BITS)
        {
            cacheData = this->m_Cache.GetData(set, index, i);
            for (int j = 0; j < TARGET_WORDS_PER_CACHE_WORD; j++)
            {
                targetData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(
                    &cacheData,
                    0,
                    j * TARGET_BYTES_PER_WORD,
                    TARGET_BYTES_PER_WORD);
                this->m_Cache.TargetWrite(targetData, cacheLineAddr, TARGET_BYTES_PER_WORD, hprot, hmastlock);
                cacheLineAddr += TARGET_BYTES_PER_WORD;
            }
        }
        // cache word smaller than target word, writing cache words as target word subblocks
        else if (!((i + 1) % CACHE_WORDS_PER_TARGET_WORD))
        {
            targetData = GatherTargetWord(set,
                index,
                (i / CACHE_WORDS_PER_TARGET_WORD) * CACHE_WORDS_PER_TARGET_WORD);
            this->m_Cache.TargetWrite(targetData, cacheLineAddr, TARGET_BYTES_PER_WORD, hprot, hmastlock);
            cacheLineAddr += TARGET_BYTES_PER_WORD;
        }
    }
    if (BURST_ENABLED)
    {
        this->m_Cache.TargetStopBurst();
    }
    this->m_Cache.SetClear(set, index);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Reads data from cache.
 *  \param  p   Request payload.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::Read(Payload<Data>& p)
{
    p.set_ahb_hready(CP_AHB_READY);
    p.set_ahb_hresp(CP_AHB_OKAY);
    p.set_data(0);
    Index sbi = p.get_address() % CParams::BYTES_PER_WORD, sbc = p.get_bc();
    codasip_address_t addr = p.get_address() - sbi;
    TData targetData = 0;
    CacheRequestType::Reset();
    _DEBUG_LINE_OUTPUT_F(
        "addr = h'" << std::hex << addr << ", sbi = " << std::dec << sbi << ", sbc = " << sbc);
    // noncacheable region read -> read target
    if (!p.is_ahb_hprot_cacheable() || !CParams::IS_ENABLED)
    {
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
        {
            NonCacheableReadAxi(p);
        }
        else
        {
            Index bi = 0;
            Data cacheData = 0;
            const Index numTargetWords = sbc < TARGET_BYTES_PER_WORD ? 1 : sbc / TARGET_BYTES_PER_WORD;
            const Index bc = sbc < TARGET_BYTES_PER_WORD ? sbc : TARGET_BYTES_PER_WORD;
            const codasip_address_t endAddr = p.get_address() + numTargetWords * bc;
            for (codasip_address_t addr = p.get_address(); addr < endAddr; addr += bc)
            {
                AHBResponseCode resp = CP_AHB_OKAY;
                targetData =
                    this->m_Cache.TargetRead(addr, bc, resp, p.get_ahb_hprot(), p.get_ahb_hmastlock());
                DEBUG_CONDITION(this->m_Cache.TargetLastAHBReadyCode() == CP_AHB_READY);
                p.set_ahb_hresp(resp);
                if (resp != CP_AHB_OKAY)
                {
                    return;
                }
                CacheRequestType::DoConcatenateCacheData(cacheData, targetData, bi++);
            }
            p.set_data(cacheData);
        }
    }
    else
    {
        Index way;
        const LineIndex tag = GetTagFromAddr(addr);
        const LineIndex index = GetIndexFromAddr(addr);
        const LineIndex offset = GetOffsetFromAddr(addr);
        if (this->m_Cache.IsHit(tag, index, way))
        {
            m_HitCounter++;
            p.set_data(this->m_Cache.GetData(way, index, offset, sbi, sbc));
        }
        else
        {
            m_MissCounter++;
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
            {
                CacheWordResponsePairContainer cacheWordsWithResponses = ReadLineAxi(addr,
                    p.get_ahb_hprot(),
                    p.get_ahb_hmastlock());
                if (AllOkay(cacheWordsWithResponses))
                {
                    way = WriteCacheLineToCache(addr,
                        StripResponses(cacheWordsWithResponses),
                        p.get_ahb_hprot(),
                        p.get_ahb_hmastlock());
                }
                const Index requestedWordCacheLineIndex = GetCacheWordCacheLineIndex(addr);
                const auto requestedWordWithResponse = cacheWordsWithResponses[requestedWordCacheLineIndex];
                if (requestedWordWithResponse.second == CP_AXI_OKAY)
                {
                    p.set_data(Unaligned<CData, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(
                        &requestedWordWithResponse.first,
                        0,
                        sbi,
                        sbc));
                }
                else
                {
                    p.set_ahb_hresp(CP_AHB_ERROR);
                }
            }
            else
            {
                CacheRequestType::SetCmd(CP_CMD_READ);
                CacheRequestType::SetAddr(addr);
                CacheRequestType::SetOffset(offset);
                if (ReadLine(addr, p.get_ahb_hprot(), p.get_ahb_hmastlock()) == CP_AHB_ERROR)
                {
                    if (CacheRequestType::GetCacheLineWordsLoaded() >= 1)
                    {
                        p.set_data(CacheRequestType::GetCacheLineWord());
                    }
                    else
                    {
                        p.set_ahb_hresp(CP_AHB_ERROR);
                    }
                    // evict cache line after failed line fill
                    EvictCacheLine(addr, p.get_ahb_hprot(), p.get_ahb_hmastlock());
                    return;
                }
                way = WriteLoadedLine(p.get_ahb_hprot(), p.get_ahb_hmastlock());
                p.set_data(this->m_Cache.GetData(way, index, offset, sbi, sbc));
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Write data to cache
 *  \param  p   Request payload.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::Write(Payload<Data>& p)
{
    p.set_ahb_hready(CP_AHB_READY);
    Index sbi = p.get_address() % CParams::BYTES_PER_WORD, sbc = p.get_bc();
    Data data = p.get_data();
    codasip_address_t addr = p.get_address() - sbi;
    CacheRequestType::Reset();
    _DEBUG_LINE_OUTPUT_F("data = h'" << std::hex << data << ", addr = h'" << std::hex << addr
                                     << ", sbi = " << std::dec << sbi << ", sbc = " << sbc);
    // noncacheable address
    if (!p.is_ahb_hprot_cacheable() || !CParams::IS_ENABLED)
    {
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
        {
            if (!IsOkay(NonCacheableWriteAxi(p)))
            {
                p.set_ahb_hresp(CP_AHB_ERROR);
                return;
            }
        }
        else
        {
            DoTargetWrite(CP_CMD_WRITE, data, p.get_address(), sbc, p.get_ahb_hprot(), p.get_ahb_hmastlock());
            DEBUG_CONDITION(this->m_Cache.TargetLastAHBReadyCode() == CP_AHB_READY);
            if (this->m_Cache.TargetLastAHBResponseCode() != CP_AHB_OKAY)
            {
                p.set_ahb_hresp(CP_AHB_ERROR);
                return;
            }
        }
    }
    else
    {
        Index way;
        const LineIndex tag = GetTagFromAddr(addr);
        const LineIndex index = GetIndexFromAddr(addr);
        const LineIndex offset = GetOffsetFromAddr(addr);
        CacheRequestType::SetCmd(CP_CMD_WRITE);
        CacheRequestType::SetAddr(addr);
        CacheRequestType::SetOffset(offset);
        if (this->m_Cache.IsHit(tag, index, way))
        {   // hit
            m_HitCounter++;
        }
        else
        {   // miss
            m_MissCounter++;
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
            {
                CacheWordResponsePairContainer cacheWordsWithResponses = ReadLineAxi(addr,
                    p.get_ahb_hprot(),
                    p.get_ahb_hmastlock());
                if (AllOkay(cacheWordsWithResponses))
                {
                    way = WriteCacheLineToCache(addr,
                        StripResponses(cacheWordsWithResponses),
                        p.get_ahb_hprot(),
                        p.get_ahb_hmastlock());
                }
                else
                {
                    p.set_ahb_hresp(CP_AHB_ERROR);
                    return;
                }
            }
            else
            {
                if (ReadLine(addr, p.get_ahb_hprot(), p.get_ahb_hmastlock()) == CP_AHB_ERROR)
                {
                    p.set_ahb_hresp(CP_AHB_ERROR);
                    // evict cache line after failed line fill
                    EvictCacheLine(addr, p.get_ahb_hprot(), p.get_ahb_hmastlock());
                    return;
                }
                way = WriteLoadedLine(p.get_ahb_hprot(), p.get_ahb_hmastlock());
            }
        }

        UpdateCacheLineInCache(data, way, index, offset, sbi, sbc);

        if (m_RegistersInterface->IsWriteThroughEnabled())
        {
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
            {
                NonCacheableWriteAxi(p);
            }
            else
            {
                DoTargetWrite(CP_CMD_WRITE,
                    data,
                    p.get_address(),
                    sbc,
                    p.get_ahb_hprot(),
                    p.get_ahb_hmastlock());
            }
        }
    }
    p.set_ahb_hresp(CP_AHB_OKAY);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief       Debug read for debugger or profiler.
 *  \copydetails codasip::resources::AhbLiteInitiatorInterface::dread
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::Data
CacheInterface<T, M, CParams>::Dread(const Payload<Data>& p)
{
    const codasip_address_t addr = p.get_address();
    const Index sbc = p.get_bc();

    _DEBUG_LINE_OUTPUT_F("addr = h'" << std::hex << addr << ", sbc = " << sbc << std::dec);
    const LineIndex tag = GetTagFromAddr(addr);
    const LineIndex index = GetIndexFromAddr(addr);
    const LineIndex offset = GetOffsetFromAddr(addr);
    // aligned addresses and byte index
    const Index addrA = addr & (1 + (~BYTES_PER_WORD));
    const Index sbiA = (addr % BYTES_PER_WORD);
    // data present in cache -> read it from cache
    Index set;
    if (CParams::IS_ENABLED && this->m_Cache.IsHit(tag, index, set))
    {
        return this->m_Cache.GetData(set, index, offset, sbiA, sbc);
    }
    else
    {
        Data cacheData = 0;
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
        {
            cacheData = DreadAxi(addr, sbc);
        }
        else
        {
            TData targetData = 0;
            codasip_address_t ncAddr = addrA;
            // prepare the cache word (load from target)
            if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
            {
                for (Index i = 0; i < this->m_Cache.GetTargetWordAlign(); i++)
                {
                    CacheRequestType::ChangeNthBitToXinAddr(ncAddr, i, 0);
                }
                this->m_Cache.TargetDread(targetData, ncAddr, TARGET_BYTES_PER_WORD);
                cacheData = Unaligned<TData, BYTE_BITS, TARGET_BYTES_PER_WORD>::template read<ENDIANNESS>(
                    &targetData,
                    0,
                    0,
                    BYTES_PER_WORD);
            }
            else
            {
                for (Index i = 0; i < TARGET_WORDS_PER_CACHE_WORD; i++)
                {
                    this->m_Cache.TargetDread(targetData, ncAddr, TARGET_BYTES_PER_WORD);
                    CacheRequestType::DoConcatenateCacheData(cacheData, targetData, i);
                    ncAddr += TARGET_BYTES_PER_WORD;
                }
                cacheData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(
                    &cacheData,
                    0,
                    0,
                    BYTES_PER_WORD);
            }
            cacheData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(&cacheData,
                0,
                sbiA,
                sbc);
        }
        // check whether there is or not a write in the buffer,
        // cache is loading the whole cache line from upper memory during write miss
        // on a miss the CA cache acknowledges the write data, saves it into a buffer
        // and fetches the cache line in the background
        if ((CacheRequestType::GetCommand() == CP_CMD_WRITE) &&
            CacheRequestType::WriteDataReady() && (tag == CacheRequestType::GetTag()) &&
            (index == CacheRequestType::GetIndex()) && (offset == CacheRequestType::GetOffset()))
        {
            Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template write<ENDIANNESS>(&cacheData,
                CacheRequestType::GetCoreWriteData(),
                0,
                CacheRequestType::GetSbi(),
                CacheRequestType::GetSbc());
            cacheData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(&cacheData,
                0,
                sbiA,
                sbc);
        }
        return cacheData;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Load for program loader.
 *  \param  p   Payload with data.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::Load(const Payload<Data>& p)
{
    if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
    {
        DwriteAxi(p.get_command(), p.get_data(), p.get_address(), p.get_bc());
    }
    else
    {
        DoTargetWrite(p.get_command(),
            p.get_data(),
            p.get_address(),
            p.get_bc(),
            p.get_ahb_hprot(),
            p.get_ahb_hmastlock());
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Debug write for debugger or profiler.
 *  \param  p   Payload with data.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::Dwrite(const Payload<Data>& p)
{
    const Command cmd = p.get_command();
    const Data data = p.get_data();
    const codasip_address_t addr = p.get_address();
    const Index sbc = p.get_bc();

    _DEBUG_LINE_OUTPUT_F(
        "addr = h'" << std::hex << addr << ", sbc = " << sbc << ", data=0x" << data << std::dec);
    Index sbiA = addr % BYTES_PER_WORD;
    Index addrA = addr - sbiA;
    Index set;
    const LineIndex tag = GetTagFromAddr(addrA);
    const LineIndex index = GetIndexFromAddr(addrA);
    const LineIndex offset = GetOffsetFromAddr(addrA);
    if (CParams::IS_ENABLED && this->m_Cache.IsHit(tag, index, set))
    {
        UpdateCacheLineInCache(data, set, index, offset, sbiA, sbc);
        if (IS_ICACHE || m_RegistersInterface->IsWriteThroughEnabled())
        {   // always update target on I cache
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
            {
                DwriteAxi(cmd, data, addr, sbc);
            }
            else
            {
                DoTargetWrite(cmd, data, addr, sbc, p.get_ahb_hprot(), p.get_ahb_hmastlock());
            }
        }
    }
    else
    {
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
        {
            DwriteAxi(cmd, data, addr, sbc);
        }
        else
        {
            DoTargetWrite(cmd, data, addr, sbc, p.get_ahb_hprot(), p.get_ahb_hmastlock());
        }
    }

    // update word in currently loaded CA cache line
    const codasip_address_t cacheLineStartAddress = GetCacheLineStartAddress(
        CacheRequestType::GetAddr());
    const codasip_address_t cacheLineEndAddress = GetCacheLineEndAddress(CacheRequestType::GetAddr());
    const Index numCacheLineWordsFilled = GetNumCacheLineWordsFilled();
    if (addrA >= cacheLineStartAddress && addrA < cacheLineEndAddress && numCacheLineWordsFilled > 0)
    {
        // dwrite address is in currently loaded cache line range and some words are already loaded
        const LineIndex transformedOffset = (offset - CacheRequestType::GetOffset() +
                                                this->m_Cache.GetWordsPerLine()) %
            this->m_Cache.GetWordsPerLine();
        if (transformedOffset < numCacheLineWordsFilled)
        {   // dwrite address has already been loaded
            auto cacheLineWordsFilled = GetCacheLineWordsFilled();
            auto& cacheData = cacheLineWordsFilled[offset];
            Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template write<ENDIANNESS>(&cacheData,
                data,
                0,
                sbiA,
                sbc);
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE)
            {
                // wrap cache line so that the requested word is first
                WrapCacheLine(cacheLineWordsFilled, this->m_Cache.GetLineFillAddr());
                // transform to target words
                const auto targetLineWordsFilled =
                    detail::TransformCacheWordsToTargetWords<TData, ENDIANNESS>(
                        cacheLineWordsFilled.begin(),
                        cacheLineWordsFilled.begin() + this->m_Cache.GetNumCacheWordsFilledAxi());
                // set target words filled
                this->m_Cache.AssignLineFillDataAxi(targetLineWordsFilled.begin(),
                    targetLineWordsFilled.end());
            }
            else
            {
                CacheRequestType::SetCacheLineWord(cacheData, offset);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::ClearCounters()
{
    m_HitCounter = 0;
    m_MissCounter = 0;
    this->m_Cache.ResetMemoryErrorCount();
#ifdef _DEBUG_CACHE_INTERFACE
    m_ClockCycleCounter = 0;
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::DoCacheOperationIA(const codasip_address_t data,
    const codasip_address_t address,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (!CParams::IS_ENABLED)
    {
        return;
    }
    switch (m_RegistersInterface->GetCacheOperation(address))
    {
        case OP_NONE:
            break;
        case OP_D_INVALIDATE_ADDRESS:
        case OP_I_INVALIDATE_ADDRESS:
            InvalidateAddressIA(data);
            break;
        case OP_D_INVALIDATE_LINE:
        case OP_I_INVALIDATE_LINE:
            InvalidateLineIA(static_cast<Index>(data));
            break;
        case OP_D_INVALIDATE_ALL:
        case OP_I_INVALIDATE_ALL:
            InvalidateAllIA();
            break;
        case OP_D_FLUSH_ADDRESS:
            FlushAddressIA(data, hprot, hmastlock);
            break;
        case OP_D_FLUSH_LINE:
            FlushLineIA(static_cast<Index>(data), hprot, hmastlock);
            break;
        case OP_D_FLUSH_ALL:
            FlushAllIA(hprot, hmastlock);
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE bool
CacheInterface<T, M, CParams>::DoCacheOperationAddressCA(const codasip_address_t address,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (!CParams::IS_ENABLED)
    {
        return true;
    }
    if (IsBusy())
    {   // Cache is not ready yet.
        _DEBUG_LINE_OUTPUT("\t" + std::string(IS_ICACHE ? ("I ") : ("D ")) + "cache is busy");
        return false;
    }
    switch (m_RegistersInterface->GetCacheOperation(address))
    {
        case OP_NONE:
            m_NextState = STATE_IDLE;
            break;
        case OP_D_INVALIDATE_ADDRESS:
            m_NextState = STATE_I_ADDR_REQ;
            if (m_FSMstate == STATE_R_MISS_DONE && m_CacheOperationDataReady)
            {
                InvalidateAddressCA(m_CacheOperationData);
            }
            break;
        case OP_I_INVALIDATE_ADDRESS:
            m_NextState = STATE_I_ADDR_REQ;
            if (m_IsRequestAccepted)
            {
                m_PostponedRequest = m_CurrentRequest;
                m_IsRequestPostponed = true;
            }
            break;
        case OP_D_INVALIDATE_LINE:
            m_NextState = STATE_I_LINE_REQ;
            if (m_FSMstate == STATE_R_MISS_DONE && m_CacheOperationDataReady)
            {
                InvalidateLineCA(m_CacheOperationData);
            }
            break;
        case OP_I_INVALIDATE_LINE:
            m_NextState = STATE_I_LINE_REQ;
            if (m_IsRequestAccepted)
            {
                m_PostponedRequest = m_CurrentRequest;
                m_IsRequestPostponed = true;
            }
            break;
        case OP_D_INVALIDATE_ALL:
            m_NextState = STATE_I_ALL_REQ;
            if (m_FSMstate == STATE_R_MISS_DONE && m_CacheOperationDataReady)
            {
                InvalidateAllCA();
            }
            break;
        case OP_I_INVALIDATE_ALL:
            m_NextState = STATE_I_ALL_REQ;
            if (m_IsRequestAccepted)
            {
                m_PostponedRequest = m_CurrentRequest;
                m_IsRequestPostponed = true;
            }
            break;
        case OP_D_FLUSH_ADDRESS:
            m_NextState = STATE_F_ADDR_REQ;
            if (m_FSMstate == STATE_R_MISS_DONE && m_CacheOperationDataReady)
            {
                FlushAddressCA(m_CacheOperationData, hprot, hmastlock);
            }
            break;
        case OP_D_FLUSH_LINE:
            m_NextState = STATE_F_LINE_REQ;
            if (m_FSMstate == STATE_R_MISS_DONE && m_CacheOperationDataReady)
            {
                FlushLineCA(m_CacheOperationData, hprot, hmastlock);
            }
            break;
        case OP_D_FLUSH_ALL:
            m_NextState = STATE_F_ALL_REQ;
            if (m_FSMstate == STATE_R_MISS_DONE && m_CacheOperationDataReady)
            {
                FlushAllCA(hprot, hmastlock);
            }
            break;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE bool CacheInterface<T, M, CParams>::DoCacheOperationDataCA(const codasip_address_t data,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (!CParams::IS_ENABLED)
    {
        return true;
    }
    switch (m_FSMstate)
    {   // start cache operation that was requested in previous clock
        case STATE_I_ADDR_REQ:
            InvalidateAddressCA(data);
            break;
        case STATE_I_LINE_REQ:
            InvalidateLineCA(data);
            break;
        case STATE_I_ALL_REQ:
            InvalidateAllCA();
            break;
        case STATE_F_ADDR_REQ:
            FlushAddressCA(data, hprot, hmastlock);
            break;
        case STATE_F_LINE_REQ:
            FlushLineCA(data, hprot, hmastlock);
            break;
        case STATE_F_ALL_REQ:
            FlushAllCA(hprot, hmastlock);
            break;
        default:
            break;
    }
    return !IsBusy();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::InvalidateAddressIA(const codasip_address_t addr)
{
    Index way;
    const LineIndex tag = GetTagFromAddr(addr);
    const LineIndex index = GetIndexFromAddr(addr);
    if (this->m_Cache.IsHit(tag, index, way))
    {
        InvalidateCacheLine(way, index);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::InvalidateAddressCA(const codasip_address_t addr)
{
    CacheRequestType::SetTag(GetTagFromAddr(addr));
    CacheRequestType::SetIndex(GetIndexFromAddr(addr));
    m_CacheOperationDataReady = false;
    if (!(m_LastIndexUsed == GetIndexFromAddr(addr) && IsHit(addr)))
    {
        CacheRequestType::SetLatency(1);
    }
    m_NextState = STATE_I_ADDR;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::InvalidateLineIA(const Index index)
{
    if (this->m_Cache.GetLinesPerSet() == 1 && (index & 0x1) == 1)
    {
        return;
    }
    Index maskedIndex = index & (this->m_Cache.GetLinesPerSet() - 1);
    for (Index way = 0; way < this->m_Cache.GetNumWays(); way++)
    {
        InvalidateCacheLine(way, maskedIndex);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::InvalidateLineCA(const Index index)
{
    m_CacheOperationDataReady = false;
    Index maskedIndex = (this->m_Cache.GetLinesPerSet() == 1 && ((index & 0x1) == 1))
        ? index
        : (index & (this->m_Cache.GetLinesPerSet() - 1));
    CacheRequestType::SetIndex(maskedIndex);
    m_NextState = STATE_I_LINE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::InvalidateAllIA()
{
    for (LineIndex index = 0; index < this->m_Cache.GetLinesPerSet(); index++)
    {
        InvalidateLineIA(index);
    }
    CacheRequestType::SetInvalidateLoadedLine();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::InvalidateAllCA()
{
    CacheRequestType::ResetCounter();
    m_CacheOperationDataReady = false;
    if (m_LastIndexUsed != 0)
    {
        CacheRequestType::SetLatency(1);
    }
    m_NextState = STATE_I_ALL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::FlushAddressIA(const codasip_address_t address,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    Index set;
    const LineIndex tag = GetTagFromAddr(address);
    const LineIndex index = GetIndexFromAddr(address);
    if (this->m_Cache.IsHit(tag, index, set) && this->m_Cache.IsDirty(set, index))
    {
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
        {
            EvictCacheLineAxi(set, index, hprot, hmastlock);
        }
        else
        {
            WriteLine(set, address, hprot, hmastlock);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::FlushAddressCA(const codasip_address_t address,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    CacheRequestType::Reset();
    CacheRequestType::SetTag(GetTagFromAddr(address));
    CacheRequestType::SetIndex(GetIndexFromAddr(address));
    CacheRequestType::SetHprot(hprot);
    CacheRequestType::SetHmastlock(hmastlock);
    CacheRequestType::AlignNCAddr(this->m_Cache.GetIndexShift());
    m_CacheOperationDataReady = false;
    if (!(m_LastIndexUsed == GetIndexFromAddr(address) && IsHit(address)))
    {
        CacheRequestType::SetLatency(1);
    }
    m_NextState = STATE_F_ADDR;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  (IA) Flush cache line in all sets to master interface. Only effective in Dcache.
 *  \param  index   Line index.
 *  \param  hprot   Protection mode.
 *  \param  hmastlock   Master lock code.
 */
template<class T, class M, class CParams>
CACHE_INLINE void
CacheInterface<T, M, CParams>::FlushLineIA(const Index index, const uint8_t hprot, const uint8_t hmastlock)
{
    if (this->m_Cache.GetLinesPerSet() == 1 && (index & 0x1) == 1)
    {
        return;
    }
    Index maskedIndex = index & (this->m_Cache.GetLinesPerSet() - 1);
    for (Index set = 0; set < this->m_Cache.GetNumWays(); set++)
    {
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
        {
            EvictCacheLineAxi(set, maskedIndex, hprot, hmastlock);
        }
        else
        {
            if (this->m_Cache.IsValid(set, maskedIndex) && this->m_Cache.IsDirty(set, maskedIndex))
            {
                WriteLine(set,
                    (this->m_Cache.GetTag(set, maskedIndex) << this->m_Cache.GetTagShift()) +
                        (maskedIndex << this->m_Cache.GetIndexShift()),
                    hprot,
                    hmastlock);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void
CacheInterface<T, M, CParams>::FlushLineCA(const Index index, const uint8_t hprot, const uint8_t hmastlock)
{
    Index maskedIndex = (this->m_Cache.GetLinesPerSet() == 1 && ((index & 0x1) == 1))
        ? index
        : (index & (this->m_Cache.GetLinesPerSet() - 1));
    CacheRequestType::Reset();
    CacheRequestType::SetIndex(maskedIndex);
    CacheRequestType::SetHprot(hprot);
    CacheRequestType::SetHmastlock(hmastlock);
    CacheRequestType::AlignNCAddr(this->m_Cache.GetIndexShift());
    m_CacheOperationDataReady = false;
    if (!(this->m_Cache.GetLinesPerSet() == 1 && ((index & 0x1) == 1)) && m_LastIndexUsed != maskedIndex)
    {
        CacheRequestType::SetLatency(1);
    }
    m_NextState = STATE_F_LINE;
    m_EvictDelay = true;
    m_EvictionBufferEmpty = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::FlushAllIA(uint8_t hprot, const uint8_t hmastlock)
{
    for (LineIndex line = 0; line < this->m_Cache.GetLinesPerSet(); line++)
    {
        FlushLineIA(line, hprot, hmastlock);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::FlushAllCA(uint8_t hprot, const uint8_t hmastlock)
{
    CacheRequestType::Reset();
    CacheRequestType::SetIndex(0);
    CacheRequestType::SetHprot(hprot);
    CacheRequestType::SetHmastlock(hmastlock);
    CacheRequestType::AlignNCAddr(this->m_Cache.GetIndexShift());
    m_EvictionBufferEmpty = true;
    if (m_LastIndexUsed != 0 && this->m_Cache.GetNumWays() != 1)
    {
        CacheRequestType::SetLatency(1);
    }
    else if (m_LastIndexUsed == 0 && this->m_Cache.GetNumWays() == 1)
    {
        if (this->m_Cache.IsValid(0, 0) && this->m_Cache.IsDirty(0, 0))
        {
            m_EvictionBufferEmpty = false;
        }
        else
        {
            m_SkipSetLatency = true;
        }
    }
    m_CacheOperationDataReady = false;
    m_NextState = STATE_F_ALL;
    m_EvictDelay = true;
    m_PenultimateLineDirty = false;
    m_PenultimateLineDirtySet = false;
    m_LastLineDirty = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE bool CacheInterface<T, M, CParams>::IsHit(const codasip_address_t addr) const
{
    Index set;
    const LineIndex tag = GetTagFromAddr(addr);
    const LineIndex index = GetIndexFromAddr(addr);
    return this->m_Cache.IsHit(tag, index, set);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE bool CacheInterface<T, M, CParams>::IsBusy() const
{
    // cache reset sequence or data cache with other than read request that hit
    if (m_FSMstate == STATE_IDLE || m_FSMstate == STATE_RESET_DONE || m_FSMstate == STATE_W_MISS_DONE ||
        m_FSMstate == STATE_WT_DONE || m_FSMstate == STATE_NCR_W_DONE ||
        (m_FSMstate == STATE_W_HIT && !m_RegistersInterface->IsWriteThroughEnabled()) ||
        m_FSMstate == STATE_R_HIT || m_FSMstate == STATE_I_ALL_DONE || m_FSMstate == STATE_I_ADDR_DONE ||
        m_FSMstate == STATE_I_LINE_DONE || m_FSMstate == STATE_F_ADDR_DONE ||
        m_FSMstate == STATE_F_LINE_DONE || m_FSMstate == STATE_F_ALL_DONE ||
        m_FSMstate == STATE_R_MISS_DONE || m_FSMstate == STATE_R_MISS_ERR)
    {
        return false;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::blocking_cb(Payload<Data>& p)
{
    _DEBUG_LINE_OUTPUT_F("::port" << m_Id << "(" << p.get_command() << ", " << std::hex
                                  << p.get_address() << ", " << std::dec << p.get_bc() << ", "
                                  << static_cast<int>(p.get_ahb_hprot())
                                  << ") index = " << GetIndexFromAddr(p.get_address()));

    const Command cmd = p.get_command();
    this->check_payload(p, true, true, IS_DCACHE);
    if (p.is_error() || (cmd == CP_CMD_WRITE && IS_ICACHE))
    {
        p.set_ahb_hresp(CP_AHB_ERROR);
        p.set_ahb_hready(CP_AHB_READY);
        return;
    }
    switch (cmd)
    {
        case CP_CMD_READ:
            Read(p);
            break;
        case CP_CMD_WRITE:
            Write(p);
            break;
        case CP_CMD_DREAD:
            p.set_data(Dread(p));
            break;
        case CP_CMD_DWRITE:
            Dwrite(p);
            break;
        case CP_CMD_LOAD:
            Load(p);
            break;
        default:
            p.set_ahb_hresp(CP_AHB_OKAY);
            p.set_ahb_hready(CP_AHB_READY);
            p.set_data(0);
            break;
    }
}   // CacheInterface::blocking
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handle request phase.
 *  \param  p   Request payload.
 */
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::DoRequest(Payload<Data>& p)
{
    m_CurrentRequest.reset();
    Command command = p.get_command();
    Index sbi = p.get_address() % CParams::BYTES_PER_WORD;
    codasip_address_t addr = p.get_address() - sbi;
    Index sbc = p.get_bc();
    _DEBUG_LINE_OUTPUT_F("::port" << m_Id << "(" << p.get_command() << ", " << std::hex << addr
                                  << std::dec << ", " << sbi << ", " << p.get_bc() << ", "
                                  << p.get_data() << ", " << GetIndexFromAddr(addr) << ")");
    if (IsBusy())
    {   // Cache is not ready yet.
        _DEBUG_LINE_OUTPUT("\t" + std::string(IS_ICACHE ? ("I ") : ("D ")) + "cache is busy");
        p.set_ahb_hresp(CP_AHB_OKAY);
        p.set_ahb_hready(CP_AHB_WAIT);
        return;
    }
    _DEBUG_LINE_OUTPUT("\t" + std::string(IS_ICACHE ? ("I ") : ("D ")) + "cache is ready");
    // invalid command check
    this->check_payload(p, false, true, IS_DCACHE);
    if (!Cache<CParams>::IsValidCommand(command) || p.is_error())
    {
        m_NextState = STATE_SKIP_CYCLE;
        m_NextResponse = CP_AHB_ERROR;
        m_NextReady = CP_AHB_WAIT;
        m_PreventRespReset = true;
    }
    // valid request
    else
    {
        m_WasHit = false;
        m_NextResponse = CP_AHB_OKAY;
        m_NextReady = CP_AHB_WAIT;

        CacheRequestType::Reset();
        CacheRequestType::SetCmd(command);
        CacheRequestType::SetAddr(addr);
        CacheRequestType::SetNCAddr(addr);
        CacheRequestType::SetSbi(sbi);
        CacheRequestType::SetSbc(sbc);
        CacheRequestType::SetHprot(p.get_ahb_hprot());
        CacheRequestType::SetHmastlock(p.get_ahb_hmastlock());
        CacheRequestType::SetTag(GetTagFromAddr(addr));
        CacheRequestType::SetIndex(GetIndexFromAddr(addr));
        CacheRequestType::SetOffset(GetOffsetFromAddr(addr));
        m_IsRequestAccepted = true;
        m_CurrentRequest = p;
        if ((IS_DCACHE && !p.is_ahb_hprot_cacheable()) || (IS_ICACHE && m_Nc) || !CParams::IS_ENABLED)
        {
            PrepareNCRRequest(command, addr, sbc, sbi);
            if (m_FSMstate == STATE_W_HIT || m_FSMstate == STATE_W_MISS_DONE ||
                m_FSMstate == STATE_I_ADDR_DONE || m_FSMstate == STATE_I_LINE_DONE ||
                m_FSMstate == STATE_I_ALL_DONE || m_FSMstate == STATE_F_ADDR_DONE ||
                m_FSMstate == STATE_F_LINE_DONE || m_FSMstate == STATE_F_ALL_DONE ||
                m_FSMstate == STATE_R_MISS_ERR)
            {
                CacheRequestType::SetLatency(1);
            }
            if (command == CP_CMD_WRITE)
            {
                m_FirstCycleOfNonCacheableRequest = true;
            }
            m_NextState = STATE_NCR_REQUEST;
        }
        else if (command == CP_CMD_READ)
        {
            CacheRequestType::AlignNCAddr(this->m_Cache.GetTargetWordAlign());
            // cachable region - request might be sent next clock (if miss)
            if (m_FSMstate == STATE_W_HIT || m_FSMstate == STATE_W_MISS_DONE ||
                (m_FSMstate == STATE_R_HIT && m_IsLastIndexUsedValid &&
                    m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                (IS_DCACHE && m_RegistersInterface->GetRequestFlag() &&
                    m_LastIndexUsed != GetIndexFromAddr(addr)))
            {
                CacheRequestType::SetLatency(1);
            }
            if (IsHit(addr))
            {
                if (m_LastIndexUsed != GetIndexFromAddr(addr) ||
                    (m_FSMstate == STATE_I_ADDR_DONE && m_LastIndexUsed == GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_ADDR_DONE && m_LastIndexUsed == GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_LINE_DONE && m_LastIndexUsed == GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_ALL_DONE && m_LastIndexUsed == GetIndexFromAddr(addr)))
                {
                    CacheRequestType::SetLatency(1);
                }
                if ((m_FSMstate == STATE_W_MISS_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_W_HIT && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_R_MISS_ERR && m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_I_ADDR_DONE && m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    m_FSMstate == STATE_I_LINE_DONE ||
                    (m_FSMstate == STATE_F_ADDR_DONE && m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_LINE_DONE && m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_ALL_DONE && m_LastIndexUsed != GetIndexFromAddr(addr)))
                {
                    CacheRequestType::SetLatency(2);
                }
                m_WasHit = true;
                m_NextState = STATE_R_HIT;
            }
            else
            {
                if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
                {
                    CacheRequestType::SetLatency(2);
                }
                else
                {
                    CacheRequestType::SetLatency(1);
                }
                if ((IS_DCACHE && m_RegistersInterface->GetRequestFlag() &&
                        m_FSMstate != STATE_R_MISS_ERR) ||
                    m_FSMstate == STATE_R_MISS_DONE || m_FSMstate == STATE_RESET_DONE ||
                    m_FSMstate == STATE_R_HIT || m_FSMstate == STATE_IDLE ||
                    m_FSMstate == STATE_NCR_W_DONE || m_FSMstate == STATE_WT_DONE)
                {
                    if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
                    {
                        CacheRequestType::SetLatency(1);
                    }
                    else
                    {
                        CacheRequestType::SetLatency(0);
                    }
                }
                m_NextState = STATE_R_BUFFER_D_DELAYED;
            }
        }
        else
        {
            CacheRequestType::AlignNCAddr(this->m_Cache.GetTargetWordAlign());
            if (IsHit(addr))
            {
                if ((m_FSMstate == STATE_W_MISS_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed == GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_WT_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_IsLastIndexUsedValid && m_LastIndexUsed != GetIndexFromAddr(addr) &&
                        m_RegistersInterface->GetRequestFlag()) ||
                    (m_FSMstate == STATE_IDLE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_R_MISS_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_R_HIT && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_NCR_W_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed != GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_ADDR_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed == GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_LINE_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed == GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_F_ALL_DONE && m_IsLastIndexUsedValid &&
                        m_LastIndexUsed == GetIndexFromAddr(addr)) ||
                    (m_FSMstate == STATE_I_ADDR_DONE && m_LastIndexUsed == GetIndexFromAddr(addr)))
                {
                    m_NextState = STATE_W_HIT_DELAYED;
                }
                else if (m_FSMstate == STATE_W_MISS_DONE || m_FSMstate == STATE_I_ADDR_DONE ||
                    m_FSMstate == STATE_I_LINE_DONE || m_FSMstate == STATE_F_ADDR_DONE ||
                    m_FSMstate == STATE_F_LINE_DONE || m_FSMstate == STATE_F_ALL_DONE)
                {
                    CacheRequestType::SetLatency(2);
                    m_NextState = STATE_W_HIT_DELAYED;
                }
                else if (m_FSMstate == STATE_W_HIT)
                {
                    if (!m_IsLastIndexUsedValid || m_LastIndexUsed != GetIndexFromAddr(addr))
                    {
                        CacheRequestType::SetLatency(2);
                    }
                    m_NextState = STATE_W_HIT_DELAYED;
                }
                else
                {
                    m_NextState = STATE_W_HIT;
                }
            }
            else
            {   // write miss
                if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
                {
                    CacheRequestType::SetLatency(1);
                }
                if (m_FSMstate == STATE_W_MISS_DONE || m_FSMstate == STATE_W_HIT ||
                    m_FSMstate == STATE_I_ALL_DONE || m_FSMstate == STATE_I_ADDR_DONE ||
                    m_FSMstate == STATE_I_LINE_DONE || m_FSMstate == STATE_F_ADDR_DONE ||
                    m_FSMstate == STATE_F_LINE_DONE || m_FSMstate == STATE_F_ALL_DONE ||
                    m_FSMstate == STATE_R_MISS_ERR)
                {
                    if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE)
                    {
                        CacheRequestType::SetLatency(2);
                    }
                    else
                    {
                        CacheRequestType::SetLatency(1);
                    }
                }
                m_NextState = STATE_R_BUFFER_D_DELAYED;
            }
        }
    }
    p.set_ahb_hresp(CP_AHB_OKAY);
    p.set_ahb_hready(CP_AHB_READY);
}   // CacheInterface::request
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handle response phase.
 *  \param  p   Response payload.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::DoResponse(Payload<Data>& p)
{
    m_HxData = p.get_data();
    switch (m_FSMstate)
    {
        case STATE_NCR_REQUEST:
        case STATE_NCR_W_FINISH:
        case STATE_NC_WRITE_DATA:
            if (!CacheRequestType::WriteDataReady())
            {
                CacheRequestType::SetCoreData(m_HxData);
                CacheRequestType::SetWriteDataReady();
                PrepareDataWritePayloadsAXI(m_HxData);
            }
            break;
        case STATE_R_BUFFER_D_DELAYED:
        case STATE_R_BUFFER_D:
            if (!CacheRequestType::WriteDataReady())
            {
                CacheRequestType::SetCoreData(m_HxData);
                CacheRequestType::SetWriteDataReady();
            }
            break;
        case STATE_W_HIT:
            // write data to cache
            {
                const codasip_address_t address = m_CurrentResponse.get_address();
                const LineIndex index = GetIndexFromAddr(address);
                const Index sbi = address % CParams::BYTES_PER_WORD;
                Index way = 0;
                if (this->m_Cache.IsHit(GetTagFromAddr(address), index, way))
                {
                    this->m_Cache.IsHit(GetTagFromAddr(address), index, way);
                    m_LastIndexUsed = index;
                    m_IsLastIndexUsedValid = true;
                    UpdateCacheLineInCache(InterfaceBaseType::MaskAndShiftData(m_HxData,
                                               address,
                                               m_CurrentResponse.get_bc()),
                        way,
                        index,
                        GetOffsetFromAddr(address),
                        sbi,
                        m_CurrentResponse.get_bc());
                    if (m_RegistersInterface->IsWriteThroughEnabled() &&
                        !CacheRequestType::WriteDataReady())
                    {   // send write request to target interface and change state
                        CacheRequestType::SetCoreData(m_HxData);
                        CacheRequestType::SetWriteDataReady();
                        PrepareDataWritePayloadsAXI(m_HxData);
                    }
                }
                else
                {
                    // debugger may invalidate cache
                    m_FSMstate = STATE_R_BUFFER_D_DELAYED;
                    m_NextState = STATE_R_BUFFER_D_DELAYED;
                    m_NextResponse = AHBResponseCode::CP_AHB_OKAY;
                    m_NextReady = AHBReadyCode::CP_AHB_WAIT;
                }
            }
            break;
        // read
        default:
            if (CacheRequestType::GetCommand() == CP_CMD_READ && CacheRequestType::DataReady())
            {
                p.set_data(CacheRequestType::GetCoreWriteData());
            }
            break;
    }
    p.set_ahb_hresp(m_NextResponse);
    p.set_ahb_hready(m_NextReady);
    _DEBUG_LINE_OUTPUT_F("::port"
        << m_Id << "(cmd=" << p.get_command() << ", data=" << std::hex << p.get_data()
        << ", bi=" << std::dec << p.get_address() % CParams::BYTES_PER_WORD << ", bc=" << p.get_bc()
        << ") resp=" << m_NextResponse << ", ready=" << m_NextReady);
}   // CacheInterface::ifinish
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::transport_cb(Payload<Data>& p, const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            DoRequest(p);
            return;
        case CP_PHS_DATA:
            DoResponse(p);
            return;
        default:
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handles STATE_NCR_REQUEST state.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::HandleNonCacheableRequest()
{
    if (TARGET_DATA_BITS < CACHE_DATA_BITS)
    {   // clear target words container on narrow master configuration
        m_TargetWords.fill(0);
    }

    // do not write data together with the first address request even if data is ready (RTL)
    m_NextResponse = CP_AHB_OKAY;
    m_NextReady = CP_AHB_WAIT;
    const Index bc = CacheRequestType::GetSbc() < TARGET_BYTES_PER_WORD ? CacheRequestType::GetSbc()
                                                                        : TARGET_BYTES_PER_WORD;
    if (this->m_Cache.TargetUsed())
    {
        this->m_Cache.SetInterfaceUsed();
        m_NextState = m_FSMstate;
    }
    else
    {
        this->m_Cache.SetInterfaceUsed();
        if (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
            MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE && TARGET_DATA_BITS < CACHE_DATA_BITS)
        {
            DEBUG_CONDITION(!m_NCAWQueue.empty());
        }
        switch (this->m_Cache.TargetRequest(CacheRequestType::GetCommand(),
            (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
                MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE && TARGET_DATA_BITS < CACHE_DATA_BITS)
                ? m_NCAWQueue.front()
                : CacheRequestType::GetNCAddr(),
            CacheRequestType::GetNCSbi(),
            CacheRequestType::GetNCSbc(),
            CacheRequestType::GetHprot(),
            CacheRequestType::GetHmastlock()))
        {
            case CP_AHB_READY:
                if (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
                    MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE &&
                    TARGET_DATA_BITS < CACHE_DATA_BITS)
                {
                    m_NCAWQueue.pop();
                }
                CacheRequestType::IncCounterTargetAddrRequest();
                if (CacheRequestType::GetCommand() == CP_CMD_READ)
                {
                    CacheRequestType::SetNCAddr(CacheRequestType::GetNCAddr() + bc);
                    m_NextState = STATE_NCR_R_FINISH;
                }
                else
                {
                    CacheRequestType::NCAddrIncWordWrap();
                    CacheRequestType::SetNCSbiSbc();
                    m_NextState = m_FSMstate == STATE_NCR_REQUEST ? STATE_NCR_W_FINISH
                                                                  : STATE_WT_FINISH;
                }
                break;
            case CP_AHB_WAIT:
                m_NextState = m_FSMstate;
                break;
        }
        // AXI: write data are ready, drive it to the slave
        if (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
            MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE &&
            CacheRequestType::WriteDataReady() && m_WriteDataEnable)
        {
            AHBReadyCode ready;
            AHBResponseCode resp;
            DoTargetWriteNCData(ready, resp);
            if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
            {   // write data has been accepted, go to the finish even
                // if address was not accepted
                m_NextState = m_FSMstate == STATE_NCR_REQUEST ? STATE_NCR_W_FINISH : STATE_WT_FINISH;
            }
        }
        m_WriteDataEnable = true;
    }
    if (m_NextState != m_FSMstate)
    {
        m_WriteDataEnable = false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
Payload<typename CacheInterface<T, M, CParams>::TData>
CacheInterface<T, M, CParams>::PrepareNonCacheableRequestAxi4()
{
    const Index numTargetWords = CacheRequestType::GetSbc() <= TARGET_BYTES_PER_WORD
        ? 1
        : CacheRequestType::GetSbc() / TARGET_BYTES_PER_WORD;
    DEBUG_CONDITION(numTargetWords - 1 <= 0xFF);

    Payload<TData> result;
    result.set_command(CacheRequestType::GetCommand());
    result.set_axi_valid(CP_AXI_VALID);
    result.set_address(CacheRequestType::GetNCAddr() + CacheRequestType::GetSbi());
    result.set_bc(std::min(static_cast<Index>(TARGET_BYTES_PER_WORD), CacheRequestType::GetSbc()));
    result.set_axi_len(numTargetWords - 1);
    result.set_axi_burst(CP_AXI_BURST_INCR);
    result.set_axi_cache(CacheRequestType::GetHprot() & CP_AHB_BUFFERABLE ? 1 : 0);
    result.set_axi_lock(CacheRequestType::GetHmastlock());
    result.set_axi_prot(2 | ((CacheRequestType::GetHprot() >> 1) & 0x1) |
        (((~CacheRequestType::GetHprot()) & 0x1) << 2));
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handles STATE_NCR_REQUEST state on Axi4 master interface.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::HandleNonCacheableRequestAxi4()
{
    m_NextState = m_FSMstate;

    if (TARGET_DATA_BITS < CACHE_DATA_BITS)
    {   // clear target words container on narrow master configuration
        m_TargetWords.fill(0);
        m_IsNonCacheableNarrowTargetReadSuccessful = true;
    }

    if (CacheRequestType::GetCommand() == CP_CMD_READ)
    {
        if (!this->m_Cache.CanStartLineFillAxi4(CacheRequestType::GetNCAddr()))
        {   // An eviction of the same address or line fill is in progress.
            return;
        }

        auto p = PrepareNonCacheableRequestAxi4();
        if (this->m_Cache.TargetRequest(p) == CP_AHB_READY)
        {
            m_NextState = STATE_NC_READ_DATA;
        }
    }
    else
    {
        if (this->m_Cache.EvictRunning())
        {   // An eviction is in progress.
            return;
        }

        HandleNonCacheableWriteAxi4();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handles STATE_NC_READ_DATA state.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::HandleNonCacheableReadAxi4()
{
    m_NextState = m_FSMstate;

    m_NextResponse = CP_AHB_OKAY;
    m_NextReady = CP_AHB_WAIT;

    if (TARGET_DATA_BITS < CACHE_DATA_BITS)
    {
        HandleNonCacheableNarrowTargetReadAxi4();
    }
    else
    {
        TData targetData = 0;
        AHBReadyCode ready = CP_AHB_READY;
        AHBResponseCode resp = CP_AHB_OKAY;
        this->m_Cache.TargetReadData(ready, resp, targetData);
        CacheRequestType::SetResp(resp);
        CacheRequestType::SetReady(ready);

        if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
        {
            CacheRequestType::SetCoreData(targetData);
            m_NextState = STATE_RAM_RESP;
        }
        else if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
        {
            CacheRequestType::ResetCacheData();
            m_NextState = STATE_RAM_RESP;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handles STATE_NC_READ_DATA state for configurations with narrow target.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::HandleNonCacheableNarrowTargetReadAxi4()
{
    TData targetData = 0;
    AHBReadyCode ready = CP_AHB_READY;
    AHBResponseCode resp = CP_AHB_OKAY;
    this->m_Cache.TargetReadData(ready, resp, targetData);

    const Index bc = std::min(CacheRequestType::GetSbc(), static_cast<Index>(TARGET_BYTES_PER_WORD));

    if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
    {
        const auto targetWordIndex = (CacheRequestType::GetNCSbi() +
                                         CacheRequestType::GetCounter() * bc) /
            TARGET_BYTES_PER_WORD;
        m_TargetWords[targetWordIndex] = targetData;

        CacheRequestType::IncCounter();
    }
    else if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
    {   // flags the read as unsuccessful and complete the burst.
        m_IsNonCacheableNarrowTargetReadSuccessful = false;
        CacheRequestType::IncCounter();
    }

    if (CacheRequestType::GetCounter() * bc >= CacheRequestType::GetSbc())
    {   // all word bytes were received
        if (m_IsNonCacheableNarrowTargetReadSuccessful)
        {
            CacheRequestType::SetResp(CP_AHB_OKAY);
            CacheRequestType::SetReady(CP_AHB_READY);
            CacheRequestType::SetCoreData(
                ConcatenateTargetWordsToCacheWords(m_TargetWords.begin(), m_TargetWords.end())[0]);
        }
        else
        {
            CacheRequestType::SetResp(CP_AHB_ERROR);
            CacheRequestType::SetReady(CP_AHB_WAIT);
            CacheRequestType::ResetCacheData();
        }
        m_NextState = STATE_RAM_RESP;
    }
}

/**
 *  \brief  Handles STATE_NC_WRITE_DATA state.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::HandleNonCacheableWriteAxi4()
{
    m_NextState = m_FSMstate;

    m_NextResponse = CP_AHB_OKAY;
    m_NextReady = CP_AHB_WAIT;

    if (m_FSMstate != STATE_NC_WRITE_DATA)
    {
        auto p = PrepareNonCacheableRequestAxi4();
        if (this->m_Cache.TargetRequest(p) == CP_AHB_READY)
        {
            m_NextState = STATE_NC_WRITE_DATA;
        }
    }

    if (m_FirstCycleOfNonCacheableRequest)
    {
        m_FirstCycleOfNonCacheableRequest = false;
    }
    else
    {
        if (!m_NCWQueue.empty())
        {
            Payload<TData> p;
            p.set_axi_valid(CP_AXI_VALID);
            p.set_data(m_NCWQueue.front().first);
            p.set_axi_last(m_NCWQueue.size() == 1 ? 1 : 0);
            p.set_axi_wstrb(m_NCWQueue.front().second);

            this->m_Cache.TargetWriteData(p);
            if (p.get_ahb_hready() == CP_AHB_READY)
            {
                m_NCWQueue.pop();
            }
        }
    }

    if (CacheRequestType::WriteDataReady() && m_NCWQueue.empty() && m_NextState == STATE_NC_WRITE_DATA)
    {
        m_NextState = STATE_NC_WRITE_RESPONSE;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handles STATE_NC_WRITE_RESPONSE state.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::HandleNonCacheableWriteResponseAxi4()
{
    m_NextState = m_FSMstate;

    m_NextResponse = CP_AHB_OKAY;
    m_NextReady = CP_AHB_WAIT;

    AHBReadyCode ready = CP_AHB_READY;
    AHBResponseCode resp = CP_AHB_OKAY;
    this->m_Cache.TargetWriteResponse(ready, resp);

    if (ready == CP_AHB_WAIT && resp == CP_AHB_OKAY)
    {
        return;
    }

    CacheRequestType::SetResp(resp);
    CacheRequestType::SetReady(ready);
    m_NextState = STATE_NCR_W_RESP;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handles STATE_NCR_R_FINISH state.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::HandleNonCacheableReadFinish()
{
    this->m_Cache.SetInterfaceUsed();
    m_NextResponse = CP_AHB_OKAY;
    m_NextReady = CP_AHB_WAIT;
    AHBReadyCode ready = CP_AHB_READY;
    AHBResponseCode resp = CP_AHB_OKAY;
    TData targetData = 0;
    this->m_Cache.TargetReadData(ready, resp, targetData);
    CacheRequestType::SetResp(resp);
    CacheRequestType::SetReady(ready);
    const Index bc = CacheRequestType::GetSbc() < TARGET_BYTES_PER_WORD ? CacheRequestType::GetSbc()
                                                                        : TARGET_BYTES_PER_WORD;
    if (ready == CP_AHB_WAIT && resp == CP_AHB_OKAY)
    {
        if (CacheRequestType::GetTargetRequestCount() * bc < CacheRequestType::GetSbc())
        {
            switch (this->m_Cache.TargetRequest(CacheRequestType::GetCommand(),
                CacheRequestType::GetNCAddr(),
                CacheRequestType::GetNCSbi(),
                CacheRequestType::GetNCSbc(),
                CacheRequestType::GetHprot(),
                CacheRequestType::GetHmastlock()))
            {
                case CP_AHB_READY:
                    CacheRequestType::IncCounterTargetAddrRequest();
                    CacheRequestType::SetNCAddr(CacheRequestType::GetNCAddr() + bc);
                    if (CacheRequestType::GetTargetErrorCount())
                    {
                        CacheRequestType::IncCounterTargetError();
                    }
                    break;
                case CP_AHB_WAIT:
                    break;
            }
        }
        m_NextState = m_FSMstate;
    }
    else if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
    {
        if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
        {
            const auto cacheData = SplitTargetWordsToCacheWords(TLine(1, targetData));

            const auto targetAlignedAddress = detail::AlignAddressToWordAddress(
                CacheRequestType::GetAddr() + CacheRequestType::GetSbi(),
                TARGET_BYTES_PER_WORD);
            const auto cacheAlignedAddress = detail::AlignAddressToWordAddress(
                CacheRequestType::GetAddr() + CacheRequestType::GetSbi(),
                BYTES_PER_WORD);
            const auto cacheWordIndex = (cacheAlignedAddress - targetAlignedAddress) / BYTES_PER_WORD;

            CacheRequestType::SetCoreData(cacheData[cacheWordIndex]);
        }
        else
        {
            const auto targetWordIndex = (CacheRequestType::GetNCSbi() +
                                             CacheRequestType::GetCounter() * bc) /
                TARGET_BYTES_PER_WORD;
            m_TargetWords[targetWordIndex] = targetData;
        }

        CacheRequestType::IncCounter();
        if (CacheRequestType::GetCounter() * bc >= CacheRequestType::GetSbc())
        {   // all word bytes were received
            if (TARGET_DATA_BITS < CACHE_DATA_BITS)
            {
                CacheRequestType::SetCoreData(
                    ConcatenateTargetWordsToCacheWords(m_TargetWords.begin(), m_TargetWords.end())[0]);
            }
            m_NextState = STATE_RAM_RESP;
        }
        else if (CacheRequestType::GetTargetRequestCount() * bc < CacheRequestType::GetSbc())
        {   // not all word bytes were requested
            switch (this->m_Cache.TargetRequest(CacheRequestType::GetCommand(),
                CacheRequestType::GetNCAddr(),
                CacheRequestType::GetNCSbi(),
                CacheRequestType::GetNCSbc(),
                CacheRequestType::GetHprot(),
                CacheRequestType::GetHmastlock()))
            {
                case CP_AHB_READY:
                    CacheRequestType::IncCounterTargetAddrRequest();
                    CacheRequestType::SetNCAddr(CacheRequestType::GetNCAddr() + bc);
                    if (CacheRequestType::GetTargetErrorCount())
                    {
                        CacheRequestType::IncCounterTargetError();
                    }
                    m_NextState = STATE_NCR_R_FINISH;
                    break;
                case CP_AHB_WAIT:
                    // check whether multiple requests are pending already,
                    // if so stay in the finish state, otherwise move to next request
                    m_NextState = (CacheRequestType::GetTargetRequestCount() >
                                      CacheRequestType::GetCounter())
                        ? m_FSMstate
                        : static_cast<FSMState>(STATE_NCR_REQUEST);
                    break;
            }
        }
        else
        {   // all word bytes were requested but not received
            m_NextState = m_FSMstate;
        }
    }
    else if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
    {
        CacheRequestType::ResetCacheData();
        m_NextState = STATE_RAM_RESP;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handle write data and response into non-cacheable region.
 *
 *          The handler should be called in the non-cacheable write finish state during write data
 *          and response phase transport handling.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::HandleNonCacheableWriteFinish()
{
    m_NextState = m_FSMstate;
    this->m_Cache.SetInterfaceUsed();
    m_NextResponse = CP_AHB_OKAY;
    m_NextReady = CP_AHB_WAIT;

    AHBReadyCode ready = CP_AHB_READY;
    AHBResponseCode resp = CP_AHB_OKAY;
    // write data phase
    // data phase may proceed faster than addresses, but only by 1
    // AXI: only one data transaction may be ACK without address ACK
    if (CacheRequestType::GetTargetBytesCount() < BYTES_PER_WORD &&
        CacheRequestType::GetTargetRequestCount() + 1 > CacheRequestType::GetCounter())
    {
        DoTargetWriteNCData(ready, resp);
    }

    if (CacheRequestType::GetTargetRequestBytesCount() < BYTES_PER_WORD)
    {   // not all writes requested
        // write address phase, continue with additional requests
        // the addresses may proceed much faster than data (AXI)
        if (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
            MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE && TARGET_DATA_BITS < CACHE_DATA_BITS)
        {
            DEBUG_CONDITION(!m_NCAWQueue.empty());
        }
        switch (this->m_Cache.TargetRequest(CacheRequestType::GetCommand(),
            (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE && TARGET_DATA_BITS < CACHE_DATA_BITS)
                ? m_NCAWQueue.front()
                : CacheRequestType::GetNCAddr(),
            CacheRequestType::GetNCSbi(),
            CacheRequestType::GetNCSbc(),
            CacheRequestType::GetHprot(),
            CacheRequestType::GetHmastlock()))
        {
            case CP_AHB_READY:
                if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE &&
                    TARGET_DATA_BITS < CACHE_DATA_BITS)
                {
                    m_NCAWQueue.pop();
                }
                CacheRequestType::IncCounterTargetAddrRequest();
                CacheRequestType::NCAddrIncWordWrap();
                CacheRequestType::SetNCSbiSbc();
                if (CacheRequestType::GetTargetErrorCount())
                {
                    CacheRequestType::IncCounterTargetError();
                }
                m_NextState = m_FSMstate;
                break;
            case CP_AHB_WAIT:
                m_NextState = m_FSMstate;
                break;
        }
    }

    // write response phase
    if (   // there is more data requests then data responses AND
        (CacheRequestType::GetCounter() > CacheRequestType::GetTargetRespCount()) &&
        // target protocol is AHB OR
        (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE ||
            // (target protocol is AXI and) there are more address requests then data responses
            CacheRequestType::GetTargetRequestCount() > CacheRequestType::GetTargetRespCount()))
    {
        this->m_Cache.TargetWriteResponse(ready, resp);
        if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
        {
            CacheRequestType::SetResp(resp);
            CacheRequestType::SetReady(ready);
            CacheRequestType::ResetCacheData();
            m_NextState = m_FSMstate == STATE_WT_FINISH ? STATE_WT_RESP : STATE_NCR_W_RESP;
        }
        else if (ready == CP_AHB_READY /*&& resp == CP_AHB_OKAY*/)
        {
            CacheRequestType::IncCounterTargetResp();
        }
    }

    if (   // there is data response for every data request AND
        (CacheRequestType::GetCounter() == CacheRequestType::GetTargetRespCount()) &&
        // all word bytes were written OR
        (CacheRequestType::GetTargetBytesCount() >= BYTES_PER_WORD ||
            // there is an error
            (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)))
    {
        CacheRequestType::SetResp(resp);
        CacheRequestType::SetReady(ready);
        m_NextState = m_FSMstate == STATE_WT_FINISH ? STATE_WT_RESP : STATE_NCR_W_RESP;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CLine
CacheInterface<T, M, CParams>::SplitTargetWordsToCacheWords(const TLine& targetWords) const
{
    CLine result = {};
    for (const auto& targetWord : targetWords)
    {
        for (Index i = 0; i < CACHE_WORDS_PER_TARGET_WORD; ++i)
        {
            result.emplace_back(
                Unaligned<TData, BYTE_BITS, TARGET_BYTES_PER_WORD>::template read<ENDIANNESS>(&targetWord,
                    0,
                    i * BYTES_PER_WORD,
                    BYTES_PER_WORD));
        }
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
template<typename IteratorType>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CLine
CacheInterface<T, M, CParams>::ConcatenateTargetWordsToCacheWords(IteratorType begin,
    IteratorType end) const
{
    CLine result = {};
    for (auto i = begin; i < end; i += TARGET_WORDS_PER_CACHE_WORD)
    {
        CData cacheWord = 0;
        for (size_t j = 0; j < TARGET_WORDS_PER_CACHE_WORD; ++j)
        {
            CData tmp = *(i + j);
            if (ENDIANNESS == CP_LITTLE_ENDIAN)
            {
                cacheWord |= LeftShift(tmp, j * TARGET_DATA_BITS);
            }
            else
            {
                cacheWord |= LeftShift(tmp, CACHE_DATA_BITS - (TARGET_DATA_BITS * (j + 1)));
            }
        }
        result.emplace_back(cacheWord);
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::CLine
CacheInterface<T, M, CParams>::ConcatenateTargetWordsToCacheWords(const TLine& targetWords) const
{
    return ConcatenateTargetWordsToCacheWords(targetWords.begin(), targetWords.end());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Performs one step of cache FSM.
 */
template<class T, class M, class CParams>
void CacheInterface<T, M, CParams>::Fsm_step()
{
    _DEBUG_LINE_OUTPUT_F("state of FSM is : " << m_StateNames.at(m_FSMstate) << " ("
                                              << static_cast<int>(m_FSMstate) << ")");
    _DEBUG_LINE_OUTPUT_F("Requested address is: "
        << std::hex << CacheRequestType::GetAddr() + CacheRequestType::GetSbi() << std::dec);
    _DEBUG_LINE_OUTPUT_F("Current latency is : " << CacheRequestType::GetLatency());
    _DEBUG_LINE_OUTPUT_F("Target used : " << this->m_Cache.TargetUsed());
    AHBResponseCode resp = CP_AHB_OKAY;
    AHBReadyCode ready = CP_AHB_READY;
    m_NextState = STATE_IDLE;
    TData targetData = 0;
    Data cacheData = 0;
    CacheRequestType::ResetDataReady();
    m_CurrentResponse.reset();
    // Each state resolves next FSM state and response that will be presented
    // during this clock cycle. Status of interface is busy when FSM is in state
    // other than STATE_IDLE.
    switch (m_FSMstate)
    {
        case STATE_WT_FINISH:
        case STATE_NCR_W_FINISH:
            HandleNonCacheableWriteFinish();
            break;
        case STATE_NCR_W_RESP:
        case STATE_WT_RESP:
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE &&
                CacheRequestType::GetResp() == CP_AHB_ERROR)
            {   // Handle second phase of the AHB3-LITE error response. Data phase has to be called because of the dumper.
                this->m_Cache.TargetWriteData(ready, resp, 0);
            }
            // fall through
        case STATE_R_MISS_RESP:
        case STATE_R_MISS_ERR_RESP:
        case STATE_RAM_RESP:
            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }
            m_NextResponse = CacheRequestType::GetResp();
            m_NextReady = CacheRequestType::GetReady();
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE &&
                m_NextResponse == CP_AHB_ERROR && (CacheRequestType::GetHprot() & CP_AHB_CACHEABLE))
            {   // evict cache line after failed line fill
                if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                    this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                {
                    PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                        CacheRequestType::GetIndex(),
                        CacheRequestType::GetHprot(),
                        CacheRequestType::GetHmastlock());
                }
            }
            CacheRequestType::SetResp(CP_AHB_OKAY);
            CacheRequestType::SetReady(CP_AHB_READY);
            if (m_NextResponse == CP_AHB_OKAY && m_NextReady == CP_AHB_READY)
            {
                CacheRequestType::SetDataReady();
            }
            this->m_Cache.SetInterfaceUsed();
            m_FSMstate = m_FSMstate == STATE_WT_RESP  ? STATE_WT_DONE
                : m_FSMstate == STATE_NCR_W_RESP      ? STATE_NCR_W_DONE
                : m_FSMstate == STATE_R_MISS_RESP     ? STATE_R_MISS_DONE
                : m_FSMstate == STATE_R_MISS_ERR_RESP ? STATE_R_MISS_ERR
                                                      : STATE_IDLE;
            break;
        // Noncachable region read. Request to target will be repeated if target is busy.
        // Error stops repeating request. Ready switches to finish state. Interface responds
        // with wait.
        case STATE_WT_REQUEST:
        case STATE_NCR_REQUEST:
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI && m_FSMstate == STATE_NCR_REQUEST)
            {
                if ((CacheRequestType::GetCommand() == CP_CMD_READ &&
                        !this->m_Cache.CanStartLineFillAxi4(CacheRequestType::GetNCAddr())) ||
                    (CacheRequestType::GetCommand() == CP_CMD_WRITE && this->m_Cache.EvictRunning()))
                {
                    m_NextResponse = CP_AHB_OKAY;
                    m_NextReady = CP_AHB_WAIT;
                    m_NextState = m_FSMstate;
                    break;
                }
            }

            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }

            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
            {
                HandleNonCacheableRequestAxi4();
            }
            else
            {
                HandleNonCacheableRequest();
            }
            break;
        //  Non-cacheable read data phase on AXI4.
        case STATE_NC_READ_DATA:
            HandleNonCacheableReadAxi4();
            break;
        //  Non-cacheable write data phase on AXI4.
        case STATE_NC_WRITE_DATA:
            HandleNonCacheableWriteAxi4();
            break;
        //  Non-cacheable write response phase on AXI4.
        case STATE_NC_WRITE_RESPONSE:
            HandleNonCacheableWriteResponseAxi4();
            break;
        // Finish will be repeated while target responds with wait. Error stops whole request.
        // Ack adds loaded data to the rest (if target word is smaller than cache word). Once
        // enough data is loaded, they can be read using ifinish. Interface responds with
        // Ack (enough data loaded), wait (not enough data loaded) or with target response.
        case STATE_NCR_R_FINISH:
            HandleNonCacheableReadFinish();
            break;
        case STATE_R_CL_REQUEST:
            if (this->m_Cache.TargetUsed())
            {
                m_NextState = m_FSMstate;
            }
            else
            {
                this->m_Cache.SetInterfaceUsed();
                switch (this->m_Cache.TargetRequest(CP_CMD_READ,
                    CacheRequestType::GetNCAddr(),
                    0,
                    TARGET_BYTES_PER_WORD,
                    CacheRequestType::GetHprot(),
                    CacheRequestType::GetHmastlock()))
                {
                    case CP_AHB_READY:
                        CacheRequestType::IncCounterTargetAddrRequest();
                        CacheRequestType::NCAddrIncWordWrap();
                        m_NextState = STATE_R_CL_FINISH;
                        break;
                    case CP_AHB_WAIT:
                        m_NextState = STATE_R_CL_REQUEST;
                        break;
                }
            }
            break;
        case STATE_R_CL_FINISH:
            m_NextResponse = CacheRequestType::GetResp();
            m_NextReady = CacheRequestType::GetReady();
            if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE ||
                MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
            {
                if (m_NextResponse == CP_AHB_OKAY && m_NextReady == CP_AHB_READY)
                {
                    CacheRequestType::SetDataReady();
                }
                m_LastIndexUsed = CacheRequestType::GetIndex();
                m_IsLastIndexUsedValid = true;
                constexpr size_t numTargetWordsWithRequestedData = TARGET_WORDS_PER_CACHE_WORD == 0
                    ? 1
                    : TARGET_WORDS_PER_CACHE_WORD;
                const auto& targetWords = this->m_Cache.GetLineFillDataAxi();

                if (CacheRequestType::GetCommand() == CP_CMD_READ &&
                    targetWords.size() == numTargetWordsWithRequestedData &&
                    !this->m_Cache.HasLineFillErrorOccuredAxi())
                {   // all target words with requested data have been read without error
                    const TLine targetWordsWithRequestedData(targetWords.begin(),
                        targetWords.begin() + numTargetWordsWithRequestedData);
                    CLine cacheWords = {};
                    if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
                    {   // split target word to cache words
                        cacheWords = SplitTargetWordsToCacheWords(targetWordsWithRequestedData);
                    }
                    else
                    {   // concatenate target words to cache word
                        cacheWords = ConcatenateTargetWordsToCacheWords(targetWordsWithRequestedData);
                    }
                    CacheRequestType::SetCoreData(cacheWords[0]);
                    CacheRequestType::SetResp(CP_AHB_OKAY);
                    CacheRequestType::SetReady(CP_AHB_READY);
                    m_NextState = m_FSMstate;
                }

                if (CacheRequestType::GetCommand() == CP_CMD_READ &&
                    targetWords.size() == numTargetWordsWithRequestedData &&
                    this->m_Cache.HasLineFillErrorOccuredAxi())
                {
                    CacheRequestType::SetResp(CP_AHB_ERROR);
                    CacheRequestType::SetReady(CP_AHB_WAIT);
                }

                if (this->m_Cache.HasLineFillFinishedAxi4())
                {   // cache line read has finished
                    if (this->m_Cache.HasLineFillErrorOccuredAxi())
                    {   // an error has occured during the read
                        if (targetWords.size() < numTargetWordsWithRequestedData ||
                            CacheRequestType::GetCommand() == CP_CMD_WRITE)
                        {
                            CacheRequestType::SetResp(CP_AHB_ERROR);
                            CacheRequestType::SetReady(CP_AHB_WAIT);
                        }
                        if (CacheRequestType::GetCommand() == CP_CMD_READ)
                        {
                            m_NextState = STATE_R_MISS_RESP;
                        }
                        else
                        {
                            m_NextState = STATE_RAM_RESP;
                        }
                    }
                    else
                    {   // all cache line words have been read successfully
                        CLine cacheWords = TransformTargetWordsToCacheWords<CLine>(
                            TLine(targetWords.begin(), targetWords.end()));
                        if (CacheRequestType::GetCommand() == CP_CMD_READ)
                        {
                            if (!(IS_DCACHE &&
                                    this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                                    this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex())))
                            {
                                CacheRequestType::SetLatency(1);
                            }
                        }

                        if (CacheRequestType::GetCommand() == CP_CMD_WRITE)
                        {   // write requested data to cache word
                            Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template write<ENDIANNESS>(
                                &(cacheWords[0]),
                                InterfaceBaseType::MaskAndShiftData(CacheRequestType::GetCoreWriteData(),
                                    CacheRequestType::GetAddr() + CacheRequestType::GetSbi(),
                                    CacheRequestType::GetSbc()),
                                0,
                                CacheRequestType::GetSbi(),
                                CacheRequestType::GetSbc());
                        }

                        UnwrapCacheLine(cacheWords,
                            CacheRequestType::GetAddr() + CacheRequestType::GetSbi());
                        for (size_t i = 0; i < cacheWords.size(); ++i)
                        {
                            CacheRequestType::SetCacheLineWord(cacheWords[i], i);
                        }

                        if (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
                            !m_RegistersInterface->IsWriteThroughEnabled())
                        {
                            if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                                this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                            {
                                if (this->m_Cache.EvictRunning())
                                {
                                    m_NextState = MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI
                                        ? STATE_SAVE_LINE_AXI4
                                        : STATE_SAVE_LINE;
                                    break;
                                }
                                else
                                {
                                    PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                                        CacheRequestType::GetIndex(),
                                        CacheRequestType::GetHprot(),
                                        CacheRequestType::GetHmastlock());
                                    this->m_Cache.IncreaseLatency();
                                }
                            }
                            this->m_Cache.SetDirty(m_ReplaceWay, CacheRequestType::GetIndex());
                            SaveCacheLineIntoCache(CacheRequestType::GetCacheLine(),
                                m_ReplaceWay,
                                CacheRequestType::GetIndex(),
                                CacheRequestType::GetTag());
                            m_FSMstate = STATE_W_MISS_DONE;
                            m_NextState = STATE_W_MISS_DONE;
                        }
                        else
                        {
                            m_NextState = MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI
                                ? STATE_SAVE_LINE_AXI4
                                : STATE_SAVE_LINE;
                        }
                    }
                }
                else
                {   // cache line read still in progress
                    m_NextState = m_FSMstate;

                    if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI && !this->m_Cache.EvictRunning())
                    {
                        if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                            this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                        {
                            PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                                CacheRequestType::GetIndex(),
                                CacheRequestType::GetHprot(),
                                CacheRequestType::GetHmastlock());
                            this->m_Cache.SetEvictionDelayAxi4(1);
                        }
                    }
                }
            }
            else
            {
                if (m_NextResponse == CP_AHB_OKAY && m_NextReady == CP_AHB_READY)
                {
                    m_LastIndexUsed = CacheRequestType::GetIndex();
                    m_IsLastIndexUsedValid = true;
                    CacheRequestType::SetDataReady();
                    CacheRequestType::SetResp(CP_AHB_OKAY);
                    CacheRequestType::SetReady(CP_AHB_READY);
                }
                this->m_Cache.SetInterfaceUsed();
                CacheRequestType::IncCounter();
                // need to split incrementing bursts
                if (BURST_ENABLED && this->m_Cache.GetTargetBurstMode() == CP_AHB_INCR &&
                    CacheRequestType::GetNCAddr() % this->m_Cache.GetLineSize() == 0)
                {
                    this->m_Cache.TargetStartBurst(this->m_Cache.GetTargetBurstMode());
                }
                this->m_Cache.TargetReadData(ready, resp, targetData);
                if (ready == CP_AHB_WAIT && resp == CP_AHB_OKAY)
                {
                    if (CacheRequestType::GetTargetRequestBytesCount() < this->m_Cache.GetLineSize())
                    {
                        switch (this->m_Cache.TargetRequest(CP_CMD_READ,
                            CacheRequestType::GetNCAddr(),
                            0,
                            TARGET_BYTES_PER_WORD,
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock()))
                        {
                            case CP_AHB_READY:
                                CacheRequestType::IncCounterTargetAddrRequest();
                                CacheRequestType::NCAddrIncWordWrap();
                                if (CacheRequestType::GetTargetErrorCount())
                                {
                                    CacheRequestType::IncCounterTargetError();
                                }
                                break;
                            case CP_AHB_WAIT:
                                break;
                        }
                    }
                    CacheRequestType::DecCounter();
                    m_NextState = m_FSMstate;
                }
                if (ready == CP_AHB_READY && resp == CP_AHB_OKAY)
                {
                    if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
                    {
                        // Split target word to cache words.
                        for (int i = 0; i < CACHE_WORDS_PER_TARGET_WORD; i++)
                        {
                            CacheRequestType::PushWord(
                                Unaligned<TData, BYTE_BITS, TARGET_BYTES_PER_WORD>::template read<
                                    ENDIANNESS>(&targetData, 0, i * BYTES_PER_WORD, BYTES_PER_WORD));
                        }
                    }
                    else
                    {
                        CacheRequestType::ConcatenateCacheData(targetData);
                        if (CacheRequestType::LoadedCacheWord())
                        {
                            CacheRequestType::PushCacheData();
                        }
                    }
                    if (CacheRequestType::NotFinished() && CacheRequestType::LoadedCacheWord())
                    {   // whole cache line is loaded
                        CacheRequestType::SetFinished();
                        m_LastIndexUsed = CacheRequestType::GetIndex();
                        m_IsLastIndexUsedValid = true;
                        if (CacheRequestType::GetCommand() == CP_CMD_READ)
                        {
                            CacheRequestType::SetCoreData(CacheRequestType::GetCacheLineWord());
                            CacheRequestType::SetResp(CP_AHB_OKAY);
                            CacheRequestType::SetReady(CP_AHB_READY);
                        }
                        else
                        {   // update cache line but do not save it to cache yet
                            cacheData = CacheRequestType::GetCacheLineWord();
                            Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template write<ENDIANNESS>(
                                &cacheData,
                                InterfaceBaseType::MaskAndShiftData(CacheRequestType::GetCoreWriteData(),
                                    CacheRequestType::GetAddr() + CacheRequestType::GetSbi(),
                                    CacheRequestType::GetSbc()),
                                0,
                                CacheRequestType::GetSbi(),
                                CacheRequestType::GetSbc());
                            CacheRequestType::SetCacheLineWord(cacheData);
                        }
                    }
                    if (CacheRequestType::GetTargetBytesCount() >= this->m_Cache.GetLineSize())
                    {
                        if (CacheRequestType::GetCommand() == CP_CMD_READ)
                        {
                            if (!(IS_DCACHE &&
                                    this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                                    this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex())))
                            {
                                CacheRequestType::SetLatency(1);
                            }
                        }
                        m_NextState = STATE_SAVE_LINE;
                        if (BURST_ENABLED)
                        {
                            this->m_Cache.TargetStopBurst();
                        }

                        if (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
                            !m_RegistersInterface->IsWriteThroughEnabled())
                        {
                            this->m_Cache.SetInterfaceUsed();
                            m_NextResponse = CacheRequestType::GetResp();
                            m_NextReady = CacheRequestType::GetReady();
                            if (m_NextResponse == CP_AHB_OKAY && m_NextReady == CP_AHB_READY)
                            {
                                CacheRequestType::SetDataReady();
                                CacheRequestType::SetResp(CP_AHB_OKAY);
                                CacheRequestType::SetReady(CP_AHB_READY);
                            }
                            if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                                this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                            {
                                if (this->m_Cache.EvictRunning())
                                {
                                    m_NextState = STATE_SAVE_LINE;
                                    break;
                                }
                                else
                                {
                                    PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                                        CacheRequestType::GetIndex(),
                                        CacheRequestType::GetHprot(),
                                        CacheRequestType::GetHmastlock());
                                    this->m_Cache.IncreaseLatency();
                                }
                            }
                            this->m_Cache.SetDirty(m_ReplaceWay, CacheRequestType::GetIndex());
                            SaveCacheLineIntoCache(CacheRequestType::GetCacheLine(),
                                m_ReplaceWay,
                                CacheRequestType::GetIndex(),
                                CacheRequestType::GetTag());
                            m_FSMstate = STATE_W_MISS_DONE;
                            m_NextState = STATE_W_MISS_DONE;
                        }
                    }
                    else if (CacheRequestType::GetTargetRequestBytesCount() <
                        this->m_Cache.GetLineSize())
                    {
                        switch (this->m_Cache.TargetRequest(CP_CMD_READ,
                            CacheRequestType::GetNCAddr(),
                            0,
                            TARGET_BYTES_PER_WORD,
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock()))
                        {
                            case CP_AHB_READY:
                                CacheRequestType::IncCounterTargetAddrRequest();
                                CacheRequestType::NCAddrIncWordWrap();
                                m_NextState = m_FSMstate;
                                break;
                            case CP_AHB_WAIT:
                                // do not move to request state once we are in finish
                                m_NextState = m_FSMstate;
                                break;
                        }
                    }
                    else
                    {   // waiting for all data to finish
                        m_NextState = m_FSMstate;
                    }
                }
                else if (ready == CP_AHB_WAIT && resp == CP_AHB_ERROR)
                {
                    if (CacheRequestType::GetTargetBytesCount() < this->m_Cache.GetLineSize())
                    {
                        // Two state error - AHB must make one more request. Result is not important
                        this->m_Cache.TargetErrRequest(CP_CMD_READ,
                            CacheRequestType::GetNCAddr(),
                            0,
                            TARGET_BYTES_PER_WORD,
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock());
                    }
                    // Burst must be terminated internally
                    if (BURST_ENABLED)
                    {
                        this->m_Cache.TargetStopBurst();
                    }
                    if (CacheRequestType::NotFinished() || CacheRequestType::GetCommand() == CP_CMD_WRITE)
                    {
                        CacheRequestType::SetResp(resp);
                        CacheRequestType::SetReady(ready);
                    }
                    CacheRequestType::ResetCacheData();
                    if (CacheRequestType::GetCommand() == CP_CMD_READ)
                    {
                        m_NextState = STATE_R_MISS_ERR_RESP;
                    }
                    else
                    {
                        m_NextState = STATE_RAM_RESP;
                    }
                }
            }
            break;
        case STATE_SAVE_LINE_AXI4:
            if (CacheRequestType::GetCommand() == CP_CMD_WRITE)
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_READY;
                CacheRequestType::SetResp(CP_AHB_OKAY);
                CacheRequestType::SetReady(CP_AHB_READY);
                if (CacheRequestType::GetLatency())
                {
                    CacheRequestType::DecLatency();
                    m_NextState = m_FSMstate;
                }
                else
                {
                    if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                        this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                    {
                        if (this->m_Cache.EvictRunning())
                        {
                            m_NextState = m_FSMstate;
                            break;
                        }
                        else
                        {
                            PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                                CacheRequestType::GetIndex(),
                                CacheRequestType::GetHprot(),
                                CacheRequestType::GetHmastlock());
                            this->m_Cache.SetEvictionDelayAxi4(1);
                            CacheRequestType::SetLatency(2);
                            m_NextState = STATE_SKIP_CYCLE_AXI4;
                        }
                    }
                    if (!m_RegistersInterface->IsWriteThroughEnabled())
                    {
                        this->m_Cache.SetDirty(m_ReplaceWay, CacheRequestType::GetIndex());
                    }
                    SaveCacheLineIntoCache(CacheRequestType::GetCacheLine(),
                        m_ReplaceWay,
                        CacheRequestType::GetIndex(),
                        CacheRequestType::GetTag());
                    if (CacheRequestType::GetInvalidateLoadedLine())
                    {
                        this->m_Cache.SetInvalid(m_ReplaceWay, CacheRequestType::GetIndex());
                    }
                    if (m_RegistersInterface->IsWriteThroughEnabled())
                    {   // send write request to target interface and change state
                        m_NextReady = CP_AHB_WAIT;
                        CacheRequestType::SetReady(CP_AHB_WAIT);
                        CacheRequestType::ResetCounter();
                        PrepareWriteThroughRequest(CacheRequestType::GetCoreWriteData(),
                            CacheRequestType::GetAddr(),
                            CacheRequestType::GetSbc(),
                            CacheRequestType::GetSbi());
                        m_FirstCycleOfNonCacheableRequest = true;
                        m_NextState = STATE_WT_REQUEST;
                    }
                    if (m_NextState == STATE_IDLE)
                    {
                        m_FSMstate = STATE_IDLE;
                    }
                }
            }
            if (CacheRequestType::GetCommand() == CP_CMD_READ)
            {
                m_NextResponse = CacheRequestType::GetResp();
                m_NextReady = CacheRequestType::GetReady();
                if (m_NextResponse == CP_AHB_OKAY && m_NextReady == CP_AHB_READY)
                {
                    CacheRequestType::SetDataReady();
                    CacheRequestType::SetResp(CP_AHB_OKAY);
                    CacheRequestType::SetReady(CP_AHB_READY);
                }
                if (CacheRequestType::GetLatency())
                {
                    CacheRequestType::DecLatency();
                    m_NextState = STATE_SAVE_LINE_AXI4;
                }
                else
                {
                    if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                        this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                    {
                        if (this->m_Cache.EvictRunning())
                        {
                            m_NextState = STATE_SAVE_LINE_AXI4;
                            break;
                        }
                        else
                        {
                            PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                                CacheRequestType::GetIndex(),
                                CacheRequestType::GetHprot(),
                                CacheRequestType::GetHmastlock());
                            this->m_Cache.SetEvictionDelayAxi4(1);
                            CacheRequestType::SetLatency(2);
                            m_NextState = STATE_R_SKIP_CYCLE_AXI4;
                        }
                    }
                    SaveCacheLineIntoCache(CacheRequestType::GetCacheLine(),
                        m_ReplaceWay,
                        CacheRequestType::GetIndex(),
                        CacheRequestType::GetTag());
                    if (CacheRequestType::GetInvalidateLoadedLine())
                    {
                        this->m_Cache.SetInvalid(m_ReplaceWay, CacheRequestType::GetIndex());
                    }
                    if (m_NextState == STATE_IDLE)
                    {
                        m_NextState = STATE_R_MISS_DONE;
                        m_FSMstate = STATE_R_MISS_DONE;
                    }
                }
            }
            break;
        case STATE_SAVE_LINE:
            this->m_Cache.SetInterfaceUsed();
            m_NextResponse = CacheRequestType::GetResp();
            m_NextReady = CacheRequestType::GetReady();
            if (m_NextResponse == CP_AHB_OKAY && m_NextReady == CP_AHB_READY)
            {
                CacheRequestType::SetDataReady();
                CacheRequestType::SetResp(CP_AHB_OKAY);
                CacheRequestType::SetReady(CP_AHB_READY);
            }
            if (CacheRequestType::GetLatency())
            {
                CacheRequestType::DecLatency();
                m_NextState = STATE_SAVE_LINE;
            }
            else
            {
                if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                    this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                {
                    if (this->m_Cache.EvictRunning())
                    {
                        m_NextState = STATE_SAVE_LINE;
                        break;
                    }
                    else
                    {
                        PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                            CacheRequestType::GetIndex(),
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock());
                        if (CacheRequestType::GetCommand() == CP_CMD_READ)
                        {
                            m_NextState = STATE_R_SKIP_CYCLE;
                        }
                        else
                        {
                            m_NextState = STATE_SKIP_CYCLE;
                        }
                    }
                }
                if (!m_RegistersInterface->IsWriteThroughEnabled() &&
                    CacheRequestType::GetCommand() == CP_CMD_WRITE)
                {
                    this->m_Cache.SetDirty(m_ReplaceWay, CacheRequestType::GetIndex());
                }
                SaveCacheLineIntoCache(CacheRequestType::GetCacheLine(),
                    m_ReplaceWay,
                    CacheRequestType::GetIndex(),
                    CacheRequestType::GetTag());
                if (CacheRequestType::GetInvalidateLoadedLine())
                {
                    this->m_Cache.SetInvalid(m_ReplaceWay, CacheRequestType::GetIndex());
                }
                if (m_RegistersInterface->IsWriteThroughEnabled() &&
                    CacheRequestType::GetCommand() == CP_CMD_WRITE)
                {   // send write request to target interface and change state
                    CacheRequestType::ResetCounter();
                    PrepareWriteThroughRequest(CacheRequestType::GetCoreWriteData(),
                        CacheRequestType::GetAddr(),
                        CacheRequestType::GetSbc(),
                        CacheRequestType::GetSbi());
                    m_NextState = STATE_WT_REQUEST;
                }
                if (m_NextState == STATE_IDLE && CacheRequestType::GetCommand() == CP_CMD_READ)
                {
                    m_NextState = STATE_R_MISS_DONE;
                    m_FSMstate = STATE_R_MISS_DONE;
                }
                else if (m_NextState == STATE_IDLE)
                {
                    m_FSMstate = STATE_IDLE;
                }
            }
            break;
        case STATE_R_SKIP_CYCLE_AXI4:
        case STATE_SKIP_CYCLE_AXI4:
            if (CacheRequestType::GetLatency())
            {
                CacheRequestType::DecLatency();
                m_NextState = m_FSMstate;
                break;
            }
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            m_FSMstate = m_FSMstate == STATE_R_SKIP_CYCLE_AXI4 ? STATE_R_MISS_DONE : STATE_IDLE;
            break;
        case STATE_R_SKIP_CYCLE:
        case STATE_SKIP_CYCLE:
            if (m_PreventRespReset)
            {
                m_PreventRespReset = false;
            }
            else
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_READY;
            }
            m_FSMstate = m_FSMstate == STATE_R_SKIP_CYCLE ? STATE_R_MISS_DONE : STATE_IDLE;
            this->m_Cache.SetInterfaceUsed();
            break;
        case STATE_I_ADDR_REQ:
            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }
            if (m_IsRequestPostponed)
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
            }
            m_NextState = m_FSMstate;
            break;
        // Clears valid bit. Response Ack.
        case STATE_I_ADDR:
        {
            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            this->m_Cache.SetInterfaceUsed();
            Index way = 0;
            if (this->m_Cache.IsHit(CacheRequestType::GetTag(), CacheRequestType::GetIndex(), way))
            {
                InvalidateCacheLine(way, CacheRequestType::GetIndex());
            }
            if (m_IsRequestPostponed)
            {
                m_IsRequestPostponed = false;
                m_FSMstate = STATE_IDLE;
                DoRequest(m_PostponedRequest);
                m_FSMstate = STATE_I_ADDR;
            }
            else
            {
                m_FSMstate = STATE_I_ADDR_DONE;
            }
        }
        break;
        // Clears cacheline in all ways.
        case STATE_I_LINE:
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            if (this->m_Cache.GetLinesPerSet() == 1 && (CacheRequestType::GetIndex() & 0x1) == 1)
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_READY;
                m_FSMstate = STATE_I_LINE_DONE;
                m_NextState = STATE_IDLE;
                break;
            }
            this->m_Cache.SetInterfaceUsed();
            for (Index i = 0; i < this->m_Cache.GetNumWays(); i++)
            {
                InvalidateCacheLine(i, CacheRequestType::GetIndex());
            }
            if (m_IsRequestPostponed)
            {
                m_IsRequestPostponed = false;
                m_FSMstate = STATE_IDLE;
                DoRequest(m_PostponedRequest);
                m_FSMstate = STATE_I_LINE;
            }
            else
            {
                m_FSMstate = STATE_I_LINE_DONE;
            }
            m_LastIndexUsed = CacheRequestType::GetIndex();
            break;
        // Clears cachelines. One line in all ways per clock cycle.
        // Response is Ack in first cycle and Idle afterwards.
        case STATE_RESET:
        case STATE_I_ALL:
            m_NextReady = m_IsRequestPostponed ? CP_AHB_WAIT : CP_AHB_READY;
            m_NextResponse = CP_AHB_OKAY;
            m_NextState = m_FSMstate;
            this->m_Cache.SetInterfaceUsed();
            for (Index i = 0; i < this->m_Cache.GetNumWays(); i++)
            {
                InvalidateCacheLine(i, CacheRequestType::GetCounter());
            }
            _DEBUG_LINE_OUTPUT("Invalidating line (" << CacheRequestType::GetCounter() << ")");
            CacheRequestType::IncCounter();
            if (CacheRequestType::LastLine())
            {
                m_LastIndexUsed = CacheRequestType::GetCounter() - 1;
                CacheRequestType::ResetCounter();
                m_NextState = STATE_IDLE;
                if (m_FSMstate != STATE_RESET)
                {
                    if (m_IsRequestPostponed)
                    {
                        m_IsRequestPostponed = false;
                        m_FSMstate = STATE_IDLE;
                        DoRequest(m_PostponedRequest);
                        m_FSMstate = STATE_I_ALL;
                    }
                    else
                    {
                        m_FSMstate = STATE_I_ALL_DONE;
                    }
                }
                else
                {
                    m_NextState = STATE_RESET_DONE;
                }
            }
            break;
        case STATE_R_HIT:
        {
            this->m_Cache.SetInterfaceUsed();
            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }
            m_IsLastIndexUsedValid = true;
            m_LastIndexUsed = CacheRequestType::GetIndex();
            Index way = 0;
            if (this->m_Cache.IsHit(CacheRequestType::GetTag(), CacheRequestType::GetIndex(), way))
            {
                m_HitCounter++;
                CacheRequestType::SetCoreData(this->m_Cache.GetData(way,
                    CacheRequestType::GetIndex(),
                    CacheRequestType::GetOffset()));
                CacheRequestType::SetDataReady();
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_READY;
            }
            else
            {
                // debugger may invalidate cache
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_FSMstate = STATE_R_BUFFER_D_DELAYED;
                m_NextState = STATE_R_BUFFER_D_DELAYED;
            }
        }
        break;
        case STATE_R_BUFFER_D_DELAYED:
            CacheRequestType::SetResp(CP_AHB_OKAY);
            CacheRequestType::SetReady(CP_AHB_WAIT);
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_WAIT;

            if (CacheRequestType::GetLatency())
            {
                this->m_Cache.SetInterfaceUsed();
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }

            m_ReplaceWay = GetReplaceWay(CacheRequestType::GetIndex());
            // fall through
        case STATE_R_BUFFER_D:
            CacheRequestType::SetResp(CP_AHB_OKAY);
            CacheRequestType::SetReady(CP_AHB_WAIT);
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_WAIT;

            if ((MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE && this->m_Cache.TargetUsed()) ||
                ((MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE ||
                     MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI) &&
                    !this->m_Cache.CanStartLineFillAxi4(CacheRequestType::GetNCAddr())))
            {
                this->m_Cache.SetInterfaceUsed();
                m_NextState = STATE_R_BUFFER_D;
            }
            else
            {   // load to cache
                m_MissCounter++;
                m_LastIndexUsed = CacheRequestType::GetIndex();
                m_IsLastIndexUsedValid = true;
                if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE)
                {
                    this->m_Cache.SetLineFillAddr(CacheRequestType::GetNCAddr());
                    this->m_Cache.SetLineFillHprot(CacheRequestType::GetHprot());
                    this->m_Cache.SetLineFillHmastlock(CacheRequestType::GetHmastlock());
                    this->m_Cache.StartLineFillAxi4Lite();

                    m_NextState = STATE_R_CL_FINISH;
                }
                else if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
                {
                    const AXIBurstType burstType = this->m_Cache.GetAXITargetBurstType();

                    if (burstType == CP_AXI_BURST_WRAP)
                    {
                        const auto startAddressTargetAligned = detail::AlignAddressToWordAddress(
                            CacheRequestType::GetAddr(),
                            TARGET_BYTES_PER_WORD);
                        this->m_Cache.SetLineFillAddresses({startAddressTargetAligned});
                        this->m_Cache.SetLineFillBurstType(burstType);
                        this->m_Cache.SetLineFillBurstLengths(
                            {static_cast<uint8_t>(this->m_Cache.GetTargetWordsPerLine() - 1)});
                        this->m_Cache.SetLineFillHprot(CacheRequestType::GetHprot());
                        this->m_Cache.SetLineFillHmastlock(CacheRequestType::GetHmastlock());
                        this->m_Cache.StartLineFillAxi4();
                        m_NextState = STATE_R_CL_FINISH;
                    }
                    else
                    {
                        const auto startAddressTargetAligned = detail::AlignAddressToWordAddress(
                            CacheRequestType::GetAddr(),
                            TARGET_BYTES_PER_WORD);

                        const auto cacheLineEndAddress = GetCacheLineEndAddress(
                            startAddressTargetAligned);
                        const auto cacheLineStartAddress = GetCacheLineStartAddress(
                            startAddressTargetAligned);

                        const Index numTargetWordsToCacheLineEnd = (cacheLineEndAddress -
                                                                       startAddressTargetAligned) /
                            TARGET_BYTES_PER_WORD;
                        const Index numTargetWordsFromCacheLineStart = (startAddressTargetAligned -
                                                                           cacheLineStartAddress) /
                            TARGET_BYTES_PER_WORD;

                        const auto lineFillBurstLengthsToCacheLineEnd = detail::PrepareBurstLengthsAxi4(
                            numTargetWordsToCacheLineEnd,
                            this->m_Cache.GetAXITargetBurstLength());
                        const auto lineFillBurstLengthsFromCacheLineStart = detail::PrepareBurstLengthsAxi4(
                            numTargetWordsFromCacheLineStart,
                            this->m_Cache.GetAXITargetBurstLength());
                        std::deque<uint8_t> lineFillBurstLengths(
                            lineFillBurstLengthsToCacheLineEnd.begin(),
                            lineFillBurstLengthsToCacheLineEnd.end());
                        lineFillBurstLengths.insert(lineFillBurstLengths.end(),
                            lineFillBurstLengthsFromCacheLineStart.begin(),
                            lineFillBurstLengthsFromCacheLineStart.end());

                        const auto lineFillBurstAddressesToCacheLineEnd =
                            detail::PrepareBurstAddressesAxi4<TARGET_BYTES_PER_WORD>(
                                startAddressTargetAligned,
                                lineFillBurstLengthsToCacheLineEnd);
                        const auto lineFillBurstAddressesFromCacheLineStart =
                            detail::PrepareBurstAddressesAxi4<TARGET_BYTES_PER_WORD>(
                                cacheLineStartAddress,
                                lineFillBurstLengthsFromCacheLineStart);
                        std::deque<codasip_address_t> lineFillBurstAddresses(
                            lineFillBurstAddressesToCacheLineEnd.begin(),
                            lineFillBurstAddressesToCacheLineEnd.end());
                        lineFillBurstAddresses.insert(lineFillBurstAddresses.end(),
                            lineFillBurstAddressesFromCacheLineStart.begin(),
                            lineFillBurstAddressesFromCacheLineStart.end());

                        this->m_Cache.SetLineFillAddresses(lineFillBurstAddresses);
                        this->m_Cache.SetLineFillBurstType(burstType);
                        this->m_Cache.SetLineFillBurstLengths(lineFillBurstLengths);
                        this->m_Cache.SetLineFillHprot(CacheRequestType::GetHprot());
                        this->m_Cache.SetLineFillHmastlock(CacheRequestType::GetHmastlock());
                        this->m_Cache.StartLineFillAxi4();
                        m_NextState = STATE_R_CL_FINISH;
                    }
                }
                else
                {
                    this->m_Cache.SetInterfaceUsed();
                    if (BURST_ENABLED)
                    {   // start a burst
                        this->m_Cache.TargetStartBurst(this->m_Cache.GetTargetBurstMode());
                    }
                    switch (this->m_Cache.TargetRequest(CP_CMD_READ,
                        CacheRequestType::GetNCAddr(),
                        0,
                        TARGET_BYTES_PER_WORD,
                        CacheRequestType::GetHprot(),
                        CacheRequestType::GetHmastlock()))
                    {
                        case CP_AHB_READY:   // request accepted
                            CacheRequestType::IncCounterTargetAddrRequest();
                            CacheRequestType::NCAddrIncWordWrap();
                            m_NextState = STATE_R_CL_FINISH;
                            break;
                        case CP_AHB_WAIT:
                            m_NextState = STATE_R_CL_REQUEST;
                            break;
                    }
                }

                if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI && !this->m_Cache.EvictRunning())
                {
                    if (this->m_Cache.IsDirty(m_ReplaceWay, CacheRequestType::GetIndex()) &&
                        this->m_Cache.IsValid(m_ReplaceWay, CacheRequestType::GetIndex()))
                    {
                        PutCacheLineIntoEvictionBuffer(m_ReplaceWay,
                            CacheRequestType::GetIndex(),
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock());
                        this->m_Cache.SetEvictionDelayAxi4(2);
                    }
                }
            }
            break;
        // This state writes data to cacheline. It writes data, that were presented previous
        // clock cycle so it directly moves to IDLE state, if write latency was met.
        // Response is Idle.
        case STATE_W_HIT_DELAYED:
            this->m_Cache.SetInterfaceUsed();
            if (CacheRequestType::GetLatency() > 1)
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }
            if (CacheRequestType::GetLatency() == 1)
            {
                CacheRequestType::DecLatency();
            }
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_WAIT;
            m_NextState = STATE_W_HIT;
            break;
        case STATE_W_HIT:
            m_HitCounter++;
            m_CurrentResponse = m_CurrentRequest;
            CacheRequestType::SetResp(CP_AHB_OKAY);
            CacheRequestType::SetReady(CP_AHB_READY);
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            if (m_RegistersInterface->IsWriteThroughEnabled())
            {
                PrepareNCRRequest(CP_CMD_WRITE,
                    CacheRequestType::GetAddr(),
                    CacheRequestType::GetSbc(),
                    CacheRequestType::GetSbi());
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
                {
                    HandleNonCacheableRequestAxi4();
                }
                else
                {
                    HandleNonCacheableRequest();
                }
            }
            else
            {
                m_NextState = STATE_IDLE;
            }
            break;
        case STATE_F_ADDR:
            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }

            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            m_NextState = m_FSMstate;
            if (!this->m_Cache.TargetUsed(true))   // evict running or CL read on AHB
            {
                this->m_Cache.SetInterfaceUsed();
                Index way = 0;
                if (this->m_Cache.IsHit(CacheRequestType::GetTag(), CacheRequestType::GetIndex(), way) &&
                    this->m_Cache.IsDirty(way, CacheRequestType::GetIndex()))
                {
                    if (!this->m_Cache.EvictRunning())
                    {
                        bool startEvictionImmediately = MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AHB_LITE
                            ? this->m_Cache.HasEvictionErrorOccuredAhb()
                            : false;
                        PutCacheLineIntoEvictionBuffer(way,
                            CacheRequestType::GetIndex(),
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock());
                        if (startEvictionImmediately)
                        {
                            this->m_Cache.EvictCacheLine();
                        }
                        m_FSMstate = STATE_F_ADDR_DONE;
                        m_NextState = STATE_IDLE;
                        m_LastIndexUsed = CacheRequestType::GetIndex();
                        m_IsLastIndexUsedValid = true;
                    }
                }
                else
                {
                    m_FSMstate = STATE_F_ADDR_DONE;
                    m_NextState = STATE_IDLE;
                    m_LastIndexUsed = CacheRequestType::GetIndex();
                    m_IsLastIndexUsedValid = true;
                }
            }
            break;
        case STATE_F_LINE:
            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }
            if (this->m_Cache.GetLinesPerSet() == 1 && (CacheRequestType::GetIndex() & 0x1) == 1)
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_READY;
                m_FSMstate = STATE_F_LINE_DONE;
                m_NextState = STATE_IDLE;
                break;
            }
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            m_NextState = m_FSMstate;
            this->m_Cache.SetInterfaceUsed();
            _DEBUG_LINE_OUTPUT("Flushing set(" << CacheRequestType::GetCounter() << ") of line (0x"
                                               << std::hex << CacheRequestType::GetIndex() << ")"
                                               << std::dec << " " << m_EvictDelay << " "
                                               << m_EvictionBufferEmpty);
            if (this->m_Cache.IsValid(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()) &&
                this->m_Cache.IsDirty(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()))
            {
                _DEBUG_LINE_OUTPUT("This line is valid and dirty");
                // eviction buffer is full
                if (this->m_Cache.EvictRunning())
                {
                    if (m_EvictionBufferEmpty)
                    {
                        m_EvictionBufferEmpty = false;
                    }
                    break;
                }
                else if (m_EvictDelay)
                {
                    if (!m_EvictionBufferEmpty)
                    {
                        PutCacheLineIntoEvictionBuffer(CacheRequestType::GetCounter(),
                            CacheRequestType::GetIndex(),
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock());
                        m_EvictionBufferEmpty = true;
                        m_EvictDelay = true;
                    }
                    else
                    {
                        m_EvictDelay = false;
                        break;
                    }
                }
                else
                {
                    PutCacheLineIntoEvictionBuffer(CacheRequestType::GetCounter(),
                        CacheRequestType::GetIndex(),
                        CacheRequestType::GetHprot(),
                        CacheRequestType::GetHmastlock());
                    this->m_Cache.EvictCacheLine();
                    m_EvictDelay = true;
                }
            }
            else
            {
                m_EvictionBufferEmpty = true;
                if (this->m_Cache.GetNumWays() == 1)
                {
                    CacheRequestType::SetLatency(1);
                }
            }
            CacheRequestType::IncCounter();
            if (CacheRequestType::GetCounter() == this->m_Cache.GetNumWays() ||
                CacheRequestType::GetIndex() >= this->m_Cache.GetLinesPerSet())
            {
                CacheRequestType::ResetCounter();
                m_FSMstate = STATE_F_LINE_DONE;
                m_NextState = STATE_IDLE;
                m_LastIndexUsed = CacheRequestType::GetIndex();
                m_IsLastIndexUsedValid = true;
            }
            break;
        case STATE_F_ALL:
            if (CacheRequestType::GetLatency())
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
                m_NextState = m_FSMstate;
                CacheRequestType::DecLatency();
                break;
            }
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            m_NextState = m_FSMstate;
            this->m_Cache.SetInterfaceUsed();
            _DEBUG_LINE_OUTPUT("Flushing set("
                << CacheRequestType::GetCounter() << ") of line (0x" << std::hex
                << CacheRequestType::GetIndex() << ")" << std::dec << " " << m_EvictDelay << " "
                << m_EvictionBufferEmpty << " " << m_PenultimateLineDirty << " " << m_LastLineDirty
                << " " << m_SkipSetLatency);
            if ((this->m_Cache.GetNumWays() == 2 &&
                    CacheRequestType::GetCounter() == this->m_Cache.GetNumWays() - 2) ||
                (this->m_Cache.GetNumWays() == 1 &&
                    CacheRequestType::GetIndex() == this->m_Cache.GetLinesPerSet() - 2))
            {
                if (!m_PenultimateLineDirtySet)
                {
                    m_PenultimateLineDirtySet = true;
                    if (this->m_Cache.IsValid(CacheRequestType::GetCounter(),
                            CacheRequestType::GetIndex()) &&
                        this->m_Cache.IsDirty(CacheRequestType::GetCounter(),
                            CacheRequestType::GetIndex()))
                    {
                        m_PenultimateLineDirty = this->m_Cache.EvictRunning();
                    }
                    else
                    {
                        m_PenultimateLineDirty = false;
                    }
                }
            }
            if ((this->m_Cache.GetNumWays() == 2 &&
                    CacheRequestType::GetCounter() == this->m_Cache.GetNumWays() - 1) ||
                (this->m_Cache.GetNumWays() == 1 &&
                    CacheRequestType::GetIndex() == this->m_Cache.GetLinesPerSet() - 1))
            {
                m_LastLineDirty = this->m_Cache.IsValid(CacheRequestType::GetCounter(),
                                      CacheRequestType::GetIndex()) &&
                    this->m_Cache.IsDirty(CacheRequestType::GetCounter(), CacheRequestType::GetIndex());
            }
            if (this->m_Cache.IsValid(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()) &&
                this->m_Cache.IsDirty(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()))
            {
                _DEBUG_LINE_OUTPUT("This line is valid and dirty");
                // eviction buffer is full
                if (this->m_Cache.EvictRunning())
                {
                    if (m_EvictionBufferEmpty)
                    {
                        m_EvictionBufferEmpty = false;
                    }
                    if (m_NumTargetUsedCycles > 0 && this->m_Cache.GetNumWays() == 1 &&
                        m_EvictDelay && !m_EvictionBufferEmpty)
                    {
                        m_DoNotSetLatency = true;
                    }
                    m_NumTargetUsedCycles++;
                    break;
                }
                else if (m_EvictDelay)
                {
                    if (!m_EvictionBufferEmpty)
                    {
                        PutCacheLineIntoEvictionBuffer(CacheRequestType::GetCounter(),
                            CacheRequestType::GetIndex(),
                            CacheRequestType::GetHprot(),
                            CacheRequestType::GetHmastlock());
                        m_EvictionBufferEmpty = true;
                        m_EvictDelay = true;
                        if (this->m_Cache.GetNumWays() == 1)
                        {
                            if (!m_DoNotSetLatency)
                            {
                                CacheRequestType::SetLatency(1);
                            }
                            else
                            {
                                if (m_NumTargetUsedCycles >= 3)
                                {
                                    m_SkipSetLatency = true;
                                }
                            }
                            m_DoNotSetLatency = false;
                        }
                    }
                    else
                    {
                        m_EvictDelay = false;
                        if (this->m_Cache.GetNumWays() == 1)
                        {
                            CacheRequestType::SetLatency(1);
                        }
                        break;
                    }
                    m_NumTargetUsedCycles = 0;
                }
                else
                {
                    PutCacheLineIntoEvictionBuffer(CacheRequestType::GetCounter(),
                        CacheRequestType::GetIndex(),
                        CacheRequestType::GetHprot(),
                        CacheRequestType::GetHmastlock());
                    this->m_Cache.EvictCacheLine();
                    m_EvictDelay = true;
                    if (this->m_Cache.GetNumWays() == 1 &&
                        CacheRequestType::GetIndex() == this->m_Cache.GetLinesPerSet() - 1)
                    {
                        m_SkipSetLatency = true;
                    }
                    m_NumTargetUsedCycles = 0;
                }
            }
            else
            {
                m_EvictionBufferEmpty = true;
                if (this->m_Cache.GetNumWays() == 1 && !m_SkipSetLatency)
                {
                    CacheRequestType::SetLatency(1);
                }
                m_SkipSetLatency = false;
            }
            CacheRequestType::IncCounter();
            if (this->m_Cache.GetNumWays() > 2 &&
                CacheRequestType::GetCounter() == this->m_Cache.GetNumWays() - 2)
            {
                if (this->m_Cache.IsValid(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()) &&
                    this->m_Cache.IsDirty(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()))
                {
                    m_PenultimateLineDirty = this->m_Cache.EvictRunning();
                }
                else
                {
                    m_PenultimateLineDirty = false;
                }
            }
            if (this->m_Cache.GetNumWays() > 2 &&
                CacheRequestType::GetCounter() == this->m_Cache.GetNumWays() - 1)
            {
                if (this->m_Cache.IsValid(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()) &&
                    this->m_Cache.IsDirty(CacheRequestType::GetCounter(), CacheRequestType::GetIndex()))
                {
                    m_LastLineDirty = true;
                }
                else
                {
                    m_LastLineDirty = false;
                }
            }
            if (CacheRequestType::GetCounter() == this->m_Cache.GetNumWays())
            {
                CacheRequestType::ResetCounter();
                CacheRequestType::IncIndex();
                m_PenultimateLineDirtySet = false;
                if (this->m_Cache.GetNumWays() != 1 &&
                    ((m_PenultimateLineDirty && !m_LastLineDirty) ||
                        (!m_PenultimateLineDirty && m_LastLineDirty)))
                {
                    CacheRequestType::SetLatency(1);
                }
                if (CacheRequestType::GetIndex() == this->m_Cache.GetLinesPerSet())
                {
                    if (this->m_Cache.GetNumWays() == 1 && !m_SkipSetLatency &&
                        !m_PenultimateLineDirty && !m_LastLineDirty)
                    {
                        m_NextState = STATE_F_ALL_DONE;
                    }
                    else
                    {
                        m_SkipSetLatency = false;
                        m_FSMstate = STATE_F_ALL_DONE;
                        m_NextState = STATE_IDLE;
                    }
                    m_LastIndexUsed = this->m_Cache.GetLinesPerSet() == 1
                        ? (!m_PenultimateLineDirty && !m_LastLineDirty)
                        : this->m_Cache.GetNumWays() == 1 ? CacheRequestType::GetIndex() - 1
                                                          : 0;
                    m_IsLastIndexUsedValid = true;
                }
            }
            break;
        case STATE_I_LINE_REQ:
        case STATE_I_ALL_REQ:
            if (m_IsRequestPostponed)
            {
                m_NextResponse = CP_AHB_OKAY;
                m_NextReady = CP_AHB_WAIT;
            }
            break;
        case STATE_R_MISS_DONE:
            m_FSMstate = STATE_IDLE;
            m_NextState = STATE_IDLE;
            // fall through
        default:
            CacheRequestType::Reset();
            m_NextResponse = CP_AHB_OKAY;
            m_NextReady = CP_AHB_READY;
            break;
    }
    _DEBUG_LINE_OUTPUT("######################################################");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::Reset()
{
    _DEBUG_LINE_OUTPUT_F("");
    this->m_Cache.ResetReplacementPolicy();
    if (m_IA || !CParams::IS_ENABLED)
    {
        m_FSMstate = STATE_IDLE;
        m_NextState = STATE_IDLE;
        InvalidateAllIA();
    }
    else
    {
        m_FSMstate = STATE_RESET;
        m_NextState = STATE_RESET;
    }
    m_NextResponse = CP_AHB_OKAY;
    m_NextReady = CP_AHB_READY;
    m_PreventRespReset = false;
    m_ErrorState = false;
    CacheRequestType::Reset();
    ClearCounters();
    m_CacheOperationData = 0;
    m_IsRequestAccepted = false;
    m_IsRequestPostponed = false;

    // Verification API variables
    m_LastSavedIndex = 0;
    m_LastSavedWay = 0;
    m_NewCacheLineSaved = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::ClockCycle()
{
    m_IsRequestAccepted = false;
    _DEBUG_LINE_OUTPUT("######################################################");
    _DEBUG_LINE_OUTPUT((IS_DCACHE ? "DATA CACHE" : "INSTRUCTION CACHE"));
#ifdef _DEBUG_CACHE_INTERFACE
    m_ClockCycleCounter++;
    _DEBUG_LINE_OUTPUT("Clock cycle: " << m_ClockCycleCounter);
    _DEBUG_LINE_OUTPUT("LFSR value: " << GetLFSRValue() % this->m_Cache.GetNumWays());
#endif
    Payload<Data> payload;
    _DEBUG_LINE_OUTPUT_F("");
    _DEBUG_LINE_OUTPUT("m_FSMstate '"
        << m_StateNames.at(m_FSMstate) << "' (" << static_cast<int>(m_FSMstate) << ") moved to '"
        << m_StateNames.at(m_NextState) << "' (" << static_cast<int>(m_NextState) << ")");
    _DEBUG_LINE_OUTPUT("Next response " << m_NextResponse);
    _DEBUG_LINE_OUTPUT("Last index used " << m_IsLastIndexUsedValid << " " << m_LastIndexUsed);

    if (m_FSMstate == STATE_I_ADDR_DONE)
    {
        m_LastIndexUsed = GetIndexFromAddr(m_HxData);
    }
    m_FSMstate = m_NextState;
    Fsm_step();
#ifdef _PRINT_CLINES
    _DEBUG_STREAM << "########################"
                  << (IS_ICACHE ? std::string("I CACHE") : std::string("D CACHE"))
                  << "##############################" << std::endl;
    _DEBUG_STREAM << std::hex;
    // print cache contents ways are separated by X X X, each line contains cacheline, cache words
    // are separated by underscores
    for (int i = 0; i < this->m_Cache.GetNumWays(); i++)
    {
        for (int j = 0; j < this->m_Cache.GetLinesPerSet(); j++)
        {
            if (!this->m_Cache.IsValid(i, j))
            {
                continue;
            }
            for (const auto& w : GetCacheLine(i, j))
            {
                _DEBUG_STREAM << w << "_";
            }
            _DEBUG_STREAM << "[[" << this->m_Cache.GetTag(i, j) << "]]"
                          << "((" << this->m_Cache.IsValid(i, j) << "))"
                          << "((" << this->m_Cache.IsDirty(i, j) << "))" << std::endl;
        }
        _DEBUG_STREAM << "X X X" << std::endl;
    }
    _DEBUG_STREAM << std::dec;
#endif
    m_HxData = 0;
    this->m_Cache.UpdateReplacementPolicy();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Calculate tag from address.
 *  \param  addr    Address from which the tag is calculated.
 *  \return Tag calculated from address.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::Tag
CacheInterface<T, M, CParams>::GetTagFromAddr(const codasip_address_t addr) const
{
    return detail::GetTagFromAddress(addr, this->m_Cache.GetLinesPerSet(), this->m_Cache.GetLineSize());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Calculate index from address.
 *  \param  addr    Address from which the index is calculated.
 *  \return Index calculated from address.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::LineIndex
CacheInterface<T, M, CParams>::GetIndexFromAddr(const codasip_address_t addr) const
{
    return detail::GetIndexFromAddress(addr,
        this->m_Cache.GetLinesPerSet(),
        this->m_Cache.GetLineSize());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Calculate offset from address.
 *  \param  addr    Address from which the offset is calculated.
 *  \return Offset calculated from address.
 */
template<class T, class M, class CParams>
CACHE_INLINE typename CacheInterface<T, M, CParams>::LineIndex
CacheInterface<T, M, CParams>::GetOffsetFromAddr(const codasip_address_t addr)
{
    return detail::GetOffsetFromAddress(addr, this->m_Cache.GetLineSize(), BYTES_PER_WORD);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
CACHE_INLINE void CacheInterface<T, M, CParams>::SetIa()
{
    m_FSMstate = m_NextState = STATE_IDLE;
    m_IA = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Initializes CacheRequest object as write-through request.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::PrepareWriteThroughRequest(const Data data,
    const codasip_address_t addr,
    const Index sbc,
    const Index sbi)
{
    PrepareNCRRequest(CP_CMD_WRITE, addr, sbc, sbi);
    CacheRequestType::SetCoreData(data);
    CacheRequestType::SetWriteDataReady();
    PrepareDataWritePayloadsAXI(data);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Initializes CacheRequest object as non-cacheable region request.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::PrepareNCRRequest(const Command cmd,
    const codasip_address_t addr,
    const Index sbc,
    const Index sbi)
{
    CacheRequestType::SetCmd(cmd);
    CacheRequestType::SetAddr(addr);
    CacheRequestType::SetNCAddr(addr);
    CacheRequestType::SetSbi(sbi);
    CacheRequestType::SetSbc(sbc);
    CacheRequestType::SetTag(GetTagFromAddr(addr));
    CacheRequestType::SetIndex(GetIndexFromAddr(addr));
    CacheRequestType::SetOffset(GetOffsetFromAddr(addr));
    if (cmd == CP_CMD_WRITE)
    {
        // target word wider than cache word, calculate needed subblock and align address
        if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
        {
            CacheRequestType::SetNCSbc(sbc);
            if (sbc || !sbi)
            {
                CacheRequestType::SetNCSbi(sbi + addr % TARGET_BYTES_PER_WORD);
            }
            CacheRequestType::AlignNCAddr(this->m_Cache.GetTargetWordAlign());
        }
        // sbi = 0, sbc = target word size
        else
        {   // target word narrower than cache word
            // EXPECT addr aligned to target word and cache word
            DEBUG_CONDITION(addr % BYTES_PER_WORD == 0 && addr % TARGET_BYTES_PER_WORD == 0);
            m_NCAWQueue = AWContainerType();
            for (codasip_address_t a = addr; a < addr + BYTES_PER_WORD; a += TARGET_BYTES_PER_WORD)
            {
                m_NCAWQueue.push(a);
            }
            CacheRequestType::SetNCSbi(sbi);
            CacheRequestType::SetNCSbc(0);
            CacheRequestType::ResetNCWMask();
            for (Index i = sbi; i < sbi + sbc; i++)
            {
                CacheRequestType::SetNCWMask(i);
            }
            CacheRequestType::SetNCSbiSbc();
            CacheRequestType::SetNcBiBcDataPhase();
        }
    }
    else
    {
        CacheRequestType::SetNCSbi(sbi);
        CacheRequestType::SetNCSbc(sbc < TARGET_BYTES_PER_WORD ? sbc : TARGET_BYTES_PER_WORD);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Prepare locally stored write data into non-cacheable region,
 *          prepare it for the target slave and proceed with write data phase.
 */
template<class T, class M, class CParams>
inline void
CacheInterface<T, M, CParams>::DoTargetWriteNCData(AHBReadyCode& ready, AHBResponseCode& resp)
{
    Data data = CacheRequestType::GetCoreWriteData();
    // prepare write data
    if (CACHE_DATA_BITS > TARGET_DATA_BITS)
    {
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE)
        {   // AXI ONLY
            Payload<TData> p;
            DEBUG_CONDITION(!m_NCWQueue.empty());
            p.set_data(m_NCWQueue.front().first);
            p.set_axi_wstrb(m_NCWQueue.front().second);
            this->m_Cache.TargetWriteData(p);
            ready = p.get_ahb_hready();
            resp = p.get_ahb_hresp();
        }
        else
        {
            TData targetData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(
                &data,
                0,
                CacheRequestType::GetTargetRequestBytesCount() - TARGET_BYTES_PER_WORD,
                TARGET_BYTES_PER_WORD);
            this->m_Cache.TargetWriteData(ready, resp, targetData);
        }
    }
    else if (CACHE_DATA_BITS < TARGET_DATA_BITS)
    {
        const auto targetAlignedAddress = detail::AlignAddressToWordAddress(
            CacheRequestType::GetAddr() + CacheRequestType::GetSbi(),
            TARGET_BYTES_PER_WORD);
        const auto cacheAlignedAddress = detail::AlignAddressToWordAddress(
            CacheRequestType::GetAddr() + CacheRequestType::GetSbi(),
            BYTES_PER_WORD);
        const auto addressOffset = cacheAlignedAddress - targetAlignedAddress;

        TData targetData = static_cast<TData>(data)
            << MasterInterface::get_amba_shift(addressOffset, BYTES_PER_WORD);
        this->m_Cache.TargetWriteData(ready, resp, targetData);
    }
    else
    {
        TData targetData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(&data,
            0,
            0,
            BYTES_PER_WORD);
        this->m_Cache.TargetWriteData(ready, resp, targetData);
    }
    if (ready == CP_AHB_READY || resp == CP_AHB_ERROR)
    {   // some data response received, error is handled elsewhere
        if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE && CACHE_DATA_BITS > TARGET_DATA_BITS)
        {
            DEBUG_CONDITION(!m_NCWQueue.empty());
            m_NCWQueue.pop();
        }
        CacheRequestType::IncCounter();
        if (CACHE_DATA_BITS > TARGET_DATA_BITS)
        {
            CacheRequestType::SetNcBiBcDataPhase();
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Handles writes to narrower or wider target interface.
 *  \param  args    Arguments forwarded to specific write functions.
 */
template<class T, class M, class CParams>
template<class... Args>
inline void CacheInterface<T, M, CParams>::DoTargetWrite(Args&&... args)
{
    if (TARGET_DATA_BITS >= CACHE_DATA_BITS)
    {
        DoWriteToWiderTarget(std::forward<Args>(args)...);
    }
    else
    {
        DoWriteToNarrowerTarget(std::forward<Args>(args)...);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Distinguish between write, debug write and debug load command.
 *  \param  cmd command to generate
 *  \param  data    data argument for command
 *  \param  address address argument for command
 *  \param  bc  byte count argument for command
 *  \param  hprot   protection argument for command
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::DoTargetWriteCommand(const Command cmd,
    const Data data,
    const codasip_address_t address,
    const Index bc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (cmd == CP_CMD_DWRITE)
    {
        this->m_Cache.TargetDwrite(data, address, bc);
    }
    else if (cmd == CP_CMD_LOAD)
    {
        this->m_Cache.TargetLoad(data, address, bc);
    }
    else if (cmd == CP_CMD_WRITE)
    {
        this->m_Cache.TargetWrite(data, address, bc, hprot, hmastlock);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
////
/**
 *  \brief  Writes data to equal or wider target interface.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::DoWriteToWiderTarget(const Command cmd,
    const TData data,
    const codasip_address_t addr,
    const Index sbc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DoTargetWriteCommand(cmd, data, addr, sbc, hprot, hmastlock);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Writes data to narrower target interface.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::DoWriteToNarrowerTarget(const Command cmd,
    const Data data,
    const codasip_address_t addr,
    const Index sbc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DEBUG_CONDITION(sbc <= TARGET_BYTES_PER_WORD || sbc % TARGET_BYTES_PER_WORD == 0);
    const Index numTargetWords = sbc <= TARGET_BYTES_PER_WORD ? 1 : sbc / TARGET_BYTES_PER_WORD;
    if (numTargetWords <= 1)
    {
        DoTargetWriteCommand(cmd, data, addr, sbc, hprot, hmastlock);
    }
    else
    {
        DEBUG_CONDITION(addr % TARGET_BYTES_PER_WORD == 0);   // address is target word aligned
        auto targetWords = detail::TransformCacheWordsToTargetWords<TData, ENDIANNESS, CData>({data});
        if (ENDIANNESS == CP_BIG_ENDIAN)
        {
            targetWords = TLine(targetWords.end() - numTargetWords, targetWords.end());
        }
        for (size_t i = 0; i < numTargetWords; ++i)
        {
            DoTargetWriteCommand(cmd,
                targetWords[i],
                addr + i * TARGET_BYTES_PER_WORD,
                TARGET_BYTES_PER_WORD,
                hprot,
                hmastlock);
            if (this->m_Cache.TargetLastAHBResponseCode() != CP_AHB_OKAY)
            {
                return;
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Puts cache line into the eviction buffer and prepares the eviction.
 *  \param  way A set in which the evicted cache line is located.
 *  \param  index   An index of evicted cache line.
 *  \param  hprot   Protection mode that should be used for eviction requests.
 *  \param  hmastlock   Master lock code that should be used for eviction requests.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::PutCacheLineIntoEvictionBuffer(const Index way,
    const LineIndex index,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    for (Index i = 0; i < this->m_Cache.GetWordsPerLine(); i++)
    {
        this->m_Cache.PushEvictWord(this->m_Cache.GetData(way, index, i));
    }
    this->m_Cache.SetEvictAddr((this->m_Cache.GetTag(way, index) << this->m_Cache.GetTagShift()) +
        (index << this->m_Cache.GetIndexShift()));
    this->m_Cache.SetEvictHprot(hprot);
    this->m_Cache.SetEvictHmastlock(hmastlock);

    if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE)
    {
        this->m_Cache.StartEvictionAxi4Lite();
    }
    else if (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI)
    {
        this->m_Cache.StartEvictionAxi4();
    }
    else
    {
        this->m_Cache.StartEvictionAhb();
    }
    this->m_Cache.SetClear(way, index);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::SaveCacheLineIntoCache(const CLine& cacheLine,
    const Index way,
    const LineIndex index,
    const Tag tag)
{
    //  Verification API
    m_LastSavedIndex = index;
    m_LastSavedWay = way;
    m_NewCacheLineSaved = true;

    this->m_Cache.SaveCacheLine(way, index, cacheLine);
    this->m_Cache.SetValid(way, index);
    this->m_Cache.SetTag(way, index, tag);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::SetDirty(const Index way, const LineIndex index)
{
    this->m_Cache.SetDirty(way, index);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
inline Index CacheInterface<T, M, CParams>::GetReplaceWay(const LineIndex index) const
{
    return this->m_Cache.GetReplaceWay(index);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
inline Index CacheInterface<T, M, CParams>::GetReplaceWay() const
{
    return m_ReplaceWay;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class CParams>
inline uint16_t CacheInterface<T, M, CParams>::GetLFSRValue() const
{
    return this->m_Cache.GetLFSRValue();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Updates the data in cached cache line.
 *  \param  data    A new data.
 *  \param  way A set where the to be updated cache line is stored.
 *  \param  index   An index under which the to be updated cache line is stored.
 *  \param  offset  A cache line offset of a word that is updated.
 *  \param  sbi Byte index within the cache line word.
 *  \param  sbc Number of bytes that are updated.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::UpdateCacheLineInCache(const Data data,
    const Index way,
    const LineIndex index,
    const LineIndex offset,
    const Index sbi,
    const Index sbc)
{
    this->m_Cache.SetData(data, way, index, offset, sbi, sbc);
    if (!m_RegistersInterface->IsWriteThroughEnabled())
    {
        this->m_Cache.SetDirty(way, index);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Invalidates cache line and clears dirty flag.
 *  \param  way A set in which the invalidated cache line is located.
 *  \param  index   An index of invalidated cache line.
 */
template<class T, class M, class CParams>
inline void CacheInterface<T, M, CParams>::InvalidateCacheLine(const Index way, const LineIndex index)
{
    this->m_Cache.SetInvalid(way, index);
    this->m_Cache.SetClear(way, index);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Prepares queue with data for AXI data write signals of non-cacheable write requests to
 *          narrow lower level memory.
 *  \param  data    Data that is to be written.
 */
template<class T, class M, class _Params>
inline void CacheInterface<T, M, _Params>::PrepareDataWritePayloadsAXI(const Data& data)
{
    if (CacheRequestType::GetCommand() == CP_CMD_WRITE &&
        (MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI_LITE ||
            MASTER_INTERFACE_PROTOCOL == CP_PROTOCOL_AXI))
    {
        m_NCWQueue = WContainerType();
        if (TARGET_BYTES_PER_WORD >= BYTES_PER_WORD)
        {
            const auto targetAlignedAddress = detail::AlignAddressToWordAddress(
                CacheRequestType::GetAddr() + CacheRequestType::GetSbi(),
                TARGET_BYTES_PER_WORD);
            const auto sbi = CacheRequestType::GetAddr() + CacheRequestType::GetSbi() -
                targetAlignedAddress;
            const auto wstrobe = CacheMasterInterface<typename _Params::master_interface_t,
                _Params::IS_WRITABLE>::template CreateWriteStrobe<typename Payload<TData>::write_strobe_type>(sbi,
                CacheRequestType::GetSbc());

            const auto cacheAlignedAddress = detail::AlignAddressToWordAddress(
                CacheRequestType::GetAddr(),
                BYTES_PER_WORD);
            CacheWordsPerTargetWordContainer cacheWords;
            cacheWords.fill(0);
            cacheWords[(cacheAlignedAddress - targetAlignedAddress) / BYTES_PER_WORD] = data;

            const auto targetData = detail::TransformCacheWordsToTargetWords<TData, ENDIANNESS>(
                cacheWords.begin(),
                cacheWords.end())[0];

            m_NCWQueue.push({targetData, wstrobe});
        }
        else
        {
            Data mask = Interface<T>::create_amba_mask(CacheRequestType::GetSbi(),
                CacheRequestType::GetSbc());
            for (Index bi = 0; bi < BYTES_PER_WORD; bi += TARGET_BYTES_PER_WORD)
            {
                TData targetData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(
                    &data,
                    0,
                    bi,
                    TARGET_BYTES_PER_WORD);
                TData maskData = Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(
                    &mask,
                    0,
                    bi,
                    TARGET_BYTES_PER_WORD);
                typename Payload<TData>::write_strobe_type wstrobe = 0;
                for (Index i = 0; i < TARGET_BYTES_PER_WORD; ++i)
                {
                    wstrobe |= (maskData >> (i * BYTE_BITS)) & 0xFF ? (0x1 << i) : 0x0;
                }
                WContainerDataType writeDataWithStrobe = {targetData, wstrobe};
                m_NCWQueue.push(writeDataWithStrobe);
            }
        }
    }
}

}   // namespace resources
}   // namespace codasip

#ifdef _DEBUG_LINE_OUTPUT
#    undef _DEBUG_LINE_OUTPUT
#endif
#ifdef _DEBUG_LINE_OUTPUT_F
#    undef _DEBUG_LINE_OUTPUT_F
#endif

#endif   // SIMULATOR_RESOURCES_CSR_CACHE_INTERFACE_H_
