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
 *  \date   Apr 27, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_FVE_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_FVE_INTERFACE_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_payload.h"

#include <vector>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::FveInterface
 *  \brief  Stores finished transactions passed through the interface in single
 *          clock cycle. The transactions are used by the UVM golden model and
 *          the data verification feature, IA mode only.
 *  \}
 */
template<class T>
class FveInterface : public T
{
public:
    /// \brief  Import payload data type
    using typename T::payload_type;

    // inherit constructor
    using T::T;
    /**
     *  \brief  Callback used when the transaction is finished.
     *  \param  p source transaction information (payload)
     */
    void blocking_d(payload_type& p);
    /**
     *  \brief  Access the first stored payload.
     */
    const payload_type& get_transaction(const size_t idx) const;
    /**
     *  \brief  Return number of stored transactions.
     */
    size_t get_transaction_count() const;
    /**
     *  \{
     *  \brief  Clear all previously stored payload data.
     */
    void clear();
    void reset();
    /** \} */
private:
    /// \brief  Container type used to store payloads for current clock cycle
    typedef std::vector<payload_type> Payloads;

    /// Request payload
    Payloads m_Payloads;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void FveInterface<T>::blocking_d(payload_type& p)
{
    T::blocking_d(p);
    // has to be after T::blocking because we need target's response
    m_Payloads.push_back(p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline const typename T::payload_type& FveInterface<T>::get_transaction(const size_t idx) const
{
    static payload_type dummy;
    if (m_Payloads.empty())
    {   // there might be no transaction for current clock cycle at all
        // the default value of the READY signal on AHB/CPB must be 1
        dummy.set_ahb_hready(CP_AHB_READY);
        return dummy;
    }
    else if (idx < m_Payloads.size())
    {   // the UVM data verification monitor needs to access all the transactions
        return m_Payloads[idx];
    }
    else
    {   // the standard ASIP UVM monitor may want to access the last one without any index
        return m_Payloads.back();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline size_t FveInterface<T>::get_transaction_count() const
{
    return m_Payloads.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void FveInterface<T>::clear()
{
    m_Payloads.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void FveInterface<T>::reset()
{
    clear();
    T::reset();
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_FVE_INTERFACE_H_
