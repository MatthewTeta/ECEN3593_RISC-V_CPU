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
 *  \date   Oct 13, 2021
 *  \brief  Implementation of the AxiWriteArbiter class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_WRITE_ARBITER_H_
#define SIMULATOR_RESOURCES_CSR_AXI_WRITE_ARBITER_H_

#include "simulator/resources/csr_arbiter_payload.h"
#include "simulator/resources/csr_axi_lite_read_arbiter.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/detail/csr_index_queue.h"

#include <array>

namespace codasip {
namespace resources {

/**
 *  \brief  Axi Lite arbiter. Arbiters only write signals.
 *  \tparam ArbiterCore Arbiter configuration.
 */
template<class ArbiterCore>
class AxiWriteArbiter
{
public:
    /// Arbiter data type.
    using DataType = typename ArbiterCore::DataType;
    /// Payload data type.
    using PayloadType = detail::AxiArbiterStoredPayload<DataType>;

    AxiWriteArbiter(ArbiterCore* core);
    void Reset();
    void ClockCycle();
    void transport_cb(Payload<DataType>& p, const Phase phase, const Uid uid);

private:
    /// A list of stored payloads per interface.
    typedef std::array<PayloadType, ArbiterCore::IFACE_COUNT> StoredPayloadsContainer;

    uint8_t GetHighestPriorityInterfaceIndexWithStoredPayload(const StoredPayloadsContainer&) const;

    bool HasMaximumNumberOfOutstandingAddressRequests(const uint8_t index) const;
    bool HasMaximumNumberOfOutstandingDataRequests(const uint8_t index) const;

    void PerformTransport(const uint8_t index);

    void ADEmptyIndicesADHandler(const uint8_t index);
    void ADEmptyIndicesAHandler(const uint8_t index);
    void ADEmptyIndicesDHandler(const uint8_t index);

    void AEmptyIndicesADHandler(const uint8_t index);
    void AEmptyIndicesAHandler(const uint8_t index);
    void AEmptyIndicesDHandler(const uint8_t index);

    void DEmptyIndicesADHandler(const uint8_t index);
    void DEmptyIndicesAHandler(const uint8_t index);
    void DEmptyIndicesDHandler(const uint8_t index);

