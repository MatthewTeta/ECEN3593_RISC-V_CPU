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
 *  \date   26. 11. 2018
 *  \brief  Definition of the class codasip::resources::CpbInitiatorInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CPB_INITIATOR_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CPB_INITIATOR_INTERFACE_H_

#include "simulator/resources/csr_interface.h"

//#define CODASIP_CPB_INITIATOR_DBG_OUT
#ifdef CODASIP_CPB_INITIATOR_DBG_OUT
#    define CODASIP_CPB_INITIATOR_DBG_OUT_PRINT(cmd, p)                                       \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() << ": CPB " \
                  << cmd << " " << p.PrintCpb() << std::endl
#else
#    define CODASIP_CPB_INITIATOR_DBG_OUT_PRINT(cmd, p)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::CpbInitiatorInterface
 *  \brief  Master interface that handles Codasip Processor Bus protocol.
 *  \}
 */
template<class T,
    class M = detail::InterfaceModule<typename T::data_type>,
    class S = detail::CODASIP_IFACE_CB_SELECT_FULL(blocking_cb, transport_cb)>
class CpbInitiatorInterface : public Interface<T, M, S>
{
public:
    // import data types from the parent/template classes
    using typename T::data_type;
    using typename T::param_type;
    /// \brief  Underlying type holding write strobe (exact bit-width)
    typedef typename std::conditional<T::BPW ==
            BitWidthTypeSelector<typename TypeSelector<T::BPW, false>::type>::value,
        typename TypeSelector<T::BPW, false>::type,
        ::codasip::Integer<T::BPW, false>>::type write_strobe_type;
    /// \brief  Data type used for effective parameter passing of the write strobe
    typedef typename detail::CallTraits<write_strobe_type>::param_type write_strobe_param_type;
    /// \brief  Interface base class
    typedef Interface<T, M, S> InterfaceBaseType;
    /// Protocol type
    static CODASIP_CONSTEXPR Protocol PROTOCOL = CP_PROTOCOL_CPB;
    /**
     *  \brief  Inherit constructor.
     */
    using InterfaceBaseType::Interface;
    /**
     *  \{
     *  \brief  Call InterfaceBaseType methods - resolve ambiguous call (multiple inheritance)
     */
    using InterfaceBaseType::blocking;
    using InterfaceBaseType::transport;
    /**
     *  \} \{
     *  \brief Override the IA interface
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
     *  \brief  Create payload for address phase from CodAL transport() function.
     *  \param[in]  phase phase identifier, must be CP_PHS_ADDRESS
     *  \param[out] aready output parameter specifying bus readiness.
     *  \param[in]  avalid indicates valid transaction from the master
     *  \param[in]  write indicates whether write or read transaction is requested
     *  \param[in]  addr requested address
     *  \param[in]  wdata write data in case of a writable interface, default
     *              value is zero.
     *  \param[in]  wstrb write strobe (per byte write enable) in case of a writable
     *              interface, default value is zero.
     */
    template<class Ready>
    void transport(const Phase phase,
        Ready& aready,
        const uint8_t avalid,
        const uint8_t write,
        const codasip_address_t addr,
        param_type wdata = 0u,
        write_strobe_param_type wstrb = 0u);
    /**
     *  \brief  Create payload for data phase from CodAL transport() function
     *          used by write-only interface.
     *  \param[in]  phase phase identifier, must be CP_PHS_DATA
     *  \param[out] valid indicates whether response is valid or not (transfer
     *          has finished or not)
     *  \param[out] resp transfer response (OKAY, ERROR)
     */
    template<class Valid, class Resp>
    void transport(const Phase phase, Valid& valid, Resp& resp);
    /**
     *  \brief  Create payload for data phase from CodAL transport() function
     *          used by read-able interface.
     *  \param[in]  phase phase identifier, must be CP_PHS_DATA
     *  \param[out] valid indicates whether response is valid or not (transfer
     *          has finished or not)
     *  \param[out] resp transfer response (OKAY, ERROR)
     *  \param[out] rdata read data from selected slave to the master
     */
    template<class Valid, class Resp, class RData>
    void transport(const Phase phase, Valid& valid, Resp& resp, RData& rdata);

protected:
    /// import payload for convenience
    using InterfaceBaseType::m_Payload;

private:
    template<class Resp>
    data_type DoReadCpb(Resp&, const codasip_address_t, const Index, const Command);
    template<class Resp>
    void DoWriteCpb(Resp&, param_type, const codasip_address_t, const Index, const Command);
    void PreparePayloadIA(const codasip_address_t, const Index, const Command, const CPBReadWriteCode);
};

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::CpbLiteInitiatorInterface
 *  \brief  Master interface that handles Codasip Processor Bus Lite protocol.
 *          The internals use the implementation of full CPB. The CA access
 *          functions \em transport() are hidden and replaced with simpler ones.
 *          Internally the full CPB implementation is called, but the new
 *          \em transport() definitions skip values of AREADY and VALID after
 *          being set.
 *  \}
 */
