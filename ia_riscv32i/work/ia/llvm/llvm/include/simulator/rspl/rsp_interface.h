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
 *  \date   Mar 19, 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RSPL_RSP_INTERFACE_H_
#define SIMULATOR_RSPL_RSP_INTERFACE_H_

#include "common/codasip_integer.h"
#include "common/toolstypes.h"

#include <cstdint>

namespace codasip {
namespace debugger {

/// Thread id
typedef uint16_t Tid;
/// DWARF id
typedef uint32_t Did;
/// Constant that denotes that all threads are active
const static Tid TID_ALL = -1;
/// Constant that denotes any thread
const static Tid TID_ANY = 0;
/// Constant that denotes the default thread
const static Tid TID_DEFAULT = 1;

/// Level of stepping and stopping of the simulator
typedef enum
{
    /// Invalid level
    DEBUG_LEVEL_INVALID = 0,
    /// Stepping in instructions / C code
    DEBUG_LEVEL_C,
    /// Stepping in CodAL statements
    DEBUG_LEVEL_CODAL

} DebugLevel;

/**
 * \class ResumeInfo
 * \brief Holding info about resume request
 */
class ResumeInfo
{
public:
    typedef enum
    {
        /// Continue
        CONTINUE,
        /// Next statement (step over)
        NEXT,
        /// Step one statement (step into)
        STEP,
        /// Step one clock cycle
        CLOCK_CYCLE,
        /// Codal version of next
        NEXT_CODAL,
        /// Codal version of step
        STEP_CODAL
    } Type;
    /**
     * \brief Constructor
     * \param tid Thread ID
     * \param type Type of resule
     */
    ResumeInfo(const Tid tid, const Type type);
    /**
     * \{
     * \brief Getter
     */
    Tid GetTid() const;
    Type GetType() const;
    /** \} */
private:
    /// Thread ID
    Tid m_Tid;
    /// type of the resume request
    Type m_Type;
};

/**
 *  \class  StopLocation
 *  \brief  Describes location in source code where debugging event occurred.
 */
class StopInfo
{
public:
    /**
     *  \brief  Constructor for breakpoint and address watchpoint.
     *  \param  tid ID of ASIP instance thread where event occurred.
     *  \param  address Code or watchpoint address.
     *  \param  dl Describes type of code where debugging event occurred.
     */
    StopInfo(const Tid tid, const codasip_address_t address, const DebugLevel debugLevel);
    /**
     *  \{
     *  \brief  Access to internal attributes
     */
    Tid GetThread() const;
    codasip_address_t GetAddress() const;
    DebugLevel GetDebugLevel() const;
    /** \} */
protected:
    /// Thread ID where event occurred.
    Tid m_Tid;
    /// Code address
    codasip_address_t m_Address;
    /// Type of code
    DebugLevel m_DebugLevel;
};

/**
 *  \class  MatchpointInfo
 *  \brief  Describes common attributes for breakpoints and watchpoints
 */
class MatchpointInfo : public StopInfo
{
public:
    /**
     *  \brief  Constructor.
     *  \param  address Address of breakpoint to change.
     *  \param  byteSize Byte size of the matchpoint
     *  \param  debugLevel Type of code where breakpoint will be set.
     *  \param  enabled True if given breakpoint will be enabled, false if it will be disabled.
     */
    MatchpointInfo(const Tid tid,
        const codasip_address_t address,
        const codasip_address_t byteSize,
        const bool enabled = true,
        const DebugLevel debugLevel = DEBUG_LEVEL_C);

    /**
     *  \brief  Return if breakpoint that is being set will get enabled or disabled.
     */
    bool IsEnabled() const;
    /**
     * \brief Byte size of a matchpoint
     */
    codasip_address_t GetByteSize() const;

protected:
    /// True if given breakpoint will be enabled, false if it will be disabled.
    bool m_Enabled;
    /// Code address
    codasip_address_t m_ByteSize;
};

/**
 *  \class  BreakpointInfo
 *  \brief  Describes attributes for changing breakpoint at given address.
 */
class BreakpointInfo : public MatchpointInfo
{
public:
    typedef enum
    {
        /// Hardware breakpoint
        HW,
        /// Software breakpoint
        SW,
        /// Codal breakpoint
        CODAL
    } Type;

