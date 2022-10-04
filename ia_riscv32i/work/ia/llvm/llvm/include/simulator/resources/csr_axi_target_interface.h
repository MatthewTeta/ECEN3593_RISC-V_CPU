/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2020 Codasip s.r.o.
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
 *  \author Karel Vorechovsky
 *  \date   11-8-2020
 *  \brief  Definition of the class codasip::resources::AxiTargetInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_TARGET_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_AXI_TARGET_INTERFACE_H_

#include "simulator/resources/csr_axi_initiator_interface.h"
#include "simulator/resources/csr_axi_request.h"
#include "simulator/resources/csr_latency_interface.h"
#include "simulator/resources/detail/csr_axi_burst_info.h"

// #define CODASIP_AXI_TARGET_DBG_OUT
#ifdef CODASIP_AXI_TARGET_DBG_OUT
#    define CODASIP_AXI_TARGET_DBG_OUT_PRINT(cmd, p)                                           \
        std::cout << __FILE__ << ":" << __LINE__ << ": " << this->get_signature() << ": AXI4 " \
                  << cmd << " " << p.PrintAxi() << std::endl
#else
#    define CODASIP_AXI_TARGET_DBG_OUT_PRINT(cmd, p) UNUSED(p)
#endif

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  AxiTargetInterface
 *  \brief  Interface that handles AXI4 protocol of a memory slave.
 *  \tparam T underlying implementation data type
 *  \tparam M memory module type
 *  \tparam A contains compile-time constants indicating read/write capability
 *  \}
 */
template<class T, class M, class A>
class AxiTargetInterface : public LatencyInterface<T, M>
{
public:
    /// Underying data type
    using typename T::data_type;
    /// Underlying parameter data type
    using typename T::DataAlignment;

