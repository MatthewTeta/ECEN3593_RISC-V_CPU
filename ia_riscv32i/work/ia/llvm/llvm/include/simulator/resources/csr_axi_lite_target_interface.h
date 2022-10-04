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
 *  \brief  Definition of the class codasip::resources::AxiLiteTargetInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_LITE_TARGET_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_AXI_LITE_TARGET_INTERFACE_H_

#include "simulator/resources/csr_axi_lite_initiator_interface.h"
#include "simulator/resources/csr_axi_request.h"
#include "simulator/resources/csr_latency_interface.h"

//#define CODASIP_AXI_LITE_TARGET_DBG_OUT
#ifdef CODASIP_AXI_LITE_TARGET_DBG_OUT
#    define CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT(cmd, p)                         \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() \
                  << ": AXI4-Lite " << cmd << " " << p.PrintAxiLite() << std::endl
#else
#    define CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT(cmd, p)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiLiteTargetInterface
 *  \brief  Interface that handles AXI4-Lite protocol of a memory slave.
 *  \tparam T underlying implementation type
 *  \tparam M parent module contains static functions and compile-time constants
 *          accessing read/write latency
 *  \tparam A contains compile-time constants indicating read/write capability
 *  \}
 */
template<class T, class M, class A>
class AxiLiteTargetInterface : public LatencyInterface<T, M>
{
public:
    /// \brief  Import type definitions from the base classes
    using typename T::data_type;
    using typename T::DataAlignment;
    /// \brief  Concrete payload type used by this class
    typedef Payload<typename T::data_type> PayloadType;
    /// \brief  Request handler class
    typedef AxiRequest<typename T::data_type> RequestType;
    /// \brief  Interface base class
    typedef LatencyInterface<T, M> InterfaceBaseType;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    AxiLiteTargetInterface(const std::string& name, const Uid uid, M* module = nullptr);
    /**
     *  \copydoc codasip::resources::Interface::blocking_cb
     */
    void blocking_cb(PayloadType& p) override;
    /**
     *  \copydoc codasip::resources::Interface::transport_cb
     */
    void transport_cb(PayloadType& p, const Phase phase) override;
    /**
     *  \brief  Delay actual write when there is a pending write for one clock cycle.
     *          It simulates FF write delay.
     */
    void clock_cycle();
    /**
     *  \brief  Reset FSM and internal payloads.
     */
    void reset();
    /**
     *  \{
     *  \brief  Properly configure alignment on the internal initiator interface
     *          as well.
     *  \param  value source value to set
     */
    void set_data_alignment(DataAlignment value);
    void set_address_alignment(const codasip_address_t value);
    /**
     *  \} \{
     *  \brief  Initiator public interface is required for memories placed
     *          directly inside of an ASIP (branch predictor).
     *  \param  args arguments passed directly to the internal initiator interface.
     */
    template<class... Args>
    data_type read(Args&&... args);
    template<class... Args>
    data_type dread(Args&&... args);
    template<class... Args>
    void write(Args&&... args);
    template<class... Args>
    void dwrite(Args&&... args);
    template<class... Args>
    void load(Args&&... args);
    template<class... Args>
    void transport(Args&&... args);
    /** \} */
private:
    void phs_address_read(PayloadType&);
    void phs_address_write(PayloadType&);
    void phs_data_read(PayloadType&);
    void phs_data_write(PayloadType&);
    void phs_response_write(PayloadType&);

    // FSMs for requests (two separate channels) to model latency
    RequestType m_ReadRequest;
    RequestType m_WriteRequest;

    // read data and response (must be stored until master is ready)
    PayloadType m_ReadPayload;
    bool m_ReadResponseValid;

    // write request to be performed in the next clock cycle
    PayloadType m_WritePayload;

    // write data cache (write data can appear before the address)
    typename PayloadType::data_type m_WriteDataCache;
    AXIWriteStrobe m_WriteStrobeCache;
    bool m_WriteDataValid;

    // write response
    AXIResponseCode m_WriteResponse;
    bool m_WriteResponseValid;

