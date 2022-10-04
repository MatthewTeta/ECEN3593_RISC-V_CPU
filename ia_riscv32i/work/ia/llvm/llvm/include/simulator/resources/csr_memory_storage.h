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
 *  \date   Mar 11, 2016
 *  \brief  Implementation of the class codasip::resources::MemoryStorage.
 */

#ifndef SIMULATOR_RESOURCES_CSR_MEMORY_STORAGE_H_
#define SIMULATOR_RESOURCES_CSR_MEMORY_STORAGE_H_

#include "simulator/dumpl/dump_stream.h"
#include "simulator/resources/csr_memory.h"
#include "simulator/resources/csr_payload_sentinel.h"
#include "simulator/resources/csr_sentinel.h"   // Logging
#include "simulator/resources/csr_storage_sentinel.h"
#include "simulator/resources/detail/csr_storage_helpers.h"

#include <type_traits>
#include <unordered_map>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  MemoryStorage
 *  \brief  Class holding data for large memories using a hash map.
 *  \}
 */
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
class MemoryStorage : public Sentinel
{
public:
    typedef T data_type;

    /// \copydoc PayloadSentinel<T, _ByteBits, _AddrBits>::ADDR_BITS
    static const Index ADDR_BITS = PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::ADDR_BITS;
    /// \copydoc PayloadSentinel<T, _ByteBits, _AddrBits>::WORD_BITS
    static const Index WORD_BITS = PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::WORD_BITS;
    /// \copydoc PayloadSentinel<T, _ByteBits, _AddrBits>::BYTE_BITS
    static const Index BYTE_BITS = PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::BYTE_BITS;
    /// \copydoc PayloadSentinel<T, _ByteBits, _AddrBits>::BPW
    static const Index BPW = PayloadSentinel<T, _ByteBits, _AddrBits, _Endianness, _PAC>::BPW;
    /// \copydoc PayloadSentinel<T, _ByteBits, _AddrBits>::ENDIANNESS
    static const Endianness ENDIANNESS = _Endianness;

    /// Unaligned handler type
    typedef _UH UnalignedHandler;
    /// Protocol specific address checker type
    typedef _PAC ProtoAddressChecker;

    /**
     * \copydoc Sentinel::Sentinel
     */
    MemoryStorage(const std::string& name, const Uid uid, const codasip_address_t memory_size);
    /**
     * \brief Destructor
     */
    ~MemoryStorage();
    /**
     * \brief forward for size getter
     */
    codasip_address_t get_size() const;
    /**
     * \{
     * \brief Data access
     */
    template<class _Pt>
    void blocking(Payload<_Pt>& p);
    template<class _Pt>
    void transport(Payload<_Pt>& p, const Phase phase);
    /** \} */
    /**
     * \brief Dump memory to the stream
     */
    void dump(simulator::DumpStream& stream);

private:
    template<class _Pt>
    void read(Payload<_Pt>&) const;
    template<class _Pt>
    void dread(Payload<_Pt>&) const;
    template<class _Pt>
    void write(const Payload<_Pt>&);
    template<class _Pt>
    void dwrite(const Payload<_Pt>&);
    template<class _Pt>
    void do_request(Payload<_Pt>& p);
    template<class _Pt>
    void do_response(Payload<_Pt>& p);

    codasip_address_t get_truncated_address(const codasip_address_t address) const;

    /// data itself
    _MemoryStorageImpl m_MemoryImpl;
    codasip_address_t m_Size;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
inline MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::MemoryStorage(
    const std::string& name,
    const Uid uid,
    const codasip_address_t memory_size)
  : Sentinel(name, uid)
  , m_MemoryImpl(memory_size / BPW)
  , m_Size(memory_size)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
inline MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::~MemoryStorage()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::blocking(
    Payload<_Pt>& p)
{
    ProtoAddressChecker::check_address(p, *this);
    if (!p.is_error())
    {
        switch (p.get_command())
        {
            case CP_CMD_READ:
                read(p);
                break;
            case CP_CMD_DREAD:
                dread(p);
                break;
            case CP_CMD_WRITE:
                write(p);
                break;
            case CP_CMD_LOAD:
            case CP_CMD_DWRITE:
                dwrite(p);
                break;
            default:
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::do_request(
    Payload<_Pt>& p)
{
    ProtoAddressChecker::check_address(p, *this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::do_response(
    Payload<_Pt>& p)
{
    ProtoAddressChecker::check_address(p, *this);
    if (!p.is_error())
    {
        switch (p.get_command())
        {
            case CP_CMD_READ:
                read(p);
                break;
            case CP_CMD_WRITE:
                write(p);
                break;
            default:
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::transport(
    Payload<_Pt>& p,
    const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
        case CP_PHS_ADDRESS_READ:
        case CP_PHS_ADDRESS_WRITE:
            do_request(p);
            return;
        case CP_PHS_DATA:
        case CP_PHS_DATA_READ:
        case CP_PHS_DATA_WRITE:
            do_response(p);
            return;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::read(
    Payload<_Pt>& p) const
{
    p.set_data(UnalignedHandler::template read<_Endianness>(m_MemoryImpl,
        get_truncated_address(p.get_address()),
        get_size(),
        p));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::dread(
    Payload<_Pt>& p) const
{
    p.set_data(UnalignedHandler::template dread<_Endianness>(m_MemoryImpl,
        get_truncated_address(p.get_address()),
        get_size(),
        p));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::write(
    const Payload<_Pt>& p)
{
    UnalignedHandler::template write<_Endianness>(m_MemoryImpl,
        p.get_data(),
        get_truncated_address(p.get_address()),
        get_size(),
        p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
template<class _Pt>
RES_INLINE void
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::dwrite(
    const Payload<_Pt>& p)
{
    UnalignedHandler::template dwrite<_Endianness>(m_MemoryImpl,
        p.get_data(),
        get_truncated_address(p.get_address()),
        get_size(),
        p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
inline void MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::dump(
    simulator::DumpStream& stream)
{
    const auto size_in_words = get_size() / BPW;
    for (codasip_address_t i = 0; i < size_in_words; ++i)
    {
        if (m_MemoryImpl[i])
        {
            stream.DumpAddr(this->get_signature(), m_MemoryImpl[i], i * BPW, WORD_BITS);
        }
    }
}

template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
inline codasip_address_t
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::get_size() const
{
    return m_Size;
}

template<class T, Index _ByteBits, Index _AddrBits, Endianness _Endianness, class _MemoryStorageImpl, class _UH, class _PAC>
RES_INLINE codasip_address_t
MemoryStorage<T, _ByteBits, _AddrBits, _Endianness, _MemoryStorageImpl, _UH, _PAC>::get_truncated_address(
    const codasip_address_t address) const
{
    return detail::TruncateAddress<ADDR_BITS>(address, get_size());
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_MEMORY_STORAGE_H_
