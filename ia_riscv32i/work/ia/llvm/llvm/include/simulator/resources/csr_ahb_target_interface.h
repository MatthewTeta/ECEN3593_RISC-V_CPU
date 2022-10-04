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
 *  \date   Aug 8, 2017
 *  \brief  Definition of the class codasip::resources::AhbLiteTargetInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AHB_TARGET_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_AHB_TARGET_INTERFACE_H_

#include "simulator/resources/csr_ahb_initiator_interface.h"
#include "simulator/resources/csr_ahb_request.h"
#include "simulator/resources/csr_target_interface.h"

//#define CODASIP_AHB_TARGET_DBG_OUT
#ifdef CODASIP_AHB_TARGET_DBG_OUT
#    define CODASIP_AHB_TARGET_DBG_OUT_PRINT(cmd, p)                                          \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() << ": AHB " \
                  << cmd << " " << p.PrintAhbLite() << std::endl
#else
#    define CODASIP_AHB_TARGET_DBG_OUT_PRINT(cmd, p)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  AhbLiteTargetInterface
 *  \brief  Interface that handles AMBA 3 AHB-Lite protocol of a memory slave.
 *  \tparam T underlying implementation type
 *  \tparam M parent module contains static functions and compile-time constants
 *          accessing read/write latency
 *  \tparam A contains compile-time constants indicating read/write capability
 *  \}
 */
template<class T, class M, class A>
class AhbLiteTargetInterface : public TargetInterface<T, M, A, AhbLiteRequest<typename T::data_type>>
{
public:
    /// \brief  Import type definitions from the base classes
    using typename T::data_type;
    using typename T::DataAlignment;
    /// \brief  Concrete payload type used by this class
    typedef Payload<data_type> PayloadType;
    /// \brief  Request handler class
    typedef AhbLiteRequest<data_type> RequestBaseType;
    /// \brief  Interface base class
    typedef TargetInterface<T, M, A, RequestBaseType> InterfaceBaseType;

    /**
     * \{
     * \brief Call Interface<T, M> methods - resolve ambiguous call (multiple inheritance)
     */
    using InterfaceBaseType::blocking;
    using InterfaceBaseType::transport;
    /** \} */

