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
 *  \date   Mar 9, 2016
 *  \brief  Definition of the class codasip::resources::AxiLitePac.
 */

#ifndef SIMULATORS_RESOURCES_CSR_AXI_LITE_PAC_H_
#define SIMULATORS_RESOURCES_CSR_AXI_LITE_PAC_H_

#include "simulator/resources/csr_pac_base.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiLitePac
 *  \brief  Protocol access checker for AMBA AXI4-Lite.
 *  \}
 */
class AxiLitePac : public PacBase
{
public:
    /**
     *  \copydoc AhbPac::check_address
     */
    template<class _Pt, class _Rt>
    static void check_address(Payload<_Pt>& p,
        const _Rt& itf,
        const bool isBlocking,
        const bool isReadable,
        const bool isWriteable);

    // import memory check
    using PacBase::check_address;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class _Pt, class _Rt>
RES_INLINE void AxiLitePac::check_address(Payload<_Pt>& p,
    const _Rt& itf,
    const bool isBlocking,
    const bool isReadable,
    const bool isWriteable)
{
    if (p.get_command() == CP_CMD_NONE)
    {   // inactive transfer, skip control
        // can't use AXI valid bit, since it is not mandatory for read data phase
        return;
    }
    const auto bc = p.get_axi_transfer_size();
    DoCheckAccess(p,
        itf,
        isBlocking,
        isReadable,
        isWriteable,
        (p.get_command() == CP_CMD_WRITE) || (p.get_command() == CP_CMD_DWRITE) ||
            (p.get_command() == CP_CMD_LOAD),
        bc);
    if (!p.is_error())
    {   // additional checks
        if (isBlocking)
        {   // IA mode
            const auto offset = p.get_axi_address_offset();
            if (IsAddrOffsetAlignmentError(offset, bc))
            {   // always check address offset + transfer size alignment
                LogAddressAlignment(itf, simulator::LOG_TYPE_ERROR, p.get_address() + offset, bc);
                p.set_axi_resp(CP_AXI_SLVERR);
            }
        }
        else
        {   // CA mode
            if (IsAddrOffsetAlignmentError(p.get_address(), _Rt::BPW))
            {   // address must be word-aligned
                // full AXI4 allows the first transfer of a burst to be unaligned,
                // but this is AXI4-Lite
                LogAddressAlignment(itf, simulator::LOG_TYPE_ERROR, p.get_address(), _Rt::BPW);
                p.set_axi_resp(CP_AXI_SLVERR);
            }
        }
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATORS_RESOURCES_CSR_AXI_LITE_PAC_H_
