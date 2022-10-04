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
 *  \author Zdenek Prikryl, Petr Hons
 *  \date   Oct 25, 2012
 *  \brief
 */

#ifndef SIMULATOR_RESOURCES_CSR_HELPERS_H_
#define SIMULATOR_RESOURCES_CSR_HELPERS_H_

#include "common/codasip_integer.h"
#include "common/codasip_vec.h"
#include "common/toolstypes.h"
#include "os/compiler.h"

#include <fstream>
#include <limits>
#include <type_traits>

namespace half_float {

// forward declaration
class half;

}   // namespace half_float

namespace codasip {
namespace resources {

class Sentinel;

// turn off force inlining for optimization level 0. It is needed for big cores on Windows
// so it will even be compilable
#if defined(CODASIP_OPTIMIZATION) && CODASIP_OPTIMIZATION == 0
#    define RES_INLINE inline
#else
#    define RES_INLINE FORCE_INLINE
#endif

namespace detail {

/**
 *  \class  codasip::resources::detail::ResourceAccess
 *  \brief  Resource access - abstraction to support unified read/write for
 *          resources and primitive types.
 */
class ResourceAccess
{
public:
    template<class T>
    static
        typename std::enable_if<std::is_base_of<Sentinel, typename std::remove_reference<T>::type>::value,
            typename T::data_type>::type
        Read(const T& resource)
    {
        return resource.read();
    }

    template<class T>
    static
        typename std::enable_if<!std::is_base_of<Sentinel, typename std::remove_reference<T>::type>::value,
            const T&>::type
        Read(const T& value)
    {
        return value;
    }

    template<class T, class V>
    static typename std::enable_if<std::is_base_of<Sentinel, T>::value>::type
    Write(T& resource, const V& value)
    {
        resource.write(value);
    }