    /**
     *  \copydoc Sentinel::Sentinel
     */
    AhbLiteTargetInterface(const std::string& name, const Uid uid, M* module = nullptr);
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
protected:
    void do_request(PayloadType&);
    void do_response(PayloadType&);

private:
    /// import payload from the parent class for convenience
    using InterfaceBaseType::m_Payload;
    /// Master interface for slaves on ASIP component memories
    /// use only basic functionality in the initiator to improve performance
    AhbLiteInitiatorInterface<typename T::PayloadSentinelType, M> m_Initiator;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline AhbLiteTargetInterface<T, M, A>::AhbLiteTargetInterface(const std::string& name,
    const Uid uid,
    M* module)
  : InterfaceBaseType(name, uid, module)
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
inline typename T::data_type AhbLiteTargetInterface<T, M, A>::read(Args&&... args)
{
    return m_Initiator.read(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline typename T::data_type AhbLiteTargetInterface<T, M, A>::dread(Args&&... args)
{
    return m_Initiator.dread(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AhbLiteTargetInterface<T, M, A>::write(Args&&... args)
{
    m_Initiator.write(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AhbLiteTargetInterface<T, M, A>::dwrite(Args&&... args)
{
    m_Initiator.dwrite(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AhbLiteTargetInterface<T, M, A>::load(Args&&... args)
{
    m_Initiator.load(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AhbLiteTargetInterface<T, M, A>::transport(Args&&... args)
{
    m_Initiator.transport(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AhbLiteTargetInterface<T, M, A>::blocking_cb(PayloadType& p)
{
    if (p.is_ahb_active_transfer())
    {
        this->check_payload(p, true, A::IS_READABLE, A::IS_WRITABLE);
        if (!p.is_error())
        {
            InterfaceBaseType::blocking_cb(p);
            if ((p.get_command() == CP_CMD_READ || p.get_command() == CP_CMD_DREAD) &&
                this->has_pending_wr_request_to_handle())
            {   // check whether there are data that are about to be written but are not written yet
                const auto& pendingRequest = this->get_pending_wr_request_to_handle();
                if (p.get_address() >= pendingRequest.get_address() &&
                    p.get_address() < pendingRequest.get_address() + pendingRequest.get_bc())
                {
                    p.set_data(pendingRequest.get_data());
                }
            }
        }
    }
    p.set_ahb_hready(CP_AHB_READY);
    T::blocking_d(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AhbLiteTargetInterface<T, M, A>::do_request(PayloadType& p)
{
    CODASIP_AHB_TARGET_DBG_OUT_PRINT("address phase begin:", p);
    // something in the progress
    if (RequestBaseType::IsBusy())
    {
        p.set_ahb_hready(CP_AHB_WAIT);
    }
    else if (p.is_ahb_active_transfer())
    {
        InterfaceBaseType::set_pending_rd_request(false);
        // read/write transfer
        unsigned latency;
        if (p.get_ahb_hwrite() == CP_AHB_READ)
        {
            latency = InterfaceBaseType::get_read_latency();
            InterfaceBaseType::set_pending_rd_request_latency(latency);
        }
        else
        {
            latency = InterfaceBaseType::get_write_latency();
        }
        RequestBaseType::AddressPhase(latency, p);
        this->check_payload(p, false, A::IS_READABLE, A::IS_WRITABLE);
        if (!p.is_error())
        {   // no error, pass to the memory to check out-of-range
            InterfaceBaseType::transport_cb(p, CP_PHS_ADDRESS);
        }
        // propagate to request for later checking in clock_cycle
        RequestBaseType::m_AddressPhasePayload.set_ahb_hresp(p.get_ahb_hresp());
        if (p.is_error())
        {   // unsupported transfer type (read-only, write-only) or invalid properties
            // two-cycle error response
            RequestBaseType::Error(2);
            InterfaceBaseType::set_pending_rd_request_latency(0);
        }
        else if (p.get_ahb_hwrite() == CP_AHB_READ)
        {   // valid read transaction
            InterfaceBaseType::set_pending_rd_request(true);
            InterfaceBaseType::inc_read_latency();
        }
        else
        {   // valid write transaction
            InterfaceBaseType::inc_write_latency();
        }
        p.set_ahb_hready(CP_AHB_READY);
    }
    else
    {
        // waiting state inserted by master
        if (p.get_ahb_htrans() == CP_AHB_BUSY)
        {
            // wait for one cycle
            RequestFSM::Request(1);
        }
        p.set_ahb_hready(CP_AHB_READY);
    }
    CODASIP_AHB_TARGET_DBG_OUT_PRINT("address phase end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AhbLiteTargetInterface<T, M, A>::do_response(PayloadType& p)
{
    CODASIP_AHB_TARGET_DBG_OUT_PRINT("data phase begin:", p);
    // data to be written (if write request)
    const auto data = p.get_data();
    RequestBaseType::DataPhase(p);
    CODASIP_AHB_TARGET_DBG_OUT_PRINT("data phase restored:", p);

    bool clear_output = true;
    // ready to proceed, but not handling IDLE or BUSY commands
    if ((p.get_ahb_hready() == CP_AHB_READY) && (p.get_ahb_hresp() == CP_AHB_OKAY) &&
        p.is_ahb_active_transfer())
    {   // there is a valid request pending
        clear_output = false;
        if (p.get_ahb_hwrite() == CP_AHB_READ)
        {   // finish read transaction
            InterfaceBaseType::transport_cb(p, CP_PHS_DATA);
        }
        else
        {   // finish write transaction
            // actual write will be performed during the clock_cycle()
            p.set_data(data);
            InterfaceBaseType::set_pending_wr_request(p);
        }
    }
    // clear output data if not valid
    if (clear_output)
    {
        p.set_data(0);
    }
    CODASIP_AHB_TARGET_DBG_OUT_PRINT("data phase end:", p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AhbLiteTargetInterface<T, M, A>::transport_cb(PayloadType& p, const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            do_request(p);
            break;
        case CP_PHS_DATA:
            do_response(p);
            break;
        default:
            break;
    }
    T::transport_d(p, phase);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AhbLiteTargetInterface<T, M, A>::clock_cycle()
{
    T::clock_cycle();
    InterfaceBaseType::clock_cycle(CP_AHB_READY, CP_PHS_DATA);
    m_Initiator.clock_cycle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AhbLiteTargetInterface<T, M, A>::reset()
{
    T::reset();
    InterfaceBaseType::reset(CP_AHB_READY);
    m_Initiator.reset();
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline void AhbLiteTargetInterface<T, M, A>::set_data_alignment(DataAlignment value)
{
    m_Initiator.set_data_alignment(value);
    InterfaceBaseType::set_data_alignment(std::move(value));
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline void AhbLiteTargetInterface<T, M, A>::set_address_alignment(const codasip_address_t value)
{
    m_Initiator.set_address_alignment(value);
    InterfaceBaseType::set_address_alignment(value);
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_AHB_TARGET_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_AHB_TARGET_INTERFACE_H_