    /// Payload type
    typedef Payload<typename T::data_type> PayloadType;
    /// FSM request class
    typedef AxiRequest<typename T::data_type> RequestType;
    /// Interface base class
    typedef LatencyInterface<T, M> InterfaceBaseType;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    AxiTargetInterface(const std::string& name, const Uid uid, M* module = nullptr);
    /**
     *  \copydoc codasip::resources::Interface::blocking_cb
     */
    void blocking_cb(PayloadType& payload) override;
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
     *  \}
     */

    /**
     * \{
     *  \brief  Initiator public interface is required for memories placed
     *          directly inside of an ASIP (branch predictor).
     *  \param  args arguments passed directly to the internal initiator interface.
     */
    template<class... Args>
    typename T::data_type read(Args&&... args);
    template<class... Args>
    typename T::data_type dread(Args&&... args);
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
    void PhsAddressRead(PayloadType&);
    void PhsAddressWrite(PayloadType&);
    void PhsDataRead(PayloadType&);
    void PhsDataWrite(PayloadType&);
    void PhsResponseWrite(PayloadType&);

    void BeginWriteTransfer();

    /// Information about current burst on blocking access
    detail::AxiBurstInfo<PayloadType> m_IABurstInfo;
    /// Information about current burst on read channels
    detail::AxiBurstInfo<PayloadType> m_ReadBurstInfo;
    /// Information about current burst on write channels
    detail::AxiBurstInfo<PayloadType> m_WriteBurstInfo;

    /// Transaction request on read channels
    RequestType m_ReadRequest;
    /// Transaction payload containing address and control signals for current read burst
    PayloadType m_ReadPayload;
    /// True if the read was performed in the memory and is waiting on master to clame the results
    bool m_ReadResponseValid = false;

    /// Transaction request on write channels
    RequestType m_WriteRequest;
    /// Transaction payload containing address and control signals for current write burst
    PayloadType m_WriteAddressPayload;
    /// Transaction payload containing data signals for current write burst
    PayloadType m_WriteDataPayload;
    /// True if the write response is valid and can be claimed by the master
    bool m_WriteResponseValid = false;
    /// Value of resp signal in the write response
    AXIResponseCode m_WriteResponse = CP_AXI_OKAY;
    /// True if last transfer in a write burst is detected (needed to determine, when the write response should be valid)
    bool m_LastTransfer = false;
    /// True if write address was performed and waiting for first data phase
    bool m_WriteFirstDataInBurst = false;

    /// Master interface for slaves on ASIP component memories
    AxiInitiatorInterface<typename T::PayloadSentinelType, M> m_Initiator;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline AxiTargetInterface<T, M, A>::AxiTargetInterface(const std::string& name, const Uid uid, M* module)
  : InterfaceBaseType(name, uid, module)
  , m_Initiator(name + "_initiator", uid & (static_cast<Uid>(-1) << (sizeof(Uid) * CHAR_BIT - 1)), nullptr)
{
    // bind internal initiator to this target interface
    m_Initiator.bind(*this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline typename T::data_type AxiTargetInterface<T, M, A>::read(Args&&... args)
{
    return m_Initiator.read(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline typename T::data_type AxiTargetInterface<T, M, A>::dread(Args&&... args)
{
    return m_Initiator.dread(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiTargetInterface<T, M, A>::write(Args&&... args)
{
    m_Initiator.write(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiTargetInterface<T, M, A>::dwrite(Args&&... args)
{
    m_Initiator.dwrite(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiTargetInterface<T, M, A>::load(Args&&... args)
{
    m_Initiator.load(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
template<class... Args>
inline void AxiTargetInterface<T, M, A>::transport(Args&&... args)
{
    m_Initiator.transport(std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
RES_INLINE void AxiTargetInterface<T, M, A>::blocking_cb(PayloadType& payload)
{
    CODASIP_AXI_TARGET_DBG_OUT_PRINT("blocking begin:", payload);

    // perform only valid operations
    if (payload.get_axi_valid() == CP_AXI_VALID)
    {
        // check payload for obvious errors and continue only if no error was found
        this->check_payload(payload, true, A::IS_READABLE, A::IS_WRITABLE);
        if (!payload.is_error())
        {
            // first transaction in the burst
            if (m_IABurstInfo.GetBeatCounter() == 0)
            {
                m_IABurstInfo.Initialize(payload);
            }

            // Update burst payload for next transaction
            m_IABurstInfo.Update(payload);
            m_IABurstInfo.IncrementBeatCounter();

            // send transaction to underlying module
            InterfaceBaseType::blocking_cb(payload);

            // check if current transaction is the last one in a burst
            if (m_IABurstInfo.GetBurstLen() == m_IABurstInfo.GetBeatCounter())
            {
                // reset burst beat counter
                m_IABurstInfo.ResetBeatCounter();

                // set the response phase into the payload (needed only for UVM verification)
                const auto command = payload.get_command();
                if (command == CP_CMD_WRITE || command == CP_CMD_DWRITE || command == CP_CMD_LOAD)
                {
                    payload.set_axi_response_phase();
                }
                // Set last signal for read transactions
                else   // (command == CP_CMD_DREAD || command == CP_CMD_READ)
                {
                    payload.set_axi_last(CP_AXI_LAST);
                }
            }
        }
    }

    // set result
    payload.set_axi_ready(CP_AXI_READY);
    T::blocking_d(payload);

    CODASIP_AXI_TARGET_DBG_OUT_PRINT("blocking end:", payload);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::PhsAddressRead(PayloadType& payload)
{
    CODASIP_AXI_TARGET_DBG_OUT_PRINT("read address begin:", payload);

    // something in progress
    if (m_ReadRequest.IsBusy())
    {
        payload.set_axi_ready(CP_AXI_WAIT);
    }

    // ready, but the address is not valid
    else if (!payload.get_axi_valid())
    {
        payload.set_axi_ready(CP_AXI_READY);
    }

    // ready and the address is valid
    else
    {
        payload.set_axi_ready(CP_AXI_READY);

        // get next latency
        const auto latency = InterfaceBaseType::get_read_latency();
        InterfaceBaseType::inc_read_latency();

        // store burst information
        m_ReadBurstInfo.Initialize(payload);

        // Check payload and perform transport on underlying module
        this->check_payload(payload, false, A::IS_READABLE, A::IS_WRITABLE);
        if (!payload.is_error())
        {
            InterfaceBaseType::transport_cb(payload, CP_PHS_ADDRESS_READ);
        }

        // Start read request FSM (simulation latency)
        m_ReadRequest.AddressPhase(latency, payload);
    }

    CODASIP_AXI_TARGET_DBG_OUT_PRINT("read address end:", payload);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::PhsAddressWrite(PayloadType& payload)
{
    CODASIP_AXI_TARGET_DBG_OUT_PRINT("write address begin:", payload);

    // something in progress
    if (m_WriteRequest.IsBusy() || m_WriteAddressPayload.get_command() != CP_CMD_NONE ||
        m_WriteResponseValid)
    {
        payload.set_axi_ready(CP_AXI_WAIT);
    }

    // ready
    else
    {
        payload.set_axi_ready(CP_AXI_READY);

        // valid transaction
        if (payload.get_axi_valid())
        {
            // Check payload and perform transport on underlying module
            this->check_payload(payload, false, A::IS_READABLE, A::IS_WRITABLE);
            if (!payload.is_error())
            {
                InterfaceBaseType::transport_cb(payload, CP_PHS_ADDRESS_WRITE);
            }

            // store the address payload
            m_WriteAddressPayload = payload;
            m_WriteBurstInfo.Initialize(m_WriteAddressPayload);

            // initialize transfer if data payload is already present
            // otherwise the transfer will be initialized when the data is received
            if (m_WriteDataPayload.get_command() != CP_CMD_NONE)
            {
                m_WriteFirstDataInBurst = false;
                BeginWriteTransfer();
            }
            else
            {
                m_WriteFirstDataInBurst = true;
            }
        }
    }

    CODASIP_AXI_TARGET_DBG_OUT_PRINT("write address end:", payload);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::PhsDataRead(PayloadType& payload)
{
    CODASIP_AXI_TARGET_DBG_OUT_PRINT("read data begin:", payload);

    // valid data has been read
    if (m_ReadResponseValid)
    {
        // only drop the data if master can received it (asserting ready)
        const bool ready = payload.get_axi_ready() == CP_AXI_READY;

        // Restore info from stored payload from address phase
        payload = m_ReadPayload;
        payload.set_axi_valid(CP_AXI_VALID);

        // Check for the last data in the burst
        if (m_ReadBurstInfo.GetBurstLen() - 1 == m_ReadBurstInfo.GetBeatCounter())
        {
            payload.set_axi_last(CP_AXI_LAST);
            m_ReadBurstInfo.ResetBeatCounter();
        }

        // If further data must be read in this burst, update the burst info and perform annother request
        else if (ready)
        {
            m_ReadBurstInfo.IncrementBeatCounter();
            m_ReadBurstInfo.Update(m_ReadPayload);
            const auto latency = InterfaceBaseType::get_read_latency();
            InterfaceBaseType::inc_read_latency();
            m_ReadRequest.AddressPhase(latency, m_ReadPayload);
        }

        // data were already processed, so they are no longer valid
        if (ready)
        {
            m_ReadResponseValid = false;
        }
    }
    // data not ready yet
    else
    {
        payload.set_axi_valid(CP_AXI_INVALID);
    }

    CODASIP_AXI_TARGET_DBG_OUT_PRINT("read data end:", payload);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::PhsDataWrite(PayloadType& payload)
{
    CODASIP_AXI_TARGET_DBG_OUT_PRINT("write data begin:", payload);

    // busy, either burst in progress or the response was not yet received or
    // one data payload is already buffered in the burst without address
    if (m_WriteRequest.IsBusy() || m_WriteResponseValid ||
        m_WriteDataPayload.get_command() != CP_CMD_NONE)
    {
        payload.set_axi_ready(CP_AXI_WAIT);
    }

    // ready for the data
    else
    {
        payload.set_axi_ready(CP_AXI_READY);

        // only write if the provided data is valid
        if (payload.get_axi_valid())
        {
            // store the payload for further use
            m_WriteDataPayload = payload;

            // Check if the address phase was already performed
            if (m_WriteAddressPayload.get_command() != CP_CMD_NONE)
            {
                // don't update burst info on first burst, it was already initialized by the address phase
                if (m_WriteFirstDataInBurst)
                {
                    m_WriteFirstDataInBurst = false;
                }
                // continue burst, update burst info
                else
                {
                    m_WriteBurstInfo.IncrementBeatCounter();
                    m_WriteBurstInfo.Update(m_WriteAddressPayload);
                }

                // perform the transaction
                BeginWriteTransfer();
            }

            // Update info if this is the last transaction in the burst
            if (payload.get_axi_last() == CP_AXI_LAST)
            {
                m_WriteBurstInfo.ResetBeatCounter();
                m_LastTransfer = true;
            }
        }
    }

    CODASIP_AXI_TARGET_DBG_OUT_PRINT("write data end:", payload);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::PhsResponseWrite(PayloadType& payload)
{
    CODASIP_AXI_TARGET_DBG_OUT_PRINT("write response begin:", payload);

    // valid response
    if (m_WriteResponseValid)
    {
        // send valid response to the master
        payload.set_axi_resp(m_WriteResponse);
        payload.set_axi_valid(CP_AXI_VALID);
        payload.set_axi_id(m_WriteAddressPayload.get_axi_id());

        // only drop the response when master accepted it (asserting ready)
        if (payload.get_axi_ready())
        {
            m_WriteResponseValid = false;
            m_WriteAddressPayload.reset();
        }
    }

    // invalid response
    else
    {
        payload.set_axi_valid(CP_AXI_INVALID);
    }

    CODASIP_AXI_TARGET_DBG_OUT_PRINT("write response end:", payload);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::transport_cb(PayloadType& payload, const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS_READ:
            PhsAddressRead(payload);
            break;
        case CP_PHS_ADDRESS_WRITE:
            PhsAddressWrite(payload);
            break;
        case CP_PHS_DATA_READ:
            PhsDataRead(payload);
            break;
        case CP_PHS_DATA_WRITE:
            PhsDataWrite(payload);
            break;
        case CP_PHS_RESPONSE_WRITE:
            PhsResponseWrite(payload);
            break;
        default:
            break;
    }
    T::transport_d(payload, phase);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::clock_cycle()
{
    T::clock_cycle();

    // handle requests
    m_ReadRequest.clock_cycle();
    m_WriteRequest.clock_cycle();

    // read has higher priority than write (if accessing the same address)
    // so the read access has to be performed first

    // read request has finished
    if (m_ReadRequest.IsFinished())
    {
        // old data has not been collected yet, the request must be stalled
        if (m_ReadResponseValid)
        {
            m_ReadRequest.Stall();
        }

        // no old data in the buffer, the transaction can be send into the underlying module
        else
        {
            m_ReadRequest.DataPhase(m_ReadPayload);
            if (!m_ReadPayload.is_error())
            {
                InterfaceBaseType::transport_cb(m_ReadPayload, CP_PHS_DATA_READ);
            }
            m_ReadResponseValid = true;
        }
    }

    // write request has finished
    if (m_WriteRequest.IsFinished())
    {
        // send the write transaction into the underlying module
        PayloadType writePayload;
        m_WriteRequest.DataPhase(writePayload);
        if (!writePayload.is_error())
        {
            InterfaceBaseType::transport_cb(writePayload, CP_PHS_DATA_WRITE);
        }

        // move to response phase if this was the last transaction in the burst
        if (m_LastTransfer)
        {
            m_LastTransfer = false;
            m_WriteResponseValid = true;
            m_WriteResponse = writePayload.get_axi_resp();
        }
    }

    m_Initiator.clock_cycle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::reset()
{
    T::reset();

    m_ReadPayload.reset(CP_AXI_READY);
    m_ReadResponseValid = false;
    m_ReadRequest.reset();

    m_WriteAddressPayload.reset(CP_AXI_READY);
    m_WriteDataPayload.reset(CP_AXI_READY);
    m_WriteRequest.reset();
    m_WriteResponseValid = false;
    m_WriteResponse = CP_AXI_OKAY;
    m_WriteFirstDataInBurst = false;
    m_LastTransfer = false;

    m_IABurstInfo.Reset();
    m_ReadBurstInfo.Reset();
    m_WriteBurstInfo.Reset();

    m_Initiator.reset();
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline void AxiTargetInterface<T, M, A>::set_data_alignment(DataAlignment value)
{
    m_Initiator.set_data_alignment(value);
    InterfaceBaseType::set_data_alignment(std::move(value));
}

////////////////////////////////////////////////////////////////////////////////
template<class T, class M, class A>
inline void AxiTargetInterface<T, M, A>::set_address_alignment(const codasip_address_t value)
{
    m_Initiator.set_address_alignment(value);
    InterfaceBaseType::set_address_alignment(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief begins write transaction when both address and data are ready to use
 */
template<class T, class M, class A>
void RES_INLINE AxiTargetInterface<T, M, A>::BeginWriteTransfer()
{
    // Check that last transaction of write burst has the last signal correctly set
    if (m_WriteDataPayload.get_axi_last() == CP_AXI_NOT_LAST &&
        m_WriteBurstInfo.GetBurstLen() - 1 == m_WriteBurstInfo.GetBeatCounter())
    {
        LOG(this->get_log(), simulator::LOG_TYPE_ERROR, 0)
            << "'" << this->get_signature()
            << "': Last transaction of write burst has not asserted the WLAST signal";
        // protocol is broken at this point, so there is no use moving on with the simulation
        this->DoAbortSimulation();
    }

    // Combine address and data payloads
    m_WriteAddressPayload.set_data(m_WriteDataPayload.get_data());
    m_WriteAddressPayload.set_axi_wstrb(m_WriteDataPayload.get_axi_wstrb());

    // Data payload is no longer needed
    m_WriteDataPayload.reset();

    // get next latency
    const auto latency = InterfaceBaseType::get_write_latency();
    InterfaceBaseType::inc_write_latency();

    // start write request (simulating latency)
    m_WriteRequest.AddressPhase(latency, m_WriteAddressPayload);
}

}   // namespace resources
}   // namespace codasip

#undef CODASIP_AXI_TARGET_DBG_OUT_PRINT

#endif   // SIMULATOR_RESOURCES_CSR_AXI_TARGET_INTERFACE_H_
