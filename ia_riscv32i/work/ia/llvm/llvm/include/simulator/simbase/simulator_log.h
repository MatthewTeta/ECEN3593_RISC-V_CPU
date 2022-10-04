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
 *  \author Hons
 *  \date   10. 5. 2016
 *  \brief  Declaration of the class codasip::simulator::Log.
 */

#ifndef SIMULATORS2_SIMBASE_SIMULATOR_LOG_H_
#define SIMULATORS2_SIMBASE_SIMULATOR_LOG_H_

#include "os/compiler.h"
#include "simulator/simbase/codasip_interface.h"

#include <sstream>
#include <vector>

/// Syntax sugar for logging
#define LOG(log, logType, ...)            \
    if (log.Header(logType, __VA_ARGS__)) \
    LogMessage(log).Stream()

namespace codasip {
namespace simulator {

/**
 *  \brief  Print standard log message start
 *  \param  logType message type (info, warning, ...)
 *  \param  verbosity verbosity
 *  \param  os stream to print to
 */
void PrintHeader(const LogType logType, const uint32_t verbosity, std::ostringstream& os);

/**
 *  \class  Log
 *  \brief  Class managing logging for single simulator
 */
class Log
{
public:
    /// Constructor
    Log(SimulatorInterface* simulator = nullptr);
    /// Destructor
    ~Log();

    /**
     *  \brief  Start new log message. If logging is enabled, true is returned
     *          and message header is created. Otherwise no header is created
     *          and false is returned. Automatically adds current clock cycle
     *          from the simulator.
     *  \param  logType message type (info, warning, ...)
     *  \param  verbosity message verbosity level
     */
    bool Header(const LogType logType, const uint32_t verbosity);
    /**
     *  \brief  Start new log message. If logging is enabled, true is returned
     *          and message header is created. Otherwise no header is created
     *          and false is returned.
     *  \param  logType message type (info, warning, ...)
     *  \param  verbosity message verbosity level
     *  \param  cc current clock cycle
     */
    bool Header(const LogType logType, const uint32_t verbosity, const uint64_t cc);
    /**
     *  \brief Finish currently creating log message
     *  \note  Priority of output: Output stream (\ref SetOutputStream), debugger, cout/cerr
     */
    void Dispatch();
    /**
     *  \brief Set output stream
     */
    void SetOutputStream(std::ostream& out);
    /**
     *  \brief Enable given types/verbosity for give log type.
     *  \param flags String describing new logging types. Format:
     *         0,1,2-3,4-,5+,h,q<X:
     *         0  : enable single type
     *         2-3: enable range
     *         -4 : disable single type
     *         5+ : enable all types from 5 up including 5
     *         h  : enable printing of headers for codasip_print as well
     *         q<1000: suppress/silent prints until 1000. clock cycle. The
     *         1000. clock cycle triggers the prints.
     */
    void SetLogging(const std::string& flags);
    /**
     *  \brief Set debugger
     */
    void SetParentLog(Log& log);
    /**
     *  \brief  Accessor to internal stream. Used in LogMessage
     */
    std::ostringstream& Stream();
    /**
     *  \brief  Return last error message
     */
    const std::string& GetLastError() const;

private:
    /**
     *  \brief Start new log message of given log type and level.
     */
    void PrintHeader(const LogType logType, const uint32_t type, const uint64_t cc);

    /// Vectors determining if given type/verbosity is enabled
    uint64_t m_EnabledType;
    /// Associated simulator. Is pointer so this class can be unittested
    SimulatorInterface* m_Simulator;
    /// Associated output stream
    std::ostream* m_Output;
    /// Parent simulator Log instance. Used to traverse error messages up
    Log* m_ParentLog;
    /// Last error message
    std::string m_LastError;
    /// number of clock cycles without any printing
    uint64_t m_SilentClockCycles;
    /// Stream where new log message is created
    std::ostringstream m_Stream;
    /// Default state (showbase, hex, dec, ...) for stream
    std::ios m_StreamDefaultState;
    /// Last successfully created header log type
    LogType m_LastLogType;
    /// True if newline should be added if logging message doesn't end on one
    bool m_AutoNewline;
    /// Indicates whether or not codasip_print() should be prefixed or not
    bool m_EnablePrintHeader;
    /// indicates whether
    bool m_LastPrintFinished;
};

/**
 *  \class  LogMessage
 *  \brief  Helper for constructing log message using stream operator <<
 */
class LogMessage
{
public:
    /// Constructor
    explicit LogMessage(Log& logger);
    /// Destructor. Will log the message
    ~LogMessage();
    /**
     * \brief Return internal stream
     */
    std::ostream& Stream();

private:
    Log& m_Logger;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline std::ostringstream& Log::Stream()
{
    return m_Stream;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline LogMessage::LogMessage(Log& logger)
  : m_Logger(logger)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline LogMessage::~LogMessage()
{
    m_Logger.Dispatch();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline std::ostream& LogMessage::Stream()
{
    return m_Logger.Stream();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
FORCE_INLINE bool Log::Header(const LogType logType, const uint32_t verbosity)
{
    return Header(logType, verbosity, m_Simulator ? m_Simulator->GetCycleCount() : 0u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
FORCE_INLINE bool Log::Header(const LogType logType, const uint32_t verbosity, const uint64_t cc)
{
    // invalid log type
    if (logType > LOG_TYPE_FATAL)
    {
        return false;
    }
    if ((cc < m_SilentClockCycles) && (logType != LOG_TYPE_FATAL))
    {   // print is suppressed except fatals until some clock cycle
        return false;
    }

    // print shares the enables with info
    LogType logType4enable = logType == LOG_TYPE_PRINT ? LOG_TYPE_INFO : logType;
    if (logType4enable >= LOG_TYPE_INFO && logType4enable <= LOG_TYPE_ERROR)
    {
        // given verbosity is disabled (note that uint64_t is used here)
        if (verbosity < 64)
        {
            if (!(m_EnabledType & (static_cast<uint64_t>(1u) << verbosity)))
            {
                return false;
            }
        }
        else
        {
            // if verbosity level outranges maximum log level (which is 64), then suppress printing
            return false;
        }
    }

    PrintHeader(logType, verbosity, cc);
    return true;
}

}   // namespace simulator
}   // namespace codasip

#endif   // SIMULATORS2_SIMBASE_SIMULATOR_LOG_H_
