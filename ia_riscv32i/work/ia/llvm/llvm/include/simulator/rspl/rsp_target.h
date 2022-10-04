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

#ifndef SIMULATOR_RSPL_RSP_TARGET_H_
#define SIMULATOR_RSPL_RSP_TARGET_H_

#include "common/codasip_integer.h"
#include "common/toolstypes.h"
#include "simulator/rspl/rsp_interface.h"
#include "simulator/simbase/codasip_interface.h"

#include <condition_variable>
#include <map>
#include <mutex>
#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>

namespace codasip {
namespace debugger {

class RspServer;
class RspInterpreter;
class RspWatchpoints;

/**
 * \class RspTarget
 * \brief Base class for RSP target, some functionality is left on the simulator via virtual calls
 *
 *        All methods marked with 'Entry point' has to have a lock at the beginning. These entry
 *        points must NOT be used internally, otherwise a deadlock occurs.
 */
class RspTarget
{
public:
    /// List of addresses in a codal stack trace
    typedef std::vector<codasip_address_t> CodalCallStack;

    /**
     * \brief Constructor
     */
    RspTarget();
    /**
     * \brief Destructor
     */
    virtual ~RspTarget();
    /**
     * \brief Read one resource (register, signal, port)
     * \param[in] tid Thread ID
     * \param[out] data Output data
     * \param[in] dwarf Dwarf index of the register
     * \return True, if the register was read properly
     */
    virtual bool ResourceRead(MaxUint& data, const Tid tid, const Did dwarf) const = 0;
    /**
     * \brief Write one resource (register, signal, port)
     * \param tid Thread ID
     * \param dwarf Dwarf index of the resource
     * \param data Data to be written
     * \return True, if the register was written properly
     */
    virtual bool ResourceWrite(const Tid tid, const Did dwarf, const MaxUint& data) = 0;
    /**
     * \brief Read one byte from memory
     * \param[out] byte Byte from the memory
     * \param[in] tid Thread ID
     * \param[in] dwarf Resource that is used for a reading (e.g. address space, interface, ...)
     * \param[in] address Address to the memory
     * \return True, if the memory was read properly
     */
    virtual bool
    MemoryRead(MaxUint& byte, const Tid tid, const Did dwarf, const codasip_address_t address) const = 0;
    /**
     * \brief Write one byte from memory
     * \param tid Thread ID
     * \param dwarf Resource that is used for a reading (e.g. address space, interface, ...)
     * \param address Address to the memory
     * \param byte Byte to be written to the memory
     * \return True, if the memory was written properly
     */
    virtual bool
    MemoryWrite(const Tid tid, const Did dwarf, const codasip_address_t address, const MaxUint& byte) = 0;
    /**
     * \brief Invalidate and flush cache to commit memory write operations made by the debugger.
     */
    virtual void CommitMemoryWrites() = 0;
    /**
     *  \brief  Halt simulator execution
     *  \note   It must be non-blocking
     */
    virtual bool Kill() = 0;
    /**
     *  \brief  Reset the simulator execution
     *  \note   It must be non-blocking
     */
    virtual int Reset() = 0;
    /**
     * \brief  Get number of clock cycle out of the target
     */
    virtual uint64_t GetCycleCount() const = 0;
    /**
     * \brief  Tell profiler to dump current data to file
     */
    virtual bool DumpProfiler(const uint64_t cycleCounter) = 0;

