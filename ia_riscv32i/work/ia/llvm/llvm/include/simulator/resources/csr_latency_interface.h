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
 *  \date   Nov 21, 2017
 *  \brief  Definition of the class codasip::resources::LatencyInterface.
 */

#ifndef SIMULATOR_RESOURCES_CSR_LATENCY_INTERFACE_H_
#define SIMULATOR_RESOURCES_CSR_LATENCY_INTERFACE_H_

#include "simulator/resources/csr_interface.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::LatencyInterface
 *  \brief  Base target interface for memory slave interfaces with separated
 *          address and data phase and optionally RW flag.
 *  \}
 */
template<class T, class M>
class LatencyInterface : public Interface<T, M>
{
public:
    /// \brief  Concrete payload type used by this class
    typedef Payload<typename T::data_type> PayloadType;
    /// \brief  Interface base class
    typedef Interface<T, M> InterfaceBaseType;

    /// Number of bytes in word
    static const Index SUBBLOCKS = T::WORD_BITS / T::BYTE_BITS;

    /**
     *  \copydoc Sentinel::Sentinel
     */
    LatencyInterface(const std::string& name, const Uid uid, M* module = nullptr);

protected:
    unsigned get_read_latency() const;
    unsigned get_write_latency() const;

    void inc_read_latency();
    void inc_write_latency();

private:
    /// Read latency
    unsigned m_ReadLatencyIndex;
    /// Write latency
    unsigned m_WriteLatencyIndex;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M>
inline LatencyInterface<T, M>::LatencyInterface(const std::string& name, const Uid uid, M* module)
  : InterfaceBaseType(name, uid, module)
  , m_ReadLatencyIndex(0)
  , m_WriteLatencyIndex(0)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M>
RES_INLINE unsigned LatencyInterface<T, M>::get_read_latency() const
{
    return InterfaceBaseType::m_Module->GetLatencyRead(InterfaceBaseType::GetUid(), m_ReadLatencyIndex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M>
RES_INLINE unsigned LatencyInterface<T, M>::get_write_latency() const
{
    return InterfaceBaseType::m_Module->GetLatencyWrite(InterfaceBaseType::GetUid(),
        m_WriteLatencyIndex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M>
RES_INLINE void LatencyInterface<T, M>::inc_read_latency()
{
    ++m_ReadLatencyIndex;
    if (m_ReadLatencyIndex >=
        InterfaceBaseType::m_Module->GetLatencySizeRead(InterfaceBaseType::GetUid()))
    {
        m_ReadLatencyIndex = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class M>
RES_INLINE void LatencyInterface<T, M>::inc_write_latency()
{
    ++m_WriteLatencyIndex;
    if (m_WriteLatencyIndex >=
        InterfaceBaseType::m_Module->GetLatencySizeWrite(InterfaceBaseType::GetUid()))
    {
        m_WriteLatencyIndex = 0;
    }
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_LATENCY_INTERFACE_H_
