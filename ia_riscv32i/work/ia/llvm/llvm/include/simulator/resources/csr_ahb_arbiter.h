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
 *  \author Dobias Roman, Kamil Michl
 *  \date   19. 8. 2019
 *  \brief  Definition of the class codasip::resources::AhbLiteArbiter.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AHB_ARBITER_H_
#define SIMULATOR_RESOURCES_CSR_AHB_ARBITER_H_

#include "simulator/resources/csr_arbiter_payload.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/simbase/simulator_resources.h"

namespace codasip {
namespace resources {
namespace details {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::details::TransactionStatus
 *  \brief  Hold status of transaction in progress
 *  \}
 */
class TransactionStatus
{
public:
    /**
     *  \brief  Determines if current transaction is CP_AHB_INCR (burst of undefined length)
     */
    bool IsAhbINCR() const;
    /**
     *  \brief  Decides whether current AHB transaction is complete/done
     *  \param  trans Transfer type of the transaction
     */
    bool IsTransactionComplete(const AHBTransferType trans) const;
    /**
     *  \brief  Initialize new transaction
     *  \param  burstType type of transaction transfer
     */
    void StartTransaction(const AHBBurstMode burstType);
    /**
     *  \brief  Called when slave sets CP_AHB_READY in HREADY signal
     */
    void SuccessfulTick();
    /**
     *  \brief  Called when master sets CP_AHB_BUSY in HTRANS signal
     */
    void BusyClock();
    /**
     *  \brief  Updates transaction status
     */
    void ClockCycle();
    /**
     *  \brief  Sets default values
     */
    void Reset();

private:
    /// Is it burst or single clock-cycle transaction ?
    bool m_IsBurst = false;
    /// Determines if burst beat counter was increased this clock cycle
    bool m_IsBurstBeat = false;
    /// Is burst transaction fixed or undefined length
    bool m_IsUndefinedLengthBurst = false;
    /// Count of beats per transaction. Equals 0 when SINGLE.
    uint16_t m_ExpectedBurstBeats = 0;
    /// Count of already passed beats. Incremented when slave's HREADY = 1
    uint16_t m_PassedBurstBeats = 0;
};

}   // namespace details

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class codasip::resources::AhbLiteArbiter
 *  \brief Arbiters N masters on a single AHB slave
 *
 *  The process of arbitration is managed by generated ArbiterCore class,
 *  which must provide methods described below.
 *  Moreover, a callback to AhbLiteArbiter must be registered at
 *  mirrored master interfaces in order to process incoming transactions
 *  by the arbiter. Maximum number of supported input interface is 8.
 *
 *  \see unittests/simulator/resources/ahb_arbiter_core.h for an example of ArbiterCore
 *
 *  ArbiterCore must support following methods:
 *  \li ArbiterCore (const std::string& name, const Uid uid, Arbiter* ptr) -> Instantiation of internal interfaces
 *  \li GetInputInterfaceCount ()                -> Get number of input interfaces
 *  \li GetOutputInterface ()                    -> Reference to output interface
 *  \li GetInputInterfaceByIndex (uint8_t index) -> Reference to input interface with given index
 *  \li GetInputInterfaceIndexFromUid (Uid uid)  -> Transfer input interface uid to it's index
 *  \}
 */
template<typename ArbiterCore>
class AhbLiteArbiter : public Sentinel, public simulator::ArbiterInfo, public ArbiterCore
{
public:
    /// Type for arbiter core
    typedef ArbiterCore CoreType;
    /// Underlying data type
    using data_type = typename CoreType::DataType;
    /// Type for underlying payload
    typedef Payload<data_type> payload_type;

    /**
     *  \brief  Arbiter constructor
     *  \param  name Name of the component
     *  \param  uid UID of the component
     */
    AhbLiteArbiter(const std::string& name, const Uid uid);
    /**
     *  \brief  Reset of the arbiter and all its interfaces
     */
    void reset();
    /**
     *  \brief  Forward address payloads to slave and updates state.
     *          In the beginning, determine what's the status of pending transaction,
     *          and if we should proceed to the next one. Then prepare address phase for slave.
     */
    void clock_cycle();
    /**
     *  \brief  Forwards data payloads
     *  \param  p Payload to be forwarded
     *  \param  uid UID of the input interface that send the transaction
     */
    void blocking_cb(payload_type& p, const Uid uid);
    /**
     *  \brief  Forwards data payloads and stores address payloads.
     *          Handle transport requests from master's. In DATA phase, forward
     *          selected interface. In ADDRESS phase, store request if input
     *          buffer is empty.
     *  \param  p Payload to be forwarded/stored
     *  \param  phase Phase of the transaction.
     *  \param  id UID of the input interface that send the transaction
     */
    void transport_cb(payload_type& p, const Phase phase, const Uid uid);

private:
    static constexpr uint8_t UNKNOWN_INDEX = 255u;