    template<class T, class V>
    static typename std::enable_if<!std::is_base_of<Sentinel, T>::value>::type
    Write(T& var, const V& value)
    {
        var = static_cast<T>(value);
    }
};

/**
 *  \{
 *  \class  IsCodasipVectorHelper
 *  \brief  Helper class used to detect types based on \ref codasip_vec and
 *          \ref codasip_vec_flt template.
 */
template<class T>
struct IsCodasipVectorHelper : public std::integral_constant<bool, false>
{};

template<unsigned TB, unsigned EB, bool S, bool E>
struct IsCodasipVectorHelper<::codasip::codasip_vec<TB, EB, S, E>>
  : public std::integral_constant<bool, true>
{};

template<unsigned TB, unsigned EB, typename B, bool E>
struct IsCodasipVectorHelper<::codasip::codasip_vec_flt<TB, EB, B, E>>
  : public std::integral_constant<bool, true>
{};

/** \} */

/**
 *  \brief  Helper class for parameter passing optimization in simulator resource templates.
 */
template<typename T>
struct CallTraits
{
    /// Type that represents the value of type T.
    typedef typename std::decay<T>::type value_type;
    /// Type that represents a constant reference to type T.
    typedef
        typename std::add_lvalue_reference<typename std::add_const<value_type>::type>::type const_reference;
    /// Type that represents the best way to pass a parameter of type T to a function.
    typedef
        typename std::conditional<sizeof(value_type) <= sizeof(void*), const value_type, const_reference>::type
            param_type;
    /// Type that represents the best way to return value of a function.
    typedef
        typename std::conditional<sizeof(value_type) <= sizeof(void*), value_type, const_reference>::type return_type;
};
}   // namespace detail

/**
 * \brief Obtain needed bit-width to store a particular value
 * \tparam Value Value for which we want to get bit-width
 */
template<codasip_address_t VALUE>
struct BitWidthSelector
{
    ///
    enum
    {
        value = 1 + BitWidthSelector<(VALUE >> 1)>::value
    };
};
template<>
struct BitWidthSelector<0>
{
    enum
    {
        value = 1
    };
};
template<>
struct BitWidthSelector<1>
{
    enum
    {
        value = 1
    };
};

/**
 * \brief  Obtain info about a value whether it is a power of two or now
 * \param  value The value for which we want to get info about power.
 */
constexpr bool IsPowerOfTwo(codasip_address_t value)
{
    return (value >= 1) & !(value & (value - 1));
}

/// Uid type
typedef uint16_t Uid;
/// Counter type
typedef uint64_t Counter;
/// Intex for bi, bc
typedef unsigned Index;
/// Integer type used to represent data port index of a register file
typedef unsigned DataPortUid;

typedef enum
{
    CP_PROTOCOL_AHB_LITE,
    CP_PROTOCOL_AXI_LITE,
    CP_PROTOCOL_CPB,
    CP_PROTOCOL_AXI
} Protocol;

/**
 *  \brief  Transaction commands (read/write).
 *  \note   Using uint16 just for simple printing, uint8 would be sufficient but
 *          printing using std::ostream is not convenient.
 */
typedef enum : uint8_t
{
    /// no/idle transaction
    CP_CMD_NONE = 0,
    /// read
    CP_CMD_READ = 2,
    /// write
    CP_CMD_WRITE = 3,

    // just simulation commands
    /// blocking debug read
    CP_CMD_DREAD = 130,
    /// blocking debug write/load
    CP_CMD_DWRITE = 131,
    /// alias used during the application load
    CP_CMD_LOAD = 195,
} Command;

/**
 *  \brief  Transport phase on the bus.
 */
typedef enum : uint8_t
{
    /// address phase used for AHB, CPB
    CP_PHS_ADDRESS = 0,
    /// data/response phase for AHB, CPB
    CP_PHS_DATA = 1,
    /// AXI4 separate data phase
    CP_PHS_DATA_READ = 2,
    CP_PHS_DATA_WRITE = 3,
    /// AXI4 separate address phases
    CP_PHS_ADDRESS_READ = 4,
    CP_PHS_ADDRESS_WRITE = 5,
    /// AXI4 write response phase
    CP_PHS_RESPONSE_WRITE = 6
} Phase;

/// Endian types
typedef enum : bool
{
    /// Storage is handled as big endian
    CP_BIG_ENDIAN = 0,
    /// Storage is handled as little endian
    CP_LITTLE_ENDIAN = 1
} Endianness;

/// AHB burst mode
typedef enum : uint8_t
{
    CP_AHB_SINGLE = 0,
    CP_AHB_INCR = 1,
    CP_AHB_WRAP4 = 2,
    CP_AHB_INCR4 = 3,
    CP_AHB_WRAP8 = 4,
    CP_AHB_INCR8 = 5,
    CP_AHB_WRAP16 = 6,
    CP_AHB_INCR16 = 7
} AHBBurstMode;

/// AHB transfer type
typedef enum : uint8_t
{
    CP_AHB_IDLE = 0,
    CP_AHB_BUSY = 1,
    CP_AHB_NONSEQ = 2,
    CP_AHB_SEQ = 3
} AHBTransferType;

/// AHB transfer type
typedef enum : uint8_t
{
    CP_AHB_SIZE_8 = 0,
    CP_AHB_SIZE_16 = 1,
    CP_AHB_SIZE_32 = 2,
    CP_AHB_SIZE_64 = 3,
    CP_AHB_SIZE_128 = 4,
    CP_AHB_SIZE_256 = 5,
    CP_AHB_SIZE_512 = 6,
    CP_AHB_SIZE_1024 = 7,
    CP_AHB_SIZE_INVALID = 8
} AHBTransferSize;

/// AHB protection mode bits
typedef enum : uint8_t
{
    CP_AHB_DATA_ACCESS = 1,
    CP_AHB_PRIVILEGED = 2,
    CP_AHB_BUFFERABLE = 4,
    CP_AHB_CACHEABLE = 8,
    CP_AHB_PROT_DEFAULT = 3
} AHBProtectionMode;

/// AHB response codes
typedef enum : uint8_t
{
    CP_AHB_OKAY = 0,
    CP_AHB_ERROR = 1
} AHBResponseCode;

/// AHB ready codes (master in HREADY, slave in HREADYIN, slave out HREADYOUT)
/// use uint8_t instead of boolean type to avoid ambiguous error under MSVC
/// while printing the enumeration variables to output stream
typedef enum : uint8_t
{
    CP_AHB_WAIT = 0,
    CP_AHB_READY = 1
} AHBReadyCode;

/// AHB HWRITE signal values
typedef enum : uint8_t
{
    CP_AHB_READ = 0,
    CP_AHB_WRITE = 1
} AHBReadWriteCode;

/// AHB masterlock codes
typedef enum : uint8_t
{
    CP_AHB_UNLOCK = 0,
    CP_AHB_LOCK = 1
} AHBMasterLockCode;

/// AXI4-Lite write strobe (the bus is limited to 64bits, 64/8)
typedef uint8_t AXIWriteStrobe;

/// AXI burst size
typedef enum : uint8_t
{
    CP_AXI_SIZE_8 = 0,
    CP_AXI_SIZE_16 = 1,
    CP_AXI_SIZE_32 = 2,
    CP_AXI_SIZE_64 = 3,
    CP_AXI_SIZE_128 = 4,
    CP_AXI_SIZE_256 = 5,
    CP_AXI_SIZE_512 = 6,
    CP_AXI_SIZE_1024 = 7,
    CP_AXI_SIZE_INVALID = 8
} AXIBurstSize;

/// AXI burst type
typedef enum : uint8_t
{
    CP_AXI_BURST_FIXED = 0,
    CP_AXI_BURST_INCR = 1,
    CP_AXI_BURST_WRAP = 2,
    CP_AXI_BURST_RESERVED = 3
} AXIBurstType;

/// AXI lock type
typedef enum : uint8_t
{
    CP_AXI_LOCK_NORMAL = 0,
    CP_AXI_LOCK_EXCLUSIVE = 1
} AXILockCode;

/// AXI protection mode
typedef enum : uint8_t
{
    CP_AXI_PROT_NONE = 0,
    CP_AXI_PROT_PRIVILEGED = 1,
    CP_AXI_PROT_NON_SECURE = 2,
    CP_AXI_PROT_INSTR = 4,
    CP_AXI_PROT_DEFAULT = 3,
    CP_AXI_PROT_ALL = 7
} AXIProtectionMode;

// AXI cache mode
typedef enum : uint8_t
{
    CP_AXI_CACHE_NONE = 0,
    CP_AXI_CACHE_BUFFERABLE = 1,
    CP_AXI_CACHE_MODIFIABLE = 2,
    CP_AXI_CACHE_ALLOCATE = 4,
    CP_AXI_CACHE_OTHER_ALLOCATE = 8,
    CP_AXI_CACHE_ALL = 15
} AXICacheMode;

/// AXI last code
typedef enum : uint8_t
{
    CP_AXI_NOT_LAST = 0,
    CP_AXI_LAST = 1
} AXILastCode;

/// AXI phase flags
typedef enum : uint8_t
{
    CP_AXI_PHASE_ADDRESS = 1,
    CP_AXI_PHASE_DATA = 2,
    CP_AXI_PHASE_RESPONSE = 4
} AXIPhaseFlag;

/// AXI response codes
typedef enum : uint8_t
{
    CP_AXI_OKAY = 0,
    CP_AXI_EXOKAY = 1,
    CP_AXI_SLVERR = 2,
    CP_AXI_DECERR = 3
} AXIResponseCode;

/// AXI ready code
typedef enum : uint8_t
{
    CP_AXI_WAIT = 0,
    CP_AXI_READY = 1
} AXIReadyCode;

/// AXI valid code
typedef enum : uint8_t
{
    CP_AXI_INVALID = 0,
    CP_AXI_VALID = 1
} AXIValidCode;

// Codasip Processor Bus

/// CPB valid code
typedef enum : uint8_t
{
    CP_CPB_INVALID = 0,
    CP_CPB_VALID = 1
} CPBValidCode;

/// CPB WRITE signal values
typedef enum : uint8_t
{
    CP_CPB_READ = 0,
    CP_CPB_WRITE = 1
} CPBReadWriteCode;

/// CPB ready code
typedef enum : uint8_t
{
    CP_CPB_WAIT = 0,
    CP_CPB_READY = 1
} CPBReadyCode;

/// CPB response codes
typedef enum : uint8_t
{
    CP_CPB_OKAY = 0,
    CP_CPB_ERROR = 1
} CPBResponseCode;

/**
 *  \brief  Enumeration of possible cache operations.
 */
enum CacheOperation : uint8_t
{
    OP_NONE,
    OP_I_INVALIDATE_ADDRESS,
    OP_I_INVALIDATE_LINE,
    OP_I_INVALIDATE_ALL,
    OP_D_INVALIDATE_ADDRESS,
    OP_D_INVALIDATE_LINE,
    OP_D_INVALIDATE_ALL,
    OP_D_FLUSH_ADDRESS,
    OP_D_FLUSH_LINE,
    OP_D_FLUSH_ALL
};

template<class T, typename U = void>
struct BitWidthTypeSelector
{
    typedef typename std::decay<T>::type type;
    // assuming codasip type
    enum
    {
        value = type::BIT_WIDTH
    };
};
template<class T>
struct BitWidthTypeSelector<T,
    typename std::enable_if<std::is_same<typename std::decay<T>::type, bool>::value>::type>
{
    typedef typename std::decay<T>::type type;
    enum
    {
        value = 1
    };
};
template<class T>
struct BitWidthTypeSelector<T,
    typename std::enable_if<std::is_arithmetic<typename std::decay<T>::type>::value &&
        !std::is_same<typename std::decay<T>::type, bool>::value>::type>
{
    typedef typename std::decay<T>::type type;
    enum
    {
        value = sizeof(type) * CHAR_BIT
    };
};
template<class T>
struct BitWidthTypeSelector<T,
    typename std::enable_if<std::is_same<typename std::decay<T>::type, ::half_float::half>::value>::type>
{
    typedef typename std::decay<T>::type type;
    enum
    {
        value = 16
    };
};

/**
 *  \brief  Helper class for holding write mask for sparse registers.
 *  \tparam T storage data type
 *  \tparam IS_ENABLED toggles the between the full and the dummy implementation
 */
template<typename T, bool IS_ENABLED>
class WriteMaskHelper
{
public:
    void SetWriteMask(T mask)
    {
        m_WriteMask = std::move(mask);
    }

