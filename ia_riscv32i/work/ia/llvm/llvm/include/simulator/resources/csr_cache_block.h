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
 *  \date   Oct 18, 2018
 *  \brief  Definition of the class codasip::resources::CacheBlock.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_H_

#include "simulator/resources/csr_memory.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/resources/csr_value_with_expression.h"
#include "simulator/resources/detail/csr_cache_helpers.h"
#include "simulator/simbase/simulator_resources.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::CacheBlock
 *  \brief  Merged data and optionally instruction cache block. This wrapper
 *          contains only minimal interface required by the simulator.
 *  \tparam CacheCore base class type containing unique definition of the cache.
 *  \}
 */
template<class CacheCore>
class CacheBlock : public Sentinel, public CacheCore
{
public:
    /// Control and status register configuration.
    typedef typename CacheCore::RParams RParams;
    /// Instruction cache configuration.
    typedef typename CacheCore::IParams IParams;
    /// Data cache configuration.
    typedef typename CacheCore::DParams DParams;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    template<typename... Args>
    CacheBlock(const std::string& name, const Uid uid, Args&&... args);
    /**
     *  \brief  Reset cache (reset request logic).
     */
    void reset();
    /**
     *  \brief  Move one clock cycle further.
     */
    void clock_cycle();
    /**
     *  \{
     *  \brief  Provide IA access and debug functions.
     *  \param  args arguments passed directly to the internal data slave interface.
     */
    template<class... Args>
    typename DParams::data_type read(Args&&... args);
    template<class... Args>
    typename DParams::data_type dread(Args&&... args);
    template<class... Args>
    void write(Args&&... args);
    template<class... Args>
    void dwrite(Args&&... args);
    template<class... Args>
    void load(Args&&... args);
    /** \} */
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
template<typename... Args>
inline CacheBlock<CacheCore>::CacheBlock(const std::string& name, const Uid uid, Args&&... args)
  : Sentinel(name, uid)
  , CacheCore(name, uid, GetValue(args)...)
{
    detail::VerifyCacheBlockRuntimeParameters<IParams, DParams>(name, std::make_tuple(args...));
    static_assert(
        static_cast<Endianness>(IParams::ENDIANNESS) == static_cast<Endianness>(DParams::ENDIANNESS),
        "Endianness mismatch between instruction and data cache!");
}

////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
inline void CacheBlock<CacheCore>::reset()
{
    CacheCore::Reset();
}

////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
inline void CacheBlock<CacheCore>::clock_cycle()
{
    CacheCore::ClockCycle();
}

////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
template<class... Args>
inline typename CacheBlock<CacheCore>::DParams::data_type CacheBlock<CacheCore>::read(Args&&... args)
{
    return CacheCore::GetDCacheSlaveInterface().read(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
template<class... Args>
inline typename CacheBlock<CacheCore>::DParams::data_type CacheBlock<CacheCore>::dread(Args&&... args)
{
    return CacheCore::GetDCacheSlaveInterface().dread(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
template<class... Args>
inline void CacheBlock<CacheCore>::write(Args&&... args)
{
    CacheCore::GetDCacheSlaveInterface().write(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
template<class... Args>
inline void CacheBlock<CacheCore>::dwrite(Args&&... args)
{
    CacheCore::GetDCacheSlaveInterface().dwrite(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class CacheCore>
template<class... Args>
inline void CacheBlock<CacheCore>::load(Args&&... args)
{
    CacheCore::GetDCacheSlaveInterface().load(std::forward<Args>(args)...);
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CACHE_BLOCK_H_
