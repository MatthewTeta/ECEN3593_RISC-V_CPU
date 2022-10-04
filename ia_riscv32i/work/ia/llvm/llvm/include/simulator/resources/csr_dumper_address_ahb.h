/**
 * Codasip s.r.o.
 * 
 * CONFIDENTIAL 
 *
 * Copyright 2021 Codasip s.r.o.
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
 *  \author Karel Vorechovsky
 *  \date   19.10. 2021
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_DUMPER_ADDRESS_AHB_H_
#define SIMULATOR_RESOURCES_CSR_DUMPER_ADDRESS_AHB_H_

#include "simulator/resources/csr_dumper_address.h"

#include <vector>

namespace codasip {
namespace resources {
/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::DumperAddressAhb
 *  \brief  Dumps changes of Ahb connected addressable resource
 *  \}
 */
template<class T>
class DumperAddressAhb : public DumperAddress<T>
{
private:
    typedef DumperBase<T> Base;
    typedef Payload<typename T::data_type> DumpPayload;

    /**
     * \brief Internal dumper state, what response is the dumper waiting for to finish
     */
    enum class PendingOperation
    {
        WRITE,
        READ,
        NONE
    };

public:
    /**
     * \copydoc DumperBase::DumperBase
     */
    DumperAddressAhb(const std::string& name, const Uid uid);
    /**
     * \copydoc DumperAddress::transport_d
     */
    void transport_d(DumpPayload& p, const Phase phase);
    /**
     * \copydoc DumperAddress::blocking_d
     */
    void blocking_d(DumpPayload& p);

private:
    bool IsValidRequest(const DumpPayload& p);
    void DoPhaseAddress(const DumpPayload& p);
    void DoPhaseData(const DumpPayload& p);
    void StoreChange(const DumpPayload& addressPayload, const DumpPayload& dataPayload);
    bool IsDataResponseFinished(const DumpPayload& p);

private:
    /// dumper state to handshake requests with responses
    PendingOperation m_PendingOperation = PendingOperation::NONE;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        DumperAddressAhb                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
DumperAddressAhb<T>::DumperAddressAhb(const std::string& name, const Uid uid)
  : DumperAddress<T>(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DumperAddressAhb<T>::transport_d(DumpPayload& p, const Phase phase)
{
    T::transport_d(p, phase);

    switch (phase)
    {
        case CP_PHS_ADDRESS:
        case CP_PHS_ADDRESS_WRITE:
            DoPhaseAddress(p);
            break;
        case CP_PHS_DATA:
        case CP_PHS_DATA_WRITE:
            DoPhaseData(p);
            break;
        case CP_PHS_DATA_READ:
        case CP_PHS_ADDRESS_READ:
        case CP_PHS_RESPONSE_WRITE:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DumperAddressAhb<T>::blocking_d(DumpPayload& p)
{
    T::blocking_d(p);
    if (this->m_Dump && p.get_command() == CP_CMD_WRITE && !p.is_error())
    {
        this->StoreChange(p, p);
    }
}

/**
 *  \brief     Check for address phase payload
 *  \param[in] p address phase payload
 *  \returns   true if the address phase payload returned from target as accepted
 */
template<class T>
bool DumperAddressAhb<T>::IsValidRequest(const DumpPayload& p)
{
    return p.get_ahb_hready() == CP_AHB_READY && p.is_ahb_active_transfer() && !p.is_error();
}

/**
 *  \brief     Handle address phase of the transport
 *  \param[in] p address phase payload
 */
template<class T>
void DumperAddressAhb<T>::DoPhaseAddress(const DumpPayload& p)
{
    if (IsValidRequest(p) && m_PendingOperation == PendingOperation::NONE)
    {
        if (p.get_ahb_hwrite() == CP_AHB_WRITE)
        {
            m_PendingOperation = PendingOperation::WRITE;
            this->m_RequestPayload = p;
        }
        else
        {
            m_PendingOperation = PendingOperation::READ;
        }
    }
}

/**
 *  \brief     Handle data phase of transport
 *  \param[in] p address phase payload
 */
template<class T>
void DumperAddressAhb<T>::DoPhaseData(const DumpPayload& p)
{
    if (IsDataResponseFinished(p))
    {
        if (m_PendingOperation == PendingOperation::WRITE)
        {
            this->StoreChange(this->m_RequestPayload, p);
        }
        m_PendingOperation = PendingOperation::NONE;
    }
}

/**
 *  \brief     Store the transaction
 *  \param[in] addressPayload address phase payload
 *  \param[in] dataPayload data phase payload
 */
template<class T>
void DumperAddressAhb<T>::StoreChange(const DumpPayload& addressPayload, const DumpPayload& dataPayload)
{
    typedef Interface<T> InterfaceBaseType;
    // create empty payload and set just mandatory attributes as in IA mode
    this->m_Changes.emplace_back();
    auto& p = this->m_Changes.back();
    p.set_address(addressPayload.get_address());
    p.set_bc(addressPayload.get_bc());
    // moves valid write data bits to LSB position
    const auto shift = InterfaceBaseType::get_amba_shift(
        InterfaceBaseType::get_offset(p.get_address(), T::BPW),
        p.get_bc());
    p.set_data(dataPayload.get_data() >> shift);
}

/**
 *  \brief     Check if the data phase payload is ok and has data
 *  \param[in] dataPayload data phase payload
 *  \returns   true on data ready and no error
 */
template<class T>
bool DumperAddressAhb<T>::IsDataResponseFinished(const DumpPayload& p)
{
    return p.get_ahb_hready() == CP_AHB_READY && !p.is_error();
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_DUMPER_H_
