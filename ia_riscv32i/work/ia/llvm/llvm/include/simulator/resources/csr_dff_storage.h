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
 *  \date   Feb 23, 2016
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_DFF_STORAGE_H_
#define SIMULATOR_RESOURCES_CSR_DFF_STORAGE_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/csr_sentinel.h"
#include "simulator/resources/csr_storage_sentinel.h"

#include <type_traits>

namespace codasip {
namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  DffStorage
 *  \brief
 *  \}
 */
template<class T, codasip_address_t _Size = 1, bool _HasWriteMask = false>
class DffStorage : public StorageSentinel<T, _Size>
{
public:
    /// \brief  Local shortcut to parent/base class
    typedef StorageSentinel<T, _Size> StorageSentinelBase;
    /// \copydoc StorageSentinelBase::data_type
    typedef typename StorageSentinelBase::data_type data_type;
    /// \copydoc StorageSentinelBase::param_type
    typedef typename StorageSentinelBase::param_type param_type;
    /// \copydoc  StorageSentinelBase::WORD_BITS
    static const Index WORD_BITS = StorageSentinelBase::WORD_BITS;
    /// \copydoc  StorageSentinelBase::BYTE_BITS
    static const Index BYTE_BITS = StorageSentinelBase::BYTE_BITS;
    /// \copydoc  StorageSentinelBase::BPW
    static const Index BPW = StorageSentinelBase::BPW;
    /// \copydoc  StorageSentinelBase::SIZE
    static const codasip_address_t SIZE = StorageSentinelBase::SIZE;

    /**
     * \copydoc Sentinel::Sentinel
     */
    DffStorage(const std::string& name, const Uid uid);
    /**
     *  \brief  Initializes the write mask
     */
    void set_write_mask(param_type writeMask);
    /**
     * \{
     * \brief Read value
     * \param addr Address to the storage
     */
    data_type read(const codasip_address_t addr = 0) const;
    data_type dread(const codasip_address_t addr = 0) const;
    /**
     * \}
     * \{
     * \brief Write data to the storage
     * \param data New data
     * \param addr Address to the storage
     */
    void write(param_type data, const codasip_address_t addr = 0);
    void dwrite(param_type data, const codasip_address_t addr = 0);
    /**
     * \}
     * \brief Initialize the value
     */
    void reset();
    /**
     * \brief Do nothing, only for nice printing
     */
    void clock_cycle();
    /**
     * \brief Stall the value to the next clock cycle
     */
    void stall();
    /**
     * \brief Clear the value to the next clock cycle
     */
    void clear();
    /**
     * \brief Signalizes that the clock was gated
     */
    void gated();

private:
    /// data itself
    data_type m_DataQ[SIZE];
    data_type m_DataD[SIZE];

    /// write_mask wrapper, ideally this would be inherited (or not) and accesses would be masked
    /// by constexpr ifs, but for now we have to keep the code compilable for both branches
    WriteMaskHelper<data_type, _HasWriteMask> m_WriteMask;

    /// pipeline handling
    bool m_Stall = false;
    bool m_Clear = false;
    bool m_Gated = false;
};

template<class T, codasip_address_t _Size, bool _HasWriteMask>
inline DffStorage<T, _Size, _HasWriteMask>::DffStorage(const std::string& name, const Uid uid)
  : StorageSentinelBase(name, uid)
{
    if (std::is_arithmetic<data_type>::value)
    {
        ::memset(m_DataQ, 0, sizeof(data_type) * SIZE);
        ::memset(m_DataD, 0, sizeof(data_type) * SIZE);
    }
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
inline void DffStorage<T, _Size, _HasWriteMask>::set_write_mask(param_type writeMask)
{
    if (_HasWriteMask)
    {
        m_WriteMask.SetWriteMask(writeMask);
    }
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE typename DffStorage<T, _Size, _HasWriteMask>::data_type
DffStorage<T, _Size, _HasWriteMask>::read(const codasip_address_t addr) const
{
    return dread(addr);
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE typename DffStorage<T, _Size, _HasWriteMask>::data_type
DffStorage<T, _Size, _HasWriteMask>::dread(const codasip_address_t addr) const
{
    // addressable, check the address
    if (SIZE > 1)
    {
        return m_DataQ[this->get_address(addr)];
    }
    // no address, no checking
    return m_DataQ[0];
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE void
DffStorage<T, _Size, _HasWriteMask>::write(param_type data, const codasip_address_t addr)
{
    // addressable, check the address
    if (SIZE > 1)
    {
        m_DataD[this->get_address(addr)] = data;
        return;
    }
    // optional masking
    if (_HasWriteMask)
    {
        m_DataD[0] = m_WriteMask.MaskValue(data, this->get_default_value());
        return;
    }
    // no address, no checking
    m_DataD[0] = data;
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE void
DffStorage<T, _Size, _HasWriteMask>::dwrite(param_type data, const codasip_address_t addr)
{
    // addressable, check the address
    if (SIZE > 1)
    {
        m_DataQ[this->get_address(addr)] = m_DataD[this->get_address(addr)] = data;
        return;
    }
    // optional masking
    if (_HasWriteMask)
    {
        m_DataQ[0] = m_DataD[0] = m_WriteMask.MaskValue(data, this->get_default_value());
        return;
    }
    // no address, no checking, no masking
    m_DataQ[0] = m_DataD[0] = data;
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE void DffStorage<T, _Size, _HasWriteMask>::reset()
{
    if (SIZE == 1)
    {
        // bypass masking on reset
        m_DataQ[0] = m_DataD[0] = this->get_default_value();
    }
    else
    {
        for (codasip_address_t ii = 0; ii < SIZE; ++ii)
        {
            dwrite(this->get_default_value(), ii);
        }
    }
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE void DffStorage<T, _Size, _HasWriteMask>::clock_cycle()
{
    if (m_Gated)
    {
        std::copy_n(m_DataQ, SIZE, m_DataD);
        m_Clear = m_Stall = m_Gated = false;
        return;
    }
    // clear has the highest priority
    if (m_Clear)
    {
        reset();
        m_Clear = m_Stall = false;
        return;
    }

    if (m_Stall)
    {
        std::copy_n(m_DataQ, SIZE, m_DataD);
        m_Stall = false;
        return;
    }
    // standard write
    std::copy_n(m_DataD, SIZE, m_DataQ);
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE void DffStorage<T, _Size, _HasWriteMask>::stall()
{
    m_Stall = true;
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE void DffStorage<T, _Size, _HasWriteMask>::clear()
{
    m_Clear = true;
}

template<class T, codasip_address_t _Size, bool _HasWriteMask>
RES_INLINE void DffStorage<T, _Size, _HasWriteMask>::gated()
{
    m_Gated = true;
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_DFF_STORAGE_H_
