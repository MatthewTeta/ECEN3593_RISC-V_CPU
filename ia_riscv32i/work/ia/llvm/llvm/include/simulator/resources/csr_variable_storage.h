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
 *  \date   Feb 22, 2016
 *  \brief  Definition of the class codasip::resources::VariableStorage.
 */

#ifndef SIMULATOR_RESOURCES_CSR_VARIABLE_STORAGE_H_
#define SIMULATOR_RESOURCES_CSR_VARIABLE_STORAGE_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/resources/csr_storage_sentinel.h"

#include <type_traits>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  VariableStorage
 *  \brief  Basic class holding data, it represents either single data or an array
 *  \tparam T underlying data type
 *  \tparam _Size size of the internal array storage, to enable array types, the
 *          value must be greater than 1. By default the storage is defined for
 *          single item only.
 *   \tparam _IsVector indicates whether to store single vector variable or not
 *          (single integer, array of integers, ...)
 *  \}
 */
template<class T,
    codasip_address_t _Size = 1,
    bool _HasWriteMask = false,
    bool _IsVector = detail::IsCodasipVectorHelper<T>::value>
class VariableStorage : public StorageSentinel<T, _Size>
{
public:
    /// \brief  Local shortcut to parent/base class
    typedef StorageSentinel<T, _Size> StorageSentinelBase;
    /// \copydoc StorageSentinelBase::data_type
    typedef typename StorageSentinelBase::data_type data_type;
    /// \copydoc StorageSentinelBase::param_type
    typedef typename StorageSentinelBase::param_type param_type;

    /// \copydoc  StorageSentinelBase::ADDR_BITS
    static const Index ADDR_BITS = StorageSentinelBase::ADDR_BITS;
    /// \copydoc  StorageSentinelBase::WORD_BITS
    static const Index WORD_BITS = StorageSentinelBase::WORD_BITS;
    /// \copydoc  StorageSentinelBase::BYTE_BITS
    static const Index BYTE_BITS = StorageSentinelBase::BYTE_BITS;
    /// \copydoc  StorageSentinelBase::BPW
    static const Index BPW = StorageSentinelBase::BPW;
    /// \copydoc  StorageSentinelBase::SIZE
    static const codasip_address_t SIZE = StorageSentinelBase::SIZE;

    /**
     *  \copydoc StorageSentinel::StorageSentinel()
     */
    VariableStorage(const std::string& name, const Uid uid);
    /**
     *  \brief  Initializes the write mask
     */
    void set_write_mask(param_type writeMask);
    /**
     *  \{
     *  \brief  Read value
     *  \param  addr Address to the storage
     */
    data_type read(const codasip_address_t addr = 0) const;
    data_type dread(const codasip_address_t addr = 0) const;
    /**
     *  \} \{
     *  \brief  Write data to the storage
     *  \param  data New data
     *  \param  addr Address to the storage
     */
    void write(param_type data, const codasip_address_t addr = 0);
    void dwrite(param_type data, const codasip_address_t addr = 0);
    /**
     *  \}
     *  \brief Initialize the value.
     */
    void reset();
    /**
     *  \{
     *  \brief  Do nothing.
     */
    void clock_cycle();
    void stall();
    void clear();
    void gated();
    /** \} */
private:
    /// data itself
    data_type m_Data[SIZE];

    /// write_mask wrapper, ideally this would be inherited (or not) and accesses would be masked
    /// by constexpr ifs, but for now we have to keep the code compilable for both branches
    WriteMaskHelper<data_type, _HasWriteMask> m_WriteMask;
};

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  VariableStorage
 *  \brief  Basic class holding single instance of a vector (SIMD) type. The
 *          class allows access to the whole vector or per single element.
 *  \tparam T underlying vector type (\ref codasip_vec or \ref codasip_vec_flt template)
 *  \}
 */
template<class T>
class VariableStorage<T, 1, false, true> : public StorageSentinel<T, 1>
{
public:
    /// \brief  Local shortcut to parent/base class
    typedef StorageSentinel<T, 1> StorageSentinelBase;
    /// \copydoc StorageSentinelBase::data_type
    typedef typename StorageSentinelBase::data_type data_type;
    /// \brief  Type used for passing data parameters
    typedef typename StorageSentinelBase::param_type data_param_type;
    /// \brief  Type representing single element of the vector
    typedef typename data_type::elem_t elem_type;
    /// \brief  Type used for passing element data parameters
    typedef typename detail::CallTraits<elem_type>::param_type elem_param_type;
    /// \brief  Type used for integer bit-casts
    typedef typename data_type::bitcast_t bitcast_type;
    /// \brief  Type used by the profiler templates - not used with this class
    typedef Payload<data_type> payload_type;

