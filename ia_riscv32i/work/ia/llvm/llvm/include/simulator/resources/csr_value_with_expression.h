/**
 * Codasip Ltd
 *
 * CONFIDENTIAL
 *
 * Copyright 2019 Codasip Ltd
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained in this file, is and shall remain the property of Codasip Ltd
 * and its suppliers, if any.
 *
 * The intellectual and technical concepts contained herein are confidential and proprietary to
 * Codasip Ltd and are protected by trade secret and copyright law.  In addition, elements of the
 * technical concepts may be patent pending.
 *
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 *  \file
 *  \author Karel Vorechovsky
 *  \date   2.9.2020
 *  \brief  Definition of the class codasip::resources::Parameter.
 */

#ifndef SIMULATOR_RESOURCES_CSR_RUNTIME_PARAMETER_H_
#define SIMULATOR_RESOURCES_CSR_RUNTIME_PARAMETER_H_

#include "simulator/simbase/simulator_log.h"

#include <sstream>
#include <type_traits>

namespace codasip {

namespace resources {

namespace detail {

/**
 *  \brief  Return error message in case there is clamping cast
 *  \param  valueExpression pretty expression
 */
template<typename TypeWanted>
std::string MakeValueDoesNotFitTypeError(const std::string& valueExpression)
{
    std::ostringstream out;
    codasip::simulator::PrintHeader(codasip::simulator::LOG_TYPE_FATAL, 0, out);
    out << "expression: " << valueExpression << std::endl
        << "resulted into value out of bounds" << std::endl
        << "maximum allowed value: " << std::numeric_limits<TypeWanted>::max() << std::endl
        << "minimum allowed value: " << std::numeric_limits<TypeWanted>::min() << std::endl;
    return out.str();
}
/**
 *  \brief  Return if the type is sufficient for the value size
 *  \param  value checked value
 */
template<typename TypeWanted, typename TypeDeduced>
bool DoesValueFitType(const TypeDeduced& value)
{
    return ((value > TypeDeduced(0)) == (TypeWanted(value) > TypeWanted(0))) &&
        TypeDeduced(TypeWanted(value)) == value;
}

}   // namespace detail

/**
 *  \addtogroup SIMULATOR
 *  \{
 *  \class  codasip::simulator::ValueWithExpression
 *  \brief  Wrapper that holds T and immediate expression used to get T from codal
 *  \internal
 *  \note   This class only serves the mere purpose of more friendly human readable
 *          message, when command line parameter value is invalid, so the user
 *          will see expression that led to such value
 *  \}
 */
template<typename Type>
class ValueWithExpression
{
public:
    typedef Type ValueType;
    /**
     *  \brief ctor
     *  \param value value
     *  \param valueExpression expression, that the value is result of
     */
    ValueWithExpression(const Type& value, const std::string& valueExpression);
    /**
     *  \brief Getter
     *  \return value
     */
    const ValueType& GetValue() const;
    /**
     *  \brief Getter
     *  \return Expression associated with that value
     */
    const std::string& GetValueExpression() const;

private:
    /// The actual value
    ValueType m_value;
    /// The expression that generated the value
    std::string m_valueExpression;
};
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
ValueWithExpression<Type>::ValueWithExpression(const Type& value, const std::string& valueExpression)
  : m_value(value)
  , m_valueExpression(valueExpression)
{}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
const Type& ValueWithExpression<Type>::GetValue() const
{
    return m_value;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
const std::string& ValueWithExpression<Type>::GetValueExpression() const
{
    return m_valueExpression;
}

/**
 *  \brief Helper for automatic template type deduction
 *  \param value value
 *  \param valueExpression expression, that the value is result of
 */
template<typename TypeWanted, typename TypeDeduced>
ValueWithExpression<TypeWanted>
MakeValueWithExpression(const TypeDeduced& value, const std::string& valueExpression)
{
    if (!detail::DoesValueFitType<TypeWanted>(value))
    {
        throw std::runtime_error{detail::MakeValueDoesNotFitTypeError<TypeWanted>(valueExpression)};
    }
    return ValueWithExpression<TypeWanted>{static_cast<TypeWanted>(value), valueExpression};
}

/**
 *  \brief  false type, matches everything except ValueWithExpression<T>
 */
template<typename T>
struct is_value_with_expression : std::false_type
{};
/**
 *  \brief true type, matches only ValueWithExpression<T>
 */
template<typename T>
struct is_value_with_expression<ValueWithExpression<T>> : std::true_type
{};
/**
 *  \brief Helper for resources to get the value of template parameter in case T is ValueWithExpression
 *  \return value
 */
template<typename T>
auto GetValue(const T& any) ->
    typename std::enable_if<is_value_with_expression<T>::value, const typename T::ValueType&>::type
{
    return any.GetValue();
}
/**
 *  \brief Helper for resources to get the value of template parameter in case T is not anything else than ValueWithExpression
 *  \return value
 */
template<typename T>
auto GetValue(const T& any) ->
    typename std::enable_if<!is_value_with_expression<T>::value, const T&>::type
{
    return any;
}
/**
 *  \brief Helper for resources to get the expression for the value
 *  \return expression string
 */
template<typename T>
auto GetValueExpression(const T& any) ->
    typename std::enable_if<is_value_with_expression<T>::value, const char* const>::type
{
    return any.GetValueExpression().c_str();
}
/**
 *  \brief Helper in case of any other type
 *  \return nullptr
 */
template<typename T>
auto GetValueExpression(const T& any) ->
    typename std::enable_if<!is_value_with_expression<T>::value, const char* const>::type
{
    (void)any;
    return nullptr;
}

}   // namespace resources

}   // namespace codasip

#endif
