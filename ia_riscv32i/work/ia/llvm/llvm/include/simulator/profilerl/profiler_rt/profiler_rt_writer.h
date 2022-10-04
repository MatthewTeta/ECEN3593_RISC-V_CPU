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
 *  \author Pavel Richtarik
 *  \date   Nov 16, 2015
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATORS2_PROFILERL_PROFILER_RT_PROFILER_RT_WRITER_H_
#define SIMULATORS2_PROFILERL_PROFILER_RT_PROFILER_RT_WRITER_H_

#include "os/filesysteml/codasip_io.h"
#include "os/filesysteml/filesystem.h"

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace codasip {
namespace profiler {
namespace runtime {

class ProfilerRt;

class Writer
{
public:
    /// Constructor.
    Writer(const ProfilerRt& profilerRt,
        const std::time_t time,
        const std::string studioVersion,
        const std::string architecture,
        const std::string hash);

    /**
     * \brief Writes current profiler information to file
     */
    bool WriteProfilerFile(const uint64_t cyclesCount, const std::string& outputPath);

private:
    /// Internal buffer size
    static const size_t BUFFER_SIZE = 100;

    void WriteHeader();
    /**
     * \brief Write profiler footer.
     * \param cyclesCount
     */
    void WriteFooter(const uint64_t cyclesCount);
    /**
     * \brief Write call stack.
     */
    void WriteCallStackSnapshots();

    /**
     * \brief Write statistics.
     */
    void WriteStatistics();

    void WritePipelinesInfo(const ProfilerRt& profiler);
    void WriteCodalInfo(const ProfilerRt& profiler);
    void WriteCodalConditions(const ProfilerRt& profiler);
    void WriteCodalExpressions(const ProfilerRt& profiler);

    void WriteSamples(const ProfilerRt& profiler);
    void WriteDecoders(const ProfilerRt& profiler);
    void WriteInterfaces(const ProfilerRt& profiler);
    void WriteBlocks(const ProfilerRt& profiler);
    void WriteResources(const ProfilerRt& profiler);
    void WritePpa(const ProfilerRt& profiler);

    // WRITE FUNCTIONS, ENCAPSULATING BUFFERING

    template<typename T>
    void Write(const T& val);

    template<typename TCast, typename T>
    void WriteCast(const T& val);

    template<typename TVec>
    void Write(const std::vector<TVec>& vec);

    template<typename TKey, typename TMap>
    void Write(const std::map<TKey, TMap>& map);
    template<typename TKey, typename TMap>
    void Write(const std::unordered_map<TKey, TMap>& map);

    void WriteString(const std::string& str);

    /// Profilers
    const ProfilerRt& m_ProfilerRt;

    /// General info
    std::time_t m_Time;
    std::string m_StudioVersion;
    std::string m_Architecture;
    std::string m_Hash;

    /// Output stream
    io::Ofstream m_Output;
};

}   // namespace runtime
}   // namespace profiler
}   // namespace codasip

#endif   // SIMULATORS2_PROFILERL_PROFILER_RT_PROFILER_RT_WRITER_H_
