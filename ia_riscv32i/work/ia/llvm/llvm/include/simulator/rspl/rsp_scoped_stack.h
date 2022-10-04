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
 *  \date   2020-05-06
 *  \brief
 */

#ifndef SIMULATOR_RSPL_SCOPED_STACK_H_
#define SIMULATOR_RSPL_SCOPED_STACK_H_

#include "simulator/rspl/rsp_target.h"

namespace codasip {
namespace debugger {

/**
 * \brief RAII-based helper for managing the CodAL call stack
 */
class ScopedCodalStack
{
public:
    /**
     * \brief Pushes a new address on the stack
     */
    ScopedCodalStack(RspTarget::CodalCallStack& stack, codasip_address_t address)
      : m_Stack(stack)
    {
        stack.push_back(address);
    }

    /**
     * \brief Pops the last address from the stack
     */
    ~ScopedCodalStack() noexcept
    {
        m_Stack.pop_back();
    }

private:
    /// Call stack reference
    RspTarget::CodalCallStack& m_Stack;
};

}   // namespace debugger
}   // namespace codasip

#endif   // SIMULATOR_RSPL_SCOPED_STACK_H_
