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
 *  \date   Nov 7, 2017
 *  \brief  Definition of the class codasip::resources::AxiLiteInitiatorInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_LITE_INITIATOR_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_AXI_LITE_INITIATOR_INTERFACE_H_

#include "simulator/resources/csr_interface.h"

//#define CODASIP_AXI_LITE_INITIATOR_DBG_OUT
#ifdef CODASIP_AXI_LITE_INITIATOR_DBG_OUT
#    define CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT(cmd, p)                      \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() \
                  << ": AXI4-Lite " << cmd << " " << p.PrintAxiLite() << std::endl
#else
#    define CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT(cmd, p)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiLiteInitiatorInterface
 *  \brief  Interface that handles AMBA AXI4-Lite protocol.
 *  \}
 */
template<class T,
    class M = detail::InterfaceModule<typename T::data_type>,
    class S = detail::CODASIP_IFACE_CB_SELECT_FULL(blocking_cb, transport_cb)>
class AxiLiteInitiatorInterface : public Interface<T, M, S>
{
public:
    using typename T::data_type;
    using typename T::param_type;
    /// \brief  Interface base class
    typedef Interface<T, M, S> InterfaceBaseType;
    /// Number of bytes in word
    static const Index SUBBLOCKS = T::WORD_BITS / T::BYTE_BITS;
    /// Protocol type
    static const Protocol PROTOCOL = CP_PROTOCOL_AXI_LITE;
    /**
     *  \{
     *  \brief  Call Interface<T, M> methods - resolve ambiguous call (multiple inheritance)
     */
    using InterfaceBaseType::blocking;
    using InterfaceBaseType::transport;
    /**
     *  \}
     *  \copydoc InterfaceBaseType::Interface()
     */
    AxiLiteInitiatorInterface(const std::string& name, const Uid uid, M* module = nullptr);
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
     *  \brief  Common interface for address/data read/write phase. Forwards the arguments
     *          to the do_address/do_data_read/do_data_write method, based on the phase.
     */
    template<class... Args>
    void transport(const Phase phase, Args&&... args);
    /**
     *  \brief  Create payload for write response phase from CodAL transport() function.
     *  \param[in]  phase CP_PHS_RESPONSE_WRITE (ignored, determined by number of arguments)
     *  \param[out] bvalid response is valid
     *  \param[in]  bready master ready
     *  \param[out] bresp transfer response (OKAY, ERROR)
     */
    template<class BValid, class BReady, class BResp>
    void transport(const Phase phase, BValid&& bvalid, BReady&& bready, BResp&& bresp);

protected:
    /// import payload for convenience
    using InterfaceBaseType::m_Payload;
    void PreparePayloadIA(const codasip_address_t, const Index, const Command);

private:
    template<class Resp>
    data_type DoRead(Resp&, const codasip_address_t, const Index, const Command);
    template<class Resp>
    void DoWrite(Resp&, param_type, const codasip_address_t, const Index, const Command);

    template<class AValid, class AReady, class AAddr, class AProt>
    void do_address(const Phase, AValid&&, AReady&&, AAddr&&, AProt&&);
    template<class RValid, class RReady, class RResp, class R>
    void do_data_read(RValid&&, RReady&&, RResp&&, R&&);
    template<class WValid, class WReady, class W, class WStrobe>
    void do_data_write(WValid&&, WReady&&, W&&, WStrobe&&);

