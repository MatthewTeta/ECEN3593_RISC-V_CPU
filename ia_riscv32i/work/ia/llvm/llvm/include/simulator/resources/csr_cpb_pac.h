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
 *  \date   27. 11. 2018
 *  \brief  Definition of the class codasip::resources::CpbPac.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CPB_PAC_H_
#define SIMULATOR_RESOURCES_CSR_CPB_PAC_H_

#include "simulator/resources/csr_pac_base.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::CpbPac
 *  \brief  Protocol access checker for the Codasip Processor Bus.
 *  \}
 */
class CpbPac : public PacBase
{
public:
    /**
     *  \copydoc AhbPac::check_address()
     */
    template<class _Pt, class _Rt>
    static void check_address(Payload<_Pt>& p,
        const _Rt& itf,
        const bool isBlocking,
        const bool isReadable,
        const bool isWriteable);

    // import memory check
    using PacBase::check_address;

private:
    template<Index BPW>
    static bool IsAddrOffsetAlignmentError(const Index offset, const Index bc);
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class _Pt, class _Rt>
RES_INLINE void CpbPac::check_address(Payload<_Pt>& p,
    const _Rt& itf,
    const bool isBlocking,
    const bool isReadable,
    const bool isWriteable)
{
    if (p.get_cpb_avalid() == CP_CPB_INVALID)
    {   // inactive transfer, skip control
        return;
    }
    // restore original address offset and transfer size used in IA mode
    const auto bc = p.get_cpb_transfer_size();
    const auto offset = p.get_cpb_address_offset();
    DoCheckAccess(p, itf, isBlocking, isReadable, isWriteable, p.get_cpb_write(), bc);
    if (!p.is_error())
    {   // additional checks
        if (isBlocking)
        {   // IA mode
            if (IsAddrOffsetAlignmentError<_Rt::BPW>(offset, bc))
            {   // always check address offset + transfer size alignment
                LogAddressAlignment(itf, simulator::LOG_TYPE_ERROR, p.get_address() + offset, bc);
                p.set_cpb_resp(CP_CPB_ERROR);
            }
        }
        else
        {   // CA mode
            const auto addrAlign = itf.get_address_alignment();
            if (IsAddrOffsetAlignmentError<_Rt::BPW>(p.get_address(), addrAlign))
            {   // check address alignment, in CA mode report warning only
                LogAddressAlignment(itf, simulator::LOG_TYPE_WARNING, p.get_address(), addrAlign);
                // do not set error flag in CA,
                // HW/RTL implementation skips address alignment errors for simplicity
                p.set_cpb_resp(CP_CPB_OKAY);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//                             Private interface                              //
////////////////////////////////////////////////////////////////////////////////
/**
 *  \copydoc PacBase::IsAddrOffsetAlignmentError()
 *  \details CPB allows BPW which is not power of 2. Provide fast detection for
 *           powers of 2 and generic (but slow) otherwise.
 */
template<Index BPW>
RES_INLINE bool CpbPac::IsAddrOffsetAlignmentError(const Index offset, const Index bc)
{
    static_assert(BPW >= 1 && BPW <= 128, "Unexpected byte per word count.");
    if (BPW == 1)
    {   // no sub-blocks, no unaligned access possible
        return false;
    }
    else if (BPW == 2 || BPW == 4 || BPW == 8 || BPW == 16 || BPW == 32 || BPW == 64 || BPW == 128)
    {   // allowed powers of 2 (max. 1024/8)
        return PacBase::IsAddrOffsetAlignmentError(offset, bc);
    }
    else
    {
        return (offset % bc) != 0;
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CPB_PAC_H_
