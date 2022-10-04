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
 *  \author Hons Petr
 *  \date   6. 10. 2015
 *  \brief
 */

#ifndef _SIMULATOR_PRIVATE_H_
#define _SIMULATOR_PRIVATE_H_

#include "common/toolstypes.h"   // profiler types
#include "simulator/simbase/codasip_interface.h"
#include "simulator/simbase/simulator_resources.h"

// forward
namespace codasip {
namespace disassembler {
class Disassembler;
}   // namespace disassembler
namespace simulator {
class DumpStream;
namespace codal {
class DebugInfo;
}
}   // namespace simulator
}   // namespace codasip

namespace codasip {
namespace simulator {
/**
 *  \class  SimulatorPrivateInterface
 *  \brief  Abstract simulator interface implemented by simulators. This private interface
 *          is used by Codasip debugger
 */
class SimulatorPrivateInterface
  : public SimulatorInterface,   // public interface available outside of Codasip tools
    public ComponentBase         // Base class for all component based instances
{
public:
    /// Enum describing simulator features
    typedef enum
    {
        /// IA simulator
        SIMULATOR_IA = 0,
        /// CA simulator
        SIMULATOR_CA = 1,
        /// Support of debugging
        DEBUGGER = SIMULATOR_CA << 1,
        /// CodAL debugging
        CODAL = DEBUGGER << 1,
        /// Support for watchpoints
        WATCHPOINTS = CODAL << 1,
        /// Support for dumping
        DUMP = WATCHPOINTS << 1,
        /// Low profiler
        PROFILER_LOW = DUMP << 1,
        /// High profiler
        PROFILER_HIGH = PROFILER_LOW << 1,
        /// Stack overflow detection
        STACK_OVERFLOW_CHECK = PROFILER_HIGH << 1,
        /// Support of Nexus/JTAG
        NEXUS = STACK_OVERFLOW_CHECK << 1,
        /// Support of Syscalls
        SYSCALL = NEXUS << 1,
        /// Support of RISC-V Debug
        RISCV_DEBUG = SYSCALL << 1
    } Features;
    /**
     * \brief  Describes mandatory resources for ASIP simulator
     */
    struct AsipInfo
    {
        AsipInfo();

        /// Program counter description
        RegisterInfo* m_Pc;
        /// Default data address space description
        AddressSpaceInfo* m_DataAs;
        /// Default program address space description
        AddressSpaceInfo* m_ProgramAs;
    };

    /// type for staring latencies <resource, read/write> -> values
    typedef std::map<std::pair<std::string, bool>, std::vector<size_t>> LatencyMapping;

    /**
     * \brief Needed for correct function overload
     * \{
     */
    using ComponentBase::ResourceRead;
    using ComponentBase::ResourceWrite;
    using SimulatorInterface::ResourceRead;
    using SimulatorInterface::ResourceWrite;
    /**
     * \}
     */
    /**
     * \brief Get simulator features
     */
    virtual Features GetFeatures() const = 0;
    /**
     * \copydoc SimulatorInterface::GetPath
     * \note Needed because same function is implemented in both SimulatorInterface and ComponentBase
     */
    virtual const char* GetPath() const override = 0;
    /**
     *  \brief  Run until all simulators ends.
     */
    virtual int Run() = 0;
    /**
     *  \brief  Returns profiling statistics for given resource. If the resource is addressable
     *          then address must be provided.
     *  \param  resource UID of resource
     *  \param  type Type of profiling statistics to be returned.
     *  \param  address Address (default 0)
     *  \return Count of accesses of given \p type on resource \p name at given \p address
     */
    virtual uint64_t ResourceStats(const Uid resource,
        const profiler::AccessType type,
        const Address address = 0) const = 0;
    /**
     *  \brief  Load program into the memory according processor address space
     *          If the bw of the word is specified, it checks, if the destination
     *          memory has proper bit-width. The -1 means "do not check bw".
     *  \param  addressSpace Uid of address space the data will be loaded into
     *  \param  data Data
     *  \param  addr Address
     *  \param  bc byte count
     *  \param  isText if true, loaded data represents program
     *  \param  bw bw of data
     */
    virtual void LoadProgram(const Uid addressSpace,
        const MaxInt& data,
        const Address addr,
        const unsigned int bc,
        const bool isText,
        const int bw = -1) = 0;
    /**
     *  \brief  Save executable path. Mandatory for correct OProfile data generation
     *  \param  executable Path to the executable file
     */
    virtual void SetExecutable(const std::string& executable) = 0;
    /**
     *  \brief  Controls stack overflow checking of simulator
     *  \param  enable True if stack overflow checking should be enabled, false otherwise
     *  \param  main Address of main symbol. After PC hits this address checking is enabled
     *  \param  low Lowest address of stack
     *  \param  high Highest address of stack
     */
    virtual void StackOverflowCheck(const bool enable,
        const Address main = 0,
        const Address low = 0,
        const Address high = 0) = 0;
    /**
     *  \brief  Dump resources into the file
     *  \param  resources List of resource UIDs to be dumped. If empty, all resources will be dumped.
     *  \param  file File to be dumped to
     *  \param  format Format to be dumped to. Currently "codasip" only. If empty, default Codasip
     *          dump format will be used.
     *  \return Success of dump
     */
    virtual bool
    Dump(DumpStream& stream, const std::vector<Uid>& resources, const bool continuous = false) = 0;
    /**
     *  \brief  Restore dumped resources values from file
     *  \param  file File containing dumped data.
     *  \param  format Format to be dumped to. Currently "codasip" only. If set to empty,
     *          automatic detection of format will be performed.
     *  \return Success of dump
     */
    virtual bool Restore(std::istream& file,
        const bool continuous = false,
        const std::string& format = std::string()) = 0;
    /**
     * \brief Get information about ASIP simulator
     * \param pcUID UID of program counter
     * \param programAsUID UID of program address space
     * \param dataAsUID UID of data address space
     */
    virtual bool GetAsipInfo(Uid* = nullptr, Uid* = nullptr, Uid* = nullptr) const
    {
        return false;
    }
    /**
     * \brief Return CodAL debug info container containing line table, debug information
     *        (block,variables,etc.) and current CodAL callstack
     */
    virtual const codal::DebugInfo* GetCodalDebugInfo() const
    {
        return nullptr;
    }
    /**
     * \brief  Sets the trace mode (only in JTAG simulator)
     * \param  onOff True if trace mode should be enabled
     * \param  trigger True if trace mode should not be changed right away, but trigger stoppoint should be used
     * \param  watchpoint True if trigger stoppoint is watchpoint, fals if it is breakpoint.. If trigger is false and watchpoint is true, the trigger is disabled
     * \param  addr Address of stoppoint to trigger the trace mode
     * \return True if trace mode was successfully set
     */
    virtual bool TraceEnable(const bool onOff,
        const bool trigger,
        const bool watchpoint = false,
        const codasip_address_t addr = 0)
    {
        UNUSED(onOff);
        UNUSED(trigger);
        UNUSED(watchpoint);
        UNUSED(addr);
        return false;
    }
    /**
     * \brief  Returns data address space of ASIP
     * \throws if data address space was not specified or found
     */
    const AddressSpaceInfo& GetDataAddressSpace() const;
    /**
     * \brief  Returns program address space of ASIP
     * \throws if program address space was not specified or found
     */
    const AddressSpaceInfo& GetProgramAddressSpace() const;
    /**
     * \brief  Returns program counter description
     * \throws if program counter was not found
     */
    const RegisterInfo& GetProgramCounter() const;
    /**
     * \brief Dump simulator hierarchy info as XML data that will be printed into \p out
     */
    void DumpHierarchyToXml(std::ostream& out) const;
    /**
     * \brief Saves a symbol to the simulator
     * \param address Address
     * \param name Symbol name
     */
    virtual void LoadSymbol(const Address address, const std::string& name) = 0;
    /**
     * \brief Return RSP JSON
     */
    virtual const std::string& GetRspJson() const;
    /**
     * \brief Return an instance of a disassembler for a given simulator
     */
    virtual disassembler::Disassembler& GetDisassembler() = 0;
    /**
     * \brief Disable ebreak interrupts on RISC-V targets.
     * \param disableEbreakInterrupt If true ebreak interrupts will be disabled. The ebreakX bits will be left in their default values.
     */
    virtual void SetDisableEbreakInterrupt(const bool disableEbreakInterrupt);
    /**
     * \brief Set specified memory latencies
     * \param latencies read and write latencies for memories and thier interfaces
     */
    virtual void SetMemoryLatencies(const LatencyMapping& latencies);
    /**
     * \brief Enable or disable printing of instruction trace from simulator
     * \param instructionTrace If true the printing is enabled, if false it is disabled
     */
    virtual void SetInstructionTraceEnabled(const bool instructionTrace);
};

/**
 *  \brief  Class that loads all ASIPs from the simulator info to be used for application loading.
 */
class Design
{
public:
    /// Description of a single resource (ASIP or Component)
    template<class T>
    struct Info
    {
        /// Name of ASIP, can be also alias (without toplevel simulator name)
        Path m_Name;
        /// Resource (simulator/component instance)
        T* m_Resource;
        /// True if \p m_Name is alias
        bool m_Alias;
    };

