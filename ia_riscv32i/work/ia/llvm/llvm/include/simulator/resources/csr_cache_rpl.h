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
 *  \date   Oct 01, 2021
 *  \brief
 */
#ifndef SIMULATOR_RESOURCES_CSR_CACHE_RPL_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_RPL_H_

#include "simulator/resources/csr_helpers.h"

namespace codasip {
namespace resources {

//#define _DEBUG_CACHE_RPL
#define CACHE_INLINE inline
/**
 *  \class  codasip::resources::RandomReplacementPolicy
 *  \brief  This class implements the random replacement policy.
 */
template<class CacheStorage>
class RandomReplacementPolicy
{
public:
    /// Cache line index.
    typedef codasip_address_t LineIndex;
    /// Bits container type.
    typedef std::vector<std::vector<bool>> BitsContainerType;
    /**
     *  \brief  Default constructor, initializes LFSR.
     */
    RandomReplacementPolicy(const CacheStorage& storage);
    /**
     *  \brief  Returns way in which a new cache line could be saved.
     *  \param  index     Cache line index.
     *  \param  validBits Validity bits for stored cache lines.
     *  \return Way index.
     */
    Index GetReplaceWay(const LineIndex index, const BitsContainerType& validBits) const;
    /**
     *  \brief  Update the LFSR value.
     */
    void Update();
    /**
     *  \brief  Resets the LFSR state.
     */
    void Reset();
    /**
     *  \brief  Returns the LFSR value.
     */
    uint16_t GetLFSRValue() const;
private:
    /// Cache storage implementation
    const CacheStorage& m_CacheStorage;
    /// Value of the Galois linear-feedback shift register
    uint16_t m_LFSR;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CacheStorage>
CACHE_INLINE RandomReplacementPolicy<CacheStorage>::RandomReplacementPolicy(const CacheStorage& cacheStorage)
  : m_CacheStorage(cacheStorage)
{
    Reset();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CacheStorage>
CACHE_INLINE Index RandomReplacementPolicy<CacheStorage>::GetReplaceWay(const LineIndex index,
    const BitsContainerType& validBits) const
{
    for (Index i = 0; i < m_CacheStorage.GetNumWays(); i++)
    {
        if (!validBits.at(i).at(index))
        {
            return i;
        }
    }
    return m_LFSR % m_CacheStorage.GetNumWays();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CacheStorage>
CACHE_INLINE void
RandomReplacementPolicy<CacheStorage>::Update()
{
    m_LFSR = (m_LFSR & 0x0001) ? ((m_LFSR >> 1) ^ 0xb400 /*toggle mask*/) : (m_LFSR >> 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CacheStorage>
CACHE_INLINE void RandomReplacementPolicy<CacheStorage>::Reset()
{
    // Initialize the LFSR register to the value used in RTL.
    m_LFSR = 0xACE1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CacheStorage>
CACHE_INLINE uint16_t RandomReplacementPolicy<CacheStorage>::GetLFSRValue() const
{
    return m_LFSR;
}
}   // namespace resources
}   // namespace codasip
#endif
