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
 *  \author Zdenek Prikryl
 *  \date   Mar 2, 2016
 *  \brief  Definition of the class codasip::resources::Watchpoint.
 */

#ifndef SIMULATOR_RESOURCES_CSR_WATCHPOINT_H_
#define SIMULATOR_RESOURCES_CSR_WATCHPOINT_H_

#include "simulator/resources/csr_ahb_pac.h"
#include "simulator/resources/csr_axi_lite_pac.h"
#include "simulator/resources/csr_axi_pac.h"
#include "simulator/resources/csr_axi_target_interface.h"
#include "simulator/resources/csr_cpb_pac.h"
#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"
#include "simulator/resources/detail/csr_axi_burst_info.h"
#include "simulator/rspl/rsp_watchpoints.h"

#include <queue>
#include <type_traits>

namespace codasip {
namespace resources {
namespace watchpoint_detail {

/**
 *  \internal
 *  \brief  Syntax shortcut to simplify selection of correct PAC implementation
 *          used by \ref DumperAddress.
 */
template<class T, class PAC, typename R = void>
using is_pac = typename std::enable_if<std::is_same<T, PAC>::value, R>::type;

}   // namespace watchpoint_detail

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::Watchpoint
 *  \brief  Class that is able to detect watchpoints on a defined interfaces.
 *          Supported watchpoint types are:
 *          \li read/write address watchpoints
 *          \li read/write address + data watchpoints
 *
 *          The data watchpoints only are not supported because the LLDB does not support it.
 *
 *          The implementation supports multiple outstanding transactions by storing
 *          required partial (per phase) payloads in internal queue(s).
 *
 *          Please, note, the implementation does not check error/response codes
 *          because they are not always available in given phase.
 *  \}
 */
template<class T>
class Watchpoint : public T
{
public:
    using T::transport;
    using typename T::data_type;
    using typename T::param_type;
    using typename T::payload_type;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    Watchpoint(const std::string& name, const Uid uid);
    /**
     *  \brief  Set RSP watchpoint
     *  \param  rspWatchpoints Watchpoint listener
     */
    void set_rsp_watchpoints(debugger::RspWatchpoints* rspWatchpoints);
    /**
     *  \{
     *  \internal
     *  \warning    No override, the virtual call is defined in the interface template
     *              which is not a base of this class. Shadowing is used instead.
     */
    void blocking_d(payload_type& p);
    void transport_d(payload_type& p, const Phase phase);
    /** \} */
private:
    /// \brief  Internal queue used to store the payloads
    typedef std::queue<payload_type> PayloadQueue;

    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, AhbPac> DoAddressPhase(const payload_type&, const Phase);
    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, AhbPac> DoDataPhase(const payload_type&, const Phase);
    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, AxiLitePac> DoAddressPhase(const payload_type&, const Phase);
    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, AxiLitePac> DoDataPhase(const payload_type&, const Phase);
    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, AxiPac> DoAddressPhase(const payload_type&, const Phase);
    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, AxiPac> DoDataPhase(const payload_type&, const Phase);
    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, CpbPac> DoAddressPhase(const payload_type&, const Phase);
    template<class _PAC>
    watchpoint_detail::is_pac<_PAC, CpbPac> DoDataPhase(const payload_type&, const Phase);

    void DoAccess(const debugger::WatchpointInfo::Type, const codasip_address_t);
    void DoAccess(const debugger::WatchpointInfo::Type, const codasip_address_t, param_type);

