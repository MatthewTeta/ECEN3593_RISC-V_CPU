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
 *  \author Adam Husar, Martin Ministr
 *  \date   1.2.2012
 *  \brief  Contains declaration of codasip::codasip_vec template class.
 */

#ifndef COMMON_CODASIP_VEC_H_
#define COMMON_CODASIP_VEC_H_

#include "common/codasip_integer.h"
#include "utility/check_condition.h"
#include <cstdint>
#include <array>
#include <limits>
#include <algorithm>            // std::copy_n, std::fill_n
#include <type_traits>

namespace codasip {
namespace vector {
namespace detail {

/**
 *  \internal
 *  \brief  Binary casting between incompatible types.
 *          Used instead of reinterpret_cast to interpret source's value as dest value.
 *          Old-style *(dest*) &source breaks strict aliasing, which is required by
 *          compilers in order to optimize correctly, without undefined behaviors.
 *  \tparam DestType target type to cast to
 *  \param  value must be of SouceType type
 */
template<typename DestType, typename SourceType>
inline DestType BitcastHelper(const SourceType& value)
{
    static_assert( sizeof(SourceType) == sizeof(DestType),
        "Incompatible types for bitcast (different byte size)" );
    DestType tmp;
    std::memcpy(&tmp, &value, sizeof(SourceType));
    return tmp;
}

/**
 *  \internal
 *  \class  underlying_type_selector
 *  \brief  Helper class used to select proper integer type for the vector's element.
 */
template<unsigned _BITS, bool _SIGN>
struct underlying_type_selector
{
    typedef typename std::conditional<_SIGN, int8_t, uint8_t>::type int8_type;
    typedef typename std::conditional<_SIGN, int16_t, uint16_t>::type int16_type;
    typedef typename std::conditional<_SIGN, int32_t, uint32_t>::type int32_type;
    typedef typename std::conditional<_SIGN, int64_t, uint64_t>::type int64_type;

