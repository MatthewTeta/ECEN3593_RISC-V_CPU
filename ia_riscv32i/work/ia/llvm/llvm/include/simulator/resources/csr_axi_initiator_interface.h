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
 *  \author Pavel Najman
 *  \date   Oct 21, 2020
 *  \brief  Definition of the class codasip::resources::AxiInitiatorInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_INITIATOR_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_AXI_INITIATOR_INTERFACE_H_

#include "simulator/resources/csr_axi_lite_initiator_interface.h"
#include "simulator/resources/csr_interface.h"
#include "simulator/resources/csr_payload.h"

//#define CODASIP_AXI_INITIATOR_DBG_OUT
#ifdef CODASIP_AXI_INITIATOR_DBG_OUT
#    define CODASIP_AXI_INITIATOR_DBG_OUT_PRINT(cmd, p)                                        \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() << ": AXI4 " \
                  << cmd << " " << p.PrintAxi() << std::endl
#else
#    define CODASIP_AXI_INITIATOR_DBG_OUT_PRINT(cmd, p)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiInitiatorInterface
 *  \brief  Interface that handles AMBA AXI4 protocol.
 *  \}
 */
template<class T,
    class M = detail::InterfaceModule<typename T::data_type>,
    class S = detail::CODASIP_IFACE_CB_SELECT_FULL(blocking_cb, transport_cb)>
class AxiInitiatorInterface : public Interface<T, M, S>
{
public:
    /// Underying data type
    using typename T::data_type;
    /// Underlying parameter data type
    using typename T::param_type;

    /// Payload type
    typedef Payload<typename T::data_type> payload_type;
    /// Interface base class
    typedef Interface<T, M, S> InterfaceBaseType;
    /// Underlying type holding write strobe (exact bit-width)
    typedef typename std::conditional<T::BPW ==
            BitWidthTypeSelector<typename TypeSelector<T::BPW, false>::type>::value,
        typename TypeSelector<T::BPW, false>::type,
        ::codasip::Integer<T::BPW, false>>::type write_strobe_type;

    /**
     *  \{
     *  \brief  Call InterfaceBaseType methods - resolve ambiguous call (multiple inheritance)
     */
    using InterfaceBaseType::blocking;
    using InterfaceBaseType::transport;
    /**
     *  \}
     */

    /// Number of bytes in word
    static const Index SUBBLOCKS = T::WORD_BITS / T::BYTE_BITS;
    /// Protocol type
    static const Protocol PROTOCOL = CP_PROTOCOL_AXI;

    /**
     *  \copydoc InterfaceBaseType::Interface()
     */
    AxiInitiatorInterface(const std::string& name, const Uid uid, M* module = nullptr);

    /**
     *  \{
     *  \brief Implement the IA interface API
     */
    data_type read(const codasip_address_t addr, const Index bc);
    template<class Resp>
    data_type read(const codasip_address_t addr, const Index bc, Resp& resp);
    data_type dread(const codasip_address_t addr, const Index bc = T::BPW);
    void write(param_type data, const codasip_address_t addr, const Index bc);
    template<class Resp>
    void write(param_type data, const codasip_address_t addr, const Index bc, Resp& resp);
    void dwrite(param_type data, const codasip_address_t addr, const Index bc = T::BPW);
    void load(param_type data, const codasip_address_t addr, const Index bc = T::BPW);
    /**
     *  \}
     */

