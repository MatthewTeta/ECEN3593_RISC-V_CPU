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

#ifndef SIMULATOR_RESOURCES_CSR_REGISTER_FILE_H_
#define SIMULATOR_RESOURCES_CSR_REGISTER_FILE_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/simbase/simulator_resources.h"

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  RegisterFile
 *  \brief  Class representing a register file
 *  \}
 */
template<class T>
class RegisterFile : public T, public simulator::RegisterInfo
{
public:
    using typename T::data_type;
    using typename T::param_type;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    RegisterFile(const std::string& name, const Uid uid);
    /**
     *  \{
     *  \copydoc VariableStorage::read
     */
    typename T::data_type read(const codasip_address_t addr, const DataPortUid idx) const;
    typename T::data_type dread(const codasip_address_t addr) const;
    /**
     *  \} \{
     *  \copydoc VariableStorage::write
     */
    void write(param_type data, const codasip_address_t addr, const DataPortUid idx);
    void dwrite(param_type data, const codasip_address_t addr);
    /** \} */

    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override;
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override;
    /// \copydoc ResourceInfo::GetBitWidth
    unsigned GetBitWidth() const override;
    /// \copydoc RegisterInfo::IsArchitectural
    bool IsArchitectural() const override;
    /// \copydoc RegisterInfo::GetPipelineStage
    const std::string& GetPipelineStage() const override;
    /// \copydoc RegisterInfo::GetSize
    unsigned GetSize() const override;

    /**
     *  \brief  Set flag that this register file is architectural
     *  \param  arch value of the flag
     */
    void set_architectural(const bool arch);

private:
    bool m_Arch;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline RegisterFile<T>::RegisterFile(const std::string& name, const Uid uid)
  : T(name, uid)
  , m_Arch(false)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline typename T::data_type
RegisterFile<T>::read(const codasip_address_t addr, const DataPortUid) const
{
    return T::read(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline typename T::data_type RegisterFile<T>::dread(const codasip_address_t addr) const
{
    return T::dread(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RegisterFile<T>::write(param_type data, const codasip_address_t addr, const DataPortUid)
{
    T::write(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RegisterFile<T>::dwrite(param_type data, const codasip_address_t addr)
{
    T::dwrite(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline Uid RegisterFile<T>::GetUid() const
{
    return T::get_uid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline const std::string& RegisterFile<T>::GetName() const
{
    return T::get_name();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline unsigned RegisterFile<T>::GetBitWidth() const
{
    return T::WORD_BITS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline unsigned RegisterFile<T>::GetSize() const
{
    return T::SIZE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline bool RegisterFile<T>::IsArchitectural() const
{
    return m_Arch;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline const std::string& RegisterFile<T>::GetPipelineStage() const
{
    // reg file never has pipeline
    static std::string g_Empty;
    return g_Empty;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void RegisterFile<T>::set_architectural(const bool arch)
{
    m_Arch = arch;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_REGISTER_FILE_H_
