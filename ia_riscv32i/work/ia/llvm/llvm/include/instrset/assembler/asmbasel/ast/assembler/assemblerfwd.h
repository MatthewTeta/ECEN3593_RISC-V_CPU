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

#ifndef INSTRSET_ASSEMBLER_ASMBASE_ASSEMBLERFWD_H_
#define INSTRSET_ASSEMBLER_ASMBASE_ASSEMBLERFWD_H_

namespace codasip {
namespace ast {
namespace assembler {

class Node;

// Expression
class Binary;
class Identifier;
class IntegerConstant;
class String;
class Ternary;
class Unary;

// ISA
class Attribute;
class Constant;
class Element;
class Set;

// commands
class ParserCommand;
class GenerateInstructionCommand;

}   // namespace assembler
}   // namespace ast
}   // namespace codasip

#endif   // INSTRSET_ASSEMBLER_ASMBASE_ASSEMBLERFWD_H_
