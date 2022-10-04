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
 *  \date   Aug 5, 2020
 *  \brief  Implementation of the AxiArbiter class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AXI_ARBITER_H_
#define SIMULATOR_RESOURCES_CSR_AXI_ARBITER_H_

#include "simulator/resources/csr_axi_lite_read_arbiter.h"
#include "simulator/resources/csr_axi_lite_write_arbiter.h"
#include "simulator/resources/csr_axi_read_arbiter.h"
#include "simulator/resources/csr_axi_write_arbiter.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/simbase/simulator_resources.h"

#include <string>

namespace codasip {
namespace resources {

/**
 *  \brief  Axi Lite arbiter
 *  \tparam ArbiterCore Arbiter configuration.
 */
template<class ArbiterCore, bool IS_AXI4_LITE = false>
class AxiArbiter : public Sentinel, public simulator::ArbiterInfo, public ArbiterCore
{
public:
    /// Arbiter data type.
    using DataType = typename ArbiterCore::DataType;

    /**
     * \brief Constructor.
     */
    AxiArbiter(const std::string& name, const Uid uid);
    /**
     * \brief Resets arbiter state.
     */
    void reset();
    /**
     * \brief Advances arbiter state.
     */
    void clock_cycle();
    /**
     *  \brief  Blocking callback handler.
     *  \param  p   Request payload.
     *  \param  uid Caller uid.
     */
    void blocking_cb(Payload<DataType>& p, const Uid uid);
    /**
     *  \brief  Transport callback handler.
     *  \param  p   Request payload.
     *  \param  phase   Transport phase.
     *  \param  uid Caller uid.
     */
    void transport_cb(Payload<DataType>& p, const Phase phase, const Uid uid);

private:
    typedef
        typename std::conditional<IS_AXI4_LITE, AxiLiteReadArbiter<ArbiterCore>, AxiReadArbiter<ArbiterCore>>::type
            ReadArbiterType;
    typedef typename std::conditional<IS_AXI4_LITE,
        AxiLiteWriteArbiter<ArbiterCore>,
        AxiWriteArbiter<ArbiterCore>>::type WriteArbiterType;

    /// arbiter for read transactions.
    ReadArbiterType m_AxiLiteReadArbiter;
    /// arbiter for write transactions.
    WriteArbiterType m_AxiLiteWriteArbiter;
};

template<class ArbiterCore, bool IS_AXI4_LITE>
inline AxiArbiter<ArbiterCore, IS_AXI4_LITE>::AxiArbiter(const std::string& name, const Uid uid)
  : Sentinel(name, uid)
  , simulator::ArbiterInfo(name, uid)
  , ArbiterCore(name, this)
  , m_AxiLiteReadArbiter(this)
  , m_AxiLiteWriteArbiter(this)
{}

template<class ArbiterCore, bool IS_AXI4_LITE>
inline void AxiArbiter<ArbiterCore, IS_AXI4_LITE>::reset()
{
    m_AxiLiteReadArbiter.Reset();
    m_AxiLiteWriteArbiter.Reset();

    for (uint8_t i = 0; i < ArbiterCore::IFACE_COUNT; i++)
    {   //  Reset input interfaces
        ArbiterCore::GetInputInterfaceByIndex(i).reset();
    }

    //  Reset output interface
    ArbiterCore::GetOutputInterface().reset();
}

template<class ArbiterCore, bool IS_AXI4_LITE>
inline void AxiArbiter<ArbiterCore, IS_AXI4_LITE>::clock_cycle()
{
    m_AxiLiteReadArbiter.ClockCycle();
    m_AxiLiteWriteArbiter.ClockCycle();

    for (uint8_t i = 0; i < ArbiterCore::IFACE_COUNT; i++)
    {   // Perform clock cycle on input interfaces.
        ArbiterCore::GetInputInterfaceByIndex(i).clock_cycle();
    }

    // Perform clock cycle on output interface.
    ArbiterCore::GetOutputInterface().clock_cycle();
}

template<class ArbiterCore, bool IS_AXI4_LITE>
inline void AxiArbiter<ArbiterCore, IS_AXI4_LITE>::blocking_cb(Payload<DataType>& p, const Uid)
{
    ArbiterCore::GetOutputInterface().blocking(p);
}

template<class ArbiterCore, bool IS_AXI4_LITE>
inline void
AxiArbiter<ArbiterCore, IS_AXI4_LITE>::transport_cb(Payload<DataType>& p, const Phase phase, const Uid uid)
{
    if (phase == CP_PHS_ADDRESS_READ || phase == CP_PHS_DATA_READ)
    {
        m_AxiLiteReadArbiter.transport_cb(p, phase, uid);
    }
    else
    {
        m_AxiLiteWriteArbiter.transport_cb(p, phase, uid);
    }
}

template<class ArbiterCore>
using AxiLiteArbiter = AxiArbiter<ArbiterCore, true>;

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AXI_ARBITER_H_
