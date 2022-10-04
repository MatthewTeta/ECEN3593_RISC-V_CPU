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
 *  \author Potesil Josef
 *  \date   27. 11. 2018
 *  \brief  Definition of the class codasip::resources::UnalignedCpb.
 */

#ifndef SIMULATOR_RESOURCES_CSR_UNALIGNED_CPB_H_
#define SIMULATOR_RESOURCES_CSR_UNALIGNED_CPB_H_

#include "simulator/resources/csr_unaligned_axi.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::UnalignedCpb
 *  \brief  Accepts array of data and it reads the word as specified in CPB.
 *  \copydetails UnalignedAxi
 *  \}
 */
template<class T, int _ByteBits>
class UnalignedCpb : public UnalignedAxi<T, _ByteBits>
{
private:
    /// \brief  Shortcut for the parent class
    typedef UnalignedAxi<T, _ByteBits> Base;
    /// \brief  Helper class performing actual write
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
    template<Endianness _Endianness, class ContainerType>
    static void write(ContainerType& dst,
        param_type data,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<T>& p);
    /**
     *  \brief  Perform actual debug write into of a word into the array.
     *  \copydetails write()
     */
    template<Endianness _Endianness, class ContainerType>
    static void dwrite(ContainerType& dst,
        param_type data,
        const codasip_address_t addr,
        const codasip_address_t memory_size,
        const Payload<T>& p);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType>
RES_INLINE void UnalignedCpb<T, _ByteBits>::write(ContainerType& dst,
    param_type data,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<T>& p)
{
    WriteStrobeHelperType::DoWrite(dst, data, Base::get_index(addr) % memory_size, p.get_cpb_wstrb());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int _ByteBits>
template<Endianness _Endianness, class ContainerType>
RES_INLINE void UnalignedCpb<T, _ByteBits>::dwrite(ContainerType& dst,
    param_type data,
    const codasip_address_t addr,
    const codasip_address_t memory_size,
    const Payload<T>& p)
{   // do not perform data shift, must be done by the origin interface
    write<_Endianness>(dst, data, addr, memory_size, p);
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_UNALIGNED_CPB_H_
