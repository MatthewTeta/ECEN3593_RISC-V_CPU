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
 *  \brief  Definition of the class codasip::resources::AhbPac.
 */

#ifndef SIMULATOR_RESOURCES_CSR_AHB_PAC_H_
#define SIMULATOR_RESOURCES_CSR_AHB_PAC_H_

#include "simulator/resources/csr_pac_base.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AhbPac
 *  \brief  Protocol access checker for AMBA 3 AHB-Lite.
 *  \}
 */
class AhbPac : private PacBase
{
public:
    /**
     *  \brief  Implements full access checks which should be done on the
     *          master and slave interface side.
     *  \param  p source transaction informations to check
     *  \param  itf resource doing the check
     *  \param  isBlocking indicates whether blocking (IA) or transport (CA) access
     *          is handled
     *  \param  isReadable indicates whether the resource supports read access or not
     *  \param  isWriteable indicates whether the resource supports read access or not
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
RES_INLINE void AhbPac::check_address(Payload<_Pt>& p,
    const _Rt& itf,
    const bool isBlocking,
    const bool isReadable,
    const bool isWriteable)
{
    if (!p.is_ahb_active_transfer())
    {   // inactive transfer, skip control
        return;
    }
    const auto bc = p.get_bc();
    DoCheckAccess(p, itf, isBlocking, isReadable, isWriteable, p.get_ahb_hwrite(), bc);
    if (!p.is_error())
    {   // additional checks
        // check data alignment in CA, IA mode has been checked by DoCheckAccess()
        if (!isBlocking && IsDataAlignmentError(bc, itf.get_data_alignment_mask()))
        {
            LogDataAlignment(itf, bc, itf.get_data_alignment());
            p.set_ahb_hresp(CP_AHB_ERROR);
        }
        // always check invalid offset, HSIZE combination
        else if (IsAddrOffsetAlignmentError(p.get_address() % _Rt::BPW, bc))
        {
            LogAddressAlignment(itf, simulator::LOG_TYPE_ERROR, p.get_address(), bc);
            p.set_ahb_hresp(CP_AHB_ERROR);
        }
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_AHB_PAC_H_
