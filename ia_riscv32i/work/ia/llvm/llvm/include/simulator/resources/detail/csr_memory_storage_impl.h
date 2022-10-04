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
 *  \author Karel Vorechovsky
 *  \date   2020-8-2
 *  \brief  Impl of memories, SparseMemory = umap, LinearMemory = vector, ParametrizedMemory = runtime wrapper that contains any of those
 */

#ifndef SIMULATOR_RESOURCES_CSR_MEMORY_STORAGE_IMPL_H_
#define SIMULATOR_RESOURCES_CSR_MEMORY_STORAGE_IMPL_H_

#include "simulator/resources/csr_helpers.h"
#include "simulator/resources/detail/csr_memory_helpers.h"

#include <cstring>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace codasip {
namespace resources {
namespace detail {

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Declaration
//
///////////////////////////////////////////////////////////////////////////////////////////////////

template<typename DataType>
class LinearMemory;

template<unsigned ADDRESS_BITS, typename DataType>
class SparseMemory;

template<typename data_type>
class MemoryBaseApi;

/**
 *  \brief  AddressType typedef for memory impl [] operator argument
 */
typedef std::size_t AddressType;

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  RuntimeMemory
 *  \brief  Wrapper for memory containers, used if memory contains codal parameter
 *          for memory size, it uses 'if' to select between vector and hash map,
 *          which was benchmarked to be faster in case the simulator doesn't fit
 *          cpu cache
 *  \param  ADDRESS_BITS  used in unorderd_map storage to select data type for address
 *  \param  DataType  underlying data type of the used container
 *  \}
 */
template<unsigned ADDRESS_BITS, typename DataType>
class RuntimeMemory
{
public:
    /**
     *  \brief  ctor
     *  \param  size size of the memory in bytes, unused for sparsed memory, if sparsed
     *          memory is used, the LinearMemory is initialized to zeroes
     */
    RuntimeMemory(codasip_address_t size);
    /**
     *  \brief  write accessor
     *  \param  address address
     */
    DataType& operator[](const AddressType& address);
    /**
     *  \brief  read accessor
     *  \param  address address
     */
    const DataType& operator[](const AddressType& address) const;

private:
    /// selector for memory type
    bool m_UseSparseMemory;
    /// vec impl
    LinearMemory<DataType> m_LinearMemory;
    /// map impl
    SparseMemory<ADDRESS_BITS, DataType> m_SparseMemory;
};

/**
 *  \brief  Linear memory implementation, uses standard vector
 *  \param  DataType T for vector
 */
template<typename DataType>
class LinearMemory
{
public:
    /**
     *  \brief  ctor, allocates and zeroes memory for pod
     *  \param  memorySize memory size in sizeof(DataType)
     */
    LinearMemory(const codasip_address_t memorySize);
    /**
     *  \brief  write accessor
     *  \param  address address
     */
    DataType& operator[](const AddressType& address);
    /**
     *  \brief  read accessor
     *  \param  address address
     */
    const DataType& operator[](const AddressType& address) const;

private:
    /// storage for words
    std::vector<DataType> m_Mem;
};

/**
 *  \brief  Sparse memory implementation, uses std::unordered_map
 *          required for system with i/o mapped into regions far far away
 *  \param  ADDRESS_BITS  number of bits necessary to represent the address
 *  \param  DataType  T for std::unordered_map<T>
 */
template<unsigned ADDRESS_BITS, typename DataType>
class SparseMemory
{
public:
    /**
     *  \brief  supposedly limit the number of bytes for the address
     */
    typedef typename TypeSelector<ADDRESS_BITS, false>::type KeyType;
    /**
     *  \brief  ctor 
     *  \param  memorySize unused for map, only here to avoid enable_if in the 
     *          memory constructor
     */
    SparseMemory(const codasip_address_t);
    /**
     *  \brief  write accessor
     *  \param  address address
     */
    DataType& operator[](const AddressType& address);
    /**
     *  \brief  read accessor
     *  \param  address address
     */
    const DataType& operator[](const AddressType& address) const;

private:
    /// storage for words
    std::unordered_map<KeyType, DataType> m_Map;
    /// used to have default value when reading uninitialized element
    static const DataType m_DefaultValue;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Definition
//
///////////////////////////////////////////////////////////////////////////////////////////////////

template<unsigned ADDRESS_BITS, typename DataType>
RuntimeMemory<ADDRESS_BITS, DataType>::RuntimeMemory(const codasip_address_t size)
  : m_UseSparseMemory(UseSparseMemory(size))
  , m_LinearMemory(GetLinearMemoryInitSize(size))
  , m_SparseMemory(size)
{}

template<unsigned ADDRESS_BITS, typename DataType>
DataType& RuntimeMemory<ADDRESS_BITS, DataType>::operator[](const AddressType& address)
{
    if (m_UseSparseMemory)
    {
        return m_SparseMemory[address];
    }
    else
    {
        return m_LinearMemory[address];
    }
}

template<unsigned ADDRESS_BITS, typename DataType>
const DataType& RuntimeMemory<ADDRESS_BITS, DataType>::operator[](const AddressType& address) const
{
    if (m_UseSparseMemory)
    {
        return m_SparseMemory[address];
    }
    else
    {
        return m_LinearMemory[address];
    }
}

template<typename DataType>
LinearMemory<DataType>::LinearMemory(const codasip_address_t memorySize)
  : m_Mem(memorySize)
{
    if (std::is_arithmetic<DataType>::value)
    {
        std::memset(m_Mem.data(), 0, sizeof(DataType) * memorySize);
    }
}

template<typename DataType>
DataType& LinearMemory<DataType>::operator[](const AddressType& address)
{
    return m_Mem[address];
}

template<typename DataType>
const DataType& LinearMemory<DataType>::operator[](const AddressType& address) const
{
    return m_Mem[address];
}

template<unsigned ADDRESS_BITS, typename DataType>
SparseMemory<ADDRESS_BITS, DataType>::SparseMemory(const codasip_address_t)
{}

template<unsigned ADDRESS_BITS, typename DataType>
DataType& SparseMemory<ADDRESS_BITS, DataType>::operator[](const AddressType& address)
{
    return m_Map[static_cast<KeyType>(address)];
}

template<unsigned ADDRESS_BITS, typename DataType>
const DataType& SparseMemory<ADDRESS_BITS, DataType>::operator[](const AddressType& address) const
{
    const auto it = m_Map.find(static_cast<KeyType>(address));
    return it == m_Map.cend() ? m_DefaultValue : it->second;
}

template<unsigned ADDRESS_BITS, typename DataType>
const DataType SparseMemory<ADDRESS_BITS, DataType>::m_DefaultValue = DataType{};

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_MEMORY_STORAGE_IMPL_H_
