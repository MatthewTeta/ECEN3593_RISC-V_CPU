/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2020 Codasip s.r.o.
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
 *  \date   5. 5. 2020
 *  \brief
 */

#ifndef SIMULATOR_PROFILERL_PROFILER_RT_PROFILER_RT_EXPRESSIONS_H_
#define SIMULATOR_PROFILERL_PROFILER_RT_PROFILER_RT_EXPRESSIONS_H_

#include "common/toolstypes.h"
#include "simulator/profilerl/profiler_rt/profiler_rt.h"

#include <tuple>

namespace codasip {
namespace profiler {
namespace runtime {

/**
 *  \{
 *  \brief  Iterates over a tuple of terms and packs their cached value into a bitset.
 *  \tparam Index iterator index
 *  \tparam Tuple tuple to iterate over
 */
template<std::size_t Index, typename Tuple>
struct TermPacker
{
    uint64_t operator()(const Tuple& data) const
    {
        // term indices grow from the most siginificant bit (true, false, false) -> 100
        auto value = static_cast<uint64_t>(
            std::get<std::tuple_size<Tuple>::value - Index>(data).GetValue());
        return (value << (Index - 1)) | TermPacker<Index - 1, Tuple>{}(data);
    }
};

template<typename Tuple>
struct TermPacker<1, Tuple>
{
    uint64_t operator()(const Tuple& data) const
    {
        return static_cast<uint64_t>(std::get<std::tuple_size<Tuple>::value - 1>(data).GetValue());
    }
};
/** \} */

/**
 *  \brief  A wrapper around an expression term in CodAL coverage
 *  \tparam Type term type - bool or uint1
 *  \tparam Evaluator evaluator type
 */
template<typename Type, typename Evaluator>
class Term
{
public:
    /**
     *  \brief Constructor
     *  \param evaluator callable evaluator object
     */
    Term(Evaluator evaluator)
      : m_Evaluator(std::move(evaluator))
    {}

    /**
     *  \brief Evaluates the term and returns the result.
     */
    Type operator()() const
    {
        m_Value = m_Evaluator();
        return m_Value;
    }

    /**
     *  \brief Returns the last evaluated value.
     */
    Type GetValue() const
    {
        return m_Value;
    }

private:
    /// Callable evaluator object
    Evaluator m_Evaluator;

    /// Last evaluated value (cached)
    mutable Type m_Value = {};
};

/**
 *  \brief  A wrapper areouund an expression in CodAL coverage
 *  \tparam Type expression type - bool or uint1
 *  \tparam Evaluator evaluator type
 *  \tparam Terms term types
 */
template<typename Type, typename Evaluator, typename... Terms>
class Expression
{
public:
    /**
     *  \brief  Constructor
     *  \param  id expression ID reported to the profiler
     *  \param  evaluator callable evaluator object
     *  \param  terms references to term objects
     */
    Expression(const codasip_address_t id, Evaluator evaluator, const Terms&... terms)
      : m_Id(id)
      , m_Evaluator(std::move(evaluator))
      , m_Terms(terms...)
    {}

    /**
     *  \brief  Evaluates the expression, returns the result and reports a hit to the profiler.
     *  \tparam Profiler profiler
     *  \param  profiler profiler
     */
    template<typename Profiler>
    Type operator()(Profiler& profiler) const
    {
        auto res = m_Evaluator();
        profiler.CodalExpressionHit(m_Id, GetPackedTerms());
        return res;
    }

    /**
     *  \brief Packs term evaluations into an integer bitset
     */
    uint64_t GetPackedTerms() const
    {
        return TermPacker<std::tuple_size<TermTuple>::value, TermTuple>{}(m_Terms);
    }

private:
    /// Tuple of terms references
    typedef std::tuple<const Terms&...> TermTuple;

    /// Expression ID reported to the profiler
    codasip_address_t m_Id = 0u;

    /// Callable evaluator object
    Evaluator m_Evaluator;

    /// References to term objects
    TermTuple m_Terms;
};

/**
 *  \brief  Creates an \ref Expression object
 *  \tparam Type expression type
 *  \tparam Evaluator evaluator type
 *  \tparam Terms term types
 *  \param  id expression id
 *  \param  evaluator evaluator object
 *  \param  terms references to terms
 */
template<typename Type, typename Evaluator, typename... Terms>
Expression<Type, Evaluator, Terms...>
ProfilerExpression(const codasip_address_t id, Evaluator&& evaluator, const Terms&... terms)
{
    return {id, std::forward<Evaluator>(evaluator), terms...};
}

/**
 *  \brief  Creates a \ref Term object
 *  \tparam Type term type
 *  \tparam Evaluator evaluator type
 *  \param  evaluator evaluator object
 */
template<typename Type, typename Evaluator>
Term<Type, Evaluator> ProfilerTerm(Evaluator&& evaluator)
{
    return {std::forward<Evaluator>(evaluator)};
}

}   // namespace runtime
}   // namespace profiler
}   // namespace codasip

#endif   // SIMULATOR_PROFILERL_PROFILER_RT_PROFILER_EXPRESSION_H_
