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
 *  \date   Nov 1, 2014
 *  \brief
 */

#ifndef LICAPP_H_
#define LICAPP_H_

#include <vector>
#include <string>

namespace codasip {
namespace lmx {

class Watermark;

typedef enum
{
    LMX_UNKNOWN,

    // generators
    LMX_GEN_ASSEMBLER,
    LMX_GEN_DISASSEMBLER,
    LMX_GEN_COMPILER,
    LMX_GEN_RTL,
    LMX_GEN_FVE,
    LMX_GEN_PROFILER_IA,
    LMX_GEN_PROFILER_CA,
    LMX_GEN_SIMULATOR_IA,
    LMX_GEN_SIMULATOR_CA,

    // fixed toools
    LMX_MW,
    LMX_LINKER,
    LMX_CODALC,
    LMX_CMDLINE,
    LMX_IDE,
    LMX_SEMEXTR,

    // exported SDK
    LMX_ASSEMBLER,
    LMX_COMPILER,
    LMX_COMPILER_DEBUG,
    LMX_DISASSEMBLER,
    LMX_SIMULATOR,
    LMX_PROFILER,

    LMX_COUNT
} LicenseFeature;

/**
 * \brief Checkin license for a given feature (return to the pool)
 * \param feature Feature id
 */
void ProtectorCheckIn(const LicenseFeature feature);
/**
 * \brief Check that the watermark of the model is the same as in the license. An exception is
 *        thrown.
 * \param watermark Watermark of the current model
 */
void ProtectorWatermark(const LicenseFeature feature, const Watermark& watermark);
/**
 * \brief Checkout license for a given feature (take it from the pool)
 * \param feature Feature id
 */
void ProtectorCheckOut(const LicenseFeature feature);

/**
 * \brief Check that there is a license for a feature. The license is immediately returned back
 *        to the pool.
 * \param feature Feature id
 */
void ProtectorSdk(const LicenseFeature feature);

/**
 * \brief Check that there is a license for a feature. The license is immediately returned back
 *        to the pool. The difference from ProtectorSdk is that the check is not conditioned with
 *        any macro.
 * \param feature Feature id
 */
void ProtectorSdkDebugSources(const LicenseFeature feature);

/**
 * \brief Return licensee string
 *
 * \param feature Feature id
 */
std::string ProtectorLicensee(const LicenseFeature feature);

}   // lmx
}   // codasip

#endif /* LICAPP_H_ */
