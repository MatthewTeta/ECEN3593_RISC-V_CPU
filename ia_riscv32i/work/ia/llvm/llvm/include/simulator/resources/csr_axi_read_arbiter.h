/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip Ltd
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the property of Codasip Ltd
 * and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and proprietary to
 * Codasip Ltd and are protected by trade secret and copyright law.  In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Kamil Michl
 *  \date   Oct 12, 2021
 *  \brief  Implementation of the AxiReadArbiter class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_READ_ARBITER_H_
#define SIMULATOR_RESOURCES_CSR_AXI_READ_ARBITER_H_

#include "simulator/resources/csr_arbiter_payload.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/detail/csr_index_queue.h"

#include <array>

namespace codasip {
namespace resources {

/**
 *  \brief  Axi arbiter. Arbiters only read signals.
 *  \tparam ArbiterCore Arbiter configuration.
 */
template<class ArbiterCore>
class AxiReadArbiter
{
public:
    /// Arbiter data type.
    using DataType = typename ArbiterCore::DataType;
    using PayloadType = detail::AxiArbiterStoredPayload<DataType>;
    using PayloadContainer = std::array<PayloadType, ArbiterCore::IFACE_COUNT>;

    /**
     * \brief Constructor.
     */
    AxiReadArbiter(ArbiterCore* core);
    /**
     * \brief Resets the arbiter state.
     */
    void Reset();
    /**
     * \brief Advances the arbiter state.
     */
    void ClockCycle();
    /**
     *  \brief  Transport callback handler.
     *  \param  p   Request payload.
     *  \param  phase   Transport phase.
     *  \param  uid Caller uid.
     */
    void transport_cb(Payload<DataType>& p, const Phase phase, const Uid uid);

private:
    bool IsAddressPayloadWithHigherPriorityStored(uint8_t);
    void SendCurrentAddressPayload();
    void SelectTheHighestPriorityPayload();
    void SelectTheSamePriorityPayload();

