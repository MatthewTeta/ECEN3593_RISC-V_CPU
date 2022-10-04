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
 *  \author Kamil Michl
 *  \date   Aug 25, 2021
 *  \brief  Definition of the class codasip::resources::AxiPac.
 */

#ifndef SIMULATORS_RESOURCES_CSR_AXI_PAC_H_
#define SIMULATORS_RESOURCES_CSR_AXI_PAC_H_

#include "simulator/resources/csr_pac_base.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AxiPac
 *  \brief  Protocol access checker for AMBA AXI4.
 *  \}
 */
class AxiPac : public PacBase
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

private:
    static const unsigned BURST_BOUNDARY = 4096;
};

////////////////////////////////////////////////////////////////////////////////
//                             Public interface                               //
////////////////////////////////////////////////////////////////////////////////
template<class _Pt, class _Rt>
RES_INLINE void AxiPac::check_address(Payload<_Pt>& p,
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
    const auto burst = p.get_axi_burst();
    const auto len = p.get_axi_len() + 1u;
    const auto offset = p.get_axi_address_offset();

    DoCheckAccess(p,
        itf,
        isBlocking,
        isReadable,
        isWriteable,
        (p.get_command() == CP_CMD_WRITE) || (p.get_command() == CP_CMD_DWRITE) ||
            (p.get_command() == CP_CMD_LOAD),
        bc);

    if (burst == CP_AXI_BURST_FIXED && len > 16)
    {
        LOG(itf.get_log(), simulator::LOG_TYPE_ERROR, 0)
            << "'" << itf.get_signature()
            << "': Fixed burst has incorrect length. Maximum: 16, Actual: " << len;
        p.set_axi_resp(CP_AXI_SLVERR);
    }

    if (burst == CP_AXI_BURST_WRAP && (len > 16 || len == 1))
    {
        LOG(itf.get_log(), simulator::LOG_TYPE_ERROR, 0)
            << "'" << itf.get_signature()
            << "': Wrap burst has incorrect length. Minimum: 2, Maximum: 16, Actual: " << len;
        p.set_axi_resp(CP_AXI_SLVERR);
    }

    if (burst == CP_AXI_BURST_WRAP && IsAddrOffsetAlignmentError(offset, bc))
    {
        LogAddressAlignment(itf, simulator::LOG_TYPE_ERROR, p.get_address(), bc);
        p.set_axi_resp(CP_AXI_SLVERR);
    }

    if (burst == CP_AXI_BURST_INCR)
    {
        const auto dtSize = bc * len;
        const auto burstBegin = p.get_address() / bc * bc;
        const auto burstEnd = burstBegin + dtSize;
        if (burstBegin / BURST_BOUNDARY != (burstEnd - 1) / BURST_BOUNDARY)
        {
            LOG(itf.get_log(), simulator::LOG_TYPE_ERROR, 0)
                << "'" << itf.get_signature()
                << "': Burst is crossing 4KB boundary. Lower address: " << burstBegin
                << ", Upper address: " << burstEnd;
            p.set_axi_resp(CP_AXI_SLVERR);
        }
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATORS_RESOURCES_CSR_AXI_PAC_H_
