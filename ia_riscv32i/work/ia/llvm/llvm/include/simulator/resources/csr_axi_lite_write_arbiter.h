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
 *  \author Pavel Najman
 *  \date   Aug 3, 2020
 *  \brief  Implementation of the AxiLiteWriteArbiter class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_LITE_WRITE_ARBITER_H_
#define SIMULATOR_RESOURCES_CSR_AXI_LITE_WRITE_ARBITER_H_

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
class AxiLiteWriteArbiter
{
public:
    /// Arbiter data type.
    using DataType = typename ArbiterCore::DataType;
    /// Payload data type.
    using PayloadType = detail::AxiArbiterStoredPayload<DataType>;

    /**
     * \brief Constructor.
     */
    AxiLiteWriteArbiter(ArbiterCore* core);
    /**
     * \brief Resets arbiter state.
     */
    void Reset();
    /**
     * \brief Advances arbiter state.
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
    /// A list of stored payloads per interface.
    typedef std::array<PayloadType, ArbiterCore::IFACE_COUNT> StoredPayloadsContainer;

    uint8_t GetHighestPriorityInterfaceIndexWithStoredPayload(const StoredPayloadsContainer&) const;
    bool HasMaximumNumberOfOutstandingAddressRequests(const uint8_t) const;
    bool HasMaximumNumberOfOutstandingDataRequests(const uint8_t) const;
    void TransportDataAndAddressPayloads(const uint8_t);

    /// Arbiter core
    ArbiterCore* m_Core = nullptr;
    /// Stored address payloads - one for each input interface.
    StoredPayloadsContainer m_AddressPayloads;
    /// Stored data payloads - one for each input interface.
    StoredPayloadsContainer m_DataPayloads;
    /// Queue of input interface indices that expect address payloads.
    detail::IndexQueue m_IndicesAddress;
    /// Queue of input interface indices that expect data payloads for sent addresses.
    detail::IndexQueue m_IndicesData;
    /// Queue of input interface indices that expect responses for written data.
    detail::IndexQueue m_IndicesResponse;
    /// Maxium number of outstanding transactions on high priority interface set according to the type of counters that the RTL uses (2-bit counters in this case).
    const uint8_t MAX_OUTSTANDING_REQUESTS_ON_HI_PRIO = 3;
    /// Maxium number of outstanding transactions on low priority interfaces set according to the type of counters that the RTL uses (1-bit counters in this case).
    const uint8_t MAX_OUTSTANDING_REQUESTS_ON_LO_PRIO = 1;
};

template<class ArbiterCore>
inline AxiLiteWriteArbiter<ArbiterCore>::AxiLiteWriteArbiter(ArbiterCore* core)
  : m_Core(core)
{}

template<class ArbiterCore>
inline void AxiLiteWriteArbiter<ArbiterCore>::Reset()
{
    // Clear the stored payloads.
    const auto ClearPayload = [](PayloadType& p)
    {
        p.Clear();
    };
    std::for_each(m_AddressPayloads.begin(), m_AddressPayloads.end(), ClearPayload);
    std::for_each(m_DataPayloads.begin(), m_DataPayloads.end(), ClearPayload);

    m_IndicesAddress.Reset();
    m_IndicesData.Reset();
    m_IndicesResponse.Reset();
}

template<class ArbiterCore>
inline void AxiLiteWriteArbiter<ArbiterCore>::ClockCycle()
{
    if (m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty() &&
        m_IndicesResponse.IsEmptyOnClockCycle())
    {   // If no address, data or response payloads are expected, we search stored payloads and
        // send the one that was received on the interface with the highest priority.
        const auto addressSelectedId = GetHighestPriorityInterfaceIndexWithStoredPayload(
            m_AddressPayloads);
        const auto dataSelectedId = GetHighestPriorityInterfaceIndexWithStoredPayload(m_DataPayloads);

        const auto index = std::min(addressSelectedId, dataSelectedId);
        TransportDataAndAddressPayloads(index);
    }
    else if (m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty() && !m_IndicesResponse.IsEmpty())
    {   // If no address or data payloads are expected but we expect a response, we can send more
        // data or address requests from the same interface.
        const auto index = m_IndicesResponse.Front();
        TransportDataAndAddressPayloads(index);
    }
    else if (!m_IndicesAddress.IsEmpty() && m_IndicesData.IsEmpty())
    {   // If address payload is expected but no data payloads are expected, we send the address
        // payload if possible and start expecting the response.
        const auto index = m_IndicesAddress.Front();

        if (m_AddressPayloads[index].IsStored())
        {
            m_Core->GetOutputInterface().transport(m_AddressPayloads[index].GetPayload(),
                CP_PHS_ADDRESS_WRITE);

            if (m_AddressPayloads[index].GetPayload().get_axi_ready())
            {
                m_AddressPayloads[index].Clear();
                m_IndicesAddress.PopOnClockCycle();
                m_IndicesResponse.Push(index);
            }
        }

        if (m_DataPayloads[index].IsStored())
        {
            m_Core->GetOutputInterface().transport(m_DataPayloads[index].GetPayload(),
                CP_PHS_DATA_WRITE);

            if (m_DataPayloads[index].GetPayload().get_axi_ready())
            {
                m_DataPayloads[index].Clear();
                m_IndicesAddress.Push(index);
            }
        }
    }
    else if (m_IndicesAddress.IsEmpty() && !m_IndicesData.IsEmpty())
    {   // If data payload is expected but no address payloads are expected, we send the data
        // payload if possible and start expecting the response.
        const auto index = m_IndicesData.Front();

        if (m_DataPayloads[index].IsStored())
        {
            m_Core->GetOutputInterface().transport(m_DataPayloads[index].GetPayload(),
                CP_PHS_DATA_WRITE);

            if (m_DataPayloads[index].GetPayload().get_axi_ready())
            {
                m_DataPayloads[index].Clear();
                m_IndicesData.PopOnClockCycle();
                m_IndicesResponse.Push(index);
            }
        }

        if (m_AddressPayloads[index].IsStored())
        {
            m_Core->GetOutputInterface().transport(m_AddressPayloads[index].GetPayload(),
                CP_PHS_ADDRESS_WRITE);

            if (m_AddressPayloads[index].GetPayload().get_axi_ready())
            {
                m_AddressPayloads[index].Clear();
                m_IndicesData.Push(index);
            }
        }
    }

    m_IndicesResponse.ClockCycle();
    m_IndicesAddress.ClockCycle();
    m_IndicesData.ClockCycle();
}

template<class ArbiterCore>
inline void
AxiLiteWriteArbiter<ArbiterCore>::transport_cb(Payload<DataType>& p, const Phase phase, const Uid uid)
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
    {   // During the read data phase, if the interface is selected, the payload is sent to the output
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
 * \brief   Gets the highest priority interface index with stored payload.
 * \param   payloads    Payload container.
 */
template<class ArbiterCore>
inline uint8_t AxiLiteWriteArbiter<ArbiterCore>::GetHighestPriorityInterfaceIndexWithStoredPayload(
    const StoredPayloadsContainer& payloads) const
{
    const auto it = std::find_if(payloads.begin(),
        payloads.end(),
        [](const PayloadType& p)
        {
            return p.IsStored();
        });
    return it != payloads.end() ? it - payloads.begin() : ArbiterCore::IFACE_COUNT;
}

/**
 *  \brief  Decides whether we have reached the maximum number of outstanding address requests on a given input interface.
 *  \param  index   Interface index.
 *  \returns    True if we have reached the maximum number of outstanding address requests, false otherwise.
 */
template<class ArbiterCore>
bool AxiLiteWriteArbiter<ArbiterCore>::HasMaximumNumberOfOutstandingAddressRequests(
    const uint8_t index) const
{
    const auto maxOutstandingRequests = index == 0 ? MAX_OUTSTANDING_REQUESTS_ON_HI_PRIO
                                                   : MAX_OUTSTANDING_REQUESTS_ON_LO_PRIO;
    return (m_IndicesData.Size() >= maxOutstandingRequests && index == m_IndicesData.Front()) ||
        (m_IndicesResponse.Size() >= maxOutstandingRequests && index == m_IndicesResponse.Front());
}
/**
 *  \brief  Decides whether we have reached the maximum number of outstanding data requests on a given input interface.
 *  \param  index   Interface index.
 *  \returns    True if we have reached the maximum number of outstanding data requests, false otherwise.
 */
template<class ArbiterCore>
bool AxiLiteWriteArbiter<ArbiterCore>::HasMaximumNumberOfOutstandingDataRequests(const uint8_t index) const
{
    const auto maxOutstandingRequests = index == 0 ? MAX_OUTSTANDING_REQUESTS_ON_HI_PRIO
                                                   : MAX_OUTSTANDING_REQUESTS_ON_LO_PRIO;
    return (m_IndicesAddress.Size() >= maxOutstandingRequests && index == m_IndicesAddress.Front()) ||
        (m_IndicesResponse.Size() >= maxOutstandingRequests && index == m_IndicesResponse.Front());
}

/**
 *  \brief  Transports address and payloads received on a given interface.
 *  \param  index   Interface index.
 */
template<class ArbiterCore>
void AxiLiteWriteArbiter<ArbiterCore>::TransportDataAndAddressPayloads(const uint8_t index)
{
    if (index >= ArbiterCore::IFACE_COUNT)
    {
        return;
    }

    if (m_DataPayloads[index].IsStored() && m_AddressPayloads[index].IsStored())
    {
        m_Core->GetOutputInterface().transport(m_AddressPayloads[index].GetPayload(),
            CP_PHS_ADDRESS_WRITE);
        m_Core->GetOutputInterface().transport(m_DataPayloads[index].GetPayload(), CP_PHS_DATA_WRITE);

        if (m_DataPayloads[index].GetPayload().get_axi_ready() &&
            m_AddressPayloads[index].GetPayload().get_axi_ready())
        {
            m_DataPayloads[index].Clear();
            m_AddressPayloads[index].Clear();
            m_IndicesResponse.Push(index);
        }
        else if (m_DataPayloads[index].GetPayload().get_axi_ready())
        {
            m_DataPayloads[index].Clear();
            m_IndicesAddress.Push(index);
        }
        else if (m_AddressPayloads[index].GetPayload().get_axi_ready())
        {
            m_AddressPayloads[index].Clear();
            m_IndicesData.Push(index);
        }
    }
    else if (m_DataPayloads[index].IsStored())
    {   // If the selected interface has only the data ready, send the data and if it is accepted,
        // add its index to the address indices queue.
        m_Core->GetOutputInterface().transport(m_DataPayloads[index].GetPayload(), CP_PHS_DATA_WRITE);

        if (m_DataPayloads[index].GetPayload().get_axi_ready())
        {
            m_DataPayloads[index].Clear();
            m_IndicesData.PopOnClockCycle();
            m_IndicesAddress.Push(index);
        }
    }
    else if (m_AddressPayloads[index].IsStored())
    {   // If the selected interface has only the address ready, send the address and if it is accepted,
        // add its index to the data indices queue.
        m_Core->GetOutputInterface().transport(m_AddressPayloads[index].GetPayload(),
            CP_PHS_ADDRESS_WRITE);

        if (m_AddressPayloads[index].GetPayload().get_axi_ready())
        {
            m_AddressPayloads[index].Clear();
            m_IndicesAddress.PopOnClockCycle();
            m_IndicesData.Push(index);
        }
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AXI_LITE_WRITE_ARBITER_H_
