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

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_STORAGE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_STORAGE_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_unaligned_native.h"
#include "simulator/resources/detail/csr_cache_utils.h"

#include <vector>

namespace codasip {
namespace resources {

//#define _DEBUG_CACHE_STORAGE
#define CACHE_INLINE inline

/**
 *  \brief  calculate number of lines per set
 *  \param  IS_ENABLED cache block is enabled
 *  \param  size cache size
 *  \param  ways cache num ways
 *  \param  lineSize cache line size
 */
template<bool IS_ENABLED>
Index CalculateLinesPerSet(const Index size, const Index numWays, const Index lineSize)
{
    return IS_ENABLED ? detail::GetNumCacheLinesPerSet(size, numWays, lineSize) : 0;
}
/**
 *  \brief  calculate words per line
 *  \param  DATA_BITS number of bits in cache data type
 *  \param  BYTE_BITS number of bits per arch byte
 *  \param  lineSize cache line size
 *
 */
template<Index DATA_BITS, Index BYTE_BITS>
Index CalculateWordsPerLine(const Index lineSize)
{
    return lineSize / (DATA_BITS / BYTE_BITS);
}
/**
 *  \brief  helper to set ahb burts mode
 *  \param  targetWordsPerLine target words per line, target = interface out of cache
 */
inline AHBBurstMode CalculateAHBBurstMode(const Index targetWordsPerLine)
{
    return targetWordsPerLine == 4 ? CP_AHB_WRAP4
        : targetWordsPerLine == 8  ? CP_AHB_WRAP8
        : targetWordsPerLine == 16 ? CP_AHB_WRAP16
                                   : CP_AHB_INCR;
}
/**
 *  \class  codasip::resources::CacheStorage
 *  \tparam _Params Cache parameters.
 */
template<class _Params>
class CacheStorage
{
public:
    /// \copydoc codasip::resources::Cache::CACHE_DATA_BITS
    static const Index CACHE_DATA_BITS = _Params::WORD_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::BYTE_BITS
    static const Index BYTE_BITS = _Params::LAU_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::CACHE_ADDR_BITS
    static const Index CACHE_ADDR_BITS = _Params::ADDR_BIT_WIDTH;
    /// \copydoc codasip::resources::Cache::BYTES_PER_WORD
    static const Index BYTES_PER_WORD = CACHE_DATA_BITS / BYTE_BITS;
    /// \copydoc codasip::resources::Cache::ENDIANNESS
    static const Endianness ENDIANNESS = static_cast<Endianness>(_Params::ENDIANNESS);
    /// Bit-width of target data.
    static const Index TARGET_DATA_BITS = _Params::TARGET_WORD_BIT_WIDTH;
    /// Target bytes per word.
    static const Index TARGET_BYTES_PER_WORD = TARGET_DATA_BITS / BYTE_BITS;

