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
 *  \date   Mar 8, 2016
 *  \brief  Definition of the class codasip::simulator::Memory.
 */

#ifndef SIMULATOR_RESOURCES_CSR_MEMORY_H_
#define SIMULATOR_RESOURCES_CSR_MEMORY_H_

#include "simulator/resources/csr_payload.h"
#include "simulator/resources/csr_value_with_expression.h"
#include "simulator/resources/detail/csr_memory_helpers.h"
#include "simulator/simbase/simulator_log.h"
#include "simulator/simbase/simulator_resources.h"

#include <stdexcept>

//#define MEMORY_INLINE inline
#define MEMORY_INLINE FORCE_INLINE

namespace codasip {

namespace simulator {
class DumpStream;
}

namespace resources {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::simulator::Memory
 *  \brief  Memory that can be placed within the ASIP or testbench. Represents
 *          simple, basic memory sub-system.
 *  \internal
 *  \note   Direct Memory Interface used to speed up IA simulation has been
 *          removed because it is protocol specific. The code has been removed
 *          and it has to be re-implemented.
 *  \}
 */
template<class MemoryCore>
class Memory : public MemoryCore, public simulator::MemoryInfo
{
public:
    /// \brief  Convenience shortcut for unit tests
    typedef typename MemoryCore::StorageType::data_type data_type;
    /**
     *  \copydoc Sentinel::Sentinel
     */
    template<typename T>
    Memory(const std::string& name, const Uid uid, const T& memory_size);
    /**
     *  \brief  Reset memory (reset request logic)
     */
    void reset();
    /**
     *  \brief  Move one clock cycle further
     */
    void clock_cycle();
    /**
     *  \} \{
     *  \brief  Interfaces callbacks
     */
    template<class T>
    void blocking_cb(Payload<T>& p, const Uid);
    template<class T>
    void transport_cb(Payload<T>& p, const Phase phase, const Uid);
    /**
     *  \} \{
     *  \brief  Sentinel methods
     */
    void set_log(simulator::Log& log);
    const std::string& get_signature() const;
    Uid get_uid() const;
    /**
     *  \}
     *  \copydoc  MemoryStorage::dump
     */
    void dump(simulator::DumpStream& stream);

    /// \copydoc ResourceInfo::GetUid
    Uid GetUid() const override;
    /// \copydoc ResourceInfo::GetName
    const std::string& GetName() const override;
    /// \copydoc ResourceInfo::GetBitWidth
    unsigned GetBitWidth() const override;
    /// \copydoc AddressableInfo::GetLAU
    unsigned GetLAU() const override;
    /// \copydoc AddressableInfo::GetAddrBitWidth
    unsigned GetAddrBitWidth() const override;
    /// \copydoc AddressableInfo::IsBig
    bool IsBig() const override;
    /// \copydoc MemoryInfo::GetSize
    simulator::Address GetSize() const override;

private:
    /// main storage
    typename MemoryCore::StorageType m_Storage;
};

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
template<typename T>
inline Memory<MemoryCore>::Memory(const std::string& name, const Uid uid, const T& memorySize)
  : MemoryCore()
  , m_Storage(name, uid, GetValue(memorySize))
{
    if (detail::IsMemorySizeInvalid(GetValue(memorySize)))
    {
        throw std::runtime_error{detail::MakeMemorySizeErrorMessage(name,
            GetValue(memorySize),
            GetValueExpression(memorySize))};
    }
}
////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline void Memory<MemoryCore>::reset()
{
    MemoryCore::Reset();
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
MEMORY_INLINE void Memory<MemoryCore>::clock_cycle()
{
    MemoryCore::ClockCycle();
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
template<class T>
MEMORY_INLINE void Memory<MemoryCore>::blocking_cb(Payload<T>& p, const Uid)
{
    m_Storage.blocking(p);
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
template<class T>
MEMORY_INLINE void Memory<MemoryCore>::transport_cb(Payload<T>& p, const Phase phase, const Uid)
{
    m_Storage.transport(p, phase);
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline void Memory<MemoryCore>::set_log(simulator::Log& log)
{
    m_Storage.set_log(log);
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline const std::string& Memory<MemoryCore>::get_signature() const
{
    return m_Storage.get_signature();
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline Uid Memory<MemoryCore>::get_uid() const
{
    return m_Storage.get_uid();
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline void Memory<MemoryCore>::dump(simulator::DumpStream& stream)
{
    m_Storage.dump(stream);
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline Uid Memory<MemoryCore>::GetUid() const
{
    return m_Storage.get_uid();
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline const std::string& Memory<MemoryCore>::GetName() const
{
    return m_Storage.get_name();
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline unsigned Memory<MemoryCore>::GetBitWidth() const
{
    return MemoryCore::StorageType::WORD_BITS;
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline unsigned Memory<MemoryCore>::GetLAU() const
{
    return MemoryCore::StorageType::BYTE_BITS;
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline unsigned Memory<MemoryCore>::GetAddrBitWidth() const
{
    return MemoryCore::StorageType::ADDR_BITS;
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline bool Memory<MemoryCore>::IsBig() const
{
    return MemoryCore::StorageType::ENDIANNESS == CP_BIG_ENDIAN;
}

////////////////////////////////////////////////////////////////////////////////
template<class MemoryCore>
inline simulator::Address Memory<MemoryCore>::GetSize() const
{
    return m_Storage.get_size();
}

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_MEMORY_H_