    T MaskValue(typename detail::CallTraits<T>::param_type value,
        typename detail::CallTraits<T>::param_type defaultValue) const
    {
        return (value & m_WriteMask) | (defaultValue & ~m_WriteMask);
    }

private:
    // will be initialized explicitly in simulator's constructor
    T m_WriteMask;
};

/**
 *  \brief  Dummy specialization of the WriteMaskHelper class.
 *
 *  Implementation of the methods is omitted intentionally. They should not be called when
 *  the mask is disabled and this way we'll get a compile error straight away.
 */
template<typename T>
class WriteMaskHelper<T, false>
{
public:
    void SetWriteMask(const T&) {}
    T MaskValue(typename detail::CallTraits<T>::param_type /*value*/,
        typename detail::CallTraits<T>::param_type /*defaultValue*/) const
    {
        THROW_ERROR() << "Calling MaskValue on disabled write mask!" << std::endl;
    }
};

template<class T>
RES_INLINE codasip_address_t GetAlignedAddress(const codasip_address_t addr)
{
    if (T::BPW == 1)
    {
        return addr;
    }
    return addr / T::BPW;
}

/**
 * \brief  Safe left shift - correctly handle too big shiftBits value (return 0).
 */
template<class T>
RES_INLINE T LeftShift(const T value, const Index shiftBits)
{
    return shiftBits < BitWidthTypeSelector<T>::value ? value << shiftBits : static_cast<T>(0);
}

/**
 * Type trait that converts value to type
 */
template<bool _B>
struct Bool2Type
{};

/**
 * Function to return storage type of n BITS
 */
template<int _BitWidth, bool _IsSigned>
struct TypeSelector
{
    typedef typename std::conditional<_IsSigned == false,
        // unsigned types, use bit approximation, the resource will truncate
        // an unneeded part
        typename std::conditional<_BitWidth <= sizeof(uint8_t) * CHAR_BIT,
            uint8_t,
            typename std::conditional<_BitWidth <= sizeof(uint16_t) * CHAR_BIT,
                uint16_t,
                typename std::conditional<_BitWidth <= sizeof(uint32_t) * CHAR_BIT,
                    uint32_t,
                    typename std::conditional<_BitWidth <= sizeof(uint64_t) * CHAR_BIT,
                        uint64_t,
                        codasip::Integer<_BitWidth, false>>::type>::type>::type>::type,
        // signed types, the bit-width must be precise
        typename std::conditional<_BitWidth == sizeof(int8_t) * CHAR_BIT,
            int8_t,
            typename std::conditional<_BitWidth == sizeof(int16_t) * CHAR_BIT,
                int16_t,
                typename std::conditional<_BitWidth == sizeof(int32_t) * CHAR_BIT,
                    int32_t,
                    typename std::conditional<_BitWidth == sizeof(int64_t) * CHAR_BIT,
                        int64_t,
                        codasip::Integer<_BitWidth, true>>::type>::type>::type>::type>::type type;
};

/**
 * \brief Template shift
 * \param _Shift    Number of shift, if positive, left shift (<<) will be used, otherwise right shift (>>) will be used
 * \usage
 *      custom_shift<2>::shift(4);  //Result: 16
 *      custom_shift<-2>::shift(4); //Result: 1
 */
template<int _Shift>
struct CustomShift
{
    /// Function that calls left or right shift according to template parameter _Shift
    template<typename _Type>
    static _Type Shift(const _Type value)
    {
        return Shift(value, Bool2Type<_Shift >= 0>());
    }

