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
 *  \date   Oct 12, 2021
 *  \brief  Declaration/Implementation of the class.
 */
#ifndef MACRO_PROCESSOR_SETTINGS_H_
#define MACRO_PROCESSOR_SETTINGS_H_

#include "utility/memory.h"

#include <cstddef>

namespace codasip {
namespace macro_processor {

CODASIP_FORWARD(Settings)
CODASIP_FORWARD(SettingsBuilder)

class Settings
{
public:
    /// Default prefix symbol
    static constexpr char DEFAULT_PREFIX_SYMBOL = '$';
    /// Default print line info
    static const bool DEFAULT_PRINT_LINE_INFO = false;
    /// Default loop watchdog limit
    static const size_t DEFAULT_LOOP_WATCHDOG_LIMIT = 1000000;
    /// Default macro watchdog limit
    static const size_t DEFAULT_MACRO_WATCHDOG_LIMIT = 1000;

    /// \brief  Creates default settings, which could be tweaked by settings builder.
    static SettingsBuilder Create();

    /**
     *  \{
     *  \brief  Getter.
     */
    char GetPrefixSymbol() const;
    bool PrintLineInfo() const;
    size_t GetLoopWatchDogLimit() const;
    size_t GetMacroWatchDogLimit() const;
    /// \}

    friend class SettingsBuilder;

private:
    /// Prefix symbol for lexical analysis
    char m_PrefixSymbol = DEFAULT_PREFIX_SYMBOL;
    /// Print line information
    bool m_PrintLineInfo = DEFAULT_PRINT_LINE_INFO;
    /// Loop watchdog limit
    size_t m_LoopWatchdogLimit = DEFAULT_LOOP_WATCHDOG_LIMIT;
    /// Macro watchdog limit
    size_t m_MacroWatchdogLimit = DEFAULT_MACRO_WATCHDOG_LIMIT;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline char Settings::GetPrefixSymbol() const
{
    return m_PrefixSymbol;
}

inline bool Settings::PrintLineInfo() const
{
    return m_PrintLineInfo;
}

inline size_t Settings::GetLoopWatchDogLimit() const
{
    return m_LoopWatchdogLimit;
}

inline size_t Settings::GetMacroWatchDogLimit() const
{
    return m_MacroWatchdogLimit;
}

}   // namespace macro_processor
}   // namespace codasip

#endif /* MACRO_PROCESSOR_SETTINGS_H_ */