    uint8_t FindPriorityTransaction();

    /// ID of currently selected input interface
    uint8_t m_SelectedId = 0;
    /// Stores result of slave's HREADY in current clock
    bool m_IsSlaveReady = true;
    /// Stores result of slave's HRESP in current clock
    bool m_IsError = false;
    /// Stores previous value of HMASTLOCK signal
    bool m_MastLock = false;
    /// Determines if current transaction is terminating, and how long it should last
    details::TransactionStatus m_TransactionStatus;
    /// Storage for address phase payloads on each interface
    std::array<detail::AhbLiteArbiterStoredPayload<data_type>, CoreType::IFACE_COUNT> m_Payloads;
    /// ID of input interface selected for next transaction
    uint8_t m_NewTransactionIndex = UNKNOWN_INDEX;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool details::TransactionStatus::IsAhbINCR() const
{
    return m_IsUndefinedLengthBurst;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool details::TransactionStatus::IsTransactionComplete(const AHBTransferType trans) const
{
    if (!m_IsBurst)
    {
        // SINGLE-mode transaction always last a single beat
        return true;
    }
    if (m_IsUndefinedLengthBurst)
    {
        // length of undefined length burst can not be predicted
        // Must use current HTRANS value to determine the end
        return (trans == CP_AHB_NONSEQ || trans == CP_AHB_IDLE);
    }
    if (m_PassedBurstBeats >= m_ExpectedBurstBeats)
    {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void details::TransactionStatus::SuccessfulTick()
{
    if (m_IsBurst && !m_IsUndefinedLengthBurst)
    {
        m_PassedBurstBeats++;
        m_IsBurstBeat = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void details::TransactionStatus::StartTransaction(const AHBBurstMode burstType)
{
    // Reset values from old transaction
    Reset();

    // Set new transaction values according to burst type
    m_IsBurst = burstType != CP_AHB_SINGLE;
    switch (burstType)
    {
        case CP_AHB_INCR4:
        case CP_AHB_WRAP4:
            m_ExpectedBurstBeats = 4;
            break;
        case CP_AHB_INCR8:
        case CP_AHB_WRAP8:
            m_ExpectedBurstBeats = 8;
            break;
        case CP_AHB_INCR16:
        case CP_AHB_WRAP16:
            m_ExpectedBurstBeats = 16;
            break;
        case CP_AHB_INCR:   // Burst of undefined size
            m_IsUndefinedLengthBurst = true;
            m_ExpectedBurstBeats = 0;
            break;
        case CP_AHB_SINGLE:   // Single transaction burst
            m_ExpectedBurstBeats = 0;
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void details::TransactionStatus::BusyClock()
{
    if (m_IsBurst && m_IsBurstBeat)
    {
        // Restore previous count of beats
        m_PassedBurstBeats--;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void details::TransactionStatus::ClockCycle()
{
    m_IsBurstBeat = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void details::TransactionStatus::Reset()
{
    m_IsBurst = false;
    m_IsBurstBeat = false;
    m_IsUndefinedLengthBurst = false;
    m_ExpectedBurstBeats = 0;
    m_PassedBurstBeats = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline AhbLiteArbiter<T>::AhbLiteArbiter(const std::string& name, const Uid uid)
  : Sentinel(name, uid)
  , simulator::ArbiterInfo(name, uid)
  , CoreType(name, static_cast<AhbLiteArbiter*>(this))
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void AhbLiteArbiter<T>::reset()
{
    // Reset input interfaces and stored payloads
    for (uint8_t i = 0; i < CoreType::IFACE_COUNT; i++)
    {
        CoreType::GetInputInterfaceByIndex(i).reset();
        m_Payloads[i].Clear();
    }

    // Reset output interface
    CoreType::GetOutputInterface().reset();

    // Reset internal state
    m_SelectedId = 0;
    m_IsSlaveReady = true;
    m_IsError = false;
    m_MastLock = false;
    m_NewTransactionIndex = UNKNOWN_INDEX;
    m_TransactionStatus.Reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void AhbLiteArbiter<T>::clock_cycle()
{
    // Get information about currently selected interface
    auto id = m_SelectedId;
    const auto trans = m_Payloads.at(id).GetPayload().get_ahb_htrans();
    const auto currentMastLock = m_Payloads.at(id).GetPayload().get_ahb_hmastlock();

    bool interfaceSwitch = false;
    if (m_IsSlaveReady)
    {
        // if slave acknowledged previous clock cycle request
        m_TransactionStatus.SuccessfulTick();
        interfaceSwitch = m_TransactionStatus.IsTransactionComplete(trans) &&
            !(m_MastLock && currentMastLock);

        if (interfaceSwitch)
        {
            // switch to next interface when transaction is done
            m_SelectedId = FindPriorityTransaction();
            interfaceSwitch = true;
            // Reset new transaction index, must be determined in next cycle
            m_NewTransactionIndex = UNKNOWN_INDEX;
        }
    }

    bool shouldClearStoredPayload = true;
    id = m_SelectedId;
    if ((!interfaceSwitch) && m_TransactionStatus.IsTransactionComplete(trans) && !m_IsError &&
        !(m_MastLock && currentMastLock))
    {
        // If this is the last clock of previous transaction and transaction is not completed,
        // then prepare the address phase of the next transation,
        // but don't clear the address phase of the next transaction.
        id = FindPriorityTransaction();
        shouldClearStoredPayload = false;
    }

    // Prepare informations for address phase
    auto& currentPayload = m_Payloads.at(id);
    auto p = currentPayload.GetPayload();

    if (shouldClearStoredPayload)
    {
        // Stores value of HMASTLOCK signal from previous payload
        m_MastLock = p.get_ahb_hmastlock();
        // Clear current paylod
        currentPayload.Clear();
    }

    if (interfaceSwitch)
    {
        // When new transaction is starting, detect metainformation
        // including transaction type, burst size etc
        m_TransactionStatus.StartTransaction(p.get_ahb_hburst());
    }
    if (p.get_ahb_htrans() == CP_AHB_BUSY)
    {
        // Propagate information about clock with BUSY transaction
        m_TransactionStatus.BusyClock();
    }

    // Transfer address phase to slave
    if (p.get_ahb_htrans() != CP_AHB_IDLE)
    {
        CoreType::GetOutputInterface().transport(p, CP_PHS_ADDRESS);
    }

    // Perform clock cycle on transation status
    m_TransactionStatus.ClockCycle();
    // Perform clock cycle on input interfaces
    for (uint8_t i = 0; i < CoreType::IFACE_COUNT; i++)
    {
        CoreType::GetInputInterfaceByIndex(i).clock_cycle();
    }
    // Perform clock cycle on output interface
    CoreType::GetOutputInterface().clock_cycle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void AhbLiteArbiter<T>::blocking_cb(payload_type& p, const Uid)
{
    CoreType::GetOutputInterface().blocking(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void AhbLiteArbiter<T>::transport_cb(payload_type& p, const Phase phase, const Uid uid)
{
    // Transform input interface UID into the index
    const uint8_t index = CoreType::GetInputInterfaceIndexFromUid(uid);

    switch (phase)
    {
        case CP_PHS_DATA:
        {
            // Perform data phase
            if (index == m_SelectedId)
            {
                // if interface is selected for transport, do the transport
                CoreType::GetOutputInterface().transport(p, phase);
                // store slave's HREADY and HRESP signals
                m_IsSlaveReady = (p.get_ahb_hready() == CP_AHB_READY);
                m_IsError = (p.get_ahb_hresp() == CP_AHB_ERROR);
            }
            else
            {
                // if there is another interface selected, do not perform the operation
                // Retrieve stored payload on the interface
                auto& pStored = m_Payloads.at(index);
                // Respond correctly
                bool isReady = !pStored.IsStored() ||
                    pStored.GetPayload().get_ahb_htrans() == CP_AHB_BUSY;
                p.set_ahb_hready(isReady ? CP_AHB_READY : CP_AHB_WAIT);
                p.set_data(0);
            }
            break;
        }
        case CP_PHS_ADDRESS:
        {
            if (!m_Payloads.at(index).IsStored())
            {
                // if buffer is empty, then store address request
                m_Payloads.at(index).Store(p);
            }
            break;
        }
        default:
            break;
    }
}

/**
 *  \brief  Find next transaction to be send through the output interface.
 */
template<typename T>
inline uint8_t AhbLiteArbiter<T>::FindPriorityTransaction()
{
    // Return index if next transaction is already found and waiting
    if (m_NewTransactionIndex != UNKNOWN_INDEX)
    {
        return m_NewTransactionIndex;
    }

    // Check all interfaces by priority
    for (size_t i = 0; i < CoreType::IFACE_COUNT; i++)
    {
        // If there is payload prepared on the interface, use it
        if (m_Payloads[i].IsStored())
        {
            // Remember found transaction, it can't be override later until transaction is processed
            m_NewTransactionIndex = i;
            return i;
        }
    }

    // If no transactions are pending use IDLE state from the most priority interface
    return 0;
}

}   // namespace resources
}   // namespace codasip

#endif   // CODASIP_ARBITER_AHB_HPP
