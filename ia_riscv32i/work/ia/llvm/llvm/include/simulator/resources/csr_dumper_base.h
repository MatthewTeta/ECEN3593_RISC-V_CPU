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

#ifndef SIMULATOR_RESOURCES_CSR_DUMPER_BASE_H_
#define SIMULATOR_RESOURCES_CSR_DUMPER_BASE_H_

#include "simulator/resources/csr_helpers.h"

namespace codasip {
namespace simulator {
class DumpStream;
}   // namespace simulator

namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::DumperBase
 *  \brief  Base class for all dumpers
 *  \}
 */
template<class T>
class DumperBase : public T
{
public:
    /**
     * \copydoc Sentinel::Sentinel
     */
    DumperBase(const std::string& name, const Uid uid);
    /**
     * \brief Set output stream.
     * \param output Output stream
     */
    void set_dump_stream(simulator::DumpStream& stream);

protected:
    /// Opened Codasip file to dump
    simulator::DumpStream* m_Dump = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          DumperBase                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline DumperBase<T>::DumperBase(const std::string& name, const Uid uid)
  : T(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void DumperBase<T>::set_dump_stream(simulator::DumpStream& output)
{
    m_Dump = &output;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_DUMPER_BASE_H_
