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

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_REQUEST_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_REQUEST_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_unaligned_generic.h"
#include "simulator/resources/csr_unaligned_native.h"
#include "utility/codasiputils.h"

namespace codasip {
namespace resources {

#define CACHE_INLINE inline
/**
 *  \class  codasip::resources::CacheRequest
 *  \brief  Request related data for use during CA simulation.
 *  \tparam _Params Generated parameters of the cache.
 */
template<class _Params, class M>
class CacheRequest
{
public:
    /// \copydoc codasip::resources::Cache::CACHE_DATA_BITS
    static const Index CACHE_DATA_BITS = _Params::WORD_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::BYTE_BITS
    static const Index BYTE_BITS = _Params::LAU_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::WORDS_PER_WORD
    static const Index BYTES_PER_WORD = CACHE_DATA_BITS / BYTE_BITS;
    /// \copydoc codasip::resources::Cache::ENDIANNESS
    static const Endianness ENDIANNESS = static_cast<Endianness>(_Params::ENDIANNESS);

    /// Data type of cache interface.
    typedef typename _Params::data_type Data;
    /// Data type of cache target.
    typedef typename _Params::target_payload_t TData;
    /// Container type of cacheline.
    typedef typename std::vector<Data> CLine;
    /// Line index of entry in cache.
    typedef codasip_address_t LineIndex;
    CacheRequest(M& cacheCore);
    /**
     *  \brief Clears loaded cacheline.
     */
    ~CacheRequest();
    /**
     * \brief Resets all members to zero.
     */
    void Reset();
    /**
     *  \{
     *  \brief  Reset methods for various counters and members.
     */
    void ResetCounter();
    void ResetCacheData();
    void ResetDataReady();
    void ResetNCWMask();
    /**
     *  \}
     *  \{
     *  \brief  Mutators.
     */
    void SetAddr(const codasip_address_t);
    void SetNCAddr(const codasip_address_t);
    void SetSbi(const Index);
    void SetNCSbi(const Index);
    void SetSbc(const Index);
    void SetNCSbc(const Index);
    void SetCmd(const Command);
    void SetResp(const AHBResponseCode);
    void SetReady(const AHBReadyCode);
    void SetTag(const LineIndex);
    void SetOffset(const LineIndex);
    void SetIndex(const LineIndex);
    void SetLatency(const Index);
    void SetCoreData(const Data);
    void SetWriteDataReady(const Data);
    void SetCacheLineWord(const Data);
    void SetCacheLineWord(const Data, const LineIndex offset);
    void SetDataReady();
    void SetWriteDataReady();
    void SetNCWMask(const Index);
    // For NC Write, uses NCW mask
    void SetNCSbiSbc();
    void SetNcBiBcDataPhase();
    void SetFinished();
    void SetTargetErrorCount();
    void SetHprot(const uint8_t hprot);
    void SetHmastlock(const uint8_t hmastlock);
    /**
     *  \}
     *  \{
     *  \brief  Accessors.
     */
    Index GetAddrModTBPW() const;
    codasip_address_t GetAddr() const;
    codasip_address_t GetNCAddr() const;
    Index GetSbi() const;
    Index GetNextWordSbi() const;
    Index GetNCSbi() const;
    Index GetNCSbiDataPhase() const;
    Index GetSbc() const;
    Index GetNCSbc() const;
    Index GetNCSbcDataPhase() const;
    Command GetCommand() const;
    AHBResponseCode GetResp() const;
    AHBReadyCode GetReady() const;
    Index GetCounter() const;
    Index GetTargetBytesCount() const;
    Index GetTargetRequestBytesCount() const;
    Index GetTargetRequestCount() const;
    Index GetTargetErrorCount() const;
    Index GetTargetRespCount() const;
    Index GetLatency() const;
    Data GetCacheLineWord() const;
    Data GetCacheLineWord(const LineIndex offset) const;
    Data GetCoreData();
    Data GetCoreWriteData() const;
    const CLine& GetCacheLine() const;
    LineIndex GetTag() const;
    LineIndex GetIndex() const;
    LineIndex GetOffset() const;
    Index GetCumulativeSbi() const;
    Index GetCumulativeSbiDataPhase() const;
    bool NotFinished() const;
    uint8_t GetHprot() const;
    uint8_t GetHmastlock() const;
    /// Return number of cache line words loaded.
    Index GetCacheLineWordsLoaded() const;
    /// \}
    /// Moves cache data to core data.
    void CacheToCore();
    /**
     *  \{
     *  \brief  Methods used to increment various counters.
     */
    void IncCounter();
    void IncIndex();
    void IncCounterTargetAddrRequest();
    void IncCounterTargetError();
    void IncCounterTargetResp();
    /**
     *  \}
     *  \{
     *  \brief  Methods used to decrement various counters.
     */
    void DecCounter();
    void DecLatency();
    void DecCounterTargetAddrRequest();
    void DecCounterTargetError();
    /// \}

