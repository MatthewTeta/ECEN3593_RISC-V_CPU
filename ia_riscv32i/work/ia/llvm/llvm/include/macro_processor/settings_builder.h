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
#ifndef MACRO_PROCESSOR_SETTINGS_BUILDER_H_
#define MACRO_PROCESSOR_SETTINGS_BUILDER_H_

#include "macro_processor/settings.h"

#include <memory>

namespace codasip {
namespace macro_processor {

// TODO replace with getoptl one day
class SettingsBuilder
{
public:
    /// \brief  Creates default settings, which could be tweaked by fluent setters.
    SettingsBuilder();

    /// \brief  Casts SettingsBuilder into Settings by retrieving the result.
    SettingsUPtr Build() const;

    SettingsBuilder& WithPrefixSymbol(const char symbol);
    SettingsBuilder& WithLineInfo(const bool value = true);
    SettingsBuilder& WithLoopWatchdogLimit(const size_t value);
    SettingsBuilder& WithMacroWatchdogLimit(const size_t value);

private:
    mutable SettingsUPtr m_Settings;
};

}   // namespace macro_processor
}   // namespace codasip

#endif /* MACRO_PROCESSOR_SETTINGS_BUILDER_H_ */
