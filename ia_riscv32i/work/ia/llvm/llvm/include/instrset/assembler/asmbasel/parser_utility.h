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
 *  \date   4. 4. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INSTRSET_ASSEMBLER_ASMBASEL_PARSER_UTILITY_H_
#define INSTRSET_ASSEMBLER_ASMBASEL_PARSER_UTILITY_H_

#include "os/compiler.h"

#include <stack>
#include <string>
#include <vector>
CODASIP_LLVM_INCLUDE_BEGIN
#include "llvm/MC/MCAsmMacro.h"
CODASIP_LLVM_INCLUDE_END
#include "common/codasip_integer.h"
#include "utility/location.h"

namespace llvm {

// Forward declaration
class MCAsmParser;
class MCExpr;
class SMLoc;

}   // namespace llvm

namespace codasip {
namespace ast {
namespace assembler {

// Forward declaration
class Element;
class Node;
class ParserCommand;

}   // namespace assembler
}   // namespace ast

namespace assembler {

////////////////////////////////////////////////////////////////////////////////////////////////////
class ParsedExpressionToken
{
public:
    /// \brief  Type of expression token
    enum Type
    {
        ATTRIBUTE,
        INTEGER_CONSTANT,
        TOKEN
    };

    ParsedExpressionToken(const llvm::SMLoc& startLocation,
        const llvm::SMLoc& endLocation,
        const Type type,
        const std::string& s,
        const MaxInt& value = 0);

