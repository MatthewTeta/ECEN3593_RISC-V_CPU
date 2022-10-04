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
 *  \date   27. 11. 2018
 *  \brief  Definition of the class codasip::resources::CpbTargetInterfaceBase and
 *          aliases codasip::resources::CpbTargetInterface and
 *          codasip::resources::CpbLiteTargetInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CPB_TARGET_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CPB_TARGET_INTERFACE_H_

#include "simulator/resources/csr_cpb_initiator_interface.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::CpbTargetInterfaceBase
 *  \brief  Interface that handles Codasip Processor Bus protocol of a memory slave.
 *          The logic of the full and lite version are identical, the only real
 *          difference is the master/initiator class and the transport function
 *          parameters.
 *  \tparam T underlying implementation type
 *  \tparam M parent module contains static functions and compile-time constants
 *          accessing read/write latency
 *  \tparam A contains compile-time constants indicating read/write capability
 *  \tparam I initiator/master interface type
 *  \}
 */
template<class T, class M, class A, class I>
class CpbTargetInterfaceBase : public Interface<T, M>
{
public:
    /// \brief  Import type definitions from the base classes
    using typename T::data_type;
    using typename T::DataAlignment;
    /// \brief  Interface base class
    typedef Interface<T, M> InterfaceBaseType;
    /// \brief  Concrete payload type used by this class
    typedef Payload<data_type> PayloadType;
    /**
     *  \{
     *  \brief Call base class methods - resolve ambiguous call (multiple inheritance)
     */
    using InterfaceBaseType::blocking;
    using InterfaceBaseType::transport;
    /** \} */

    /**
     *  \copydoc Sentinel::Sentinel
     */
    CpbTargetInterfaceBase(const std::string& name, const Uid uid, M* module = nullptr);
    /**
     *  \{
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
    /**
     *  \}
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
    /** \} */
private:
    /// \brief  Local typedef for the master/initiator interface type
    typedef I InitiatorInterfaceType;

    void DoAddressPhase(PayloadType&);
    void DoDataPhase(PayloadType&);

    /// auxiliary payload imported from the parent class for convenience
    using InterfaceBaseType::m_Payload;
    /// valid response/read data register
    CPBValidCode m_Valid;
    /// response for current clock cycle
    CPBResponseCode m_Response;
    /// registered read data by the last read access
    data_type m_RegisteredRData;
    /// Master interface for slaves on ASIP component memories
    InitiatorInterfaceType m_Initiator;
};

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \brief  Template alias definition for the CPB target interface.
 */
template<class T, class M, class A>
using CpbTargetInterface =
    CpbTargetInterfaceBase<T, M, A, CpbInitiatorInterface<typename T::PayloadSentinelType, M>>;

/**
 *  \brief  Template alias definition for the CPB-Lite target interface.
 *  \}
 */
