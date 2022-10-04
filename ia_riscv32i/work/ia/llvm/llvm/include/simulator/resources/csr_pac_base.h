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
 *  \date   10. 4. 2019
 *  \brief  Definition of the class codasip::resources::PacBase.
 */

#ifndef SIMULATOR_RESOURCES_CSR_PAC_BASE_H_
#define SIMULATOR_RESOURCES_CSR_PAC_BASE_H_

#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_payload_sentinel.h"
#include "simulator/simbase/simulator_log.h"   // LOG
#include "utility/codasiputils.h"              // BitMask
#include "utility/stringutils.h"               // codasip::WriteList

#include <algorithm>   // std::find
#include <sstream>     // std::ostringstream

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::PacBase
 *  \brief  Represents base class for all bus Protocol Access Checker classes.
 *          Contains common reporting and utility code.
 *  \}
 */
class PacBase
{
public:
    /**
     *  \brief  Check out-of-range access on a memory.
     *  \param  p source transaction informations to check
     *  \param  mem memory storage type doing the check
     */
    template<class _Pt, class _Rt>
    static void check_address(Payload<_Pt>& p, const _Rt& mem);

protected:
    /**
     *  \brief  Implements common access checks which should be done on the
     *          master and slave interface side.
     *  \param  p source transaction informations to check
     *  \param  itf resource doing the check
     *  \param  isBlocking indicates whether blocking (IA) or transport (CA) access
     *          is handled
     *  \param  isReadable indicates whether the resource supports read access or not
     *  \param  isWriteable indicates whether the resource supports read access or not
     *  \param  isWriteAccess indicates whether write (true) or read (false) access
     *          is being checked
     *  \param  offset address offset
     *  \param  bc actual transfer size in bytes
     */
    template<class _Pt, class _Rt>
    static void DoCheckAccess(Payload<_Pt>& p,
        const _Rt& itf,
        const bool isBlocking,
        const bool isReadable,
        const bool isWriteable,
        const bool isWriteAccess,
        const Index bc);
    /**
     *  \brief  Indicates whether transfer size is supported or not.
     *  \param  bc transfer size in bytes
     *  \param  a mask of allowed alignments
     */
    static bool IsDataAlignmentError(const Index bc, const Index alignmentMask);
    /**
     *  \brief  Indicates whether transfer size is supported by the debug access
     *          functions or not.
     *  \param  bc transfer size in bytes
     *  \param  bpw number of bytes per word
     */
    static bool IsDataAlignmentErrorDebug(const Index bc, const Index bpw);
    /**
     *  \brief  Indicates whether address offset is not aligned with the transfer size.
     *  \param  offset address offset
     *  \param  bc transfer size in bytes (must be non-zero, power of 2)
     */
    static bool IsAddrOffsetAlignmentError(const Index offset, const Index bc);
    /**
     *  \brief  Generate error message when unsupported access type is requested
     *          (write access on read-only interface).
     *  \param  itf CodAL interface which detected the error
     *  \param  isWriteAccess unsupported access type, true for write, false for read
     */
    static void LogUnsupported(const Sentinel& itf, const bool isWriteAccess);
    /**
     *  \brief  Generate error message for out-of-range access.
     *  \param  itf CodAL interface which detected the error
     *  \param  addr requested address causing the error
     *  \param  size size of the array
     */
    static void
    LogOOR(const Sentinel& itf, const codasip_address_t addr, const codasip_address_t size);
    /**
     *  \brief  Generate error message for data alignment violation.
     *  \param  itf CodAL interface which detected the error
     *  \param  bc byte count/transfer size causing the error
     *  \param  align container holding allowed data alignment in bytes
     */
    static void
    LogDataAlignment(const Sentinel& itf, const Index bc, const detail::DataAlignment& align);
    /**
     *  \brief  Generate error message for address alignment violation.
     *  \param  itf CodAL interface which detected the error
     *  \param  logType type of logging message (e.g. warning/error)
     *  \param  addr requested address causing the error
     *  \param  addressAlignment allowed address alignment in bytes
     */
    static void LogAddressAlignment(const Sentinel& itf,
        const simulator::LogType logType,
        const codasip_address_t addr,
        const codasip_address_t addressAlignment);
    /**
     *  \brief  Create container holding all legal data alignment values for
     *          given byte count.
     *  \param  bpw number of bytes per word
     */
    static detail::DataAlignment CreateFullDataAlingment(const Index bpw);
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class _Pt, class _Rt>
RES_INLINE void PacBase::check_address(Payload<_Pt>& p, const _Rt& mem)
{
    if (p.is_error())
    {   // propagate error
        return;
    }
    else if (p.get_address() >= mem.get_size())
    {   // out-of-range
        LogOOR(mem, p.get_address(), mem.get_size());
        p.set_error(true);
    }
    else
    {   // everything good, no need to update response flag
    }
}

////////////////////////////////////////////////////////////////////////////////
//                            Protected interface                             //
////////////////////////////////////////////////////////////////////////////////
template<class _Pt, class _Rt>
RES_INLINE void PacBase::DoCheckAccess(Payload<_Pt>& p,
    const _Rt& itf,
    const bool isBlocking,
    const bool isReadable,
    const bool isWriteable,
    const bool isWriteAccess,
    const Index bc)
{
    const bool isDebug = isBlocking && p.is_debug_access();
    if (p.is_error())
    {   // propagate error
        return;
    }
    else if (isDebug)
    {
        if (IsDataAlignmentErrorDebug(bc, _Rt::BPW))
        {   // check byte count for debug access
            LogDataAlignment(itf, bc, CreateFullDataAlingment(_Rt::BPW));
            p.set_error(true);
        }
    }
    else if ((!isReadable && !isWriteAccess) || (!isWriteable && isWriteAccess))
    {   // unsupported command
        LogUnsupported(itf, isWriteAccess);
        p.set_error(true);
    }
    else if (isBlocking)
    {
        if (IsDataAlignmentError(bc, itf.get_data_alignment_mask()))
        {   // check data alignment in IA mode only
            // in CA is it not required to have byte count set correctly
            // because all transfers are word-wide by default and WSTRB is used instead of BC
            LogDataAlignment(itf, bc, itf.get_data_alignment());
            p.set_error(true);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
RES_INLINE bool PacBase::IsDataAlignmentError(const Index bc, const Index alignmentMask)
{
    //Determine if matches data alignment mask
    return !(IsPowerOfTwo(bc) && (bc & alignmentMask));
}

////////////////////////////////////////////////////////////////////////////////
RES_INLINE bool PacBase::IsDataAlignmentErrorDebug(const Index bc, const Index bpw)
{
    // A full mask contains all bits set from LSB to BPW included
    return IsDataAlignmentError(bc, bpw * 2 - 1);
}

////////////////////////////////////////////////////////////////////////////////
RES_INLINE bool PacBase::IsAddrOffsetAlignmentError(const Index offset, const Index bc)
{
    return ((offset & (bc - 1)) != 0);
}

////////////////////////////////////////////////////////////////////////////////
inline void PacBase::LogUnsupported(const Sentinel& itf, const bool isWriteAccess)
{
    LOG(itf.get_log(), simulator::LOG_TYPE_ERROR, 0)
        << "'" << itf.get_signature() << "': Interface does not support '"
        << (!isWriteAccess ? "read" : "write") << "' access, defined as '"
        << (isWriteAccess ? "read" : "write") << "-only'.";
}

////////////////////////////////////////////////////////////////////////////////
inline void
PacBase::LogOOR(const Sentinel& itf, const codasip_address_t addr, const codasip_address_t size)
{
    LOG(itf.get_log(), simulator::LOG_TYPE_ERROR, 0)
        << "'" << itf.get_signature() << "': Address '0x" << std::hex << addr
        << "' is out-of-range, max address is '0x" << (size - 1) << "'.";
}

////////////////////////////////////////////////////////////////////////////////
inline void
PacBase::LogDataAlignment(const Sentinel& itf, const Index bc, const detail::DataAlignment& align)
{
    std::ostringstream values;
    ::codasip::WriteList(values, align.begin(), align.end(), "', '");

    LOG(itf.get_log(), simulator::LOG_TYPE_ERROR, 0)
        << "'" << itf.get_signature() << "': Data alignment broken, byte count '" << bc
        << "' is not allowed. Allowed values in bytes: '" << values.str() << "'.";
}

////////////////////////////////////////////////////////////////////////////////
inline void PacBase::LogAddressAlignment(const Sentinel& itf,
    const simulator::LogType logType,
    const codasip_address_t addr,
    const codasip_address_t align)
{
    LOG(itf.get_log(), logType, 0)
        << "'" << itf.get_signature() << "': Address alignment broken, address '0x" << std::hex
        << addr << "' is not aligned to '" << std::dec << align << "' bytes.";
}

////////////////////////////////////////////////////////////////////////////////
inline detail::DataAlignment PacBase::CreateFullDataAlingment(const Index bpw)
{
    detail::DataAlignment dataAlignment;
    for (Index ii = 1; ii <= bpw; ii *= 2)
    {
        dataAlignment.push_back(ii);
    }
    return dataAlignment;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_PAC_BASE_H_