    /// Master interface for slaves on ASIP component memories
    /// use only basic functionality in the initiator to improve performance
    AxiLiteInitiatorInterface<typename T::PayloadSentinelType, M> m_Initiator;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline AxiLiteTargetInterface<T, M, A>::AxiLiteTargetInterface(const std::string& name,
    const Uid uid,
    M* module)
  : InterfaceBaseType(name, uid, module)
  , m_ReadResponseValid(false)
  , m_WriteStrobeCache(0)
  , m_WriteDataValid(false)
  , m_WriteResponse(CP_AXI_OKAY)
  , m_WriteResponseValid(false)
  ,
  // The initiator can't have pointer to parent module otherwise parent callbacks would be called.
  // Interface routing must be used instead
  m_Initiator(name + "_initiator", uid & (static_cast<Uid>(-1) << (sizeof(Uid) * CHAR_BIT - 1)), nullptr)
{
    // bind internal initiator to this target interface
    m_Initiator.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline typename T::data_type AxiLiteTargetInterface<T, M, A>::read(Args&&... args)
{
    return m_Initiator.read(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline typename T::data_type AxiLiteTargetInterface<T, M, A>::dread(Args&&... args)
{
    return m_Initiator.dread(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiLiteTargetInterface<T, M, A>::write(Args&&... args)
{
    m_Initiator.write(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiLiteTargetInterface<T, M, A>::dwrite(Args&&... args)
{
    m_Initiator.dwrite(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiLiteTargetInterface<T, M, A>::load(Args&&... args)
{
    m_Initiator.load(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiLiteTargetInterface<T, M, A>::transport(Args&&... args)
{
    m_Initiator.transport(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::blocking_cb(PayloadType& p)
{
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("blocking begin:", p);
    if (p.get_axi_valid() == CP_AXI_VALID)
    {
        this->check_payload(p, true, A::IS_READABLE, A::IS_WRITABLE);
        if (!p.is_error())
        {
            InterfaceBaseType::blocking_cb(p);
        }
        // update internal information required by the UVM data verification
        p.set_axi_data_phase();
        p.set_axi_response_phase();
    }
    p.set_axi_ready(CP_AXI_READY);
    T::blocking_d(p);
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("blocking end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::phs_address_read(PayloadType& p)
{
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("read address begin:", p);
    // something in progress
    if (m_ReadRequest.IsBusy())
    {
        p.set_axi_ready(CP_AXI_WAIT);
    }
    // ready, but the address is not valid
    else if (!p.get_axi_valid())
    {
        p.set_axi_ready(CP_AXI_READY);
    }
    // ready and the address is valid
    else
    {
        p.set_axi_ready(CP_AXI_READY);
        if (A::IS_READABLE)
        {   // read/write transfer
            unsigned latency = InterfaceBaseType::get_read_latency();

            m_ReadRequest.AddressPhase(latency, p);
            this->check_payload(p, false, A::IS_READABLE, A::IS_WRITABLE);
            if (!p.is_error())
            {   // no error, pass to the memory to check out-of-range
                InterfaceBaseType::transport_cb(p, CP_PHS_ADDRESS_READ);
            }
            // propagate to request for later checking in clock_cycle
            m_ReadRequest.m_AddressPhasePayload.set_axi_resp(p.get_axi_resp());
        }
        else
        {
            p.set_axi_resp(CP_AXI_SLVERR);

            m_ReadRequest.m_AddressPhasePayload = p;
        }
        InterfaceBaseType::inc_read_latency();
    }
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("read address end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::phs_address_write(PayloadType& p)
{
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("write address begin:", p);
    // something in progress
    if (m_WriteRequest.IsBusy() || m_WriteRequest.m_DataPhasePayload.get_command() != CP_CMD_NONE)
    {
        p.set_axi_ready(CP_AXI_WAIT);
    }
    // ready, but the address is not valid
    else if (!p.get_axi_valid())
    {
        p.set_axi_ready(CP_AXI_READY);
    }
    else
    {
        p.set_axi_ready(CP_AXI_READY);
        if (A::IS_WRITABLE)
        {   // read/write transfer
            unsigned latency = InterfaceBaseType::get_write_latency();
            m_WriteRequest.AddressPhase(latency, p);
            this->check_payload(p, false, A::IS_READABLE, A::IS_WRITABLE);
            if (!p.is_error())
            {   // no error, pass to the memory to check out-of-range
                InterfaceBaseType::transport_cb(p, CP_PHS_ADDRESS_WRITE);
            }
            // propagate to request for later checking in clock_cycle
            m_WriteRequest.m_AddressPhasePayload.set_axi_resp(p.get_axi_resp());
        }
        else
        {
            p.set_axi_ready(CP_AXI_READY);
            p.set_axi_resp(CP_AXI_SLVERR);

            m_WriteRequest.m_AddressPhasePayload = p;
        }
        InterfaceBaseType::inc_write_latency();
    }
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("write address end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::phs_data_read(PayloadType& p)
{
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("read data begin:", p);
    // valid data has been read
    if (m_ReadResponseValid)
    {
        // only drop the data if master has received it (asserting ready)
        if (p.get_axi_ready())
        {
            m_ReadResponseValid = false;
        }

        p = m_ReadPayload;
        p.set_axi_valid(CP_AXI_VALID);
    }
    else
    {
        p.set_axi_valid(CP_AXI_INVALID);
    }
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("read data end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::phs_data_write(PayloadType& p)
{
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("write data begin:", p);
    // suppose data is valid (initiator interface forwards only valid data)
    unsigned latency = InterfaceBaseType::m_Module->GetLatencyWrite(InterfaceBaseType::GetUid());
    // If the data has already been set and hand-shaked, or the latency between address and data
    // hasn't expired, return BUSY.
    // If address hasn't been set yet (IsIdle), latency has to be 0, only then data is allowed
    // before address.
    if (m_WriteDataValid || m_WriteRequest.IsBusy() || (m_WriteRequest.IsIdle() && latency > 0))
    {
        p.set_axi_ready(CP_AXI_WAIT);
    }
    // ready for the data
    else
    {
        p.set_axi_ready(CP_AXI_READY);

        // only write if the provided data is valid
        if (p.get_axi_valid())
        {
            // actual write will be performed during the clock_cycle()
            m_WriteDataCache = p.get_data();
            m_WriteStrobeCache = p.get_axi_wstrb();
            m_WriteDataValid = true;
        }
    }
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("write data end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::phs_response_write(PayloadType& p)
{
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("write response begin:", p);
    if (m_WriteResponseValid)
    {
        // only drop the response when master accepted it (asserting ready)
        if (p.get_axi_ready())
        {
            m_WriteResponseValid = false;
        }

        p.set_axi_resp(m_WriteResponse);
        p.set_axi_valid(CP_AXI_VALID);
    }
    else
    {
        p.set_axi_valid(CP_AXI_INVALID);
    }
    CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT("write response end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::transport_cb(PayloadType& p, const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS_READ:
            phs_address_read(p);
            break;
        case CP_PHS_ADDRESS_WRITE:
            phs_address_write(p);
            break;
        case CP_PHS_DATA_READ:
            phs_data_read(p);
            break;
        case CP_PHS_DATA_WRITE:
            phs_data_write(p);
            break;
        case CP_PHS_RESPONSE_WRITE:
            phs_response_write(p);
            break;
        default:
            break;
    }
    T::transport_d(p, phase);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::clock_cycle()
{
    T::clock_cycle();
    // write the old data
    if (m_WritePayload.get_axi_valid() == CP_AXI_VALID)
    {
        InterfaceBaseType::transport_cb(m_WritePayload, CP_PHS_DATA_WRITE);
    }

    // stall the write (skip clk)
    // store the write data, to perform the slave access in the next clock cycle
    m_WriteRequest.DataPhase(m_WritePayload);
    if (m_WritePayload.get_axi_valid() == CP_AXI_VALID && m_WritePayload.get_axi_ready() == CP_AXI_READY)
    {
        // the write response has not been collected yet, or the data has not been set yet
        // stall the write request
        if (!m_WriteDataValid || m_WriteResponseValid)
        {
            m_WriteRequest.Stall();
        }
        else
        {
            m_WritePayload.set_data(m_WriteDataCache);
            m_WritePayload.set_axi_wstrb(m_WriteStrobeCache);

            // invalidate write data cache
            m_WriteDataValid = false;

            // set write response (OOR has been checked in the address phase)
            m_WriteResponse = m_WritePayload.get_axi_resp();
            m_WriteResponseValid = true;
        }
    }

    m_ReadRequest.clock_cycle();
    m_WriteRequest.clock_cycle();

    // read request has finished - store the data
    // must appear after the clock cycle and before the data_read phase
    if (m_ReadRequest.IsFinished())
    {
        // old data has not been collected yet, the request must be stalled
        if (m_ReadResponseValid)
        {
            m_ReadRequest.Stall();
        }
        else
        {
            // there is a valid request pending
            // finish read transaction
            m_ReadRequest.DataPhase(m_ReadPayload);
            InterfaceBaseType::transport_cb(m_ReadPayload,
                CP_PHS_DATA_READ);   // clear output data if not valid
            m_ReadResponseValid = true;
            if (m_ReadPayload.is_error())
            {
                m_ReadPayload.set_axi_resp(CP_AXI_SLVERR);
            }
        }
    }
    m_Initiator.clock_cycle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiLiteTargetInterface<T, M, A>::reset()
{
    T::reset();
    m_ReadPayload.reset(CP_AXI_READY);
    m_ReadResponseValid = false;
    m_ReadRequest.reset();
    m_WritePayload.reset(CP_AXI_READY);
    m_WriteDataValid = false;
    m_WriteResponseValid = false;
    m_WriteRequest.reset();
    m_Initiator.reset();
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline void AxiLiteTargetInterface<T, M, A>::set_data_alignment(DataAlignment value)
{
    m_Initiator.set_data_alignment(value);
    InterfaceBaseType::set_data_alignment(std::move(value));
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline void AxiLiteTargetInterface<T, M, A>::set_address_alignment(const codasip_address_t value)
{
    m_Initiator.set_address_alignment(value);
    InterfaceBaseType::set_address_alignment(value);
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_AXI_LITE_TARGET_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_AXI_LITE_TARGET_INTERFACE_H_
