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

#ifndef SIMULATOR_RESOURCES_CSR_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_INTERFACE_H_

#include "simulator/resources/csr_interface_base.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/simbase/simulator_resources.h"
#include "utility/codasiputils.h"

namespace codasip {
namespace resources {

/**
 *  \brief  Get name of callback selector with custom names of all callback methods.
 *          This name is used in third template parameter in Interface class.
 *  \param  b_cb Name of blocking callback method in underling module.
 *  \param  t_cb Name of transfer callback method in underling module.
 */
#define CODASIP_IFACE_CB_SELECT_FULL(b_cb, t_cb) codasip_iface_select_##b_cb##_##t_cb

/**
 *  \brief  Create interface callback selector with custom names of all callback methods.
 *  \param  b_cb Name of blocking callback method in underling module.
 *  \param  t_cb Name of transfer callback method in underling module.
 */
#define CODASIP_IFACE_CB_SELECTOR_FULL(b_cb, t_cb)                                     \
    struct CODASIP_IFACE_CB_SELECT_FULL(b_cb, t_cb)                                    \
    {                                                                                  \
        template<class M, class T, class U>                                            \
        static inline void blocking_cb(M& module, T& p, const U& uid)                  \
        {                                                                              \
            module.b_cb(p, uid);                                                       \
        }                                                                              \
        template<class M, class T, class P, class U>                                   \
        static inline void transport_cb(M& module, T& p, const P& phase, const U& uid) \
        {                                                                              \
            module.t_cb(p, phase, uid);                                                \
        }                                                                              \
    }

/**
 *  \brief  Create interface callback selector with standard names of callback methods.
 *          The names are IFACE_blocking_cb, IFACE_transport_cb.
 *  \param  name Name of IFACE prefix (usually interface name).
 */
#define CODASIP_IFACE_CB_SELECTOR(name) \
    CODASIP_IFACE_CB_SELECTOR_FULL(name##_blocking_cb, name##_transport_cb)

/**
 *  \brief  Get name of callback selector with standard names of callback methods.
 *          This name is used in third template parameter in Interface class.
 *  \param  name Name of IFACE prefix (usually interface name).
 */
#define CODASIP_IFACE_CB_SELECT(name) \
    CODASIP_IFACE_CB_SELECT_FULL(name##_blocking_cb, name##_transport_cb)

namespace detail {

// Create default selector in separate namespace
CODASIP_IFACE_CB_SELECTOR_FULL(blocking_cb, transport_cb);

/**
 * \brief Empty module, provides empty callbacks.
 */
template<class T>
class InterfaceModule
{
public:
    void blocking_cb(Payload<T>&, Uid) {}
    void transport_cb(Payload<T>&, const Phase, Uid) {}
};

}   // namespace detail

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  Interface
 *  \brief  Basic interface that can be placed on a platform
 *  \}
 */
template<class T,
    class M = detail::InterfaceModule<typename T::data_type>,
    class S = detail::CODASIP_IFACE_CB_SELECT_FULL(blocking_cb, transport_cb)>
class Interface : public T, public InterfaceBase<typename T::data_type>, public simulator::InterfaceInfo
{
public:
    /// Data type
    using typename T::data_type;
    using typename T::param_type;
    using typename T::payload_type;
    /// Mixin base
    typedef T mixin_base;
    /// Module type
    typedef M module_type;
    /// Callback selector
    typedef S selector_type;
    /// Callback function
    typedef void (M::*Cb)(payload_type&);

    /**
     * \copydoc Sentinel::Sentinel
     */
    Interface(const std::string& name, const Uid uid, M* module = NULL);
    /**
     *  \{
     *  \brief  Access methods for the IA mode. These methods should be implemented
     *          in the derived classes based on the bus protocol.
     *  \internal
     *  \note   Here are only declarations to avoid virtual calls.
     */
    data_type read(const codasip_address_t addr, const Index bc);
    data_type dread(const codasip_address_t addr, const Index bc = T::BPW);
    void write(param_type data, const codasip_address_t addr, const Index bc);
    void dwrite(param_type data, const codasip_address_t addr, const Index bc = T::BPW);
    void load(param_type data, const codasip_address_t addr, const Index bc = T::BPW);
    /** \} */

    void blocking(payload_type& p) override;
    void transport(payload_type& p, const Phase phase) override;

    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override;
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override;
    /// \copydoc ResourceInfo::GetBitWidth
    unsigned GetBitWidth() const override;
    /// \copydoc AddressableInfo::GetLAU
    unsigned GetLAU() const override;
    /// \copydoc AddressableInfo::GetAddrBitWidth
    unsigned GetAddrBitWidth() const override;
    /// \copydoc AddressableInfo::IsBig
    bool IsBig() const override;
    /// \copydoc InterfaceInfo::GetFlag
    Flag GetFlag() const override;
    /// \copydoc InterfaceInfo::GetDataAlignment
    const simulator::InterfaceInfo::DataAlignment& GetDataAlignment() const override;

    /**
     *  \{
     *  \brief AMBA shifting helpers
     */

    /**
     * \brief Get aligned portion of address.
     * 
     * When accessing an address in aligned mode, the address bitmask is split into 
     * aligned address portion (returned by this function) and the offset, returned
     * by \ref get_offset().  
     * 
     * \param addr 
     * \param align must be an exponent of 2
     * \return codasip_address_t 
     */
    static codasip_address_t
    get_aligned_address(const codasip_address_t addr, const codasip_address_t align);
    /**
     * \brief Returns an offset part of address, masked according to align.
     * 
     * \param addr 
     * \param align must be an exponent of 2 (e.g. 2,4,8, etc.) 
     * \return Index 
     */
    static Index get_offset(const codasip_address_t addr, const codasip_address_t align);
    static Index get_amba_shift(const Index offset, const Index bc);
    static data_type create_amba_mask(const Index offset, const Index bc);
    /** \} */

    /**
     *  \brief  Create AXI/CPB write strobe with respect to the interface endianness.
     *  \param  offset address offset within the word
     *  \param  bc transfer size in bytes, must be a power of 2
     */
    template<class WSTRB>
    static WSTRB CreateWriteStrobe(const Index offset, const Index bc);
    /**
     *  \brief  Reconstruct address offset and transfer size from AXI/CPB write strobe
     *          with respect to the interface endianness.
     *  \param[out] offset address offset within the word
     *  \param[out] bc transfer size in bytes
     *  \param[in]  wstrb write strobes
     */
    template<class WSTRB>
    static void CreateOffsetTransferSizeFromWstrb(Index& offset, Index& bc, const WSTRB& wstrb);

protected:
    void blocking_cb(payload_type& p) override;
    void transport_cb(payload_type& p, const Phase phase) override;
    void DoAbortSimulation() const noexcept(false);

    /// Payload for helper functions
    payload_type m_Payload;
    /// Owning module
    M* m_Module;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
inline Interface<T, M, S>::Interface(const std::string& name, const Uid uid, M* module)
  : T(name, uid)
  , m_Module(module)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void Interface<T, M, S>::blocking(payload_type& p)
{
    blocking_cb(p);
    this->handle_blocking_cb(p);
    T::blocking_d(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void Interface<T, M, S>::transport(payload_type& p, const Phase phase)
{
    transport_cb(p, phase);
    this->handle_transport_cb(p, phase);
    T::transport_d(p, phase);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void Interface<T, M, S>::blocking_cb(payload_type& p)
{
    T::blocking(p);
    if (m_Module)
    {
        S::blocking_cb(*m_Module, p, this->get_uid());
    }
    if (this->IsRouterOnly())
    {
        T::blocking_d(p);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void Interface<T, M, S>::transport_cb(payload_type& p, const Phase phase)
{
    T::transport(p, phase);
    if (m_Module)
    {
        S::transport_cb(*m_Module, p, phase, this->get_uid());
    }
    if (this->IsRouterOnly())
    {
        T::transport_d(p, phase);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
void Interface<T, M, S>::DoAbortSimulation() const noexcept(false)
{
    throw exceptions::BasicError(
        "Aborted simulation, fatal error when accessing '" + this->get_signature() + "'");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE Uid Interface<T, M, S>::GetUid() const
{
    return T::get_uid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE const std::string& Interface<T, M, S>::GetName() const
{
    return T::get_name();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE unsigned Interface<T, M, S>::GetBitWidth() const
{
    return T::WORD_BITS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE unsigned Interface<T, M, S>::GetLAU() const
{
    return T::BYTE_BITS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE unsigned Interface<T, M, S>::GetAddrBitWidth() const
{
    return T::ADDR_BITS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE bool Interface<T, M, S>::IsBig() const
{
    return T::ENDIANNESS == CP_BIG_ENDIAN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE simulator::InterfaceInfo::Flag Interface<T, M, S>::GetFlag() const
{
    return FLAG_RW;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE const simulator::InterfaceInfo::DataAlignment& Interface<T, M, S>::GetDataAlignment() const
{
    return T::get_data_alignment();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE codasip_address_t Interface<T, M, S>::get_aligned_address(const codasip_address_t addr,
    const codasip_address_t align)
{
    return (addr & ~(align - 1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE Index Interface<T, M, S>::get_offset(const codasip_address_t addr,
    const codasip_address_t align)
{
    return (addr & (align - 1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE Index Interface<T, M, S>::get_amba_shift(const Index offset, const Index bc)
{
    if (T::ENDIANNESS == CP_LITTLE_ENDIAN)
    {
        return offset * T::BYTE_BITS;
    }
    else
    {
        return (T::BPW - bc - offset) * T::BYTE_BITS;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
Interface<T, M, S>::create_amba_mask(const Index offset, const Index bc)
{
    return BitMask<data_type>(T::BYTE_BITS * bc) << get_amba_shift(offset, bc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class WSTRB>
RES_INLINE WSTRB Interface<T, M, S>::CreateWriteStrobe(const Index offset, const Index bc)
{
    const Index shift = (T::ENDIANNESS == CP_LITTLE_ENDIAN) ? offset : (T::BPW - bc - offset);
    return BitMask<WSTRB>(bc) << shift;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class WSTRB>
inline void
Interface<T, M, S>::CreateOffsetTransferSizeFromWstrb(Index& offset, Index& bc, const WSTRB& wstrb)
{
    bc = 0;
    offset = 0;
    bool offsetFound = false;
    // for BC count the number of asserted bits
    // patterns like 1001 are expected not to occur
    // for offset find the first asserted bit and compute the offset
    for (unsigned ii = 0; ii < T::BPW; ++ii)
    {
        const auto lsb = (wstrb & static_cast<WSTRB>(1u) << ii) != 0u;
        bc += lsb;
        if (!offsetFound && lsb != 0)
        {
            offsetFound = true;
            offset = ii;
        }
    }
    if (T::ENDIANNESS == CP_BIG_ENDIAN)
    {
        offset = T::BPW - bc - offset;
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_INTERFACE_H_
