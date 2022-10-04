/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2021 Codasip s.r.o.
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
 *  \author Martin Ministr
 *  \date   Oct 13, 2021
 *  \brief  Declaration/Implementation of the class.
 */
#ifndef MACRO_PROCESSOR_WATCHDOG_H_
#define MACRO_PROCESSOR_WATCHDOG_H_

#include <cstddef>
#include <string>

namespace codasip {

class Location;

namespace macro_processor {

class MacroProcessor;

/// \brief  Provides watchdog facility for loops and macros.
class Watchdog
{
public:
    Watchdog(const size_t limit, const std::string& construct);

    /**
     *  \brief  Checks that watchdog counter is within the limit. Prints error on check failure.
     *          Increments counter afterwards.
     *  \return false on success, true otherwise.
     */
    bool CheckAndIncrement(MacroProcessor& processor, const Location& location);
    /// \brief  Decrements counter.
    void Decrement();

private:
    /// Watchdog counter
    size_t m_Counter = 0;
    /// Watchdog limit
    size_t m_Limit;
    /// Guarded construct name
    std::string m_Construct;
};

}   // namespace macro_processor
}   // namespace codasip

#endif /* MACRO_PROCESSOR_WATCHDOG_H_ */