    /**
     *  \copydoc StorageSentinel::StorageSentinel()
     */
    VariableStorage(const std::string& name, const Uid uid);
    /**
     *  \{
     *  \brief  Read the whole vector value.
     *  \param  addr unused parameter, only for compatibility with upper templates
     */
    data_type read(const codasip_address_t addr = 0) const;
    data_type dread(const codasip_address_t addr = 0) const;
    /**
     *  \} \{
     *  \brief  Read value of a single element of the vector.
     *  \param  addr element index
     */
    elem_type extract(const codasip_address_t addr) const;
    /**
     *  \} \{
     *  \brief  Write data to the storage (the whole vector).
     *  \param  data updated value
     *  \param  addr unused parameter, only for compatibility with upper templates
     */
    void write(data_param_type data, const codasip_address_t addr = 0);
    void dwrite(data_param_type data, const codasip_address_t addr = 0);
    /**
     *  \}
     *  \brief  Write single element of the vector in the storage.
     *  \param  data updated value
     *  \param  addr element index
     */
    void insert(elem_param_type data, const codasip_address_t addr);
    /**
     *  \}
     *  \brief  Initialize the value.
     */
    void reset();
    /**
     *  \{
     *  \brief  Do nothing.
     */
    void clock_cycle();
    void stall();
    void clear();
    void gated();
    /** \} */
private:
    /// data itself
    data_type m_Data;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
inline VariableStorage<T, _Size, _HasWriteMask, _IsVector>::VariableStorage(const std::string& name,
    const Uid uid)
  : StorageSentinel<T, _Size>(name, uid)
{
    if (std::is_arithmetic<data_type>::value)
    {
        ::memset(m_Data, 0, sizeof(T) * SIZE);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
inline void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::set_write_mask(param_type writeMask)
{
    if (_HasWriteMask)
    {
        m_WriteMask.SetWriteMask(writeMask);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE typename VariableStorage<T, _Size, _HasWriteMask, _IsVector>::data_type
VariableStorage<T, _Size, _HasWriteMask, _IsVector>::read(const codasip_address_t addr) const
{
    return dread(addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE typename VariableStorage<T, _Size, _HasWriteMask, _IsVector>::data_type
VariableStorage<T, _Size, _HasWriteMask, _IsVector>::dread(const codasip_address_t addr) const
{
    // addressable, check the address
    if (SIZE > 1)
    {
        return m_Data[this->get_address(addr)];
    }
    // no address, no checking
    return m_Data[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::write(param_type data,
    const codasip_address_t addr)
{
    dwrite(data, addr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::dwrite(param_type data,
    const codasip_address_t addr)
{
    // addressable, check the address
    if (SIZE > 1)
    {
        m_Data[this->get_address(addr)] = data;
        return;
    }
    // optional masking
    if (_HasWriteMask)
    {
        m_Data[0] = m_WriteMask.MaskValue(data, this->get_default_value());
        return;
    }
    // no address, no checking
    m_Data[0] = data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
inline void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::reset()
{
    if (SIZE == 1)
    {
        // bypass masking on reset
        m_Data[0] = this->get_default_value();
    }
    else
    {
        for (codasip_address_t ii = 0; ii < SIZE; ++ii)
        {
            dwrite(this->get_default_value(), ii);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::clock_cycle()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::stall()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::clear()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, codasip_address_t _Size, bool _HasWriteMask, bool _IsVector>
RES_INLINE void VariableStorage<T, _Size, _HasWriteMask, _IsVector>::gated()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline VariableStorage<T, 1, false, true>::VariableStorage(const std::string& name, const Uid uid)
  : StorageSentinelBase(name, uid)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename VariableStorage<T, 1, false, true>::data_type
VariableStorage<T, 1, false, true>::read(const codasip_address_t) const
{
    return dread();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename VariableStorage<T, 1, false, true>::data_type
VariableStorage<T, 1, false, true>::dread(const codasip_address_t) const
{
    return m_Data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE typename VariableStorage<T, 1, false, true>::elem_type
VariableStorage<T, 1, false, true>::extract(const codasip_address_t addr) const
{
    return m_Data[addr];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void
VariableStorage<T, 1, false, true>::write(data_param_type data, const codasip_address_t)
{
    m_Data = data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void
VariableStorage<T, 1, false, true>::dwrite(data_param_type data, const codasip_address_t)
{
    m_Data = data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void
VariableStorage<T, 1, false, true>::insert(elem_param_type data, const codasip_address_t addr)
{
    m_Data[addr] = data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline void VariableStorage<T, 1, false, true>::reset()
{
    dwrite(this->get_default_value());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void VariableStorage<T, 1, false, true>::clock_cycle()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void VariableStorage<T, 1, false, true>::stall()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void VariableStorage<T, 1, false, true>::clear()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
RES_INLINE void VariableStorage<T, 1, false, true>::gated()
{}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_VARIABLE_STORAGE_H_