    /// Data type of the interface.
    typedef typename _Params::data_type Data;
    /// Container type of cacheline.
    typedef typename std::vector<Data> CLine;
    /// Line index of entry in cache.
    typedef codasip_address_t LineIndex;
    /// Tag type.
    typedef codasip_address_t Tag;
    /**
     *  \brief  Initialize data CacheStorage.
     */
    CacheStorage(const Index size, const Index numWays, const Index lineSize);
    /**
     *  \brief  Free allocated data CacheStorage.
     */
    ~CacheStorage();
    /// \copydoc codasip::resources::Cache::reset
    void Reset();
    /**
     *  \brief Determines if data in specific set and on specific index are valid.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     *  \param return Returns true if is falid, false if is invalid.
     */
    bool IsValid(const Index set, const LineIndex line) const;
    /**
     *  \brief Determines if data in specific set and on specific index are dirty.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     *  \param return Returns true if is dirty, false if is clear.
     */
    bool IsDirty(const Index set, const LineIndex line) const;
    /**
     *  \brief Marks data in specific set and on specific index as valid.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     */
    void SetValid(const Index set, const LineIndex line);
    /**
     *  \brief Marks data in specific set and on specific index as invalid.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     */
    void SetInvalid(const Index set, const LineIndex line);
    /**
     *  \brief Marks data in specific set and on specific index as dirty.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     */
    void SetDirty(const Index set, const LineIndex line);
    /**
     *  \brief Marks data in specific set and on specific index as clear.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     */
    void SetClear(const Index set, const LineIndex line);
    /**
     *  \brief Save tag for specific set and on specific index.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     *  \param tag    Tag calculated from address.
     */
    void SetTag(const Index set, const LineIndex line, const Tag tag);
    /**
     *  \brief Returns tag for specific set and on specific index.
     *  \param set    Cache way/set.
     *  \param line   Index calculated from address.
     *  \return       Tag.
     */
    Tag GetTag(const Index set, const LineIndex line) const;
    /**
     *  \brief       Determines if on specific index are valid data for specific tag.
     *  \param  tag  Tag calculated from address.
     *  \param  line Index calculated from address.
     *  \param  set  Way/set in which are HITted data.
     *  \return      Returns true if is HIT, false is is MISS.
     */
    bool IsHit(const Tag tag, const LineIndex line, Index& set);
    /**
     *  \brief  Gets cache line saved in cache.
     *  \param  set     Way/set of the cache line.
     *  \param  index   Cache line index.
     *  \return         Cache line.
     */
    const CLine& GetCacheLine(const Index set, const LineIndex index) const;
    /**
     *  \brief          Gets data saved in cache.
     *  \param  set     Way/set in which are data.
     *  \param  index   Index calculated from address.
     *  \param  offset  Offset Index calculated from address.
     *  \param  si      Subblock index.
     *  \param  sc      Subblock counter.
     *  \return         Cache data.
     */
    Data
    GetData(const Index set, const LineIndex index, const LineIndex offset, const Index si, const Index sc);
    /**
     *  \brief  Gets data saved in cache.
     *  \param  set     Way/set in which are data.
     *  \param  index   Index calculated from address.
     *  \param  offset  Offset Index calculated from address.
     *  \return         Cache data.
     */
    Data GetData(const Index set, const LineIndex index, const LineIndex offset);
    /**
     *  \brief  Writes data to cache.
     *  \param  data    Data to write.
     *  \param  set     Way/set in which are data.
     *  \param  index   Index calculated from address.
     *  \param  offset  Offset Index calculated from address.
     *  \param  si      Subblock index.
     *  \param  sc      Subblock counter.
     *  \return         Cache data.
     */
    void SetData(typename CacheStorage<_Params>::Data data,
        const Index set,
        const LineIndex index,
        const LineIndex offset,
        const Index si,
        const Index sc);
    /**
     *  \brief  Saves cache line into cache.
     *  \param  set           Way/set into which are data saved.
     *  \param  index         Index calculated from address.
     *  \param  cacheLineData Cache line data.
     */
    void SaveCacheLine(const Index set, const LineIndex index, const CLine cacheLineData);
    /**
     *  \brief  Returns current replace way/set.
     *  \param  index Index calculated from address.
     *  \return Current replace way/set.
     */
    Index GetReplaceWay(const LineIndex index) const;
    /// Size getter
    Index GetSize() const;
    /// NumWays getter
    Index GetNumWays() const;
    /// LineSize getter
    Index GetLineSize() const;
    /// LSB of line size getter
    Index GetLineShift() const;
    /// Line count per set accessor
    Index GetLinesPerSet() const;
    /// Words per line getter
    Index GetWordsPerLine() const;
    /// Tag shift getter
    int GetTagShift() const;
    /// Tag bits getter
    int GetTagBits() const;
    /// Lsb of index getter
    int GetIndexShift() const;
    ///
    int GetTargetWordAlign() const;
    /// Target words per line getter
    Index GetTargetWordsPerLine() const;
    /// (AHB) Burst mode getter.
    AHBBurstMode GetTargetBurstMode() const;
    /// (AXI) Burst type getter.
    AXIBurstType GetAXITargetBurstType() const;
    /// (AXI) Burst length getter.
    uint8_t GetAXITargetBurstLength() const;
    /**
     *  \copydoc codasip::resources::RandomReplacementPolicy::Update
     */
    void UpdateReplacementPolicy();
    /**
     *  \copydoc codasip::resources::RandomReplacementPolicy::Reset
     */
    void ResetReplacementPolicy();
    /**
     *  \copydoc codasip::resources::RandomReplacementPolicy::GetLFSRValue
     */
    uint16_t GetLFSRValue() const;

private:
    const Index m_Size;
    /// Number of ways.
    const Index m_NumWays;
    /// Cache linesize
    const Index m_LineSize;
    /// LSB position of cacheline index.
    const Index m_LineShift;
    /// Number of lines per set.
    const Index m_LinesPerSet;
    /// Number of words in one cache line
    const Index m_WordsPerLine;
    /// LSB of address tag
    const int m_TagShift;
    /// Tag bits
    const int m_TagBits;
    /// LSB of address index.
    const int m_IndexShift;
    /// Number of target bits per word.
    const int m_TargetWordAlign;
    /// Target words per line
    const Index m_TargetWordsPerLine;
    /// (AHB) Burst mode for cache line load/store. Yes, this is here.
    const AHBBurstMode m_AHBTargetBurstMode;
    /// (AXI) Burst type for cache line load/store.
    const AXIBurstType m_AXITargetBurstType;
    /// (AXI) Burst length for cache line load/store.
    const uint8_t m_AXITargetBurstLength;

