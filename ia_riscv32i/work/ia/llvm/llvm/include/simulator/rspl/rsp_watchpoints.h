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
 *  \author zdeny
 *  \date   Oct 30, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RSPL_RSP_WATCHPOINTS_H_
#define SIMULATOR_RSPL_RSP_WATCHPOINTS_H_

#include "common/codasip_integer.h"
#include "simulator/rspl/rsp_interface.h"

#include <unordered_map>

namespace codasip {
namespace debugger {

/**
 * \class RspWatchpoints
 * \brief Class that holds all watchpoints and it is also used by all interfaces to report all
 *        activities on them
 */
class RspWatchpoints
{
public:
    /**
     * \brief Constructor
     */
    RspWatchpoints();
    /**
     * \brief Destructor
     */
    virtual ~RspWatchpoints();
    /**
     * \brief Return true, if there is a hit and fill the watchpoint info.
     * \param info Hit info
     */
    bool IsHit(WatchpointInfo& info);
    /**
     * \brief Return true, if there is a hit 
     */
    bool IsAnyHit() const;
    /**
     * \brief Data that was used during the transaction
     */
    void Access(const WatchpointInfo::Type, const codasip_address_t address, const MaxUint* data);
    /**
     * \brief Update a list of watchpoints
     * \param info Watchpoint info
     */
    bool UpdateWatchpoint(const WatchpointInfo& info);

private:
    /// Set of watchpoints
    std::unordered_map<codasip_address_t, WatchpointInfo> m_Watchpoints;
    /// Last hit of the watchpoint
    WatchpointInfo m_Hit;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool RspWatchpoints::IsHit(WatchpointInfo& info)
{
    if (m_Hit.IsEnabled())
    {
        info = m_Hit;
        m_Hit = WatchpointInfo();
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool RspWatchpoints::IsAnyHit() const
{
    return m_Hit.IsEnabled();
}

}   // namespace debugger
}   // namespace codasip

#endif   // SIMULATOR_RSPL_RSP_WATCHPOINTS_H_
