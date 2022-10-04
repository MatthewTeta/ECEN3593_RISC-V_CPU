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
 *  \author Martin Ministr
 *  \date   11. 4. 2017
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_SIMBASE_SIMULATOR_HELPERS_H_
#define SIMULATOR_SIMBASE_SIMULATOR_HELPERS_H_

#include <string>

#include "common/codasip_integer.h"
#include "common/codasip_vec.h"
#include "simulator/resources/csr_helpers.h"
#include "utility/codasiputils.h"
#include "contrib/half_float/half_float.h"
#include <type_traits>
#include <cstring>

// following definitions are used for generated code
// definitions of bool, true and false
#include <cstdbool>

namespace codasip {
namespace simulator {

namespace detail {

template<typename T>
using is_native_float = typename std::enable_if<std::is_floating_point<T>::value, T>::type;

template<typename T>
using is_half_float = typename std::enable_if<std::is_same<T, ::half_float::half>::value, T>::type;

// helpers to identify codasip_vec type for codasip_bitreverse sfinae
template<typename T, typename _ = void>
struct is_codasip_vec : std::false_type
{};

template<typename T>
struct is_codasip_vec<T,
    typename std::conditional<false, decltype(T::ELEM_COUNT), void>::type>
  : public std::true_type
{};

}   // namespace detail

// constants
const std::string SIM_EXIT_CODE_FILE = "sim_exit_code";

// types declared here should be used only within simulator helpers, only few of them
// warning: when adding new types, erase them from simulator_helpers_test.cpp (Windows issues)
typedef codasip::Integer<1, false> uint1;
typedef codasip::Integer<32, true> int32;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Internal Functions

/// Helper for float casts
template<class To, class From>
struct BitcastHelperImpl
{
    static To Cast(const From& from)
    {
        static_assert(sizeof(To) == sizeof(From), "Invalid bitcast, sizeof mismatch");
        To tmp;
        std::memcpy(&tmp, &from, sizeof(From));
        return tmp;
    }
};

/// Helper for float casts specialization for cast to half_float
template<class From>
struct BitcastHelperImpl< ::half_float::half, From>
{
    static ::half_float::half Cast(const From& from)
    {
        return ::half_float::detail::half_bitcast(
            static_cast< ::half_float::detail::uint16>(from));
    }
};

/// Helper for float casts specialization for cast from half_float
template<class To>
struct BitcastHelperImpl<To, ::half_float::half>
{
    static To Cast(const ::half_float::half from)
    {
        ::half_float::detail::uint16 bitcast = ::half_float::detail::half_bitcast(from);
        return static_cast<To>(bitcast);
    }
};

/// Helper for float casts specialization for cast from float vector to int
template<class To, unsigned _VecBits, unsigned _ElemBits, typename _ElemType, bool _Endianness>
struct BitcastHelperImpl<To, ::codasip::codasip_vec_flt<_VecBits, _ElemBits, _ElemType, _Endianness> >
{
    static To Cast(const ::codasip::codasip_vec_flt<_VecBits, _ElemBits, _ElemType, _Endianness>& from)
    {
        return from.get_as_bits();
    }
};

/// Helper for float casts specialization for cast from float vector to int
template<class To, unsigned _VecBits, unsigned _ElemBits, bool _Signed, bool _Endianness>
struct BitcastHelperImpl<To, ::codasip::codasip_vec<_VecBits, _ElemBits, _Signed, _Endianness> >
{
    static To Cast(const ::codasip::codasip_vec<_VecBits, _ElemBits, _Signed, _Endianness>& from)
    {
        return from.get_as_bits();
    }
};

/**
 * \brief Helper for bitcasts to/from float types in simulator
 */
template<class To, class From>
inline To BitcastHelper(const From& from)
{
    return BitcastHelperImpl<To, typename std::decay<From>::type>::Cast(from);
}

namespace detail {

/**
 *  \internal
 *  \class  BitConcatHelper
 *  \brief  Helper class used to collect useful type informations for bit-concatenation function.
 */
template<typename T1, typename T2>
struct BitConcatHelper
{   /// bare type of the first operand without any qualifiers/specifiers
    typedef typename std::decay<T1>::type LhsType;
    /// bare type of the seond operand without any qualifiers/specifiers
    typedef typename std::decay<T2>::type RhsType;