    /**
     *  \brief Create payload for read/write address phase from CodAL transport() function.
     *  \param[in]  phase   CP_PHS_ADDRESS_WRITE/READ (ignored, determined by number of arguments)
     *  \param[in]  aid     R/W ID tag
     *  \param[in]  aaddr   R/W address
     *  \param[in]  alen    Burst length
     *  \param[in]  asize   Burst size
     *  \param[in]  aburst  Burst type
     *  \param[in]  alock   Lock type
     *  \param[in]  acache  Memory type
     *  \param[in]  aprot   Protection type
     *  \param[in]  aqos    Quality of Service
     *  \param[in]  aregion Region identifier
     *  \param[in]  avalid  R/W address valid
     *  \param[out] aready  R/W address ready
     */
    template<class AReady,
        class AValid,
        class AAddr,
        class AProt,
        class ASize,
        class ABurst,
        class ALen,
        class ALock,
        class ACache,
        class AQos,
        class ARegion,
        class AId>
    void transport(const Phase phase,
        AValid&& axvalid,
        AReady&& axready,
        AAddr&& axaddr,
        AProt&& axprot,
        ASize&& axsize,
        ABurst&& axburst,
        ALen&& axlen,
        ALock&& axlock,
        ACache&& axcache,
        AQos&& axqos,
        ARegion&& axregion,
        AId&& axid);

    /**
     *  \brief Create payload for read data phase from CodAL transport() function.
     *  \param[in]  phase  CP_PHS_DATA_READ (ignored, determined by the arguments)
     *  \param[in]  rready Read ready
     *  \param[out] rid    Read ID tag
     *  \param[out] rdata  Read data
     *  \param[out] rresp  Read response
     *  \param[out] rlast  Read last
     *  \param[out] rvalid Read valid
     */
    template<class RId, class RData, class RResp, class RLast, class RValid, class RReady>
    void transport(const Phase phase,
        RValid&& rvalid,
        RReady&& rready,
        RResp&& rresp,
        RData&& rdata,
        RLast&& rlast,
        RId&& rid);

    /**
     *  \brief Create payload for write data phase from CodAL transport() function.
     *  \param[in]  phase  CP_PHS_DATA_WRITE (ignored, determined by the arguments)
     *  \param[in]  wdata  Write data
     *  \param[in]  wstrb  Write strobes
     *  \param[in]  wlast  Write last
     *  \param[in]  wvalid Write valid
     *  \param[out] wready Write ready
     */
    template<class WValid, class WReady, class W, class WStrobe, class WLast>
    void
    transport(const Phase phase, WValid&& wvalid, WReady&& wready, W&& wdata, WStrobe wstrb, WLast wlast);

    /**
     *  \brief Create payload for write response phase from CodAL transport() function.
     *  \param[in]  phase  CP_PHS_RESPONSE_WRITE (ignored, determined by number of arguments)
     *  \param[in]  bready Response ready
     *  \param[out] bid    Response ID tag
     *  \param[out] bresp  Write response
     *  \param[out] bvalid Write response valid
     */
    template<class BId, class BResp, class BValid, class BReady>
    void transport(const Phase phase, BValid&& bvalid, BReady&& bready, BResp&& bresp, BId&& bid);

protected:
    /// import payload for convenience
    using InterfaceBaseType::m_Payload;

    void PreparePayloadIA(const codasip_address_t, const Index, const Command);

private:
    template<class Resp>
    data_type DoRead(Resp&, const codasip_address_t, const Index, const Command);