    /**
     * \brief Return RSP Json
     */
    virtual const std::string& GetRspJson() const = 0;
    /**
     *  \brief  Controls of single logging type logging for simulator.
     *  \param  options Options setting enabled logging type verbosity levels. Format:
     *          0,1,2-3,-4,5+,h,q<1000:
     *          0  : enable single type
     *          2-3: enable range
     *          -4 : disable single type
     *          5+ : enable all types from 5 up including 5
     *          h  : enable printing of headers for prints as well
     *          q<1000: suppress/silent prints until 1000. clock cycle. The
     *          1000. clock cycle triggers the prints.
     *  \note   see codasip_interface.h
     */
    virtual void SetLogging(const char* options) = 0;
    /**
     * \brief Regiter RSP server in which the target is registered
     * \param server RSP server
     */
    void Register(RspServer& server);
    /**
     *  \brief  Change breakpoint in given ASIP instance
     *  \note   Entry point
     *  \param  info Information about breakpoint to change. Contains address and state
     *          of the breakpoint to set (enable/disable).
     */
    bool UpdateBreakpoint(const BreakpointInfo& info);
    /**
     *  \brief  Change trigger module configuration in the model for a breakpoint.
     *  \param  info Information about breakpoint to change. Contains address and state
     *          of the breakpoint to set (enable/disable).
     */
    virtual bool UpdateBreakpointCallback(const BreakpointInfo& info);
    /**
     *  \brief  Update configuration registers before resume (step, continue) if necessary.
     */
    virtual void BeforeResumeCallback();
    /**
     *  \brief  Empty body, called after interrupt from debugger, overriden by generated code in sim
     */
    virtual void AfterInterruptCallback();
    /**
     *  \brief  Change data/address watchpoint (hit when given addres is read/written) in given ASIP
     *          instance
     *  \note   Entry point
     *  \param  info Information about watchpoint to change. Contains address/data and state
     *          of the watchpoint to be set (enable/disable).
     */
    virtual bool UpdateWatchpoint(const WatchpointInfo& info);
    /**
     *  \brief  Resume ASIP execution and all its threads. Undefined behavior when given ASIP
     *          instance is not suspended.
     *  \note   It must be non-blocking
     *  \note   Entry point
     */
    bool Resume(const ResumeInfo& info);
    /**
     *  \brief  Interrupt ASIP execution and all its threads. When its already interrupted, no
     *          action is performed.
     *  \note   It must be non-blocking
     *  \note   Entry point
     */
    bool Interrupt(const Tid tid);
    /**
     *  \brief  Getter for step mode
     */
    bool IsStepMode() const;
    /**
     *  \brief  Set debugging level for given ASIP instance. Controls where execution will
     *          be suspended (HandleEvent will be called) when step mode is enabled.
     *  \note   Entry point
     *  \param  level Debugging level to be set
     */
    void SetDebugLevel(const DebugLevel debugLevel);
    /**
     * \brief Return state change info
     * \note  Entry point
     */
    const StateChangeInfo& GetStateChangeInfo() const;
    /**
     * \brief Return current thread id
     * \note  Entry point
     */
    Tid GetTid() const;
    /**
     * \brief Return codal stack trace address list
     * \note  Entry point
     */
    const CodalCallStack& GetCodalCallStack() const;
    /**
     * \brief Return true, if the SW breakpoints are supported
     * \note  Entry point
     */
    bool IsSoftwareBreakpoint() const;

protected:
    /// bytes of instructions for SW break
    typedef std::vector<MaxUint> Instruction;
    /// List of addresses in a codal stack trace [size](bytes, dwarf for patching)
    typedef std::map<unsigned, std::pair<Instruction, Did>> BreakpointInstructions;

    /// When OCD is present, the Nexus or RISC-V Debug block changes it's states accordingly
    typedef enum
    {
        /// default mode after reset
        OCD_USER_MODE,
        /// end of debug mode
        OCD_USER_WAIT,
        /// request to enter debug mode
        OCD_DEBUG_MODE,
        /// CPU is not ready to ender debug mode
        OCD_DEBUG_WAIT,
    } OcdState;

    typedef enum
    {
        /// source was hw break (Nexus client)
        OCD_HW_BREAK_REQUEST,
        /// source was sw break (CPU)
        OCD_SW_BREAK_REQUEST_CONFIRMED,
        /// source was sw break, not sure whether it is a syscall or not
        OCD_SW_BREAK_REQUEST_SYSCALL,

    } OcdSource;

    typedef enum
    {
    	/// No step mode
    	STEP_MODE_NONE = 0,
		/// Clock cyle mode
		STEP_MODE_CYCLE = 1,
		/// Standard step mode (instruction, codal, ...)
		STEP_MODE_STANDARD,
    } StepMode;

    /**
     * \brief Check whether there is a need for state change (e.g. hit breakpoint, stepmode, ...)
     *        and if so, it notifies the RSP server and suspends simulation thread
     *        This version is used when OCD is NOT preset
     * \note  Entry point
     * \param address Current address
     * \param tid Current thread
     * \param debugLevel Current debug level of the check
     */
    void UpdateStateChangeAndInterrupt(const Tid tid,
        const codasip_address_t address,
        const DebugLevel debugLevel);

    /**
     * \brief Check whether there is a need for state change in the case of clock cycle
     *        step
     *        This version is used with or without OCD
     * \note  Entry point
     * \param address Current address
     * \param tid Current thread
     * \param debugLevel Current debug level of the check
     */
    void UpdateStateChangeAndInterruptClockCycle(const Tid tid,
        const codasip_address_t address,
        const DebugLevel debugLevel);

