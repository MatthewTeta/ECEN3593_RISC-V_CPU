/**
 * Codasip s.r.o.
 * 
 * CONFIDENTIAL 
 *
 * Copyright 2021 Codasip s.r.o.
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
 *  \author Petr Hons
 *  \date   7. 4. 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_DUMPER_ADDRESS_H_
#define SIMULATOR_RESOURCES_CSR_DUMPER_ADDRESS_H_

#include "simulator/resources/csr_ahb_pac.h"
#include "simulator/resources/csr_axi_lite_pac.h"
#include "simulator/resources/csr_axi_pac.h"
#include "simulator/resources/csr_cpb_pac.h"
#include "simulator/resources/csr_dumper_base.h"
#include "simulator/resources/csr_interface.h"
#include "simulator/resources/csr_payload.h"

#include <vector>

namespace codasip {
namespace resources {
namespace detail {
/**
 *  \internal
 *  \brief  Syntax shortcut to simplify selection of correct PAC implementation
 *          used by \ref DumperAddress.
 */
template<class T, class PAC, typename R = bool>
using is_pac = typename std::enable_if<std::is_same<T, PAC>::value, R>::type;

}   // namespace detail

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::Dumper
 *  \brief  Dumps changes of addressable resource (register file, interface) into the file
 *  \}
 */
template<class T>
class DumperAddress : public DumperBase<T>
{
    typedef DumperBase<T> Base;
    typedef Payload<typename T::data_type> DumpPayload;

public:
    using typename T::param_type;
    /**
     * \copydoc DumperBase::DumperBase
     */
    DumperAddress(const std::string& name, const Uid uid);
    /**
     *  \brief  Detect change of resources
     *  \{
     */
    void write(param_type data, const codasip_address_t addr = 0);
    void blocking_d(DumpPayload& p);
    void transport_d(DumpPayload& p, const Phase phase);
    /**
     *  \}
     */
    /**
     *  \brief  Dump changes into the file
     *  \param  clockCycle Current clock cycle counter
     *  \{
     */
    void dump(const Counter clockCycle);
    /**
     *  \}
     */
private:
    // AXI-lite
    template<class _PAC>
    static detail::is_pac<_PAC, AxiLitePac> IsWriteAddressValid(const DumpPayload&);
    template<class _PAC>
    detail::is_pac<_PAC, AxiLitePac> IsWriteDataValid(const DumpPayload&) const;
    template<class _PAC>
    detail::is_pac<_PAC, AxiLitePac, void> StoreChange(const DumpPayload&, const DumpPayload&);
    // AXI
    template<class _PAC>
    static detail::is_pac<_PAC, AxiPac> IsWriteAddressValid(const DumpPayload&);
    template<class _PAC>
    detail::is_pac<_PAC, AxiPac> IsWriteDataValid(const DumpPayload&) const;
    template<class _PAC>
    detail::is_pac<_PAC, AxiPac, void> StoreChange(const DumpPayload&, const DumpPayload&);
    // CPB
    template<class _PAC>
    static detail::is_pac<_PAC, CpbPac> IsWriteAddressValid(const DumpPayload&);
    template<class _PAC>
    detail::is_pac<_PAC, CpbPac> IsWriteDataValid(const DumpPayload&) const;
    template<class _PAC>
    detail::is_pac<_PAC, CpbPac, void> StoreChange(const DumpPayload&, const DumpPayload&);