    template<class Resp>
    void DoWrite(Resp&, param_type, const codasip_address_t, const Index, const Command);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
inline AxiInitiatorInterface<T, M, S>::AxiInitiatorInterface(const std::string& name,
    const Uid uid,
    M* module)
  : InterfaceBaseType(name, uid, module)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
AxiInitiatorInterface<T, M, S>::read(const codasip_address_t addr, const Index bc)
{
    AXIResponseCode resp = CP_AXI_OKAY;
    auto rdata = this->read(addr, bc, resp);
    if (resp != CP_AXI_OKAY)
    {
        this->DoAbortSimulation();
    }
    return rdata;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type
AxiInitiatorInterface<T, M, S>::read(const codasip_address_t addr, const Index bc, Resp& resp)
{
    return DoRead(resp, addr, bc, CP_CMD_READ);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
AxiInitiatorInterface<T, M, S>::dread(const codasip_address_t addr, const Index bc)
{
    // ignore response, debug access should not shutdown the simulation
    AXIResponseCode resp = CP_AXI_OKAY;
    return DoRead(resp, addr, bc, CP_CMD_DREAD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AxiInitiatorInterface<T, M, S>::write(param_type data, const codasip_address_t addr, const Index bc)
{
    AXIResponseCode resp = CP_AXI_OKAY;
    this->write(data, addr, bc, resp);
    if (resp != CP_AXI_OKAY)
    {
        this->DoAbortSimulation();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE void AxiInitiatorInterface<T, M, S>::write(param_type data,
    const codasip_address_t addr,
    const Index bc,
    Resp& resp)
{
    DoWrite(resp, data, addr, bc, CP_CMD_WRITE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AxiInitiatorInterface<T, M, S>::dwrite(param_type data, const codasip_address_t addr, const Index bc)
{
    // ignore response, debug access should not shutdown the simulation
    AXIResponseCode resp = CP_AXI_OKAY;
    DoWrite(resp, data, addr, bc, CP_CMD_DWRITE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AxiInitiatorInterface<T, M, S>::load(param_type data, const codasip_address_t addr, const Index bc)
{
    AXIResponseCode resp = CP_AXI_OKAY;
    DoWrite(resp, data, addr, bc, CP_CMD_LOAD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class AReady, class AValid, class AAddr, class AProt, class ASize, class ABurst, class ALen, class ALock, class ACache, class AQos, class ARegion, class AId>
RES_INLINE void AxiInitiatorInterface<T, M, S>::transport(const Phase phase,
    AValid&& axvalid,
    AReady&& axready,
    AAddr&& axaddr,
    AProt&& axprot,
    ASize&& axsize,
    ABurst&& axburst,
    ALen&& axlen,
    ALock&& axlock,
    ACache&& axcache,
    AQos&& axqos,
    ARegion&& axregion,
    AId&& axid)
{
    CHECK_CONDITION(phase == CP_PHS_ADDRESS_READ || phase == CP_PHS_ADDRESS_WRITE);
    m_Payload.reset();

    // fill payload with given values
    m_Payload.set_axi_id(detail::ResourceAccess::Read(axid));
    m_Payload.set_address(detail::ResourceAccess::Read(axaddr));
    m_Payload.set_axi_len(detail::ResourceAccess::Read(axlen) & 0xFF);
    m_Payload.set_axi_size(detail::ResourceAccess::Read(axsize) & CP_AXI_SIZE_1024);
    m_Payload.set_axi_burst(detail::ResourceAccess::Read(axburst) & CP_AXI_BURST_RESERVED);
    m_Payload.set_axi_lock(detail::ResourceAccess::Read(axlock) & CP_AXI_LOCK_EXCLUSIVE);
    m_Payload.set_axi_cache(detail::ResourceAccess::Read(axcache) & CP_AXI_CACHE_ALL);
    m_Payload.set_axi_prot(detail::ResourceAccess::Read(axprot) & CP_AXI_PROT_ALL);
    m_Payload.set_axi_qos(detail::ResourceAccess::Read(axqos) & 0x0F);
    m_Payload.set_axi_region(detail::ResourceAccess::Read(axregion) & 0x0F);
    m_Payload.set_axi_valid(detail::ResourceAccess::Read(axvalid) & CP_AXI_VALID);

    // only valid transactions should have valid command
    if (m_Payload.get_axi_valid() == CP_AXI_VALID)
    {
        m_Payload.set_command(phase == CP_PHS_ADDRESS_WRITE ? CP_CMD_WRITE : CP_CMD_READ);
    }
    // address offset is calculated to enable pac to detect address alignment errors
    m_Payload.set_axi_address_offset(InterfaceBaseType::get_offset(m_Payload.get_address(), SUBBLOCKS));

    // perform transport
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT(
        std::string(phase == CP_PHS_ADDRESS_WRITE ? "write" : "read") + " address phase begin:",
        m_Payload);
    this->transport(m_Payload, phase);
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT(
        std::string(phase == CP_PHS_ADDRESS_WRITE ? "write" : "read") + " address phase end:",
        m_Payload);

    // write output values
    detail::ResourceAccess::Write(axready, m_Payload.get_axi_ready());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class RId, class RData, class RResp, class RLast, class RValid, class RReady>
RES_INLINE void AxiInitiatorInterface<T, M, S>::transport(const Phase phase,
    RValid&& rvalid,
    RReady&& rready,
    RResp&& rresp,
    RData&& rdata,
    RLast&& rlast,
    RId&& rid)
{
    CHECK_CONDITION(phase == CP_PHS_DATA_READ);
    m_Payload.reset();

    // fill payload with given values
    m_Payload.set_command(CP_CMD_READ);
    m_Payload.set_axi_ready(detail::ResourceAccess::Read(rready) & CP_AXI_READY);

    // perform transport
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT("read data phase begin:", m_Payload);
    this->transport(m_Payload, phase);
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT("read data phase end:", m_Payload);

    // write output values
    detail::ResourceAccess::Write(rid, m_Payload.get_axi_id());
    detail::ResourceAccess::Write(rdata, m_Payload.get_data());
    detail::ResourceAccess::Write(rresp, m_Payload.get_axi_resp());
    detail::ResourceAccess::Write(rlast, m_Payload.get_axi_last());
    detail::ResourceAccess::Write(rvalid, m_Payload.get_axi_valid());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class WValid, class WReady, class W, class WStrobe, class WLast>
RES_INLINE void AxiInitiatorInterface<T, M, S>::transport(const Phase phase,
    WValid&& wvalid,
    WReady&& wready,
    W&& wdata,
    WStrobe wstrb,
    WLast wlast)
{
    CHECK_CONDITION(phase == CP_PHS_DATA_WRITE);
    m_Payload.reset();

    // fill payload with given values
    m_Payload.set_data(detail::ResourceAccess::Read(wdata));
    m_Payload.set_axi_wstrb(detail::ResourceAccess::Read(wstrb));
    m_Payload.set_axi_last(detail::ResourceAccess::Read(wlast) & CP_AXI_LAST);
    m_Payload.set_axi_valid(detail::ResourceAccess::Read(wvalid) & CP_AXI_VALID);

    // only valid transactions should have valid command
    if (m_Payload.get_axi_valid() == CP_AXI_VALID)
    {
        m_Payload.set_command(CP_CMD_WRITE);
    }

    // perform transport
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT("write data phase begin:", m_Payload);
    this->transport(m_Payload, phase);
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT("write data phase end:", m_Payload);

    // write output values
    detail::ResourceAccess::Write(wready, m_Payload.get_axi_ready());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class BId, class BResp, class BValid, class BReady>
RES_INLINE void AxiInitiatorInterface<T, M, S>::transport(const Phase phase,
    BValid&& bvalid,
    BReady&& bready,
    BResp&& bresp,
    BId&& bid)
{
    CHECK_CONDITION(phase == CP_PHS_RESPONSE_WRITE);
    m_Payload.reset();

    // fill payload with given values
    m_Payload.set_command(CP_CMD_WRITE);
    m_Payload.set_axi_ready(detail::ResourceAccess::Read(bready) & CP_AXI_READY);

    // perform transport
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT("write response begin:", m_Payload);
    this->transport(m_Payload, CP_PHS_RESPONSE_WRITE);
    CODASIP_AXI_INITIATOR_DBG_OUT_PRINT("write response end:", m_Payload);

    // write output values
    detail::ResourceAccess::Write(bid, m_Payload.get_axi_id());
    detail::ResourceAccess::Write(bvalid, m_Payload.get_axi_valid());
    detail::ResourceAccess::Write(bresp, m_Payload.get_axi_resp());
}

/**
 *  \brief Prepare payload for an IA access function with given arguments.
 *  \param[in] addr requested address
 *  \param[in] bc   byte count
 *  \param[in] cmd  requested command (write/dwrite/load/read/dread)
 */
template<class T, class M, class S>
RES_INLINE void AxiInitiatorInterface<T, M, S>::PreparePayloadIA(const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    // Fill payload with given values and set other signals to default values
    m_Payload.reset(CP_AXI_READY);
    m_Payload.set_command(cmd);
    m_Payload.set_address(addr);
    m_Payload.set_bc(bc);
    m_Payload.set_axi_valid(CP_AXI_VALID);
    m_Payload.set_axi_prot(CP_AXI_PROT_DEFAULT);
    m_Payload.set_axi_burst(CP_AXI_BURST_INCR);
    m_Payload.set_axi_last(CP_AXI_LAST);
    m_Payload.set_axi_address_offset(InterfaceBaseType::get_offset(addr, SUBBLOCKS));
    m_Payload.set_axi_address_phase();

    // set additional values for write access
    if (cmd == CP_CMD_WRITE || cmd == CP_CMD_DWRITE || cmd == CP_CMD_LOAD)
    {
        m_Payload.set_axi_data_phase();   // for UVM only
        m_Payload.set_axi_wstrb(this->template CreateWriteStrobe<write_strobe_type>(
            InterfaceBaseType::get_offset(addr, SUBBLOCKS),
            bc));
    }
}

/**
 *  \brief  Common implementation of the read/dread access in IA.
 *  \param[out] resp transfer response (OKAY, SLVERR, DECERR)
 *  \param[in]  addr requested address
 *  \param[in]  bc   byte count
 *  \param[in]  cmd  requested command (read/dread)
 */
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type AxiInitiatorInterface<T, M, S>::DoRead(Resp& resp,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    // in IA do not create payload and do not pass it further to the slaves
    // the transaction is not valid
    if (bc == 0)
    {
        detail::ResourceAccess::Write(resp, CP_AXI_OKAY);
        return static_cast<data_type>(0u);
    }

    // prepare payload and perform blocking transaction
    PreparePayloadIA(addr, bc, cmd);
    this->blocking(m_Payload);

    // process transaction results
    detail::ResourceAccess::Write(resp, m_Payload.get_axi_resp());
    const auto shift = InterfaceBaseType::get_amba_shift(InterfaceBaseType::get_offset(addr, SUBBLOCKS),
        bc);
    auto mask = InterfaceBaseType::create_amba_mask(InterfaceBaseType::get_offset(addr, SUBBLOCKS), bc);
    return (m_Payload.get_data() & mask) >> shift;
}

/**
 *  \brief Common implementation of the write/dwrite functions.
 *  \param[out] resp transfer response (OKAY, SLVERR, DECERR)
 *  \param[in]  data write data from the master to the slaves
 *  \param[in]  addr requested address
 *  \param[in]  bc   byte count
 *  \param[in]  cmd  requested command (write/dwrite/load)
 */
template<class T, class M, class S>
template<class Resp>
RES_INLINE void AxiInitiatorInterface<T, M, S>::DoWrite(Resp& resp,
    param_type data,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    // in IA do not create payload and do not pass it further to the slaves
    // the transaction is not valid
    if (bc == 0)
    {
        detail::ResourceAccess::Write(resp, CP_AXI_OKAY);
        return;
    }

    // prepare payload and perform blocking transaction
    PreparePayloadIA(addr, bc, cmd);
    m_Payload.set_data(data
        << InterfaceBaseType::get_amba_shift(InterfaceBaseType::get_offset(addr, SUBBLOCKS), bc));
    this->blocking(m_Payload);

    // process transaction results
    detail::ResourceAccess::Write(resp, m_Payload.get_axi_resp());
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_AXI_INITIATOR_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_AXI_INITIATOR_INTERFACE_H_
