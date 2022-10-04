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
 *  \date   March 17, 2020
 *  \brief  Placeholder for std::make_unique from C++14
 */

#ifndef CODASIP_UTILITY_MEMORY_H_
#define CODASIP_UTILITY_MEMORY_H_

#include <memory>

namespace codasip {

namespace mem {

// see: https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}   // namespace mem

}   // namespace codasip

#endif   // CODASIP_UTILITY_MEMORY_H_