    /// Debugger connection
    debugger::RspWatchpoints* m_RspWatchpoints;
    /// store address payload in case the there are multiple read addresses acknowledged
    /// all stored payloads have asserted the ARVALID and ARREADY signals
    /// reused for AHB and CPB as well
    PayloadQueue m_ReadAddress;
    /// store address payload in case the write data on AXI are delayed
    /// all stored payloads have asserted the AWVALID and AWREADY signals
    PayloadQueue m_WriteAddress;
    /// store write data payloads in case the address on AXI is delayed
    /// all stored payloads have asserted the WVALID and WREADY signals
    PayloadQueue m_WriteData;
    /// Information about AXI burst transaction, needed to calculate all used addresses
    detail::AxiBurstInfo<payload_type> m_AxiBurstInfo;
    /// Payload used to calculate all used addresses by an AXI burst transaction
    payload_type m_AxiTmpPayload;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Watchpoint<T>::Watchpoint(const std::string& name, const Uid uid)
  : T(name, uid)
  , m_RspWatchpoints(nullptr)
{}

////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void Watchpoint<T>::set_rsp_watchpoints(debugger::RspWatchpoints* rspWatchpoints)
{
    m_RspWatchpoints = rspWatchpoints;
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Watchpoint<T>::blocking_d(payload_type& p)
{
    T::blocking_d(p);
    if (p.get_command() == CP_CMD_READ || p.get_command() == CP_CMD_WRITE)
    {
        const debugger::WatchpointInfo::Type type = p.get_command() == CP_CMD_READ
            ? debugger::WatchpointInfo::READ
            : debugger::WatchpointInfo::WRITE;
        // must be called twice, otherwise the underlying RSP implementation
        // can't distinguish between address and address+data watchpoint
        DoAccess(type, p.get_address());
        DoAccess(type, p.get_address(), p.get_data());
    }
}

////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Watchpoint<T>::transport_d(payload_type& p, const Phase phase)
{
    T::transport_d(p, phase);
    switch (phase)
    {
        case CP_PHS_ADDRESS:
        case CP_PHS_ADDRESS_READ:
        case CP_PHS_ADDRESS_WRITE:
            DoAddressPhase<typename T::PacType>(p, phase);
            break;
        case CP_PHS_DATA:
        case CP_PHS_DATA_READ:
        case CP_PHS_DATA_WRITE:
            DoDataPhase<typename T::PacType>(p, phase);
            break;
        case CP_PHS_RESPONSE_WRITE:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Detect address watchpoint on AMBA 3 AHB-Lite interface.
 *  \param  p source transaction information
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, AhbPac>
Watchpoint<T>::DoAddressPhase(const payload_type& p, const Phase)
{
    if ((p.get_ahb_hready() == CP_AHB_READY) && p.is_ahb_active_transfer() && m_ReadAddress.empty())
    {
        const debugger::WatchpointInfo::Type type = p.get_ahb_hwrite() == CP_AHB_READ
            ? debugger::WatchpointInfo::READ
            : debugger::WatchpointInfo::WRITE;
        DoAccess(type, p.get_address());
        m_ReadAddress.push(p);
    }
}

/**
 *  \brief  Detect address + data watchpoint on AMBA 3 AHB-Lite interface.
 *  \param  p source transaction information
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, AhbPac>
Watchpoint<T>::DoDataPhase(const payload_type& p, const Phase)
{
    if ((p.get_ahb_hready() == CP_AHB_READY) && !m_ReadAddress.empty())
    {
        const auto& addrPhase = m_ReadAddress.front();
        const debugger::WatchpointInfo::Type type = addrPhase.get_ahb_hwrite() == CP_AHB_READ
            ? debugger::WatchpointInfo::READ
            : debugger::WatchpointInfo::WRITE;
        DoAccess(type, addrPhase.get_address(), p.get_data());
        m_ReadAddress.pop();
    }
}

/**
 *  \brief  Detect address watchpoint on AMBA AXI4-Lite interface.
 *  \param  p source transaction information
 *  \param  phase read or write phase
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, AxiLitePac>
Watchpoint<T>::DoAddressPhase(const payload_type& p, const Phase phase)
{
    if ((p.get_axi_ready() == CP_AXI_READY) && (p.get_axi_valid() == CP_AXI_VALID))
    {
        if (phase == CP_PHS_ADDRESS_WRITE)
        {
            if (!m_WriteData.empty())
            {   // there is a write data payload pending (write data came before the address)
                // write address+data WP
                DoAccess(debugger::WatchpointInfo::WRITE,
                    p.get_address(),
                    m_WriteData.front().get_data());
                m_WriteData.pop();
            }
            else
            {   // write address WP, store payload for write address+data WP
                DoAccess(debugger::WatchpointInfo::WRITE, p.get_address());
                m_WriteAddress.push(p);
            }
        }
        else
        {   // read address watchpoint
            DoAccess(debugger::WatchpointInfo::READ, p.get_address());
            m_ReadAddress.push(p);
        }
    }
}

/**
 *  \brief  Detect address + data watchpoint on AMBA AXI4-Lite interface.
 *  \param  p source transaction information
 *  \param  phase read or write phase
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, AxiLitePac>
Watchpoint<T>::DoDataPhase(const payload_type& p, const Phase phase)
{
    if ((p.get_axi_ready() == CP_AXI_READY) && (p.get_axi_valid() == CP_AXI_VALID))
    {
        if (phase == CP_PHS_DATA_READ)
        {   // slave restores the address
            DoAccess(debugger::WatchpointInfo::READ, m_ReadAddress.front().get_address(), p.get_data());
            m_ReadAddress.pop();
        }
        else
        {   // write address + data watchpoint
            if (!m_WriteAddress.empty())
            {   // there is a write address payload pending (write address came before the data)
                // write address+data WP
                DoAccess(debugger::WatchpointInfo::WRITE,
                    m_WriteAddress.front().get_address(),
                    p.get_data());
                m_WriteAddress.pop();
            }
            else
            {   // write data came before address, store for latter usage
                m_WriteData.push(p);
            }
        }
    }
}

/**
 *  \brief  Detect address watchpoint on AMBA AXI4-Lite interface.
 *  \param  p source transaction information
 *  \param  phase read or write phase
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, AxiPac>
Watchpoint<T>::DoAddressPhase(const payload_type& p, const Phase phase)
{
    // only process valid address payloads
    if ((p.get_axi_ready() == CP_AXI_READY) && (p.get_axi_valid() == CP_AXI_VALID))
    {
        // calculate all used addresses in the burst
        m_AxiTmpPayload.reset();
        m_AxiBurstInfo.Reset();
        m_AxiBurstInfo.Initialize(p);
        while (m_AxiBurstInfo.GetBeatCounter() != m_AxiBurstInfo.GetBurstLen())
        {
            // each address used by the burst must be checked for address watchpoint
            // and stored for future data watchpoint detection
            m_AxiBurstInfo.Update(m_AxiTmpPayload);
            if (phase == CP_PHS_ADDRESS_WRITE)
            {
                DoAccess(debugger::WatchpointInfo::WRITE, m_AxiTmpPayload.get_address());
                m_WriteAddress.push(m_AxiTmpPayload);
            }
            else
            {
                DoAccess(debugger::WatchpointInfo::READ, m_AxiTmpPayload.get_address());
                m_ReadAddress.push(m_AxiTmpPayload);
            }
            m_AxiBurstInfo.IncrementBeatCounter();
        }

        // If some write data is already present, consume it and appropriate address and check for data watchpoints
        if (phase == CP_PHS_ADDRESS_WRITE)
        {
            while (!m_WriteData.empty() && !m_WriteAddress.empty())
            {
                DoAccess(debugger::WatchpointInfo::WRITE,
                    m_WriteAddress.front().get_address(),
                    m_WriteData.front().get_data());
                m_WriteData.pop();
                m_WriteAddress.pop();
            }
        }
    }
}

/**
 *  \brief  Detect address + data watchpoint on AMBA AXI4-Lite interface.
 *  \param  p source transaction information
 *  \param  phase read or write phase
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, AxiPac>
Watchpoint<T>::DoDataPhase(const payload_type& p, const Phase phase)
{
    // only process valid address payloads
    if ((p.get_axi_ready() == CP_AXI_READY) && (p.get_axi_valid() == CP_AXI_VALID))
    {
        if (phase == CP_PHS_DATA_READ)
        {
            // Perform check for data watchpoint with appropriate address
            DoAccess(debugger::WatchpointInfo::READ, m_ReadAddress.front().get_address(), p.get_data());
            m_ReadAddress.pop();
        }
        else
        {
            if (!m_WriteAddress.empty())
            {
                // Perform check for data watchpoint if we have address to pair it with
                DoAccess(debugger::WatchpointInfo::WRITE,
                    m_WriteAddress.front().get_address(),
                    p.get_data());
                m_WriteAddress.pop();
            }
            else
            {   // If we don't have an address, store the data for future analysis
                m_WriteData.push(p);
            }
        }
    }
}

/**
 *  \brief  Detect address or address + write data watchpoint on CPB interface.
 *  \param  p source transaction information
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, CpbPac>
Watchpoint<T>::DoAddressPhase(const payload_type& p, const Phase)
{
    if ((p.get_cpb_aready() == CP_CPB_READY) && p.get_cpb_avalid() == CP_CPB_VALID)
    {
        if (p.get_cpb_write() == CP_CPB_WRITE)
        {
            // must be called twice, otherwise the underlying RSP implementation
            // can't distinguish between address and address+data watchpoint
            DoAccess(debugger::WatchpointInfo::WRITE, p.get_address());
            DoAccess(debugger::WatchpointInfo::WRITE, p.get_address(), p.get_data());
        }
        else
        {
            DoAccess(debugger::WatchpointInfo::READ, p.get_address());
        }
        // read and write addresses have to be stored for data phase
        // because read and write transfers can be mixed
        m_ReadAddress.push(p);
    }
}

/**
 *  \brief  Detect address + data watchpoint on CPB interface.
 *  \param  p source transaction information
 */
template<class T>
template<class _PAC>
inline watchpoint_detail::is_pac<_PAC, CpbPac>
Watchpoint<T>::DoDataPhase(const payload_type& p, const Phase)
{
    if (p.get_cpb_valid() == CP_CPB_VALID)
    {
        const auto& addrPhase = m_ReadAddress.front();
        if (addrPhase.get_cpb_write() == CP_CPB_READ)
        {
            DoAccess(debugger::WatchpointInfo::READ, addrPhase.get_address(), p.get_data());
        }
        m_ReadAddress.pop();
    }
}

/**
 *  \brief  Report access to the debugger in case it is set properly.
 *  \param  type read/write access type
 *  \param  addr source address
 */
template<class T>
inline void
Watchpoint<T>::DoAccess(const debugger::WatchpointInfo::Type type, const codasip_address_t addr)
{
    if (m_RspWatchpoints != nullptr)
    {
        /*
        std::cerr
            << "WATCHPOINT TRIGGER - "
            << (type == debugger::WatchpointInfo::READ ? std::string("READ") : std::string("WRITE"))
            << " 0x" << std::hex << addr << std::dec << std::endl;
        */
        m_RspWatchpoints->Access(type, addr, nullptr);
    }
}

/**
 *  \brief  Report access to the debugger in case it is set properly.
 *  \param  type read/write access type
 *  \param  addr source address
 *  \param  data source data
 */
template<class T>
inline void Watchpoint<T>::DoAccess(const debugger::WatchpointInfo::Type type,
    const codasip_address_t addr,
    param_type data)
{
    if (m_RspWatchpoints != nullptr)
    {
        /*
        std::cerr
            << "WATCHPOINT TRIGGER - "
            << (type == debugger::WatchpointInfo::READ ? std::string("READ") : std::string("WRITE"))
            << " 0x" << std::hex << addr << " : 0x" << data << std::dec << std::endl;
        */
        const MaxUint rspData(data);
        m_RspWatchpoints->Access(type, addr, &rspData);
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_WATCHPOINT_H_