    typedef std::vector<std::vector<CLine>> DataContainerType;
    typedef std::vector<std::vector<bool>> BitsContainerType;
    typedef std::vector<std::vector<Tag>> TagsContainerType;
    void SetValidBit(const Index, const LineIndex, const bool);
    void SetDirtyBit(const Index, const LineIndex, const bool);
    void ResetContainers();
    LineIndex GetIndexFromAddr(const codasip_address_t);
    template<class V>
    typename V::value_type::value_type Access(const V&, const Index, const LineIndex) const;
    template<class V>
    void Update(V&, const typename V::value_type::value_type, const Index, const LineIndex);
    /// Container with actual data.
    DataContainerType m_Data;
    /// Container with valid bits.
    BitsContainerType m_ValidBits;   // true == valid
    /// Container with dirty bits.
    BitsContainerType m_DirtyBits;   // true == dirty
    /// Container with tags.
    TagsContainerType m_Tags;
    /// Replacement Policy
    typename _Params::replacement_policy_t m_ReplacementPolicy;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE
CacheStorage<_Params>::CacheStorage(const Index size, const Index numWays, const Index lineSize)
  : m_Size(size)
  , m_NumWays(numWays)
  , m_LineSize(lineSize)
  , m_LineShift(ILog2(lineSize))
  , m_LinesPerSet(CalculateLinesPerSet<_Params::IS_ENABLED>(size, numWays, lineSize))
  , m_WordsPerLine(CalculateWordsPerLine<CACHE_DATA_BITS, BYTE_BITS>(lineSize))
  , m_TagShift(ILog2(m_LinesPerSet * m_WordsPerLine * BYTES_PER_WORD))
  , m_TagBits(CACHE_ADDR_BITS - m_TagShift)
  , m_IndexShift(ILog2(m_WordsPerLine * BYTES_PER_WORD))
  , m_TargetWordAlign(ILog2(TARGET_BYTES_PER_WORD))
  , m_TargetWordsPerLine(lineSize / TARGET_BYTES_PER_WORD)
  , m_AHBTargetBurstMode(CalculateAHBBurstMode(m_TargetWordsPerLine))
  , m_AXITargetBurstType(detail::GetBurstTypeAxi4(m_TargetWordsPerLine))
  , m_AXITargetBurstLength(detail::GetBurstLengthAxi4(m_TargetWordsPerLine))
  , m_Data(m_NumWays, typename DataContainerType::value_type(m_LinesPerSet, CLine(m_WordsPerLine, 0)))
  , m_ValidBits(m_NumWays, typename BitsContainerType::value_type(m_LinesPerSet, false))
  , m_DirtyBits(m_NumWays, typename BitsContainerType::value_type(m_LinesPerSet, false))
  , m_Tags(m_NumWays, typename TagsContainerType::value_type(m_LinesPerSet, 0))
  , m_ReplacementPolicy(*this)
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE CacheStorage<_Params>::~CacheStorage()
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief Marks data in specific set and on specific index as valid or invalid.
 *  \param set    Cache way/set.
 *  \param line   Index calculated from address.
 *  \param value  True if data should be marked as valid, else others.
 */
template<class _Params>
CACHE_INLINE void
CacheStorage<_Params>::SetValidBit(const Index set, const LineIndex line, const bool value)
{
#ifdef _DEBUG_CACHE_STORAGE
    std::cerr << __FUNCTION__ << " : set(" << set << ") line(" << line << ") value(" << value << ")"
              << std::endl;
#endif
    Update(m_ValidBits, value, set, line);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief Marks data in specific set and on specific index as dirty or clear.
 *  \param set    Cache way/set.
 *  \param line   Index calculated from address.
 *  \param value  True if data should be marked as dirty, else clear.
 */
template<class _Params>
CACHE_INLINE void
CacheStorage<_Params>::SetDirtyBit(const Index set, const LineIndex line, const bool value)
{
    Update(m_DirtyBits, value, set, line);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE bool CacheStorage<_Params>::IsValid(const Index set, const LineIndex line) const
{
    return Access(m_ValidBits, set, line);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE bool CacheStorage<_Params>::IsDirty(const Index set, const LineIndex line) const
{
    return Access(m_DirtyBits, set, line);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::SetValid(const Index set, const LineIndex line)
{
    this->SetValidBit(set, line, true);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::SetInvalid(const Index set, const LineIndex line)
{
    this->SetValidBit(set, line, false);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::SetDirty(const Index set, const LineIndex line)
{
    this->SetDirtyBit(set, line, true);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::SetClear(const Index set, const LineIndex line)
{
    this->SetDirtyBit(set, line, false);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::SetTag(const Index set, const LineIndex line, const Tag tag)
{
    Update(m_Tags, tag, set, line);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE typename CacheStorage<_Params>::Tag
CacheStorage<_Params>::GetTag(const Index set, const LineIndex line) const
{
    return Access(m_Tags, set, line);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE bool CacheStorage<_Params>::IsHit(const Tag tag, const LineIndex line, Index& set)
{
    for (set = 0; set < m_NumWays; set++)
    {
        // tag comparison in every set! if match, cache hit only if valid_bit set to 1, else miss!
        if (tag == this->GetTag(set, line))
        {
            if (this->IsValid(set, line))
            {
                break;
            }
        }
    }
    if (set < m_NumWays)
    {
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

template<class _Params>
CACHE_INLINE const typename CacheStorage<_Params>::CLine&
CacheStorage<_Params>::GetCacheLine(const Index set, const LineIndex index) const
{
    return this->m_Data.at(set).at(index);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE typename CacheStorage<_Params>::Data CacheStorage<_Params>::GetData(const Index set,
    const LineIndex index,
    const LineIndex offset,
    const Index si,
    const Index sc)
{
    Data data = GetData(set, index, offset);
    return Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template read<ENDIANNESS>(&data, 0, si, sc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE typename CacheStorage<_Params>::Data
CacheStorage<_Params>::GetData(const Index set, const LineIndex index, const LineIndex offset)
{
    return this->m_Data.at(set).at(index).at(offset);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::SetData(typename CacheStorage<_Params>::Data data,
    const Index set,
    const LineIndex index,
    const LineIndex offset,
    const Index si,
    const Index sc)
{
#ifdef _DEBUG_CACHE_STORAGE
    std::cerr << "CacheStorage::" << __FUNCTION__ << "(data(" << data << ") set(" << set
              << ") index(" << index << ") offset(" << offset << ") si(" << si << ") sc(" << sc
              << "))" << std::endl;
#endif
    Data d = this->GetData(set, index, offset);
    Unaligned<Data, BYTE_BITS, BYTES_PER_WORD>::template write<ENDIANNESS>(&d, data, 0, si, sc);
    this->m_Data[set][index][offset] = d;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void
CacheStorage<_Params>::SaveCacheLine(const Index set, const LineIndex index, CLine cacheLineData)
{
#ifdef _DEBUG_CACHE_STORAGE
    std::cerr << "CacheStorage::SaveCacheLine( set = " << std::dec << set << ", index = h'"
              << std::hex << index << ", cacheLineData = h'";
    for (int i = 0; i < cacheLineData.size(); i++)
    {
        if (i != 0)
        {
            std::cerr << "_";
        }
        std::cerr << std::hex << cacheLineData.at(i);
    }
    std::cerr << " ) m_Data.size() = " << std::dec << m_Data.size() << std::endl;
#endif
    for (unsigned int i = 0; i < cacheLineData.size(); i++)
    {
#ifdef _DEBUG_CACHE_STORAGE
        std::cerr << "i = " << std::dec << i << std::endl;
#endif
        m_Data.at(set).at(index).at(i) = cacheLineData.at(i);
    }
    return;
#ifdef _DEBUG_CACHE_STORAGE
    std::cerr << "CacheStorage::SaveCacheLine()  saved" << std::endl;
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE Index CacheStorage<_Params>::GetReplaceWay(const LineIndex index) const
{
    if (index < m_LinesPerSet)
    {
        return m_ReplacementPolicy.GetReplaceWay(index, this->m_ValidBits);
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/// Reinitializes all containers.
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::ResetContainers()
{
    m_Data.assign(m_NumWays,
        typename DataContainerType::value_type(m_LinesPerSet, CLine(m_WordsPerLine, 0)));
    m_ValidBits.assign(m_NumWays, typename BitsContainerType::value_type(m_LinesPerSet, false));
    m_DirtyBits.assign(m_NumWays, typename BitsContainerType::value_type(m_LinesPerSet, false));
    m_Tags.assign(m_NumWays, typename TagsContainerType::value_type(m_LinesPerSet, 0));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE Index CacheStorage<_Params>::GetSize() const
{
    return m_Size;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE Index CacheStorage<_Params>::GetNumWays() const
{
    return m_NumWays;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE Index CacheStorage<_Params>::GetLineSize() const
{
    return m_LineSize;
}
template<class _Params>
CACHE_INLINE Index CacheStorage<_Params>::GetLineShift() const
{
    return m_LineShift;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE Index CacheStorage<_Params>::GetLinesPerSet() const
{
    return m_LinesPerSet;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE Index CacheStorage<_Params>::GetWordsPerLine() const
{
    return m_WordsPerLine;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE int CacheStorage<_Params>::GetTagShift() const
{
    return m_TagShift;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE int CacheStorage<_Params>::GetTagBits() const
{
    return m_TagBits;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE int CacheStorage<_Params>::GetIndexShift() const
{
    return m_IndexShift;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE int CacheStorage<_Params>::GetTargetWordAlign() const
{
    return m_TargetWordAlign;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
inline Index CacheStorage<_Params>::GetTargetWordsPerLine() const
{
    return m_TargetWordsPerLine;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
inline AHBBurstMode CacheStorage<_Params>::GetTargetBurstMode() const
{
    return m_AHBTargetBurstMode;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
inline AXIBurstType CacheStorage<_Params>::GetAXITargetBurstType() const
{
    return m_AXITargetBurstType;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
inline uint8_t CacheStorage<_Params>::GetAXITargetBurstLength() const
{
    return m_AXITargetBurstLength;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::Reset()
{
#ifdef _DEBUG_CACHE_STORAGE
    std::cerr << "CacheStorage::Reset()" << std::endl;
#endif
    ResetContainers();
    ResetReplacementPolicy();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Calculate index from address.
 *  \param  addr Address.
 *  \return Index calculated from address addr.
 */
template<class _Params>
CACHE_INLINE typename CacheStorage<_Params>::LineIndex
CacheStorage<_Params>::GetIndexFromAddr(const codasip_address_t addr)
{
    return ((addr / m_LineSize) % m_LinesPerSet);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Accesses a container value when the location is valid.
 *  \param  container   A container that is accessed.
 *  \param  set Accessed set.
 *  \param  line    Accessed line.
 *  \return Value in container if set and line locations are valid, zero value otherwise.
 */
template<class _Params>
template<class V>
CACHE_INLINE typename V::value_type::value_type
CacheStorage<_Params>::Access(const V& container, const Index set, const LineIndex line) const
{
    if (set < m_NumWays && line < m_LinesPerSet)
    {
        return container.at(set).at(line);
    }
    return static_cast<typename V::value_type::value_type>(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Updates a container when the location is valid.
 *  \param  container   A container that is updated.
 *  \param  value   New value.
 *  \param  set Updated set.
 *  \param  line    Updated line.
 */
template<class _Params>
template<class V>
CACHE_INLINE void CacheStorage<_Params>::Update(V& container,
    const typename V::value_type::value_type value,
    const Index set,
    const LineIndex line)
{
    if (set < m_NumWays && line < m_LinesPerSet)
    {
        container.at(set).at(line) = value;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void
CacheStorage<_Params>::UpdateReplacementPolicy()
{
    m_ReplacementPolicy.Update();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE void CacheStorage<_Params>::ResetReplacementPolicy()
{
    m_ReplacementPolicy.Reset();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _Params>
CACHE_INLINE uint16_t CacheStorage<_Params>::GetLFSRValue() const
{
    return m_ReplacementPolicy.GetLFSRValue();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}   // namespace resources
}   // namespace codasip

#endif
