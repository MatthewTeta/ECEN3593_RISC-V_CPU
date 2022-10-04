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
 *  \author Tomas Ondrus
 *  \date   Mar 30, 2015
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef GETOPTL_INTERFACE_OPTIONSSIM_H_
#define GETOPTL_INTERFACE_OPTIONSSIM_H_

#include "common/codasip_integer.h"
#include "getoptl/interface/basicoptions.h"
#include "utility/stringutils.h"

#include <map>
#include <set>

namespace codasip {
namespace getopt {

/// Container for options for logging
typedef std::string LogTypeOptions;

/**
 * \brief Options for starting of simulation.
 */
class SimulatorOptions : public virtual BasicOptions
{
public:
    /**
     * \class SimulatorOptions::Asip
     * \brief Options for single ASIP in simulation. Specifies executable and arguments.
     *        If executable is empty, such ASIP was used in configuration but no executable was
     *        set, so we just check correct ASIP name and use global executable.
     */
    class Asip
    {
    public:
        Asip()
          : m_LoadSim(true)
        {}
        const std::string& GetExecutable() const
        {
            return m_Executable;
        }
        bool HasExecutable() const
        {
            return !m_Executable.empty();
        }
        const std::string& GetProgArgs() const
        {
            return m_ProgArgs;
        }
        bool LoadSim() const
        {
            return m_LoadSim;
        }
        void SetExecutable(const std::string& exe, const std::string& args)
        {
            m_Executable = exe;
            m_ProgArgs = args;
        }
        void SetLoadSim(const bool loadSim)
        {
            m_LoadSim = loadSim;
        }
        const LogTypeOptions& GetLogOptions() const
        {
            return m_Log;
        }
        void AppendLogOptions(const LogTypeOptions& value)
        {
            m_Log = Concatenate(m_Log, value, ",");
        }

    private:
        std::string m_Executable;
        std::string m_ProgArgs;
        bool m_LoadSim;
        LogTypeOptions m_Log;
    };

    /**
     * \class SimulatorOptions::Component
     * \brief Options for a single component in simulation. Specifies custom params.
     */
    class Component
    {
    public:
        typedef std::vector<std::string> Args;

        Component() {}
        const Args& GetArgs() const
        {
            return m_Args;
        }
        void SetArgs(const Args& args)
        {
            m_Args = args;
        }

    private:
        Args m_Args;
    };

    class DumpOptions
    {
    public:
        DumpOptions()
          : m_Load(false)
          , m_Vcd(false){};

        bool IsLoad() const
        {
            return m_Load;
        }
        bool IsVcd() const
        {
            return m_Vcd;
        }
        void SetFormat(const bool load, const bool vcd)
        {
            m_Load = load;
            m_Vcd = vcd;
        }
        const std::vector<std::string>& GetResources() const
        {
            return m_Resources;
        }
        std::vector<std::string>& GetResources()
        {
            return m_Resources;
        }

    private:
        bool m_Load;
        bool m_Vcd;
        std::vector<std::string> m_Resources;
    };

    /// Container for options (value) for ASIP of given name (key)
    typedef std::map<std::string, Asip> AsipOptions;
    /// Container for options (value) for component of given name (key)
    typedef std::map<std::string, Component> ComponentOptions;
    /// Container for dump options (value) for file (key)
    typedef std::map<std::string, DumpOptions> DumpFiles;
    ///
    typedef std::set<unsigned int> Sequences;
    /// Container for memory latencies mapping
    typedef std::map<std::pair<std::string, bool>, std::vector<size_t>> MemoryLatencies;

    virtual bool IsRunOnly() const = 0;
    virtual unsigned short GetRspPort() const = 0;
    virtual unsigned short GetLldbPort() const = 0;
    virtual bool HasRspPort() const = 0;
    virtual bool HasLldbPort() const = 0;
    virtual bool IsProfiler() const = 0;
    virtual const std::string& GetProfilerOutput() const = 0;
    virtual unsigned int GetProfilerSamplingRate() const = 0;
    virtual bool ProfilerEnabledCallStack() const = 0;
    virtual Sequences GetProfilerSequences() const = 0;
    virtual bool HasDumpClockCycles() const = 0;
    virtual const std::string& GetDumpClockCycles() const = 0;
    virtual bool GetDumpSimulatorInfo() const = 0;
    virtual bool GetDumpRspJson() const = 0;
    virtual bool ExecuteInitBatchFile() const = 0;
    virtual bool VerifyExecutables() const = 0;
    virtual uint64_t GetTimeout() const = 0;
    virtual bool HasSyscallAddress() const = 0;
    virtual bool IsEbreakInterruptDisabled() const = 0;
    virtual uint64_t GetSyscallAddress() const = 0;
    virtual const char* GetCodalParameters() const = 0;
    virtual const std::string& GetNamedPipePrefix() const = 0;
    virtual const MemoryLatencies& GetMemoryLatencies() const = 0;
    virtual bool IsInstructionTraceEnabled() const = 0;

    /**
     * \brief Get options for specific ASIPs
     */
    const ComponentOptions& GetComponentOptions() const
    {
        return m_ComponentArgs;
    }
    /**
     * \brief Get global options for all ASIPs
     */
    const Asip& GetGlobalOptions() const
    {
        return m_GlobalArgs;
    }
    /**
     * \brief Get options for dumping of resources
     */
    const DumpFiles& GetDumpFiles() const
    {
        return m_DumpFiles;
    }

    static SimulatorOptions* Create(const char* codalParametersHelp);

protected:
    ComponentOptions m_ComponentArgs;
    Asip m_GlobalArgs;
    DumpFiles m_DumpFiles;
};

}   // namespace getopt
}   // namespace codasip

#endif   // GETOPTL_INTERFACE_OPTIONSSIM_H_
