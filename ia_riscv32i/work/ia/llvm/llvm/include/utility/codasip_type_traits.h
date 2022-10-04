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
 *  \author Potesil Josef
 *  \date   25.1.2012
 *  \brief  Contains simple versions of type traits class templates available
 *          in C++11.
 */

#ifndef UTILITY_CODASIP_TYPE_TRAITS_H_
#define UTILITY_CODASIP_TYPE_TRAITS_H_

#include <iterator>
#include <limits>
#include <type_traits>

namespace codasip {
namespace detail {

/**
 *  \addtogroup CODASIP_UTILITY
 *  \{
 *  \defgroup CODASIP_UTILITY_TYPETRAITS  Type traits
 *  Temporal replacement for some type traits class templates available in C++11/C++14.
 *  \}
 */
/**
 *  \addtogroup CODASIP_UTILITY_TYPETRAITS
 *  \{
 */
using std::add_const;
using std::add_lvalue_reference;
using std::conditional;
using std::is_const;
using std::is_floating_point;
using std::is_pointer;
using std::is_same;
using std::remove_const;
using std::remove_cv;
using std::remove_pointer;
using std::remove_reference;
using std::remove_volatile;

/**
 *  \brief  Based on the condition C template parameter adds or removes const
 *          qualifier from the data type T.
 */
template<bool C, typename T>
struct use_const
{
    typedef
        typename conditional<C, typename add_const<T>::type, typename remove_const<T>::type>::type type;
};
/**
 *  \brief  Adds const qualifier to the source type if condition C is true
 *          otherwise leaves the type untouched.
 */
template<bool C, typename T>
struct add_const_cnd
{
    typedef typename conditional<C, typename add_const<T>::type, T>::type type;
};
/**
 *  \brief  C++14 like helper class adding optionally const qualifier.
 */
template<bool C, typename T>
using add_const_cnd_t = typename add_const_cnd<C, T>::type;
/**
 *  \brief  Indicates if iterator type is const_iterator or simple iterator.
 */
template<typename Iterator>
struct is_const_iterator
{
    enum
    {
        value = is_const<typename remove_reference<typename std::iterator_traits<Iterator>::reference>::type>::value
    };
};
/**
 *  \brief  Helper class implementing the unified access to variables (pointers
 *          and variables)
 *  \see GetRef()
 */
template<typename T, bool isPointer = is_pointer<typename remove_reference<T>::type>::value>
struct get_ref_helper
{
    typedef typename add_lvalue_reference<T>::type argument_type;
    typedef argument_type result_type;

    result_type operator()(argument_type x) const
    {
        return x;
    };
};
/**
 *  \brief  Specialization of \ref get_ref_helper for pointer type.
 */
template<typename T>
struct get_ref_helper<T, true>
{
    typedef typename remove_reference<T>::type argument_type;
    typedef
        typename add_lvalue_reference<typename remove_pointer<argument_type>::type>::type result_type;

    result_type operator()(argument_type x) const
    {
        return *x;
    }
};
/**
 *  \brief  Helper class implementing the detection whether variables (pointer
 *          or value is valid or not.
 *  \see    IsValid()
 */
template<typename T, bool isPointer = is_pointer<T>::value>
struct is_valid_helper
{
    typedef typename add_lvalue_reference<T>::type argument_type;
    typedef bool result_type;

    result_type operator()(argument_type) const
    {
        return true;
    }
};
/**
 *  \brief  Specialization of \ref is_valid_helper for pointer type.
 */
template<typename T>
struct is_valid_helper<T, true>
{
    typedef typename add_lvalue_reference<T>::type argument_type;
    typedef bool result_type;

    result_type operator()(argument_type x) const
    {
        return x;
    }
};
/**
 *  \brief  This function was designed to provide unified access using the .
 *          operator to access members of pointers and values. This function
 *          should be used to provide reference to an object in situations, when
 *          the caller does not known, whether accessed variable is a pointer or
 *          value. If given variable is not a pointer, returns reference to
 *          given type, otherwise the pointer will be dereferenced and reference
 *          to underlying object will be returned.
 *  \param  x source variable
 */
template<typename T>
inline typename codasip::detail::get_ref_helper<T>::result_type GetRef(T& x)
{
    return codasip::detail::get_ref_helper<T>()(x);
}
/**
 *  \brief  This function was designed to provide detection whether given
 *          variable is valid or not. For pointers it is checked whether it is
 *          not NULL, values are always valid.
 *  \param  x source variable
 */
template<typename T>
inline bool IsValid(T& x)
{
    return codasip::detail::is_valid_helper<T>()(x);
}

/**
 *  \brief  Helper macro for optional call to member function, that is called only when
 *          such method exists.
 *  \param  func Name of function to detect
 *  \param  ret Return type of function
 *  \param  def Default return type that will be returned if method is not present.
 *  \note   Usage:
 *          OPTIONAL_CALL_DEF(Method, int, -1);
 *          int ret = OptionalCallMethod(obj, arg1, arg2);
 */
#ifdef _MSVC

#    define OPTIONAL_CALL_DEF(func, ret, def)                 \
        template<typename T, typename... Args>                \
        inline ret OptionalCall##func(T& obj, Args&&... args) \
        {                                                     \
            __if_exists(T::func)                              \
            {                                                 \
                return obj.func(std::forward<Args>(args)...); \
            }                                                 \
            return def;                                       \
        }

#else

#    define OPTIONAL_CALL_DEF(func, ret, def)                                             \
        template<class T, typename... Args>                                               \
        inline auto OptionalCall##func(T& obj, Args&&... args)->decltype(&T::func, ret()) \
        {                                                                                 \
            return obj.func(std::forward<Args>(args)...);                                 \
        }                                                                                 \
        template<typename... Args>                                                        \
        inline ret OptionalCall##func(Args&&...)                                          \
        {                                                                                 \
            return def;                                                                   \
        }

#endif

/**
 *  \brief  Helper macto for optional call to void member function
 */
#define OPTIONAL_CALL_DEF_VOID(func) OPTIONAL_CALL_DEF(func, void, void())

/**
 *  \{
 *  \class  IntegerInfoHepler
 *  \brief  Helps to extract data type (bit-width, sign) information from given
 *          integer type.
 *
 */
template<typename T, bool IsEnum = std::is_enum<T>::value>
struct IntegerInfoHepler
{
    enum
    {
        sign = std::numeric_limits<T>::is_signed,
        bits = std::numeric_limits<T>::digits + sign,
    };
};
template<typename T>
struct IntegerInfoHepler<T, true> : public IntegerInfoHepler<typename std::underlying_type<T>::type>
{};

template<typename T>
struct IntegerInfo : public IntegerInfoHepler<typename std::decay<T>::type>
{};

/** \} */

/** \} */   // end DOXYGEN group comment

}   // namespace detail
}   // namespace codasip

#endif   // UTILITY_CODASIP_TYPE_TRAITS_H_