template<class T, class M, class A>
using CpbLiteTargetInterface =
    CpbTargetInterfaceBase<T, M, A, CpbLiteInitiatorInterface<typename T::PayloadSentinelType, M>>;

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
inline CpbTargetInterfaceBase<T, M, A, I>::CpbTargetInterfaceBase(const std::string& name,
    const Uid uid,
    M* module)
  : InterfaceBaseType(name, uid, module)
  , m_Valid(CP_CPB_INVALID)
  , m_Response(CP_CPB_OKAY)
  , m_RegisteredRData(0u)
  ,
  // The initiator can't have pointer to parent module otherwise parent callbacks would be called.
  // Interface routing must be used instead
  m_Initiator(name + "_initiator", uid & (static_cast<Uid>(-1) << (sizeof(Uid) * CHAR_BIT - 1)), nullptr)
{
    m_Payload.reset(CP_CPB_READY);
    // bind internal initiator to this target interface
    m_Initiator.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
template<class... Args>
RES_INLINE typename T::data_type CpbTargetInterfaceBase<T, M, A, I>::read(Args&&... args)
{
    return m_Initiator.read(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
template<class... Args>
inline typename T::data_type CpbTargetInterfaceBase<T, M, A, I>::dread(Args&&... args)
{
    return m_Initiator.dread(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
template<class... Args>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::write(Args&&... args)
{
    m_Initiator.write(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
template<class... Args>
inline void CpbTargetInterfaceBase<T, M, A, I>::dwrite(Args&&... args)
{
    m_Initiator.dwrite(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
template<class... Args>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::load(Args&&... args)
{
    m_Initiator.load(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
template<class... Args>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::transport(Args&&... args)
{
    m_Initiator.transport(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::blocking_cb(PayloadType& p)
{
    if (p.get_cpb_avalid() == CP_CPB_VALID)
    {
        this->check_payload(p, true, A::IS_READABLE, A::IS_WRITABLE);
        if (!p.is_error())
        {
            InterfaceBaseType::blocking_cb(p);
        }
    }
    p.set_cpb_valid(p.get_cpb_avalid());
    p.set_cpb_aready(CP_CPB_READY);
    T::blocking_d(p);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::transport_cb(PayloadType& p, const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            DoAddressPhase(p);
            break;
        case CP_PHS_DATA:
            DoDataPhase(p);
            break;
        default:
            break;
    }
    T::transport_d(p, phase);
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::clock_cycle()
{
    m_Valid = m_Payload.get_cpb_avalid();
    // modify internals only if there is a transaction pending
    if (m_Payload.get_cpb_avalid() == CP_CPB_VALID)
    {
        m_Response = m_Payload.get_cpb_resp();
        if (m_Payload.get_cpb_resp() == CP_CPB_OKAY)
        {   // successful access
            // pass either read or write to the memory/slave
            InterfaceBaseType::transport_cb(m_Payload, CP_PHS_DATA);
            // no need to check the response again,
            // it was fully checked during the address phase
            if (m_Payload.get_cpb_write() == CP_CPB_READ)
            {   // create output register for read data till next read
                m_RegisteredRData = m_Payload.get_data();
            }
        }
        m_Payload.set_cpb_avalid(CP_CPB_INVALID);
    }
    else
    {   // overwrite in case of a previous error
        m_Response = CP_CPB_OKAY;
    }
    InterfaceBaseType::clock_cycle();
    m_Initiator.clock_cycle();
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::reset()
{
    InterfaceBaseType::reset();
    m_Payload.reset(CP_CPB_READY);
    m_Valid = CP_CPB_INVALID;
    m_Response = CP_CPB_OKAY;
    m_RegisteredRData = 0u;
    m_Initiator.reset();
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
inline void CpbTargetInterfaceBase<T, M, A, I>::set_data_alignment(DataAlignment value)
{
    m_Initiator.set_data_alignment(value);
    InterfaceBaseType::set_data_alignment(std::move(value));
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A, class I>
inline void CpbTargetInterfaceBase<T, M, A, I>::set_address_alignment(const codasip_address_t value)
{
    m_Initiator.set_address_alignment(value);
    InterfaceBaseType::set_address_alignment(value);
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  CPB memory supports only latency 1, 1 -> it is always ready. For the
 *          address phase, copy given payload and modify the internal one by
 *          performing the access.
 *  \param  p transaction properties from the master
 */
template<class T, class M, class A, class I>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::DoAddressPhase(PayloadType& p)
{   // CPB memory supports only latency 1, 1 -> it is always ready
    p.set_cpb_aready(CP_CPB_READY);
    // store the payload and modify the internal one
    m_Payload = p;
    // modify the internal payload and return during data phase
    if (m_Payload.get_cpb_avalid() == CP_CPB_VALID)
    {
        this->check_payload(m_Payload, false, A::IS_READABLE, A::IS_WRITABLE);
        if (m_Payload.get_cpb_resp() == CP_CPB_OKAY)
        {
            InterfaceBaseType::transport_cb(m_Payload, CP_PHS_ADDRESS);
        }
    }
}

/**
 *  \brief  CPB memory supports only latency 1, 1 -> it is always ready.
 *  \param  p transaction properties from the master
 */
template<class T, class M, class A, class I>
RES_INLINE void CpbTargetInterfaceBase<T, M, A, I>::DoDataPhase(PayloadType& p)
{
    p.set_cpb_valid(m_Valid);
    p.set_cpb_resp(m_Response);
    if (A::IS_READABLE)
    {   // preserve/register RDATA value similarly to HW until next read is done
        // and the value changes (do not clear the data with zeros)
        p.set_data(m_RegisteredRData);
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CPB_TARGET_INTERFACE_H_
