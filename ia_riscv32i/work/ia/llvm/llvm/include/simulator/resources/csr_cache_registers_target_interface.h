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
 *  \author Pavel Najman
 *  \date   Oct 23, 2018
 *  \brief  Ahb Lite target interface for cache registers.
 *
 *  It reimplements the do_response method of its parent
 *  so that it does not perform write during next clock cycle.
 */

#ifndef SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_TARGET_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_TARGET_INTERFACE_H_

#include "simulator/resources/csr_ahb_target_interface.h"

namespace codasip {
namespace resources {
/**
 *  \class  codasip::resources::CacheRegistersTargetInterface
 *  \brief  Handles incoming cache registers requests.
 *  \copydetails    codasip::resources::AhbLiteTargetInterface
 */
template<class T, class M, class A>
class CacheRegistersTargetInterface : public AhbLiteTargetInterface<T, M, A>
{
public:
    /// Base class type.
    typedef AhbLiteTargetInterface<T, M, A> TargetInterfaceBaseType;
    /// \copydoc     codasip::resources::AhbLiteTargetInterface::PayloadType
    typedef typename TargetInterfaceBaseType::PayloadType PayloadType;
    /// \copydoc     codasip::resources::AhbLiteTargetInterface::RequestBaseType
    typedef typename TargetInterfaceBaseType::RequestBaseType RequestBaseType;
    /// \copydoc     codasip::resources::AhbLiteTargetInterface::InterfaceBaseType
    typedef typename TargetInterfaceBaseType::InterfaceBaseType InterfaceBaseType;
    /// \copydoc     codasip::resources::AhbLiteTargetInterface::AhbLiteTargetInterface
    using TargetInterfaceBaseType::AhbLiteTargetInterface;
    /// \copydoc    codasip::resources::Interface::transport_cb
    void transport_cb(PayloadType& p, const Phase phase) override;
    /// \copydoc    codasip::resources::Interface::blocking_cb
    void blocking_cb(PayloadType& p) override;
    /**
     *  \brief  Checks whether the given byte count is maximum byte count for this interface.
     *  \param  bc  Checked byte count value.
     *  \return True if bc is maximum interface bc, false otherwise.
     */
    static constexpr bool IsMaxBc(const Index bc);

protected:
    /// \copydoc    codasip::resources::AhbLiteTargetInterface::do_request
    using TargetInterfaceBaseType::do_request;
    /// \copydoc    codasip::resources::AhbLiteTargetInterface::do_response
    void do_response(PayloadType&);
};

template<class T, class M, class A>
void CacheRegistersTargetInterface<T, M, A>::blocking_cb(PayloadType& p)
{
    if (!IsMaxBc(p.get_bc()))
    {
        p.set_data(0);
        p.set_ahb_hready(CP_AHB_READY);
        p.set_ahb_hresp(CP_AHB_ERROR);
        return;
    }
    TargetInterfaceBaseType::blocking_cb(p);
}

template<class T, class M, class A>
void CacheRegistersTargetInterface<T, M, A>::transport_cb(PayloadType& p, const Phase phase)
{
    switch (phase)
    {
        case CP_PHS_ADDRESS:
            do_request(p);
            return;
        case CP_PHS_DATA:
            do_response(p);
            return;
        default:
            break;
    }
}

template<class T, class M, class A>
void CacheRegistersTargetInterface<T, M, A>::do_response(PayloadType& p)
{
    // data to be written (if write request)
    const auto data = p.get_data();
    const auto address = p.get_address();
    RequestBaseType::DataPhase(p);
    p.set_address(address);
    bool clear_output = true;
    // ready to proceed, but not handling IDLE or BUSY commands
    if ((p.get_ahb_hready() == CP_AHB_READY) && (p.get_ahb_hresp() == CP_AHB_OKAY) &&
        p.is_ahb_active_transfer())
    {   // there is a valid request pending
        if (!IsMaxBc(p.get_bc()))
        {   // allow only request with maximum hsize
            p.set_ahb_hresp(CP_AHB_ERROR);
            p.set_ahb_hready(CP_AHB_WAIT);
        }
        else
        {
            clear_output = false;
            if (p.get_ahb_hwrite() == CP_AHB_WRITE)
            {   // finish write transaction
                p.set_data(data);
            }
            InterfaceBaseType::transport_cb(p, CP_PHS_DATA);
        }
    }
    // clear output data if not valid
    if (clear_output)
    {
        p.set_data(0);
    }
}

template<class T, class M, class A>
constexpr bool CacheRegistersTargetInterface<T, M, A>::IsMaxBc(const Index bc)
{
    return bc == static_cast<Index>(BitWidthTypeSelector<typename PayloadType::data_type>::value / 8);
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_CACHE_REGISTERS_TARGET_INTERFACE_H_
