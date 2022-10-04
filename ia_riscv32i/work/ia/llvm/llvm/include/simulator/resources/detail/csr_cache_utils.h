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
 *  \date   Jul 21, 2021
 *  \brief  Utility functions for the cache.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_UTILS_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_UTILS_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_unaligned_native.h"

#include <deque>
#include <vector>

namespace codasip {
namespace resources {
namespace detail {

using Tag = codasip_address_t;
using LineIndex = codasip_address_t;

/**
 *  \brief  Alignes given address to nearest lowest word address.
 *  \param  address Address that is to be aligned.
 *  \param  bytesPerWord    Number of bytes per word.
 *  \return Aligned address.
 */
codasip_address_t AlignAddressToWordAddress(const codasip_address_t address, const Index bytesPerWord);

/**
 *  \brief  Computes the number of cache lines per set.
 *  \param  size    Size of cache.
 *  \param  numWays Number of ways.
 *  \param  lineSize    Size of the cache line.
 *  \return Number of cache lines per set.
 */
Index GetNumCacheLinesPerSet(const Index size, const Index numWays, const Index lineSize);

/**
 *  \brief  Computes the tag from an address.
 *  \param  address Address whose tag is computed.
 *  \param  numLinesPerSet  Number of cache lines per set.
 *  \param  lineSize    Size of the cache line.
 *  \return Address tag.
 */
Tag GetTagFromAddress(const codasip_address_t address, const Index numLinesPerSet, const Index lineSize);

/**
 *  \brief  Computes the index from an address.
 *  \param  address Address whose index is computed.
 *  \param  numLinesPerSet  Number of cache lines per set.
 *  \param  lineSize    Size of the cache line.
 *  \return Address index.
 */
LineIndex
GetIndexFromAddress(const codasip_address_t address, const Index numLinesPerSet, const Index lineSize);

/**
 *  \brief  Computes the word offset from the begining of its cache line.
 *  \param  address Address of a word whose offset is computed.
 *  \param  lineSize Size of the cache line.
 *  \param  bytesPerWord    Number of bytes per cache word.
 *  \return Word offset.
 */
LineIndex
GetOffsetFromAddress(const codasip_address_t address, const Index lineSize, const Index bytesPerWord);

/**
 *  \brief  Decides the AXI4 burst type based on the number of target words per cache line.
 *  \param  targetWordsPerLine Number of target words per line.
 *  \return AXI4 burst type.
 */
AXIBurstType GetBurstTypeAxi4(const Index targetWordsPerLine);

/**
 *  \brief  Returns the AXI4 maximum burst length that can be used for line fill or eviction based on the number of target words per cache line.
 *  \param  targetWordsPerLine  Number of target words per line.
 *  \return AXI4 burst length.
 */
uint8_t GetBurstLengthAxi4(const Index targetWordsPerLine);

/**
 *  \brief  Prepares a vector of AXI4 burst lengths that can be used for line fill or eviction.
 *  \param  numTargetWords  Number of words that will be read from the target.
 *  \param  maxBurstLength  Maximum burst length that cache supports for line fill or eviction.
 *  \return A vector of burst lengths.
 */
std::deque<uint8_t> PrepareBurstLengthsAxi4(const Index numTargetWords, const uint8_t maxBurstLength);

/**
 *  \brief  Prepares a vector of AXI4 burst addresses that will be used for the line fill or eviction.
 *  \param  startAddressTargetAligned   Starting address aligned to the target word.
 *  \param  burstLengths    Container with burst lengths.
 *  \return Container with burst addresses.
 */
template<Index TARGET_BYTES_PER_WORD>
std::deque<codasip_address_t>
PrepareBurstAddressesAxi4(const codasip_address_t startAddressTargetAligned,
    const std::deque<uint8_t>& burstLengths);

/**
 *  \brief  Concatenates cache words to target words.
 *  \param  cacheWords  A cache word container.
 *  \return A container with target words.
 */
template<typename TargetDataType, Endianness EndianType, typename IteratorType>
std::vector<TargetDataType> ConcatenateCacheWordsToTargetWords(IteratorType begin, IteratorType end);

/**
 *  \brief  Splits cache words to target words.
 *  \param  cacheWords  A cache word container.
 *  \return A container with target words.
 */
template<typename TargetDataType, Endianness EndianType, typename IteratorType>
std::vector<TargetDataType> SplitCacheWordsToTargetWords(IteratorType begin, IteratorType end);

/**
 *  \brief  Transforms cache words to target words.
 *  \param  begin   An iterator pointing to the first cache word.
 *  \param  end An iterator pointing behing the last cache word.
 *  \return A container of target words.
 */
template<typename TargetDataType, Endianness EndianType, typename IteratorType>
std::vector<TargetDataType> TransformCacheWordsToTargetWords(IteratorType begin, IteratorType end);

/**
 *  \brief  Transforms cache words to target words.
 *  \param  cacheLine   A cache word container.
 *  \return A container of target words.
 */
template<typename TargetDataType, Endianness EndianType, typename CacheDataType>
std::vector<TargetDataType>
TransformCacheWordsToTargetWords(const std::vector<CacheDataType>& cacheLine);

template<Index TARGET_BYTES_PER_WORD>
std::deque<codasip_address_t>
PrepareBurstAddressesAxi4(const codasip_address_t startAddressTargetAligned,
    const std::deque<uint8_t>& burstLengths)
{
    if (burstLengths.empty())
    {
        return {};
    }
    else if (burstLengths.size() == 1)
    {
        return {startAddressTargetAligned};
    }

    std::deque<codasip_address_t> result(burstLengths.size());
    auto address = startAddressTargetAligned;
    for (size_t i = 0; i < burstLengths.size() - 1; ++i)
    {
        result[i] = address;
        address += (static_cast<codasip_address_t>(burstLengths[i]) + 1) * TARGET_BYTES_PER_WORD;
    }
    return result;
}

template<typename TargetDataType, Endianness EndianType, typename IteratorType>
std::vector<TargetDataType> ConcatenateCacheWordsToTargetWords(IteratorType begin, IteratorType end)
{
    using ElementDataType = typename std::remove_reference<decltype(*begin)>::type;
    static constexpr Index targetBytesPerWord = sizeof(TargetDataType);
    static constexpr Index cacheBytesPerWord = sizeof(ElementDataType);
    static constexpr Index cacheWordsPerTargetWord = targetBytesPerWord / cacheBytesPerWord;

    static constexpr Index byteBits = 8;
    static constexpr Index cacheDataBits = cacheBytesPerWord * byteBits;
    static constexpr Index targetDataBits = targetBytesPerWord * byteBits;

    std::vector<TargetDataType> result = {};
    for (auto i = begin; i < end; i += cacheWordsPerTargetWord)
    {
        TargetDataType targetWord = 0;
        for (size_t j = 0; j < cacheWordsPerTargetWord; ++j)
        {
            TargetDataType tmp = *(i + j);
            if (EndianType == CP_LITTLE_ENDIAN)
            {
                targetWord |= LeftShift(tmp, j * cacheDataBits);
            }
            else
            {
                targetWord |= LeftShift(tmp, targetDataBits - (cacheDataBits * (j + 1)));
            }
        }
        result.emplace_back(targetWord);
    }
    return result;
}

template<typename TargetDataType, Endianness EndianType, typename IteratorType>
std::vector<TargetDataType> SplitCacheWordsToTargetWords(IteratorType begin, IteratorType end)
{
    using ElementDataType = typename std::remove_reference<decltype(*begin)>::type;
    static constexpr Index targetBytesPerWord = sizeof(TargetDataType);
    static constexpr Index cacheBytesPerWord = sizeof(ElementDataType);
    static constexpr Index targetWordsPerCacheWord = cacheBytesPerWord / targetBytesPerWord;

    static constexpr Index byteBits = 8;

    std::vector<TargetDataType> result = {};
    for (auto j = begin; j != end; ++j)
    {
        for (Index i = 0; i < targetWordsPerCacheWord; ++i)
        {
            const TargetDataType targetWord =
                Unaligned<ElementDataType, byteBits, cacheBytesPerWord>::template read<
                    EndianType>(j, 0, i * targetBytesPerWord, targetBytesPerWord);
            result.emplace_back(targetWord);
        }
    }
    return result;
}

template<typename TargetDataType, Endianness EndianType, typename IteratorType>
std::vector<TargetDataType> TransformCacheWordsToTargetWords(IteratorType begin, IteratorType end)
{
    if (sizeof(TargetDataType) >= sizeof(typename std::remove_reference<decltype(*begin)>::type))
    {
        return ConcatenateCacheWordsToTargetWords<TargetDataType, EndianType>(begin, end);
    }
    return SplitCacheWordsToTargetWords<TargetDataType, EndianType>(begin, end);
}

template<typename TargetDataType, Endianness EndianType, typename CacheDataType>
std::vector<TargetDataType>
TransformCacheWordsToTargetWords(const std::vector<CacheDataType>& cacheLine)
{
    return TransformCacheWordsToTargetWords<TargetDataType, EndianType>(cacheLine.begin(),
        cacheLine.end());
}

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   //  SIMULATOR_RESOURCES_CSR_CACHE_UTILS_H_
