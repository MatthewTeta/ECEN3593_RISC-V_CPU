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
 *  \date   Jan 12, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_MASTER_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_MASTER_INTERFACE_H_

#include "simulator/resources/csr_ahb_initiator_interface.h"
#include "simulator/resources/csr_axi_lite_initiator_interface.h"
#include "simulator/resources/csr_helpers.h"

namespace codasip {
namespace resources {

/// Protocol specific method.
#define SPEC_DO_METHOD_DECL(PROT)                                \
    template<Protocol _Protocol = _InitiatorInterface::PROTOCOL, \
        class Resp,                                              \
        typename std::enable_if<_Protocol == CP_PROTOCOL_##PROT>::type* = nullptr>
#define SPEC_DO_METHOD_AHB SPEC_DO_METHOD_DECL(AHB_LITE)
#define SPEC_DO_METHOD_AXI_LITE SPEC_DO_METHOD_DECL(AXI_LITE)
#define SPEC_DO_METHOD_AXI SPEC_DO_METHOD_DECL(AXI)
#define SPEC_METHOD_DECL(PROT)                                   \
    template<Protocol _Protocol = _InitiatorInterface::PROTOCOL, \
        typename std::enable_if<_Protocol == CP_PROTOCOL_##PROT>::type* = nullptr>
#define SPEC_METHOD_AHB SPEC_METHOD_DECL(AHB_LITE)
#define SPEC_METHOD_AXI_LITE SPEC_METHOD_DECL(AXI_LITE)
#define SPEC_METHOD_AXI SPEC_METHOD_DECL(AXI)
#define SPEC_DO_METHOD_DEF(PROT) \
    template<Protocol _Protocol, class Resp, typename std::enable_if<_Protocol == CP_PROTOCOL_##PROT>::type*>
#define SPEC_METHOD_DEF(PROT) \
    template<Protocol _Protocol, typename std::enable_if<_Protocol == CP_PROTOCOL_##PROT>::type*>

/**
 *  \class  codasip::resources::CacheMasterInterface
 *  \brief  Cache master interface - unifies access through AHB/AXI/CLB interfaces.
 *  \tparam _InitiatorInterface Underlying protocol-specific initiator interface.
 */
template<class _InitiatorInterface, bool IsLoadStore>
class CacheMasterInterface : public _InitiatorInterface
{
public:
    /// Base protocol-specific interface type.
    typedef _InitiatorInterface InterfaceBaseType;
    /// Module type.
    typedef typename InterfaceBaseType::module_type module_type;
    /// Data type.
    typedef typename InterfaceBaseType::data_type data_type;
    /// Param type.
    typedef typename InterfaceBaseType::param_type param_type;
    /// Payload type.
    typedef typename InterfaceBaseType::payload_type payload_type;
    using InterfaceBaseType::PROTOCOL;
    /**
     *  \copydoc InterfaceBaseType::Interface()
     */
    CacheMasterInterface(const std::string& name, const Uid uid, module_type* module = nullptr);
    /**
     *  \brief  Reset state informations (required when burst is interrupted with reset).
     */
    void Reset();
    /**
     *  \brief  Move simulation one clock cycle.
     */
    void ClockCycle();
    /**
      * \{
      * \brief Override the IA interface.
      */
    template<class Resp>
    data_type read(const codasip_address_t addr,
        const Index bc,
        Resp& resp,
        const uint8_t hprot,
        const uint8_t hmastlock);
    data_type dread(const codasip_address_t addr, const Index bc = InterfaceBaseType::mixin_base::BPW);
    template<class Resp>
    data_type dread(const codasip_address_t addr, const Index bc, Resp& resp);
    template<class Resp>
    void write(param_type data,
        const codasip_address_t addr,
        const Index bc,
        Resp& resp,
        const uint8_t hprot,
        const uint8_t hmastlock);
    void dwrite(param_type data,
        const codasip_address_t addr,
        const Index bc = InterfaceBaseType::mixin_base::BPW);
    void load(param_type data,
        const codasip_address_t addr,
        const Index bc = InterfaceBaseType::mixin_base::BPW);
    /**
     *  \}
     *  \brief Return last IA ahb response code - read() and write() do not return it directly.
     */
    AHBResponseCode GetLastAHBResponseCode() const;
    /**
     *  \brief Return last IA ahb ready code - read() and write() do not return it directly.
     */
    AHBReadyCode GetLastAHBReadyCode() const;
    /**
     *  \brief Start burst - set up burst mode for subsequent CA transactions. Only important
     *         for AHB.
     *  \param mode Burst mode.
     */
    void StartBurst(const AHBBurstMode mode);
    /**
     *  \brief  Start burst - set up burst mode for subsequent CA transactions. Only important
     *          for AXI.
     *  \param  type Burst type.
     *  \param  address Initial burst address.
     *  \param  length Burst length.
     */
    void StartBurst(const AXIBurstType type, const codasip_address_t address, const uint8_t length);
    /**
     *  \brief Stop burst - go back to single transfers. Only important for AHB.
     */
    void StopBurst();
    /**
     *  \brief  Returns number of memory interface errors.
     */
    Counter GetMemoryErrorCount() const
    {
        return m_MemErrorCount;
    }
    /**
     *  \brief  Resets memory error counter.
     */
    void ResetMemoryErrorCount()
    {
        m_MemErrorCount = 0;
    }
    /// Sets NC flag for next request.
    void SetNonCacheable()
    {
        m_NonCacheable = true;
    }
    /**
     *  \{
     *  \brief Specific for AHB Lite.
     */
    SPEC_METHOD_AHB AHBReadyCode AddressPhase(const Command cmd,
        const codasip_address_t addr,
        const Index bi,
        const Index bc,
        const uint8_t hprot,
        const uint8_t hmastlock);
    SPEC_METHOD_AHB AHBReadyCode AddressPhase(Payload<data_type>& p);
    SPEC_METHOD_AHB void DataPhaseRead(AHBReadyCode& ready, AHBResponseCode& resp, data_type& data);
    SPEC_METHOD_AHB void
    DataPhaseWrite(AHBReadyCode& ready, AHBResponseCode& resp, const data_type data);
    SPEC_METHOD_AHB void DataPhaseWrite(Payload<data_type>& p);
    SPEC_METHOD_AHB void DataPhaseWriteResponse(AHBReadyCode& ready, AHBResponseCode& resp);
    SPEC_METHOD_AHB void
    PreparePayloadIA(const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);
    /**
    *  \} \{
    *  \brief Specific for AXI Lite.
    */
    SPEC_METHOD_AXI_LITE AHBReadyCode AddressPhase(const Command cmd,
        const codasip_address_t addr,
        const Index bi,
        const Index bc,
        const uint8_t hprot,
        const uint8_t hmastlock);
    SPEC_METHOD_AXI_LITE AHBReadyCode AddressPhase(Payload<data_type>& p);
    SPEC_METHOD_AXI_LITE void
    DataPhaseRead(AHBReadyCode& ready, AHBResponseCode& resp, data_type& data);
    SPEC_METHOD_AXI_LITE void
    DataPhaseWrite(AHBReadyCode& ready, AHBResponseCode& resp, const data_type data);
    SPEC_METHOD_AXI_LITE void DataPhaseWrite(Payload<data_type>& p);
    SPEC_METHOD_AXI_LITE void DataPhaseWriteResponse(AHBReadyCode& ready, AHBResponseCode& resp);
    SPEC_METHOD_AXI_LITE void
    PreparePayloadIA(const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);
    /**
    *  \} \{
    *  \brief Specific for AXI.
    */
    SPEC_METHOD_AXI AHBReadyCode AddressPhase(const Command cmd,
        const codasip_address_t addr,
        const Index bi,
        const Index bc,
        const uint8_t hprot,
        const uint8_t hmastlock);
    SPEC_METHOD_AXI AHBReadyCode AddressPhase(Payload<data_type>& p);
    SPEC_METHOD_AXI void DataPhaseRead(AHBReadyCode& ready, AHBResponseCode& resp, data_type& data);
    SPEC_METHOD_AXI void
    DataPhaseWrite(AHBReadyCode& ready, AHBResponseCode& resp, const data_type data);
    SPEC_METHOD_AXI void DataPhaseWrite(Payload<data_type>& p);
    SPEC_METHOD_AXI void DataPhaseWriteResponse(AHBReadyCode& ready, AHBResponseCode& resp);
    SPEC_METHOD_AXI void
    PreparePayloadIA(const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);
    /** \} */
protected:
    using InterfaceBaseType::m_Payload;

private:
    static constexpr AHBProtectionMode AHB_PROTECTION_MODE = static_cast<AHBProtectionMode>(
        IsLoadStore ? CP_AHB_PROT_DEFAULT : CP_AHB_PRIVILEGED);
    static constexpr AXIProtectionMode AXI_PROTECTION_MODE = static_cast<AXIProtectionMode>(
        IsLoadStore ? CP_AXI_PROT_PRIVILEGED : (CP_AXI_PROT_INSTR | CP_AXI_PROT_PRIVILEGED));
    /**
     *  \{
     *  \brief  Increments memory error counter in case of error response.
     */
    SPEC_METHOD_AHB void UpdateMemoryErrorCount(const AHBResponseCode resp)
    {
        if (resp == CP_AHB_ERROR)
        {
            m_MemErrorCount = 1;
        }
    }
    SPEC_METHOD_AXI_LITE void UpdateMemoryErrorCount(const AXIResponseCode resp)
    {
        if ((resp == CP_AXI_SLVERR) || (resp == CP_AXI_DECERR))
        {
            m_MemErrorCount = 1;
        }
    }
    SPEC_METHOD_AXI void UpdateMemoryErrorCount(const AXIResponseCode resp)
    {
        if ((resp == CP_AXI_SLVERR) || (resp == CP_AXI_DECERR))
        {
            m_MemErrorCount = 1;
        }
    }
    void UpdateMemoryErrorCount(const bool inc)
    {
        if (inc)
        {
            m_MemErrorCount = 1;
        }
    }
    /// \}