    // phasing
    void DoPhaseAddress(const DumpPayload&);
    void DoPhaseData(const DumpPayload&);

protected:
    /// Vector of payloads that were written in current clock cycle
    std::vector<DumpPayload> m_Changes;
    /// Stored payload from request, used in finish to determine sbi,sbc and address
    DumpPayload m_RequestPayload;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         DumperAddress                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline DumperAddress<T>::DumperAddress(const std::string& name, const Uid uid)
  : Base(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void DumperAddress<T>::dump(const Counter clockCycle)
{
    if (!this->m_Dump || m_Changes.empty())
    {
        return;
    }

    this->m_Dump->DumpClockCycle(clockCycle);

    for (const auto& payload : m_Changes)
    {
        this->m_Dump->DumpAddr(this->get_signature(),
            payload.get_data(),
            payload.get_address(),
            T::BYTE_BITS * payload.get_bc());
    }
    m_Changes.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void DumperAddress<T>::write(param_type data, const codasip_address_t addr)
{
    if (this->m_Dump)
    {
        m_Changes.emplace_back();
        auto& payload = m_Changes.back();
        payload.set_data(data);
        payload.set_address(addr);
        payload.set_bc(T::BPW);
    }

    T::write(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void DumperAddress<T>::blocking_d(DumpPayload& p)
{
    T::blocking_d(p);
    if (this->m_Dump && p.get_command() == CP_CMD_WRITE && !p.is_error())
    {
        this->template StoreChange<typename T::PacType>(p, p);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void DumperAddress<T>::transport_d(DumpPayload& p, const Phase phase)
{
    T::transport_d(p, phase);

    switch (phase)
    {
        case CP_PHS_ADDRESS:
        case CP_PHS_ADDRESS_WRITE:
            DoPhaseAddress(p);
            break;
        case CP_PHS_DATA:
        case CP_PHS_DATA_WRITE:
            DoPhaseData(p);
            break;
        case CP_PHS_DATA_READ:
        case CP_PHS_ADDRESS_READ:
        case CP_PHS_RESPONSE_WRITE:
            break;
    }
}

/**
 *  \brief  Indicates whether or not there is a new AMBA AXI4 write transaction
 *          and the slave is ready.
 *  \param  p source transaction information
 */
template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, AxiLitePac>
DumperAddress<T>::IsWriteAddressValid(const DumpPayload& p)
{
    return (p.get_axi_valid() == CP_AXI_VALID) && (p.get_axi_ready() == CP_AXI_READY);
}

template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, AxiPac> DumperAddress<T>::IsWriteAddressValid(const DumpPayload& p)
{
    return (p.get_axi_valid() == CP_AXI_VALID) && (p.get_axi_ready() == CP_AXI_READY);
}

/**
 *  \brief  Indicates whether or not there is valid AMBA AXI4 write data from
 *          the master and the slave is ready to accept.
 *  \copydetails DoPhaseData()
 */
template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, AxiLitePac>
DumperAddress<T>::IsWriteDataValid(const DumpPayload& p) const
{
    return (p.get_axi_valid() == CP_AXI_VALID) && (p.get_axi_ready() == CP_AXI_READY);
}

template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, AxiPac> DumperAddress<T>::IsWriteDataValid(const DumpPayload& p) const
{
    return (p.get_axi_valid() == CP_AXI_VALID) && (p.get_axi_ready() == CP_AXI_READY);
}

/**
 *  \brief  Store required payload attributes as a change for AXI4-Lite.
 *  \param[in] addr payload containing valid control signals (address)
 *  \param[in] data address payload containing write data (transfer size)
 */
template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, AxiLitePac, void>
DumperAddress<T>::StoreChange(const DumpPayload& addr, const DumpPayload& data)
{
    typedef Interface<T> InterfaceBaseType;
    // create empty payload and set just mandatory attributes as in IA mode
    m_Changes.emplace_back();
    auto& p = m_Changes.back();
    p.set_address(addr.get_address() + data.get_axi_address_offset());
    p.set_bc(data.get_axi_transfer_size());
    // moves valid write data bits to LSB position
    const auto shift = InterfaceBaseType::get_amba_shift(
        InterfaceBaseType::get_offset(p.get_address(), T::BPW),
        p.get_bc());
    p.set_data(data.get_data() >> shift);
}

template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, AxiPac, void>
DumperAddress<T>::StoreChange(const DumpPayload& addr, const DumpPayload& data)
{
    typedef Interface<T> InterfaceBaseType;
    // create empty payload and set just mandatory attributes as in IA mode
    m_Changes.emplace_back();
    auto& p = m_Changes.back();
    p.set_address(addr.get_address() + data.get_axi_address_offset());
    p.set_bc(data.get_axi_transfer_size());
    // moves valid write data bits to LSB position
    const auto shift = InterfaceBaseType::get_amba_shift(
        InterfaceBaseType::get_offset(p.get_address(), T::BPW),
        p.get_bc());
    p.set_data(data.get_data() >> shift);
}

/**
 *  \brief  Indicates whether or not there is a new CPB write transaction
 *          and the slave is ready.
 *  \param  p source transaction information
 */
template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, CpbPac> DumperAddress<T>::IsWriteAddressValid(const DumpPayload& p)
{
    return (p.get_cpb_aready() == CP_CPB_READY) && (p.get_cpb_avalid() == CP_CPB_VALID) &&
        (p.get_cpb_write() == CP_CPB_WRITE);
}

/**
 *  \brief  Indicates whether or not there is valid CPB write data from
 *          the master and the slave is ready to accept.
 *  \copydetails DoPhaseData()
 */
template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, CpbPac> DumperAddress<T>::IsWriteDataValid(const DumpPayload& p) const
{
    return (p.get_cpb_valid() == CP_CPB_VALID) && (m_RequestPayload.get_cpb_write() == CP_CPB_WRITE);
}

/**
 *  \brief  Store required payload attributes as a change for CPB.
 *  \param[in]  addr payload containing valid control signals (address, transfer size),
 *              write data and write strobe
 */
template<class T>
template<class _PAC>
RES_INLINE detail::is_pac<_PAC, CpbPac, void>
DumperAddress<T>::StoreChange(const DumpPayload& addr, const DumpPayload&)
{
    typedef Interface<T> InterfaceBaseType;
    // create empty payload and set just mandatory attributes as in IA mode
    m_Changes.emplace_back();
    auto& p = m_Changes.back();
    p.set_address(addr.get_address() + addr.get_cpb_address_offset());
    p.set_bc(addr.get_cpb_transfer_size());
    // moves valid write data bits to LSB position
    const auto shift = InterfaceBaseType::get_amba_shift(
        InterfaceBaseType::get_offset(p.get_address(), T::BPW),
        p.get_bc());
    p.set_data(addr.get_data() >> shift);
}

/**
 *  \brief  Store transaction attributes if there is a new valid transaction.
 *  \param  p source transaction information
 */
template<class T>
RES_INLINE void DumperAddress<T>::DoPhaseAddress(const DumpPayload& p)
{
    if (this->m_Dump && this->template IsWriteAddressValid<typename T::PacType>(p))
    {   // have to store transaction attributes (e.g. address)
        // because the payload might be changed in data phase
        // e.g. bus will translate the address
        // TODO FIXME won't work if AXI slave is able to buffer multiple addresses
        // before accepting any data (outstanding writes)
        m_RequestPayload = p;
    }
}

/**
 *  \brief  Store changes is there is a valid write data.
 *  \copydetails DoPhaseAddress()
 */
template<class T>
RES_INLINE void DumperAddress<T>::DoPhaseData(const DumpPayload& p)
{
    if (this->m_Dump && this->template IsWriteDataValid<typename T::PacType>(p))
    {   // store transaction attributes from the address phase
        if (!p.is_error())
        {
            this->template StoreChange<typename T::PacType>(m_RequestPayload, p);
        }
        // always reset the payload (even after a previous error)
        m_RequestPayload.reset();
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_DUMPER_ADDRESS_H_