    enum : unsigned
    {   /// bit-width of the first operand
        LHS_BITS = std::numeric_limits<LhsType>::digits + std::numeric_limits<LhsType>::is_signed,
        /// bit-width of the second operand
        RHS_BITS = std::numeric_limits<RhsType>::digits + std::numeric_limits<RhsType>::is_signed,
        /// bit-width of the result
        BITS = LHS_BITS + RHS_BITS
    };
    /// \brief  Resulting type of the bit-concatenation operation
    typedef ::codasip::Integer<BITS, false> type;
};

template<typename T, typename U = typename std::decay<T>::type>
struct MakeUnsignedHelper
{
    typedef typename std::make_unsigned<U>::type type;
};
template<typename T>
struct MakeUnsignedHelper<T, bool>
{
    typedef bool type;
};

}  // namespace codasip::simulator::detail

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Debug Functions

/**
 * \brief Store program exit code to a file named 'sim_exit_code'.
 * \param[in] code
 */
void codasip_store_exit_code(int32 code);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Compiler Functions

/**
 * \brief Returns value representing undefined value, -1.
 */
template<typename T>
T codasip_undef()
{
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Arithmetic Functions

template<typename T>
uint1 codasip_borrow_sub(T a, T b)
{
    typedef typename std::make_unsigned<typename std::decay<T>::type>::type UT;
    return static_cast<UT>(a) < static_cast<UT>(b);
}

template<typename T>
uint1 codasip_borrow_sub_c(T a, T b, uint1 c)
{
    typedef typename std::make_unsigned<typename std::decay<T>::type>::type UT;
    return c
        ? static_cast<UT>(a) < static_cast<UT>(a - b - c) || static_cast<UT>(b) == static_cast<UT>(-1)
        : static_cast<UT>(a) < static_cast<UT>(b);
}

template<typename T>
uint1 codasip_carry_add(T a, T b)
{
    typedef typename std::make_unsigned<typename std::decay<T>::type>::type UT;
    return static_cast<UT>(a + b) < static_cast<UT>(a);
}

template<typename T>
uint1 codasip_carry_add_c(T a, T b, uint1 c)
{
    typedef typename std::make_unsigned<typename std::decay<T>::type>::type UT;
    return c
        ? static_cast<UT>(a + b + c) <= static_cast<UT>(a)
        : static_cast<UT>(a + b + c) <  static_cast<UT>(a);
}

template<typename T>
T codasip_ctlz(T src)
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    T res = 0;
    while (res < BIT_WIDTH && (src & ((T)1 << ((BIT_WIDTH - 1) - res))) == 0)
    {
        res++;
    }
    return res;
}

template<typename T>
T codasip_cttz(T src)
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    T res = 0;
    while (res < BIT_WIDTH && (src & ((T)1 << res)) == 0)
    {
        res++;
    }
    return res;
}

template<typename T>
T codasip_ctlo(T src)
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    T res = 0;
    while (res < BIT_WIDTH && (src & ((T)1 << ((BIT_WIDTH - 1) - res))) != 0)
    {
        res++;
    }
    return res;
}

template<typename T>
T codasip_ctto(T src)
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    T res = 0;
    while (res < BIT_WIDTH && (src & ((T)1 << res)) != 0)
    {
        res++;
    }
    return res;
}

template<typename T>
T codasip_ctpop(T src)
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    T res = 0;
    for (int i = 0; i < BIT_WIDTH; i++)
    {
        if ((src >> i) & 1)
        {
            res++;
        }
    }
    return res;
}

template<typename T>
uint1 codasip_overflow_add(T a, T b)
{
    typedef typename std::make_signed<typename std::decay<T>::type>::type ST;
    return static_cast<ST>((a ^ (a + b)) & (b ^ (a + b))) < 0;
}

template<typename T>
uint1 codasip_overflow_add_c(T a, T b, uint1 c)
{
    typedef typename std::make_signed<typename std::decay<T>::type>::type ST;
    return static_cast<ST>((a ^ (a + b + c)) & (b ^ (a + b + c))) < 0;
}

template<typename T>
uint1 codasip_overflow_sub(T a, T b)
{
    typedef typename std::make_signed<typename std::decay<T>::type>::type ST;
    return static_cast<ST>((a ^ b) & (a ^ (a - b))) < 0;
}

