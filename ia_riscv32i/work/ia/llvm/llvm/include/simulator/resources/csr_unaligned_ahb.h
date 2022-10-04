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
 *  \author Richtarik Pavel
 *  \date   2017-09-21
 *  \brief  Definition of the class codasip::resources::UnalignedAhb.
 */

#ifndef SIMULATOR_RESOURCES_CSR_UNALIGNED_AHB_H_
#define SIMULATOR_RESOURCES_CSR_UNALIGNED_AHB_H_

#include "simulator/resources/csr_helpers.h"
#include "utility/codasiputils.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  UnalignedAhb
 *  \brief  Accepts array of data and it reads the word as specified in AHB Lite.
 *  \tparam T word data type
 *  \tparam _ByteBits Bit-Width of the byte
 */
template<class T, int _ByteBits>
class UnalignedAhb
{
protected:
    /// word bit-width
    static const Index WORD_BITS = BitWidthTypeSelector<T>::value;
    /// byte bit-width (always 8)
    static const Index BYTE_BITS = _ByteBits;
    /// bytes per word
    static const Index BPW = WORD_BITS / BYTE_BITS;

    /// type used for word bit-width
    typedef typename TypeSelector<WORD_BITS, false>::type data_type;

    static codasip_address_t get_index(const codasip_address_t addr);
    static codasip_address_t get_offset(const codasip_address_t addr);

public:
    typedef typename detail::CallTraits<data_type>::param_type param_type;

    template<Endianness _Endianness, class ContainerType>
    static data_type
    read(const ContainerType& src, const codasip_address_t addr, const codasip_address_t memory_size);

    /// interface compatibility - p is not used
    template<Endianness _Endianness, class ContainerType, class _Pt>
    static data_type read(const ContainerType& src,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<_Pt>& p);

    template<Endianness _Endianness, class ContainerType, class _Pt>
    static data_type dread(const ContainerType& src,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<_Pt>& p);

    template<Endianness _Endianness, class ContainerType, class _Pt>
    static void write(ContainerType& dst,
        param_type data,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<_Pt>& p);

    template<Endianness _Endianness, class ContainerType, class _Pt>
    static void dwrite(ContainerType& dst,
        param_type data,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<_Pt>& p);

    template<Endianness _Endianness>
    static data_type create_mask(const Index offset, const Index bc);

    template<Endianness _Endianness>
    static Index get_shift(const Index offset, const Index bc);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
RES_INLINE codasip_address_t UnalignedAhb<T, _ByteBits>::get_index(const codasip_address_t addr)
{
    return addr / BPW;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
RES_INLINE codasip_address_t UnalignedAhb<T, _ByteBits>::get_offset(const codasip_address_t addr)
{
    return addr % BPW;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType>
RES_INLINE typename UnalignedAhb<T, _ByteBits>::data_type
UnalignedAhb<T, _ByteBits>::read(const ContainerType& src,
    const codasip_address_t addr,
    const codasip_address_t memory_size)
{
    return src[get_index(addr) % memory_size];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType, class _Pt>
RES_INLINE typename UnalignedAhb<T, _ByteBits>::data_type
UnalignedAhb<T, _ByteBits>::read(const ContainerType& src,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<_Pt>&)
{
    return read<_Endianness>(src, addr, memory_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType, class _Pt>
RES_INLINE typename UnalignedAhb<T, _ByteBits>::data_type
UnalignedAhb<T, _ByteBits>::dread(const ContainerType& src,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<_Pt>&)
{   // do not perform data shift, must be done by the origin interface
    return read<_Endianness>(src, addr, memory_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType, class _Pt>
RES_INLINE void UnalignedAhb<T, _ByteBits>::write(ContainerType& dst,
    param_type data,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<_Pt>& p)
{
    static_assert(BYTE_BITS == 8, "Byte bit-width must be 8!");
    // word index
    codasip_address_t ind = get_index(addr) % memory_size;
    data_type mask = create_mask<_Endianness>(get_offset(addr), p.get_bc());
    dst[ind] = (dst[ind] & ~mask) | (data & mask);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType, class _Pt>
RES_INLINE void UnalignedAhb<T, _ByteBits>::dwrite(ContainerType& dst,
    param_type data,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<_Pt>& p)
{   // do not perform data shift, must be done by the origin interface
    write<_Endianness>(dst, data, addr, memory_size, p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness>
RES_INLINE typename UnalignedAhb<T, _ByteBits>::data_type
UnalignedAhb<T, _ByteBits>::create_mask(const Index offset, const Index bc)
{
    return BitMask<data_type>(BYTE_BITS * bc) << get_shift<_Endianness>(offset, bc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness>
RES_INLINE Index UnalignedAhb<T, _ByteBits>::get_shift(const Index offset, const Index bc)
{
    if (_Endianness == CP_LITTLE_ENDIAN)
    {
        return offset * BYTE_BITS;
    }
    else
    {
        return (BPW - bc - offset) * BYTE_BITS;
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_UNALIGNED_AHB_H_
