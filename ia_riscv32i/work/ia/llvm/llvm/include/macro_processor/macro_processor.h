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
 *  \date   Sep 29, 2021
 *  \brief  Declaration/Implementation of the class.
 */
#ifndef MACRO_PROCESSOR_MACRO_PROCESSOR_H_
#define MACRO_PROCESSOR_MACRO_PROCESSOR_H_

#include "common/codasip_integer.h"
#include "macro_processor/ast/expression/expression_node.h"
#include "macro_processor/ast/statement/macro_definition.h"
#include "macro_processor/settings_builder.h"
#include "macro_processor/symbols/symbol_context.h"
#include "macro_processor/watchdog.h"

#include <iosfwd>
#include <map>

namespace codasip {
namespace filesystem {

class Path;

}   // namespace filesystem

namespace macro_processor {

/**
 *  \brief  Preprocess macros from input stream into output stream.
 */
class MacroProcessor : public SymbolContext
{
public:
    /**
     *  \brief  Preprocess macros from input stream into output stream.
     *  \param[out] out Output stream
     *  \param[in]  in Input file path
     *  \param[in]  settings Settings of macro processor
     */
    static int PreprocessFile(std::ostream& out,
        const filesystem::Path& in,
        SettingsUPtr settings = Settings::Create().Build());
    /**
     *  \brief  Method to simplify the unittesting.
     *  \param[out] out Output stream
     *  \param[in]  in Input string
     *  \param[in]  settings Settings of macro processor
     */
    static int Preprocess(std::ostream& out,
        const std::string& in,
        SettingsUPtr settings = Settings::Create().Build());

    // TODO temporary public because of error logging in unittests
    MacroProcessor(std::ostream& out, SettingsUPtr settings);

    /**
     *  \{
     *  \brief  Getter.
     */
    bool HasError() const;
    Watchdog& GetMacroWatchdog();
    char GetPrefixSymbol() const;
    bool PrintLineInfo() const;
    size_t GetLoopWatchdogLimit() const;
    size_t GetMacroWatchdogLimit() const;
    /**
     *  \}
     *  \{
     *  \brief  Setter.
     */
    void SetError();
    /** \} */

    /// \brief  Define macro in macro table.
    void DefineMacro(ast::MacroDefinitionUPtr macro);
    /// \brief  Get macro from macro table.
    const ast::MacroDefinition* GetMacro(const std::string& id) const;
    /// \brief  Prints text on output stream.
    void Print(const std::string& text);

private:
    static int
    Preprocess(std::ostream& out, std::istream& in, const std::string& fileName, SettingsUPtr settings);

    /// Output stream
    std::ostream& m_Out;
    /// Error happened, TODO remove this with proper logger and simplify the affected code around it
    bool m_Error = false;
    /// Macro table
    std::map<std::string, ast::MacroDefinitionUPtr> m_MacroTable;
    /// Macro call watchdog
    Watchdog m_MacroWatchdog;
    /// Settings
    SettingsUPtr m_Settings;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool MacroProcessor::HasError() const
{
    return m_Error;
}

inline Watchdog& MacroProcessor::GetMacroWatchdog()
{
    return m_MacroWatchdog;
}

inline char MacroProcessor::GetPrefixSymbol() const
{
    return m_Settings->GetPrefixSymbol();
}

inline bool MacroProcessor::PrintLineInfo() const
{
    return m_Settings->PrintLineInfo();
}

inline size_t MacroProcessor::GetLoopWatchdogLimit() const
{
    return m_Settings->GetLoopWatchDogLimit();
}

inline size_t MacroProcessor::GetMacroWatchdogLimit() const
{
    return m_Settings->GetMacroWatchDogLimit();
}

inline void MacroProcessor::SetError()
{
    m_Error = true;
}

}   // namespace macro_processor
}   // namespace codasip

#endif /* MACRO_PROCESSOR_MACRO_PROCESSOR_H_ */
