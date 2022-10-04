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
 *  \date   Feb 25, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_PAYLOAD_SENTINEL_H_
#define SIMULATOR_RESOURCES_CSR_PAYLOAD_SENTINEL_H_

#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/simbase/simulator_resources.h"

#include <climits>

namespace codasip {
namespace resources {
namespace detail {

/// \brief  Container type storing the data alignment values
typedef ::codasip::simulator::InterfaceInfo::DataAlignment DataAlignment;

}   // namespace detail

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::PayloadSentinel
 *  \brief  Basic storage for a payload
 *  \}
 */
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
class PayloadSentinel : public Sentinel
{
public:
    /// \brief public underlying data type
    typedef T data_type;
    /// \brief type used for effective data type passing
    typedef typename detail::CallTraits<data_type>::param_type param_type;
    /// \brief  Allows profiler to work with vector types
    typedef data_type elem_type;
    /// \brief  Allows profiler to work with vector types
    typedef typename detail::CallTraits<elem_type>::param_type elem_param_type;
    /// \brief  Allows profiler to work with interface payload types
    typedef Payload<data_type> payload_type;
    /// Data alignment
    typedef detail::DataAlignment DataAlignment;
    /// protocol access/address checker type
    typedef _PAC PacType;
    /// \brief  Allows the upper templates to access this type
    typedef PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC> PayloadSentinelType;

    static const Index ADDR_BITS = _AddrBits;
    static const Index WORD_BITS = BitWidthTypeSelector<T>::value;
    static const Index BYTE_BITS = _ByteBits;
    static const Index BPW = WORD_BITS / BYTE_BITS;
    static const Endianness ENDIANNESS = _Endianness;
    static const codasip_address_t SIZE = (_AddrBits == sizeof(codasip_address_t) * CHAR_BIT
            ? codasip_address_t(-1)
            : (codasip_address_t(1) << _AddrBits));

    /**
     *  \copydoc Sentinel::Sentinel
     *  Sets default address and data alignment. Address alignment to word and
     *  data alignment to powers of 2.
     */
    PayloadSentinel(const std::string& name, const Uid uid);

    void blocking(payload_type& p);
    void transport(payload_type& p, const Phase phase);

    /**
     *  \{
     *  \brief  Do nothing.
     */
    void clock_cycle() {}
    void reset() {}
    void stall() {}
    void gated() {}
    /**
     *  \} \{
     *  \brief  Callback when action is done.
     */
    void blocking_d(payload_type&) {}
    void transport_d(payload_type&, const Phase) {}
    /**
     *  \} \{
     *  \brief  Setter
     */
    void set_data_alignment(DataAlignment data);
    void set_address_alignment(const Index address);
    /**
     *  \} \{
     *  \brief  Getter
     */
    const DataAlignment& get_data_alignment() const;
    Index get_address_alignment() const;
    /**
     *  \}
     *  \brief  Check transaction properties (payload) during address phase.
     *  \param  isBlocking indicates whether the access is in IA mode using
     *          \em blocking function (true) or CA mode using \em transport (false).
     *          Default value is true (IA mode).
     *  \param  isReadable indicates whether read access is support or not.
     *          Default value is true.
     *  \param  isWriteable indicates whether read access is support or not.
     *          Default value is true.
     */
    void check_payload(payload_type& p,
        const bool isBlocking = true,
        const bool isReadable = true,
        const bool isWriteable = true);

    /// Return data alignment mask. Replaces DataAlignment vector
    Index get_data_alignment_mask() const;

private:
    static void fix_address(payload_type&);

    /// Data alignment mask used instead of DataAlignment
    Index m_DataAlignmentMask;

    /// Address Alignment
    Index m_AddressAlignment;

    /// Data alignment
    DataAlignment m_DataAlignment;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE
PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::PayloadSentinel(const std::string& name,
    const Uid uid)
  : Sentinel(name, uid)
  , m_AddressAlignment(BPW)
{
    DataAlignment data;
    for (Index ii = 1u; ii <= BPW; ii *= 2u)
    {
        data.push_back(ii);
    }
    set_data_alignment(std::move(data));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE void PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::blocking(payload_type& p)
{
    fix_address(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE void
PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::transport(payload_type& p, const Phase)
{
    fix_address(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE void
PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::fix_address(payload_type& p)
{
    p.set_address((p.get_address() << (sizeof(codasip_address_t) * CHAR_BIT - ADDR_BITS)) >>
        (sizeof(codasip_address_t) * CHAR_BIT - ADDR_BITS));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE void
PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::set_data_alignment(DataAlignment data)
{
    // Compute alignment mask
    Index temporaryMask = 0;
    for (auto index : data)
    {
        temporaryMask |= index;
    }
    this->m_DataAlignmentMask = temporaryMask;
    m_DataAlignment = std::move(data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE void
PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::set_address_alignment(const Index address)
{
    m_AddressAlignment = address;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE const typename PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::DataAlignment&
PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::get_data_alignment() const
{
    return m_DataAlignment;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE Index PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::get_address_alignment() const
{
    return m_AddressAlignment;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE void
PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::check_payload(payload_type& p,
    const bool isBlocking,
    const bool isReadable,
    const bool isWriteable)
{
    PacType::check_address(p, *this, isBlocking, isReadable, isWriteable);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _PAC>
RES_INLINE Index PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::get_data_alignment_mask() const
{
    return this->m_DataAlignmentMask;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_PAYLOAD_SENTINEL_H_