template<typename T>
uint1 codasip_overflow_sub_c(T a, T b, uint1 c)
{
    typedef typename std::make_signed<typename std::decay<T>::type>::type ST;
    return static_cast<ST>((a ^ b) & (a ^ (a - b - c))) < 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Saturated Arithmetic Functions

template<typename T>
typename std::enable_if<!std::is_signed<T>::value, T>::type codasip_usadd(T a, T b)
{
    return codasip_carry_add<T>(a, b) ? (T)-1 /*unsigned max*/ : a + b;
}

template<typename T>
typename std::enable_if<!std::is_signed<T>::value, uint1>::type codasip_usadd_occured(T a, T b)
{
    return codasip_carry_add<T>(a, b);
}

template<typename T>
typename std::enable_if<!std::is_signed<T>::value, T>::type codasip_ussub(T a, T b)
{
    return codasip_borrow_sub<T>(a, b) ? (T)-1 /*unsigned max*/ : a - b;
}

template<typename T>
typename std::enable_if<!std::is_signed<T>::value, uint1>::type codasip_ussub_occured(T a, T b)
{
    return codasip_borrow_sub<T>(a, b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// RTL Functions
/**
 *  \brief  Provides replication operator implementation for the simulator.
 *  \tparam R target return type
 *  \param  value source value to replicate
 *  \param  n number of replications
 */
template<typename R, typename T>
R codasip_replicate( const T& value, const unsigned n )
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    typedef typename detail::MakeUnsignedHelper<T>::type UT;
    R result( static_cast<UT>(value) );
    for ( unsigned ii = 1; ii < n; ++ii )
    {
        result <<= BIT_WIDTH;
        result |= static_cast<R>(static_cast<UT>(value));
    }
    return result;
}

/**
 *  \brief  Provides bit concatenation operation implementation for the simulator.
 *  \param  a first operand
 *  \param  b second operand
 */
template<typename T1, typename T2>
typename detail::BitConcatHelper<T1, T2>::type codasip_concatenate( const T1& a, const T2& b )
{
    typedef detail::BitConcatHelper<T1, T2> HelperType;
    typedef typename detail::MakeUnsignedHelper<typename HelperType::LhsType>::type UT1;
    typedef typename detail::MakeUnsignedHelper<typename HelperType::RhsType>::type UT2;
    typedef typename HelperType::type RT;

    RT result( static_cast<UT1>(a) );
    result <<= HelperType::RHS_BITS;
    result |= static_cast<UT2>(b);
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Floating Point Functions

template<typename T>
detail::is_native_float<T> codasip_ceil(T a)
{
    return std::ceil(a);
}

template<typename T>
detail::is_half_float<T> codasip_ceil(T a)
{
    return half_float::detail::functions::ceil(a);
}

template<typename T>
detail::is_native_float<T> codasip_cos(T a)
{
    return std::cos(a);
}

template<typename T>
detail::is_half_float<T> codasip_cos(T a)
{
    return half_float::detail::functions::cos(a);
}

template<typename T>
detail::is_native_float<T> codasip_exp(T a)
{
    return std::exp(a);
}

template<typename T>
detail::is_half_float<T> codasip_exp(T a)
{
    return half_float::detail::functions::exp(a);
}

template<typename T>
detail::is_native_float<T> codasip_fabs(T a)
{
    return std::fabs(a);
}

template<typename T>
detail::is_half_float<T> codasip_fabs(T a)
{
    return half_float::detail::fabs(a);
}

// scalar float
template<typename CompareType, typename T>
typename std::enable_if<std::is_floating_point<T>::value, CompareType>::type IsNan(T a)
{
    return std::isnan(a);
}

template<typename CompareType, typename T>
typename std::enable_if<std::is_same<T, ::half_float::half>::value, CompareType>::type IsNan(T a)
{
    return half_float::detail::functions::isnan(a);
}

// vector float
template<typename CompareType, typename T>
typename std::enable_if<!std::is_floating_point<T>::value
    && !std::is_same<T, ::half_float::half>::value, CompareType>::type IsNan(T a)
{
    CompareType res;
    for (size_t i = 0; i < T::ELEM_COUNT; i++)
    {
        res[i] = IsNan<bool>(a[i]);
    }
    return res;
}

/**
 * \brief Compares two floats or two float vectors if they are comparable.
 *        CompareType could be uint1 or vector of uintX, where X is size of T vector item.
 * \note  Similar description fits all other float compare functions.
 * \param[in] a
 * \param[in] b
 */
template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_ord(T a, T b)
{
    return (!IsNan<CompareType, T>(a)) & (!IsNan<CompareType, T>(b));
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_oeq(T a, T b)
{
    return codasip_fcmp_ord<CompareType, T>(a, b) & (a == b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_oge(T a, T b)
{
    return codasip_fcmp_ord<CompareType, T>(a, b) & (a >= b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_ogt(T a, T b)
{
    return codasip_fcmp_ord<CompareType, T>(a, b) & (a > b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_ole(T a, T b)
{
    return codasip_fcmp_ord<CompareType, T>(a, b) & (a <= b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_olt(T a, T b)
{
    return codasip_fcmp_ord<CompareType, T>(a, b) & (a < b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_one(T a, T b)
{
    return codasip_fcmp_ord<CompareType, T>(a, b) & (a != b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_uno(T a, T b)
{
    return IsNan<CompareType, T>(a) | IsNan<CompareType, T>(b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_ueq(T a, T b)
{
    return codasip_fcmp_uno<CompareType, T>(a, b) | (a == b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_uge(T a, T b)
{
    return codasip_fcmp_uno<CompareType, T>(a, b) | (a >= b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_ugt(T a, T b)
{
    return codasip_fcmp_uno<CompareType, T>(a, b) | (a > b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_ule(T a, T b)
{
    return codasip_fcmp_uno<CompareType, T>(a, b) | (a <= b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_ult(T a, T b)
{
    return codasip_fcmp_uno<CompareType, T>(a, b) | (a < b);
}

template<typename CompareType, typename T>
typename std::enable_if<!std::is_integral<T>::value, CompareType>::type codasip_fcmp_une(T a, T b)
{
    return codasip_fcmp_uno<CompareType, T>(a, b) | (a != b);
}

template<typename T>
detail::is_native_float<T> codasip_floor(T a)
{
    return std::floor(a);
}

template<typename T>
detail::is_half_float<T> codasip_floor(T a)
{
    return half_float::detail::floor(a);
}

template<typename T>
detail::is_native_float<T> codasip_fma(T a, T b, T c)
{
    return std::fma(a, b, c);
}

template<typename T>
detail::is_half_float<T> codasip_fma(T a, T b, T c)
{
    return half_float::detail::fma(a, b, c);
}

template<typename T>
detail::is_native_float<T> codasip_frem(T a, T b)
{
    return std::fmod(a, b);
}

template<typename T>
detail::is_half_float<T> codasip_frem(T a, T b)
{
    return half_float::detail::fmod(a, b);
}

/**
 * \brief Get rounding mode.
 */
int32 codasip_fpu_getround();
/**
 * \brief Sets rounding mode.
 * \param[in] mode rounding mode
 */
void codasip_fpu_setround(int32 mode);

/**
 * \brief Test FPU exception
 */
int32 codasip_fpu_test_exception(const int32 exception);
/**
 * \brief Clear FPU exception
 */
int32 codasip_fpu_clear_exception(const int32 exception);

template<typename T>
detail::is_native_float<T> codasip_ftrunc(T a)
{
    return std::trunc(a);
}

template<typename T>
detail::is_half_float<T> codasip_ftrunc(T a)
{
    return half_float::detail::functions::trunc(a);
}

template<typename T>
detail::is_native_float<T> codasip_log(T a)
{
    return std::log(a);
}

template<typename T>
detail::is_half_float<T> codasip_log(T a)
{
    return half_float::detail::functions::log(a);
}

template<typename T>
detail::is_native_float<T> codasip_pow(T a, T b)
{
    return std::pow(a, b);
}

template<typename T>
detail::is_half_float<T> codasip_pow(T a, T b)
{
    return half_float::detail::functions::pow(a, b);
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value \
    || std::is_same<T, ::half_float::half>::value, T>::type codasip_powi(T a, int32 b)
{
    return codasip_pow<T>(a, (T)b);
}

template<typename T>
detail::is_native_float<T> codasip_rint(T a)
{
    return std::rint(a);
}

template<typename T>
detail::is_half_float<T> codasip_rint(T a)
{
    return half_float::detail::functions::rint(a);
}

template<typename T>
detail::is_native_float<T> codasip_round(T a)
{
    return std::round(a);
}

template<typename T>
detail::is_half_float<T> codasip_round(T a)
{
    return half_float::detail::functions::round(a);
}

template<typename T>
detail::is_native_float<T> codasip_sin(T a)
{
    return std::sin(a);
}

template<typename T>
detail::is_half_float<T> codasip_sin(T a)
{
    return half_float::detail::functions::sin(a);
}

template<typename T>
detail::is_native_float<T> codasip_sqrt(T a)
{
    return std::sqrt(a);
}

template<typename T>
detail::is_half_float<T> codasip_sqrt(T a)
{
    return half_float::detail::functions::sqrt(a);
}

// Macros for vector float built-ins
#define VECTOR_FLOAT_OP_1ARG(name) \
    template<typename T> \
    typename std::enable_if<!std::is_floating_point<T>::value \
        && !std::is_same<T, ::half_float::half>::value, T>::type name(T a) \
    { \
        T res; \
        for (size_t i = 0; i < T::ELEM_COUNT; i++) \
        { \
            res[i] = name(a[i]); \
        } \
        return res; \
    }

#define VECTOR_FLOAT_OP_2ARG(name) \
    template<typename T> \
    typename std::enable_if<!std::is_floating_point<T>::value \
        && !std::is_same<T, ::half_float::half>::value, T>::type name(T a, T b) \
    { \
        T res; \
        for (size_t i = 0; i < T::ELEM_COUNT; i++) \
        { \
            res[i] = name(a[i], b[i]); \
        } \
        return res; \
    }

#define VECTOR_FLOAT_OP_3ARG(name) \
    template<typename T> \
    typename std::enable_if<!std::is_floating_point<T>::value \
        && !std::is_same<T, ::half_float::half>::value, T>::type name(T a, T b, T c) \
    { \
        T res; \
        for (size_t i = 0; i < T::ELEM_COUNT; i++) \
        { \
            res[i] = name(a[i], b[i], c[i]); \
        } \
        return res; \
    }

VECTOR_FLOAT_OP_1ARG(codasip_ceil)
VECTOR_FLOAT_OP_1ARG(codasip_cos)
VECTOR_FLOAT_OP_1ARG(codasip_exp)
VECTOR_FLOAT_OP_1ARG(codasip_fabs)
VECTOR_FLOAT_OP_1ARG(codasip_floor)
VECTOR_FLOAT_OP_3ARG(codasip_fma)
VECTOR_FLOAT_OP_2ARG(codasip_frem)
VECTOR_FLOAT_OP_1ARG(codasip_ftrunc)
VECTOR_FLOAT_OP_1ARG(codasip_log)
VECTOR_FLOAT_OP_2ARG(codasip_pow)

template<typename T> \
typename std::enable_if<!std::is_integral<T>::value \
    && !std::is_floating_point<T>::value \
    && !std::is_same<T, ::half_float::half>::value, T>::type codasip_powi(T a, const int32 b) \
{ \
    T res; \
    for (size_t i = 0; i < T::ELEM_COUNT; i++) \
    { \
        res[i] = codasip_powi(a[i], b); \
    } \
    return res; \
}

VECTOR_FLOAT_OP_1ARG(codasip_rint)
VECTOR_FLOAT_OP_1ARG(codasip_round)
VECTOR_FLOAT_OP_1ARG(codasip_sin)
VECTOR_FLOAT_OP_1ARG(codasip_sqrt)

#undef VECTOR_FLOAT_OP_1ARG
#undef VECTOR_FLOAT_OP_2ARG
#undef VECTOR_FLOAT_OP_3ARG

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Vector Functions

template<typename ValueVectorType, typename ConditionVectorType>
ValueVectorType codasip_select(ConditionVectorType cond, ValueVectorType a, ValueVectorType b)
{
    ValueVectorType res;
    for (size_t i = 0; i < ValueVectorType::ELEM_COUNT; i++)
    {
        res[i] = cond[i] ? a[i] : b[i];
    }
    return res;
}

template<typename TargetVectorType, typename SourceVectorType>
TargetVectorType codasip_sext(SourceVectorType a)
{
    TargetVectorType res;
    for (size_t i = 0; i < TargetVectorType::ELEM_COUNT; i++)
    {
        res[i] = (codasip::Integer<TargetVectorType::ELEM_BITS, true>)
            (codasip::Integer<SourceVectorType::ELEM_BITS, true>)a[i];
    }
    return res;
}

template<typename MaskVectorType, typename ValueVectorType>
ValueVectorType codasip_shufflevector(ValueVectorType a, ValueVectorType b, MaskVectorType mask)
{
    ValueVectorType res;
    for (size_t i = 0; i < ValueVectorType::ELEM_COUNT; i++)
    {
        size_t pos = mask[i];
        res[i] = (pos < ValueVectorType::ELEM_COUNT)? a[pos] : b[pos - ValueVectorType::ELEM_COUNT];
    }
    return res;
}

/**
 * \brief Quarantined to work only when target element type is smaller then source element type.
 * \param[in] a source vector
 */
template<typename TargetVectorType, typename SourceVectorType>
TargetVectorType codasip_trunc(SourceVectorType a)
{
    TargetVectorType res;
    for (size_t i = 0; i < TargetVectorType::ELEM_COUNT; i++)
    {
        res[i] = a[i];
    }
    return res;
}

template<typename TargetVectorType, typename SourceVectorType>
TargetVectorType codasip_zext(SourceVectorType a)
{
    TargetVectorType res;
    for (size_t i = 0; i < TargetVectorType::ELEM_COUNT; i++)
    {
        res[i] = (codasip::Integer<TargetVectorType::ELEM_BITS, false>)
            (codasip::Integer<SourceVectorType::ELEM_BITS, false>)a[i];
    }
    return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Fixed Point Functions

template<typename T>
//typename std::enable_if<std::is_signed<T>::value, T>::type FIXME does not work
T codasip_fx_div(T a, T b, int32 fract_bits, uint1 rounding_flag)
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    typedef codasip::Integer<2 * BIT_WIDTH, true> Type;

    Type c = a;
    Type d = b;

    return rounding_flag ? ((c << fract_bits) + (d >> 2)) / d : (c << fract_bits) / d;
}

template<typename FixedPointType, typename FloatType>
typename std::enable_if</*std::is_signed<FixedPointType>::value FIXME does not work
    && */(std::is_floating_point<FloatType>::value || std::is_same<FloatType, ::half_float::half>::value),
FixedPointType>::type codasip_fx_fptofx_to(FloatType a, int32 fract_bits)
{
    FloatType res = a * codasip_pow((FloatType)2, (FloatType)fract_bits);
    return (FixedPointType)(uint64_t)(codasip_rint(res));
}

template<typename FloatType, typename FixedPointType>
typename std::enable_if</*std::is_signed<FixedPointType>::value FIXME does not work
    && */(std::is_floating_point<FloatType>::value || std::is_same<FloatType, ::half_float::half>::value),
FloatType>::type codasip_fx_fxtofp_to(FixedPointType a, int32 fract_bits)
{
    return (FloatType)a * codasip_pow((FloatType)2, (FloatType)-fract_bits);;
}

template<typename IntegerType, typename FixedPointType>
/*typename std::enable_if<std::is_signed<IntegerType>::value FIXME does not work
    && std::is_signed<FixedPointType>::value, IntegerType>::type*/
IntegerType codasip_fx_fxtoi_to(FixedPointType a, int32 fract_bits)
{
    return a >> fract_bits;
}

template<typename FixedPointType, typename IntegerType>
/*typename std::enable_if<std::is_signed<FixedPointType>::value FIXME does not work
    && std::is_signed<IntegerType>::value, FixedPointType>::type*/
FixedPointType codasip_fx_itofx_to(IntegerType a, int32 fract_bits)
{
    return a << fract_bits;
}

template<typename T>
//typename std::enable_if<std::is_signed<T>::value, T>::type FIXME does not work
T codasip_fx_mul(T a, T b, int32 fract_bits, uint1 rounding_flag)
{
    enum { BIT_WIDTH = ::codasip::resources::BitWidthTypeSelector<T>::value };
    typedef codasip::Integer<2 * BIT_WIDTH, true> Type;

    Type res = (Type)a * (Type)b;

    if (rounding_flag)
    {
        res = res + ((res & (Type)1 << (fract_bits - 1)) << 1);
    }

    return res >> fract_bits;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Complex Numbers Functions

template<typename VectorType>
VectorType codasip_cplx_add(VectorType a, VectorType b)
{
    return a + b;
}

template<typename VectorType>
VectorType codasip_cplx_sub(VectorType a, VectorType b)
{
    return a - b;
}

template<typename VectorType>
VectorType codasip_cplx_mul(VectorType a, VectorType b)
{
    VectorType res;
    for (size_t i = 0; i < VectorType::ELEM_COUNT / 2; i += 2)
    {
        res[i] = a[i] * b[i] - a[i+1] * b[i+1];
        res[i+1] = a[i] * b[i+1] - a[i+1] * b[i];
    }
    return res;
}

template<typename VectorType>
VectorType codasip_cplx_div(VectorType a, VectorType b)
{
    VectorType res;
    for (size_t i = 0; i < VectorType::ELEM_COUNT / 2; i += 2)
    {
        res[i] = (a[i] * b[i] + a[i+1] * b[i+1]) / (b[i] * b[i] + a[i+1] * b[i+1]);
        res[i+1] = (a[i+1] * b[i] - a[i] * b[i+1]) / (b[i] * b[i] + a[i+1] * b[i+1]);
    }
    return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Miscellaneous Functions

/**
 * \brief Does conversion from uintX to floatX.
 * \param[in] value source integer value
 */
template<typename TargetType, typename SourceType>
inline TargetType codasip_bitcast_to_float(SourceType&& value)
{
    typedef typename ::codasip::resources::TypeSelector<
        ::codasip::resources::BitWidthTypeSelector<TargetType>::value,
        false>::type BitcastType;

    return BitcastHelper<TargetType>(static_cast<BitcastType>(
        std::forward<SourceType>(value)));
}

/**
 * \brief Does conversion from uintX to vY[uif]Z.
 * \param[in] value source unsigned integer value
 */
template<typename TargetType, typename SourceType>
inline TargetType codasip_bitcast_to_vector(SourceType&& value)
{
    return TargetType(static_cast<typename TargetType::bitcast_t>(
        std::forward<SourceType>(value)));
}

/**
 * \brief Does conversion from vY[uif]Z or floatX to uintX.
 * \param[in] value source vector value
 */
template<typename TargetType, typename SourceType>
inline TargetType codasip_bitcast_to_uint(SourceType&& value)
{
    return BitcastHelper<TargetType>(std::forward<SourceType>(value));
}

/**
 *  \brief Does bit reverse
 *  \param[in] value to reverse
 *  \return    bit reversed value
 *
 *  \details the algorithm follows this pattern:
 *           given 8bit number = 0b11101000 - algorithm
 *           takes low nibble and high nibble and swapps them -> 0b10001110
 *           swaps halfs in both nibbles                      -> 0b00101011
 *           swaps halfs in those halfs                       -> 0b00010111
 *
 *           If the data type has bit width different from pow(2), the algorithm
 *           uses the next pow(2) bit width.
 *           Once finished, the final value is shifted into the original data type
 *           given 5bit number = 0b10011
 *           8bit number with leading zeroes    -> 0b00010011
 *           do the bit reverse as usual        -> 0b11001000
 *           shift the result to fit            -> 0b00011001
 *           put result into original data type -> 0b11001
 */
template<typename T,
    std::size_t bitWidth = ::codasip::resources::BitWidthTypeSelector<T>::value,
    typename std::enable_if<(bitWidth <= 8) && !detail::is_codasip_vec<T>::value, T>::type* = nullptr>
inline T codasip_bitreverse(T value)
{
    constexpr auto finalShift = 8 - bitWidth;
    uint8_t result = value;
    result = (result & 0xf0) >> 4 | (result & 0x0f) << 4;
    result = (result & 0xcc) >> 2 | (result & 0x33) << 2;
    result = (result & 0xaa) >> 1 | (result & 0x55) << 1;
    return T(result >> finalShift);
}

template<typename T,
    std::size_t bitWidth = ::codasip::resources::BitWidthTypeSelector<T>::value,
    typename std::enable_if<(bitWidth > 8 && bitWidth <= 16) && !detail::is_codasip_vec<T>::value, T>::type* = nullptr>
inline T codasip_bitreverse(T value)
{
    constexpr auto finalShift = 16 - bitWidth;
    uint16_t result = value;
    result = (result & 0xff00) >> 8 | (result & 0xff) << 8;
    result = (result & 0xf0f0) >> 4 | (result & 0xf0f) << 4;
    result = (result & 0xcccc) >> 2 | (result & 0x3333) << 2;
    result = (result & 0xaaaa) >> 1 | (result & 0x5555) << 1;
    return T(result >> finalShift);
}

template<typename T,
    std::size_t bitWidth = ::codasip::resources::BitWidthTypeSelector<T>::value,
    typename std::enable_if<(bitWidth > 16 && bitWidth <= 32) && !detail::is_codasip_vec<T>::value, T>::type* = nullptr>
inline T codasip_bitreverse(T value)
{
    constexpr auto finalShift = 32 - bitWidth;
    uint32_t result = value;
    result = (result & 0xffff0000) >> 16 | (result & 0xffff) << 16;
    result = (result & 0xff00ff00) >> 8 | (result & 0xff00ff) << 8;
    result = (result & 0xf0f0f0f0) >> 4 | (result & 0xf0f0f0f) << 4;
    result = (result & 0xcccccccc) >> 2 | (result & 0x33333333) << 2;
    result = (result & 0xaaaaaaaa) >> 1 | (result & 0x55555555) << 1;
    return T(result >> finalShift);
}

template<typename T,
    std::size_t bitWidth = ::codasip::resources::BitWidthTypeSelector<T>::value,
    typename std::enable_if<(bitWidth > 32 && bitWidth <= 64) && !detail::is_codasip_vec<T>::value, T>::type* = nullptr>
inline T codasip_bitreverse(T value)
{
    constexpr auto finalShift = 64 - bitWidth;
    uint64_t result = value;
    result = (result & 0xffffffff00000000) >> 32 | (result & 0xffffffff) << 32;
    result = (result & 0xffff0000ffff0000) >> 16 | (result & 0xffff0000ffff) << 16;
    result = (result & 0xff00ff00ff00ff00) >> 8 | (result & 0xff00ff00ff00ff) << 8;
    result = (result & 0xf0f0f0f0f0f0f0f0) >> 4 | (result & 0xf0f0f0f0f0f0f0f) << 4;
    result = (result & 0xcccccccccccccccc) >> 2 | (result & 0x3333333333333333) << 2;
    result = (result & 0xaaaaaaaaaaaaaaaa) >> 1 | (result & 0x5555555555555555) << 1;
    return T(result >> finalShift);
}

template<typename T,
    std::size_t bitWidth = ::codasip::resources::BitWidthTypeSelector<T>::value,
    typename std::enable_if<(bitWidth > 64) && !detail::is_codasip_vec<T>::value, T>::type* = nullptr>
inline T codasip_bitreverse(const T& value)
{
    // find the next usable datatype of pow(2) bit width
    constexpr auto nextPowerOfTwo = NextClosestPowTwo::Get(bitWidth);

    // this data type is used for mask and value swapping
    typedef codasip::Uint<nextPowerOfTwo> ResultT;

    // calculate the value of final shift
    constexpr auto finalShift = nextPowerOfTwo - bitWidth;

    // make pow(2) bit width data type from data type to rotate
    ResultT result(value);

    // this value is used to step the masking & shifting process
    short bits = nextPowerOfTwo;

    // initialize the mask to be 0x111111....n
    ResultT mask = ~ResultT(0);

    // basicly divide bit width by 2, until there is not bits left
    while (bits >>= 1)
    {
        // create mask, this does literally the same as the non loop versions
        // given 8bit mask
        // the entry mask starts as 0b11111111 -> 0b11110000 -> 0b11001100 -> 0b10101010
        mask ^= mask << (bits);

        // do the shift & mask operations as the non loop version
        // use mask = 0b11110000 -> ~mask = 0b00001111
        // bits value is always halved, so if the entry value is 8, the first iteration shifts by 4
        result = (result & ~mask) >> bits | (result & mask) << bits;
    }

    // perform the final shift
    return T(result >> finalShift);
}

// vector type support implementation
template<typename T,
    std::size_t bitWidth = ::codasip::resources::BitWidthTypeSelector<T>::value,
    typename std::enable_if<detail::is_codasip_vec<T>::value, T>::type* = nullptr>
inline T codasip_bitreverse(const T& value)
{
    T ret;
    for (int i = 0; i < T::ELEM_COUNT; ++i)
    {
        ret[i] = codasip_bitreverse(value[i]);
    }
    return ret;
}

}   // namespace simulator
}   // namespace codasip

#endif   // SIMULATOR_SIMBASE_SIMULATOR_HELPERS_H_
