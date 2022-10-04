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
 *  \date   5. 12. 2018
 *  \brief  Definition of the class codasip::resources::CpbBus.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CPB_BUS_H_
#define SIMULATOR_RESOURCES_CSR_CPB_BUS_H_

#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::CpbBus
 *  \brief  Implements bus interconnect for Codasip Processor Bus protocol.
 *  \}
 */
template<class _BusCore>
class CpbBus : public _BusCore, public Sentinel
{
public:
    /// \brief  Import slave interface typedef from the base class
    typedef typename _BusCore::SlaveInterface SlaveInterface;
    /// \brief  Import payload type from the slave interface
    typedef typename SlaveInterface::payload_type payload_type;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    template<typename... Args>
    CpbBus(const std::string& name, const Uid uid, Args&&... args);
    /**
     *  \brief  Reset bus (reset request logic)
     */
    void reset();
    /**
     *  \brief  Move one clock cycle further.
     */
    void clock_cycle();
    /**
     *  \brief  Interface callback for the master routing the transaction to the
     *          appropriate slave.
     *  \param  p source transaction payload
     *  \param  uid bus master identifier initiating the transaction
     */
    void blocking_cb(payload_type& p, const Uid uid);
    /**
     *  \copydoc blocking_cb()
     *  \param  phase transport phase identifier
     */
    void transport_cb(payload_type& p, const Phase phase, const Uid uid);

private:
    void DoAddrPhase(payload_type&, const Phase);
    void DoDataPhase(payload_type&, const Phase);
    void LogOOR(const codasip_address_t);

