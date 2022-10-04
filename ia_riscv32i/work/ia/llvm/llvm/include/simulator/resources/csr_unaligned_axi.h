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
 *  \date   2017-11-08
 *  \brief  Definition of the class codasip::resources::UnalignedAxi.
 */

#ifndef SIMULATOR_RESOURCES_CSR_UNALIGNED_AXI_H_
#define SIMULATOR_RESOURCES_CSR_UNALIGNED_AXI_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_unaligned_ahb.h"
#include "utility/codasiputils.h"

namespace codasip {
namespace resources {
namespace detail {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::detail::WriteStrobeHelper
 *  \brief  Implements write into an array using write strobes.
 *  \tparam T word data type
 *  \tparam _ByteBits Bit-Width of the byte
 *  \}
 */
template<class T, int _ByteBits>
class WriteStrobeHelper
{
public:
    /// \brief  Data type used for effective parameter passing
    typedef typename detail::CallTraits<T>::param_type param_type;
    /**
     *  \brief  Create write into the container/array using write strobes.
     *  \param  dst target to write
     *  \param  data source data to write
     *  \param  idx index to the target container/array
     *  \param  wstr write strobes
     */
    template<class ContainerType, class WSTRB>
    static void
    DoWrite(ContainerType& dst, param_type data, const codasip_address_t idx, const WSTRB& wstrb);

private:
    template<class WSTRB>
    static T CreateWriteMask(const WSTRB&);
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<class ContainerType, class WSTRB>
inline void WriteStrobeHelper<T, _ByteBits>::DoWrite(ContainerType& dst,
    param_type data,
    const codasip_address_t idx,
    const WSTRB& wstrb)
{
    const auto mask = CreateWriteMask(wstrb);
    dst[idx] = (dst[idx] & ~mask) | (data & mask);
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Create word bit mask by extending write strobes.
 *  \param  wstrb write strobe mask (single write enable bit per byte)
 */
template<class T, int _ByteBits>
template<class WSTRB>
inline T WriteStrobeHelper<T, _ByteBits>::CreateWriteMask(const WSTRB& wstrb)
{
    T wordMask = 0;
    T byteMask = BitMask<T>(_ByteBits);
    WSTRB remainingStrobes = wstrb;
    while (remainingStrobes > 0)
    {
        if (remainingStrobes & 1u)
        {
            wordMask |= byteMask;
        }
        remainingStrobes >>= 1;
        byteMask = LeftShift(byteMask, _ByteBits);
    }
    return wordMask;
}

}   // namespace detail

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  UnalignedAxi
 *  \brief  Accepts array of data and it reads the word as specified in AXI4-Lite.
 *  \tparam T word data type
 *  \tparam _ByteBits Bit-Width of the byte
 */
template<class T, int _ByteBits>
class UnalignedAxi : public UnalignedAhb<T, _ByteBits>
{
private:
    /// \brief  Shortcut for the parent class
    typedef UnalignedAhb<T, _ByteBits> Base;
    /// \brief  Performs actual write
    typedef detail::WriteStrobeHelper<T, _ByteBits> WriteStrobeHelperType;

public:
    /// \brief  Import data type used for effective parameter passing
    using typename Base::param_type;
    /**
     *  \brief  Perform actual write into of a word into the array.
     *  \param  dst target array to write
     *  \param  data source data to write
     *  \param  addr target array index
     *  \param  memory_size target memory size
     *  \param  p source transaction properties (payload)
     */
    template<Endianness _Endianness, class ContainerType, class _Pt>
    static void write(ContainerType& dst,
        param_type data,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<_Pt>& p);
    /**
     *  \brief  Perform actual debug write into of a word into the array.
     *  \copydetails write()
     */
    template<Endianness _Endianness, class ContainerType, class _Pt>
    static void dwrite(ContainerType& dst,
        param_type data,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<_Pt>& p);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType, class _Pt>
RES_INLINE void UnalignedAxi<T, _ByteBits>::write(ContainerType& dst,
    param_type data,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<_Pt>& p)
{
    static_assert(_ByteBits == 8, "Byte bit-width must be 8!");
    static_assert(std::is_same<T, _Pt>::value, "Payload type does not match underlying type!");
    WriteStrobeHelperType::DoWrite(dst, data, Base::get_index(addr) % memory_size, p.get_axi_wstrb());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType, class _Pt>
RES_INLINE void UnalignedAxi<T, _ByteBits>::dwrite(ContainerType& dst,
    param_type data,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<_Pt>& p)
{   // do not perform data shift, must be done by the origin interface
    write<_Endianness>(dst, data, addr, memory_size, p);
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_UNALIGNED_AXI_H_
