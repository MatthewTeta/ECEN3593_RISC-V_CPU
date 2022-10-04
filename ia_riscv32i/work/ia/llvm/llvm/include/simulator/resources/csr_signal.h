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
 *  \date   Feb 26, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_SIGNAL_H_
#define SIMULATOR_RESOURCES_CSR_SIGNAL_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/simbase/simulator_resources.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  Signal
 *  \brief  Class representing a signal
 *  \}
 */
template<class T>
class Signal : public T, public simulator::SignalInfo
{
public:
    /**
     * \copydoc Sentinel::Sentinel
     */
    Signal(const std::string& name, const Uid uid);
    /**
     * \brief  Assign default value
     */
    void clock_cycle();

    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override;
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override;
    /// \copydoc ResourceInfo::GetBitWidth
    unsigned GetBitWidth() const override;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Signal<T>::Signal(const std::string& name, const Uid uid)
  : T(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void Signal<T>::clock_cycle()
{
    typedef typename T::data_type data_type;
    T::clock_cycle();
    T::dwrite(data_type());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE Uid Signal<T>::GetUid() const
{
    return T::get_uid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE const std::string& Signal<T>::GetName() const
{
    return T::get_name();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE unsigned Signal<T>::GetBitWidth() const
{
    return T::WORD_BITS;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_SIGNAL_H_
