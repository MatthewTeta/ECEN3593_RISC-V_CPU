/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip Ltd
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the property of Codasip Ltd
 * and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and proprietary to
 * Codasip Ltd and are protected by trade secret and copyright law.  In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Pavel Najman
 *  \date   Nov 28, 2019
 *  \brief  Implementation of utility classes for arbiters.
 */

#ifndef SIMULATOR_RESOURCES_CSR_ARBITER_PAYLOAD_H_
#define SIMULATOR_RESOURCES_CSR_ARBITER_PAYLOAD_H_

#include "simulator/resources/csr_payload.h"

namespace codasip {
namespace resources {
namespace detail {

/**
 *  \brief  Base class for arbiters' input interface payload.
 *  \tparam T   Payload data type
 */
template<typename T>
class ArbiterStoredPayload
{
public:
    /// Type for underlying payload.
    typedef Payload<T> payload_type;

    /**
     * \brief Destructor.
     */
    virtual ~ArbiterStoredPayload() = default;
    /**
     * \brief Store payload to the buffer.
     * \param p Payload to be stored.
     */
    void Store(const payload_type& p);
    /**
     * \brief Check if the stored payload contains valid transaction.
     * \return True if payload contains a valid transaction, false otherwise.
     */
    virtual bool IsStored() const = 0;
    /**
     * \brief Stored payload accessor.
     * \return Payload stored in this container.
     */
    payload_type& GetPayload();
    /**
     * \brief Removes the stored payload from buffer.
     */
    void Clear();

protected:
    /// Stored payload.
    payload_type m_Payload;
    /// Is valid payload stored.
    bool m_IsStored = false;
};

template<typename T>
inline void ArbiterStoredPayload<T>::Store(const payload_type& p)
{
    m_Payload = p;
    m_IsStored = true;
}

template<typename T>
inline typename ArbiterStoredPayload<T>::payload_type& ArbiterStoredPayload<T>::GetPayload()
{
    return m_Payload;
}

template<typename T>
inline void ArbiterStoredPayload<T>::Clear()
{
    m_IsStored = false;
    m_Payload.reset();
}

/**
 *  \brief  Axi Lite arbiter input interface payload.
 *  \tparam T   Payload data type.
 */
template<typename T>
class AxiArbiterStoredPayload : public ArbiterStoredPayload<T>
{
public:
    /**
     *  \copydoc    ArbiterStoredPayload::IsStored()
     */
    bool IsStored() const override;
};

template<typename T>
bool AxiArbiterStoredPayload<T>::IsStored() const
{
    return this->m_IsStored && this->m_Payload.get_axi_valid() == CP_AXI_VALID;
}

/**
 *  \brief  Ahb Lite arbiter input interface payload.
 *  \tparam T   Payload data type.
 */
template<typename T>
class AhbLiteArbiterStoredPayload : public ArbiterStoredPayload<T>
{
public:
    /**
     *  \copydoc    ArbiterStoredPayload::IsStored()
     */
    bool IsStored() const override;
};

template<typename T>
bool AhbLiteArbiterStoredPayload<T>::IsStored() const
{
    return this->m_IsStored && this->m_Payload.get_ahb_htrans() != CP_AHB_IDLE;
}

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_ARBITER_PAYLOAD_H_
