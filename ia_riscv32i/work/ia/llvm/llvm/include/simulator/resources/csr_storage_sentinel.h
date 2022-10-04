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
 *  \author Zdenek Prikryl
 *  \date   Feb 23, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_STORAGE_SENTINEL_H_
#define SIMULATOR_RESOURCES_CSR_STORAGE_SENTINEL_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/resources/detail/csr_storage_helpers.h"

namespace codasip {
namespace resources {

// forward declaration
template<typename T>
class Payload;

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::Storage
 *  \brief
 *  \}
 */
template<class T, codasip_address_t _Size>
class StorageSentinel : public Sentinel
{
public:
    /// Typedef for used data type
    typedef T data_type;
    /// Typedef for used parameter type
    typedef typename detail::CallTraits<data_type>::param_type param_type;
    /// \brief  Allows profiler to work with vector types
    typedef data_type elem_type;
    /// \brief  Allows profiler to work with vector types
    typedef typename detail::CallTraits<elem_type>::param_type elem_param_type;
    /// \brief  Type used by the profiler templates - not used with this class
    typedef Payload<data_type> payload_type;

    static constexpr Index ADDR_BITS = BitWidthSelector<_Size - 1>::value;
    static constexpr Index WORD_BITS = BitWidthTypeSelector<T>::value;
    static constexpr Index BYTE_BITS = WORD_BITS;
    static constexpr Index BPW = WORD_BITS / BYTE_BITS;
    static constexpr codasip_address_t SIZE = _Size;

    StorageSentinel(const std::string& name, const Uid uid);
    /**
     * \brief Truncate address to the correct boundaries
     */
    static codasip_address_t get_address(const codasip_address_t);
    /**
     * \brief Set default value
     * \param defaultValue Default value
     */
    void set_default_value(param_type defaultValue);
    /**
     * \brief Return default value
     */
    data_type get_default_value() const;

protected:
    /// default value for reset and clear
    data_type m_DefaultValue;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size>
inline StorageSentinel<T, _Size>::StorageSentinel(const std::string& name, const Uid uid)
  : Sentinel(name, uid)
  , m_DefaultValue()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size>
RES_INLINE codasip_address_t StorageSentinel<T, _Size>::get_address(const codasip_address_t addr)
{
    return detail::TruncateAddress<SIZE, ADDR_BITS>(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size>
inline void StorageSentinel<T, _Size>::set_default_value(param_type defaultValue)
{
    m_DefaultValue = defaultValue;
}

template<class T, codasip_address_t _Size>
RES_INLINE typename StorageSentinel<T, _Size>::data_type
StorageSentinel<T, _Size>::get_default_value() const
{
    return m_DefaultValue;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_STORAGE_SENTINEL_H_