    typedef Info<SimulatorPrivateInterface> AsipInfo;
    typedef Info<Component> ComponentInfo;

    typedef std::vector<ComponentInfo> ComponentInfos;

    /**
     *  \brief  Constructor
     *  \param  sim ASIP simulator interface
     */
    Design(SimulatorPrivateInterface& sim);
    /**
     *  \{
     *  \brief  Get infos
     */
    const AsipInfo& GetAsipInfo() const;
    const ComponentInfos& GetComponentInfos() const;
    /**
     *  \}
     */
    /**
     *  \brief  Load executables to destination - debugger or simulator directly
     */
    template<class Destination, class Options>
    void LoadExecutables(Destination& dest, const Options& args);
    /**
     * \brief Print clock cycle info
     * \param log Path to the output file, or empty for printing to stdout
     */
    void DumpClockCycles(const std::string& log);
    /**
     * \brief Dump profiler file
     * \details Used for dumping profiler info on receiving signal
     */
    void DumpProfiler();

private:
    /// Load single simulator info
    void Load(SimulatorPrivateInterface& sim);

    void Load(SimulatorPrivateInterface& dest,
        SimulatorPrivateInterface& sim,
        const std::string& exe,
        const std::string& args,
        const bool load);

    /// Single ASIP infos
    AsipInfo m_AsipInfo;
    /// List of component infos
    ComponentInfos m_ComponentInfos;
    /// Toplevel simulator
    SimulatorPrivateInterface& m_Top;
};

/**
 * \brief Load executable set in arguments into destination (simulator or debugger)
 * \param dest Simulator or debugger that will be used to load executable using
 *             LoadExecutable method
 * \param asipNames Container of ASIP names in simulator
 * \param args Arguments set by user to run simulator
 * \return Return true on success, false on error
 */
template<class Destination, class Options>
void Design::LoadExecutables(Destination& dest, const Options& args)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Load executables
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // use global options
    if (args.GetGlobalOptions().HasExecutable())
    {
        Load(dest,
            *GetAsipInfo().m_Resource,
            args.GetGlobalOptions().GetExecutable(),
            args.GetGlobalOptions().GetProgArgs(),
            args.GetGlobalOptions().LoadSim());
    }
    // no application found and we are not using debugger
    else if (args.IsRunOnly())
    {
        THROW_ERROR() << "No executable set for ASIP " << GetAsipInfo().m_Name << std::endl;
    }
}

}   // namespace simulator
}   // namespace codasip

#endif   // _SIMULATOR_PRIVATE_H_