    /**
     *  \brief  Clears LSBs of private member m_NCAddr.
     *  \param  wordBits Number of LSBs to clear.
     */
    void AlignNCAddr(const Index wordBits);
    /**
     *  \brief  Moves private member m_NCAddr to next target word.
     */
    void NCAddrIncWord();
    /**
    *  \brief  Moves private member m_NCAddr to next target word & wrap around cache line.
    */
    void NCAddrIncWordWrap();
    /**
     *  \brief  Moves private member m_NCAddr to previous target word.
     */
    void NCAddrDecWord();
    /**
     *  \brief  Moves private member m_NCAddr to previous target word & wrap around cache line.
     */
    void NCAddrDecWordWrap();
    /**
     *  \brief  Concatenates data to private member m_CacheData, adding MSBs.
     *  \param  data Data to concatenate.
     */
    void ConcatenateCacheData(const TData data);
    /**
     *  \brief  Pushes word to cacheline container m_CacheLine.
     *  \param  word Word to push.
     */
    void PushWord(const Data word);
    /**
     *  \brief  Pushes m_CacheData to cacheline container m_CacheLine.
     */
    void PushCacheData();
    /**
     *  \brief  Informs whether or not all cachelines have been processed.
     *  \return True if m_Counter == SET_LINE_COUNT, false otherwise.
     */
    bool LastLine() const;
    /**
     *  \brief  Used when cache word size is bigger than target word size.
     *          Informs whether or not enough target words have been loaded.
     *  \return True if m_Counter == TARGET_WORDS_PER_CACHE_WORD, false otherwise.
     */
    bool LoadedCacheWord() const;
    /**
     *  \brief  Clears LSBs of address to align it to cacheline size.
     *  \param  addrToCache Address to be aligned.
     *  \return Address aligned to cacheline size.
     */
    codasip_address_t GetCachelineAddr(const codasip_address_t addrToCache) const;
    /**
     *  \brief  Changes Nth bit of address to X.
     *  \param  addr Address to be modified.
     *  \param  n Bit to modify.
     *  \param  value New value of selected bit.
     */
    static void ChangeNthBitToXinAddr(codasip_address_t& addr, const int n, const int value);
    /**
     * \brief  Used to check whether or not are data ready to be read by master.
     * \return m_DataReady value.
     */
    bool DataReady() const;
    /**
     * \brief  Used to check whether or not are data ready to be written.
     * \return m_WriteDataReady value.
     */
    bool WriteDataReady() const;
    /// Sets invalidate loaded line flag to true.
    void SetInvalidateLoadedLine();
    /// Returns the value of invalidate loaded line flag.
    bool GetInvalidateLoadedLine() const;

