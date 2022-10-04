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
 *  \date   Nov 5, 2019
 *  \brief  Definition of the class codasip::resources::Tcm.
 */

#ifndef SIMULATOR_RESOURCES_CSR_TCM_H_
#define SIMULATOR_RESOURCES_CSR_TCM_H_

#include "getoptl/interface/optionssim.h"
#include "simulator/resources/csr_ahb_arbiter.h"
#include "simulator/resources/csr_memory.h"
#include "simulator/simbase/simulator_resources.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::Tcm
 *  \brief  Tightly coupled memory.
 *  \tparam TcmCore Tcm configuration.
 *
 *  TcmCore must define the following types:
 *  -   InterfaceType
 *  TcmCore must contain the following static constants:
 *  -   DEFINITION_BLOCK_COUNT
 *  -   SLAVE_UID
 *  TcmCore must support following methods:
 *  -   TcmCore(const std::string& name, const Uid uid, Tcm<TcmCore>*)
 *  -   codasip_address_t GetBaseAddress(size_t index);
 *  -   codasip_address_t GetSize(size_t index);
 *  -   void DispatchBlocking(size_t index, Payload<DataType>& p);
 *  -   void DispatchBlocking(Payload<DataType>& p);
 *  -   void DispatchTransport(size_t index, Payload<DataType>& p, const Phase phase);
 *  -   void DispatchTransport(Payload<DataType>& p, const Phase phase);
 *  \}
 */
template<class TcmCore>
class Tcm : public simulator::TcmInfo,
            public TcmCore   // TcmInfo must be first to support insertion by TcmCore
{
public:
    /// Slave interface type.
    typedef typename TcmCore::InterfaceType InterfaceType;
    /// Slave interface payload type.
    typedef typename InterfaceType::payload_type payload_type;

    /**
     *  \brief  Constructs TCM object.
     *  \param  name Name of the component
     *  \param  uid UID of the component
     *  \param  args used to forward codal parameters to tcm core, if any
     */
    template<typename... Args>
    Tcm(const std::string& name, const Uid uid, Args&&... args);
    /**
     *  \brief  Advances TCM state.
     */
    void clock_cycle();
    /**
     *  \brief  Resets TCM state.
     */
    void reset();
    /**
     *  \brief  Checks whether the given address is in indexed arbiter range.
     *  \param  address Checked address.
     *  \param  index TCM definition/block index.
     *  \return true if address is in TCM range, false otherwise.
     */
    bool IsAddressInRange(const codasip_address_t address, const size_t index) const;
    /**
     *  \brief  Interfaces callback for IA mode.
     *  \param  p source transaction payload
     *  \param  uid unique identification of the source interface where the
     *          transaction comes from
     */
    void blocking_cb(payload_type& p, const Uid uid);
    /**
     *  \brief  Interfaces callback for CA mode.
     *  \param  p source transaction payload
     *  \param  phase phase identifier
     *  \param  uid unique identification of the source interface where the
     *          transaction comes from
     */
    void transport_cb(payload_type& p, const Phase phase, const Uid uid);

private:
    /// Last clock destination index.
    Index m_LastDestinationIndex;
    /// Current clock destination index.
    Index m_CurrentDestinationIndex;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TcmCore>
template<typename... Args>
inline Tcm<TcmCore>::Tcm(const std::string& name, const Uid uid, Args&&... args)
  : simulator::TcmInfo(name, uid)
  , TcmCore(name, this, std::forward<Args>(args)...)
  , m_LastDestinationIndex(0)
  , m_CurrentDestinationIndex(0)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TcmCore>
RES_INLINE void Tcm<TcmCore>::clock_cycle()
{
    TcmCore::ClockCycle();
    m_LastDestinationIndex = m_CurrentDestinationIndex;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TcmCore>
inline void Tcm<TcmCore>::reset()
{
    TcmCore::Reset();
    m_LastDestinationIndex = 0;
    m_CurrentDestinationIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TcmCore>
RES_INLINE bool
Tcm<TcmCore>::IsAddressInRange(const codasip_address_t address, const size_t index) const
{
    const auto indexBitWidth = TcmCore::GetIndexBitWidth(index);
    const auto baseAddress = TcmCore::GetBaseAddress(index);

    const auto baseOfComparedAddress = ((address >> indexBitWidth) << indexBitWidth);
    return (baseOfComparedAddress == baseAddress);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TcmCore>
inline void Tcm<TcmCore>::blocking_cb(payload_type& p, const Uid uid)
{
    if (uid == TcmCore::SLAVE_UID)
    {
        for (size_t ii = 0; ii < TcmCore::DEFINITION_BLOCK_COUNT; ++ii)
        {
            if (IsAddressInRange(p.get_address(), ii))
            {
                const codasip_address_t addr = p.get_address();
                p.set_address(addr & (TcmCore::GetSize(ii) - 1));
                TcmCore::DispatchBlocking(ii, p, uid);
                // restore original address for the dumper and UVM data verification
                p.set_address(addr);
                return;
            }
        }
    }
    else
    {
        TcmCore::DispatchBlocking(p, uid);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TcmCore>
inline void Tcm<TcmCore>::transport_cb(payload_type& p, const Phase phase, const Uid uid)
{
    if (uid == TcmCore::SLAVE_UID)
    {   // for slave interface, we need to decide to which internal arbiter we send the request
        for (size_t ii = 0; ii < TcmCore::DEFINITION_BLOCK_COUNT; ++ii)
        {
            if (phase == CP_PHS_DATA && m_LastDestinationIndex == ii)
            {
                TcmCore::DispatchTransport(ii, p, phase, uid);
                return;
            }
            else if (phase == CP_PHS_ADDRESS && IsAddressInRange(p.get_address(), ii))
            {
                const codasip_address_t addr = p.get_address();
                p.set_address(p.get_address() & (TcmCore::GetSize(ii) - 1));
                TcmCore::DispatchTransport(ii, p, phase, uid);
                // restore original address for the dumper and UVM data verification
                p.set_address(addr);
                m_CurrentDestinationIndex = ii;
                return;
            }
        }
    }
    else
    {   // for non slave interface, we do not need to decide to which internal arbiter we send
        // the request because the decision makes the TcmCore
        TcmCore::DispatchTransport(p, phase, uid);
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_TCM_H_
