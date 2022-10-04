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
 *  \date   Sep 14, 2017
 *  \brief  Definition of the class codasip::resources::AhbLiteInitiatorInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AHB_INITIATOR_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_AHB_INITIATOR_INTERFACE_H_

#include "simulator/resources/csr_interface.h"

//#define CODASIP_AHB_INITIATOR_DBG_OUT
#ifdef CODASIP_AHB_INITIATOR_DBG_OUT
#    define CODASIP_AHB_INITIATOR_DBG_OUT_PRINT(cmd, p)                                       \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() << ": AHB " \
                  << cmd << " " << p.PrintAhbLite() << std::endl
#else
#    define CODASIP_AHB_INITIATOR_DBG_OUT_PRINT(cmd, p)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AhbLiteInitiatorInterface
 *  \brief  Interface that handles AMBA 3 AHB-Lite protocol.
 *  \}
 */
template<class T,
    class M = detail::InterfaceModule<typename T::data_type>,
    class S = detail::CODASIP_IFACE_CB_SELECT_FULL(blocking_cb, transport_cb)>
class AhbLiteInitiatorInterface : public Interface<T, M, S>
{
public:
    using typename T::data_type;
    using typename T::param_type;
    using typename T::payload_type;
    /// \brief  Interface base class
    typedef Interface<T, M, S> InterfaceBaseType;
    /// Number of bytes in word
    static const Index SUBBLOCKS = T::WORD_BITS / T::BYTE_BITS;
    /// Protocol type
    static const Protocol PROTOCOL = CP_PROTOCOL_AHB_LITE;
    /**
     *  \{
     *  \brief  Call InterfaceBaseType methods - resolve ambiguous call (multiple inheritance)
     */
    using InterfaceBaseType::blocking;
    using InterfaceBaseType::transport;
    /**
     *  \}
     *  \copydoc InterfaceBaseType::Interface()
     */
    AhbLiteInitiatorInterface(const std::string& name, const Uid uid, M* module = nullptr);
    /**
     *  \{
     *  \brief Implement the IA interface API
     */
    data_type read(const codasip_address_t addr, const Index bc);
    template<class Resp>
    data_type read(const codasip_address_t addr,
        const Index bc,
        Resp& resp,
        const uint8_t hprot = CP_AHB_PROT_DEFAULT,
        const uint8_t hmastlock = CP_AHB_UNLOCK);
    data_type dread(const codasip_address_t addr, const Index bc = T::BPW);
    template<class Resp>
    data_type dread(const codasip_address_t addr, const Index bc, Resp& resp);
    void write(param_type data, const codasip_address_t addr, const Index bc);
    template<class Resp>
    void write(param_type data,
        const codasip_address_t addr,
        const Index bc,
        Resp& resp,
        const uint8_t hprot = CP_AHB_PROT_DEFAULT,
        const uint8_t hmastlock = CP_AHB_UNLOCK);
    void dwrite(param_type data, const codasip_address_t addr, const Index bc = T::BPW);
    void load(param_type data, const codasip_address_t addr, const Index bc = T::BPW);
    /**
     *  \}
     *  \brief  Create payload for address phase from CodAL transport() function.
     *  \param  phase phase identifier, must be CP_PHS_ADDRESS
     *  \param  htrans transaction type specifier
     *  \param  hwrite indicates whether write or read transaction is requested
     *  \param  addr requested address
     *  \param  hsize size of the transfer
     *  \param  hprot protection control signal
     *  \param  hmastlock indicates part of a locked sequence
     *  \param  hburst burst type specification
     */
    void transport(const Phase phase,
        const uint8_t htrans,
        const uint8_t hwrite,
        const codasip_address_t addr,
        const uint8_t hsize,
        const uint8_t hprot,
        const uint8_t hmastlock,
        const uint8_t hburst);
    /**
     *  \brief  Create payload for data phase from CodAL transport() function
     *          used by read-only or write-only interface.
     *  \param[in]  phase phase identifier, must be CP_PHS_DATA
     *  \param[out] hready indicates whether transfer has finished or not
     *  \param[out] hresp transfer response (OKAY, ERROR)
     *  \param[in,out] hdata data transfered over the bus
     */
    template<class R, class HReady, class HResp>
    void transport(const Phase phase, HReady& hready, HResp& hresp, R&& hdata);
    /**
     *  \brief  Create payload for data phase from CodAL transport() function
     *          used by read-write interface.
     *  \param[in]  phase phase identifier, must be CP_PHS_DATA
     *  \param[out] hready indicates whether transfer has finished or not
     *  \param[out] hresp transfer response (OKAY, ERROR)
     *  \param[out] hrdata read data from selected slave to the master
     *  \param[in]  hwdata write data from the master to the slaves
     */
    template<class IR, class OR, class HReady, class HResp>
    void transport(const Phase phase, HReady& hready, HResp& hresp, IR& hrdata, OR&& hwdata);

protected:
    /// import payload for convenience
    using InterfaceBaseType::m_Payload;
    void
    PreparePayloadIA(const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);
    static data_type MaskAndShiftData(param_type, const codasip_address_t, const Index);

private:
    template<class Resp>
    data_type
    DoRead(Resp&, const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);
    template<class Resp>
    void
    DoWrite(Resp&, param_type, const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
inline AhbLiteInitiatorInterface<T, M, S>::AhbLiteInitiatorInterface(const std::string& name,
    const Uid uid,
    M* module)
  : InterfaceBaseType(name, uid, module)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
AhbLiteInitiatorInterface<T, M, S>::read(const codasip_address_t addr, const Index bc)
{
    AHBResponseCode resp = CP_AHB_OKAY;
    auto rdata = this->read(addr, bc, resp);
    if (resp != CP_AHB_OKAY)
    {
        this->DoAbortSimulation();
    }
    return rdata;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type
AhbLiteInitiatorInterface<T, M, S>::read(const codasip_address_t addr,
    const Index bc,
    Resp& resp,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    return DoRead(resp, addr, bc, CP_CMD_READ, hprot, hmastlock);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
AhbLiteInitiatorInterface<T, M, S>::dread(const codasip_address_t addr, const Index bc)
{   // ignore response, debug access should not shutdown the simulation
    AHBResponseCode resp = CP_AHB_OKAY;
    return DoRead(resp, addr, bc, CP_CMD_DREAD, CP_AHB_PROT_DEFAULT, CP_AHB_UNLOCK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type
AhbLiteInitiatorInterface<T, M, S>::dread(const codasip_address_t addr, const Index bc, Resp& resp)
{
    return DoRead(resp, addr, bc, CP_CMD_DREAD, CP_AHB_PROT_DEFAULT, CP_AHB_UNLOCK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AhbLiteInitiatorInterface<T, M, S>::write(param_type data, const codasip_address_t addr, const Index bc)
{
    AHBResponseCode resp = CP_AHB_OKAY;
    this->write(data, addr, bc, resp);
    if (resp != CP_AHB_OKAY)
    {
        this->DoAbortSimulation();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE void AhbLiteInitiatorInterface<T, M, S>::write(param_type data,
    const codasip_address_t addr,
    const Index bc,
    Resp& resp,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DoWrite(resp, data, addr, bc, CP_CMD_WRITE, hprot, hmastlock);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AhbLiteInitiatorInterface<T, M, S>::dwrite(param_type data, const codasip_address_t addr, const Index bc)
{   // ignore response, debug access should not shutdown the simulation
    AHBResponseCode resp = CP_AHB_OKAY;
    DoWrite(resp, data, addr, bc, CP_CMD_DWRITE, CP_AHB_PROT_DEFAULT, CP_AHB_UNLOCK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AhbLiteInitiatorInterface<T, M, S>::load(param_type data, const codasip_address_t addr, const Index bc)
{
    AHBResponseCode resp = CP_AHB_OKAY;
    DoWrite(resp, data, addr, bc, CP_CMD_LOAD, CP_AHB_PROT_DEFAULT, CP_AHB_UNLOCK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void AhbLiteInitiatorInterface<T, M, S>::transport(const Phase phase,
    const uint8_t htrans,
    const uint8_t hwrite,
    const codasip_address_t addr,
    const uint8_t hsize,
    const uint8_t hprot,
    const uint8_t hmastlock,
    const uint8_t hburst)
{
    // order of transfer type and read/write is mandatory
    // ignore unused bits similar to HW
    m_Payload.set_ahb_htrans(htrans & CP_AHB_SEQ);
    m_Payload.set_ahb_hwrite(hwrite & CP_AHB_WRITE);
    // use same order of writes as definition in the payload structure
    m_Payload.set_ahb_hprot(hprot & 0x0Fu);
    m_Payload.set_ahb_hmastlock(hmastlock & CP_AHB_LOCK);
    m_Payload.set_ahb_hburst(hburst & 0x07u);
    m_Payload.set_ahb_hready(CP_AHB_BUSY);
    m_Payload.set_ahb_hresp(CP_AHB_OKAY);
    m_Payload.set_ahb_hsel(false);
    m_Payload.set_address(addr);
    m_Payload.set_ahb_hsize(hsize & CP_AHB_SIZE_1024);
    m_Payload.set_data(0u);

    CODASIP_AHB_INITIATOR_DBG_OUT_PRINT("address phase begin:", m_Payload);
    this->transport(m_Payload, phase);
    CODASIP_AHB_INITIATOR_DBG_OUT_PRINT("address phase end:", m_Payload);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class R, class HReady, class HResp>
RES_INLINE void
AhbLiteInitiatorInterface<T, M, S>::transport(const Phase phase, HReady& hready, HResp& hresp, R&& hdata)
{
    transport(phase, hready, hresp, hdata, std::forward<R>(hdata));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class IR, class OR, class HReady, class HResp>
RES_INLINE void AhbLiteInitiatorInterface<T, M, S>::transport(const Phase phase,
    HReady& hready,
    HResp& hresp,
    IR& hrdata,
    OR&& hwdata)
{
    static_assert(T::BYTE_BITS == 8, "Byte bit-width must be 8!");
    m_Payload.reset();
    // output -> set write data
    m_Payload.set_data(detail::ResourceAccess::Read(hwdata));
    CODASIP_AHB_INITIATOR_DBG_OUT_PRINT("data phase begin:", m_Payload);
    // transaction
    this->transport(m_Payload, phase);
    detail::ResourceAccess::Write(hready, m_Payload.get_ahb_hready());
    detail::ResourceAccess::Write(hresp, m_Payload.get_ahb_hresp());
    detail::ResourceAccess::Write(hrdata, m_Payload.get_data());
    CODASIP_AHB_INITIATOR_DBG_OUT_PRINT("data phase end:", m_Payload);
}

/**
 *  \brief  Common implementation of the read/dread functions.
 *  \param[out] resp transfer response (OKAY, ERROR)
 *  \param[in]  addr requested address
 *  \param[in]  bc byte count
 *  \param[in]  cmd requested command (read/dread)
 *  \param[in]  hprot   AHB protection mode
 *  \param[in]  hmastlock   AHB master lock code
 */
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type AhbLiteInitiatorInterface<T, M, S>::DoRead(Resp& resp,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (bc == 0)
    {   // in IA do not create payload and do not pass it further to the slaves
        // the transaction is not valid
        detail::ResourceAccess::Write(resp, CP_AHB_OKAY);
        return static_cast<data_type>(0u);
    }
    PreparePayloadIA(addr, bc, cmd, hprot, hmastlock);
    this->blocking(m_Payload);

    detail::ResourceAccess::Write(resp, m_Payload.get_ahb_hresp());
    return MaskAndShiftData(m_Payload.get_data(), addr, bc);
}

/**
 *  \brief  Common implementation of the write/dwrite functions.
 *  \param[out] resp transfer response (OKAY, ERROR)
 *  \param[in]  data write data from the master to the slaves
 *  \param[in]  addr requested address
 *  \param[in]  bc byte count
 *  \param[in]  cmd requested command (write/dwrite)
 *  \param[in]  hprot   AHB protection mode
 *  \param[in]  hmastlock   AHB master lock code
 */
template<class T, class M, class S>
template<class Resp>
RES_INLINE void AhbLiteInitiatorInterface<T, M, S>::DoWrite(Resp& resp,
    param_type data,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (bc == 0)
    {   // in IA do not create payload and do not pass it further to the slaves
        // the transaction is not valid
        // for AHB the transfer might be dangerous because BC=0 maps to HSIZE=0
        // could write single byte instead of none
        detail::ResourceAccess::Write(resp, CP_AHB_OKAY);
        return;
    }
    PreparePayloadIA(addr, bc, cmd, hprot, hmastlock);
    m_Payload.set_data(data
        << InterfaceBaseType::get_amba_shift(InterfaceBaseType::get_offset(addr, SUBBLOCKS), bc));
    this->blocking(m_Payload);
    detail::ResourceAccess::Write(resp, m_Payload.get_ahb_hresp());
}

/**
 *  \brief  Prepare payload for an IA access function with given arguments.
 *  \param  addr requested address
 *  \param  bc byte count
 *  \param  cmd requested command (read/dread/write/dwrite)
 *  \param  hprot AHB protection mode
 *  \param  hmastlock   AHB master lock code
 */
template<class T, class M, class S>
RES_INLINE void AhbLiteInitiatorInterface<T, M, S>::PreparePayloadIA(const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const AHBReadWriteCode rw = (cmd == CP_CMD_READ || cmd == CP_CMD_DREAD) ? CP_AHB_READ
                                                                            : CP_AHB_WRITE;
    m_Payload.set_ahb_htrans(CP_AHB_NONSEQ);
    m_Payload.set_ahb_hwrite(rw);
    m_Payload.set_command(cmd);
    m_Payload.set_address(addr);
    m_Payload.set_bc(bc);
    m_Payload.set_ahb_hprot(hprot);
    m_Payload.set_ahb_hmastlock(hmastlock);
    m_Payload.set_ahb_hburst(CP_AHB_SINGLE);
    m_Payload.set_ahb_hready(CP_AHB_READY);
    m_Payload.set_ahb_hresp(CP_AHB_OKAY);
    m_Payload.set_ahb_hsel(false);
}

/**
 *  \brief  Masks and shifts the given data.
 *  \param  data    Data to be masked and shifted.
 *  \param  address Adress from which the offset is computed.
 *  \param  bc  Number of data bytes.
 */
template<class T, class M, class S>
RES_INLINE typename T::data_type AhbLiteInitiatorInterface<T, M, S>::MaskAndShiftData(param_type data,
    const codasip_address_t address,
    const Index bc)
{
    const auto offset = InterfaceBaseType::get_offset(address, SUBBLOCKS);
    const auto shift = InterfaceBaseType::get_amba_shift(offset, bc);
    const auto mask = InterfaceBaseType::create_amba_mask(offset, bc);
    return (data & mask) >> shift;
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_AHB_INITIATOR_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_AHB_INITIATOR_INTERFACE_H_