    template<class Resp>
    data_type
    DoRead(Resp&, const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);

    template<class Resp>
    void
    DoWrite(Resp&, param_type, const codasip_address_t, const Index, const Command, const uint8_t, const uint8_t);

    /// Stored offset for masking during the data phase.
    Index m_Offset = 0;
    /// Stored bc for masking during the data phase.
    Index m_Bc = 0;
    /// (AHB) Burst mode used when reading/writing whole cache line.
    AHBBurstMode m_BurstMode = CP_AHB_SINGLE;
    /// (AHB) Transfer type.
    AHBTransferType m_TransferType = CP_AHB_NONSEQ;
    /// (AXI) Burst address.
    codasip_address_t m_AXIBurstAddress = 0;
    /// (AXI) Burst type.
    AXIBurstType m_AXIBurstType = CP_AXI_BURST_INCR;
    /// (AXI) Burst length.
    uint8_t m_AXIBurstLength = 0;
    /// (AXI) Number of realized transfers.
    uint8_t m_AXINumTransfers = 0;
    /// Memory error counter.
    Counter m_MemErrorCount = 0;
    /// Last payload - needed for AHB.
    payload_type m_LastPayload;
    /// Non-cacheable flag for next request.
    bool m_NonCacheable = false;
};

#define MASTER_INTERFACE_DO_METHOD(PROT, RET_TYPE)        \
    template<class _InitiatorInterface, bool IsLoadStore> \
    SPEC_DO_METHOD_DEF(PROT)                              \
    RES_INLINE RET_TYPE CacheMasterInterface<_InitiatorInterface, IsLoadStore>

#define MASTER_INTERFACE_METHOD(PROT, RET_TYPE)           \
    template<class _InitiatorInterface, bool IsLoadStore> \
    SPEC_METHOD_DEF(PROT)                                 \
    RES_INLINE RET_TYPE CacheMasterInterface<_InitiatorInterface, IsLoadStore>

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              AHB                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AHB_LITE, AHBReadyCode)::AddressPhase(const Command cmd,
    const codasip_address_t addr,
    const Index bi,
    const Index bc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    // if bc is 0, perform an idle transfer
    if (bc == 0)
    {
        this->transport(CP_PHS_ADDRESS,
            CP_AHB_IDLE,
            cmd == CP_CMD_READ ? CP_AHB_READ : CP_AHB_WRITE,
            addr + bi,
            0,
            hprot,
            hmastlock,
            CP_AHB_SINGLE);
    }
    else
    {
        // store for data phase
        m_Offset = InterfaceBaseType::get_offset(addr + bi, InterfaceBaseType::SUBBLOCKS);
        m_Bc = bc;
        this->transport(CP_PHS_ADDRESS,
            m_TransferType,
            cmd == CP_CMD_READ ? CP_AHB_READ : CP_AHB_WRITE,
            addr + bi,
            Payload<data_type>::get_ahb_hsize(bc),
            hprot,
            hmastlock,
            m_BurstMode);

        // if the burst continues, next transfer is sequential
        if (m_BurstMode != CP_AHB_SINGLE)
        {
            m_TransferType = CP_AHB_SEQ;
        }
    }
    return m_LastPayload.get_ahb_hready();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AHB_LITE, AHBReadyCode)::AddressPhase(Payload<data_type>&)
{
    //UNUSED
    return CP_AHB_READY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AHB_LITE,
    void)::DataPhaseRead(AHBReadyCode& ready, AHBResponseCode& resp, data_type& data)
{
    this->transport(CP_PHS_DATA, ready, resp, data);

    UpdateMemoryErrorCount(resp);
    m_LastPayload.set_ahb_hready(ready);
    m_LastPayload.set_ahb_hresp(resp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AHB_LITE,
    void)::DataPhaseWrite(AHBReadyCode& ready, AHBResponseCode& resp, const data_type data)
{
    data_type rdata;   // will be discarded
    data_type wdata = data;
    this->transport(CP_PHS_DATA, ready, resp, rdata, wdata);
    UpdateMemoryErrorCount(resp);
    m_LastPayload.set_ahb_hready(ready);
    m_LastPayload.set_ahb_hresp(resp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AHB_LITE, void)::DataPhaseWrite(Payload<data_type>& p)
{
    AHBReadyCode ready = CP_AHB_READY;
    AHBResponseCode resp = CP_AHB_OKAY;
    DataPhaseWrite(ready, resp, p.get_data());
    p.set_ahb_hready(ready);
    p.set_ahb_hresp(resp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AHB_LITE, void)::DataPhaseWriteResponse(AHBReadyCode& ready,
    AHBResponseCode& resp)
{   // should be called right after DataPhaseWrite
    ready = this->m_Payload.get_ahb_hready();
    resp = this->m_Payload.get_ahb_hresp();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AHB_LITE, void)::PreparePayloadIA(const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const AHBReadWriteCode rw = (cmd == CP_CMD_READ || cmd == CP_CMD_DREAD) ? CP_AHB_READ
                                                                            : CP_AHB_WRITE;
    m_Payload.set_ahb_htrans(m_TransferType);
    m_Payload.set_ahb_hwrite(rw);
    m_Payload.set_command(cmd);
    m_Payload.set_address(addr);
    m_Payload.set_bc(bc);
    m_Payload.set_ahb_hprot(hprot);
    m_Payload.set_ahb_hmastlock(hmastlock);
    m_Payload.set_ahb_hburst(m_BurstMode);
    m_Payload.set_ahb_hready(CP_AHB_READY);
    m_Payload.set_ahb_hresp(CP_AHB_OKAY);
    m_Payload.set_ahb_hsel(false);

    if (m_BurstMode != CP_AHB_SINGLE)
    {
        m_TransferType = CP_AHB_SEQ;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           AXI LITE                                             //
////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI_LITE, AHBReadyCode)::AddressPhase(const Command cmd,
    const codasip_address_t addr,
    const Index bi,
    const Index bc,
    const uint8_t hprot,
    const uint8_t /*hmastlock*/)
{
    AXIReadyCode ready;
    // need to read whole word and manually do the bit mask & shift
    codasip_address_t alignedAddr = InterfaceBaseType::get_aligned_address(addr + bi,
        InterfaceBaseType::SUBBLOCKS);
    // store for data phase
    m_Offset = InterfaceBaseType::get_offset(addr + bi, InterfaceBaseType::SUBBLOCKS);
    m_Bc = bc;

    uint8_t axprot = 2 | ((hprot >> 1) & 0x1) | (((~hprot) & 0x1) << 2);
    this->transport(cmd == CP_CMD_READ ? CP_PHS_ADDRESS_READ : CP_PHS_ADDRESS_WRITE,
        CP_AXI_VALID,
        ready,
        alignedAddr,
        axprot);
    return ready == CP_AXI_READY ? CP_AHB_READY : CP_AHB_WAIT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI_LITE, AHBReadyCode)::AddressPhase(Payload<data_type>&)
{
    //UNUSED
    return CP_AHB_READY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI_LITE,
    void)::DataPhaseRead(AHBReadyCode& ready, AHBResponseCode& resp, data_type& data)
{
    AXIValidCode valid;
    AXIResponseCode axiResponse;
    this->transport(CP_PHS_DATA_READ, valid, CP_AXI_READY, axiResponse, data);

    if (valid == CP_AXI_INVALID)
    {
        ready = CP_AHB_WAIT;
        resp = CP_AHB_OKAY;
    }
    else
    {
        if (axiResponse == CP_AXI_DECERR || axiResponse == CP_AXI_SLVERR)
        {
            ready = CP_AHB_WAIT;
            resp = CP_AHB_ERROR;
        }
        else
        {
            ready = CP_AHB_READY;
            resp = CP_AHB_OKAY;
        }
    }
    if (valid != CP_AXI_INVALID)
    {
        UpdateMemoryErrorCount(axiResponse);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI_LITE,
    void)::DataPhaseWrite(AHBReadyCode& ready, AHBResponseCode& resp, const data_type data)
{
    AXIReadyCode axiReady;
    // prepare data
    data_type wdata = data;
    // prepare write strobe
    auto wstrobe = InterfaceBaseType::template CreateWriteStrobe<uint8_t>(m_Offset, m_Bc);
    this->transport(CP_PHS_DATA_WRITE, CP_AXI_VALID, axiReady, wdata, wstrobe);

    resp = CP_AHB_OKAY;
    ready = (axiReady == CP_AXI_WAIT) ? CP_AHB_WAIT : CP_AHB_READY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI_LITE, void)::DataPhaseWrite(Payload<data_type>& p)
{
    AXIReadyCode axiReady;
    this->transport(CP_PHS_DATA_WRITE, CP_AXI_VALID, axiReady, p.get_data(), p.get_axi_wstrb());
    p.set_ahb_hresp(CP_AHB_OKAY);
    p.set_ahb_hready((axiReady == CP_AXI_WAIT) ? CP_AHB_WAIT : CP_AHB_READY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI_LITE, void)::DataPhaseWriteResponse(AHBReadyCode& ready,
    AHBResponseCode& resp)
{
    // get last write response
    AXIValidCode bvalid;
    AXIResponseCode bresp;
    this->transport(CP_PHS_RESPONSE_WRITE, bvalid, CP_AXI_READY, bresp);

    if (bvalid == CP_AXI_INVALID)
    {
        ready = CP_AHB_WAIT;
        resp = CP_AHB_OKAY;
    }
    else
    {
        if (bresp == CP_AXI_OKAY)
        {
            ready = CP_AHB_READY;
            resp = CP_AHB_OKAY;
        }
        else
        {
            ready = CP_AHB_WAIT;
            resp = CP_AHB_ERROR;
        }
    }
    if (bvalid != CP_AXI_INVALID)
    {
        UpdateMemoryErrorCount(bresp);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI_LITE, void)::PreparePayloadIA(const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const uint8_t hprot,
    const uint8_t /*hmastlock*/)
{
    _InitiatorInterface::PreparePayloadIA(addr, bc, cmd);
    uint8_t axprot = 2 | ((hprot >> 1) & 0x1) | (((~hprot) & 0x1) << 2);
    m_Payload.set_axi_prot(axprot);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              AXI                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI, AHBReadyCode)::AddressPhase(const Command cmd,
    const codasip_address_t /*addr*/,
    const Index /*bi*/,
    const Index bc,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    const auto phase = cmd == CP_CMD_READ ? CP_PHS_ADDRESS_READ : CP_PHS_ADDRESS_WRITE;
    auto axready = CP_AXI_READY;
    const auto axprot = 2 | ((hprot >> 1) & 0x1) | (((~hprot) & 0x1) << 2);
    const auto axsize = payload_type::get_axi_size(bc);
    const auto axcache = hprot & CP_AHB_CACHEABLE ? 0xF : (hprot & CP_AHB_BUFFERABLE ? 0x1 : 0x0);

    this->transport(phase,
        CP_AXI_VALID,
        axready,
        m_AXIBurstAddress,
        axprot,
        axsize,
        m_AXIBurstType,
        m_AXIBurstLength,
        hmastlock,
        axcache,
        0,
        0,
        0);
    return axready == CP_AXI_READY ? CP_AHB_READY : CP_AHB_WAIT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI, AHBReadyCode)::AddressPhase(Payload<data_type>& p)
{
    const auto phase = p.get_command() == CP_CMD_READ ? CP_PHS_ADDRESS_READ : CP_PHS_ADDRESS_WRITE;
    auto axready = CP_AXI_READY;
    this->transport(phase,
        CP_AXI_VALID,
        axready,
        p.get_address(),
        p.get_axi_prot(),
        p.get_axi_size(),
        p.get_axi_burst(),
        p.get_axi_len(),
        p.get_axi_lock(),
        p.get_axi_cache(),
        0,
        0,
        0);

    return axready == CP_AXI_READY ? CP_AHB_READY : CP_AHB_WAIT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI,
    void)::DataPhaseRead(AHBReadyCode& ready, AHBResponseCode& resp, data_type& data)
{
    auto rvalid = CP_AXI_INVALID;
    auto rresp = CP_AXI_OKAY;
    uint8_t rlast = 0;
    uint8_t rid;

    this->transport(CP_PHS_DATA_READ, rvalid, CP_AXI_READY, rresp, data, rlast, rid);

    if (rvalid == CP_AXI_INVALID)
    {
        ready = CP_AHB_WAIT;
        resp = CP_AHB_OKAY;
    }
    else
    {
        UpdateMemoryErrorCount(rresp);
        if (rresp == CP_AXI_DECERR || rresp == CP_AXI_SLVERR)
        {
            ready = CP_AHB_WAIT;
            resp = CP_AHB_ERROR;
        }
        else
        {
            ready = CP_AHB_READY;
            resp = CP_AHB_OKAY;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI,
    void)::DataPhaseWrite(AHBReadyCode& /*ready*/, AHBResponseCode& /*resp*/, const data_type /*data*/)
{
    // unused
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI, void)::DataPhaseWrite(Payload<data_type>& p)
{
    AXIReadyCode wready = CP_AXI_READY;
    this->transport(CP_PHS_DATA_WRITE,
        CP_AXI_VALID,
        wready,
        p.get_data(),
        p.get_axi_wstrb(),
        p.get_axi_last());
    p.set_ahb_hready(wready == CP_AXI_READY ? CP_AHB_READY : CP_AHB_WAIT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI, void)::DataPhaseWriteResponse(AHBReadyCode& ready, AHBResponseCode& resp)
{
    AXIValidCode bvalid = CP_AXI_VALID;
    AXIResponseCode bresp = CP_AXI_OKAY;
    uint8_t bid = 0;

    this->transport(CP_PHS_RESPONSE_WRITE, bvalid, CP_AXI_READY, bresp, bid);

    if (bvalid == CP_AXI_INVALID)
    {
        ready = CP_AHB_WAIT;
        resp = CP_AHB_OKAY;
    }
    else
    {
        if (bresp == CP_AXI_OKAY)
        {
            ready = CP_AHB_READY;
            resp = CP_AHB_OKAY;
        }
        else
        {
            ready = CP_AHB_WAIT;
            resp = CP_AHB_ERROR;
        }
        UpdateMemoryErrorCount(bresp);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
MASTER_INTERFACE_METHOD(AXI, void)::PreparePayloadIA(const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    _InitiatorInterface::PreparePayloadIA(addr, bc, cmd);

    m_Payload.clear_axi_phase();
    if (m_AXINumTransfers == 0)
    {
        m_Payload.set_axi_address_phase();
        m_Payload.set_address(m_AXIBurstAddress);
        m_Payload.set_axi_burst(m_AXIBurstType);
        m_Payload.set_axi_len(m_AXIBurstLength);
        m_Payload.set_axi_lock(hmastlock);
        if (hprot & CP_AHB_CACHEABLE)
        {
            m_Payload.set_axi_cache(0xF);
        }
        else
        {
            m_Payload.set_axi_cache(0x0);
            if (hprot & CP_AHB_BUFFERABLE)
            {
                m_Payload.set_axi_cache(0x1);
            }
        }
        const uint8_t axprot = 2 | ((hprot >> 1) & 0x1) | (((~hprot) & 0x1) << 2);
        m_Payload.set_axi_prot(axprot);
    }
    if (cmd == CP_CMD_WRITE || cmd == CP_CMD_DWRITE || cmd == CP_CMD_LOAD)
    {
        m_Payload.set_axi_data_phase();
    }

    if (m_AXINumTransfers++ == m_AXIBurstLength &&
        (cmd == CP_CMD_WRITE || cmd == CP_CMD_DWRITE || cmd == CP_CMD_LOAD))
    {
        m_Payload.set_axi_last(1);
    }
    else
    {
        m_Payload.set_axi_last(0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                            COMMON                                              //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::CacheMasterInterface(const std::string& name,
    const Uid uid,
    module_type* module)
  : InterfaceBaseType(name, uid, module)
{
    m_LastPayload.reset(CP_AHB_READY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE void CacheMasterInterface<_InitiatorInterface, IsLoadStore>::Reset()
{
    m_Offset = 0;
    m_Bc = 0;
    m_BurstMode = CP_AHB_SINGLE;
    m_TransferType = CP_AHB_NONSEQ;
    ResetMemoryErrorCount();
    InterfaceBaseType::reset();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE void CacheMasterInterface<_InitiatorInterface, IsLoadStore>::ClockCycle()
{
    if (m_LastPayload.get_ahb_hresp() == CP_AHB_ERROR)
    {
        if (m_LastPayload.get_ahb_hready() == CP_AHB_WAIT)
        {
            m_LastPayload.set_ahb_hready(CP_AHB_READY);
        }
        if (m_LastPayload.get_ahb_hready() == CP_AHB_READY)
        {
            m_LastPayload.set_ahb_hresp(CP_AHB_OKAY);
        }
    }
    else
    {
        m_LastPayload.reset(CP_AHB_READY);
    }
    InterfaceBaseType::clock_cycle();
}
//////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
template<class Resp>
RES_INLINE typename _InitiatorInterface::data_type
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::read(const codasip_address_t addr,
    const Index bc,
    Resp& resp,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    return DoRead(resp, addr, bc, CP_CMD_READ, hprot, hmastlock);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE typename _InitiatorInterface::data_type
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::dread(const codasip_address_t addr,
    const Index bc)
{
    uint8_t resp = 0;
    return DoRead(resp, addr, bc, CP_CMD_DREAD, AHB_PROTECTION_MODE, CP_AHB_UNLOCK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
template<class Resp>
RES_INLINE typename _InitiatorInterface::data_type
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::dread(const codasip_address_t addr,
    const Index bc,
    Resp& resp)
{
    return DoRead(resp, addr, bc, CP_CMD_DREAD, AHB_PROTECTION_MODE, CP_AHB_UNLOCK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
template<class Resp>
RES_INLINE void CacheMasterInterface<_InitiatorInterface, IsLoadStore>::write(param_type data,
    const codasip_address_t addr,
    const Index bc,
    Resp& resp,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    DoWrite(resp, data, addr, bc, CP_CMD_WRITE, hprot, hmastlock);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE void CacheMasterInterface<_InitiatorInterface, IsLoadStore>::dwrite(param_type data,
    const codasip_address_t addr,
    const Index bc)
{
    uint8_t resp = 0;
    DoWrite(resp, data, addr, bc, CP_CMD_DWRITE, AHB_PROTECTION_MODE, CP_AHB_UNLOCK);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE void CacheMasterInterface<_InitiatorInterface, IsLoadStore>::load(param_type data,
    const codasip_address_t addr,
    const Index bc)
{
    uint8_t resp = 0;
    DoWrite(resp, data, addr, bc, CP_CMD_LOAD, AHB_PROTECTION_MODE, CP_AHB_UNLOCK);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE AHBResponseCode
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::GetLastAHBResponseCode() const
{
    return m_Payload.get_ahb_hresp();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE AHBReadyCode CacheMasterInterface<_InitiatorInterface, IsLoadStore>::GetLastAHBReadyCode() const
{
    return m_Payload.get_ahb_hready();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE void
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::StartBurst(const AHBBurstMode mode)
{
    // empty for non-AHB
    if (InterfaceBaseType::PROTOCOL == CP_PROTOCOL_AHB_LITE)
    {
        m_BurstMode = mode;
        // change of the burst mode means nonsequential transfer type (first in the new burst)
        m_TransferType = CP_AHB_NONSEQ;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE void
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::StartBurst(const AXIBurstType type,
    const codasip_address_t address,
    const uint8_t length)
{
    if (InterfaceBaseType::PROTOCOL == CP_PROTOCOL_AXI)
    {
        m_AXIBurstAddress = address;
        m_AXIBurstType = type;
        m_AXIBurstLength = length;
        m_AXINumTransfers = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _InitiatorInterface, bool IsLoadStore>
RES_INLINE void CacheMasterInterface<_InitiatorInterface, IsLoadStore>::StopBurst()
{
    if (InterfaceBaseType::PROTOCOL == CP_PROTOCOL_AHB_LITE)
    {
        m_BurstMode = CP_AHB_SINGLE;
        m_TransferType = CP_AHB_NONSEQ;
    }
    if (InterfaceBaseType::PROTOCOL == CP_PROTOCOL_AXI)
    {
        m_AXIBurstType = CP_AXI_BURST_INCR;
        m_AXIBurstLength = 0;
        m_AXINumTransfers = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \copydoc codasip::resources::AxiInitiatorInterface::DoRead()
template<class _InitiatorInterface, bool IsLoadStore>
template<class Resp>
RES_INLINE typename _InitiatorInterface::data_type
CacheMasterInterface<_InitiatorInterface, IsLoadStore>::DoRead(Resp& resp,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const uint8_t hprot,
    const uint8_t hmastlock)
{
    if (bc == 0)
    {   // in IA do not create payload and do not pass it further to the slaves
        // the transaction is not valid
        detail::ResourceAccess::Write(resp, 0);
        return static_cast<data_type>(0u);
    }
    PreparePayloadIA(addr, bc, cmd, hprot, hmastlock);
    this->blocking(m_Payload);

    detail::ResourceAccess::Write(resp, static_cast<uint8_t>(m_Payload.get_axi_resp()));
    UpdateMemoryErrorCount(m_Payload.is_error());
    const auto shift = InterfaceBaseType::get_amba_shift(
        InterfaceBaseType::get_offset(addr, InterfaceBaseType::SUBBLOCKS),
        bc);
    auto mask = InterfaceBaseType::create_amba_mask(
        InterfaceBaseType::get_offset(addr, InterfaceBaseType::SUBBLOCKS),
        bc);
    return (m_Payload.get_data() & mask) >> shift;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \copydoc codasip::resources::AxiInitiatorInterface::DoWrite()
template<class _InitiatorInterface, bool IsLoadStore>
template<class Resp>
RES_INLINE void CacheMasterInterface<_InitiatorInterface, IsLoadStore>::DoWrite(Resp& resp,
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
        detail::ResourceAccess::Write(resp, 0);
        return;
    }
    PreparePayloadIA(addr, bc, cmd, hprot, hmastlock);
    m_Payload.set_data(data << InterfaceBaseType::get_amba_shift(
                           InterfaceBaseType::get_offset(addr, InterfaceBaseType::SUBBLOCKS),
                           bc));
    this->blocking(m_Payload);
    detail::ResourceAccess::Write(resp, static_cast<uint8_t>(m_Payload.get_axi_resp()));
    UpdateMemoryErrorCount(m_Payload.is_error());
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CACHE_MASTER_INTERFACE_H_
