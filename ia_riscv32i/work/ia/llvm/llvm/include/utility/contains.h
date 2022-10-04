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
 *  \author Martin Moracek
 *  \date   2020-06-15
 *  \brief  codasip::Contains utility
 */

#ifndef UTILITY_CONTAINS_H_
#define UTILITY_CONTAINS_H_

#include <algorithm>
#include <array>
#include <initializer_list>
#include <map>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace codasip {

/**
 * \brief Checks whether an item specified by the given predicate exists in the container.
 * \tparam Container Container type
 * \tparam Predicate Predicate type
 * \param container searched container
 * \param predicate predicate identifying the sought item
 */
template<typename Container, typename Predicate>
inline auto Contains(const Container& container, Predicate&& predicate)
    -> decltype(predicate(std::declval<typename Container::value_type>()), true)
{
    return std::find_if(container.begin(), container.end(), std::forward<Predicate>(predicate)) !=
        container.end();
}

/**
 * \brief Checks whether an item specified by the given predicate exists in the container.
 * \tparam Container Container type
 * \tparam Predicate Predicate type
 * \param container searched container
 * \param predicate predicate identifying the sought item
 */
template<typename Container, typename Predicate>
inline auto Contains(const Container& container, Predicate&& predicate) ->
    typename std::enable_if<std::is_array<Container>::value, decltype(predicate(*container), true)>::type
{
    return std::find_if(std::begin(container),
               std::end(container),
               std::forward<Predicate>(predicate)) != std::end(container);
}

/**
 * \brief Checks whether an item specified by the given key exists in the container.
 * \tparam Container Associative container type
 * \param container searched container
 * \param key key indentifying the sought item
 */
template<typename Container>
inline bool Contains(const Container& container, const typename Container::key_type& key)
{
    return container.find(key) != container.end();
}

/**
 * \brief Checks whether the given item exists in the container.
 * \tparam Key Key type of the map type
 * \tparam Value Value type of the map type
 * \param container searched container
 * \param keyValue sought key-value pair
 */
template<typename Key, typename Value>
inline bool Contains(const std::map<Key, Value>& container,
    const typename std::map<Key, Value>::value_type& keyValue)
{
    const auto pos = container.find(keyValue.first);
    return pos != container.end() && pos->second == keyValue.second;
}

/**
 * \brief Checks whether the given item exists in the container.
 * \tparam Key Key type of the map type
 * \tparam Value Value type of the map type
 * \param container searched container
 * \param keyValue sought key-value pair
 */
template<typename Key, typename Value>
inline bool Contains(const std::unordered_map<Key, Value>& container,
    const typename std::unordered_map<Key, Value>::value_type& keyValue)
{
    const auto pos = container.find(keyValue.first);
    return pos != container.end() && pos->second == keyValue.second;
}

/**
 * \brief Checks whether the given item exists in the container.
 * \tparam Key Key type of the map type
 * \tparam Value Value type of the map type
 * \param container searched container
 * \param keyValue sought key-value pair
 */
template<typename Container>
inline auto Contains(const Container& container, const typename Container::value_type& keyValue)
    -> decltype(std::declval<typename Container::mapped_type>(), true)
{
    // generic fallback for associative containers
    const auto range = container.equal_range(keyValue.first);
    for (auto itr = range.first; itr != range.second; ++itr)
    {
        if (itr->second == keyValue.second)
        {
            return true;
        }
    }

    return false;
}

/**
 * \brief Checks whether the given item exists in the container.
 * \tparam Container Sequence container type
 * \tparam Value Argument value type
 * \param container searched container
 * \param value sought value
 */
template<typename Container, typename Value>
inline auto Contains(const Container& container, const Value& value) ->
    // container.front() ensures it is SequenceContainer
    // is_convertible filters out predicates that have their own overload
    typename std::enable_if<std::is_convertible<Value, typename Container::value_type>::value,
        decltype(container.front(), true)>::type
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

/**
 * \brief Checks whether the given item exists in the container.
 * \tparam Element Initializer list element type
 * \tparam Value Argument value type
 * \param container searched container
 * \param value sought value
 */
template<typename Element, typename Value>
inline auto Contains(const std::initializer_list<Element>& container, const Value& value)
    -> decltype(std::declval<Element>() == value, true)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

/**
 * \brief Checks whether the given item exists in the container.
 * \tparam Container Array container type
 * \tparam Value Argument value type
 * \param container searched container
 * \param value sought value
 */
template<typename Container, typename Value>
inline auto Contains(const Container& container, const Value& value) ->
    typename std::enable_if<std::is_array<Container>::value, decltype(*container == value, true)>::type
{
    return std::find(std::begin(container), std::end(container), value) != std::end(container);
}

}   // namespace codasip

#endif
