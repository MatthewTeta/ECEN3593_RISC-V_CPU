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
 *  \date   19. 10. 2021
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef SIMULATOR_RESOURCES_CSR_DUMPER_H_
#define SIMULATOR_RESOURCES_CSR_DUMPER_H_

#include "simulator/resources/csr_dumper_address.h"
#include "simulator/resources/csr_dumper_address_ahb.h"
#include "simulator/resources/csr_dumper_single.h"

#include <vector>

namespace codasip {
namespace resources {
namespace detail {

template<bool CONDITION>
struct Condition
{};

template<>
struct Condition<true>
{
    static const int ALLOWED = 0;
};

// clang-format off
struct DumperSelectorHelper
{
    template<class T>
    static auto SelectDumperType(T* t) -> decltype(
        T::SIZE,
        Condition<T::SIZE == 1>::ALLOWED,
        DumperSingle<T>("", 0));

    template<class T>
    static auto SelectDumperType(T* t) -> decltype(
        T::SIZE,
        Condition<(T::SIZE > 1) && (std::is_same<typename T::PacType, CpbPac>::value)>::ALLOWED,
        DumperAddress<T>("", 0));

    template<class T>
    static auto SelectDumperType(T* t) -> decltype(
        T::SIZE,
        Condition<(T::SIZE > 1) && (std::is_same<typename T::PacType, AxiLitePac>::value)>::ALLOWED,
        DumperAddress<T>("", 0));

    template<class T>
    static auto SelectDumperType(T* t) -> decltype(
        T::SIZE,
        Condition<(T::SIZE > 1) && (std::is_same<typename T::PacType, AxiPac>::value)>::ALLOWED,
        DumperAddress<T>("", 0));

    template<class T>
    static auto SelectDumperType(T* t) -> decltype(
        T::SIZE,
        Condition<(T::SIZE > 1) && (std::is_same<typename T::PacType, AhbPac>::value)>::ALLOWED,
        DumperAddressAhb<T>("", 0));

    // Some resources are dumpable but do not have PacType defined
    template<class T>
    static auto SelectDumperType(T* t) -> decltype(
        T::SIZE,
        Condition<(T::SIZE > 1)>::ALLOWED,
        t->stall(),
        t->clear(),
        t->gated(),
        DumperAddress<T>("", 0));
};
// clang-format on
}   // namespace detail
/**
 * \brief compile time selector for dumper type
 */
template<typename T>
using Dumper = decltype(detail::DumperSelectorHelper::SelectDumperType<T>(nullptr));

}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_DUMPER_H_