    /// pointer to selected slave during address phase
    SlaveInterface* m_SlaveSelect;
    /// pointer to selected slave used during data phase
    SlaveInterface* m_SlaveSelectReg;
    /// indicates whether response of the default slave used for current clock
    /// cycle is valid or not
    CPBValidCode m_DefaultSlaveValidReg;
    /// indicates whether response of the default slave used for next clock
    /// cycle will be valid or not
    CPBValidCode m_DefaultSlaveValidNext;
    /// response of the default slave used for current clock cycle
    CPBResponseCode m_DefaultSlaveResponseReg;
    /// response of the default slave used to store for next clock cycle
    CPBResponseCode m_DefaultSlaveResponseNext;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
template<typename... Args>
inline CpbBus<_BusCore>::CpbBus(const std::string& name, const Uid uid, Args&&... args)
  : _BusCore(name.substr(0, name.find_last_of('.')), std::forward<Args>(args)...)
  , Sentinel(name, uid)
  , m_SlaveSelect(nullptr)
  , m_SlaveSelectReg(nullptr)
  , m_DefaultSlaveValidReg(CP_CPB_INVALID)
  , m_DefaultSlaveValidNext(CP_CPB_INVALID)
  , m_DefaultSlaveResponseReg(CP_CPB_OKAY)
  , m_DefaultSlaveResponseNext(CP_CPB_OKAY)
{}

////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void CpbBus<_BusCore>::reset()
{
    _BusCore::Reset();
    m_SlaveSelect = nullptr;
    m_SlaveSelectReg = nullptr;
    m_DefaultSlaveValidReg = CP_CPB_INVALID;
    m_DefaultSlaveValidNext = CP_CPB_INVALID;
    m_DefaultSlaveResponseReg = CP_CPB_OKAY;
    m_DefaultSlaveResponseNext = CP_CPB_OKAY;
}

////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void CpbBus<_BusCore>::clock_cycle()
{
    _BusCore::ClockCycle();
    // check whether there is a transfer in progress (data phase)
    if (m_SlaveSelectReg == nullptr)
    {   // bus is ready, the slave may change
        m_SlaveSelectReg = m_SlaveSelect;
    }
    m_SlaveSelect = nullptr;
    m_DefaultSlaveValidReg = m_DefaultSlaveValidNext;
    m_DefaultSlaveResponseReg = m_DefaultSlaveResponseNext;
    // reset the flag in case there is no transport() after error
    m_DefaultSlaveValidNext = CP_CPB_INVALID;
    m_DefaultSlaveResponseNext = CP_CPB_OKAY;
}

////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void CpbBus<_BusCore>::blocking_cb(payload_type& p, const Uid)
{
    const bool load = p.get_command() == CP_CMD_LOAD;
    const codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;
    SlaveInterface* slave = nullptr;
    // call address decoder
    this->GetSlaveInterface(oAddr, nAddr, slave, load);
    if (slave != nullptr)
    {
        p.set_address(nAddr);
        slave->blocking(p);
        p.set_address(oAddr);
    }
    else if (p.get_cpb_avalid() == CP_CPB_VALID)
    {   // do not throw, just log and store error
        LogOOR(oAddr);
        p.set_cpb_resp(CP_CPB_ERROR);
    }
}

////////////////////////////////////////////////////////////////////////////////
template<class _BusCore>
RES_INLINE void CpbBus<_BusCore>::transport_cb(payload_type& p, const Phase phase, const Uid)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            DoAddrPhase(p, phase);
            break;
        case CP_PHS_DATA:
            DoDataPhase(p, phase);
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Address phase handling. Decodes the address of an incoming transaction
 *          and routes it to target slave. In case the decoding fails for valid
 *          transaction, an error response will be stored for the next data phase.
 *  \param  p source transaction payload
 *  \param  phase transport phase identifier
 */
template<class _BusCore>
inline void CpbBus<_BusCore>::DoAddrPhase(payload_type& p, const Phase phase)
{
    if (m_SlaveSelectReg != nullptr)
    {   // transfer already in progress, can't handle new/another transfer
        p.set_cpb_aready(CP_CPB_WAIT);
        return;
    }
    // check that there is a slave
    const bool load = p.get_command() == CP_CMD_LOAD;
    const codasip_address_t oAddr = p.get_address();
    codasip_address_t nAddr = 0;
    // call address decoder
    this->GetSlaveInterface(oAddr, nAddr, m_SlaveSelect, load);
    if (m_SlaveSelect != nullptr)
    {
        p.set_address(nAddr);
        m_SlaveSelect->transport(p, phase);
        p.set_address(oAddr);
        if (p.get_cpb_avalid() == CP_CPB_INVALID)
        {   // clear the slave selection for idle transfer, this way the data phase
            // does not need to be called in order to issue new address phase
            // transfer in the next clock cycle
            m_SlaveSelect = nullptr;
        }
    }
    else
    {   // next state is ready, for valid transfer issue an error response
        m_DefaultSlaveValidNext = p.get_cpb_avalid();
        m_DefaultSlaveResponseNext = (p.get_cpb_avalid() == CP_CPB_VALID) ? CP_CPB_ERROR : CP_CPB_OKAY;
    }
}

/**
 *  \brief  Data phase handling. Routes the transaction based on stored slave
 *          selection register to target slave. In case the default slave is selected,
 *          set default state flag and prepared response.
 *  \param  p source transaction payload
 *  \param  phase transport phase identifier
 */
template<class _BusCore>
inline void CpbBus<_BusCore>::DoDataPhase(payload_type& p, const Phase phase)
{
    if (m_SlaveSelectReg == nullptr)
    {   // no running transaction, store response of the default slave
        p.set_cpb_valid(m_DefaultSlaveValidReg);
        p.set_cpb_resp(m_DefaultSlaveResponseReg);
        p.set_data(static_cast<typename payload_type::data_type>(0u));
    }
    else
    {   // route the transaction
        m_SlaveSelectReg->transport(p, phase);
        if (p.get_cpb_valid() == CP_CPB_VALID)
        {   // the transaction is finished
            // the bus is ready to process new request in the same clock cycle
            m_SlaveSelectReg = nullptr;
        }
    }
}

/**
 *  \brief  Log error message describing no slave selection (out-of-range).
 *  \param  addr requested address causing the error
 */
template<class _BusCore>
void CpbBus<_BusCore>::LogOOR(const codasip_address_t addr)
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature()
                               << "': no slave selected at address: 0x" << std::hex << addr;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CPB_BUS_H_