    typedef typename std::conditional<_BITS == std::numeric_limits<uint8_t>::digits, int8_type,
        typename std::conditional<_BITS == std::numeric_limits<uint16_t>::digits, int16_type,
            typename std::conditional<_BITS == std::numeric_limits<uint32_t>::digits, int32_type,
                typename std::conditional<_BITS == std::numeric_limits<uint64_t>::digits,
                    int64_type,
                    ::codasip::Integer<_BITS, _SIGN> >::type>::type>::type>::type type;
};

template<unsigned _BITS, bool _SIGN>
using underlying_type_selector_t = typename underlying_type_selector<_BITS, _SIGN>::type;

/**
 *  \internal
 *  \brief  Return index for a single element into vector container for BIG endian.
 *  \param  index element index
 */
template<bool _Endianness, unsigned _N>
typename std::enable_if<_Endianness == false, unsigned>::type
GetVectorIndex( const unsigned index  )
{
    return _N - index -1;
}
/**
 *  \internal
 *  \brief  Return index for a single element into vector container for LITTLE endian.
 *  \param  index element index
 */
template<bool _Endianness, unsigned>
typename std::enable_if<_Endianness == true, unsigned>::type
GetVectorIndex( const unsigned index  )
{
    return index;
}

}  // namespace codasip::vector::detail
}  // namespace codasip::vector

#define CODASIP_VEC_BINARY_OPERATOR(op, ret_type) \
    friend ret_type operator op(const self_t& lhs, const self_t& rhs) \
    { \
        ret_type res; \
        for (unsigned ii = 0; ii < ELEM_COUNT; ++ii) \
        { \
            res[ii] = lhs[ii] op rhs[ii]; \
        } \
        return res; \
    }

#define CODASIP_VEC_UNARY_OPERATOR(op) \
    self_t operator op() const \
    { \
        self_t res; \
        for ( unsigned ii = 0; ii < ELEM_COUNT; ++ii ) \
        { \
            res[ii] = op(this->operator[](ii)); \
        } \
        return res; \
    }

#define CODASIP_VEC_ARRAY_OPERATOR() \
    elem_t& operator[](const size_t index) \
    { \
        return m_Elems.at( ::codasip::vector::detail::GetVectorIndex<ENDIANNESS, ELEM_COUNT>(index) ); \
    } \
    const elem_t& operator[](const size_t index) const \
    { \
        return m_Elems.at( ::codasip::vector::detail::GetVectorIndex<ENDIANNESS, ELEM_COUNT>(index) ); \
    }

#define CODASIP_VEC_ENABLE_IF_INT( T ) \
    typename = typename std::enable_if< \
        std::is_same<typename std::decay< T >::type, codasip::Integer<BIT_WIDTH, SIGNED> >::value || \
        std::is_same<typename std::decay< T >::type, codasip::Integer<BIT_WIDTH, !SIGNED> >::value || \
        std::is_same<typename std::decay< T >::type, full_t>::value || \
        std::is_same<typename std::decay< T >::type, full_diff_sign_t>::value>::type

/**
 *  \class  codasip_vec
 *  \brief  Implements integer vector type (SIMD).
 *          v4i8 is indexed as bits of byte, (uint32)0x11223344 => {0x44, 0x33, 0x22, 0x11}.
 *  \tparam _VecBits total bit-width of the vector type
 *  \tparam _ElemBits bit-width of a single element
 *  \tparam _Signed signed (true) or unsigned (false) integer type
 *  \tparam _Endianness LITTLE (true) or BIG (false) endian
 */
template
<
    unsigned _VecBits,
    unsigned _ElemBits,
    bool _Signed,
    bool _Endianness
>
class codasip_vec
{
public:
    enum : unsigned
    {   /// total bit-width, required to work with BitWidthTypeSelector
        BIT_WIDTH = _VecBits,
        /// bit-width of a single element
        ELEM_BITS = _ElemBits,
        /// number of elements in the vector
        ELEM_COUNT = BIT_WIDTH / ELEM_BITS
    };
    enum : bool
    {   /// LITTLE (true) or BIG (false) endian
        ENDIANNESS = _Endianness,
        /// signed (true) or unsigned (false) integer type
        SIGNED = _Signed
    };
    /// \brief  Underlying integer type representing single element
    typedef vector::detail::underlying_type_selector_t<ELEM_BITS, SIGNED> elem_t;
    /// \brief  Underlying integer type representing the whole vector as scalar
    typedef vector::detail::underlying_type_selector_t<BIT_WIDTH, SIGNED> full_t;
    /// \brief  Underlying integer type representing the whole vector as scalar
    ///         with inverted sign
    typedef vector::detail::underlying_type_selector_t<BIT_WIDTH, !SIGNED> full_diff_sign_t;
    /// \brief  Integer type used by default for bit casts
    typedef Integer<BIT_WIDTH, false> bitcast_t;
    /// \brief  Shortcut for this type
    typedef codasip_vec<BIT_WIDTH, ELEM_BITS, SIGNED, ENDIANNESS> self_t;
    /// \brief  Vector type with different sign
    typedef codasip_vec<BIT_WIDTH, ELEM_BITS, !SIGNED, ENDIANNESS> vec_diff_sign_t;
    /// \brief   Integer vector types used as comparison result
    typedef self_t cmp_res_t;

