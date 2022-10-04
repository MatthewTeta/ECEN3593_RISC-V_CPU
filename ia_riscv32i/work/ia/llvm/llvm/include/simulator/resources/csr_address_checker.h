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
 *  \date   Feb 25, 2016
 *  \brief  Definition of the class codasip::resources::AddressChecker.
 */

#ifndef SIMULATOR_RESOURCES_CSR_ADDRESS_CHECKER_H_
#define SIMULATOR_RESOURCES_CSR_ADDRESS_CHECKER_H_

#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_sentinel.h"   // Logging

#include <climits>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::AddressChecker
 *  \brief  This class is used to detect out-of-range access to register file
 *          and to perform protocol specific checks in case of a bus transfer.
 *  \}
 */
template<class T>
class AddressChecker : public T
{
public:
    using typename T::data_type;
    using typename T::param_type;
    using typename T::payload_type;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    AddressChecker(const std::string& name, const Uid uid);
    /**
     *  \{
     *  \brief  Checks the out-of-range access for register file.
     *  \param  addr source address to check
     */
    data_type read(const codasip_address_t addr) const;
    data_type dread(const codasip_address_t addr) const;
    /**
     *  \} \{
     *  \copydoc read()
     *  \param  data source data to write
     */
    void write(param_type data, const codasip_address_t addr);
    void dwrite(param_type data, const codasip_address_t addr);
    /**
     *  \}
     *  \brief  Checks the blocking transaction and in case of an error on
     *          standard (no debug) access throw an exception to stop simulation.
     *  \param  p source transaction payload
     */
    void blocking(payload_type& p);
    /**
     *  \brief  Checks the nonblocking transaction and reports error if one occurs.
     *          The simulation is not stopped, transaction is routed further to
     *          the target even in case of an error. The final error response
     *          should be set by the target.
     */
    void transport(payload_type& p, const Phase phase);

private:
    void check_address(const codasip_address_t, const bool = false) const;
    void log_oor(const codasip_address_t addr) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline AddressChecker<T>::AddressChecker(const std::string& name, const Uid uid)
  : T(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename T::data_type AddressChecker<T>::read(const codasip_address_t addr) const
{
    check_address(addr, true);
    return T::read(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename T::data_type AddressChecker<T>::dread(const codasip_address_t addr) const
{
    check_address(addr);
    return T::dread(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AddressChecker<T>::write(param_type data, const codasip_address_t addr)
{
    check_address(addr, true);
    T::write(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AddressChecker<T>::dwrite(param_type data, const codasip_address_t addr)
{
    check_address(addr);
    T::dwrite(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AddressChecker<T>::blocking(payload_type& p)
{   // Use local copy of the payload because we do not want to stop transaction/payload routing
    // from master to the slave. The final error response should be set by the slave, not this class.
    payload_type lp(p);
    this->check_payload(lp, true);
    // move on, route the transaction/payload
    T::blocking(p);
    if (!p.is_error() && lp.is_error())
    {
        p.set_axi_resp(lp.get_axi_resp());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void AddressChecker<T>::transport(payload_type& p, const Phase phase)
{   // Use local copy of the payload because we do not want to stop transaction/payload routing
    // from master to the slave. For CA the final error response should be set
    // by the slave, not this class. This class serves just to report errors in the very origin.
    payload_type lp(p);
    this->check_payload(lp, false);
    // move on, route the transaction/payload
    T::transport(p, phase);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void
AddressChecker<T>::check_address(const codasip_address_t addr, const bool endOnError) const
{
    // maximum, there is no way to get overflow
    if (T::ADDR_BITS == sizeof(codasip_address_t) * CHAR_BIT)
    {
        return;
    }
    if (addr >= T::SIZE)
    {
        log_oor(addr);
        if (endOnError)
        {
            throw exceptions::BasicError("Aborted simulation, fatal error when accessing "
                                         "'" +
                this->get_signature() + "'");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void AddressChecker<T>::log_oor(const codasip_address_t addr) const
{
    RES_LOG(LOG_TYPE_ERROR, 0) << "'" << this->get_signature() << "': Address '0x" << std::hex << addr
                               << "' is out-of-range, max address is '0x" << (T::SIZE - 1) << "'.";
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_ADDRESS_CHECKER_H_