    /**
     *  \brief  Constructor.
     *  \param  address Address of breakpoint to change.
     *  \param  debugLevel Type of code where breakpoint will be set.
     *  \param  enabled True if given breakpoint will be enabled, false if it will be disabled.
     */
    BreakpointInfo(const Tid tid,
        const codasip_address_t address,
        const codasip_address_t byteSize,
        const Type = HW,
        const bool enabled = true,
        const DebugLevel debugLevel = DEBUG_LEVEL_C);
    /**
     *  \{
     *  \brief  Access to internal attributes
     */
    Type GetType() const;
    /** \} */
protected:
    /// Type of breakpoint
    Type m_Type;
};

/**
 *  \class  WatchpointInfo
 *  \brief  Describes attributes for changing watchpoint or informing when given watchpoint is hit
 */
class WatchpointInfo : public MatchpointInfo
{
public:
    /// Type of memory access
    typedef enum
    {
        /// Invalid type
        NONE = 0,
        /// Hit watchpoint when given data/address is read
        READ = 1,
        /// Hit watchpoint when given data/address is written
        WRITE = READ << 1,
        /// Hit watchpoint when given data/address is read or written
        ACCESS = READ | WRITE
    } Type;

    /**
     * \brief Default constructor
     */
    WatchpointInfo();
    /**
     *  \brief  Constructor for a address and data watchpoint
     *  \param  type Type of access for a watchpoint
     *  \param  address Address of breakpoint to change.
     *  \param  byteSize Size of watchpoint
     *  \param  data Data to be compared (optional)
     *  \param  debugLevel Type of code where breakpoint will be set.
     *  \param  enabled True if given breakpoint will be enabled, false if it will be disabled.
     */
    WatchpointInfo(const Tid tid,
        const Type type,
        const codasip_address_t address,
        const codasip_address_t byteSize,
        const MaxUint* data = nullptr,
        const bool enabled = true,
        const DebugLevel debugLevel = DEBUG_LEVEL_C);
    /**
     * \brief Destructor
     */
    ~WatchpointInfo();
    /**
     * \brief Copy constructor
     */
    WatchpointInfo(const WatchpointInfo&);
    /**
     * \brief Assignee operator
     */
    WatchpointInfo& operator=(const WatchpointInfo&);
    /**
     *  \{
     *  \brief  Access to internal attributes
     */
    Type GetType() const;
    const MaxUint* GetData() const;
    /** \} */
protected:
    /// Access definition for a watchpoint
    Type m_Type;
    /// Data for a watchpoint if present
    MaxUint* m_Data;
};

/**
 *  \class  StaetInfo
 *  \brief  Describes state info for a debugger. It could be breakpoint state etc.
 */
class StateChangeInfo : public StopInfo
{
public:
    /// Type of state change events
    typedef enum
    {
        /// Invalid stop reason
        INVALID = 0,
        /// Breakpoint was hit
        HW_BREAKPOINT,
        /// Breakpoint was hit
        SW_BREAKPOINT,
        /// Single step was performed
        STEP,
        /// Read watchpoint was hit
        READ_WATCHPOINT,
        /// Read watchpoint was hit
        WRITE_WATCHPOINT,
        /// Read/Write watchpoint was hit
        ACCESS_WATCHPOINT,
        /// Invalid instruction was decoded
        INVALID_INSTRUCTION,
        /// Program finished
        FINISHED,
        /// Target is running
        RUNNING,
        /// Program was killed
        KILLED,
        /// Program was aborted
        ABORTED,
        /// Codal breakpoint hit
        CODAL_BREAKPOINT,
        /// Single step in codal
        CODAL_STEP
    } Type;

    /**
     *  \brief  Constructor
     *  \param  tid ID of the thread where debugging event occurred.
     *  \param  addr Code address where debugging event occurred.
     *  \param  lvl Level describing type of code address.
     *  \param  type Reason describing type of event
     */
    StateChangeInfo(const Tid tid,
        const codasip_address_t address,
        const DebugLevel debugLevel,
        const Type type);
    /**
     *  \{
     *  \brief  Access to internal attributes
     */
    Type GetType() const;
    /** \} */
protected:
    /// Type of event
    Type m_Type;
};

}   // namespace debugger
}   // namespace codasip

#endif   // SIMULATOR_RSPL_RSP_INTERFACE_H_
