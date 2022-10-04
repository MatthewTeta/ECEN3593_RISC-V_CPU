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
 *  \author Pavel Richtarik
 *  \date   Mar 15, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_UNALIGNED_NATIVE_H_
#define SIMULATOR_RESOURCES_UNALIGNED_NATIVE_H_

#include "simulator/resources/csr_endianness.h"
#include "simulator/resources/csr_unaligned_generic.h"
#include "utility/codasiputils.h"

namespace codasip {
namespace resources {

/**
 * \brief Unaligned accessor - specializations for native types.
 */
#define UNALIGNED_SPEC(T, _ByteBits)                                                                     \
    template<codasip_address_t _Size>                                                                    \
    class Unaligned<T, _ByteBits, _Size> : UnalignedGeneric<T, _ByteBits, _Size>                         \
    {                                                                                                    \
    private:                                                                                             \
        enum                                                                                             \
        {                                                                                                \
            WORD_BITS = UnalignedGeneric<T, _ByteBits, _Size>::WORD_BITS,                                \
            BYTE_BITS = UnalignedGeneric<T, _ByteBits, _Size>::BYTE_BITS,                                \
            BPW = UnalignedGeneric<T, _ByteBits, _Size>::BPW                                             \
        };                                                                                               \
        typedef typename UnalignedGeneric<T, _ByteBits, _Size>::data_type data_type;                     \
        typedef typename TypeSelector<BYTE_BITS, false>::type byte_type;                                 \
        typedef typename detail::CallTraits<T>::param_type param_type;                                   \
                                                                                                         \
    public:                                                                                              \
        template<Endianness _Endianness, class ContainerType>                                            \
        static RES_INLINE T read(const ContainerType& src,                                               \
            const codasip_address_t addr,                                                                \
            const Index bi = 0,                                                                          \
            const Index bc = BPW)                                                                        \
        {                                                                                                \
            return UnalignedGeneric<T, _ByteBits, _Size>::template read<_Endianness>(src, addr, bi, bc); \
        }                                                                                                \
        template<Endianness _Endianness, class ContainerType, class _Pt>                                 \
        static RES_INLINE T read(const ContainerType& src,                                               \
            const codasip_address_t addr,                                                                \
            const Payload<_Pt>& p)                                                                       \
        {                                                                                                \
            return read<_Endianness>(src, addr, p.get_bi(), p.get_bc());                                 \
        }                                                                                                \
        template<Endianness _Endianness>                                                                 \
        static RES_INLINE T                                                                              \
        read(const T* src, const codasip_address_t addr, const Index bi = 0, const Index bc = BPW)       \
        {                                                                                                \
            /* nothing to read */                                                                        \
            if (!bc)                                                                                     \
                return 0;                                                                                \
                                                                                                         \
            /* little */                                                                                 \
            if (_Endianness == CP_LITTLE_ENDIAN)                                                         \
            {                                                                                            \
                return *reinterpret_cast<const data_type*>(                                              \
                           reinterpret_cast<const byte_type*>(src) + addr + bi) &                        \
                    BitMask<data_type>(bc * BYTE_BITS);                                                  \
            }                                                                                            \
            /* big */                                                                                    \
            /* generic version is faster in this case */                                                 \
            if (BPW == sizeof(data_type))                                                                \
            {                                                                                            \
                return UnalignedGeneric<T, _ByteBits, _Size>::template read<_Endianness>(src,            \
                    addr,                                                                                \
                    bi,                                                                                  \
                    bc);                                                                                 \
            }                                                                                            \
                                                                                                         \
            codasip_address_t ind1 = (addr / BPW) % _Size;                                               \
            codasip_address_t offset = addr % BPW;                                                       \
            if (!offset && bc == BPW)                                                                    \
                return src[ind1];                                                                        \
                                                                                                         \
            data_type be[2];                                                                             \
            be[0] = src[(ind1 + 1) % _Size];                                                             \
            be[1] = src[ind1];                                                                           \
            data_type ret = 0;                                                                           \
            for (Index i = 0; i < BPW; i++)                                                              \
            {                                                                                            \
                if (i < bc)                                                                              \
                    *((byte_type*)&ret + i) = *((byte_type*)be + 2 * BPW - offset - bi - bc + i);        \
            }                                                                                            \
            return ret;                                                                                  \
        }                                                                                                \
        template<Endianness _Endianness, class _Pt>                                                      \
        static RES_INLINE T read(const T* src, const codasip_address_t addr, const Payload<_Pt>& p)      \
        {                                                                                                \
            return read<_Endianness>(src, addr, p.get_bi(), p.get_bc());                                 \
        }                                                                                                \
                                                                                                         \
        template<Endianness _Endianness, class ContainerType>                                            \
        static RES_INLINE T dread(const ContainerType& src,                                              \
            const codasip_address_t addr,                                                                \
            const Index bi = 0,                                                                          \
            const Index bc = BPW)                                                                        \
        {                                                                                                \
            return read<_Endianness>(src, addr, bi, bc);                                                 \
        }                                                                                                \
        template<Endianness _Endianness, class ContainerType, class _Pt>                                 \
        static RES_INLINE T dread(const ContainerType& src,                                              \
            const codasip_address_t addr,                                                                \
            const Payload<_Pt>& p)                                                                       \
        {                                                                                                \
            return dread<_Endianness>(src, addr, p.get_bi(), p.get_bc());                                \
        }                                                                                                \
                                                                                                         \
        template<Endianness _Endianness, class ContainerType>                                            \
        static RES_INLINE void write(ContainerType& dst,                                                 \
            param_type data,                                                                             \
            const codasip_address_t addr,                                                                \
            const Index bi = 0,                                                                          \
            const Index bc = BPW)                                                                        \
        {                                                                                                \
            UnalignedGeneric<T, _ByteBits, _Size>::template write<_Endianness>(dst, data, addr, bi, bc); \
        }                                                                                                \
        template<Endianness _Endianness, class ContainerType, class _Pt>                                 \
        static RES_INLINE void                                                                           \
        write(ContainerType& dst, param_type data, const codasip_address_t addr, const Payload<_Pt>& p)  \
        {                                                                                                \
            write<_Endianness>(dst, data, addr, p.get_bi(), p.get_bc());                                 \
        }                                                                                                \
        template<Endianness _Endianness>                                                                 \
        static RES_INLINE void write(T* dst,                                                             \
            param_type data,                                                                             \
            const codasip_address_t addr,                                                                \
            const Index bi = 0,                                                                          \
            const Index bc = BPW)                                                                        \
        {                                                                                                \
            if (!bc)                                                                                     \
                return;                                                                                  \
            /* generic version is faster in this case */                                                 \
            if (BPW == sizeof(data_type))                                                                \
            {                                                                                            \
                UnalignedGeneric<T, _ByteBits, _Size>::template write<_Endianness>(dst,                  \
                    data,                                                                                \
                    addr,                                                                                \
                    bi,                                                                                  \
                    bc);                                                                                 \
                return;                                                                                  \
            }                                                                                            \
                                                                                                         \
            codasip_address_t offset = addr % BPW + bi;                                                  \
            codasip_address_t ind1 = (addr / BPW) % _Size;                                               \
            codasip_address_t ind2 = (ind1 + 1) % _Size;                                                 \
            data_type bedst[2];                                                                          \
            /* little */                                                                                 \
            if (_Endianness == CP_LITTLE_ENDIAN)                                                         \
            {                                                                                            \
                bedst[0] = dst[ind1];                                                                    \
                bedst[1] = dst[ind2];                                                                    \
                byte_type* out = reinterpret_cast<byte_type*>(bedst) + offset;                           \
                for (Index i = 0; i < BPW; i++)                                                          \
                {                                                                                        \
                    if (i < bc)                                                                          \
                        out[i] = reinterpret_cast<const byte_type*>(&data)[i];                           \
                }                                                                                        \
                dst[ind1] = bedst[0];                                                                    \
                dst[ind2] = bedst[1];                                                                    \
            }                                                                                            \
            /* big */                                                                                    \
            else                                                                                         \
            {                                                                                            \
                bedst[0] = dst[ind2];                                                                    \
                bedst[1] = dst[ind1];                                                                    \
                byte_type* out = reinterpret_cast<byte_type*>(bedst) + 2 * BPW - offset - bc;            \
                for (Index i = 0; i < BPW; i++)                                                          \
                {                                                                                        \
                    if (i < bc)                                                                          \
                        out[i] = reinterpret_cast<const byte_type*>(&data)[i];                           \
                }                                                                                        \
                dst[ind1] = bedst[1];                                                                    \
                dst[ind2] = bedst[0];                                                                    \
            }                                                                                            \
        }                                                                                                \
        template<Endianness _Endianness, class _Pt>                                                      \
        static RES_INLINE void                                                                           \
        write(T* dst, param_type data, const codasip_address_t addr, const Payload<_Pt>& p)              \
        {                                                                                                \
            write<_Endianness>(dst, data, addr, p.get_bi(), p.get_bc());                                 \
        }                                                                                                \
                                                                                                         \
        template<Endianness _Endianness, class ContainerType>                                            \
        static RES_INLINE void dwrite(ContainerType& dst,                                                \
            param_type data,                                                                             \
            const codasip_address_t addr,                                                                \
            const Index bi = 0,                                                                          \
            const Index bc = BPW)                                                                        \
        {                                                                                                \
            write<_Endianness>(dst, data, addr, bi, bc);                                                 \
        }                                                                                                \
        template<Endianness _Endianness, class ContainerType, class _Pt>                                 \
        static RES_INLINE void                                                                           \
        dwrite(ContainerType& dst, param_type data, const codasip_address_t addr, const Payload<_Pt>& p) \
        {                                                                                                \
            write<_Endianness>(dst, data, addr, p.get_bi(), p.get_bc());                                 \
        }                                                                                                \
    };

// create specializations for native types
UNALIGNED_SPEC(short, 8)
//UNALIGNED_SPEC(int, 16)
UNALIGNED_SPEC(int, 8)
//UNALIGNED_SPEC(long, 16)
UNALIGNED_SPEC(long, 8)
//UNALIGNED_SPEC(long long, 32)
//UNALIGNED_SPEC(long long, 16)
UNALIGNED_SPEC(long long, 8)

UNALIGNED_SPEC(unsigned short, 8)
//UNALIGNED_SPEC(unsigned int, 16)
UNALIGNED_SPEC(unsigned int, 8)
//UNALIGNED_SPEC(unsigned long, 16)
UNALIGNED_SPEC(unsigned long, 8)
//UNALIGNED_SPEC(unsigned long long, 32)
//UNALIGNED_SPEC(unsigned long long, 16)
UNALIGNED_SPEC(unsigned long long, 8)

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_UNALIGNED_NATIVE_H_