    /**
     * \brief Check whether there is a need for state change (e.g. hit breakpoint, stepmode, ...)
     *        and if so, it notifies the RSP server and suspends simulation thread.
     *        This verison is used when OCD/Nexus is present
     * \note  Entry point
     * \param tid Current thread
     * \param address Current address
     * \param valid Instruction address is valid
     * \param syscall Address for a syscalls
     * \param swBreakRequest SW break request
     */
    void UpdateStateChangeAndInterruptNexus(const codasip_address_t instructionAddress,
        const bool instructionValid,
        const bool swBreakRequest,
        const codasip_address_t syscall,
        const Tid tid,
        const DebugLevel debugLevel);
    /**
     * \brief Check whether there is a need for state change (e.g. hit breakpoint, stepmode, ...)
     *        and if so, it notifies the RSP server and suspends simulation thread.
     *        This verison is used when RISC-V Debug Module is present
     * \note  Entry point
     * \param address Current address
     * \param hwBreakRequest HW break request from trigger module
     * \param swBreakRequest SW break request
     * \param syscall Address for syscalls
     * \param tid Current thread
     * \param debugLevel Current debug level of the check
     */
    void UpdateStateChangeAndInterruptRiscv(const codasip_address_t instructionAddress,
        const codasip_address_t syscall,
        const bool hwBreakRequest,
        const bool swBreakRequest,
        const Tid tid,
        const DebugLevel debugLevel);
    /**
     * \brief Update the state change variable and sends the notification to the RSP server
     * \note  Entry point
     * \param rc Simulator return code
     * \param address Current program counter
     */
    void UpdateStateChangeAndNotify(const simulator::SimulatorReturnCode rc,
        const codasip_address_t address);
    /**
     * \brief Enable watchpoints in the RSP Target
     * \note  Entry point
     */
    void EnableWatchpoints();
    /**
     * \brief Add opcode for a SW break instruction
     * \param instruction SW break instruction
     * \param asDwarf Dwarf that should be used for patching of the instruction
     * \note  Entry point
     */
    void AddSoftwareBreakpoint(const Instruction& instruction, const Did asDwarf);

    bool IsRunning() const;

    bool IsEbreakInterruptDisabled() const;
    void SetDisableEbreakInterrupt(const bool disableEbreakInterrupt);

    /// Current debug level
    DebugLevel m_DebugLevel = DEBUG_LEVEL_CODAL;
    /// flag handling enabling the step mode
    std::atomic<StepMode> m_StepMode;
    /// flag handling halt request from the RISC-V Debug Module
    bool m_HaltReq = false;
    /// Fast map for a breakpoint detection
    std::unordered_map<codasip_address_t, bool> m_HardwareBreakpoints;
    /// Map of software breakpoints [address](bytes, dwarf for patching)
    std::unordered_map<codasip_address_t, std::pair<Instruction, Did>> m_SoftwareBreakpoints;
    /// Watchpoints
    RspWatchpoints* m_Watchpoints = nullptr;
    /// Fast map for codal breakpoint detection
    std::unordered_map<codasip_address_t, bool> m_CodalBreakpoints;
    /// Mutex that is used for suspending or resuming the simulation thread
    mutable std::mutex m_Mutex;
    /// Condition variable that wakes up a suspended thread
    mutable std::condition_variable m_Thread;
    /// Current thread id
    Tid m_Tid = TID_DEFAULT;
    /// Current Nexus state
    OcdState m_OcdState = OCD_USER_MODE;
    /// Nexus source
    OcdSource m_OcdSource = OCD_HW_BREAK_REQUEST;
    /// Nexus Enable port
    bool m_NexusEnable = false;
    /// Nexus HwBreakRequest port
    bool m_NexusHwBreakRequest = false;
    /// Current codal stack
    CodalCallStack m_CodalCallStack;
    /// Information for the last state change
    StateChangeInfo m_StateChangeInfo;
    /// Value of the software breakpoint
    BreakpointInstructions m_BreakpointInstructions;

private:
    virtual void OcdSysCall(const codasip_address_t);
    void NotifyStateChange();
    bool UpdateStateChangeHandleWatchpoints(const Tid, const DebugLevel);
    void UpdateStateChangeHandleStep(const Tid, const codasip_address_t, const DebugLevel);
    bool UpdateStateChangeHandleHwBreak(const Tid, const codasip_address_t, const DebugLevel);
    bool UpdateStateChange(const Tid, const codasip_address_t, const DebugLevel);
    bool UpdateStateChangeNexus(const Tid, const codasip_address_t, const DebugLevel);
    bool UpdateStateChangeRiscv(const Tid, const codasip_address_t, const DebugLevel);
    bool UpdateStateChange(const simulator::SimulatorReturnCode, const codasip_address_t);
    void Suspend();
    void Wakeup();
    RspInterpreter& GetInterpreter();
    RspServer& GetServer();
    bool AddSoftwareBreakpoint(const BreakpointInfo&);
    bool RemoveSoftwareBreakpoint(const BreakpointInfo&);

    /// Pointer to the server, it is used for a asynchronous notification about state
    RspServer* m_Server = nullptr;
    /// flag to disable dcsr ebreakX manipulation on risc-v debug targets
    bool m_DisableEbreakInterrupt = false;
};

}   // namespace debugger
}   // namespace codasip

#endif   // SIMULATOR_RSPL_RSP_TARGET_H_
