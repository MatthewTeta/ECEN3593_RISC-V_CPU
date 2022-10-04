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
 *  \author Petr Hons
 *  \date   7. 4. 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_DUMPER_SINGLE_H_
#define SIMULATOR_RESOURCES_CSR_DUMPER_SINGLE_H_

#include "simulator/resources/csr_dumper_base.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::Dumper
 *  \brief  Dumps changes of single addressable resource (port, signal, register) into the file
 *  \}
 */
template<class T>
class DumperSingle : public DumperBase<T>
{
    typedef DumperBase<T> Base;

public:
    using typename T::param_type;
    /**
     * \copydoc DumperBase::DumperBase
     */
    DumperSingle(const std::string& name, const Uid uid);
    /**
     *  \brief  Detect change of resources
     */
    void write(param_type data, const codasip_address_t addr = 0);
    /**
     *  \brief  Detect changes when simulator is reseted after the run
     */
    void reset();
    /**
     *  \brief  Dump changes into the file
     *  \param  clockCycle Current clock cycle counter
     *  \{
     */
    void dump(const Counter clockCycle);
    /**
     *  \}
     */
private:
    /// True when value was written
    bool m_Changed = false;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         DumperSingle                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline DumperSingle<T>::DumperSingle(const std::string& name, const Uid uid)
  : Base(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void DumperSingle<T>::reset()
{
    // only in non-addressable items
    if (this->m_Dump)
    {
        m_Changed = true;
    }
    T::reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void DumperSingle<T>::write(param_type data, const codasip_address_t addr)
{
    if (this->m_Dump)
    {
        m_Changed = true;
    }
    T::write(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void DumperSingle<T>::dump(const Counter clockCycle)
{
    if (!this->m_Dump || !m_Changed)
    {
        return;
    }

    this->m_Dump->DumpClockCycle(clockCycle);
    this->m_Dump->Dump(this->get_signature(), T::dread());
    m_Changed = false;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_DUMPER_SINGLE_H_
