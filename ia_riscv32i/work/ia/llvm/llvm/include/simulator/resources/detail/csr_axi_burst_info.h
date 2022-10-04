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
 *  \brief  Definition of the class codasip::resources::detail::AxiBurstInfo.
 */

#ifndef SIMULATOR_RESOURCES_DETAIL_CSR_AXI_BURST_INFO_H_
#define SIMULATOR_RESOURCES_DETAIL_CSR_AXI_BURST_INFO_H_

namespace codasip {
namespace resources {
namespace detail {

/**
 * \class AxiBurstInfo
 * \brief Information about single burst (type, length, addresses, ...)
 */
template<class P>
class AxiBurstInfo
{
public:
    void Reset();
    /**
     *  \brief in case of new transfer initialize internal registers
     *         to process further transactions in burst
     *  \param[in]  payload   initial burst address pahse payload
     */
    void Initialize(const P& payload);
    /**
     *  \brief update address and w/r/last indicator for ongoing transactions
     *  \param[out]   payload address phase payload to update according to the current burst state
     */
    void Update(P& payload);

    void IncrementBeatCounter();
    void ResetBeatCounter();
    unsigned GetBeatCounter() const;
    unsigned GetBurstLen() const;

private:
    /// ordinal number of the burst
    unsigned m_BeatCounter = 0;
    /// flag for address being aligned to transfer size
    bool m_AddressIsAligned = false;
    /// address after alignment
    codasip_address_t m_AlignedAddress = 0;
    /// lower boundary for wrap mode
    codasip_address_t m_LowerWrapBoundary = 0;
    /// upper boundary for wrap mode
    codasip_address_t m_UpperWrapBoundary = 0;
    /// address used during burst
    codasip_address_t m_Address = 0;
    /// burst type
    AXIBurstType m_BurstType = AXIBurstType::CP_AXI_BURST_INCR;
    /// byte count in each beat
    uint8_t m_ByteCount = 0;
    /// length of burst (actual length, not the AXI len signal)
    unsigned m_BurstLen = 1;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class P>
void AxiBurstInfo<P>::Reset()
{
    m_BeatCounter = 0;
    m_AddressIsAligned = false;
    m_AlignedAddress = 0;
    m_LowerWrapBoundary = 0;
    m_UpperWrapBoundary = 0;
    m_Address = 0;
    m_BurstType = AXIBurstType::CP_AXI_BURST_INCR;
    m_ByteCount = 0;
    m_BurstLen = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class P>
void AxiBurstInfo<P>::Initialize(const P& payload)
{
    // store generic burst info
    m_Address = payload.get_address();
    m_ByteCount = payload.get_bc();
    m_BurstType = static_cast<AXIBurstType>(payload.get_axi_burst());
    m_BurstLen = payload.get_axi_len() + 1;
    m_AlignedAddress = (static_cast<codasip_address_t>(m_Address / m_ByteCount)) * m_ByteCount;
    m_AddressIsAligned = m_AlignedAddress == m_Address;

    // store wrap specific information
    if (payload.get_axi_burst() == CP_AXI_BURST_WRAP)
    {
        const auto dtSize = m_ByteCount * m_BurstLen;
        m_LowerWrapBoundary = static_cast<codasip_address_t>((m_Address / dtSize * dtSize));
        m_UpperWrapBoundary = m_LowerWrapBoundary + dtSize;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class P>
void AxiBurstInfo<P>::Update(P& payload)
{
    // calculate next address in INCR and WRAP bursts
    if (m_BurstType != CP_AXI_BURST_FIXED && m_BeatCounter > 0)
    {
        // previous address was aligned
        if (m_AddressIsAligned)
        {
            // update address
            m_Address += m_ByteCount;

            // check address for wrap burst boundary
            if (m_BurstType == CP_AXI_BURST_WRAP)
            {
                if (m_Address >= m_UpperWrapBoundary)
                {
                    m_Address = m_LowerWrapBoundary;
                }
            }
        }

        // previous address was not aligned, allign the next one
        else
        {
            m_Address = m_AlignedAddress + m_ByteCount;
            m_AddressIsAligned = true;
        }
    }

    // set address into the payload
    payload.set_address(m_Address);
    // set data phase into the payload (needed by UVM only)
    payload.set_axi_data_phase();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class P>
void AxiBurstInfo<P>::IncrementBeatCounter()
{
    m_BeatCounter++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class P>
void AxiBurstInfo<P>::ResetBeatCounter()
{
    m_BeatCounter = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class P>
unsigned AxiBurstInfo<P>::GetBeatCounter() const
{
    return m_BeatCounter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class P>
unsigned AxiBurstInfo<P>::GetBurstLen() const
{
    return m_BurstLen;
}

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_DETAIL_CSR_AXI_BURST_INFO_H_