    /// Arbiter core
    ArbiterCore* m_Core = nullptr;
    /// Stored address payloads - one for each input interface.
    PayloadContainer m_AddressPayloads;
    /// Queue of input interface indices that expect data payloads for sent addresses.
    detail::IndexQueue m_IndicesData;
    /// Stores address payload that was sent to output interface but was not accepted yet.
    PayloadType m_CurrentAddressPayload;
    /// An index of an input interface that currently transacts on the output interface.
    uint8_t m_CurrentInterfaceIndex = 0;
    /// Set when the payload arrives on interface with priority higher than the priority of the currently active interface.
    bool m_LastLowerPriorityRequest = false;
    /// Number of currently outstanding transactions
    uint8_t InProgressTransactionsCount = 0;
    /// Maxium number of outstanding transactions set according to the type of counters that the RTL uses (2-bit counters in this case).
    const uint8_t MAX_OUTSTANDING_TRANSACTIONS = 3;
};

template<class ArbiterCore>
inline AxiReadArbiter<ArbiterCore>::AxiReadArbiter(ArbiterCore* core)
  : m_Core(core)
{}

template<class ArbiterCore>
inline void AxiReadArbiter<ArbiterCore>::Reset()
{
    // Clear the stored payloads.
    for (auto& payload : m_AddressPayloads)
    {
        payload.Clear();
    }

    // Clear indices.
    m_IndicesData.Reset();

    // Clear selected payload and reset the selected interface.
    m_CurrentAddressPayload.Clear();
    m_CurrentInterfaceIndex = 0;
    m_LastLowerPriorityRequest = false;
    InProgressTransactionsCount = 0;
}

template<class ArbiterCore>
inline void AxiReadArbiter<ArbiterCore>::ClockCycle()
{
    if (m_IndicesData.IsEmpty() && !m_CurrentAddressPayload.IsStored())
    {   // No transaction in progress AND no address request waiting to be retransmitted.
        SelectTheHighestPriorityPayload();
        SendCurrentAddressPayload();
        m_LastLowerPriorityRequest = false;
    }
    else if (m_IndicesData.IsEmpty() && m_CurrentAddressPayload.IsStored())
    {   // No transaction is in progress AND an address request is waiting to be retransmitted.
        SendCurrentAddressPayload();
    }
    else if (!m_IndicesData.IsEmpty() && !m_CurrentAddressPayload.IsStored())
    {   // The transaction is in progress AND no address request waiting to be retransmitted.
        if (InProgressTransactionsCount < MAX_OUTSTANDING_TRANSACTIONS &&
            m_AddressPayloads[m_CurrentInterfaceIndex].IsStored())
        {   // Less than three addresses have been requested AND
            // a new request on the current interface has been received.
            SelectTheSamePriorityPayload();
            SendCurrentAddressPayload();
            m_LastLowerPriorityRequest = !m_LastLowerPriorityRequest &&
                IsAddressPayloadWithHigherPriorityStored(m_CurrentInterfaceIndex);
        }
        else if (m_IndicesData.IsEmptyOnClockCycle())
        {   // All transactions has been finished.
            SelectTheHighestPriorityPayload();
            SendCurrentAddressPayload();
            m_LastLowerPriorityRequest = false;
        }
    }
    else   // if (!m_IndicesData.IsEmpty() && m_CurrentAddressPayload.IsStored())
    {      // The transaction is in progress AND an address request waiting to be retransmitted.
        if (InProgressTransactionsCount < MAX_OUTSTANDING_TRANSACTIONS)
        {   // Less than three addresses have been requested.
            SendCurrentAddressPayload();
            m_LastLowerPriorityRequest = IsAddressPayloadWithHigherPriorityStored(
                m_CurrentInterfaceIndex);
        }
    }

    m_IndicesData.ClockCycle();
}

template<class ArbiterCore>
inline void
AxiReadArbiter<ArbiterCore>::transport_cb(Payload<DataType>& p, const Phase phase, const Uid uid)
{
    uint8_t index = m_Core->GetInputInterfaceIndexFromUid(uid);

    if (phase == CP_PHS_ADDRESS_READ)
    {   //  During the read address phase, if the interface has already a VALID payload stored OR
        //  the last request is being processed OR we have maximum number of transaction in
        //  progress, it has to WAIT, otherwise, it is READY and if the payload is VALID, it is
        //  stored.
        p.set_axi_ready(m_AddressPayloads[index].IsStored() || m_LastLowerPriorityRequest ||
                    InProgressTransactionsCount >= MAX_OUTSTANDING_TRANSACTIONS
                ? CP_AXI_WAIT
                : CP_AXI_READY);

        if (p.get_axi_ready() == CP_AXI_READY)
        {
            m_AddressPayloads[index].Store(p);
        }
    }
    else if (phase == CP_PHS_DATA_READ)
    {   //  During the read data phase, if the index is equal to the index of the input interface
        //  that expect the next data payload, the payload is sent to the output interface and if
        //  the output is READY to accept it, the input interface index is removed from the indices
        //  queue. If the index is not equal to the index of the input interface that expect the
        //  next data payload, the arbiter responds with INVALID.
        if (!m_IndicesData.IsEmpty() && index == m_IndicesData.Front())
        {
            m_Core->GetOutputInterface().transport(p, CP_PHS_DATA_READ);

            if (p.get_axi_valid() && p.get_axi_ready())
            {
                m_IndicesData.PopOnClockCycle();
                if (m_IndicesData.IsEmptyOnClockCycle())
                {
                    InProgressTransactionsCount--;
                }
            }
        }
        else
        {
            p.set_axi_valid(CP_AXI_INVALID);
        }
    }
}

/**
 *  \brief  Decides whether the address payload from higher priority interface is stored.
 *  \param  priority    Priority threshold.
 *  \returns    True if the higher priority payload is stored, false otherwise.
 */
template<class ArbiterCore>
bool AxiReadArbiter<ArbiterCore>::IsAddressPayloadWithHigherPriorityStored(uint8_t priority)
{
    for (size_t i = 0; i < m_AddressPayloads.size() && i < priority; ++i)
    {
        if (m_AddressPayloads[i].IsStored())
        {
            return true;
        }
    }
    return false;
}

/// Sends the current address payload to the output interface.
template<class ArbiterCore>
void AxiReadArbiter<ArbiterCore>::SendCurrentAddressPayload()
{
    if (!m_CurrentAddressPayload.IsStored())
    {
        return;
    }

    auto& payload = m_CurrentAddressPayload.GetPayload();

    m_Core->GetOutputInterface().transport(payload, CP_PHS_ADDRESS_READ);

    if (payload.get_axi_ready())
    {   //  The sent address payload was accepted, therefore, we clear the current address
        //  payload as well as the buffered payload and add the id of the sending interface to the id queue.
        for (size_t i = 0; i <= payload.get_axi_len(); i++)
        {
            m_IndicesData.Push(m_CurrentInterfaceIndex);
        }
        m_AddressPayloads[m_CurrentInterfaceIndex].Clear();
        m_CurrentAddressPayload.Clear();
        InProgressTransactionsCount++;
    }
}

/// Selects the highest priority payload as the payload that will be processed next.
template<class ArbiterCore>
void AxiReadArbiter<ArbiterCore>::SelectTheHighestPriorityPayload()
{
    for (size_t i = 0; i < m_AddressPayloads.size(); i++)
    {
        if (m_AddressPayloads[i].IsStored())
        {
            m_CurrentAddressPayload.Store(m_AddressPayloads[i].GetPayload());
            m_CurrentInterfaceIndex = i;
            return;
        }
    }
}

/// Selects the payload from the currently active interface as the payload that will be processed next.
template<class ArbiterCore>
void AxiReadArbiter<ArbiterCore>::SelectTheSamePriorityPayload()
{
    if (m_AddressPayloads[m_CurrentInterfaceIndex].IsStored())
    {
        m_CurrentAddressPayload.Store(m_AddressPayloads[m_CurrentInterfaceIndex].GetPayload());
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AXI_READ_ARBITER_H_
