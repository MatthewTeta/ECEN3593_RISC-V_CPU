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
 *  \date   18. 9. 2018
 *  \brief  Declaration of the class codasip::profiler::ProfilerDpi.
 */

#ifndef SIMULATOR_PROFILERL_PROFILER_DPI_H_
#define SIMULATOR_PROFILERL_PROFILER_DPI_H_

#include "common/toolstypes.h"
#include "simulator/profilerl/profiler_interface.h"

namespace codasip {
namespace profiler {

/// \brief  Integer handle allowing to support multiple profiler sessions
typedef int ProfilerHandle;

/**
 *  \addtogroup PROFILERL
 *  \{
 *  \class  codasip::profiler::ProfilerDpi
 *  \brief  Implements generic profiler API with disassembler functionality only.
 *          The class is used to work with the \ref Profiler class with limited
 *          functionality. The functionality should be just parse raw trace data
 *          and dump into text format. The disassembler is used to split
 *          executed instruction address ranges into single addresses.
 *  \}
 */
class ProfilerDpi : public ProfilerInterface
{
public:
    /**
     *  \brief  Valid disassembler is returned. The actual implementation must
     *          be defined in generated code together with the DPI golden mode.
     */
    disassembler::Disassembler* GetDisassembler(const std::string&) override;
    /**
     *  \{
     *  \brief  Implements required interface without any functionality.
     */
    DecodersInterface* GetDecoders(const std::string&) override;
    const std::string& GetModelHash() const override;
    std::string GetAddressSpace(const int) const override;
    void DumpInfo(std::ostream&) const override;
    /** \} */
    /**
     *  \brief  Create and start new profiler.
     *  \param  id ASIP identifier
     *  \param  signature ASIP signature
     *  \param  hash ASIP project hash
     *  \param  output path to the profiler output file
     *  \param  executable path to the simulated executable on the ASIP
     *  \return integer handle used to reference the new profiler
     *  \retval -1 invalid profiler handle, failed to create profiler
     */
    static ProfilerHandle codasip_profiler_constructor(const char* id,
        const char* signature,
        const char* hash,
        const char* output,
        const char* executable);
    /**
     *  \brief  Stop profiling and destroy previously created profiler.
     *  \param  handle reference to the profiler handle
     *  \param  clock_cycle current clock cycle
     *  \return success flag (true OK, false ERROR)
     */
    static bool
    codasip_profiler_destructor(codasip::profiler::ProfilerHandle handle, const uint64_t clock_cycle);
    /**
     *  \brief  Create a new sample that is used for data logging.
     *  \param  handle reference to the profiler handle
     *  \param  clock_cycle current clock cycle
     *  \param  address current address of the sample
     *  \return success flag (true OK, false ERROR)
     */
    static bool codasip_profiler_create_sample(codasip::profiler::ProfilerHandle handle,
        const uint64_t clock_cycle,
        const codasip_address_t address);
    /**
     *  \brief  Commit sample, update counters for the active address.
     *  \param  address optional ending address of the sample. If zero, it is the
     *          same as the start address.
     *  \return success flag (true OK, false ERROR)
     */
    static bool codasip_profiler_commit_sample(codasip::profiler::ProfilerHandle handle,
        const codasip_address_t address);
    /**
     *  \brief  Compare two profiler outputs and indicate whether trace is identical
     *          or not.
     *  \param  project name of the ASIP project
     *  \param  goldInput file path to the first profiler output file
     *  \param  goldHash hash of the golden model project (typically IA)
     *  \param  dutInput file path to the second profiler output file
     *  \param  dutHash hash of the design under test project (typically CA/RTL)
     *  \return success flag (true IDENTICAL, false MISMATCH)
     */
    static bool codasip_profiler_compare_trace(const char* project,
        const char* goldHash,
        const char* goldInput,
        const char* dutHash,
        const char* dutInput);

protected:
    /**
     *  \brief  Creates output file holding required trace informations used for
     *          later to comparison.
     *  \param  project ASIP project name
     *  \param  hash hash of the ASIP project
     *  \param  input path to the source profile to parse and process
     *  \return path to the trace output file
     */
    static std::string
    PrepareTraceComparisonFile(const char* project, const char* hash, const char* input);
};

}   // namespace profiler
}   // namespace codasip

#endif   // SIMULATOR_PROFILERL_PROFILER_DPI_H_
