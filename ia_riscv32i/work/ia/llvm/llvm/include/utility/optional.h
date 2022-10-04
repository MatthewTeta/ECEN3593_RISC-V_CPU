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
 *  \author Libor Vasicek
 *  \date   2015-05-13
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef UTILITY_OPTIONAL_H_
#define UTILITY_OPTIONAL_H_

#include "utility/check_condition.h"
#include "utility/codasip_type_traits.h"

#include <cstddef>

namespace codasip {

namespace {

static const std::string UNINITIALIZED_VALUE_ACCESS = "Access to uninitialized optional value.";

}   // anonymous namespace

namespace detail {
template<typename T>
class OptionalPointer
{
public:
    OptionalPointer(T value = NULL);

protected:
    typedef typename detail::remove_pointer<T>::type& TypeRef;

    bool IsSet() const;
    void MarkInitialized(const bool isInitialized);
    TypeRef GetRef() const;

    /// Pointer to specific object or NULL.
    T m_Value;
};

template<typename T>
class OptionalValue
{
public:
    OptionalValue();
    OptionalValue(const T& value);

protected:
    typedef typename detail::remove_const<T>::type TypeNoConst;

    bool IsSet() const;
    void MarkInitialized(const bool isInitialized);
    TypeNoConst& GetRef() const;

    /// Holds value when is initialized.
    TypeNoConst m_Value;
    /// Tells that value is initialized.
    bool m_IsInitialized;
};

}   // namespace detail

/**
 *  \addtogroup CODASIP_UTILITY
 *  \{
 *  \class  codasip::Optional
 *  \brief  Holds pointer to specific type and checks references with NULL pointer.
 *          Other option is to hold value and checks whether is is initialized.
 *  \}
 */
template<typename T, bool isPointer = detail::is_pointer<T>::value>
class Optional
  : private detail::conditional<isPointer, detail::OptionalPointer<T>, detail::OptionalValue<T>>::type
{
public:
    typedef
        typename detail::conditional<isPointer, detail::OptionalPointer<T>, detail::OptionalValue<T>>::type Parent;
    typedef
        typename detail::conditional<isPointer, typename detail::remove_pointer<T>::type, T>::type Type;
    typedef typename detail::conditional<isPointer,
        typename detail::remove_const<Type>::type*,
        typename detail::remove_const<Type>::type>::type TypeNoConst;

    typedef Type& TypeRef;
    typedef Type* TypePtr;

    /**
     *  \brief  Create uninitialized value or set to NULL pointer.
     */
    Optional();
    /**
     *  \brief  Initialize value or pointer to specific object.
     */
    Optional(T value);
    /**
     *  \brief  Implicit conversion from non-const member to const.
     */
    Optional(const Optional<TypeNoConst, isPointer>& other);
    /**
     *  \brief  Reset value and return previous one.
     */
    T ResetValue();
    /**
     *  \{
     *  \brief  Overloaded operator.
     */
    TypeRef operator*() const;
    TypePtr operator->() const;
    Optional<T, isPointer>& operator=(T value);
    operator bool() const;
    /** \} */

private:
    TypeRef GetValue() const;
    T SetValue(T);

    typedef typename detail::conditional<isPointer,
        typename detail::add_const<Type>::type*,
        typename detail::add_const<Type>::type>::type TypeConst;

    friend class Optional<TypeConst, isPointer>;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Public interface                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline detail::OptionalPointer<T>::OptionalPointer(T value)
  : m_Value(value)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void detail::OptionalPointer<T>::MarkInitialized(const bool isInitialized)
{
    if (!isInitialized)
    {
        m_Value = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename detail::OptionalPointer<T>::TypeRef detail::OptionalPointer<T>::GetRef() const
{
    return *m_Value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Public interface                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline detail::OptionalValue<T>::OptionalValue()
  : m_Value()
  , m_IsInitialized(false)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline detail::OptionalValue<T>::OptionalValue(const T& value)
  : m_Value(value)
  , m_IsInitialized(true)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void detail::OptionalValue<T>::MarkInitialized(const bool isInitialized)
{
    m_IsInitialized = isInitialized;
    if (!isInitialized)
    {
        m_Value = T();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename detail::OptionalValue<T>::TypeNoConst& detail::OptionalValue<T>::GetRef() const
{
    return const_cast<TypeNoConst&>(m_Value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline Optional<T, isPointer>::Optional()
  : Parent()
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline Optional<T, isPointer>::Optional(T value)
  : Parent(value)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline Optional<T, isPointer>::Optional(const Optional<TypeNoConst, isPointer>& other)
  : Parent()
{
    if (other.IsSet())
    {
        SetValue(other.m_Value);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline T Optional<T, isPointer>::ResetValue()
{
    T prev = this->m_Value;
    this->MarkInitialized(false);
    return prev;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline typename Optional<T, isPointer>::TypeRef Optional<T, isPointer>::operator*() const
{
    return GetValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline typename Optional<T, isPointer>::TypePtr Optional<T, isPointer>::operator->() const
{
    return &GetValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline Optional<T, isPointer>& Optional<T, isPointer>::operator=(T value)
{
    SetValue(value);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, bool isPointer>
inline Optional<T, isPointer>::operator bool() const
{
    return this->IsSet();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Private interface                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Check if pointer is set.
 */
template<typename T>
inline bool detail::OptionalPointer<T>::IsSet() const
{
    return m_Value != NULL;
}

/**
 *  \brief  Check if pointer is set.
 */
template<typename T>
inline bool detail::OptionalValue<T>::IsSet() const
{
    return m_IsInitialized;
}

/**
 *  \brief  Return value when is set or throw an error.
 */
template<typename T, bool isPointer>
inline typename Optional<T, isPointer>::TypeRef Optional<T, isPointer>::GetValue() const
{
    CHECK_CONDITION(this->IsSet()) << UNINITIALIZED_VALUE_ACCESS;
    return this->GetRef();
}

/**
 *  \brief  Set new value and return previous one.
 */
template<typename T, bool isPointer>
inline T Optional<T, isPointer>::SetValue(T value)
{
    T prev = this->m_Value;
    this->m_Value = value;
    this->MarkInitialized(true);
    return prev;
}

}   // namespace codasip

#endif   // UTILITY_OPTIONAL_H_