    /**
     *  \brief  Default constructor initializes to zero.
     */
    codasip_vec()
    {
        m_Elems.fill( static_cast<elem_t>(0) );
    }
    /**
     *  \brief  Constructor from scalar underlying integer (POD) type.
     *  \param  v scalar value to assign.
     */
    template<typename T, CODASIP_VEC_ENABLE_IF_INT(T)>
    codasip_vec( T&& v )
    {
        set_from_bits( std::forward<T>(v) );
    }
    /**
     *  \brief  Enable conversion from vector with different sign
     *  \param  v value for initialization.
     */
    explicit codasip_vec( const vec_diff_sign_t& v )
    {
        CopyVector( *this, v );
    }
    /**
     *  \{
     *  \brief  Default copy and move semantic.
     *  \param  v vector value to assign.
     */
    codasip_vec( const codasip_vec& v ) = default;
    codasip_vec& operator=( const codasip_vec& v ) = default;
    codasip_vec( codasip_vec&& v ) = default;
    codasip_vec& operator=( codasip_vec&& v ) = default;
    /**
     *  \}
     *  \brief  Enable conversion to underlying POD type.
     */
    template<typename T, CODASIP_VEC_ENABLE_IF_INT(T)>
    operator T() const
    {
        return static_cast<T>(get_as_bits());
    }
    /**
     *  \brief  Enable conversion to vector with different sign
     */
    explicit operator vec_diff_sign_t() const
    {
        return vec_diff_sign_t(*this);
    }
    /**
     *  \brief  Bit-cast conversion function - converts vector into unsigned scalar.
     */
    bitcast_t get_as_bits() const
    {   // used for zero extension of the underlying element type
        typedef vector::detail::underlying_type_selector_t<ELEM_BITS, false> uelem_t;
        bitcast_t res;
        for ( unsigned ii = 0; ii < ELEM_COUNT; ++ii )
        {   // unsigned bit extension and shift
            res |= static_cast<bitcast_t>(static_cast<uelem_t>(m_Elems[ii])) << (ii * ELEM_BITS);
        }
        return res;
    }
    /**
     *  \brief  Initialize vector type from scalar of the same bit-width.
     *  \param  v value for initialization.
     */
    void set_from_bits( const bitcast_t& v )
    {
        for ( unsigned ii = 0; ii < ELEM_COUNT; ++ii )
        {
            m_Elems[ii] = v >> (ii * ELEM_BITS);
        }
    }
    /**
     *  \brief  Return number of elements in the vector.
     */
    unsigned size() const
    {
        return ELEM_COUNT;
    }
    /**
     *  \{
     *  \brief  Access element on given index. Has protection for out-of-range
     *          access.
     *  \param  index address to access
     */
    CODASIP_VEC_ARRAY_OPERATOR()
    /**
     *  \} \{
     *  \brief  Definition of binary operator.
     *  \param  lhs first operand
     *  \param  rhs second operand
     */
    CODASIP_VEC_BINARY_OPERATOR( +, self_t )
    CODASIP_VEC_BINARY_OPERATOR( -, self_t )
    CODASIP_VEC_BINARY_OPERATOR( *, self_t )
    CODASIP_VEC_BINARY_OPERATOR( /, self_t )
    CODASIP_VEC_BINARY_OPERATOR( %, self_t )
    CODASIP_VEC_BINARY_OPERATOR( &, self_t )
    CODASIP_VEC_BINARY_OPERATOR( |, self_t )
    CODASIP_VEC_BINARY_OPERATOR( ^, self_t )
    CODASIP_VEC_BINARY_OPERATOR( <<, self_t )
    CODASIP_VEC_BINARY_OPERATOR( >>, self_t )
    CODASIP_VEC_BINARY_OPERATOR( >, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( <, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( >=, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( <=, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( ==, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( !=, cmp_res_t )
    /**
     * \brief Bitwise negation operator.
     */
    CODASIP_VEC_UNARY_OPERATOR( ~ )
    /**
     * \brief Logical negation operator.
     */
    CODASIP_VEC_UNARY_OPERATOR( ! )
private:
    template<class V1, class V2>
    static void CopyVector( V1& dst, const V2& src )
    {
        for ( unsigned ii = 0; ii < ELEM_COUNT; ++ii )
        {
            dst[ii] = src[ii];
        }
    }
    /// actual storage, v4u8 [0, 1, 2, 3] stored as 00112233 as uint32 33221100
    /// needs to be public to cooperate with codasip_vec_flt
    std::array<elem_t, ELEM_COUNT> m_Elems;
};

/**
 *  \class  codasip_vec_flt
 *  \brief  Implements floating point vector type.
 */
template
<
    unsigned _VecBits,
    unsigned _ElemBits,
    typename _ElemType,
    bool _Endianness
>
class codasip_vec_flt
{
public:
   enum : unsigned
   {   /// total bit-width, required to work with BitWidthTypeSelector
       BIT_WIDTH = _VecBits,
       /// bit-width of a single element
       ELEM_BITS = _ElemBits,
       /// number of elements in the vector
       ELEM_COUNT = BIT_WIDTH / ELEM_BITS
   };
   enum : bool
   {   /// LITTLE (true) or BIG (false) endian
       ENDIANNESS = _Endianness
   };
   /// \brief   Underlying floating type representing single element
   typedef _ElemType elem_t;
   /// \brief   Unsigned integer type representing single element
   typedef vector::detail::underlying_type_selector_t<ELEM_BITS, false> elem_int_t;
   /// \brief   Shortcut for this type
   typedef codasip_vec_flt<BIT_WIDTH, ELEM_BITS, elem_t, ENDIANNESS> self_t;
   /// \brief   Integer vector types used as comparison result
   typedef codasip_vec<BIT_WIDTH, ELEM_BITS, false, ENDIANNESS> cmp_res_t;
   /// \brief   Integer type used by default for bit casts
   typedef Integer<BIT_WIDTH, false> bitcast_t;

    /**
     *  \brief  Default constructor.
     */
    codasip_vec_flt()
    {
        m_Elems.fill( static_cast<elem_t>(0.0) );
    }
    /**
     *  \brief  Constructor from scalar integer type.
     *  \param  v assigned value
     */
    explicit codasip_vec_flt( const bitcast_t& v )
    {
        set_from_bits( v );
    }
    /**
     *  \{
     *  \brief  Default copy and move semantic.
     *  \param  v assigned/copied/moved value
     */
    codasip_vec_flt( const codasip_vec_flt& v ) = default;
    codasip_vec_flt& operator=( const codasip_vec_flt& v ) = default;
    codasip_vec_flt( codasip_vec_flt&& v ) = default;
    codasip_vec_flt& operator=( codasip_vec_flt&& v ) = default;
    /**
     *  \}
     *  \brief  Conversion from codasip::Integer.
     *  \param  v assigned value
     */
    void set_from_bits( const bitcast_t& v )
    {
        for ( unsigned ii = 0; ii < ELEM_COUNT; ++ii )
        {
            elem_int_t tmp = (v >> (ii * ELEM_BITS));
            m_Elems[ii] = vector::detail::BitcastHelper<elem_t>(tmp);
        }
    }
    /**
     *  \brief  Bit-cast conversion function - converts vector into unsigned scalar.
     */
    bitcast_t get_as_bits() const
    {   // used for zero extension of the underlying element type
        typedef vector::detail::underlying_type_selector_t<ELEM_BITS, false> uelem_int_t;
        bitcast_t res;
        for ( unsigned ii = 0; ii < ELEM_COUNT; ++ii )
        {
            uelem_int_t tmp = *((uelem_int_t*)(&m_Elems[ii]));
            res |= static_cast<bitcast_t>(static_cast<uelem_int_t>(tmp)) << (ii * ELEM_BITS);
        }
        return res;
    }
    /**
     *  \brief  Return number of elements in the vector.
     */
    unsigned size() const
    {
        return ELEM_COUNT;
    }
    /**
     *  \{
     *  \brief  Access element on given index. Has protection for out-of-range
     *          access.
     *  \param  index address to access
     */
    CODASIP_VEC_ARRAY_OPERATOR()
    /**
     *  \} \{
     *  \brief  Definition of binary operator.
     *  \param  lhs first operand
     *  \param  rhs second operand
     */
    CODASIP_VEC_BINARY_OPERATOR( +, self_t )
    CODASIP_VEC_BINARY_OPERATOR( -, self_t )
    CODASIP_VEC_BINARY_OPERATOR( *, self_t )
    CODASIP_VEC_BINARY_OPERATOR( /, self_t )
    CODASIP_VEC_BINARY_OPERATOR( >, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( <, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( >=, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( <=, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( ==, cmp_res_t )
    CODASIP_VEC_BINARY_OPERATOR( !=, cmp_res_t )
    /** \} */
private:
    /// actual storage
    std::array<elem_t, ELEM_COUNT> m_Elems;
};

} // namespace codasip

#undef CODASIP_VEC_ENABLE_IF_INT
#undef CODASIP_VEC_ARRAY_OPERATOR
#undef CODASIP_VEC_BINARY_OPERATOR
#undef CODASIP_VEC_UNARY_OPERATOR

#endif // COMMON_CODASIP_VEC_H_