template<class T,
    class M = detail::InterfaceModule<typename T::data_type>,
    class S = detail::CODASIP_IFACE_CB_SELECT_FULL(blocking_cb, transport_cb)>
class CpbLiteInitiatorInterface : public CpbInitiatorInterface<T, M, S>
{
public:
    /// initiator base class
    typedef CpbInitiatorInterface<T, M, S> CpbInterfaceBaseType;
    // import data types from parent
    using typename T::param_type;
    using typename T::payload_type;
    typedef typename CpbInterfaceBaseType::write_strobe_param_type write_strobe_param_type;

    /**
     *  \brief  Inherit constructor.
     */
    using CpbInterfaceBaseType::CpbInitiatorInterface;
    /**
     *  \brief  Call InterfaceBaseType methods - resolve ambiguous call (multiple inheritance)
     *  \param  p transaction payload
     *  \param  phase transport phase identifier
     */
    void transport(payload_type& p, const Phase phase) override;
    /**
     *  \brief  Create payload for address phase from CodAL transport() function.
     *  \param[in]  phase phase identifier, must be CP_PHS_ADDRESS
     *  \param[in]  avalid indicates valid transaction from the master
     *  \param[in]  write indicates whether write or read transaction is requested
     *  \param[in]  addr requested address
     *  \param[in]  wdata write data in case of a writable interface, default
     *              value is zero.
     *  \param[in]  wstrb write strobe (per byte write enable) in case of a writable
     *              interface, default value is zero.
     */
    void transport(const Phase phase,
        const uint8_t avalid,
        const uint8_t write,
        const codasip_address_t addr,
        param_type wdata = 0u,
        write_strobe_param_type wstrb = 0u);
    /**
     *  \brief  Create payload for data phase from CodAL transport() function
     *          used by write-only interface.
     *  \param[in]  phase phase identifier, must be CP_PHS_DATA
     *  \param[out] resp transfer response (OKAY, ERROR)
     */
    template<class Resp>
    void transport(const Phase phase, Resp& resp);
    /**
     *  \brief  Create payload for data phase from CodAL transport() function
     *          used by read-able interface.
     *  \param[in]  phase phase identifier, must be CP_PHS_DATA
     *  \param[out] resp transfer response (OKAY, ERROR)
     *  \param[out] rdata read data from selected slave to the master
     */
    template<class Resp, class RData>
    void transport(const Phase phase, Resp& resp, RData& rdata);
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
CpbInitiatorInterface<T, M, S>::read(const codasip_address_t addr, const Index bc)
{
    CPBResponseCode resp = CP_CPB_OKAY;
    auto rdata = this->read(addr, bc, resp);
    if (resp != CP_CPB_OKAY)
    {
        this->DoAbortSimulation();
    }
    return rdata;
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type
CpbInitiatorInterface<T, M, S>::read(const codasip_address_t addr, const Index bc, Resp& resp)
{
    return DoReadCpb(resp, addr, bc, CP_CMD_READ);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE typename T::data_type
CpbInitiatorInterface<T, M, S>::dread(const codasip_address_t addr, const Index bc)
{   // ignore response, debug access should not shutdown the simulation
    CPBResponseCode resp = CP_CPB_OKAY;
    return DoReadCpb(resp, addr, bc, CP_CMD_DREAD);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
CpbInitiatorInterface<T, M, S>::write(param_type data, const codasip_address_t addr, const Index bc)
{
    CPBResponseCode resp = CP_CPB_OKAY;
    this->write(data, addr, bc, resp);
    if (resp != CP_CPB_OKAY)
    {
        this->DoAbortSimulation();
    }
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE void CpbInitiatorInterface<T, M, S>::write(param_type data,
    const codasip_address_t addr,
    const Index bc,
    Resp& resp)
{
    DoWriteCpb(resp, data, addr, bc, CP_CMD_WRITE);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
CpbInitiatorInterface<T, M, S>::dwrite(param_type data, const codasip_address_t addr, const Index bc)
{   // ignore response, debug access should not shutdown the simulation
    CPBResponseCode resp = CP_CPB_OKAY;
    DoWriteCpb(resp, data, addr, bc, CP_CMD_DWRITE);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void
CpbInitiatorInterface<T, M, S>::load(param_type data, const codasip_address_t addr, const Index bc)
{
    CPBResponseCode resp = CP_CPB_OKAY;
    DoWriteCpb(resp, data, addr, bc, CP_CMD_LOAD);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Ready>
RES_INLINE void CpbInitiatorInterface<T, M, S>::transport(const Phase phase,
    Ready& aready,
    const uint8_t avalid,
    const uint8_t write,
    const codasip_address_t addr,
    param_type wdata,
    write_strobe_param_type wstrb)
{
    m_Payload.reset(CP_CPB_READY);
    // order of valid and read/write is mandatory
    // ignore unused bits similar to HW
    m_Payload.set_cpb_avalid(avalid & CP_CPB_VALID);
    m_Payload.set_cpb_write(write & CP_CPB_WRITE);
    m_Payload.set_address(addr);
    m_Payload.set_data(wdata);
    m_Payload.set_cpb_wstrb(wstrb);
    // for the dumper it is required to set transfer size and address offset
    // must be reconstructed from the WSTRB
    Index bc = 0, offset = 0;
    InterfaceBaseType::CreateOffsetTransferSizeFromWstrb(offset, bc, wstrb);
    m_Payload.set_cpb_address_offset(offset);
    m_Payload.set_cpb_transfer_size(bc);

    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("address phase begin:", m_Payload);
    this->transport(m_Payload, phase);
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("address phase end:", m_Payload);
    detail::ResourceAccess::Write(aready, m_Payload.get_cpb_aready());
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Valid, class Resp>
RES_INLINE void CpbInitiatorInterface<T, M, S>::transport(const Phase phase, Valid& valid, Resp& resp)
{
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("data phase begin:", m_Payload);
    // do the transfer
    m_Payload.reset();
    this->transport(m_Payload, phase);
    // copy attributes
    detail::ResourceAccess::Write(valid, m_Payload.get_cpb_valid());
    detail::ResourceAccess::Write(resp, m_Payload.get_cpb_resp());
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("data phase end:", m_Payload);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Valid, class Resp, class RData>
RES_INLINE void
CpbInitiatorInterface<T, M, S>::transport(const Phase phase, Valid& valid, Resp& resp, RData& rdata)
{
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("data phase begin:", m_Payload);
    this->transport(phase, valid, resp);
    detail::ResourceAccess::Write(rdata, m_Payload.get_data());
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("data phase end:", m_Payload);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void CpbLiteInitiatorInterface<T, M, S>::transport(payload_type& p, const Phase phase)
{
    CpbInterfaceBaseType::transport(p, phase);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
RES_INLINE void CpbLiteInitiatorInterface<T, M, S>::transport(const Phase phase,
    const uint8_t avalid,
    const uint8_t write,
    const codasip_address_t addr,
    param_type wdata,
    write_strobe_param_type wstrb)
{
    CPBReadyCode dummyAReady = CP_CPB_READY;
    CpbInterfaceBaseType::transport(phase, dummyAReady, avalid, write, addr, wdata, wstrb);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp>
RES_INLINE void CpbLiteInitiatorInterface<T, M, S>::transport(const Phase phase, Resp& resp)
{
    CPBValidCode dummyValid = CP_CPB_INVALID;
    CpbInterfaceBaseType::transport(phase, dummyValid, resp);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class S>
template<class Resp, class RData>
RES_INLINE void
CpbLiteInitiatorInterface<T, M, S>::transport(const Phase phase, Resp& resp, RData& rdata)
{
    CPBValidCode dummyValid = CP_CPB_INVALID;
    CpbInterfaceBaseType::transport(phase, dummyValid, resp, rdata);
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Common implementation of the read/dread functions.
 *  \param[out] resp transfer response (OKAY, ERROR)
 *  \param[in]  addr requested address
 *  \param[in]  bc byte count
 *  \param[in]  cmd requested command (read/dread)
 */
template<class T, class M, class S>
template<class Resp>
RES_INLINE typename T::data_type CpbInitiatorInterface<T, M, S>::DoReadCpb(Resp& resp,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    if (bc == 0)
    {   // in IA do not create payload and do not pass it further to the slaves
        // the transaction is not valid
        detail::ResourceAccess::Write(resp, CP_CPB_OKAY);
        return static_cast<data_type>(0u);
    }
    PreparePayloadIA(addr, bc, cmd, CP_CPB_READ);
    m_Payload.set_cpb_wstrb(static_cast<data_type>(0u));
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("read begin:", m_Payload);
    this->blocking(m_Payload);
    detail::ResourceAccess::Write(resp, m_Payload.get_cpb_resp());
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("read end, not masked:", m_Payload);
    const auto offset = m_Payload.get_cpb_address_offset();
    const auto shift = InterfaceBaseType::get_amba_shift(offset, bc);
    const auto mask = InterfaceBaseType::create_amba_mask(offset, bc);
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
RES_INLINE void CpbInitiatorInterface<T, M, S>::DoWriteCpb(Resp& resp,
    param_type data,
    const codasip_address_t addr,
    const Index bc,
    const Command cmd)
{
    if (bc == 0)
    {   // in IA do not create payload and do not pass it further to the slaves
        // the transaction is not valid
        detail::ResourceAccess::Write(resp, CP_CPB_OKAY);
        return;
    }
    PreparePayloadIA(addr, bc, cmd, CP_CPB_WRITE);
    const auto offset = InterfaceBaseType::get_offset(addr, this->get_address_alignment());
    m_Payload.set_cpb_wstrb(this->template CreateWriteStrobe<write_strobe_type>(offset, bc));
    m_Payload.set_data(data << InterfaceBaseType::get_amba_shift(offset, bc));
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("write begin:", m_Payload);
    this->blocking(m_Payload);
    detail::ResourceAccess::Write(resp, m_Payload.get_cpb_resp());
    CODASIP_CPB_INITIATOR_DBG_OUT_PRINT("write end:", m_Payload);
}

/**
 *  \brief  Prepare payload for an IA access function with given arguments.
 *  \param  addr requested address
 *  \param  bc byte count
 *  \param  cmd requested command (read/dread/write/dwrite)
 *  \param  rw requested CPB access type (read or write)
 */
template<class T, class M, class S>
RES_INLINE void CpbInitiatorInterface<T, M, S>::PreparePayloadIA(const codasip_address_t addr,
    const Index bc,
    const Command cmd,
    const CPBReadWriteCode rw)
{
    m_Payload.reset(CP_CPB_WAIT);
    m_Payload.set_cpb_avalid(CP_CPB_VALID);
    m_Payload.set_cpb_write(rw);
    m_Payload.set_command(cmd);
    // for the outside world, the access is always word-wide
    m_Payload.set_address(InterfaceBaseType::get_aligned_address(addr, this->get_address_alignment()));
    m_Payload.set_bc(T::BPW);
    // store address offset and original transfer size for CPB protocol checker,
    // otherwise invalid values and combinations won't be detected
    // and write dumper would provide bad data
    m_Payload.set_cpb_address_offset(
        InterfaceBaseType::get_offset(addr, this->get_address_alignment()));
    m_Payload.set_cpb_transfer_size(bc);
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_CPB_INITIATOR_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_CPB_INITIATOR_INTERFACE_H_