    /// Arbiter core
    ArbiterCore* m_Core = nullptr;
    /// Stored address payloads - one for each input interface
    StoredPayloadsContainer m_AddressPayloads;
    /// Stored data payloads - one for each input interface
    StoredPayloadsContainer m_DataPayloads;
    /// Queue of input interface indices that expect address payloads
    /// Note: There is one address index if there is at least one data transaction without address received.
    ///       For every completed data burst without address transaction, there is additional index stored.
    ///       So there is possible to jump from 0 to 2 indicies if the first data burst has length 0.
    ///       Also address indices can be cleared, if the size drops bellow 2 if there no more lingerring data payloads.
    detail::IndexQueue m_IndicesAddress;
    /// Queue of input interface indices that expect data payloads for sent addresses
    /// Note: Data index is added for each data transaction that is expected, not for entire burst.
    ///       We also need to calculate number uf in progress bursts, so the special counter is used for this.
    detail::IndexQueue m_IndicesData;
    /// Queue of input interface indices that expect responses for written data
    /// Note: One for each completed burst
    detail::IndexQueue m_IndicesResponse;
    /// Number of currently outstanding bursts in data phase
    size_t m_InProgressDataBurstsCount = 0;
    /// Number of received data transactions in current burst (with no address)
    size_t m_CurentBurstDataWithoutAddress = 0;
    /// True if the next next data payload will start new burst without known address phase
    bool m_LastBurstDataPayloadWithoutAddress = true;
    /// Maxium number of outstanding transactions on high priority interface
    /// set according to the type of counters that the RTL uses (2-bit counters in this case)
    const uint8_t MAX_OUTSTANDING_REQUESTS_ON_HI_PRIO = 3;
    /// Maxium number of outstanding transactions on low priority interfaces
    /// set according to the type of counters that the RTL uses (1-bit counters in this case)
    const uint8_t MAX_OUTSTANDING_REQUESTS_ON_LO_PRIO = 1;
};

template<class ArbiterCore>
inline AxiWriteArbiter<ArbiterCore>::AxiWriteArbiter(ArbiterCore* core)
  : m_Core(core)
{}

template<class ArbiterCore>
inline void AxiWriteArbiter<ArbiterCore>::Reset()
{
    // Clear the stored payloads.
    const auto ClearPayload = [](PayloadType& p)
    {
        p.Clear();
    };
    std::for_each(m_AddressPayloads.begin(), m_AddressPayloads.end(), ClearPayload);
    std::for_each(m_DataPayloads.begin(), m_DataPayloads.end(), ClearPayload);

    // Clear stored indices
    m_IndicesAddress.Reset();
    m_IndicesData.Reset();
    m_IndicesResponse.Reset();

    // Reset counters and flags
    m_InProgressDataBurstsCount = 0;
    m_CurentBurstDataWithoutAddress = 0;
    m_LastBurstDataPayloadWithoutAddress = true;
}

template<class ArbiterCore>
inline void AxiWriteArbiter<ArbiterCore>::ClockCycle()
{
    uint8_t index = 0;

    // No instruction is currently processed in any phase
    if (m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty() &&
        m_IndicesResponse.IsEmptyOnClockCycle())
    {
        const auto addressSelectedId = GetHighestPriorityInterfaceIndexWithStoredPayload(
            m_AddressPayloads);
        const auto dataSelectedId = GetHighestPriorityInterfaceIndexWithStoredPayload(m_DataPayloads);
        index = std::min(addressSelectedId, dataSelectedId);
    }

    // No address and data phases are currently in progress, only some responses were not yet processed
    else if (m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty() && !m_IndicesResponse.IsEmpty())
    {
        index = m_IndicesResponse.Front();
    }

    // Some address phases were received, but waiting for corresponding data phases to finish the burst
    else if (!m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty())
    {
        index = m_IndicesAddress.Front();
    }

    // Some data phases were received, but waiting for corresponding address phases to finish the burst
    else if (m_IndicesAddress.IsEmpty() && !m_IndicesData.IsEmpty())
    {
        index = m_IndicesData.Front();
    }

    // Perform the transport with payloads from interface on the calculated index
    PerformTransport(index);

    // Perform clock cycle on indices
    m_IndicesResponse.ClockCycle();
    m_IndicesAddress.ClockCycle();
    m_IndicesData.ClockCycle();
}

template<class ArbiterCore>
inline void
AxiWriteArbiter<ArbiterCore>::transport_cb(Payload<DataType>& p, const Phase phase, const Uid uid)
{
    const auto index = m_Core->GetInputInterfaceIndexFromUid(uid);

    if (phase == CP_PHS_ADDRESS_WRITE)
    {   // During the write address phase, if the interface has stored VALID payload or has reached
        // the maximum number of outstanding transactions, it has to WAIT, otherwise, it is READY
        // and if the payload is VALID, it is stored.
        p.set_axi_ready(m_AddressPayloads[index].IsStored() ||
                    HasMaximumNumberOfOutstandingAddressRequests(index)
                ? CP_AXI_WAIT
                : CP_AXI_READY);

        if (p.get_axi_ready() == CP_AXI_READY)
        {
            m_AddressPayloads[index].Store(p);
        }
    }
    else if (phase == CP_PHS_DATA_WRITE)
    {   // During the write data phase, if the interface has stored VALID payload or has reached
        // the maximum number of outstanding transactions, it has to WAIT, otherwise, it is READY
        // and if the payload is VALID, it is stored.
        p.set_axi_ready(
            m_DataPayloads[index].IsStored() || HasMaximumNumberOfOutstandingDataRequests(index)
                ? CP_AXI_WAIT
                : CP_AXI_READY);

        if (p.get_axi_ready() == CP_AXI_READY)
        {
            m_DataPayloads[index].Store(p);
        }
    }
    else if (phase == CP_PHS_RESPONSE_WRITE)
    {   // During the write response phase, if the interface is selected, the payload is sent to the output
        // interface and if the output is READY to accept it, the request is removed from the stored
        // payloads. If the interface is not selected, arbiter responds with INVALID.
        if (!m_IndicesResponse.IsEmpty() && index == m_IndicesResponse.Front())
        {
            m_Core->GetOutputInterface().transport(p, CP_PHS_RESPONSE_WRITE);

            if (p.get_axi_valid() && p.get_axi_ready())
            {
                m_IndicesResponse.PopOnClockCycle();
            }
        }
        else
        {
            p.set_axi_valid(CP_AXI_INVALID);
        }
    }
}

/**
 * \brief Gets the highest priority interface index with stored payload
 * \param payloads Payload container
 */
template<class ArbiterCore>
inline uint8_t AxiWriteArbiter<ArbiterCore>::GetHighestPriorityInterfaceIndexWithStoredPayload(
    const StoredPayloadsContainer& payloads) const
{
    for (uint8_t i = 0; i < ArbiterCore::IFACE_COUNT; i++)
    {
        if (payloads[i].IsStored())
        {
            return i;
        }
    }
    return ArbiterCore::IFACE_COUNT;
}

/**
 *  \brief Decides whether we have reached the maximum number of outstanding address requests on a given input interface
 *  \param index Interface index
 */
template<class ArbiterCore>
bool AxiWriteArbiter<ArbiterCore>::HasMaximumNumberOfOutstandingAddressRequests(const uint8_t index) const
{
    const auto maxOutstandingRequests = index == 0 ? MAX_OUTSTANDING_REQUESTS_ON_HI_PRIO
                                                   : MAX_OUTSTANDING_REQUESTS_ON_LO_PRIO;
    return (m_InProgressDataBurstsCount >= maxOutstandingRequests && index == m_IndicesData.Front()) ||
        (m_IndicesResponse.Size() >= maxOutstandingRequests && index == m_IndicesResponse.Front());
}
/**
 *  \brief Decides whether we have reached the maximum number of outstanding data requests on a given input interface
 *  \param index Interface index
 */
template<class ArbiterCore>
bool AxiWriteArbiter<ArbiterCore>::HasMaximumNumberOfOutstandingDataRequests(const uint8_t index) const
{
    const auto maxOutstandingRequests = index == 0 ? MAX_OUTSTANDING_REQUESTS_ON_HI_PRIO
                                                   : MAX_OUTSTANDING_REQUESTS_ON_LO_PRIO;
    return (m_LastBurstDataPayloadWithoutAddress && m_IndicesAddress.Size() > maxOutstandingRequests &&
               index == m_IndicesAddress.Front()) ||
        (m_IndicesResponse.Size() >= maxOutstandingRequests && index == m_IndicesResponse.Front());
}

/**
 * \brief Perfroms write address and data transports if there are valid payloads on the given interface
 * \param index Index of interface that can send it's transactions in this cycle
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::PerformTransport(const uint8_t index)
{
    // Check for out of range index
    if (index >= ArbiterCore::IFACE_COUNT)
    {
        return;
    }

    // Assume unsuccessfull phases in the beginning
    // (not valid payloads or target not ready to receive)
    bool addressSuccess = false;
    bool dataSuccess = false;

    // Perform write address phase transport if payload is valid and check if the target processed it
    if (m_AddressPayloads[index].IsStored())
    {
        m_Core->GetOutputInterface().transport(m_AddressPayloads[index].GetPayload(),
            CP_PHS_ADDRESS_WRITE);
        addressSuccess = m_AddressPayloads[index].GetPayload().get_axi_ready() == CP_AXI_READY;
    }
    // Perform write data phase transport if payload is valid and check if the target processed it
    if (m_DataPayloads[index].IsStored())
    {
        m_Core->GetOutputInterface().transport(m_DataPayloads[index].GetPayload(), CP_PHS_DATA_WRITE);
        dataSuccess = m_DataPayloads[index].GetPayload().get_axi_ready() == CP_AXI_READY;
    }

    // Select result handler according to successfull transports and current state of the arbiter indices
    // a) No instruction is currently processed in any phase
    if (m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty())
    {
        if (addressSuccess && dataSuccess)
        {
            ADEmptyIndicesADHandler(index);
        }
        else if (addressSuccess)
        {
            ADEmptyIndicesAHandler(index);
        }
        else if (dataSuccess)
        {
            ADEmptyIndicesDHandler(index);
        }
    }
    // b) Some address phases were received, but waiting for corresponding data phases to finish the burst
    else if (!m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty())
    {
        if (addressSuccess && dataSuccess)
        {
            DEmptyIndicesADHandler(index);
        }
        else if (addressSuccess)
        {
            DEmptyIndicesAHandler(index);
        }
        else if (dataSuccess)
        {
            DEmptyIndicesDHandler(index);
        }
    }
    // c) Some data phases were received, but waiting for corresponding address phases to finish the burst
    else if (m_IndicesAddress.IsEmpty() && !m_IndicesData.IsEmpty())
    {
        if (addressSuccess && dataSuccess)
        {
            AEmptyIndicesADHandler(index);
        }
        else if (addressSuccess)
        {
            AEmptyIndicesAHandler(index);
        }
        else if (dataSuccess)
        {
            AEmptyIndicesDHandler(index);
        }
    }

    // Clear the payloads that were successfully transported and processed
    if (addressSuccess)
    {
        m_AddressPayloads[index].Clear();
    }
    if (dataSuccess)
    {
        m_DataPayloads[index].Clear();
    }
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                    | Address | Data
 *        Indices     | EMPTY   | EMPTY
 *        Transports  | DONE    | DONE
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::ADEmptyIndicesADHandler(const uint8_t index)
{
    // Burst with length 1 is already completed, so expect reponse next
    if (m_AddressPayloads[index].GetPayload().get_axi_len() == 0)
    {
        m_IndicesResponse.Push(index);
    }

    // Burst with length larger than 1 requires more data
    else
    {
        for (unsigned i = 0; i < m_AddressPayloads[index].GetPayload().get_axi_len(); i++)
        {
            m_IndicesData.Push(index);
        }
        m_InProgressDataBurstsCount++;
    }
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | EMPTY   | EMPTY
 *        Transports | DONE    | WAITING
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::ADEmptyIndicesAHandler(const uint8_t index)
{
    // Address was received, so we need how many data transactions we need to complete the burst
    for (unsigned i = 0; i <= m_AddressPayloads[index].GetPayload().get_axi_len(); i++)
    {
        m_IndicesData.Push(index);
    }
    m_InProgressDataBurstsCount++;
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | EMPTY   | EMPTY
 *        Transports | WAITING | DONE
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::ADEmptyIndicesDHandler(const uint8_t index)
{
    // Data was received without address, so we need the address next
    m_IndicesAddress.Push(index);

    // If the data were last in the burst, we need to store another address index to indicate end of current burst
    if (m_DataPayloads[index].GetPayload().get_axi_last() == CP_AXI_LAST)
    {
        m_LastBurstDataPayloadWithoutAddress = true;
        m_IndicesAddress.Push(index);
    }

    // If the data were not last we need to update the number of data that we already have for the current burst
    else
    {
        m_LastBurstDataPayloadWithoutAddress = false;
        m_CurentBurstDataWithoutAddress++;
    }
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | EMPTY   | PRESENT
 *        Transports | DONE    | DONE
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::AEmptyIndicesADHandler(const uint8_t index)
{
    // Perform actions for address and data, no special handling for the combination needed
    AEmptyIndicesAHandler(index);
    AEmptyIndicesDHandler(index);
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | EMPTY   | PRESENT
 *        Transports | DONE    | WAITING
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::AEmptyIndicesAHandler(const uint8_t index)
{
    // Another address received with at least one burst already waiting for data
    // Push additional data indices for the new following burst indicated by the address
    for (unsigned i = 0; i <= m_AddressPayloads[index].GetPayload().get_axi_len(); i++)
    {
        m_IndicesData.Push(index);
    }
    m_InProgressDataBurstsCount++;
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | EMPTY   | PRESENT
 *        Transports | WAITING | DONE
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::AEmptyIndicesDHandler(const uint8_t index)
{
    // We received expected data
    // We remove the appropriate data index
    m_IndicesData.PopOnClockCycle();

    // if the burst is completed, also update the burst counter and expect reponse phase in the future
    if (m_DataPayloads[index].GetPayload().get_axi_last() == CP_AXI_LAST)
    {
        m_IndicesResponse.Push(index);
        m_InProgressDataBurstsCount--;
    }
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | PRESENT | EMPTY
 *        Transports | DONE    | DONE
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::DEmptyIndicesADHandler(const uint8_t index)
{
    // Increment number of data we received
    m_CurentBurstDataWithoutAddress++;

    // There is at least one complete burst (data-wise) waiting for the address we just received
    if (m_IndicesAddress.Size() > 1)
    {
        // Burst is completed, so expect response in the future
        m_IndicesResponse.Push(index);

        // If current data is the last in a burst we can leave the address index be for the next burst
        if (m_DataPayloads[index].GetPayload().get_axi_last() == CP_AXI_LAST)
        {
            m_LastBurstDataPayloadWithoutAddress = true;
            m_CurentBurstDataWithoutAddress = 0;
        }
        // Otherwise we need one less address indices, because there is no new burst in progress
        else
        {
            m_IndicesAddress.PopOnClockCycle();
            m_LastBurstDataPayloadWithoutAddress = false;
        }
    }

    // There is no data-wise completed burst, so we are processing the only in-progress burst
    else
    {
        // Address for the burst was received, so we don't need to wait for another
        m_IndicesAddress.PopOnClockCycle();

        // Data was the last in a burst, so we completed the current burst and we will expect response
        if (m_DataPayloads[index].GetPayload().get_axi_last() == CP_AXI_LAST)
        {
            m_LastBurstDataPayloadWithoutAddress = true;
            m_IndicesResponse.Push(index);
            m_CurentBurstDataWithoutAddress = 0;
        }

        // We are still waiting for more data to finish the current burst
        // But now we know how much data are we expecting because of the address phase
        // So we move from waiting-on-address state to waiting-for-data state
        else
        {
            m_LastBurstDataPayloadWithoutAddress = m_IndicesAddress.IsEmptyOnClockCycle();
            for (unsigned i = m_CurentBurstDataWithoutAddress;
                 i <= m_AddressPayloads[index].GetPayload().get_axi_len();
                 i++)
            {
                m_IndicesData.Push(index);
            }
            m_InProgressDataBurstsCount++;
            m_CurentBurstDataWithoutAddress = 0;
        }
    }
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | PRESENT | EMPTY
 *        Transports | DONE    | WAITING
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::DEmptyIndicesAHandler(const uint8_t index)
{
    // One of the burst waiting on address (only) is completed, so we expect response in the future
    if (m_IndicesAddress.Size() > 1)
    {
        m_IndicesResponse.Push(index);

        // We used one address index, so it should be poped
        // But if there will be only one address index after the pop, it means that
        // there is no completed burst (data-wise) waiting on next address
        // So if there is currently no data buffered, we are not waiting for another address
        // and the address indices must be reset, so we will be in state
        // where no transaction is in progress (except the response phase)
        if (m_CurentBurstDataWithoutAddress == 0 && m_IndicesAddress.Size() == 2)
        {
            m_IndicesAddress.Reset();
        }
        else
        {
            m_IndicesAddress.PopOnClockCycle();
        }
    }

    // We don't have enough data for complete burst yet, but we received the address for the current burst
    else
    {
        m_IndicesAddress.PopOnClockCycle();

        // We need to move to waiting-on-data state and we know how many data we expect
        while (m_CurentBurstDataWithoutAddress > 0)
        {
            for (unsigned i = m_CurentBurstDataWithoutAddress;
                 i <= m_AddressPayloads[index].GetPayload().get_axi_len();
                 i++)
            {
                m_IndicesData.Push(index);
            }
            m_InProgressDataBurstsCount++;
            m_CurentBurstDataWithoutAddress = 0;
        }
    }
}

/**
 * \brief Updates internal state of the arbiter after transports
 *                   | Address | Data
 *        Indices    | PRESENT | EMPTY
 *        Transports | WAITING | DONE
 * \param index Currently selected input interface index
 */
template<class ArbiterCore>
void AxiWriteArbiter<ArbiterCore>::DEmptyIndicesDHandler(const uint8_t index)
{
    // We are waiting on address, but next data was received, so we need to buffer it
    m_CurentBurstDataWithoutAddress++;
    if (m_LastBurstDataPayloadWithoutAddress)
    {
        m_LastBurstDataPayloadWithoutAddress = false;
    }

    // If the data is last in a burst, we need to wait on another address to complete the burst
    if (m_DataPayloads[index].GetPayload().get_axi_last() == CP_AXI_LAST)
    {
        m_LastBurstDataPayloadWithoutAddress = true;
        m_IndicesAddress.Push(index);
        m_CurentBurstDataWithoutAddress = 0;
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AXI_WRITE_ARBITER_H_
