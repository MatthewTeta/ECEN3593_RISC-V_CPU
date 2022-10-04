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
 *  \author Martin Ministr
 *  \date   3. 3. 2017
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INSTRSET_DISASSEMBLER_DSMUTILSL_DSM_TEXT_H_
#define INSTRSET_DISASSEMBLER_DSMUTILSL_DSM_TEXT_H_

#include <string>
#include <vector>

namespace codasip {
namespace disassembler {

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * \brief Represents one part of generated assembler syntax.
 */
class DsmTextPart
{
public:
    DsmTextPart(const std::string& text, const bool isConcatenation)
      : m_Text(text)
      , m_Concatenation(isConcatenation)
    {}

    const std::string& GetText() const;
    bool IsConcatenation() const;

private:
    /// stored generated assembler syntax
    std::string m_Text;
    /// is concatenation, not a valid text
    bool m_Concatenation;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const std::string& DsmTextPart::GetText() const
{
    return m_Text;
}

inline bool DsmTextPart::IsConcatenation() const
{
    return m_Concatenation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * \brief Wrapper around generated assembler syntax. Need to know what parts are generated and
 *        concatenations between them.
 */
class DsmText
{
public:
    typedef std::vector<DsmTextPart> Parts;

    const Parts& GetParts() const;

    /**
     * \brief Appends another DsmText.
     * \param[in] text
     */
    void operator+=(const DsmText& text);
    /**
     * \brief Appends another assembler syntax.
     * \param[in] text
     */
    void operator+=(const std::string& text);
    /**
     * \brief Appends concatenation at the end of generated assembler syntax.
     */
    void AppendConcatenation();

    /**
     * \brief Clears the stored assembler syntax.
     */
    void Clear();

    const std::string ToString() const;

private:
    Parts m_Parts;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline const DsmText::Parts& DsmText::GetParts() const
{
    return m_Parts;
}

inline void DsmText::operator+=(const DsmText& text)
{
    for (const DsmTextPart& part : text.GetParts())
    {
        if (part.IsConcatenation())
        {
            AppendConcatenation();
        }
        else
        {
            if (part.GetText() == "," && (!m_Parts.empty() && !m_Parts.back().IsConcatenation()))
            {
                AppendConcatenation();
            }
            *this += part.GetText();
        }
    }
}

inline void DsmText::operator+=(const std::string& text)
{
    m_Parts.push_back(DsmTextPart(text, false));
}

inline void DsmText::AppendConcatenation()
{
    m_Parts.push_back(DsmTextPart("", true));
}

inline void DsmText::Clear()
{
    m_Parts.clear();
}

inline const std::string DsmText::ToString() const
{
    // firstly process concatenations
    // examples: "a" => "a", "a"~"b"~"c" => "abc", "a"~""~"c" => "ac", ""~""~"" => ""
    std::vector<std::string> processed;
    processed.push_back("");   // will be removed in second phase
    for (size_t i = 0; i < m_Parts.size(); i++)
    {
        DsmTextPart first = m_Parts[i];
        if (first.IsConcatenation())
        {
            i++;
            if (i < m_Parts.size())   // concatenation should not be last, condition happens always
            {
                processed.back() += m_Parts[i].GetText();
            }
        }
        else
        {
            processed.push_back(first.GetText());
        }
    }

    // do not print empty strings, before each non-first print add space
    std::string text = "";
    bool firstPrinted = false;
    for (const std::string& s : processed)
    {
        if (s.empty())
        {
            continue;
        }

        if (firstPrinted)
        {
            text += " ";
        }
        text += s;
        firstPrinted = true;
    }

    return text;
}

}   // namespace disassembler
}   // namespace codasip

#endif   // INSTRSET_DISASSEMBLER_DSMUTILSL_DSM_TEXT_H_
