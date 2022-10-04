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
 *  \author Pavel Najman
 *  \date   Jul 1, 2021
 *  \brief  Declaration of utility classes.
 */

#ifndef SIMULATOR_RESOURCES_CSR_INDEX_QUEUE_H_
#define SIMULATOR_RESOURCES_CSR_INDEX_QUEUE_H_

#include <cstdint>
#include <queue>

namespace codasip {
namespace resources {
namespace detail {

/**
 *  \brief  Holds and manages a queue of indices.
 */
class IndexQueue
{
public:
    /**
     *  \brief  Advances state.
     */
    void ClockCycle();
    /**
     *  \brief  Schedules queue pop on clock cycle.
     */
    void PopOnClockCycle();
    /**
     *  \brief  Accesses queue front.
     */
    uint8_t Front() const;
    /**
     *  \brief  Adds a value to the queue.
     *  \param  value A value to be added.
     */
    void Push(const uint8_t value);
    /**
     *  \brief  Resets the state.
     */
    void Reset();
    /**
     *  \brief  Returns whether the queue is empty.
     */
    bool IsEmpty() const;
    /**
     *  \brief  Returns the size of the queue.
     */
    size_t Size() const;
    /**
     *  \brief  Decides whether the queue will be empty on clock cycle.
     */
    bool IsEmptyOnClockCycle() const;

private:
    /// Queue of indices.
    std::queue<uint8_t> m_Indices;
    /// Flags whether an index should be poped from the queue on the clock cycle.
    bool m_PopOnClockCycle = false;
};

}   // namespace detail
}   // namespace resources
}   // namespace codasip

#endif   // SIMULATOR_RESOURCES_CSR_INDEX_QUEUE_H_