    /**
     *  \brief  Inserts target data to cache data , adding MSBs.
     *  \param [in]     targetData Source data from memory to add.
     *  \param [in]     shiftBytes Target data offset within the cache word.
     */
    void DoConcatenateCacheData(const TData targetData, const Index shiftBytes);
    /**
     *  \brief  Concatenates cache data from target, adding MSBs.
     *  \param [in,out] cacheData Data to concatenate.
     *  \param [in]     targetData Source data from memory to add.
     *  \param [in]     counter Round index.
     */
    static void DoConcatenateCacheData(Data& cacheData, const TData targetData, const Index counter);

protected:
    enum
    {
        /// Target data bit width.
        TARGET_DATA_BITS = _Params::TARGET_WORD_BIT_WIDTH,
        /// Target LAUs per target word.
        TARGET_BYTES_PER_WORD = TARGET_DATA_BITS / BYTE_BITS,
        /// How many target words fit into one cache word.
        TARGET_WORDS_PER_CACHE_WORD = CACHE_DATA_BITS / TARGET_DATA_BITS,
        /// How many cache words fit into one target word.
        CACHE_WORDS_PER_TARGET_WORD = TARGET_DATA_BITS / CACHE_DATA_BITS
    };

private:
    Index GetActualWordIndex() const;
    void DoSetNCBiBc(Index&, Index&, Index&, const Index) const;

protected:
    /// Cache core
    M& m_Cache;

private:
    /// Request address.
    codasip_address_t m_Addr;
    /// Noncachable address - address aligned to either target word size or cache line size.
    codasip_address_t m_NCAddr;
    /// Offset into target word.
    Index m_AddrModTBPW;
    /// Request SBI.
    Index m_Sbi;
    /// Recalculated SBI used for some target requests.
    Index m_NCSbi;
    /// Recalculated byte index used for non-cacheable access during data phase (required by AXI).
    Index m_NCSbiDataPhase;
    /// Request SBC.
    Index m_Sbc;
    /// Recalculated SBC used for some target requests.
    Index m_NCSbc;
    /// Recalculated byte count used for non-cacheable access during data phase (required by AXI).
    Index m_NCSbcDataPhase;
    /// Request type.
    Command m_Command;
    /// Precalculated response code allowing merge of some FSM states.
    AHBResponseCode m_AHBResponseCode;
    /// Precalculated ready code allowing merge of some FSM states.
    AHBReadyCode m_AHBReadyCode;
    /// Generic counter.
    Index m_Counter;
    /// Number of accepted address requests by the target memory sub-system.
    Index m_TargetAddrCounter;
    /// Number of error responses needed to receive.
    Index m_TargetErrCounter;
    /// Number of received responses for write.
    Index m_TargetRespCounter;
    /// Cache write/read latency counter.
    Index m_Latency;
    /// Cache word size data, used in ifinsh method and as temporary cache word storage.
    Data m_CacheData;
    /// Cache word size data, used in ofinsh method.
    Data m_CoreData;
    /// Cacheline container.
    CLine m_CacheLine;
    /// Actual number of words loaded in the actual cache line. Each PushWord() call increments
    /// this value.
    Index m_CacheLineWordsLoaded;
    /// Tag parsed from request addr.
    LineIndex m_Tag;
    /// Offset parsed from request addr. (number of cache words).
    LineIndex m_Offset;
    /// Offset aligned to whole target words.
    LineIndex m_AlignedOffset;
    /// Index parsed from request addr.
    LineIndex m_Index;
    /// Data ready to be read.
    bool m_DataReady;
    /// Data ready to be written.
    bool m_WriteDataReady;
    /// Mask for non-cacheable region write, used when ASIP data are wider than RAM data.
    bool m_NCWriteMask[BYTES_PER_WORD];
    /// Request finished (still might need to finish loading cache line).
    bool m_Finished;
    /// Cumulative sbi for NC region write in case of cache word being wider than target word.
    Index m_CumulativeSbi;
    /// Cumulative byte index for NC region write in case of cache word being wider than target word
    /// (required by AXI).
    Index m_CumulativeSbiDataPhase;
    /// Do not set loaded line valid after finishing.
    bool m_InvalidateLoadedLine;
    /// Request hprot.
    uint8_t m_Hprot;
    /// Request hmastlock.
    uint8_t m_Hmastlock;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE CacheRequest<_Params, M>::CacheRequest(M& cacheCore)
  : m_Cache(cacheCore)
  , m_Addr(0)
  , m_NCAddr(0)
  , m_AddrModTBPW(0)
  , m_Sbi(0)
  , m_NCSbi(0)
  , m_NCSbiDataPhase(0)
  , m_Sbc(0)
  , m_NCSbc(0)
  , m_NCSbcDataPhase(0)
  , m_Command(CP_CMD_NONE)
  , m_AHBResponseCode(CP_AHB_OKAY)
  , m_AHBReadyCode(CP_AHB_READY)
  , m_Counter(0)
  , m_TargetAddrCounter(0)
  , m_TargetErrCounter(0)
  , m_TargetRespCounter(0)
  , m_Latency(0)
  , m_CacheData(0)
  , m_CoreData(0)
  , m_CacheLineWordsLoaded(0)
  , m_Tag(0)
  , m_Offset(0)
  , m_AlignedOffset(0)
  , m_Index(0)
  , m_DataReady(false)
  , m_WriteDataReady(false)
  , m_Finished(false)
  , m_CumulativeSbi(0)
  , m_CumulativeSbiDataPhase(0)
  , m_InvalidateLoadedLine(false)
{
    m_CacheLine.resize(m_Cache.GetWordsPerLine());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE CacheRequest<_Params, M>::~CacheRequest()
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::Reset()
{
    m_Addr = 0;
    m_NCAddr = 0;
    m_AddrModTBPW = 0;
    m_Sbi = 0;
    m_NCSbi = 0;
    m_NCSbiDataPhase = 0;
    m_Sbc = 0;
    m_NCSbc = m_Cache.GetWordsPerLine();
    m_NCSbcDataPhase = m_Cache.GetWordsPerLine();
    m_AHBResponseCode = CP_AHB_OKAY;
    m_AHBReadyCode = CP_AHB_READY;
    m_CoreData = 0;
    m_Tag = 0;
    m_Offset = 0;
    m_AlignedOffset = 0;
    m_Index = 0;
    m_Latency = 0;
    m_CumulativeSbi = 0;
    m_CumulativeSbiDataPhase = 0;
    m_Finished = false;
    m_WriteDataReady = false;
    m_Command = CP_CMD_NONE;
    ResetCounter();
    ResetCacheData();
    ResetDataReady();
    m_CacheLineWordsLoaded = 0;
    m_InvalidateLoadedLine = false;
    m_Hprot = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::ResetNCWMask()
{
    for (Index i = 0; i < BYTES_PER_WORD; i++)
    {
        m_NCWriteMask[i] = false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::ResetCounter()
{
    m_Counter = 0;
    m_TargetAddrCounter = 0;
    m_TargetErrCounter = 0;
    m_TargetRespCounter = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::ResetCacheData()
{
    m_CacheData = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::ResetDataReady()
{
    m_DataReady = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::NCAddrIncWord()
{
    m_NCAddr += TARGET_BYTES_PER_WORD;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::NCAddrIncWordWrap()
{
    NCAddrIncWord();
    // wrap around, start a new burst
    if (m_NCAddr % m_Cache.GetLineSize() == 0)
    {
        m_NCAddr -= m_Cache.GetLineSize();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::NCAddrDecWord()
{
    m_NCAddr -= TARGET_BYTES_PER_WORD;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::NCAddrDecWordWrap()
{
    // wrap around, start a new burst
    if (m_NCAddr % m_Cache.GetLineSize() == 0)
    {
        m_NCAddr += m_Cache.GetLineSize();
    }
    NCAddrDecWord();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::AlignNCAddr(const Index wordBits)
{
    for (Index i = 0; i < wordBits; i++)
    {
        ChangeNthBitToXinAddr(m_NCAddr, i, 0);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetNCWMask(const Index pos)
{
    m_NCWriteMask[pos] = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetAddr(const codasip_address_t addr)
{
    m_Addr = addr;
    m_AddrModTBPW = (Index)(addr % TARGET_BYTES_PER_WORD);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetNCAddr(const codasip_address_t addr)
{
    m_NCAddr = addr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetSbi(const Index sbi)
{
    m_Sbi = sbi;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetNCSbi(const Index sbi)
{
    m_NCSbi = sbi;
    m_NCSbiDataPhase = sbi;
    m_CumulativeSbi = sbi;
    m_CumulativeSbiDataPhase = sbi;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetSbc(const Index sbc)
{
    m_Sbc = sbc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetNCSbc(const Index sbc)
{
    m_NCSbc = sbc;
    m_NCSbcDataPhase = sbc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetNCSbiSbc()
{
    DoSetNCBiBc(m_CumulativeSbi, m_NCSbi, m_NCSbc, GetTargetRequestBytesCount());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetNcBiBcDataPhase()
{
    DoSetNCBiBc(m_CumulativeSbiDataPhase, m_NCSbiDataPhase, m_NCSbcDataPhase, GetTargetBytesCount());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetCmd(const Command command)
{
    m_Command = command;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetResp(const AHBResponseCode response)
{
    m_AHBResponseCode = response;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetReady(const AHBReadyCode value)
{
    m_AHBReadyCode = value;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetFinished()
{
    m_Finished = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
inline void CacheRequest<_Params, M>::SetTargetErrorCount()
{   // store number of additional error responses needed to receive
    m_TargetErrCounter = m_TargetAddrCounter - m_Counter;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
inline void CacheRequest<_Params, M>::SetHprot(const uint8_t hprot)
{
    m_Hprot = hprot;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
inline void CacheRequest<_Params, M>::SetHmastlock(const uint8_t hmastlock)
{
    m_Hmastlock = hmastlock;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::ConcatenateCacheData(const TData data)
{
    DoConcatenateCacheData(m_CacheData, data, m_Counter - 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void
CacheRequest<_Params, M>::DoConcatenateCacheData(const TData targetData, const Index shiftBytes)
{
    Data tmp = targetData;
    if (ENDIANNESS == CP_LITTLE_ENDIAN)
    {
        m_CacheData |= LeftShift(tmp, shiftBytes * BYTE_BITS);
    }
    else
    {
        m_CacheData |= LeftShift(tmp, (BYTES_PER_WORD - shiftBytes) * BYTE_BITS);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::DoConcatenateCacheData(Data& cacheData,
    const TData targetData,
    const Index counter)
{
    Data tmp = targetData;
    if (ENDIANNESS == CP_LITTLE_ENDIAN)
    {
        cacheData += LeftShift(tmp, (counter * TARGET_DATA_BITS) % CACHE_DATA_BITS);
    }
    else
    {
        cacheData = LeftShift(cacheData, TARGET_DATA_BITS);
        cacheData |= tmp;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetCoreData(const Data data)
{
    m_CoreData = data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::IncCounter()
{
    m_Counter++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::DecCounter()
{
    m_Counter--;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::IncCounterTargetAddrRequest()
{
    m_TargetAddrCounter++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::IncCounterTargetError()
{
    m_TargetErrCounter++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::DecCounterTargetAddrRequest()
{
    m_TargetAddrCounter--;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::DecCounterTargetError()
{
    m_TargetErrCounter--;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::IncCounterTargetResp()
{
    m_TargetRespCounter++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::PushWord(const Data data)
{
    m_CacheLine[GetActualWordIndex()] = data;
    m_CacheLineWordsLoaded++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::PushCacheData()
{
    m_CacheLine[GetActualWordIndex()] = m_CacheData;
    m_CacheLineWordsLoaded++;
    ResetCacheData();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetTag(const LineIndex tag)
{
    m_Tag = tag;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetOffset(const LineIndex offset)
{
    m_Offset = offset;
    if (TARGET_DATA_BITS > CACHE_DATA_BITS)
    {
        m_AlignedOffset = (m_Offset / CACHE_WORDS_PER_TARGET_WORD) * CACHE_WORDS_PER_TARGET_WORD;
    }
    else
    {
        m_AlignedOffset = m_Offset;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetIndex(const LineIndex index)
{
    m_Index = index;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetDataReady()
{
    m_DataReady = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetWriteDataReady()
{
    m_WriteDataReady = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::IncIndex()
{
    m_Index++;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::DecLatency()
{
    m_Latency--;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetLatency(const Index latency)
{
    m_Latency = latency;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE codasip_address_t CacheRequest<_Params, M>::GetAddr() const
{
    return m_Addr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetAddrModTBPW() const
{
    return m_AddrModTBPW;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE codasip_address_t CacheRequest<_Params, M>::GetNCAddr() const
{
    return m_NCAddr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetSbi() const
{
    return m_Sbi;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetNextWordSbi() const
{
    return m_Counter * m_NCSbc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE bool CacheRequest<_Params, M>::NotFinished() const
{
    return !m_Finished;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE uint8_t CacheRequest<_Params, M>::GetHprot() const
{
    return m_Hprot;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE uint8_t CacheRequest<_Params, M>::GetHmastlock() const
{
    return m_Hmastlock;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetCacheLineWordsLoaded() const
{
    return m_CacheLineWordsLoaded;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetNCSbi() const
{
    return m_NCSbi;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetNCSbiDataPhase() const
{
    return m_NCSbiDataPhase;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetSbc() const
{
    return m_Sbc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetNCSbc() const
{
    return m_NCSbc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetNCSbcDataPhase() const
{
    return m_NCSbcDataPhase;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Command CacheRequest<_Params, M>::GetCommand() const
{
    return m_Command;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE AHBResponseCode CacheRequest<_Params, M>::GetResp() const
{
    return m_AHBResponseCode;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE AHBReadyCode CacheRequest<_Params, M>::GetReady() const
{
    return m_AHBReadyCode;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetCounter() const
{
    return m_Counter;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetTargetBytesCount() const
{
    return m_Counter * TARGET_BYTES_PER_WORD;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetTargetRequestBytesCount() const
{
    return GetTargetRequestCount() * TARGET_BYTES_PER_WORD;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetTargetRequestCount() const
{
    return m_TargetAddrCounter;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetTargetErrorCount() const
{
    return m_TargetErrCounter;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetTargetRespCount() const
{
    return m_TargetRespCounter;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE bool CacheRequest<_Params, M>::LastLine() const
{
    return m_Counter == m_Cache.GetLinesPerSet();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE bool CacheRequest<_Params, M>::LoadedCacheWord() const
{
    Index value = TARGET_WORDS_PER_CACHE_WORD != 0 ? m_Counter % TARGET_WORDS_PER_CACHE_WORD : 0;
    return value == 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetLatency() const
{
    return m_Latency;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::CacheToCore()
{
    m_CoreData = m_CacheData;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetCumulativeSbi() const
{
    return m_CumulativeSbi;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetCumulativeSbiDataPhase() const
{
    return m_CumulativeSbiDataPhase;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE typename CacheRequest<_Params, M>::Data CacheRequest<_Params, M>::GetCoreData()
{
    return Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(&m_CoreData,
        0,
        m_Sbi,
        m_Sbc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE typename CacheRequest<_Params, M>::Data CacheRequest<_Params, M>::GetCoreWriteData() const
{
    return m_CoreData;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE const typename CacheRequest<_Params, M>::CLine&
CacheRequest<_Params, M>::GetCacheLine() const
{
    return m_CacheLine;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE typename CacheRequest<_Params, M>::Data CacheRequest<_Params, M>::GetCacheLineWord() const
{
    return GetCacheLineWord(m_Offset);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE typename CacheRequest<_Params, M>::Data
CacheRequest<_Params, M>::GetCacheLineWord(const LineIndex offset) const
{
    return m_CacheLine.at(offset);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetCacheLineWord(const Data data)
{
    SetCacheLineWord(data, m_Offset);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetCacheLineWord(const Data data, const LineIndex offset)
{
    m_CacheLine.at(offset) = data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE typename CacheRequest<_Params, M>::LineIndex CacheRequest<_Params, M>::GetTag() const
{
    return m_Tag;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE typename CacheRequest<_Params, M>::LineIndex CacheRequest<_Params, M>::GetIndex() const
{
    return m_Index;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE typename CacheRequest<_Params, M>::LineIndex CacheRequest<_Params, M>::GetOffset() const
{
    return m_Offset;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE codasip_address_t CacheRequest<_Params, M>::GetCachelineAddr(
    const codasip_address_t addrToCache) const
{
    codasip_address_t newAddr = addrToCache;
    if (BYTES_PER_WORD < m_Cache.GetLineSize())
    {
        for (int i = 0; i < m_Cache.GetLineShift(); i++)
        {
            ChangeNthBitToXinAddr(newAddr, i, 0);
        }
    }
    return newAddr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void
CacheRequest<_Params, M>::ChangeNthBitToXinAddr(codasip_address_t& addr, const int n, const int value)
{
    addr ^= (-value ^ addr) & (1 << n);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE bool CacheRequest<_Params, M>::DataReady() const
{
    return m_DataReady;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE bool CacheRequest<_Params, M>::WriteDataReady() const
{
    return m_WriteDataReady;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void CacheRequest<_Params, M>::SetInvalidateLoadedLine()
{
    m_InvalidateLoadedLine = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE bool CacheRequest<_Params, M>::GetInvalidateLoadedLine() const
{
    return m_InvalidateLoadedLine;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE Index CacheRequest<_Params, M>::GetActualWordIndex() const
{
    // the first address is the requested one, so the index of the word is shifted by offset
    // and wrapped by the cache line size
    // offset is number of cache words from the start of the cache line, however it needs to be
    // aligned to whole target words, becasue target access is always aligned to target words
    return (m_CacheLineWordsLoaded + m_AlignedOffset) % m_Cache.GetWordsPerLine();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params, class M>
CACHE_INLINE void
CacheRequest<_Params, M>::DoSetNCBiBc(Index& cumulativeBi, Index& bi, Index& bc, const Index bytesCount) const
{
    cumulativeBi += bc;
    bi = 0;
    bc = 0;
    bool stop = false;
    for (Index ii = bytesCount; ii < bytesCount + TARGET_BYTES_PER_WORD; ++ii)
    {
        if (m_NCWriteMask[ii])
        {
            bc++;
            stop = true;
        }
        else if (stop)
        {
            break;
        }
        else
        {
            bi++;
        }
    }
    bi %= TARGET_BYTES_PER_WORD;
}

}   // namespace resources
}   // namespace codasip
#endif
