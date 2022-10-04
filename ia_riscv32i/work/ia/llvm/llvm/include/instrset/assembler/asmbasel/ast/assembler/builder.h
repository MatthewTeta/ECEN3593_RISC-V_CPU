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
 *  \date   22. 3. 2018
 *  \brief  Declaration/Implementation of the class.
 */

#ifndef INSTRSET_ASSEMBLER_ASMBASEL_AST_ASSEMBLER_BUILDER_H_
#define INSTRSET_ASSEMBLER_ASMBASEL_AST_ASSEMBLER_BUILDER_H_

#include "common/codasip_integer.h"
#include "instrset/assembler/asmbasel/ast/assembler/assemblerfwd.h"

#include <string>

namespace codasip {

// Forward declaration
class Location;

namespace ast {
namespace assembler {

// TODO remove duplicate
typedef bool (*CheckFunction)(Element&);

/**
 *  \brief  This class is used for building assembler AST nodes.
 *          It stores them to be freed after the work over them is done.
 *          With usage of bison %merge functions deletion of nodes is forbidden during parsing.
 *  \warning    This builder could be used only during AST creation.
 */
class Builder
{
public:
    /**
     *  \brief  Create binary.
     *  \param[in]  location
     *  \param[in]  op Operator
     *  \param[in]  lhs Left hand side operand
     *  \param[in]  rhs Right hand side operand
     *  \param[in]  matchInfoSize Match info size
     */
    static Node& CreateBinary(const Location& location,
        const std::string& op,
        Node& lhs,
        Node& rhs,
        const unsigned int matchInfoSize);
    /**
     *  \brief  Create identifier.
     *  \param[in]  location
     *  \param[in]  value Identifier value
     */
    static Node& CreateIdentifier(const Location& location, const std::string& value);
    /**
     *  \brief  Create integer constant.
     *  \param[in]  location
     *  \param[in]  value Integer constant value
     *  \param[in]  parsedStr Parsed string
     */
    static Node&
    CreateIntegerConstant(const Location& location, const MaxInt& value, const std::string& parsedStr);
    /**
     *  \brief  Create string.
     *  \param[in]  location
     *  \param[in]  value String value
     */
    static Node& CreateString(const Location& location, const std::string& value);
    /**
     *  \brief  Create ternary.
     *  \param[in]  location
     *  \param[in]  op Operator
     *  \param[in]  lhs Left hand side operand
     *  \param[in]  middle Middle operand
     *  \param[in]  rhs Right hand side operand
     *  \param[in]  matchInfoSize Match info size
     */
    static Node& CreateTernary(const Location& location,
        const std::string& op,
        Node& lhs,
        Node& middle,
        Node& rhs,
        const unsigned int matchInfoSize);
    /**
     *  \brief  Create unary.
     *  \param[in]  location
     *  \param[in]  op Operator
     *  \param[in]  rhs Right hand side operand
     *  \param[in]  matchInfoSize Match info size
     */
    static Node& CreateUnary(const Location& location,
        const std::string& op,
        Node& rhs,
        const unsigned int matchInfoSize);
    /**
     *  \brief  Create attribute.
     *  \param[in]  location
     *  \param[in]  id attribute identifier
     *  \param[in]  signature attribute signature
     *  \param[in]  ast attribute AST
     *  \param[in]  bitWidth attribute bit-width
     *  \param[in]  isRelative is relative
     */
    static Node& CreateAttribute(const Location& location,
        const std::string& id,
        const std::string& signature,
        Node& ast,
        const unsigned int bitWidth,
        const bool isRelative);
    /**
     *  \brief  Create constant.
     *  \param[in]  location
     *  \param[in]  text constant text
     */
    static Node& CreateConstant(const Location& location, const std::string& text);
    /**
     *  \brief  Create element.
     *  \param[in]  location
     *  \param[in]  id element identifier
     *  \param[in]  signature signature
     *  \param[in]  isRegisterClass element is a register class
     *  \param[in]  isSlot element is a slot
     *  \param[in]  checkFunction function to check validity of conditional section selection
     */
    static Node& CreateElement(const Location& location,
        const std::string& id,
        const std::string& signature,
        const bool isRegisterClass,
        const bool isSlot,
        CheckFunction checkFunction = nullptr);
    /**
     *  \brief  Create set.
     *  \param[in]  location
     *  \param[in]  id set identifier
     *  \param[in]  signature signature
     *  \param[in]  isRegisterClass set is a register class
     */
    static Node& CreateSet(const Location& location,
        const std::string& id,
        const std::string& signature,
        const bool isRegisterClass);
    /**
     *  \brief  Create space.
     *  \param[in]  location
     *  \param[in]  count Whitespace character count
     */
    static Node& CreateSpace(const Location& location, const unsigned int count);
    /**
     *  \brief  Create command for instruction, example 'r1 = addi r2, 10'.
     *  \param[in]  location
     *  \param[in]  root
     *  \param[in]  isVliw Architecture is VLIW
     */
    static Node&
    CreateGenerateInstructionCommand(const Location& location, Node& root, const bool isVliw);
};

}   // namespace assembler
}   // namespace ast
}   // namespace codasip

#endif   // INSTRSET_ASSEMBLER_ASMBASEL_AST_ASSEMBLER_BUILDER_H_