    /// Function for left shift
    template<typename _Type>
    static _Type Shift(const _Type value, const Bool2Type<true>)
    {
        return value << _Shift;
    }

    /// Function for left right
    template<typename _Type>
    static _Type Shift(const _Type value, const Bool2Type<false>)
    {
        return value >> -_Shift;
    }
};

template<Index _BW>
RES_INLINE void CopyInteger(uint32_t* dst, const Integer<_BW, false>& src)
{
    enum
    {
        NATIVE_BIT_WIDTH = std::numeric_limits<uint32_t>::digits,
        SIZE_IN_BYTES = sizeof(uint32_t) * ((_BW + NATIVE_BIT_WIDTH) / NATIVE_BIT_WIDTH)
    };
    std::memcpy(dst, src.get_data(), SIZE_IN_BYTES);
}

template<Index _BW>
RES_INLINE void CopyInteger(Integer<_BW, false>& dst, const uint32_t* src)
{
    enum
    {
        NATIVE_BIT_WIDTH = std::numeric_limits<uint32_t>::digits,
        SIZE_IN_BYTES = sizeof(uint32_t) * ((_BW + NATIVE_BIT_WIDTH) / NATIVE_BIT_WIDTH)
    };
    std::memcpy(dst.get_data(), src, SIZE_IN_BYTES);
    dst.bit_correction();
}

/**
 * \brief Wrapper for correct handling pragma simulator. It allows also nested functions etc.
 */
class BlockPragmaSimulator
{
public:
    /**
     * \brief Increase counter
     * \param checker Reference to the checker
     */
    BlockPragmaSimulator(Index& checker)
      : m_Checker(checker)
    {
        ++m_Checker;
    }
    /**
     * \brief Decrease counter
     */
    ~BlockPragmaSimulator()
    {
        --m_Checker;
    }

private:
    /// reference to the pointer
    Index& m_Checker;
};

namespace detail {

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::resources::detail::DebugLogger
 *  \brief  Enables logging of the debug outputs to a file.
 *
 *  This is especially useful when debugging zero tolerance debugger checks as the debugger
 *  timeouts on too many stdout prints.
 *  \}
 */
class DebugLogger
{
public:
    /**
     *  \brief  Deleted copy and move constructors and assignment operators.
     *  \{
     */
    DebugLogger(const DebugLogger&) = delete;
    DebugLogger(DebugLogger&&) = delete;
    DebugLogger& operator=(const DebugLogger&) = delete;
    DebugLogger& operator=(DebugLogger&&) = delete;
    /// \}

    /// Destructor.
    ~DebugLogger()
    {
        m_Log.close();
    }
    /// Returns a DebugLogger instance.
    static DebugLogger& Get()
    {
        static DebugLogger instance;
        return instance;
    }
    /**
     *  \brief  Writes given value to output file stream.
     *  \param  value   Value that should be written to output file stream.
     *  \return Output file stream.
     */
    template<typename T>
    std::ostream& operator<<(T&& value)
    {
        m_Log << value;
        return m_Log;
    }

private:
    /// Constructor.
    DebugLogger()
      : m_Log("sim_log.txt")
    {}
    /// Logging file stream.
    std::ofstream m_Log;
};

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_HELPERS_H_