    const llvm::SMLoc& GetStartLocation() const;
    const llvm::SMLoc& GetEndLocation() const;
    Type GetType() const;
    const std::string& GetString() const;
    const MaxInt& GetValue() const;

private:
    /// Start location
    llvm::SMLoc m_StartLocation;
    /// End location
    llvm::SMLoc m_EndLocation;
    /// Type
    Type m_Type;
    /// String for token
    std::string m_String;
    /// Value of integer constant
    MaxInt m_Value;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline ParsedExpressionToken::ParsedExpressionToken(const llvm::SMLoc& startLocation,
    const llvm::SMLoc& endLocation,
    const Type type,
    const std::string& s,
    const MaxInt& value)
  : m_StartLocation(startLocation)
  , m_EndLocation(endLocation)
  , m_Type(type)
  , m_String(s)
  , m_Value(value)
{}

inline const llvm::SMLoc& ParsedExpressionToken::GetStartLocation() const
{
    return m_StartLocation;
}

inline const llvm::SMLoc& ParsedExpressionToken::GetEndLocation() const
{
    return m_EndLocation;
}

inline ParsedExpressionToken::Type ParsedExpressionToken::GetType() const
{
    return m_Type;
}

inline const std::string& ParsedExpressionToken::GetString() const
{
    return m_String;
}

inline const MaxInt& ParsedExpressionToken::GetValue() const
{
    return m_Value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
class ParsedToken
{
public:
    /// \brief  Type of parsed token
    enum Type
    {
        TOKEN,
        REGISTER,
        IMMEDIATE
    };

    /// \brief  Container of tokens representing expression
    typedef std::vector<ParsedExpressionToken*> ParsedExpressionTokens;

    ParsedToken(const llvm::SMLoc& startLocation,
        const llvm::SMLoc& endLocation,
        const Type type,
        const std::string& s);

    ~ParsedToken();

    const llvm::SMLoc& GetStartLocation() const;
    const llvm::SMLoc& GetEndLocation() const;
    Type GetType() const;
    const std::string& GetString() const;
    ParsedExpressionTokens& GetParsedTokens();
    const ParsedExpressionTokens& GetParsedTokens() const;

private:
    /// Start location
    llvm::SMLoc m_StartLocation;
    /// End location
    llvm::SMLoc m_EndLocation;
    /// Type
    Type m_Type;
    /// String for token or register, attribute identifier for immediate
    std::string m_String;
    /// Parsed expression of immediate
    ParsedExpressionTokens m_ParsedTokens;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline ParsedToken::ParsedToken(const llvm::SMLoc& startLocation,
    const llvm::SMLoc& endLocation,
    const Type type,
    const std::string& s)
  : m_StartLocation(startLocation)
  , m_EndLocation(endLocation)
  , m_Type(type)
  , m_String(s)
{}

inline const llvm::SMLoc& ParsedToken::GetStartLocation() const
{
    return m_StartLocation;
}

inline const llvm::SMLoc& ParsedToken::GetEndLocation() const
{
    return m_EndLocation;
}

inline ParsedToken::Type ParsedToken::GetType() const
{
    return m_Type;
}

inline const std::string& ParsedToken::GetString() const
{
    return m_String;
}

inline ParsedToken::ParsedExpressionTokens& ParsedToken::GetParsedTokens()
{
    return m_ParsedTokens;
}

inline const ParsedToken::ParsedExpressionTokens& ParsedToken::GetParsedTokens() const
{
    return m_ParsedTokens;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  \brief  Provides functions to be used directly by syntactic analyzer.
 *          TODO rename to InstructionParser
 */
class ParserUtility
{
public:
    /// Parsed tokens for further usage
    typedef std::vector<ParsedToken*> ParsedTokens;
    /// Parsed instructions for further usage
    typedef std::vector<ParsedTokens*> ParsedInstructions;
    // LLVM tokens
    typedef std::vector<llvm::AsmToken*> LLVMTokens;

    /**
     *  \brief  Initialize class with MCAsmParser for later usage.
     *  \param[in]  parser MCAsmParser
     */
    static void Init(llvm::MCAsmParser& parser);
    /**
     *  \{
     *  \brief  Getter.
     */
    static const llvm::SMLoc& GetBase();
    /// \}
    /**
     *  \{
     *  \brief  Setter.
     */
    static void SetBase(llvm::SMLoc& base);
    /// \}

    /**
     *  \brief  Converts numeric constant from parsed string to token.
     *  \param[in]  location
     *  \param[in]  constant converted constant '0xffff'
     *  \param[in]  prefixSize size of the prefix of constant such a '0b', '0', '' or '0x'
     *  \param[in]  base base of constant
     *  \param[in]  baseStr base description
     */
    static ast::assembler::Node& ConvertConstantToToken(const Location& location,
        const std::string& constant,
        const unsigned int prefixSize,
        const unsigned int base,
        const std::string& baseStr);
    /**
     *  \brief  Merge two possible AST of node.
     *          Handles ambiguity between opcodes and attributes.
     *  \param[in]  x1 first AST
     *  \param[in]  x2 second AST
     */
    static ast::assembler::Node* MergeNode(ast::assembler::Node* x1, ast::assembler::Node* x2);
    /**
     *  \brief  Merge two possible AST of conditional section.
     *          Handles ambiguity of conditional sections.
     *  \param[in]  x1 first AST
     *  \param[in]  x2 second AST
     */
    static ast::assembler::Node*
    MergeConditionalSections(ast::assembler::Node* x1, ast::assembler::Node* x2);
    /**
     *  \brief  Merge two possible AST of code.
     *          Handles ambiguity between instruction and symbol definition.
     *  \param[in]  x1 first AST
     *  \param[in]  x2 second AST
     */
    static ast::assembler::Node* MergeCode(ast::assembler::Node* x1, ast::assembler::Node* x2);
    /**
     *  \brief  Converts given AST to instructions of tokens for LLVM matcher.
     *  \param[out] instructions Parsed tokens split into parsed instructions
     *  \param[in]  ast AST created by Codasip parser
     *  \param[in]  base Base location for parsed instruction
     */
    static void Ast2Instructions(ParsedInstructions& instructions,
        const ast::assembler::Node& ast,
        const llvm::SMLoc& base);
    /**
     *  \brief  Converts given AST to tokens for LLVM matcher.
     *  \param[out] tokens Parsed tokens
     *  \param[in]  ast AST created by Codasip parser
     *  \param[in]  base Base location for parsed instruction
     */
    static void
    Ast2Tokens(ParsedTokens& tokens, const ast::assembler::Node& ast, const llvm::SMLoc& base);
    /**
     *  \brief  Deletes all available AST nodes and memory records after parsing.
     */
    static void CleanAfterParse();
    /**
      *  \brief  Get value of given attribute.
      *  \warning    Function is used just a few times in generated files on specific models.
      *  \param[in]  element Element
      *  \param[in]  id Identifier
      */
    static int64_t GetAttributeValue(const ast::assembler::Element& element, const std::string& id);
    /**
     *  \brief  Convert Codasip tokens into LLVM tokens.
     *  \param[out] dst LLVM tokens
     *  \param[in]  src Codasip tokens
     */
    static void
    ConvertCodasipToLlvmTokens(LLVMTokens& dst, const ParsedToken::ParsedExpressionTokens& src);
    /**
     *  \brief  Create MCExpr from LLVM tokens.
     *  \param[in]  src LLVM tokens
     */
    static const llvm::MCExpr* CreateExpression(LLVMTokens& src);

private:
    static llvm::MCAsmParser& GetParser();

    static std::string AsmCStringToString(const std::string& str);
    static MaxInt GetConstant(const Location& location,
        const std::string& constant,
        const unsigned int prefixSize,
        const unsigned int base,
        const std::string& baseStr);
    static ast::assembler::Node* MergeNodes(ast::assembler::Node& first, ast::assembler::Node& second);
    static bool Parse(codasip::ast::assembler::Node*& ast, llvm::SMLoc nameLoc);
    static llvm::AsmToken::TokenKind GetTokenKind(const std::string& s);

    /// Pointer on MCAsmParser, it will be used by many methods
    static llvm::MCAsmParser* m_Parser;
    /// LLVM location base, need to be copied here due elements of conditional sections
    static llvm::SMLoc m_Base;
};

}   // namespace assembler
}   // namespace codasip

#endif   // INSTRSET_ASSEMBLER_ASMBASEL_PARSER_UTILITY_H_