    using InterfaceBaseType::BPW;
    using InterfaceBaseType::BYTE_BITS;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
inline AxiLiteInitiatorInterface<T, M, S>::AxiLiteInitiatorInterface(const std::string& name,
    const Uid uid,
    M* module)
  : InterfaceBaseType(name, uid, module)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
AxiLiteInitiatorInterface<T, M, S>::read(const codasip_address_t addr, const Index bc)
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
AxiLiteInitiatorInterface<T, M, S>::read(const codasip_address_t addr, const Index bc, Resp& resp)
{
    return DoRead(resp, addr, bc, CP_CMD_READ);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
AxiLiteInitiatorInterface<T, M, S>::dread(const codasip_address_t addr, const Index bc)
{   // ignore response, debug access should not shutdown the simulation
    AXIResponseCode resp = CP_AXI_OKAY;
    return DoRead(resp, addr, bc, CP_CMD_DREAD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AxiLiteInitiatorInterface<T, M, S>::write(param_type data, const codasip_address_t addr, const Index bc)
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
RES_INLINE void AxiLiteInitiatorInterface<T, M, S>::write(param_type data,
    const codasip_address_t addr,
    const Index bc,
    Resp& resp)
{
    DoWrite(resp, data, addr, bc, CP_CMD_WRITE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AxiLiteInitiatorInterface<T, M, S>::dwrite(param_type data, const codasip_address_t addr, const Index bc)
{   // ignore response, debug access should not shutdown the simulation
    AXIResponseCode resp = CP_AXI_OKAY;
    DoWrite(resp, data, addr, bc, CP_CMD_DWRITE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
AxiLiteInitiatorInterface<T, M, S>::load(param_type data, const codasip_address_t addr, const Index bc)
{
    AXIResponseCode resp = CP_AXI_OKAY;
    DoWrite(resp, data, addr, bc, CP_CMD_LOAD);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class... Args>
RES_INLINE void AxiLiteInitiatorInterface<T, M, S>::transport(const Phase phase, Args&&... args)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS_READ:
        case CP_PHS_ADDRESS_WRITE:
            do_address(phase, std::forward<Args>(args)...);
            break;
        case CP_PHS_DATA_READ:
            do_data_read(std::forward<Args>(args)...);
            break;
        case CP_PHS_DATA_WRITE:
            do_data_write(std::forward<Args>(args)...);
            break;
        default:
            // CodAL compiler should guarantee valid phases
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class BValid, class BReady, class BResp>
RES_INLINE void
AxiLiteInitiatorInterface<T, M, S>::transport(const Phase, BValid&& bvalid, BReady&& bready, BResp&& bresp)
{
    m_Payload.reset();
    // ignore unused bits similar to HW
    m_Payload.set_axi_ready(detail::ResourceAccess::Read(bready) & CP_AXI_READY);
    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT("write resp begin:", m_Payload);
    this->transport(m_Payload, CP_PHS_RESPONSE_WRITE);
    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT("write resp begin:", m_Payload);
    detail::ResourceAccess::Write(bvalid, m_Payload.get_axi_valid());
    detail::ResourceAccess::Write(bresp, m_Payload.get_axi_resp());
}

/**
 *  \brief  Common implementation of the read/dread functions.
 *  \param[out] resp transfer response (OKAY, ERROR)
 *  \param[in]  addr requested address
 *  \param[in]  bc byte count
 *  \param[in]  cmd requested command (read/dread)
 */
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type AxiLiteInitiatorInterface<T, M, S>::DoRead(Resp& resp,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    if (bc == 0)
    {   // in IA do not create payload and do not pass it further to the slaves
        // the transaction is not valid
        detail::ResourceAccess::Write(resp, CP_AXI_OKAY);
        return static_cast<data_type>(0u);
    }
    PreparePayloadIA(addr, bc, cmd);
    this->blocking(m_Payload);

    detail::ResourceAccess::Write(resp, m_Payload.get_axi_resp());
    const auto shift = InterfaceBaseType::get_amba_shift(InterfaceBaseType::get_offset(addr, SUBBLOCKS),
        bc);
    auto mask = InterfaceBaseType::create_amba_mask(InterfaceBaseType::get_offset(addr, SUBBLOCKS), bc);
    return (m_Payload.get_data() & mask) >> shift;
}

/**
 *  \brief  Common implementation of the write/dwrite functions.
 *  \param[out] resp transfer response (OKAY, ERROR)
 *  \param[in]  data write data from the master to the slaves
 *  \param[in]  addr requested address
 *  \param[in]  bc byte count
 *  \param[in]  cmd requested command (write/dwrite)
 */
template<class T, class M, class S>
template<class Resp>
RES_INLINE void AxiLiteInitiatorInterface<T, M, S>::DoWrite(Resp& resp,
    param_type data,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    if (bc == 0)
    {   // in IA do not create payload and do not pass it further to the slaves
        // the transaction is not valid
        detail::ResourceAccess::Write(resp, CP_AXI_OKAY);
        return;
    }
    PreparePayloadIA(addr, bc, cmd);
    m_Payload.set_data(data
        << InterfaceBaseType::get_amba_shift(InterfaceBaseType::get_offset(addr, SUBBLOCKS), bc));
    this->blocking(m_Payload);
    detail::ResourceAccess::Write(resp, m_Payload.get_axi_resp());
}

/**
 *  \brief  Prepare payload for an IA access function with given arguments.
 *  \param  addr requested address
 *  \param  bc byte count
 *  \param  cmd requested command (write/dwrite/load)
 */
template<class T, class M, class S>
RES_INLINE void AxiLiteInitiatorInterface<T, M, S>::PreparePayloadIA(const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    m_Payload.reset(CP_AXI_READY);
    m_Payload.set_command(cmd);
    m_Payload.set_address(InterfaceBaseType::get_aligned_address(addr, SUBBLOCKS));
    // for the outside world, the access is always word-wide
    m_Payload.set_bc(SUBBLOCKS);
    m_Payload.set_axi_valid(CP_AXI_VALID);
    // default AxPROT: Data access, Non-secure, Privileged
    m_Payload.set_axi_prot(CP_AXI_PROT_PRIVILEGED | CP_AXI_PROT_NON_SECURE);
    // store address offset and original transfer size for protocol checker,
    // otherwise invalid values and combinations won't be detected
    // and write dumper would provide bad data
    m_Payload.set_axi_address_offset(InterfaceBaseType::get_offset(addr, SUBBLOCKS));
    m_Payload.set_axi_transfer_size(bc);
    m_Payload.set_axi_address_phase();
    if (cmd == CP_CMD_WRITE || cmd == CP_CMD_DWRITE || cmd == CP_CMD_LOAD)
    {
        m_Payload.set_axi_data_phase();
        m_Payload.set_axi_wstrb(this->template CreateWriteStrobe<AXIWriteStrobe>(
            InterfaceBaseType::get_offset(addr, SUBBLOCKS),
            bc));
    }
}

/**
 *  \brief  Create payload for address phase from CodAL transport() function.
 *  \param  [in]  phase CP_PHS_ADDRESS_READ/WRITE
 *  \param  [in]  avalid address is valid
 *  \param  [out] aready slave is ready
 *  \param  [in]  addr requested address
 *  \param  [in]  aprot protection control signal
 */
template<class T, class M, class S>
template<class AValid, class AReady, class AAddr, class AProt>
RES_INLINE void AxiLiteInitiatorInterface<T, M, S>::do_address(const Phase phase,
    AValid&& avalid,
    AReady&& aready,
    AAddr&& addr,
    AProt&& aprot)
{
    CHECK_CONDITION(phase == CP_PHS_ADDRESS_READ || phase == CP_PHS_ADDRESS_WRITE) << "Wrong phase";

    // always read/write whole word
    m_Payload.reset();
    m_Payload.set_address(detail::ResourceAccess::Read(addr));
    m_Payload.set_bc(SUBBLOCKS);
    // ignore unused bits similar to HW
    m_Payload.set_axi_valid(detail::ResourceAccess::Read(avalid) & CP_AXI_VALID);
    m_Payload.set_command((m_Payload.get_axi_valid() == CP_AXI_INVALID)
            ? CP_CMD_NONE
            : ((phase == CP_PHS_ADDRESS_READ ? CP_CMD_READ : CP_CMD_WRITE)));
    m_Payload.set_axi_prot(detail::ResourceAccess::Read(aprot) & 0x07u);

    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT(
        "address " << (phase == CP_PHS_ADDRESS_READ ? "read" : "write") << " begin:",
        m_Payload);
    this->transport(m_Payload, phase);
    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT(
        "address " << (phase == CP_PHS_ADDRESS_READ ? "read" : "write") << " end:",
        m_Payload);
    detail::ResourceAccess::Write(aready, m_Payload.get_axi_ready());
}

/**
 *  \brief  Create payload for data read phase from CodAL transport() function.
 *  \param[out] rvalid data is valid
 *  \param[in]  rready master is ready
 *  \param[out] rresp data transfered over the bus
 *  \param[out] rdata received data
 */
template<class T, class M, class S>
template<class RValid, class RReady, class RResp, class R>
RES_INLINE void
AxiLiteInitiatorInterface<T, M, S>::do_data_read(RValid&& rvalid, RReady&& rready, RResp&& rresp, R&& rdata)
{
    m_Payload.reset();
    m_Payload.set_command(CP_CMD_READ);
    // ignore unused bits similar to HW
    m_Payload.set_axi_ready(detail::ResourceAccess::Read(rready) & CP_AXI_READY);
    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT("read data begin:", m_Payload);
    this->transport(m_Payload, CP_PHS_DATA_READ);
    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT("read data end:", m_Payload);
    detail::ResourceAccess::Write(rvalid, m_Payload.get_axi_valid());
    detail::ResourceAccess::Write(rresp, m_Payload.get_axi_resp());
    detail::ResourceAccess::Write(rdata, m_Payload.get_data());
}

/**
 *  \brief  Create payload for data write phase from CodAL transport() function.
 *  \param[in] wvalid data is valid
 *  \param[out] wready slave is ready
 *  \param[in]  wdata data to be written
 *  \param[in]  wstrobe write strobe
 */
template<class T, class M, class S>
template<class WValid, class WReady, class W, class WStrobe>
RES_INLINE void AxiLiteInitiatorInterface<T, M, S>::do_data_write(WValid&& wvalid,
    WReady&& wready,
    W&& wdata,
    WStrobe&& wstrobe)
{
    m_Payload.reset();
    m_Payload.set_data(detail::ResourceAccess::Read(wdata));
    m_Payload.set_axi_wstrb(detail::ResourceAccess::Read(wstrobe));
    // ignore unused bits similar to HW
    m_Payload.set_axi_valid(detail::ResourceAccess::Read(wvalid) & CP_AXI_VALID);
    m_Payload.set_command((m_Payload.get_axi_valid() == CP_AXI_VALID) ? CP_CMD_WRITE : CP_CMD_NONE);
    // for the dumper it is required to set transfer size and address offset
    // must be reconstructed from the WSTRB
    Index bc = 0, offset = 0;
    InterfaceBaseType::CreateOffsetTransferSizeFromWstrb(offset,
        bc,
        static_cast<AXIWriteStrobe>(detail::ResourceAccess::Read(wstrobe)));
    m_Payload.set_axi_address_offset(offset);
    m_Payload.set_axi_transfer_size(bc);
    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT("write data begin:", m_Payload);
    this->transport(m_Payload, CP_PHS_DATA_WRITE);
    CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT("write data end:", m_Payload);
    detail::ResourceAccess::Write(wready, m_Payload.get_axi_ready());
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_AXI_LITE_INITIATOR_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_AXI_INITIATOR_INTERFACE_H_
