/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 1






/* First part of user prologue.  */
#line 121 "merged_parser_gen.yy"

#ifndef ASSEMBLER_BASE_SCANNER_H_
#define ASSEMBLER_BASE_SCANNER_H_

#define YYDEBUG 1
#define YYMAXDEPTH 2000000

#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <string>

#include "utility/codasip_log.h"
#include "utility/codasiputils.h"

#include "instrset/assembler/asmbasel/ast/assembler/builder.h"
#include "instrset/assembler/asmbasel/parser_utility.h"

using namespace codasip;
using namespace codasip::assembler;

extern filesystem::Path inputFileName;

#endif  // ASSEMBLER_BASE_SCANNER_H_

#line 84 "merged_parser_gen.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "merged_parser_gen.hpp"

/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_UNICODE_LETTER = 3,             /* "unicode letter"  */
  YYSYMBOL_UNICODE_MARK = 4,               /* "unicode mark"  */
  YYSYMBOL_UNICODE_NUMBER = 5,             /* "unicode number"  */
  YYSYMBOL_STRING = 6,                     /* "string"  */
  YYSYMBOL_A = 7,                          /* "a"  */
  YYSYMBOL_B = 8,                          /* "b"  */
  YYSYMBOL_C = 9,                          /* "c"  */
  YYSYMBOL_D = 10,                         /* "d"  */
  YYSYMBOL_E = 11,                         /* "e"  */
  YYSYMBOL_F = 12,                         /* "f"  */
  YYSYMBOL_G = 13,                         /* "g"  */
  YYSYMBOL_H = 14,                         /* "h"  */
  YYSYMBOL_I = 15,                         /* "i"  */
  YYSYMBOL_J = 16,                         /* "j"  */
  YYSYMBOL_K = 17,                         /* "k"  */
  YYSYMBOL_L = 18,                         /* "l"  */
  YYSYMBOL_M = 19,                         /* "m"  */
  YYSYMBOL_N = 20,                         /* "n"  */
  YYSYMBOL_O = 21,                         /* "o"  */
  YYSYMBOL_P = 22,                         /* "p"  */
  YYSYMBOL_Q = 23,                         /* "q"  */
  YYSYMBOL_R = 24,                         /* "r"  */
  YYSYMBOL_S = 25,                         /* "s"  */
  YYSYMBOL_T = 26,                         /* "t"  */
  YYSYMBOL_U = 27,                         /* "u"  */
  YYSYMBOL_V = 28,                         /* "v"  */
  YYSYMBOL_W = 29,                         /* "w"  */
  YYSYMBOL_X = 30,                         /* "x"  */
  YYSYMBOL_Y = 31,                         /* "y"  */
  YYSYMBOL_Z = 32,                         /* "z"  */
  YYSYMBOL_33_ = 33,                       /* '?'  */
  YYSYMBOL_34_ = 34,                       /* ':'  */
  YYSYMBOL_35_ = 35,                       /* '|'  */
  YYSYMBOL_36_ = 36,                       /* '&'  */
  YYSYMBOL_37_ = 37,                       /* '^'  */
  YYSYMBOL_38_ = 38,                       /* '='  */
  YYSYMBOL_39_ = 39,                       /* '!'  */
  YYSYMBOL_40_ = 40,                       /* '<'  */
  YYSYMBOL_41_ = 41,                       /* '>'  */
  YYSYMBOL_42_ = 42,                       /* '+'  */
  YYSYMBOL_43_ = 43,                       /* '-'  */
  YYSYMBOL_44_ = 44,                       /* '*'  */
  YYSYMBOL_45_ = 45,                       /* '/'  */
  YYSYMBOL_46_ = 46,                       /* '%'  */
  YYSYMBOL_47_ = 47,                       /* '~'  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* ')'  */
  YYSYMBOL_50___ = 50,                     /* '_'  */
  YYSYMBOL_51_ = 51,                       /* '.'  */
  YYSYMBOL_52_ = 52,                       /* '$'  */
  YYSYMBOL_53_0_ = 53,                     /* '0'  */
  YYSYMBOL_54_ = 54,                       /* '\''  */
  YYSYMBOL_55_ = 55,                       /* '\\'  */
  YYSYMBOL_56_t_ = 56,                     /* '\t'  */
  YYSYMBOL_57_n_ = 57,                     /* '\n'  */
  YYSYMBOL_58_r_ = 58,                     /* '\r'  */
  YYSYMBOL_59_ = 59,                       /* ' '  */
  YYSYMBOL_60_ = 60,                       /* '"'  */
  YYSYMBOL_61_ = 61,                       /* '#'  */
  YYSYMBOL_62_ = 62,                       /* ','  */
  YYSYMBOL_63_ = 63,                       /* ';'  */
  YYSYMBOL_64_ = 64,                       /* '@'  */
  YYSYMBOL_65_ = 65,                       /* '['  */
  YYSYMBOL_66_ = 66,                       /* ']'  */
  YYSYMBOL_67_ = 67,                       /* '`'  */
  YYSYMBOL_68_ = 68,                       /* '{'  */
  YYSYMBOL_69_ = 69,                       /* '}'  */
  YYSYMBOL_70_1_ = 70,                     /* '1'  */
  YYSYMBOL_71_2_ = 71,                     /* '2'  */
  YYSYMBOL_72_3_ = 72,                     /* '3'  */
  YYSYMBOL_73_4_ = 73,                     /* '4'  */
  YYSYMBOL_74_5_ = 74,                     /* '5'  */
  YYSYMBOL_75_6_ = 75,                     /* '6'  */
  YYSYMBOL_76_7_ = 76,                     /* '7'  */
  YYSYMBOL_77_8_ = 77,                     /* '8'  */
  YYSYMBOL_78_9_ = 78,                     /* '9'  */
  YYSYMBOL_YYACCEPT = 79,                  /* $accept  */
  YYSYMBOL_Start = 80,                     /* Start  */
  YYSYMBOL_Program = 81,                   /* Program  */
  YYSYMBOL_SymbolIdentifier = 82,          /* SymbolIdentifier  */
  YYSYMBOL_Attribute = 83,                 /* Attribute  */
  YYSYMBOL_Expression1 = 84,               /* Expression1  */
  YYSYMBOL_Expression2 = 85,               /* Expression2  */
  YYSYMBOL_Expression3 = 86,               /* Expression3  */
  YYSYMBOL_Expression4 = 87,               /* Expression4  */
  YYSYMBOL_Expression5 = 88,               /* Expression5  */
  YYSYMBOL_Expression6 = 89,               /* Expression6  */
  YYSYMBOL_Expression7 = 90,               /* Expression7  */
  YYSYMBOL_Expression8 = 91,               /* Expression8  */
  YYSYMBOL_Expression9 = 92,               /* Expression9  */
  YYSYMBOL_Expression10 = 93,              /* Expression10  */
  YYSYMBOL_Expression11 = 94,              /* Expression11  */
  YYSYMBOL_Expression12 = 95,              /* Expression12  */
  YYSYMBOL_Expression13 = 96,              /* Expression13  */
  YYSYMBOL_Identifier = 97,                /* Identifier  */
  YYSYMBOL_IdentifierTop = 98,             /* IdentifierTop  */
  YYSYMBOL_IdentifierStart = 99,           /* IdentifierStart  */
  YYSYMBOL_IdentifierPart = 100,           /* IdentifierPart  */
  YYSYMBOL_String = 101,                   /* String  */
  YYSYMBOL_IntegerConstant = 102,          /* IntegerConstant  */
  YYSYMBOL_BinaryConstant = 103,           /* BinaryConstant  */
  YYSYMBOL_OctalConstant = 104,            /* OctalConstant  */
  YYSYMBOL_DecimalConstant = 105,          /* DecimalConstant  */
  YYSYMBOL_HexadecimalConstant = 106,      /* HexadecimalConstant  */
  YYSYMBOL_CharLiteral = 107,              /* CharLiteral  */
  YYSYMBOL_MaybeCharEscape = 108,          /* MaybeCharEscape  */
  YYSYMBOL_MaybeCharEnd = 109,             /* MaybeCharEnd  */
  YYSYMBOL_BinaryConstantCore = 110,       /* BinaryConstantCore  */
  YYSYMBOL_OctalConstantCore = 111,        /* OctalConstantCore  */
  YYSYMBOL_DecimalConstantCore = 112,      /* DecimalConstantCore  */
  YYSYMBOL_HexadecimalConstantCore = 113,  /* HexadecimalConstantCore  */
  YYSYMBOL_CharLiteralCore = 114,          /* CharLiteralCore  */
  YYSYMBOL_AlphaNumber = 115,              /* AlphaNumber  */
  YYSYMBOL_BinaryDigit = 116,              /* BinaryDigit  */
  YYSYMBOL_OctalDigit = 117,               /* OctalDigit  */
  YYSYMBOL_DecimalDigit = 118,             /* DecimalDigit  */
  YYSYMBOL_HexadecimalDigit = 119,         /* HexadecimalDigit  */
  YYSYMBOL_Alpha = 120,                    /* Alpha  */
  YYSYMBOL_Newline = 121,                  /* Newline  */
  YYSYMBOL_MWS = 122,                      /* MWS  */
  YYSYMBOL_WS = 123,                       /* WS  */
  YYSYMBOL_WSChar = 124,                   /* WSChar  */
  YYSYMBOL_Code = 125,                     /* Code  */
  YYSYMBOL_Instructions = 126,             /* Instructions  */
  YYSYMBOL_MI5start = 127,                 /* MI5start  */
  YYSYMBOL_MI13default_start_broken = 128, /* MI13default_start_broken  */
  YYSYMBOL_MI13default_start_identifier_identifier = 129, /* MI13default_start_identifier_identifier  */
  YYSYMBOL_MI19roots_default_start_identifier_identifier = 130, /* MI19roots_default_start_identifier_identifier  */
  YYSYMBOL_MI3isaIH1_13default_start_identifier_identifier = 131, /* MI3isaIH1_13default_start_identifier_identifier  */
  YYSYMBOL_MI11i_rtype_aluIH1_13default_start = 132, /* MI11i_rtype_aluIH1_13default_start  */
  YYSYMBOL_MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc = 133, /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc  */
  YYSYMBOL_MI7xpr_allIH1_13default_start9_7xpr_all2rd = 134, /* MI7xpr_allIH1_13default_start9_7xpr_all2rd  */
  YYSYMBOL_MI11xpr_generalIH1_13default_start9_7xpr_all2rd = 135, /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd  */
  YYSYMBOL_MI7xpr_allIH1_13default_start9_7xpr_all3rs1 = 136, /* MI7xpr_allIH1_13default_start9_7xpr_all3rs1  */
  YYSYMBOL_MI11xpr_generalIH1_13default_start9_7xpr_all3rs1 = 137, /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1  */
  YYSYMBOL_MI7xpr_allIH1_13default_start9_7xpr_all3rs2 = 138, /* MI7xpr_allIH1_13default_start9_7xpr_all3rs2  */
  YYSYMBOL_MI11xpr_generalIH1_13default_start9_7xpr_all3rs2 = 139, /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2  */
  YYSYMBOL_MI13i_rtype_shiftIH1_13default_start = 140, /* MI13i_rtype_shiftIH1_13default_start  */
  YYSYMBOL_MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc = 141, /* MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc  */
  YYSYMBOL_MI11i_itype_aluIH1_13default_start = 142, /* MI11i_itype_aluIH1_13default_start  */
  YYSYMBOL_MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc = 143, /* MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc  */
  YYSYMBOL_MI11i_utype_opsIH1_13default_start = 144, /* MI11i_utype_opsIH1_13default_start  */
  YYSYMBOL_MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc = 145, /* MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc  */
  YYSYMBOL_MI13i_jtype_jlinkIH1_13default_start = 146, /* MI13i_jtype_jlinkIH1_13default_start  */
  YYSYMBOL_MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc = 147, /* MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc  */
  YYSYMBOL_MI16i_btype_branchesIH1_13default_start = 148, /* MI16i_btype_branchesIH1_13default_start  */
  YYSYMBOL_MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc = 149, /* MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc  */
  YYSYMBOL_MI10i_li_aliasIH1_13default_start = 150, /* MI10i_li_aliasIH1_13default_start  */
  YYSYMBOL_MI10i_mv_aliasIH1_13default_start = 151, /* MI10i_mv_aliasIH1_13default_start  */
  YYSYMBOL_MI11i_not_aliasIH1_13default_start = 152, /* MI11i_not_aliasIH1_13default_start  */
  YYSYMBOL_MI11i_neg_aliasIH1_13default_start = 153, /* MI11i_neg_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_seqz_aliasIH1_13default_start = 154, /* MI12i_seqz_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_snez_aliasIH1_13default_start = 155, /* MI12i_snez_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_sltz_aliasIH1_13default_start = 156, /* MI12i_sltz_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_sgtz_aliasIH1_13default_start = 157, /* MI12i_sgtz_aliasIH1_13default_start  */
  YYSYMBOL_MI11i_sgt_aliasIH1_13default_start = 158, /* MI11i_sgt_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_beqz_aliasIH1_13default_start = 159, /* MI12i_beqz_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_bnez_aliasIH1_13default_start = 160, /* MI12i_bnez_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_blez_aliasIH1_13default_start = 161, /* MI12i_blez_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_bltz_aliasIH1_13default_start = 162, /* MI12i_bltz_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_bgez_aliasIH1_13default_start = 163, /* MI12i_bgez_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_bgtz_aliasIH1_13default_start = 164, /* MI12i_bgtz_aliasIH1_13default_start  */
  YYSYMBOL_MI11i_bgt_aliasIH1_13default_start = 165, /* MI11i_bgt_aliasIH1_13default_start  */
  YYSYMBOL_MI11i_ble_aliasIH1_13default_start = 166, /* MI11i_ble_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_bgtu_aliasIH1_13default_start = 167, /* MI12i_bgtu_aliasIH1_13default_start  */
  YYSYMBOL_MI12i_bleu_aliasIH1_13default_start = 168, /* MI12i_bleu_aliasIH1_13default_start  */
  YYSYMBOL_MI10i_jr_aliasIH1_13default_start = 169, /* MI10i_jr_aliasIH1_13default_start  */
  YYSYMBOL_MI13default_start_identifier_non_identifier = 170, /* MI13default_start_identifier_non_identifier  */
  YYSYMBOL_MI19roots_default_start_identifier_non_identifier = 171, /* MI19roots_default_start_identifier_non_identifier  */
  YYSYMBOL_MI3isaIH1_13default_start_identifier_non_identifier = 172, /* MI3isaIH1_13default_start_identifier_non_identifier  */
  YYSYMBOL_MI13i_itype_loadsIH1_13default_start = 173, /* MI13i_itype_loadsIH1_13default_start  */
  YYSYMBOL_MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc = 174, /* MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc  */
  YYSYMBOL_MI13i_stype_storeIH1_13default_start = 175, /* MI13i_stype_storeIH1_13default_start  */
  YYSYMBOL_MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc = 176, /* MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc  */
  YYSYMBOL_MI13i_itype_jlregIH1_13default_start = 177, /* MI13i_itype_jlregIH1_13default_start  */
  YYSYMBOL_MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc = 178, /* MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc  */
  YYSYMBOL_MI16i_call_reg_aliasIH1_13default_start = 179 /* MI16i_call_reg_aliasIH1_13default_start  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


/* Unqualified %code blocks.  */
#line 221 "merged_parser_gen.yy"

/**
 * \brief Return location in the current parsed source
 */
static Location GetLocation(YYLTYPE location);
ast::assembler::Node* MergeNode(YYSTYPE x1, YYSTYPE x2);
ast::assembler::Node* MergeConditionalSections(YYSTYPE x1, YYSTYPE x2);
ast::assembler::Node* MergeCode(YYSTYPE x1, YYSTYPE x2);
#line 305 "merged_parser_gen.yy"


#line 322 "merged_parser_gen.cpp"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif
#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#ifdef __cplusplus
  typedef bool yybool;
# define yytrue true
# define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
  typedef signed char yybool;
# define yytrue 1
# define yyfalse 0
#endif

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
# define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YY_ASSERT (0);                               \
 } while (yyfalse)
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
# if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)))
#  define _Noreturn [[noreturn]]
# elif ((!defined __cplusplus || defined __clang__) \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) \
            || (!defined __STRICT_ANSI__ \
                && (__4 < __GNUC__ + (7 <= __GNUC_MINOR__) \
                    || (defined __apple_build_version__ \
                        ? 6000000 <= __apple_build_version__ \
                        : 3 < __clang_major__ + (5 <= __clang_minor__))))))
   /* _Noreturn works as-is.  */
# elif (2 < __GNUC__ + (8 <= __GNUC_MINOR__) || defined __clang__ \
        || 0x5110 <= __SUNPRO_C)
#  define _Noreturn __attribute__ ((__noreturn__))
# elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  100
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1323

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  504
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  901
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 18
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,    56,
      57,     2,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    59,    39,    60,    61,    52,    46,    36,    54,
      48,    49,    44,    42,    62,    43,    51,    45,    53,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    34,    63,
      40,    38,    41,    33,    64,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    65,    55,    66,    37,    50,    67,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,    35,    69,    47,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   313,   313,   324,   328,   329,   333,   338,   342,   346,
     350,   354,   358,   362,   366,   370,   374,   378,   382,   386,
     390,   394,   398,   402,   406,   410,   414,   418,   422,   426,
     430,   434,   438,   442,   446,   450,   454,   458,   462,   466,
     470,   474,   479,   480,   481,   644,   652,   660,   665,   673,
     678,   682,   686,   690,   691,   695,   700,   705,   710,   715,
     720,   725,   731,   739,   749,   750,   751,   752,   753,   757,
     768,   778,   786,   797,   815,   818,   826,   829,   836,   841,
     849,   854,   862,   867,   875,   880,   888,   889,   890,   891,
     892,   893,   894,   895,   896,   897,   898,   899,   900,   901,
     902,   903,   904,   905,   906,   907,   908,   909,   910,   911,
     912,   913,   914,   915,   916,   917,   918,   919,   920,   921,
     922,   923,   924,   928,   929,   933,   934,   938,   939,   940,
     941,   942,   943,   944,   945,   949,   950,   951,   952,   953,
     954,   955,   956,   957,   958,   962,   963,   964,   965,   966,
     967,   968,   969,   970,   971,   972,   973,   974,   975,   976,
     977,   981,   982,   983,   984,   985,   986,   987,   988,   989,
     990,   991,   992,   993,   994,   995,   996,   997,   998,   999,
    1000,  1001,  1002,  1003,  1004,  1005,  1006,  1023,  1028,  1031,
    1035,  1039,  1046,  1047,  1048,  1054,  1058,  1065,  1072,  1080,
    1085,  1093,  1101,  1109,  1114,  1119,  1124,  1129,  1134,  1139,
    1146,  1151,  1156,  1161,  1166,  1171,  1176,  1181,  1186,  1191,
    1196,  1201,  1206,  1211,  1216,  1221,  1226,  1231,  1236,  1241,
    1252,  1257,  1264,  1275,  1287,  1305,  1312,  1319,  1326,  1333,
    1340,  1347,  1354,  1361,  1368,  1378,  1383,  1390,  1400,  1407,
    1414,  1421,  1428,  1435,  1442,  1449,  1456,  1463,  1470,  1477,
    1484,  1491,  1498,  1505,  1512,  1519,  1526,  1533,  1540,  1547,
    1554,  1561,  1568,  1575,  1582,  1589,  1596,  1603,  1610,  1617,
    1624,  1631,  1638,  1645,  1652,  1659,  1666,  1673,  1680,  1687,
    1694,  1701,  1708,  1715,  1722,  1729,  1736,  1743,  1750,  1757,
    1764,  1771,  1778,  1785,  1792,  1799,  1806,  1813,  1820,  1827,
    1834,  1844,  1849,  1856,  1866,  1873,  1880,  1887,  1894,  1901,
    1908,  1915,  1922,  1929,  1936,  1943,  1950,  1957,  1964,  1971,
    1978,  1985,  1992,  1999,  2006,  2013,  2020,  2027,  2034,  2041,
    2048,  2055,  2062,  2069,  2076,  2083,  2090,  2097,  2104,  2111,
    2118,  2125,  2132,  2139,  2146,  2153,  2160,  2167,  2174,  2181,
    2188,  2195,  2202,  2209,  2216,  2223,  2230,  2237,  2244,  2251,
    2258,  2265,  2272,  2279,  2286,  2293,  2300,  2310,  2315,  2322,
    2332,  2339,  2346,  2353,  2360,  2367,  2374,  2381,  2388,  2395,
    2402,  2409,  2416,  2423,  2430,  2437,  2444,  2451,  2458,  2465,
    2472,  2479,  2486,  2493,  2500,  2507,  2514,  2521,  2528,  2535,
    2542,  2549,  2556,  2563,  2570,  2577,  2584,  2591,  2598,  2605,
    2612,  2619,  2626,  2633,  2640,  2647,  2654,  2661,  2668,  2675,
    2682,  2689,  2696,  2703,  2710,  2717,  2724,  2731,  2738,  2745,
    2752,  2759,  2766,  2776,  2796,  2803,  2810,  2820,  2840,  2847,
    2854,  2861,  2868,  2875,  2885,  2901,  2908,  2918,  2934,  2944,
    2964,  2971,  2978,  2985,  2992,  2999,  3009,  3025,  3039,  3053,
    3067,  3081,  3095,  3109,  3123,  3141,  3157,  3173,  3189,  3205,
    3221,  3237,  3257,  3277,  3297,  3317,  3327,  3335,  3343,  3348,
    3353,  3358,  3366,  3388,  3395,  3402,  3409,  3416,  3426,  3448,
    3455,  3462,  3472,  3494,  3504
};
#endif

#define YYPACT_NINF (-668)
#define YYTABLE_NINF (-189)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     872,    32,   230,    75,   112,    46,   494,    94,    -5,   127,
     160,   887,   159,   153,  -668,   535,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,   535,  -668,   535,  -668,   535,  -668,   535,
    -668,   535,  -668,   535,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,   535,  -668,
     535,  -668,   535,  -668,   172,   184,   187,   191,   133,   134,
     193,   198,   200,   214,   535,  -668,  -668,  -668,   929,  -668,
     210,   235,   535,   225,  -668,   535,   261,   132,   263,   250,
    -668,   267,   275,  -668,    55,   303,    37,   299,  -668,   293,
    -668,   -33,   535,   322,   322,   322,   322,   322,   398,   322,
     408,   322,   316,   328,   331,   333,    16,    19,    91,    81,
     345,   361,   357,   360,   398,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,   535,   535,   535,   535,   535,  -668,
    -668,  -668,   103,   334,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,   180,   170,   244,    -9,
     383,   759,   674,   810,   861,   274,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,    14,  -668,
    -668,  -668,  -668,  -668,   322,  -668,   322,   535,  -668,   535,
    -668,  -668,   354,   125,   391,   262,   366,   394,   401,  -668,
     402,  -668,  -668,  -668,   399,   382,   396,   406,    23,   213,
     285,   416,   535,  -668,   535,   535,   535,   535,   474,   404,
     407,   424,   115,   238,   296,   425,   535,  -668,   535,   584,
     413,   421,   430,   181,   253,   415,   435,   535,  -668,   535,
    -668,  -668,   440,   535,  -668,   535,   535,   535,   408,   535,
     535,   408,  -668,   535,   535,   510,  -668,  -668,  -668,  1081,
    1081,  1081,  1081,  1005,     4,    54,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,   669,  -668,  -668,  1229,   113,   419,
     428,   414,   429,    71,   229,   241,   298,   -35,  1157,  -668,
    -668,  -668,  -668,   535,   535,   322,   322,   535,   535,   322,
    -668,   452,  -668,   535,   535,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,    50,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,   441,
     502,    68,  -668,  -668,  -668,  -668,  -668,  -668,   456,   422,
     434,   443,   444,   445,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,    82,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,   511,   546,   102,  -668,  -668,
    -668,  -668,  -668,  -668,   459,   448,   460,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
     142,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,   555,   755,
     177,  -668,  -668,  -668,  -668,  -668,  -668,   477,   463,   466,
    -668,   398,   398,   408,   408,   535,   408,   408,   535,   398,
     398,   508,   929,  -668,  -668,  -668,  -668,   535,  -668,  -668,
       4,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,    54,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,   479,  -668,  -668,
    -668,   535,   501,   507,   535,   535,   535,   499,   519,   645,
     651,   518,   520,   535,   535,   535,   535,   535,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,   503,   505,   535,   535,   322,
     322,   535,  -668,   322,   322,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,   571,
     536,   537,   538,   539,   541,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,   580,
     535,   543,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,   582,   545,   548,   535,
     535,   535,   535,   547,   535,   535,   549,   535,   535,   594,
    -668,   565,  -668,  -668,  -668,  -668,  1005,   535,   535,  1005,
    1005,  1005,   535,   535,   535,  1005,   535,  1005,   535,   535,
    1005,  1005,  1005,  1005,  1005,   535,   535,   572,   573,   535,
     535,   574,   535,   535,  -668,   535,   535,   535,   535,   535,
    -668,   699,   535,  -668,   535,   535,   576,   577,   578,   579,
     535,   581,   586,   535,   589,   599,   629,  -668,   535,  1005,
    1005,   439,   389,   784,  1005,  1005,  1005,   934,  1005,  1009,
    1005,  1005,   620,  1264,  -668,  -668,  -668,  1005,   777,   535,
     535,   608,   610,   535,   613,   615,   777,   777,   777,  1005,
    1005,   535,  1005,  1005,  1005,   535,   535,   535,   535,   777,
     535,   535,   777,   535,   535,   535,   648,   554,   329,  1080,
    1084,  1155,  1159,   870,  1163,  -668,  -668,   699,   777,   535,
     535,   699,   535,   535,   535,   535,   535,  -668,  -668,   624,
     535,   535,   535,  1005,  1005,   777,  1005,   535,   777,  1005,
     535,  1005,  1005,   633,   535,  -668,  -668,   777,   699,   535,
     777,   699,   634,   636,   640,   535,   671,   672,   673,  -668,
    -668,   535,  -668,   664,   535,  -668,   675,  -668,  -668,   535,
    1005,  -668,  -668,   685,  -668,  -668,   677,   689,   690,  1005,
     535,   535,   535,   692,   535,   695,   535,  1005,  -668,   535,
     535,   535,   535,  -668,   777,   777,   777,   535,  1005,   535,
    1005,   535,   777,   699,  1005,  1005,   535,   535,   535,  1005,
    -668,  1005,  -668,   713,  -668,  -668,  -668,  -668,   717,   718,
     721,  -668,  -668,   535,  -668,  -668,  -668,   777,   535,   722,
    -668
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,   188,   196,   197,   198,   199,
     201,   202,   203,     0,   204,     0,   205,     0,   206,     0,
     207,     0,   208,     0,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   230,   200,   486,   487,   488,     0,   489,
       0,   490,     0,   491,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,   194,   192,     0,   191,
     493,   494,     0,     0,   495,     0,     0,     0,   243,     0,
     499,     0,     0,   500,     0,     0,     0,     0,   501,     0,
       1,     0,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   235,   244,     0,   460,   463,     0,     0,   462,
     461,     0,     0,   458,     0,    53,    54,    63,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   188,   188,   188,   188,   188,    50,
      51,    52,   135,    74,   136,   137,   138,   139,   140,   141,
     142,   143,   144,    43,   229,     6,     8,    10,    12,    14,
      16,    18,    21,    26,    29,    32,    36,    41,     4,    45,
      62,     5,    42,    64,    65,    66,    67,    68,    71,    83,
      49,   190,   496,   497,     0,   455,     0,     0,   209,     0,
     452,   231,     0,     0,   237,   238,     0,   242,   241,   236,
     240,   187,   195,     3,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   245,   188,   188,   188,   188,     0,     0,
       0,     0,     0,     0,     0,     0,   188,   311,   188,     0,
       0,     0,     0,     0,     0,     0,     0,   188,   377,   188,
     448,   453,     0,     0,   465,     0,     0,     0,     0,     0,
       0,     0,   464,     0,     0,     0,   233,   503,   485,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,   130,
     131,   132,   133,   134,    70,    81,    75,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    47,
      48,   135,    82,   188,   188,     0,     0,     0,     0,     0,
     444,   449,   239,     0,     0,   446,   445,   451,   268,   270,
     272,   274,   276,   278,   280,   282,   263,   253,   249,   251,
     264,   266,   284,   286,   288,   290,   292,   294,   296,   298,
     255,   257,   259,   261,   304,   306,   308,   310,   246,   248,
     250,   252,   254,   256,   258,   260,   262,   265,     0,     0,
       0,     0,     0,     0,   334,   336,   338,   340,   342,   344,
     346,   348,   329,   319,   315,   317,   330,   332,   350,   352,
     354,   356,   358,   360,   362,   364,   321,   323,   325,   327,
     370,   372,   374,   376,   312,   314,   316,   318,   320,   322,
     324,   326,   328,   331,     0,     0,     0,   400,   402,   404,
     406,   408,   410,   412,   414,   395,   385,   381,   383,   396,
     398,   416,   418,   420,   422,   424,   426,   428,   430,   387,
     389,   391,   393,   436,   438,   440,   442,   378,   380,   382,
     384,   386,   388,   390,   392,   394,   397,     0,     0,     0,
     456,     0,     0,     0,     0,   188,     0,     0,   188,     0,
       0,     0,     0,    40,    37,    38,    39,   188,   125,   126,
      69,    79,   155,   156,   157,   158,   159,   160,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,    72,    85,
      80,   111,   106,   120,    96,   116,   109,    91,   108,   110,
     101,   103,   100,   105,    95,   122,    98,    99,   117,   104,
      94,    97,   114,    87,    88,    89,    90,    92,    93,   102,
     107,   112,   113,   115,   118,   119,   121,    76,    86,   123,
     124,   188,     0,     0,   188,   188,   188,     0,     0,   188,
     188,     0,     0,   188,   188,   188,   188,   188,    59,    60,
      61,    56,    57,    58,    55,     0,     0,   188,   188,     0,
       0,   188,   450,     0,     0,   300,   302,   267,   269,   271,
     273,   275,   277,   279,   281,   283,   285,   287,   289,   291,
     293,   295,   297,   299,   301,   303,   305,   307,   309,     0,
       0,     0,     0,     0,     0,   366,   368,   333,   335,   337,
     339,   341,   343,   345,   347,   349,   351,   353,   355,   357,
     359,   361,   363,   365,   367,   369,   371,   373,   375,     0,
     188,     0,   432,   434,   399,   401,   403,   405,   407,   409,
     411,   413,   415,   417,   419,   421,   423,   425,   427,   429,
     431,   433,   435,   437,   439,   441,     0,     0,     0,   188,
     188,   188,   188,     0,   188,   188,     0,   188,   188,     0,
     232,     0,    78,    84,    77,    73,     0,   188,   188,     0,
       0,     0,   188,   188,   188,     0,   188,     0,   188,   188,
       0,     0,     0,     0,     0,   188,   188,     0,     0,   188,
     188,     0,   188,   188,   247,   188,   188,   188,   188,   188,
     313,     0,   188,   379,   188,   188,     0,     0,     0,     0,
     188,     0,     0,   188,     0,     0,     0,    44,   188,     0,
       0,    13,    15,    17,     0,     0,     0,    22,     0,    24,
       0,     0,    30,    31,    33,    34,    35,     0,     0,   188,
     188,     0,     0,   188,     0,     0,     0,     0,     0,     0,
       0,   188,     0,     0,     0,   188,   188,   188,   188,     0,
     188,   188,     0,   188,   188,   188,     0,     9,    11,    19,
      20,    23,    25,    27,    28,   466,   467,     0,     0,   188,
     188,     0,   188,   188,   188,   188,   188,   454,   457,     0,
     188,   188,   188,     0,     0,     0,     0,   188,     0,     0,
     188,     0,     0,     0,   188,   469,   468,     0,     0,   188,
       0,     0,     0,     0,     0,   188,     0,     0,     0,   475,
     479,   188,   480,     0,   188,   477,     0,   478,   476,   188,
       0,   470,   473,     0,   472,   471,     0,     0,     0,     0,
     188,   188,   188,     0,   188,     0,   188,     0,     7,   188,
     188,   188,   188,   459,     0,     0,     0,   188,     0,   188,
       0,   188,     0,     0,     0,     0,   188,   188,   188,     0,
     481,     0,   482,     0,   474,   234,   443,   447,     0,     0,
       0,   483,   484,   188,   492,   498,   502,     0,   188,     0,
     504
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -668,  -668,  -668,  -668,  -467,  -281,  -668,    43,    52,    97,
      93,   107,  -430,  -667,  -390,  -315,  -484,   179,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,   475,   311,   500,  -191,
     295,  -229,  -668,   -15,    -2,   -70,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,   -92,  -668,   101,  -668,  -267,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,  -668,
    -668
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,    14,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   308,   191,   192,   193,   194,   195,   196,   197,   297,
     675,   480,   294,   198,   498,   537,   538,   481,   295,   199,
     499,   200,   223,   305,   102,    79,    15,    16,    17,    18,
      19,    20,    21,    22,    23,   232,   233,   246,   247,   257,
     258,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     101,   465,   477,    78,   468,   670,    86,   312,   201,   555,
     556,   557,   234,   235,   236,   237,    87,   248,   737,   259,
     739,   103,   309,   104,   221,   105,   310,   106,  -188,   107,
     222,   108,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,    64,   264,   217,   339,   266,    75,   265,    76,
      77,   267,    65,    73,   201,   218,   109,   478,   110,    66,
     111,   482,   483,   484,   485,   486,   487,   311,   540,   781,
      74,   782,   124,   214,   479,    75,   340,    76,    77,   540,
     204,   215,    71,   206,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   341,   342,   343,   344,   345,   346,   347,
     348,   349,    75,   575,    76,    77,   539,   488,   272,   547,
     548,   284,   313,   273,   314,   268,   271,   539,   269,    72,
     576,   597,    85,   270,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   285,   201,   605,   201,   385,   598,   279,
     280,   281,   282,   283,   116,   118,   541,    75,   542,    76,
      77,    88,   606,   100,   208,   627,   286,   318,   209,   117,
     119,   298,   299,   300,   301,   302,   303,   304,   386,   306,
     307,    89,   628,   287,   288,   289,   290,   291,   292,   293,
      99,    75,   112,    76,    77,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   113,   632,   661,   662,   201,   664,
     665,   201,   114,   428,   120,   315,  -188,   316,   744,   745,
     746,   319,   633,  -188,   115,  -188,   121,   369,   122,   370,
     371,   372,   373,   567,   568,   278,    75,   571,    76,    77,
     654,   415,   123,   416,   429,   350,    75,   202,    76,    77,
     205,    67,   458,    68,   459,   201,   201,   655,    69,   201,
      70,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     396,   461,   203,   462,   463,   464,   351,   466,   467,   549,
     550,   469,   470,   472,   207,   439,   211,   321,   210,   -12,
     785,   551,   552,   352,   353,   354,   355,   356,   357,   322,
     212,   397,   797,   798,   323,   800,   801,   802,   565,   566,
      75,   213,    76,    77,   779,   780,   440,   219,   398,   399,
     400,   401,   402,   403,   216,   569,   570,   220,  -188,  -188,
    -188,   573,   574,   441,   442,   443,   444,   445,   446,   224,
      75,   260,    76,    77,   225,   226,   829,   830,   358,   832,
     553,   554,   835,   261,   837,   838,   227,   228,   229,   404,
     783,   784,   230,   262,   231,   359,   360,   361,   362,   363,
     364,   365,   366,   367,   -11,   263,   405,   406,   407,   408,
     409,   410,   411,   412,   413,   742,   743,   274,    75,   275,
      76,    77,   863,   276,   277,    75,   317,    76,    77,   296,
     871,   201,   201,   201,   201,   728,   201,   201,   324,   201,
     201,   880,   201,   882,   336,   238,   320,   886,   887,   325,
     239,   240,   891,   338,   892,   249,   326,   327,   337,   -16,
     250,   251,   241,   242,   243,   -15,   382,   368,   244,   383,
     245,   384,   252,   253,   254,   425,   414,   427,   255,    75,
     256,    76,    77,   426,   761,    75,   457,    76,    77,   460,
     663,   545,   328,   666,    75,   543,    76,    77,   473,   474,
     475,   476,   671,   544,    75,   546,    76,    77,   447,   329,
     330,   331,   332,   333,   334,   335,  -188,   699,   700,   572,
     599,   702,   703,   629,   600,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   577,    75,   601,    76,    77,   201,
     201,   656,    80,   201,   201,   602,   603,   604,    81,    82,
     630,   578,   579,   580,   581,   582,   583,   584,   585,   586,
     815,    83,   631,    84,   819,   657,   676,   374,   658,   679,
     680,   681,   669,   674,   685,   687,   677,   682,   690,   691,
     692,   693,   694,   678,   375,   376,   377,   378,   379,   380,
     381,   842,   697,   698,   845,   587,   701,   683,   688,   858,
     471,   689,   659,   660,   607,   695,    75,   696,    76,    77,
     667,   668,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   608,   609,   610,   611,   612,   613,   614,   615,   616,
    -188,    75,   704,    76,    77,   705,   706,   707,   708,   617,
     709,   710,   712,   713,   714,   726,   885,   715,   634,   720,
      75,   723,    76,    77,   727,   711,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   635,   636,   637,   638,   639,
     640,   641,   642,   643,   749,   750,   753,   417,   765,   766,
     767,   768,   775,   770,   716,   717,   718,   719,   771,   721,
     722,   773,   724,   725,   418,   419,   420,   421,   422,   423,
     424,   774,   729,   730,  -188,  -188,  -188,   734,   735,   736,
     789,   738,   790,   740,   741,   792,    75,   793,    76,    77,
     747,   748,   814,   684,   751,   752,   825,   754,   755,   686,
     756,   757,   758,   759,   760,   839,   846,   762,   847,   763,
     764,    75,   848,    76,    77,   769,   249,    75,   772,    76,
      77,   250,   251,   776,  -188,  -188,   301,   302,   303,   850,
     851,   852,   286,   252,   253,   254,   854,   307,   307,   255,
      75,   256,    76,    77,   787,   788,   860,   856,   791,   287,
     288,   289,   290,   291,   292,   293,   799,   859,   861,   862,
     803,   804,   805,   806,   867,   808,   809,   869,   811,   812,
     813,   893,   299,   300,   304,   304,   894,   895,   306,   306,
     896,   900,   777,   732,   817,   818,   731,   820,   821,   822,
     823,   824,   778,   564,   238,   826,   827,   828,   733,   239,
     240,   672,   833,   673,   500,   836,     0,  -188,  -188,   840,
       0,   241,   242,   243,   843,     0,     0,   244,   644,   245,
     849,     0,     0,     0,     0,    75,   853,    76,    77,   855,
       0,     0,  -188,  -188,   857,   645,   646,   647,   648,   649,
     650,   651,   652,   653,     0,   864,   865,   866,     0,   868,
      75,   870,    76,    77,   872,   873,   874,   875,     0,   786,
     -26,   -26,   879,     0,   881,     0,   883,   794,   795,   796,
       0,   888,   889,   890,     0,     0,    75,     0,    76,    77,
     807,     0,     0,   810,     0,     0,     0,     0,   897,     1,
       2,     3,     0,   899,     0,     0,     4,     0,     5,   816,
       6,     7,     8,     9,     0,    90,    10,    11,    91,     0,
      92,    93,    12,  -188,  -188,    94,   831,    95,     0,   834,
       0,    96,  -188,  -188,    97,     0,    98,    75,   841,    76,
      77,   844,     0,     0,     0,     0,    75,     0,    76,    77,
       0,     0,   125,   126,     0,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,     0,     0,     0,   876,   877,   878,   154,     0,
       0,   155,   156,   884,   -22,   -22,   157,   158,     0,   159,
     160,   161,   162,   163,     0,    75,     0,    76,    77,     0,
      75,     0,    76,    77,     0,     0,     0,     0,   898,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   125,   126,
       0,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,     0,     0,
       0,     0,     0,     0,   154,     0,     0,   155,   156,   -24,
     -24,     0,   157,   158,     0,   159,   160,   161,   162,   163,
       0,     0,     0,     0,     0,    75,     0,    76,    77,     0,
       0,     0,     0,     0,     0,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   125,   126,     0,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,     0,     0,     0,     0,     0,     0,
    -188,  -188,     0,     0,  -188,  -188,     0,     0,     0,   158,
       0,   159,   160,   161,   162,   163,    75,     0,    76,    77,
      75,     0,    76,    77,     0,     0,     0,     0,     0,     0,
       0,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     558,   559,   560,     0,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
       0,     0,     0,     0,     0,   -23,   -23,     0,     0,   -25,
     -25,     0,     0,     0,     0,  -188,  -188,   561,   562,   563,
     311,    75,     0,    76,    77,    75,     0,    76,    77,    75,
       0,    76,    77,     0,     0,     0,     0,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   311,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   164,
     165,   166,   167,   168,   169,   170,   171,   172,  -188,  -188,
    -188,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,     0,    76,    77
};

static const yytype_int16 yycheck[] =
{
      15,   268,   283,     5,   271,   472,    11,   198,    78,    44,
      45,    46,   104,   105,   106,   107,    21,   109,   685,   111,
     687,    23,     8,    25,    57,    27,    12,    29,    37,    31,
      63,    33,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,    10,    27,     7,    22,    27,    56,    32,    58,
      59,    32,    20,     7,   124,    18,    58,    53,    60,    27,
      62,     7,     8,     9,    10,    11,    12,    53,   297,   736,
      24,   738,    74,    18,    70,    56,    53,    58,    59,   308,
      82,    26,     7,    85,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    56,    53,    58,    59,   297,    53,    27,    38,
      39,     8,   204,    32,   206,   117,   118,   308,    27,     7,
      70,    53,    28,    32,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    30,   204,    53,   206,    22,    70,   154,
     155,   156,   157,   158,    11,    11,    33,    56,    35,    58,
      59,    24,    70,     0,    22,    53,    53,    32,    26,    26,
      26,   176,   177,   178,   179,   180,   181,   182,    53,   184,
     185,    11,    70,    70,    71,    72,    73,    74,    75,    76,
      21,    56,    10,    58,    59,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    10,    53,   463,   464,   268,   466,
     467,   271,    15,    22,    11,   207,    36,   209,   692,   693,
     694,   213,    70,    33,    23,    35,    18,   232,    18,   234,
     235,   236,   237,   315,   316,   124,    56,   319,    58,    59,
      53,   246,    18,   248,    53,    22,    56,    27,    58,    59,
      15,    11,   257,    13,   259,   315,   316,    70,    18,   319,
      20,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      22,   263,    27,   265,   266,   267,    53,   269,   270,    40,
      41,   273,   274,   275,    13,    22,    26,    15,    15,    35,
     747,    40,    41,    70,    71,    72,    73,    74,    75,    27,
      23,    53,   759,   760,    32,   762,   763,   764,   313,   314,
      56,    26,    58,    59,   734,   735,    53,     8,    70,    71,
      72,    73,    74,    75,    11,   317,   318,    24,    44,    45,
      46,   323,   324,    70,    71,    72,    73,    74,    75,     7,
      56,    15,    58,    59,    12,    13,   803,   804,    53,   806,
      42,    43,   809,    15,   811,   812,    24,    25,    26,    53,
     740,   741,    30,    22,    32,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    35,    32,    70,    71,    72,    73,
      74,    75,    76,    77,    78,   690,   691,    32,    56,    18,
      58,    59,   849,    26,    24,    56,    32,    58,    59,    55,
     857,   461,   462,   463,   464,   676,   466,   467,    32,   469,
     470,   868,   472,   870,    22,     7,    15,   874,   875,    15,
      12,    13,   879,     7,   881,     7,    15,    15,    22,    36,
      12,    13,    24,    25,    26,    36,    22,    11,    30,    22,
      32,     7,    24,    25,    26,    22,    11,     7,    30,    56,
      32,    58,    59,    22,   711,    56,    11,    58,    59,     9,
     465,    37,    53,   468,    56,    36,    58,    59,   279,   280,
     281,   282,   477,    35,    56,    36,    58,    59,    53,    70,
      71,    72,    73,    74,    75,    76,    37,   569,   570,    27,
      24,   573,   574,    24,    62,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    53,    56,    62,    58,    59,   569,
     570,    24,     8,   573,   574,    62,    62,    62,    14,    15,
      62,    70,    71,    72,    73,    74,    75,    76,    77,    78,
     787,    27,    62,    29,   791,    62,   541,    53,    62,   544,
     545,   546,    24,    54,   549,   550,    35,    38,   553,   554,
     555,   556,   557,    36,    70,    71,    72,    73,    74,    75,
      76,   818,   567,   568,   821,    53,   571,    38,    40,   840,
      50,    41,   461,   462,    53,    62,    56,    62,    58,    59,
     469,   470,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      36,    56,    21,    58,    59,    59,    59,    59,    59,    53,
      59,    21,    59,    21,    59,    11,   873,    59,    53,    62,
      56,    62,    58,    59,    49,   630,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    62,    62,    62,    53,    62,    62,
      62,    62,    13,    62,   659,   660,   661,   662,    62,   664,
     665,    62,   667,   668,    70,    71,    72,    73,    74,    75,
      76,    62,   677,   678,    44,    45,    46,   682,   683,   684,
      62,   686,    62,   688,   689,    62,    56,    62,    58,    59,
     695,   696,    34,    38,   699,   700,    62,   702,   703,    38,
     705,   706,   707,   708,   709,    62,    62,   712,    62,   714,
     715,    56,    62,    58,    59,   720,     7,    56,   723,    58,
      59,    12,    13,   728,    40,    41,   731,   732,   733,    48,
      48,    48,    53,    24,    25,    26,    62,   742,   743,    30,
      56,    32,    58,    59,   749,   750,    59,    62,   753,    70,
      71,    72,    73,    74,    75,    76,   761,    62,    59,    59,
     765,   766,   767,   768,    62,   770,   771,    62,   773,   774,
     775,    48,   777,   778,   779,   780,    49,    49,   783,   784,
      49,    49,   729,   680,   789,   790,   679,   792,   793,   794,
     795,   796,   730,   308,     7,   800,   801,   802,   681,    12,
      13,   480,   807,   498,   294,   810,    -1,    38,    39,   814,
      -1,    24,    25,    26,   819,    -1,    -1,    30,    53,    32,
     825,    -1,    -1,    -1,    -1,    56,   831,    58,    59,   834,
      -1,    -1,    38,    39,   839,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,   850,   851,   852,    -1,   854,
      56,   856,    58,    59,   859,   860,   861,   862,    -1,   748,
      40,    41,   867,    -1,   869,    -1,   871,   756,   757,   758,
      -1,   876,   877,   878,    -1,    -1,    56,    -1,    58,    59,
     769,    -1,    -1,   772,    -1,    -1,    -1,    -1,   893,     7,
       8,     9,    -1,   898,    -1,    -1,    14,    -1,    16,   788,
      18,    19,    20,    21,    -1,     8,    24,    25,    11,    -1,
      13,    14,    30,    42,    43,    18,   805,    20,    -1,   808,
      -1,    24,    42,    43,    27,    -1,    29,    56,   817,    58,
      59,   820,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,
      -1,    -1,     3,     4,    -1,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,   864,   865,   866,    39,    -1,
      -1,    42,    43,   872,    40,    41,    47,    48,    -1,    50,
      51,    52,    53,    54,    -1,    56,    -1,    58,    59,    -1,
      56,    -1,    58,    59,    -1,    -1,    -1,    -1,   897,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     3,     4,
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    43,    40,
      41,    -1,    47,    48,    -1,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,     3,     4,    -1,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    -1,    -1,    40,    41,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    53,    54,    56,    -1,    58,    59,
      56,    -1,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    40,
      41,    -1,    -1,    -1,    -1,    42,    43,    50,    51,    52,
      53,    56,    -1,    58,    59,    56,    -1,    58,    59,    56,
      -1,    58,    59,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    58,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    14,    16,    18,    19,    20,    21,
      24,    25,    30,    80,    81,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,    10,    20,    27,    11,    13,    18,
      20,     7,     7,     7,    24,    56,    58,    59,   123,   124,
       8,    14,    15,    27,    29,    28,    11,    21,    24,    11,
       8,    11,    13,    14,    18,    20,    24,    27,    29,    21,
       0,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,    10,    10,    15,    23,    11,    26,    11,    26,
      11,    18,    18,    18,   123,     3,     4,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    39,    42,    43,    47,    48,    50,
      51,    52,    53,    54,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   101,   102,   103,   104,   105,   106,   107,   112,   118,
     120,   124,    27,    27,   123,    15,   123,    13,    22,    26,
      15,    26,    23,    26,    18,    26,    11,     7,    18,     8,
      24,    57,    63,   121,     7,    12,    13,    24,    25,    26,
      30,    32,   134,   135,   134,   134,   134,   134,     7,    12,
      13,    24,    25,    26,    30,    32,   136,   137,   134,     7,
      12,    13,    24,    25,    26,    30,    32,   138,   139,   134,
      15,    15,    22,    32,    27,    32,    27,    32,   123,    27,
      32,   123,    27,    32,    32,    18,    26,    24,   136,   122,
     122,   122,   122,   122,     8,    30,    53,    70,    71,    72,
      73,    74,    75,    76,   111,   117,    55,   108,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   100,     8,
      12,    53,   118,   134,   134,   123,   123,    32,    32,   123,
      15,    15,    27,    32,    32,    15,    15,    15,    53,    70,
      71,    72,    73,    74,    75,    76,    22,    22,     7,    22,
      53,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      22,    53,    70,    71,    72,    73,    74,    75,    53,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    11,   122,
     122,   122,   122,   122,    53,    70,    71,    72,    73,    74,
      75,    76,    22,    22,     7,    22,    53,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    22,    53,    70,    71,
      72,    73,    74,    75,    53,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    11,   122,   122,    53,    70,    71,
      72,    73,    74,    75,    76,    22,    22,     7,    22,    53,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    22,
      53,    70,    71,    72,    73,    74,    75,    53,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    11,   122,   122,
       9,   123,   123,   123,   123,   138,   123,   123,   138,   123,
     123,    50,   123,    96,    96,    96,    96,    84,    53,    70,
     110,   116,     7,     8,     9,    10,    11,    12,    53,    70,
      71,    72,    73,    74,    75,    76,    77,    78,   113,   119,
     117,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,   114,   115,   118,
     120,    33,    35,    36,    35,    37,    36,    38,    39,    40,
      41,    40,    41,    42,    43,    44,    45,    46,     3,     4,
       5,    50,    51,    52,   115,   122,   122,   134,   134,   123,
     123,   134,    27,   123,   123,    53,    70,    53,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    53,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    53,    70,    24,
      62,    62,    62,    62,    62,    53,    70,    53,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    53,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    53,    70,    24,
      62,    62,    53,    70,    53,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    53,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    53,    70,    24,    62,    62,   136,
     136,   138,   138,   122,   138,   138,   122,   136,   136,    24,
      83,   122,   116,   119,    54,   109,   122,    35,    36,   122,
     122,   122,    38,    38,    38,   122,    38,   122,    40,    41,
     122,   122,   122,   122,   122,    62,    62,   122,   122,   134,
     134,   122,   134,   134,    21,    59,    59,    59,    59,    59,
      21,   122,    59,    21,    59,    59,   122,   122,   122,   122,
      62,   122,   122,    62,   122,   122,    11,    49,    84,   122,
     122,    88,    89,    90,   122,   122,   122,    92,   122,    92,
     122,   122,    94,    94,    95,    95,    95,   122,   122,    62,
      62,   122,   122,    62,   122,   122,   122,   122,   122,   122,
     122,   138,   122,   122,   122,    62,    62,    62,    62,   122,
      62,    62,   122,    62,    62,    13,   122,    86,    87,    91,
      91,    92,    92,    93,    93,    83,   136,   122,   122,    62,
      62,   122,    62,    62,   136,   136,   136,    83,    83,   122,
      83,    83,    83,   122,   122,   122,   122,   136,   122,   122,
     136,   122,   122,   122,    34,   138,   136,   122,   122,   138,
     122,   122,   122,   122,   122,    62,   122,   122,   122,    83,
      83,   136,    83,   122,   136,    83,   122,    83,    83,    62,
     122,   136,   138,   122,   136,   138,    62,    62,    62,   122,
      48,    48,    48,   122,    62,   122,    62,   122,    84,    62,
      59,    59,    59,    83,   122,   122,   122,    62,   122,    62,
     122,    83,   122,   122,   122,   122,   136,   136,   136,   122,
      83,   122,    83,   122,   136,   138,    83,    83,   122,   122,
     122,    83,    83,    48,    49,    49,    49,   122,   136,   122,
      49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    82,    82,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    89,    90,
      90,    90,    91,    91,    91,    91,    91,    92,    92,    92,
      93,    93,    93,    94,    94,    94,    94,    95,    95,    95,
      95,    95,    96,    96,    96,    97,    98,    98,    98,    99,
      99,    99,    99,    99,    99,   100,   100,   100,   100,   100,
     100,   100,   100,   101,   102,   102,   102,   102,   102,   103,
     104,   105,   106,   107,   108,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   115,   115,   116,   116,   117,   117,   117,
     117,   117,   117,   117,   117,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   121,   122,   122,
     123,   123,   124,   124,   124,   121,   125,   126,   127,   128,
     128,   129,   130,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   132,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   134,   134,   134,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138,   138,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   140,   141,   141,   141,   142,   143,   143,
     143,   143,   143,   143,   144,   145,   145,   146,   147,   148,
     149,   149,   149,   149,   149,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   172,
     172,   172,   173,   174,   174,   174,   174,   174,   175,   176,
     176,   176,   177,   178,   179
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     1,     1,     1,     9,     1,     6,
       1,     6,     1,     5,     1,     5,     1,     5,     1,     6,
       6,     1,     5,     6,     5,     6,     1,     6,     6,     1,
       5,     5,     1,     5,     5,     5,     1,     3,     3,     3,
       3,     1,     1,     1,     5,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     0,     1,     1,     1,     1,     1,     1,     3,
       2,     1,     3,     4,     0,     1,     0,     1,     2,     1,
       2,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     6,     4,    13,     3,     3,     3,     3,     4,
       3,     3,     3,     2,     3,     1,     2,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       3,     3,     3,     3,     2,     3,     2,     3,     2,     3,
       2,     1,     2,     4,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     3,     3,     3,     3,
       2,     3,     2,     3,     2,     3,     2,     1,     2,     4,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     3,     3,     3,     3,     2,     3,     2,     3,
       2,     3,     2,    13,     4,     4,     4,    13,     4,     4,
       5,     4,     3,     4,     8,     3,     5,     8,     3,    11,
       3,     3,     3,     3,     4,     4,     8,     8,     9,     9,
      10,    10,    10,    10,    13,    10,    10,    10,    10,    10,
      10,    13,    13,    14,    14,     4,     1,     1,     1,     1,
       1,     1,    14,     2,     2,     2,     3,     3,    14,     2,
       2,     2,    14,     4,    18
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const yytype_int8 yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const yytype_int8 yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     0,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const yytype_uint8 yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,     0,    43,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     7,     9,    11,    13,    15,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,     0,    29,    31,
       0,     0,     0,     0,     0,     0,    21,     0,    23,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,     0,    37,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,     0,    85,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   147,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   149,     0,   151,   153,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    47,
       0,     0,     0,     0,     0,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,    51,    53,     0,     0,    97,     0,    99,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,     0,    91,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     141,     0,   143,   145,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,     0,   131,   133,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,     0,    63,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,     0,    57,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     103,     0,   105,   107,     0,     0,     0,     0,     0,     0,
      67,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,    73,    75,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,     0,    79,
      81,     0,     0,     0,     0,     0,   187,     0,   189,   191,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,     0,   115,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   119,
     121,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   123,     0,   125,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   155,     0,   157,   159,
     161,     0,   163,   165,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   167,   169,     0,     0,   177,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   171,     0,   173,   175,   181,     0,   183,   185,   193,
       0,   195,   197,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,     0,   137,   139
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,   135,     0,   135,     0,   135,     0,   135,     0,   135,
       0,   135,     0,   135,     0,   135,     0,   135,     0,    74,
       0,     8,     0,     8,     0,     8,     0,    10,     0,    10,
       0,    10,     0,   188,     0,    12,     0,    12,     0,    12,
       0,    14,     0,    14,     0,    14,     0,   188,     0,    16,
       0,    16,     0,    16,     0,    18,     0,    18,     0,    18,
       0,    21,     0,    21,     0,    21,     0,   188,     0,   188,
       0,    26,     0,    26,     0,    26,     0,    29,     0,    29,
       0,    29,     0,    32,     0,    32,     0,    32,     0,    13,
       0,    13,     0,    13,     0,   188,     0,    15,     0,    15,
       0,    15,     0,    17,     0,    17,     0,    17,     0,   188,
       0,   188,     0,    22,     0,    22,     0,    22,     0,   188,
       0,   188,     0,    24,     0,    24,     0,    24,     0,    30,
       0,    30,     0,    30,     0,    31,     0,    31,     0,    31,
       0,     9,     0,     9,     0,     9,     0,   188,     0,    11,
       0,    11,     0,    11,     0,    19,     0,    19,     0,    19,
       0,    20,     0,    20,     0,    20,     0,   188,     0,   188,
       0,    23,     0,    23,     0,    23,     0,   188,     0,   188,
       0,    25,     0,    25,     0,    25,     0,    27,     0,    27,
       0,    27,     0,    28,     0,    28,     0,    28,     0
};


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)



#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)


enum { YYENOMEM = -2 };

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif

/** State numbers. */
typedef int yy_state_t;

/** Rule numbers. */
typedef int yyRuleNum;

/** Item references. */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_t yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  YYPTRDIFF_T yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  nonterminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  YYPTRDIFF_T yysize;
  YYPTRDIFF_T yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  YYPTRDIFF_T yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

_Noreturn static void
yyFail (yyGLRStack* yystackp, YYLTYPE *yylocp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yylocp, scanner, parser, base, ast, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

_Noreturn static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

/** Accessing symbol of state YYSTATE.  */
static inline yysymbol_kind_t
yy_accessing_symbol (yy_state_t yystate)
{
  return YY_CAST (yysymbol_kind_t, yystos[yystate]);
}

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"unicode letter\"",
  "\"unicode mark\"", "\"unicode number\"", "\"string\"", "\"a\"", "\"b\"",
  "\"c\"", "\"d\"", "\"e\"", "\"f\"", "\"g\"", "\"h\"", "\"i\"", "\"j\"",
  "\"k\"", "\"l\"", "\"m\"", "\"n\"", "\"o\"", "\"p\"", "\"q\"", "\"r\"",
  "\"s\"", "\"t\"", "\"u\"", "\"v\"", "\"w\"", "\"x\"", "\"y\"", "\"z\"",
  "'?'", "':'", "'|'", "'&'", "'^'", "'='", "'!'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'~'", "'('", "')'", "'_'", "'.'", "'$'",
  "'0'", "'\\''", "'\\\\'", "'\\t'", "'\\n'", "'\\r'", "' '", "'\"'",
  "'#'", "','", "';'", "'@'", "'['", "']'", "'`'", "'{'", "'}'", "'1'",
  "'2'", "'3'", "'4'", "'5'", "'6'", "'7'", "'8'", "'9'", "$accept",
  "Start", "Program", "SymbolIdentifier", "Attribute", "Expression1",
  "Expression2", "Expression3", "Expression4", "Expression5",
  "Expression6", "Expression7", "Expression8", "Expression9",
  "Expression10", "Expression11", "Expression12", "Expression13",
  "Identifier", "IdentifierTop", "IdentifierStart", "IdentifierPart",
  "String", "IntegerConstant", "BinaryConstant", "OctalConstant",
  "DecimalConstant", "HexadecimalConstant", "CharLiteral",
  "MaybeCharEscape", "MaybeCharEnd", "BinaryConstantCore",
  "OctalConstantCore", "DecimalConstantCore", "HexadecimalConstantCore",
  "CharLiteralCore", "AlphaNumber", "BinaryDigit", "OctalDigit",
  "DecimalDigit", "HexadecimalDigit", "Alpha", "Newline", "MWS", "WS",
  "WSChar", "Code", "Instructions", "MI5start", "MI13default_start_broken",
  "MI13default_start_identifier_identifier",
  "MI19roots_default_start_identifier_identifier",
  "MI3isaIH1_13default_start_identifier_identifier",
  "MI11i_rtype_aluIH1_13default_start",
  "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc",
  "MI7xpr_allIH1_13default_start9_7xpr_all2rd",
  "MI11xpr_generalIH1_13default_start9_7xpr_all2rd",
  "MI7xpr_allIH1_13default_start9_7xpr_all3rs1",
  "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1",
  "MI7xpr_allIH1_13default_start9_7xpr_all3rs2",
  "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2",
  "MI13i_rtype_shiftIH1_13default_start",
  "MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc",
  "MI11i_itype_aluIH1_13default_start",
  "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc",
  "MI11i_utype_opsIH1_13default_start",
  "MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc",
  "MI13i_jtype_jlinkIH1_13default_start",
  "MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc",
  "MI16i_btype_branchesIH1_13default_start",
  "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc",
  "MI10i_li_aliasIH1_13default_start", "MI10i_mv_aliasIH1_13default_start",
  "MI11i_not_aliasIH1_13default_start",
  "MI11i_neg_aliasIH1_13default_start",
  "MI12i_seqz_aliasIH1_13default_start",
  "MI12i_snez_aliasIH1_13default_start",
  "MI12i_sltz_aliasIH1_13default_start",
  "MI12i_sgtz_aliasIH1_13default_start",
  "MI11i_sgt_aliasIH1_13default_start",
  "MI12i_beqz_aliasIH1_13default_start",
  "MI12i_bnez_aliasIH1_13default_start",
  "MI12i_blez_aliasIH1_13default_start",
  "MI12i_bltz_aliasIH1_13default_start",
  "MI12i_bgez_aliasIH1_13default_start",
  "MI12i_bgtz_aliasIH1_13default_start",
  "MI11i_bgt_aliasIH1_13default_start",
  "MI11i_ble_aliasIH1_13default_start",
  "MI12i_bgtu_aliasIH1_13default_start",
  "MI12i_bleu_aliasIH1_13default_start",
  "MI10i_jr_aliasIH1_13default_start",
  "MI13default_start_identifier_non_identifier",
  "MI19roots_default_start_identifier_non_identifier",
  "MI3isaIH1_13default_start_identifier_non_identifier",
  "MI13i_itype_loadsIH1_13default_start",
  "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc",
  "MI13i_stype_storeIH1_13default_start",
  "MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc",
  "MI13i_itype_jlregIH1_13default_start",
  "MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc",
  "MI16i_call_reg_aliasIH1_13default_start", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YY_FPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_FPRINTF_

# define YY_FPRINTF_(Args)                      \
  do {                                          \
    YYFPRINTF Args;                             \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

# define YY_DPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_DPRINTF_

# define YY_DPRINTF_(Args)                      \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */



/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (parser);
  YY_USE (base);
  YY_USE (ast);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, parser, base, ast);
  YYFPRINTF (yyo, ")");
}

# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YY_FPRINTF ((stderr, "%s ", Title));                            \
        yy_symbol_print (stderr, Kind, Value, Location, scanner, parser, base, ast);        \
        YY_FPRINTF ((stderr, "\n"));                                    \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

static void yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YY_DPRINTF(Args) do {} while (yyfalse)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)

#endif /* !YYDEBUG */

#ifndef yystrlen
# define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}


/** If yychar is empty, fetch the next token.  */
static inline yysymbol_kind_t
yygetToken (int *yycharp, yyGLRStack* yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  yysymbol_kind_t yytoken;
  YY_USE (scanner);
  YY_USE (parser);
  YY_USE (base);
  YY_USE (ast);
  if (*yycharp == YYEMPTY)
    {
      YY_DPRINTF ((stderr, "Reading a token\n"));
      *yycharp = yylex (&yylval, &yylloc, scanner);
    }
  if (*yycharp <= YYEOF)
    {
      *yycharp = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YY_DPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (*yycharp);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }
  return yytoken;
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, YYLTYPE *yylocp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = yystackp->yysplitPoint == YY_NULLPTR;
  int yylow;
  YY_USE (yyvalp);
  YY_USE (yylocp);
  YY_USE (scanner);
  YY_USE (parser);
  YY_USE (base);
  YY_USE (ast);
  YY_USE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (yylocp, scanner, parser, base, ast, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  /* Default location. */
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;

  switch (yyn)
    {
  case 2: /* Start: Program  */
#line 314 "merged_parser_gen.yy"
    {
        ast = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode);
        YYACCEPT;
    }
#line 2377 "merged_parser_gen.cpp"
    break;

  case 7: /* Expression1: Expression2 MWS '?' MWS Expression1 MWS ':' MWS Expression1  */
#line 339 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateTernary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), "?:", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2385 "merged_parser_gen.cpp"
    break;

  case 9: /* Expression2: Expression2 MWS '|' '|' MWS Expression3  */
#line 347 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "||", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2393 "merged_parser_gen.cpp"
    break;

  case 11: /* Expression3: Expression3 MWS '&' '&' MWS Expression4  */
#line 355 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "&&", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2401 "merged_parser_gen.cpp"
    break;

  case 13: /* Expression4: Expression4 MWS '|' MWS Expression5  */
#line 363 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "|", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2409 "merged_parser_gen.cpp"
    break;

  case 15: /* Expression5: Expression5 MWS '^' MWS Expression6  */
#line 371 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "^", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2417 "merged_parser_gen.cpp"
    break;

  case 17: /* Expression6: Expression6 MWS '&' MWS Expression7  */
#line 379 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "&", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2425 "merged_parser_gen.cpp"
    break;

  case 19: /* Expression7: Expression7 MWS '=' '=' MWS Expression8  */
#line 387 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "==", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2433 "merged_parser_gen.cpp"
    break;

  case 20: /* Expression7: Expression7 MWS '!' '=' MWS Expression8  */
#line 391 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "!=", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2441 "merged_parser_gen.cpp"
    break;

  case 22: /* Expression8: Expression8 MWS '<' MWS Expression9  */
#line 399 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "<", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2449 "merged_parser_gen.cpp"
    break;

  case 23: /* Expression8: Expression8 MWS '<' '=' MWS Expression9  */
#line 403 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "<=", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2457 "merged_parser_gen.cpp"
    break;

  case 24: /* Expression8: Expression8 MWS '>' MWS Expression9  */
#line 407 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ">", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2465 "merged_parser_gen.cpp"
    break;

  case 25: /* Expression8: Expression8 MWS '>' '=' MWS Expression9  */
#line 411 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), ">=", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2473 "merged_parser_gen.cpp"
    break;

  case 27: /* Expression9: Expression9 MWS '<' '<' MWS Expression10  */
#line 419 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "<<", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2481 "merged_parser_gen.cpp"
    break;

  case 28: /* Expression9: Expression9 MWS '>' '>' MWS Expression10  */
#line 423 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), ">>", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2489 "merged_parser_gen.cpp"
    break;

  case 30: /* Expression10: Expression10 MWS '+' MWS Expression11  */
#line 431 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "+", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2497 "merged_parser_gen.cpp"
    break;

  case 31: /* Expression10: Expression10 MWS '-' MWS Expression11  */
#line 435 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "-", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2505 "merged_parser_gen.cpp"
    break;

  case 33: /* Expression11: Expression11 MWS '*' MWS Expression12  */
#line 443 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "*", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2513 "merged_parser_gen.cpp"
    break;

  case 34: /* Expression11: Expression11 MWS '/' MWS Expression12  */
#line 447 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "/", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2521 "merged_parser_gen.cpp"
    break;

  case 35: /* Expression11: Expression11 MWS '%' MWS Expression12  */
#line 451 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateBinary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "%", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2529 "merged_parser_gen.cpp"
    break;

  case 37: /* Expression12: '+' MWS Expression13  */
#line 459 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateUnary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "+", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2537 "merged_parser_gen.cpp"
    break;

  case 38: /* Expression12: '-' MWS Expression13  */
#line 463 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateUnary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "-", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2545 "merged_parser_gen.cpp"
    break;

  case 39: /* Expression12: '~' MWS Expression13  */
#line 467 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateUnary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "~", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2553 "merged_parser_gen.cpp"
    break;

  case 40: /* Expression12: '!' MWS Expression13  */
#line 471 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateUnary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "!", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2561 "merged_parser_gen.cpp"
    break;

  case 44: /* Expression13: '(' MWS Expression1 MWS ')'  */
#line 482 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateUnary(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), "()", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.assemblerNode), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num) + (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num));
    }
#line 2569 "merged_parser_gen.cpp"
    break;

  case 45: /* Identifier: IdentifierTop  */
#line 645 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateIdentifier(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text));
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2578 "merged_parser_gen.cpp"
    break;

  case 46: /* IdentifierTop: IdentifierStart IdentifierPart  */
#line 653 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string();
        *((*yyvalp).text) += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2590 "merged_parser_gen.cpp"
    break;

  case 47: /* IdentifierTop: DecimalConstantCore "b"  */
#line 661 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2599 "merged_parser_gen.cpp"
    break;

  case 48: /* IdentifierTop: DecimalConstantCore "f"  */
#line 666 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2608 "merged_parser_gen.cpp"
    break;

  case 49: /* IdentifierStart: Alpha  */
#line 674 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string();
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2617 "merged_parser_gen.cpp"
    break;

  case 50: /* IdentifierStart: '_'  */
#line 679 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string("_");
    }
#line 2625 "merged_parser_gen.cpp"
    break;

  case 51: /* IdentifierStart: '.'  */
#line 683 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string(".");
    }
#line 2633 "merged_parser_gen.cpp"
    break;

  case 52: /* IdentifierStart: '$'  */
#line 687 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string("$");
    }
#line 2641 "merged_parser_gen.cpp"
    break;

  case 55: /* IdentifierPart: IdentifierPart AlphaNumber  */
#line 696 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2650 "merged_parser_gen.cpp"
    break;

  case 56: /* IdentifierPart: IdentifierPart '_'  */
#line 701 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += "_";
    }
#line 2659 "merged_parser_gen.cpp"
    break;

  case 57: /* IdentifierPart: IdentifierPart '.'  */
#line 706 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += ".";
    }
#line 2668 "merged_parser_gen.cpp"
    break;

  case 58: /* IdentifierPart: IdentifierPart '$'  */
#line 711 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += "$";
    }
#line 2677 "merged_parser_gen.cpp"
    break;

  case 59: /* IdentifierPart: IdentifierPart "unicode letter"  */
#line 716 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2686 "merged_parser_gen.cpp"
    break;

  case 60: /* IdentifierPart: IdentifierPart "unicode mark"  */
#line 721 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2695 "merged_parser_gen.cpp"
    break;

  case 61: /* IdentifierPart: IdentifierPart "unicode number"  */
#line 726 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2704 "merged_parser_gen.cpp"
    break;

  case 62: /* IdentifierPart: %empty  */
#line 731 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string();
    }
#line 2712 "merged_parser_gen.cpp"
    break;

  case 63: /* String: "string"  */
#line 740 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateString(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text));
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2721 "merged_parser_gen.cpp"
    break;

  case 69: /* BinaryConstant: '0' "b" BinaryConstantCore  */
#line 758 "merged_parser_gen.yy"
    {
        std::string s = "0";
        s += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.character);
        s += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
        ((*yyvalp).assemblerNode) = &ParserUtility::ConvertConstantToToken(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), s, 2, 2, "binary");
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2733 "merged_parser_gen.cpp"
    break;

  case 70: /* OctalConstant: '0' OctalConstantCore  */
#line 769 "merged_parser_gen.yy"
    {
        std::string s = "0";
        s += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
        ((*yyvalp).assemblerNode) = &ParserUtility::ConvertConstantToToken(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), s, 1, 8, "octal");
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2744 "merged_parser_gen.cpp"
    break;

  case 71: /* DecimalConstant: DecimalConstantCore  */
#line 779 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ParserUtility::ConvertConstantToToken(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text), 0, 10, "decimal");
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2753 "merged_parser_gen.cpp"
    break;

  case 72: /* HexadecimalConstant: '0' "x" HexadecimalConstantCore  */
#line 787 "merged_parser_gen.yy"
    {
        std::string s = "0";
        s += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.character);
        s += *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
        ((*yyvalp).assemblerNode) = &ParserUtility::ConvertConstantToToken(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), s, 2, 16, "hexadecimal");
        delete (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
    }
#line 2765 "merged_parser_gen.cpp"
    break;

  case 73: /* CharLiteral: '\'' MaybeCharEscape CharLiteralCore MaybeCharEnd  */
#line 798 "merged_parser_gen.yy"
    {
        std::string s = "'";
        if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.character) != '\0')
        {
            s += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.character);
        }
        s += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.character);
        if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character) != '\0')
        {
            s += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
        }
        ((*yyvalp).assemblerNode) = &ParserUtility::ConvertConstantToToken(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), s, 1, 0, "character");
    }
#line 2783 "merged_parser_gen.cpp"
    break;

  case 74: /* MaybeCharEscape: %empty  */
#line 815 "merged_parser_gen.yy"
    {
        ((*yyvalp).character) = '\0';
    }
#line 2791 "merged_parser_gen.cpp"
    break;

  case 75: /* MaybeCharEscape: '\\'  */
#line 819 "merged_parser_gen.yy"
    {
        ((*yyvalp).character) = '\\';
    }
#line 2799 "merged_parser_gen.cpp"
    break;

  case 76: /* MaybeCharEnd: %empty  */
#line 826 "merged_parser_gen.yy"
    {
        ((*yyvalp).character) = '\0';
    }
#line 2807 "merged_parser_gen.cpp"
    break;

  case 77: /* MaybeCharEnd: '\''  */
#line 830 "merged_parser_gen.yy"
    {
        ((*yyvalp).character) = '\'';
    }
#line 2815 "merged_parser_gen.cpp"
    break;

  case 78: /* BinaryConstantCore: BinaryConstantCore BinaryDigit  */
#line 837 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2824 "merged_parser_gen.cpp"
    break;

  case 79: /* BinaryConstantCore: BinaryDigit  */
#line 842 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string();
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2833 "merged_parser_gen.cpp"
    break;

  case 80: /* OctalConstantCore: OctalConstantCore OctalDigit  */
#line 850 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2842 "merged_parser_gen.cpp"
    break;

  case 81: /* OctalConstantCore: OctalDigit  */
#line 855 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string();
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2851 "merged_parser_gen.cpp"
    break;

  case 82: /* DecimalConstantCore: DecimalConstantCore DecimalDigit  */
#line 863 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2860 "merged_parser_gen.cpp"
    break;

  case 83: /* DecimalConstantCore: DecimalDigit  */
#line 868 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string();
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2869 "merged_parser_gen.cpp"
    break;

  case 84: /* HexadecimalConstantCore: HexadecimalConstantCore HexadecimalDigit  */
#line 876 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text);
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2878 "merged_parser_gen.cpp"
    break;

  case 85: /* HexadecimalConstantCore: HexadecimalDigit  */
#line 881 "merged_parser_gen.yy"
    {
        ((*yyvalp).text) = new std::string();
        *((*yyvalp).text) += (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.character);
    }
#line 2887 "merged_parser_gen.cpp"
    break;

  case 87: /* CharLiteralCore: '\t'  */
#line 889 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '\t'; }
#line 2893 "merged_parser_gen.cpp"
    break;

  case 88: /* CharLiteralCore: '\n'  */
#line 890 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '\n'; }
#line 2899 "merged_parser_gen.cpp"
    break;

  case 89: /* CharLiteralCore: '\r'  */
#line 891 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '\r'; }
#line 2905 "merged_parser_gen.cpp"
    break;

  case 90: /* CharLiteralCore: ' '  */
#line 892 "merged_parser_gen.yy"
           { ((*yyvalp).character) = ' '; }
#line 2911 "merged_parser_gen.cpp"
    break;

  case 91: /* CharLiteralCore: '!'  */
#line 893 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '!'; }
#line 2917 "merged_parser_gen.cpp"
    break;

  case 92: /* CharLiteralCore: '"'  */
#line 894 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '"'; }
#line 2923 "merged_parser_gen.cpp"
    break;

  case 93: /* CharLiteralCore: '#'  */
#line 895 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '#'; }
#line 2929 "merged_parser_gen.cpp"
    break;

  case 94: /* CharLiteralCore: '$'  */
#line 896 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '$'; }
#line 2935 "merged_parser_gen.cpp"
    break;

  case 95: /* CharLiteralCore: '%'  */
#line 897 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '%'; }
#line 2941 "merged_parser_gen.cpp"
    break;

  case 96: /* CharLiteralCore: '&'  */
#line 898 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '&'; }
#line 2947 "merged_parser_gen.cpp"
    break;

  case 97: /* CharLiteralCore: '\''  */
#line 899 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '\''; }
#line 2953 "merged_parser_gen.cpp"
    break;

  case 98: /* CharLiteralCore: '('  */
#line 900 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '('; }
#line 2959 "merged_parser_gen.cpp"
    break;

  case 99: /* CharLiteralCore: ')'  */
#line 901 "merged_parser_gen.yy"
           { ((*yyvalp).character) = ')'; }
#line 2965 "merged_parser_gen.cpp"
    break;

  case 100: /* CharLiteralCore: '*'  */
#line 902 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '*'; }
#line 2971 "merged_parser_gen.cpp"
    break;

  case 101: /* CharLiteralCore: '+'  */
#line 903 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '+'; }
#line 2977 "merged_parser_gen.cpp"
    break;

  case 102: /* CharLiteralCore: ','  */
#line 904 "merged_parser_gen.yy"
           { ((*yyvalp).character) = ','; }
#line 2983 "merged_parser_gen.cpp"
    break;

  case 103: /* CharLiteralCore: '-'  */
#line 905 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '-'; }
#line 2989 "merged_parser_gen.cpp"
    break;

  case 104: /* CharLiteralCore: '.'  */
#line 906 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '.'; }
#line 2995 "merged_parser_gen.cpp"
    break;

  case 105: /* CharLiteralCore: '/'  */
#line 907 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '/'; }
#line 3001 "merged_parser_gen.cpp"
    break;

  case 106: /* CharLiteralCore: ':'  */
#line 908 "merged_parser_gen.yy"
           { ((*yyvalp).character) = ':'; }
#line 3007 "merged_parser_gen.cpp"
    break;

  case 107: /* CharLiteralCore: ';'  */
#line 909 "merged_parser_gen.yy"
           { ((*yyvalp).character) = ';'; }
#line 3013 "merged_parser_gen.cpp"
    break;

  case 108: /* CharLiteralCore: '<'  */
#line 910 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '<'; }
#line 3019 "merged_parser_gen.cpp"
    break;

  case 109: /* CharLiteralCore: '='  */
#line 911 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '='; }
#line 3025 "merged_parser_gen.cpp"
    break;

  case 110: /* CharLiteralCore: '>'  */
#line 912 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '>'; }
#line 3031 "merged_parser_gen.cpp"
    break;

  case 111: /* CharLiteralCore: '?'  */
#line 913 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '?'; }
#line 3037 "merged_parser_gen.cpp"
    break;

  case 112: /* CharLiteralCore: '@'  */
#line 914 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '@'; }
#line 3043 "merged_parser_gen.cpp"
    break;

  case 113: /* CharLiteralCore: '['  */
#line 915 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '['; }
#line 3049 "merged_parser_gen.cpp"
    break;

  case 114: /* CharLiteralCore: '\\'  */
#line 916 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '\\'; }
#line 3055 "merged_parser_gen.cpp"
    break;

  case 115: /* CharLiteralCore: ']'  */
#line 917 "merged_parser_gen.yy"
           { ((*yyvalp).character) = ']'; }
#line 3061 "merged_parser_gen.cpp"
    break;

  case 116: /* CharLiteralCore: '^'  */
#line 918 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '^'; }
#line 3067 "merged_parser_gen.cpp"
    break;

  case 117: /* CharLiteralCore: '_'  */
#line 919 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '_'; }
#line 3073 "merged_parser_gen.cpp"
    break;

  case 118: /* CharLiteralCore: '`'  */
#line 920 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '`'; }
#line 3079 "merged_parser_gen.cpp"
    break;

  case 119: /* CharLiteralCore: '{'  */
#line 921 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '{'; }
#line 3085 "merged_parser_gen.cpp"
    break;

  case 120: /* CharLiteralCore: '|'  */
#line 922 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '|'; }
#line 3091 "merged_parser_gen.cpp"
    break;

  case 121: /* CharLiteralCore: '}'  */
#line 923 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '}'; }
#line 3097 "merged_parser_gen.cpp"
    break;

  case 122: /* CharLiteralCore: '~'  */
#line 924 "merged_parser_gen.yy"
           { ((*yyvalp).character) = '~'; }
#line 3103 "merged_parser_gen.cpp"
    break;

  case 125: /* BinaryDigit: '0'  */
#line 933 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '0'; }
#line 3109 "merged_parser_gen.cpp"
    break;

  case 126: /* BinaryDigit: '1'  */
#line 934 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '1'; }
#line 3115 "merged_parser_gen.cpp"
    break;

  case 127: /* OctalDigit: '0'  */
#line 938 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '0'; }
#line 3121 "merged_parser_gen.cpp"
    break;

  case 128: /* OctalDigit: '1'  */
#line 939 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '1'; }
#line 3127 "merged_parser_gen.cpp"
    break;

  case 129: /* OctalDigit: '2'  */
#line 940 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '2'; }
#line 3133 "merged_parser_gen.cpp"
    break;

  case 130: /* OctalDigit: '3'  */
#line 941 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '3'; }
#line 3139 "merged_parser_gen.cpp"
    break;

  case 131: /* OctalDigit: '4'  */
#line 942 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '4'; }
#line 3145 "merged_parser_gen.cpp"
    break;

  case 132: /* OctalDigit: '5'  */
#line 943 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '5'; }
#line 3151 "merged_parser_gen.cpp"
    break;

  case 133: /* OctalDigit: '6'  */
#line 944 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '6'; }
#line 3157 "merged_parser_gen.cpp"
    break;

  case 134: /* OctalDigit: '7'  */
#line 945 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '7'; }
#line 3163 "merged_parser_gen.cpp"
    break;

  case 135: /* DecimalDigit: '0'  */
#line 949 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '0'; }
#line 3169 "merged_parser_gen.cpp"
    break;

  case 136: /* DecimalDigit: '1'  */
#line 950 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '1'; }
#line 3175 "merged_parser_gen.cpp"
    break;

  case 137: /* DecimalDigit: '2'  */
#line 951 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '2'; }
#line 3181 "merged_parser_gen.cpp"
    break;

  case 138: /* DecimalDigit: '3'  */
#line 952 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '3'; }
#line 3187 "merged_parser_gen.cpp"
    break;

  case 139: /* DecimalDigit: '4'  */
#line 953 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '4'; }
#line 3193 "merged_parser_gen.cpp"
    break;

  case 140: /* DecimalDigit: '5'  */
#line 954 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '5'; }
#line 3199 "merged_parser_gen.cpp"
    break;

  case 141: /* DecimalDigit: '6'  */
#line 955 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '6'; }
#line 3205 "merged_parser_gen.cpp"
    break;

  case 142: /* DecimalDigit: '7'  */
#line 956 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '7'; }
#line 3211 "merged_parser_gen.cpp"
    break;

  case 143: /* DecimalDigit: '8'  */
#line 957 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '8'; }
#line 3217 "merged_parser_gen.cpp"
    break;

  case 144: /* DecimalDigit: '9'  */
#line 958 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '9'; }
#line 3223 "merged_parser_gen.cpp"
    break;

  case 145: /* HexadecimalDigit: '0'  */
#line 962 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '0'; }
#line 3229 "merged_parser_gen.cpp"
    break;

  case 146: /* HexadecimalDigit: '1'  */
#line 963 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '1'; }
#line 3235 "merged_parser_gen.cpp"
    break;

  case 147: /* HexadecimalDigit: '2'  */
#line 964 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '2'; }
#line 3241 "merged_parser_gen.cpp"
    break;

  case 148: /* HexadecimalDigit: '3'  */
#line 965 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '3'; }
#line 3247 "merged_parser_gen.cpp"
    break;

  case 149: /* HexadecimalDigit: '4'  */
#line 966 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '4'; }
#line 3253 "merged_parser_gen.cpp"
    break;

  case 150: /* HexadecimalDigit: '5'  */
#line 967 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '5'; }
#line 3259 "merged_parser_gen.cpp"
    break;

  case 151: /* HexadecimalDigit: '6'  */
#line 968 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '6'; }
#line 3265 "merged_parser_gen.cpp"
    break;

  case 152: /* HexadecimalDigit: '7'  */
#line 969 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '7'; }
#line 3271 "merged_parser_gen.cpp"
    break;

  case 153: /* HexadecimalDigit: '8'  */
#line 970 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '8'; }
#line 3277 "merged_parser_gen.cpp"
    break;

  case 154: /* HexadecimalDigit: '9'  */
#line 971 "merged_parser_gen.yy"
          { ((*yyvalp).character) = '9'; }
#line 3283 "merged_parser_gen.cpp"
    break;

  case 188: /* MWS: %empty  */
#line 1028 "merged_parser_gen.yy"
    {
        ((*yyvalp).num) = 0;
    }
#line 3291 "merged_parser_gen.cpp"
    break;

  case 190: /* WS: WS WSChar  */
#line 1036 "merged_parser_gen.yy"
    {
        ((*yyvalp).num) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num) + 1;
    }
#line 3299 "merged_parser_gen.cpp"
    break;

  case 191: /* WS: WSChar  */
#line 1040 "merged_parser_gen.yy"
    {
        ((*yyvalp).num) = 1;
    }
#line 3307 "merged_parser_gen.cpp"
    break;

  case 196: /* Code: Instructions  */
#line 1059 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode);
    }
#line 3315 "merged_parser_gen.cpp"
    break;

  case 197: /* Instructions: MI5start  */
#line 1066 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateGenerateInstructionCommand(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 0);
    }
#line 3323 "merged_parser_gen.cpp"
    break;

  case 198: /* MI5start: MI13default_start_broken  */
#line 1073 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI5start", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3332 "merged_parser_gen.cpp"
    break;

  case 199: /* MI13default_start_broken: MI13default_start_identifier_identifier  */
#line 1081 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13default_start_broken", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3341 "merged_parser_gen.cpp"
    break;

  case 200: /* MI13default_start_broken: MI13default_start_identifier_non_identifier  */
#line 1086 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13default_start_broken", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3350 "merged_parser_gen.cpp"
    break;

  case 201: /* MI13default_start_identifier_identifier: MI19roots_default_start_identifier_identifier  */
#line 1094 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI13default_start_identifier_identifier", "", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3359 "merged_parser_gen.cpp"
    break;

  case 202: /* MI19roots_default_start_identifier_identifier: MI3isaIH1_13default_start_identifier_identifier  */
#line 1102 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI19roots_default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3368 "merged_parser_gen.cpp"
    break;

  case 203: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_rtype_aluIH1_13default_start  */
#line 1110 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3377 "merged_parser_gen.cpp"
    break;

  case 204: /* MI3isaIH1_13default_start_identifier_identifier: MI13i_rtype_shiftIH1_13default_start  */
#line 1115 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3386 "merged_parser_gen.cpp"
    break;

  case 205: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_itype_aluIH1_13default_start  */
#line 1120 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3395 "merged_parser_gen.cpp"
    break;

  case 206: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_utype_opsIH1_13default_start  */
#line 1125 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3404 "merged_parser_gen.cpp"
    break;

  case 207: /* MI3isaIH1_13default_start_identifier_identifier: MI13i_jtype_jlinkIH1_13default_start  */
#line 1130 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3413 "merged_parser_gen.cpp"
    break;

  case 208: /* MI3isaIH1_13default_start_identifier_identifier: MI16i_btype_branchesIH1_13default_start  */
#line 1135 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3422 "merged_parser_gen.cpp"
    break;

  case 209: /* MI3isaIH1_13default_start_identifier_identifier: "n" "o" "p"  */
#line 1140 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_nop_aliasIH1_13default_start", "i_nop_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "nop"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3433 "merged_parser_gen.cpp"
    break;

  case 210: /* MI3isaIH1_13default_start_identifier_identifier: MI10i_li_aliasIH1_13default_start  */
#line 1147 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3442 "merged_parser_gen.cpp"
    break;

  case 211: /* MI3isaIH1_13default_start_identifier_identifier: MI10i_mv_aliasIH1_13default_start  */
#line 1152 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3451 "merged_parser_gen.cpp"
    break;

  case 212: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_not_aliasIH1_13default_start  */
#line 1157 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3460 "merged_parser_gen.cpp"
    break;

  case 213: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_neg_aliasIH1_13default_start  */
#line 1162 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3469 "merged_parser_gen.cpp"
    break;

  case 214: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_seqz_aliasIH1_13default_start  */
#line 1167 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3478 "merged_parser_gen.cpp"
    break;

  case 215: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_snez_aliasIH1_13default_start  */
#line 1172 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3487 "merged_parser_gen.cpp"
    break;

  case 216: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_sltz_aliasIH1_13default_start  */
#line 1177 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3496 "merged_parser_gen.cpp"
    break;

  case 217: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_sgtz_aliasIH1_13default_start  */
#line 1182 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3505 "merged_parser_gen.cpp"
    break;

  case 218: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_sgt_aliasIH1_13default_start  */
#line 1187 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3514 "merged_parser_gen.cpp"
    break;

  case 219: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_beqz_aliasIH1_13default_start  */
#line 1192 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3523 "merged_parser_gen.cpp"
    break;

  case 220: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_bnez_aliasIH1_13default_start  */
#line 1197 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3532 "merged_parser_gen.cpp"
    break;

  case 221: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_blez_aliasIH1_13default_start  */
#line 1202 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3541 "merged_parser_gen.cpp"
    break;

  case 222: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_bltz_aliasIH1_13default_start  */
#line 1207 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3550 "merged_parser_gen.cpp"
    break;

  case 223: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_bgez_aliasIH1_13default_start  */
#line 1212 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3559 "merged_parser_gen.cpp"
    break;

  case 224: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_bgtz_aliasIH1_13default_start  */
#line 1217 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3568 "merged_parser_gen.cpp"
    break;

  case 225: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_bgt_aliasIH1_13default_start  */
#line 1222 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3577 "merged_parser_gen.cpp"
    break;

  case 226: /* MI3isaIH1_13default_start_identifier_identifier: MI11i_ble_aliasIH1_13default_start  */
#line 1227 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3586 "merged_parser_gen.cpp"
    break;

  case 227: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_bgtu_aliasIH1_13default_start  */
#line 1232 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3595 "merged_parser_gen.cpp"
    break;

  case 228: /* MI3isaIH1_13default_start_identifier_identifier: MI12i_bleu_aliasIH1_13default_start  */
#line 1237 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3604 "merged_parser_gen.cpp"
    break;

  case 229: /* MI3isaIH1_13default_start_identifier_identifier: "j" WS Attribute  */
#line 1242 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI9i_j_aliasIH1_13default_start", "i_j_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "j"));
        x1->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // WS
        ast::assembler::Node* x2 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr20IH1_13default_start18_15relative_addr204simm", "relative_addr20", 0, 0);
        x2->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20", "addr20", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 20, 1));
        x1->AddChild(*x2);
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3619 "merged_parser_gen.cpp"
    break;

  case 230: /* MI3isaIH1_13default_start_identifier_identifier: MI10i_jr_aliasIH1_13default_start  */
#line 1253 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3628 "merged_parser_gen.cpp"
    break;

  case 231: /* MI3isaIH1_13default_start_identifier_identifier: "r" "e" "t"  */
#line 1258 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_ret_aliasIH1_13default_start", "i_ret_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "ret"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3639 "merged_parser_gen.cpp"
    break;

  case 232: /* MI3isaIH1_13default_start_identifier_identifier: "c" "a" "l" "l" WS Attribute  */
#line 1265 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_call_aliasIH1_13default_start", "i_call_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), "call"));
        x1->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // WS
        ast::assembler::Node* x2 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr20IH1_13default_start18_15relative_addr204simm", "relative_addr20", 0, 0);
        x2->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20", "addr20", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 20, 1));
        x1->AddChild(*x2);
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3654 "merged_parser_gen.cpp"
    break;

  case 233: /* MI3isaIH1_13default_start_identifier_identifier: "h" "a" "l" "t"  */
#line 1276 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_identifier", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6i_haltIH1_13default_start", "i_halt", 0, 0);
        ast::assembler::Node* x2 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_haltIH1_13default_start10_8opc_halt3opc", "opc_halt", 0, 0);
        x2->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "halt"));
        x1->AddChild(*x2);
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3667 "merged_parser_gen.cpp"
    break;

  case 234: /* MI11i_rtype_aluIH1_13default_start: MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2  */
#line 1288 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_rtype_aluIH1_13default_start", "i_rtype_alu", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3686 "merged_parser_gen.cpp"
    break;

  case 235: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "a" "d" "d"  */
#line 1306 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_addIH1_13default_start16_13opc_rtype_alu3opc", "opc_add", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "add"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3697 "merged_parser_gen.cpp"
    break;

  case 236: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "s" "u" "b"  */
#line 1313 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_subIH1_13default_start16_13opc_rtype_alu3opc", "opc_sub", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "sub"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3708 "merged_parser_gen.cpp"
    break;

  case 237: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "s" "l" "l"  */
#line 1320 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_sllIH1_13default_start16_13opc_rtype_alu3opc", "opc_sll", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "sll"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3719 "merged_parser_gen.cpp"
    break;

  case 238: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "s" "l" "t"  */
#line 1327 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_sltIH1_13default_start16_13opc_rtype_alu3opc", "opc_slt", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "slt"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3730 "merged_parser_gen.cpp"
    break;

  case 239: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "s" "l" "t" "u"  */
#line 1334 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_sltuIH1_13default_start16_13opc_rtype_alu3opc", "opc_sltu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "sltu"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3741 "merged_parser_gen.cpp"
    break;

  case 240: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "x" "o" "r"  */
#line 1341 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_xorIH1_13default_start16_13opc_rtype_alu3opc", "opc_xor", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "xor"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3752 "merged_parser_gen.cpp"
    break;

  case 241: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "s" "r" "l"  */
#line 1348 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_srlIH1_13default_start16_13opc_rtype_alu3opc", "opc_srl", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "srl"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3763 "merged_parser_gen.cpp"
    break;

  case 242: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "s" "r" "a"  */
#line 1355 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_sraIH1_13default_start16_13opc_rtype_alu3opc", "opc_sra", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "sra"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3774 "merged_parser_gen.cpp"
    break;

  case 243: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "o" "r"  */
#line 1362 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6opc_orIH1_13default_start16_13opc_rtype_alu3opc", "opc_or", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "or"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3785 "merged_parser_gen.cpp"
    break;

  case 244: /* MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc: "a" "n" "d"  */
#line 1369 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_rtype_aluIH1_13default_start16_13opc_rtype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_andIH1_13default_start16_13opc_rtype_alu3opc", "opc_and", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "and"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3796 "merged_parser_gen.cpp"
    break;

  case 245: /* MI7xpr_allIH1_13default_start9_7xpr_all2rd: MI11xpr_generalIH1_13default_start9_7xpr_all2rd  */
#line 1379 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all2rd", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 3805 "merged_parser_gen.cpp"
    break;

  case 246: /* MI7xpr_allIH1_13default_start9_7xpr_all2rd: "x" '0'  */
#line 1384 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all2rd", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_0IH1_13default_start9_7xpr_all2rd", "x_0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3816 "merged_parser_gen.cpp"
    break;

  case 247: /* MI7xpr_allIH1_13default_start9_7xpr_all2rd: "z" "e" "r" "o"  */
#line 1391 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all2rd", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI9x_0_aliasIH1_13default_start9_7xpr_all2rd", "x_0_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "zero"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3827 "merged_parser_gen.cpp"
    break;

  case 248: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1'  */
#line 1401 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_1IH1_13default_start9_7xpr_all2rd", "x_1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3838 "merged_parser_gen.cpp"
    break;

  case 249: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "r" "a"  */
#line 1408 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_1_alias0IH1_13default_start9_7xpr_all2rd", "x_1_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "ra"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3849 "merged_parser_gen.cpp"
    break;

  case 250: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2'  */
#line 1415 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_2IH1_13default_start9_7xpr_all2rd", "x_2", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3860 "merged_parser_gen.cpp"
    break;

  case 251: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" "p"  */
#line 1422 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_2_alias0IH1_13default_start9_7xpr_all2rd", "x_2_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "sp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3871 "merged_parser_gen.cpp"
    break;

  case 252: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '3'  */
#line 1429 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_3IH1_13default_start9_7xpr_all2rd", "x_3", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3882 "merged_parser_gen.cpp"
    break;

  case 253: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "g" "p"  */
#line 1436 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_3_alias0IH1_13default_start9_7xpr_all2rd", "x_3_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "gp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3893 "merged_parser_gen.cpp"
    break;

  case 254: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '4'  */
#line 1443 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_4IH1_13default_start9_7xpr_all2rd", "x_4", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3904 "merged_parser_gen.cpp"
    break;

  case 255: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" "p"  */
#line 1450 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_4_alias0IH1_13default_start9_7xpr_all2rd", "x_4_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "tp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3915 "merged_parser_gen.cpp"
    break;

  case 256: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '5'  */
#line 1457 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_5IH1_13default_start9_7xpr_all2rd", "x_5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3926 "merged_parser_gen.cpp"
    break;

  case 257: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" '0'  */
#line 1464 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_5_alias0IH1_13default_start9_7xpr_all2rd", "x_5_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3937 "merged_parser_gen.cpp"
    break;

  case 258: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '6'  */
#line 1471 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_6IH1_13default_start9_7xpr_all2rd", "x_6", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3948 "merged_parser_gen.cpp"
    break;

  case 259: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" '1'  */
#line 1478 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_6_alias0IH1_13default_start9_7xpr_all2rd", "x_6_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3959 "merged_parser_gen.cpp"
    break;

  case 260: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '7'  */
#line 1485 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_7IH1_13default_start9_7xpr_all2rd", "x_7", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3970 "merged_parser_gen.cpp"
    break;

  case 261: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" '2'  */
#line 1492 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_7_alias0IH1_13default_start9_7xpr_all2rd", "x_7_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3981 "merged_parser_gen.cpp"
    break;

  case 262: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '8'  */
#line 1499 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_8IH1_13default_start9_7xpr_all2rd", "x_8", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x8"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 3992 "merged_parser_gen.cpp"
    break;

  case 263: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "f" "p"  */
#line 1506 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_8_alias0IH1_13default_start9_7xpr_all2rd", "x_8_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "fp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4003 "merged_parser_gen.cpp"
    break;

  case 264: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '0'  */
#line 1513 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_8_alias1IH1_13default_start9_7xpr_all2rd", "x_8_alias1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4014 "merged_parser_gen.cpp"
    break;

  case 265: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '9'  */
#line 1520 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_9IH1_13default_start9_7xpr_all2rd", "x_9", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x9"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4025 "merged_parser_gen.cpp"
    break;

  case 266: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '1'  */
#line 1527 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_9_alias0IH1_13default_start9_7xpr_all2rd", "x_9_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4036 "merged_parser_gen.cpp"
    break;

  case 267: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '0'  */
#line 1534 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_10IH1_13default_start9_7xpr_all2rd", "x_10", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x10"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4047 "merged_parser_gen.cpp"
    break;

  case 268: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '0'  */
#line 1541 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_10_alias0IH1_13default_start9_7xpr_all2rd", "x_10_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4058 "merged_parser_gen.cpp"
    break;

  case 269: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '1'  */
#line 1548 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_11IH1_13default_start9_7xpr_all2rd", "x_11", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x11"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4069 "merged_parser_gen.cpp"
    break;

  case 270: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '1'  */
#line 1555 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_11_alias0IH1_13default_start9_7xpr_all2rd", "x_11_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4080 "merged_parser_gen.cpp"
    break;

  case 271: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '2'  */
#line 1562 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_12IH1_13default_start9_7xpr_all2rd", "x_12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x12"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4091 "merged_parser_gen.cpp"
    break;

  case 272: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '2'  */
#line 1569 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_12_alias0IH1_13default_start9_7xpr_all2rd", "x_12_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4102 "merged_parser_gen.cpp"
    break;

  case 273: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '3'  */
#line 1576 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_13IH1_13default_start9_7xpr_all2rd", "x_13", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x13"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4113 "merged_parser_gen.cpp"
    break;

  case 274: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '3'  */
#line 1583 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_13_alias0IH1_13default_start9_7xpr_all2rd", "x_13_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4124 "merged_parser_gen.cpp"
    break;

  case 275: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '4'  */
#line 1590 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_14IH1_13default_start9_7xpr_all2rd", "x_14", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x14"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4135 "merged_parser_gen.cpp"
    break;

  case 276: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '4'  */
#line 1597 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_14_alias0IH1_13default_start9_7xpr_all2rd", "x_14_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4146 "merged_parser_gen.cpp"
    break;

  case 277: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '5'  */
#line 1604 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_15IH1_13default_start9_7xpr_all2rd", "x_15", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x15"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4157 "merged_parser_gen.cpp"
    break;

  case 278: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '5'  */
#line 1611 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_15_alias0IH1_13default_start9_7xpr_all2rd", "x_15_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4168 "merged_parser_gen.cpp"
    break;

  case 279: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '6'  */
#line 1618 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_16IH1_13default_start9_7xpr_all2rd", "x_16", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x16"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4179 "merged_parser_gen.cpp"
    break;

  case 280: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '6'  */
#line 1625 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_16_alias0IH1_13default_start9_7xpr_all2rd", "x_16_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4190 "merged_parser_gen.cpp"
    break;

  case 281: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '7'  */
#line 1632 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_17IH1_13default_start9_7xpr_all2rd", "x_17", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x17"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4201 "merged_parser_gen.cpp"
    break;

  case 282: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "a" '7'  */
#line 1639 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_17_alias0IH1_13default_start9_7xpr_all2rd", "x_17_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4212 "merged_parser_gen.cpp"
    break;

  case 283: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '8'  */
#line 1646 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_18IH1_13default_start9_7xpr_all2rd", "x_18", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x18"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4223 "merged_parser_gen.cpp"
    break;

  case 284: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '2'  */
#line 1653 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_18_alias0IH1_13default_start9_7xpr_all2rd", "x_18_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4234 "merged_parser_gen.cpp"
    break;

  case 285: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '1' '9'  */
#line 1660 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_19IH1_13default_start9_7xpr_all2rd", "x_19", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x19"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4245 "merged_parser_gen.cpp"
    break;

  case 286: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '3'  */
#line 1667 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_19_alias0IH1_13default_start9_7xpr_all2rd", "x_19_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4256 "merged_parser_gen.cpp"
    break;

  case 287: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '0'  */
#line 1674 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_20IH1_13default_start9_7xpr_all2rd", "x_20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x20"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4267 "merged_parser_gen.cpp"
    break;

  case 288: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '4'  */
#line 1681 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_20_alias0IH1_13default_start9_7xpr_all2rd", "x_20_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4278 "merged_parser_gen.cpp"
    break;

  case 289: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '1'  */
#line 1688 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_21IH1_13default_start9_7xpr_all2rd", "x_21", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x21"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4289 "merged_parser_gen.cpp"
    break;

  case 290: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '5'  */
#line 1695 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_21_alias0IH1_13default_start9_7xpr_all2rd", "x_21_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4300 "merged_parser_gen.cpp"
    break;

  case 291: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '2'  */
#line 1702 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_22IH1_13default_start9_7xpr_all2rd", "x_22", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x22"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4311 "merged_parser_gen.cpp"
    break;

  case 292: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '6'  */
#line 1709 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_22_alias0IH1_13default_start9_7xpr_all2rd", "x_22_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4322 "merged_parser_gen.cpp"
    break;

  case 293: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '3'  */
#line 1716 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_23IH1_13default_start9_7xpr_all2rd", "x_23", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x23"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4333 "merged_parser_gen.cpp"
    break;

  case 294: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '7'  */
#line 1723 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_23_alias0IH1_13default_start9_7xpr_all2rd", "x_23_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4344 "merged_parser_gen.cpp"
    break;

  case 295: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '4'  */
#line 1730 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_24IH1_13default_start9_7xpr_all2rd", "x_24", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x24"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4355 "merged_parser_gen.cpp"
    break;

  case 296: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '8'  */
#line 1737 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_24_alias0IH1_13default_start9_7xpr_all2rd", "x_24_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s8"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4366 "merged_parser_gen.cpp"
    break;

  case 297: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '5'  */
#line 1744 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_25IH1_13default_start9_7xpr_all2rd", "x_25", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x25"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4377 "merged_parser_gen.cpp"
    break;

  case 298: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '9'  */
#line 1751 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_25_alias0IH1_13default_start9_7xpr_all2rd", "x_25_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s9"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4388 "merged_parser_gen.cpp"
    break;

  case 299: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '6'  */
#line 1758 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_26IH1_13default_start9_7xpr_all2rd", "x_26", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x26"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4399 "merged_parser_gen.cpp"
    break;

  case 300: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '1' '0'  */
#line 1765 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_26_alias0IH1_13default_start9_7xpr_all2rd", "x_26_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "s10"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4410 "merged_parser_gen.cpp"
    break;

  case 301: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '7'  */
#line 1772 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_27IH1_13default_start9_7xpr_all2rd", "x_27", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x27"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4421 "merged_parser_gen.cpp"
    break;

  case 302: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "s" '1' '1'  */
#line 1779 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_27_alias0IH1_13default_start9_7xpr_all2rd", "x_27_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "s11"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4432 "merged_parser_gen.cpp"
    break;

  case 303: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '8'  */
#line 1786 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_28IH1_13default_start9_7xpr_all2rd", "x_28", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x28"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4443 "merged_parser_gen.cpp"
    break;

  case 304: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" '3'  */
#line 1793 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_28_alias0IH1_13default_start9_7xpr_all2rd", "x_28_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4454 "merged_parser_gen.cpp"
    break;

  case 305: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '2' '9'  */
#line 1800 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_29IH1_13default_start9_7xpr_all2rd", "x_29", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x29"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4465 "merged_parser_gen.cpp"
    break;

  case 306: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" '4'  */
#line 1807 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_29_alias0IH1_13default_start9_7xpr_all2rd", "x_29_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4476 "merged_parser_gen.cpp"
    break;

  case 307: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '3' '0'  */
#line 1814 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_30IH1_13default_start9_7xpr_all2rd", "x_30", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x30"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4487 "merged_parser_gen.cpp"
    break;

  case 308: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" '5'  */
#line 1821 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_30_alias0IH1_13default_start9_7xpr_all2rd", "x_30_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4498 "merged_parser_gen.cpp"
    break;

  case 309: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "x" '3' '1'  */
#line 1828 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_31IH1_13default_start9_7xpr_all2rd", "x_31", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x31"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4509 "merged_parser_gen.cpp"
    break;

  case 310: /* MI11xpr_generalIH1_13default_start9_7xpr_all2rd: "t" '6'  */
#line 1835 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all2rd", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_31_alias0IH1_13default_start9_7xpr_all2rd", "x_31_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4520 "merged_parser_gen.cpp"
    break;

  case 311: /* MI7xpr_allIH1_13default_start9_7xpr_all3rs1: MI11xpr_generalIH1_13default_start9_7xpr_all3rs1  */
#line 1845 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all3rs1", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 4529 "merged_parser_gen.cpp"
    break;

  case 312: /* MI7xpr_allIH1_13default_start9_7xpr_all3rs1: "x" '0'  */
#line 1850 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all3rs1", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_0IH1_13default_start9_7xpr_all3rs1", "x_0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4540 "merged_parser_gen.cpp"
    break;

  case 313: /* MI7xpr_allIH1_13default_start9_7xpr_all3rs1: "z" "e" "r" "o"  */
#line 1857 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all3rs1", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI9x_0_aliasIH1_13default_start9_7xpr_all3rs1", "x_0_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "zero"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4551 "merged_parser_gen.cpp"
    break;

  case 314: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1'  */
#line 1867 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_1IH1_13default_start9_7xpr_all3rs1", "x_1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4562 "merged_parser_gen.cpp"
    break;

  case 315: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "r" "a"  */
#line 1874 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_1_alias0IH1_13default_start9_7xpr_all3rs1", "x_1_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "ra"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4573 "merged_parser_gen.cpp"
    break;

  case 316: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2'  */
#line 1881 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_2IH1_13default_start9_7xpr_all3rs1", "x_2", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4584 "merged_parser_gen.cpp"
    break;

  case 317: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" "p"  */
#line 1888 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_2_alias0IH1_13default_start9_7xpr_all3rs1", "x_2_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "sp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4595 "merged_parser_gen.cpp"
    break;

  case 318: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '3'  */
#line 1895 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_3IH1_13default_start9_7xpr_all3rs1", "x_3", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4606 "merged_parser_gen.cpp"
    break;

  case 319: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "g" "p"  */
#line 1902 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_3_alias0IH1_13default_start9_7xpr_all3rs1", "x_3_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "gp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4617 "merged_parser_gen.cpp"
    break;

  case 320: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '4'  */
#line 1909 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_4IH1_13default_start9_7xpr_all3rs1", "x_4", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4628 "merged_parser_gen.cpp"
    break;

  case 321: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" "p"  */
#line 1916 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_4_alias0IH1_13default_start9_7xpr_all3rs1", "x_4_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "tp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4639 "merged_parser_gen.cpp"
    break;

  case 322: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '5'  */
#line 1923 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_5IH1_13default_start9_7xpr_all3rs1", "x_5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4650 "merged_parser_gen.cpp"
    break;

  case 323: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" '0'  */
#line 1930 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_5_alias0IH1_13default_start9_7xpr_all3rs1", "x_5_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4661 "merged_parser_gen.cpp"
    break;

  case 324: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '6'  */
#line 1937 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_6IH1_13default_start9_7xpr_all3rs1", "x_6", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4672 "merged_parser_gen.cpp"
    break;

  case 325: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" '1'  */
#line 1944 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_6_alias0IH1_13default_start9_7xpr_all3rs1", "x_6_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4683 "merged_parser_gen.cpp"
    break;

  case 326: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '7'  */
#line 1951 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_7IH1_13default_start9_7xpr_all3rs1", "x_7", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4694 "merged_parser_gen.cpp"
    break;

  case 327: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" '2'  */
#line 1958 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_7_alias0IH1_13default_start9_7xpr_all3rs1", "x_7_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4705 "merged_parser_gen.cpp"
    break;

  case 328: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '8'  */
#line 1965 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_8IH1_13default_start9_7xpr_all3rs1", "x_8", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x8"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4716 "merged_parser_gen.cpp"
    break;

  case 329: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "f" "p"  */
#line 1972 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_8_alias0IH1_13default_start9_7xpr_all3rs1", "x_8_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "fp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4727 "merged_parser_gen.cpp"
    break;

  case 330: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '0'  */
#line 1979 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_8_alias1IH1_13default_start9_7xpr_all3rs1", "x_8_alias1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4738 "merged_parser_gen.cpp"
    break;

  case 331: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '9'  */
#line 1986 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_9IH1_13default_start9_7xpr_all3rs1", "x_9", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x9"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4749 "merged_parser_gen.cpp"
    break;

  case 332: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '1'  */
#line 1993 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_9_alias0IH1_13default_start9_7xpr_all3rs1", "x_9_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4760 "merged_parser_gen.cpp"
    break;

  case 333: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '0'  */
#line 2000 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_10IH1_13default_start9_7xpr_all3rs1", "x_10", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x10"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4771 "merged_parser_gen.cpp"
    break;

  case 334: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '0'  */
#line 2007 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_10_alias0IH1_13default_start9_7xpr_all3rs1", "x_10_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4782 "merged_parser_gen.cpp"
    break;

  case 335: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '1'  */
#line 2014 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_11IH1_13default_start9_7xpr_all3rs1", "x_11", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x11"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4793 "merged_parser_gen.cpp"
    break;

  case 336: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '1'  */
#line 2021 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_11_alias0IH1_13default_start9_7xpr_all3rs1", "x_11_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4804 "merged_parser_gen.cpp"
    break;

  case 337: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '2'  */
#line 2028 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_12IH1_13default_start9_7xpr_all3rs1", "x_12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x12"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4815 "merged_parser_gen.cpp"
    break;

  case 338: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '2'  */
#line 2035 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_12_alias0IH1_13default_start9_7xpr_all3rs1", "x_12_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4826 "merged_parser_gen.cpp"
    break;

  case 339: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '3'  */
#line 2042 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_13IH1_13default_start9_7xpr_all3rs1", "x_13", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x13"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4837 "merged_parser_gen.cpp"
    break;

  case 340: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '3'  */
#line 2049 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_13_alias0IH1_13default_start9_7xpr_all3rs1", "x_13_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4848 "merged_parser_gen.cpp"
    break;

  case 341: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '4'  */
#line 2056 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_14IH1_13default_start9_7xpr_all3rs1", "x_14", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x14"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4859 "merged_parser_gen.cpp"
    break;

  case 342: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '4'  */
#line 2063 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_14_alias0IH1_13default_start9_7xpr_all3rs1", "x_14_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4870 "merged_parser_gen.cpp"
    break;

  case 343: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '5'  */
#line 2070 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_15IH1_13default_start9_7xpr_all3rs1", "x_15", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x15"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4881 "merged_parser_gen.cpp"
    break;

  case 344: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '5'  */
#line 2077 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_15_alias0IH1_13default_start9_7xpr_all3rs1", "x_15_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4892 "merged_parser_gen.cpp"
    break;

  case 345: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '6'  */
#line 2084 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_16IH1_13default_start9_7xpr_all3rs1", "x_16", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x16"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4903 "merged_parser_gen.cpp"
    break;

  case 346: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '6'  */
#line 2091 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_16_alias0IH1_13default_start9_7xpr_all3rs1", "x_16_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4914 "merged_parser_gen.cpp"
    break;

  case 347: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '7'  */
#line 2098 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_17IH1_13default_start9_7xpr_all3rs1", "x_17", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x17"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4925 "merged_parser_gen.cpp"
    break;

  case 348: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "a" '7'  */
#line 2105 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_17_alias0IH1_13default_start9_7xpr_all3rs1", "x_17_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4936 "merged_parser_gen.cpp"
    break;

  case 349: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '8'  */
#line 2112 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_18IH1_13default_start9_7xpr_all3rs1", "x_18", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x18"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4947 "merged_parser_gen.cpp"
    break;

  case 350: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '2'  */
#line 2119 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_18_alias0IH1_13default_start9_7xpr_all3rs1", "x_18_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4958 "merged_parser_gen.cpp"
    break;

  case 351: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '1' '9'  */
#line 2126 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_19IH1_13default_start9_7xpr_all3rs1", "x_19", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x19"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4969 "merged_parser_gen.cpp"
    break;

  case 352: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '3'  */
#line 2133 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_19_alias0IH1_13default_start9_7xpr_all3rs1", "x_19_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4980 "merged_parser_gen.cpp"
    break;

  case 353: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '0'  */
#line 2140 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_20IH1_13default_start9_7xpr_all3rs1", "x_20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x20"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 4991 "merged_parser_gen.cpp"
    break;

  case 354: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '4'  */
#line 2147 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_20_alias0IH1_13default_start9_7xpr_all3rs1", "x_20_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5002 "merged_parser_gen.cpp"
    break;

  case 355: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '1'  */
#line 2154 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_21IH1_13default_start9_7xpr_all3rs1", "x_21", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x21"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5013 "merged_parser_gen.cpp"
    break;

  case 356: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '5'  */
#line 2161 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_21_alias0IH1_13default_start9_7xpr_all3rs1", "x_21_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5024 "merged_parser_gen.cpp"
    break;

  case 357: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '2'  */
#line 2168 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_22IH1_13default_start9_7xpr_all3rs1", "x_22", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x22"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5035 "merged_parser_gen.cpp"
    break;

  case 358: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '6'  */
#line 2175 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_22_alias0IH1_13default_start9_7xpr_all3rs1", "x_22_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5046 "merged_parser_gen.cpp"
    break;

  case 359: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '3'  */
#line 2182 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_23IH1_13default_start9_7xpr_all3rs1", "x_23", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x23"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5057 "merged_parser_gen.cpp"
    break;

  case 360: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '7'  */
#line 2189 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_23_alias0IH1_13default_start9_7xpr_all3rs1", "x_23_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5068 "merged_parser_gen.cpp"
    break;

  case 361: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '4'  */
#line 2196 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_24IH1_13default_start9_7xpr_all3rs1", "x_24", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x24"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5079 "merged_parser_gen.cpp"
    break;

  case 362: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '8'  */
#line 2203 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_24_alias0IH1_13default_start9_7xpr_all3rs1", "x_24_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s8"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5090 "merged_parser_gen.cpp"
    break;

  case 363: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '5'  */
#line 2210 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_25IH1_13default_start9_7xpr_all3rs1", "x_25", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x25"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5101 "merged_parser_gen.cpp"
    break;

  case 364: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '9'  */
#line 2217 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_25_alias0IH1_13default_start9_7xpr_all3rs1", "x_25_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s9"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5112 "merged_parser_gen.cpp"
    break;

  case 365: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '6'  */
#line 2224 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_26IH1_13default_start9_7xpr_all3rs1", "x_26", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x26"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5123 "merged_parser_gen.cpp"
    break;

  case 366: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '1' '0'  */
#line 2231 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_26_alias0IH1_13default_start9_7xpr_all3rs1", "x_26_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "s10"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5134 "merged_parser_gen.cpp"
    break;

  case 367: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '7'  */
#line 2238 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_27IH1_13default_start9_7xpr_all3rs1", "x_27", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x27"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5145 "merged_parser_gen.cpp"
    break;

  case 368: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "s" '1' '1'  */
#line 2245 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_27_alias0IH1_13default_start9_7xpr_all3rs1", "x_27_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "s11"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5156 "merged_parser_gen.cpp"
    break;

  case 369: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '8'  */
#line 2252 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_28IH1_13default_start9_7xpr_all3rs1", "x_28", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x28"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5167 "merged_parser_gen.cpp"
    break;

  case 370: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" '3'  */
#line 2259 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_28_alias0IH1_13default_start9_7xpr_all3rs1", "x_28_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5178 "merged_parser_gen.cpp"
    break;

  case 371: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '2' '9'  */
#line 2266 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_29IH1_13default_start9_7xpr_all3rs1", "x_29", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x29"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5189 "merged_parser_gen.cpp"
    break;

  case 372: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" '4'  */
#line 2273 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_29_alias0IH1_13default_start9_7xpr_all3rs1", "x_29_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5200 "merged_parser_gen.cpp"
    break;

  case 373: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '3' '0'  */
#line 2280 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_30IH1_13default_start9_7xpr_all3rs1", "x_30", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x30"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5211 "merged_parser_gen.cpp"
    break;

  case 374: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" '5'  */
#line 2287 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_30_alias0IH1_13default_start9_7xpr_all3rs1", "x_30_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5222 "merged_parser_gen.cpp"
    break;

  case 375: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "x" '3' '1'  */
#line 2294 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_31IH1_13default_start9_7xpr_all3rs1", "x_31", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x31"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5233 "merged_parser_gen.cpp"
    break;

  case 376: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs1: "t" '6'  */
#line 2301 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs1", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_31_alias0IH1_13default_start9_7xpr_all3rs1", "x_31_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5244 "merged_parser_gen.cpp"
    break;

  case 377: /* MI7xpr_allIH1_13default_start9_7xpr_all3rs2: MI11xpr_generalIH1_13default_start9_7xpr_all3rs2  */
#line 2311 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all3rs2", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 5253 "merged_parser_gen.cpp"
    break;

  case 378: /* MI7xpr_allIH1_13default_start9_7xpr_all3rs2: "x" '0'  */
#line 2316 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all3rs2", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_0IH1_13default_start9_7xpr_all3rs2", "x_0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5264 "merged_parser_gen.cpp"
    break;

  case 379: /* MI7xpr_allIH1_13default_start9_7xpr_all3rs2: "z" "e" "r" "o"  */
#line 2323 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI7xpr_allIH1_13default_start9_7xpr_all3rs2", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI9x_0_aliasIH1_13default_start9_7xpr_all3rs2", "x_0_alias", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "zero"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5275 "merged_parser_gen.cpp"
    break;

  case 380: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1'  */
#line 2333 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_1IH1_13default_start9_7xpr_all3rs2", "x_1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5286 "merged_parser_gen.cpp"
    break;

  case 381: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "r" "a"  */
#line 2340 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_1_alias0IH1_13default_start9_7xpr_all3rs2", "x_1_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "ra"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5297 "merged_parser_gen.cpp"
    break;

  case 382: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2'  */
#line 2347 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_2IH1_13default_start9_7xpr_all3rs2", "x_2", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5308 "merged_parser_gen.cpp"
    break;

  case 383: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" "p"  */
#line 2354 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_2_alias0IH1_13default_start9_7xpr_all3rs2", "x_2_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "sp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5319 "merged_parser_gen.cpp"
    break;

  case 384: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '3'  */
#line 2361 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_3IH1_13default_start9_7xpr_all3rs2", "x_3", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5330 "merged_parser_gen.cpp"
    break;

  case 385: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "g" "p"  */
#line 2368 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_3_alias0IH1_13default_start9_7xpr_all3rs2", "x_3_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "gp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5341 "merged_parser_gen.cpp"
    break;

  case 386: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '4'  */
#line 2375 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_4IH1_13default_start9_7xpr_all3rs2", "x_4", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5352 "merged_parser_gen.cpp"
    break;

  case 387: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" "p"  */
#line 2382 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_4_alias0IH1_13default_start9_7xpr_all3rs2", "x_4_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "tp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5363 "merged_parser_gen.cpp"
    break;

  case 388: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '5'  */
#line 2389 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_5IH1_13default_start9_7xpr_all3rs2", "x_5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5374 "merged_parser_gen.cpp"
    break;

  case 389: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" '0'  */
#line 2396 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_5_alias0IH1_13default_start9_7xpr_all3rs2", "x_5_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5385 "merged_parser_gen.cpp"
    break;

  case 390: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '6'  */
#line 2403 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_6IH1_13default_start9_7xpr_all3rs2", "x_6", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5396 "merged_parser_gen.cpp"
    break;

  case 391: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" '1'  */
#line 2410 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_6_alias0IH1_13default_start9_7xpr_all3rs2", "x_6_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5407 "merged_parser_gen.cpp"
    break;

  case 392: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '7'  */
#line 2417 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_7IH1_13default_start9_7xpr_all3rs2", "x_7", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5418 "merged_parser_gen.cpp"
    break;

  case 393: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" '2'  */
#line 2424 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_7_alias0IH1_13default_start9_7xpr_all3rs2", "x_7_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5429 "merged_parser_gen.cpp"
    break;

  case 394: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '8'  */
#line 2431 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_8IH1_13default_start9_7xpr_all3rs2", "x_8", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x8"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5440 "merged_parser_gen.cpp"
    break;

  case 395: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "f" "p"  */
#line 2438 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_8_alias0IH1_13default_start9_7xpr_all3rs2", "x_8_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "fp"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5451 "merged_parser_gen.cpp"
    break;

  case 396: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '0'  */
#line 2445 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_8_alias1IH1_13default_start9_7xpr_all3rs2", "x_8_alias1", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5462 "merged_parser_gen.cpp"
    break;

  case 397: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '9'  */
#line 2452 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI3x_9IH1_13default_start9_7xpr_all3rs2", "x_9", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "x9"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5473 "merged_parser_gen.cpp"
    break;

  case 398: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '1'  */
#line 2459 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10x_9_alias0IH1_13default_start9_7xpr_all3rs2", "x_9_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5484 "merged_parser_gen.cpp"
    break;

  case 399: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '0'  */
#line 2466 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_10IH1_13default_start9_7xpr_all3rs2", "x_10", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x10"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5495 "merged_parser_gen.cpp"
    break;

  case 400: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '0'  */
#line 2473 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_10_alias0IH1_13default_start9_7xpr_all3rs2", "x_10_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a0"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5506 "merged_parser_gen.cpp"
    break;

  case 401: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '1'  */
#line 2480 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_11IH1_13default_start9_7xpr_all3rs2", "x_11", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x11"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5517 "merged_parser_gen.cpp"
    break;

  case 402: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '1'  */
#line 2487 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_11_alias0IH1_13default_start9_7xpr_all3rs2", "x_11_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a1"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5528 "merged_parser_gen.cpp"
    break;

  case 403: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '2'  */
#line 2494 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_12IH1_13default_start9_7xpr_all3rs2", "x_12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x12"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5539 "merged_parser_gen.cpp"
    break;

  case 404: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '2'  */
#line 2501 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_12_alias0IH1_13default_start9_7xpr_all3rs2", "x_12_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5550 "merged_parser_gen.cpp"
    break;

  case 405: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '3'  */
#line 2508 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_13IH1_13default_start9_7xpr_all3rs2", "x_13", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x13"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5561 "merged_parser_gen.cpp"
    break;

  case 406: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '3'  */
#line 2515 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_13_alias0IH1_13default_start9_7xpr_all3rs2", "x_13_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5572 "merged_parser_gen.cpp"
    break;

  case 407: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '4'  */
#line 2522 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_14IH1_13default_start9_7xpr_all3rs2", "x_14", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x14"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5583 "merged_parser_gen.cpp"
    break;

  case 408: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '4'  */
#line 2529 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_14_alias0IH1_13default_start9_7xpr_all3rs2", "x_14_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5594 "merged_parser_gen.cpp"
    break;

  case 409: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '5'  */
#line 2536 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_15IH1_13default_start9_7xpr_all3rs2", "x_15", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x15"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5605 "merged_parser_gen.cpp"
    break;

  case 410: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '5'  */
#line 2543 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_15_alias0IH1_13default_start9_7xpr_all3rs2", "x_15_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5616 "merged_parser_gen.cpp"
    break;

  case 411: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '6'  */
#line 2550 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_16IH1_13default_start9_7xpr_all3rs2", "x_16", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x16"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5627 "merged_parser_gen.cpp"
    break;

  case 412: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '6'  */
#line 2557 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_16_alias0IH1_13default_start9_7xpr_all3rs2", "x_16_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5638 "merged_parser_gen.cpp"
    break;

  case 413: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '7'  */
#line 2564 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_17IH1_13default_start9_7xpr_all3rs2", "x_17", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x17"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5649 "merged_parser_gen.cpp"
    break;

  case 414: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "a" '7'  */
#line 2571 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_17_alias0IH1_13default_start9_7xpr_all3rs2", "x_17_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "a7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5660 "merged_parser_gen.cpp"
    break;

  case 415: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '8'  */
#line 2578 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_18IH1_13default_start9_7xpr_all3rs2", "x_18", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x18"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5671 "merged_parser_gen.cpp"
    break;

  case 416: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '2'  */
#line 2585 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_18_alias0IH1_13default_start9_7xpr_all3rs2", "x_18_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s2"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5682 "merged_parser_gen.cpp"
    break;

  case 417: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '1' '9'  */
#line 2592 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_19IH1_13default_start9_7xpr_all3rs2", "x_19", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x19"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5693 "merged_parser_gen.cpp"
    break;

  case 418: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '3'  */
#line 2599 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_19_alias0IH1_13default_start9_7xpr_all3rs2", "x_19_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5704 "merged_parser_gen.cpp"
    break;

  case 419: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '0'  */
#line 2606 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_20IH1_13default_start9_7xpr_all3rs2", "x_20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x20"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5715 "merged_parser_gen.cpp"
    break;

  case 420: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '4'  */
#line 2613 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_20_alias0IH1_13default_start9_7xpr_all3rs2", "x_20_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5726 "merged_parser_gen.cpp"
    break;

  case 421: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '1'  */
#line 2620 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_21IH1_13default_start9_7xpr_all3rs2", "x_21", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x21"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5737 "merged_parser_gen.cpp"
    break;

  case 422: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '5'  */
#line 2627 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_21_alias0IH1_13default_start9_7xpr_all3rs2", "x_21_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5748 "merged_parser_gen.cpp"
    break;

  case 423: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '2'  */
#line 2634 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_22IH1_13default_start9_7xpr_all3rs2", "x_22", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x22"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5759 "merged_parser_gen.cpp"
    break;

  case 424: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '6'  */
#line 2641 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_22_alias0IH1_13default_start9_7xpr_all3rs2", "x_22_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5770 "merged_parser_gen.cpp"
    break;

  case 425: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '3'  */
#line 2648 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_23IH1_13default_start9_7xpr_all3rs2", "x_23", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x23"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5781 "merged_parser_gen.cpp"
    break;

  case 426: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '7'  */
#line 2655 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_23_alias0IH1_13default_start9_7xpr_all3rs2", "x_23_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s7"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5792 "merged_parser_gen.cpp"
    break;

  case 427: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '4'  */
#line 2662 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_24IH1_13default_start9_7xpr_all3rs2", "x_24", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x24"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5803 "merged_parser_gen.cpp"
    break;

  case 428: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '8'  */
#line 2669 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_24_alias0IH1_13default_start9_7xpr_all3rs2", "x_24_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s8"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5814 "merged_parser_gen.cpp"
    break;

  case 429: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '5'  */
#line 2676 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_25IH1_13default_start9_7xpr_all3rs2", "x_25", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x25"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5825 "merged_parser_gen.cpp"
    break;

  case 430: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '9'  */
#line 2683 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_25_alias0IH1_13default_start9_7xpr_all3rs2", "x_25_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "s9"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5836 "merged_parser_gen.cpp"
    break;

  case 431: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '6'  */
#line 2690 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_26IH1_13default_start9_7xpr_all3rs2", "x_26", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x26"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5847 "merged_parser_gen.cpp"
    break;

  case 432: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '1' '0'  */
#line 2697 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_26_alias0IH1_13default_start9_7xpr_all3rs2", "x_26_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "s10"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5858 "merged_parser_gen.cpp"
    break;

  case 433: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '7'  */
#line 2704 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_27IH1_13default_start9_7xpr_all3rs2", "x_27", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x27"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5869 "merged_parser_gen.cpp"
    break;

  case 434: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "s" '1' '1'  */
#line 2711 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_27_alias0IH1_13default_start9_7xpr_all3rs2", "x_27_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "s11"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5880 "merged_parser_gen.cpp"
    break;

  case 435: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '8'  */
#line 2718 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_28IH1_13default_start9_7xpr_all3rs2", "x_28", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x28"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5891 "merged_parser_gen.cpp"
    break;

  case 436: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" '3'  */
#line 2725 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_28_alias0IH1_13default_start9_7xpr_all3rs2", "x_28_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t3"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5902 "merged_parser_gen.cpp"
    break;

  case 437: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '2' '9'  */
#line 2732 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_29IH1_13default_start9_7xpr_all3rs2", "x_29", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x29"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5913 "merged_parser_gen.cpp"
    break;

  case 438: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" '4'  */
#line 2739 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_29_alias0IH1_13default_start9_7xpr_all3rs2", "x_29_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t4"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5924 "merged_parser_gen.cpp"
    break;

  case 439: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '3' '0'  */
#line 2746 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_30IH1_13default_start9_7xpr_all3rs2", "x_30", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x30"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5935 "merged_parser_gen.cpp"
    break;

  case 440: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" '5'  */
#line 2753 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_30_alias0IH1_13default_start9_7xpr_all3rs2", "x_30_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t5"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5946 "merged_parser_gen.cpp"
    break;

  case 441: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "x" '3' '1'  */
#line 2760 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI4x_31IH1_13default_start9_7xpr_all3rs2", "x_31", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "x31"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5957 "merged_parser_gen.cpp"
    break;

  case 442: /* MI11xpr_generalIH1_13default_start9_7xpr_all3rs2: "t" '6'  */
#line 2767 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI11xpr_generalIH1_13default_start9_7xpr_all3rs2", "xpr_general", 1);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11x_31_alias0IH1_13default_start9_7xpr_all3rs2", "x_31_alias0", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "t6"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5968 "merged_parser_gen.cpp"
    break;

  case 443: /* MI13i_rtype_shiftIH1_13default_start: MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' ' ' MWS Attribute  */
#line 2777 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI13i_rtype_shiftIH1_13default_start", "i_rtype_shift", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI5uimm5IH1_13default_start7_5uimm53imm", "uimm5", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI5valueIH1_13default_start7_5uimm53imm1_5uimm5", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 5, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 5989 "merged_parser_gen.cpp"
    break;

  case 444: /* MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc: "s" "l" "l" "i"  */
#line 2797 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_slliIH1_13default_start18_15opc_rtype_shift3opc", "opc_slli", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "slli"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6000 "merged_parser_gen.cpp"
    break;

  case 445: /* MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc: "s" "r" "l" "i"  */
#line 2804 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_srliIH1_13default_start18_15opc_rtype_shift3opc", "opc_srli", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "srli"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6011 "merged_parser_gen.cpp"
    break;

  case 446: /* MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc: "s" "r" "a" "i"  */
#line 2811 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_rtype_shiftIH1_13default_start18_15opc_rtype_shift3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_sraiIH1_13default_start18_15opc_rtype_shift3opc", "opc_srai", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "srai"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6022 "merged_parser_gen.cpp"
    break;

  case 447: /* MI11i_itype_aluIH1_13default_start: MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' ' ' MWS Attribute  */
#line 2821 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_itype_aluIH1_13default_start", "i_itype_alu", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6043 "merged_parser_gen.cpp"
    break;

  case 448: /* MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc: "a" "d" "d" "i"  */
#line 2841 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_addiIH1_13default_start16_13opc_itype_alu3opc", "opc_addi", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "addi"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6054 "merged_parser_gen.cpp"
    break;

  case 449: /* MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc: "s" "l" "t" "i"  */
#line 2848 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_sltiIH1_13default_start16_13opc_itype_alu3opc", "opc_slti", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "slti"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6065 "merged_parser_gen.cpp"
    break;

  case 450: /* MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc: "s" "l" "t" "i" "u"  */
#line 2855 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI9opc_sltiuIH1_13default_start16_13opc_itype_alu3opc", "opc_sltiu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), "sltiu"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6076 "merged_parser_gen.cpp"
    break;

  case 451: /* MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc: "x" "o" "r" "i"  */
#line 2862 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_xoriIH1_13default_start16_13opc_itype_alu3opc", "opc_xori", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "xori"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6087 "merged_parser_gen.cpp"
    break;

  case 452: /* MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc: "o" "r" "i"  */
#line 2869 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_oriIH1_13default_start16_13opc_itype_alu3opc", "opc_ori", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "ori"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6098 "merged_parser_gen.cpp"
    break;

  case 453: /* MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc: "a" "n" "d" "i"  */
#line 2876 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_itype_aluIH1_13default_start16_13opc_itype_alu3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_andiIH1_13default_start16_13opc_itype_alu3opc", "opc_andi", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "andi"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6109 "merged_parser_gen.cpp"
    break;

  case 454: /* MI11i_utype_opsIH1_13default_start: MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute  */
#line 2886 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_utype_opsIH1_13default_start", "i_utype_ops", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6uimm20IH1_13default_start8_6uimm203imm", "uimm20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI5valueIH1_13default_start8_6uimm203imm1_6uimm20", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 20, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6126 "merged_parser_gen.cpp"
    break;

  case 455: /* MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc: "l" "u" "i"  */
#line 2902 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_luiIH1_13default_start16_13opc_utype_ops3opc", "opc_lui", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "lui"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6137 "merged_parser_gen.cpp"
    break;

  case 456: /* MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc: "a" "u" "i" "p" "c"  */
#line 2909 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI13opc_utype_opsIH1_13default_start16_13opc_utype_ops3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI9opc_auipcIH1_13default_start16_13opc_utype_ops3opc", "opc_auipc", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), "auipc"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6148 "merged_parser_gen.cpp"
    break;

  case 457: /* MI13i_jtype_jlinkIH1_13default_start: MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute  */
#line 2919 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI13i_jtype_jlinkIH1_13default_start", "i_jtype_jlink", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr20IH1_13default_start18_15relative_addr204simm", "relative_addr20", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr20IH1_13default_start18_15relative_addr204simm1_15relative_addr20", "addr20", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 20, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6165 "merged_parser_gen.cpp"
    break;

  case 458: /* MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc: "j" "a" "l"  */
#line 2935 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_jtype_jlinkIH1_13default_start18_15opc_jtype_jlink3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_jalIH1_13default_start18_15opc_jtype_jlink3opc", "opc_jal", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "jal"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6176 "merged_parser_gen.cpp"
    break;

  case 459: /* MI16i_btype_branchesIH1_13default_start: MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS Attribute  */
#line 2945 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI16i_btype_branchesIH1_13default_start", "i_btype_branches", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr123imm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr123imm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6197 "merged_parser_gen.cpp"
    break;

  case 460: /* MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc: "b" "e" "q"  */
#line 2965 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_beqIH1_13default_start21_18opc_btype_branches3opc", "opc_beq", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "beq"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6208 "merged_parser_gen.cpp"
    break;

  case 461: /* MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc: "b" "n" "e"  */
#line 2972 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_bneIH1_13default_start21_18opc_btype_branches3opc", "opc_bne", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "bne"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6219 "merged_parser_gen.cpp"
    break;

  case 462: /* MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc: "b" "l" "t"  */
#line 2979 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_bltIH1_13default_start21_18opc_btype_branches3opc", "opc_blt", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "blt"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6230 "merged_parser_gen.cpp"
    break;

  case 463: /* MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc: "b" "g" "e"  */
#line 2986 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_bgeIH1_13default_start21_18opc_btype_branches3opc", "opc_bge", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "bge"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6241 "merged_parser_gen.cpp"
    break;

  case 464: /* MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc: "b" "l" "t" "u"  */
#line 2993 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_bltuIH1_13default_start21_18opc_btype_branches3opc", "opc_bltu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "bltu"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6252 "merged_parser_gen.cpp"
    break;

  case 465: /* MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc: "b" "g" "e" "u"  */
#line 3000 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI18opc_btype_branchesIH1_13default_start21_18opc_btype_branches3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_bgeuIH1_13default_start21_18opc_btype_branches3opc", "opc_bgeu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "bgeu"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6263 "merged_parser_gen.cpp"
    break;

  case 466: /* MI10i_li_aliasIH1_13default_start: "l" "i" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS Attribute  */
#line 3010 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10i_li_aliasIH1_13default_start", "i_li_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), "li"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6280 "merged_parser_gen.cpp"
    break;

  case 467: /* MI10i_mv_aliasIH1_13default_start: "m" "v" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1  */
#line 3026 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10i_mv_aliasIH1_13default_start", "i_mv_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), "mv"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6295 "merged_parser_gen.cpp"
    break;

  case 468: /* MI11i_not_aliasIH1_13default_start: "n" "o" "t" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1  */
#line 3040 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_not_aliasIH1_13default_start", "i_not_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yyloc)), "not"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6310 "merged_parser_gen.cpp"
    break;

  case 469: /* MI11i_neg_aliasIH1_13default_start: "n" "e" "g" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2  */
#line 3054 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_neg_aliasIH1_13default_start", "i_neg_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yyloc)), "neg"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6325 "merged_parser_gen.cpp"
    break;

  case 470: /* MI12i_seqz_aliasIH1_13default_start: "s" "e" "q" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1  */
#line 3068 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_seqz_aliasIH1_13default_start", "i_seqz_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "seqz"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6340 "merged_parser_gen.cpp"
    break;

  case 471: /* MI12i_snez_aliasIH1_13default_start: "s" "n" "e" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2  */
#line 3082 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_snez_aliasIH1_13default_start", "i_snez_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "snez"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6355 "merged_parser_gen.cpp"
    break;

  case 472: /* MI12i_sltz_aliasIH1_13default_start: "s" "l" "t" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1  */
#line 3096 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_sltz_aliasIH1_13default_start", "i_sltz_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "sltz"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6370 "merged_parser_gen.cpp"
    break;

  case 473: /* MI12i_sgtz_aliasIH1_13default_start: "s" "g" "t" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2  */
#line 3110 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_sgtz_aliasIH1_13default_start", "i_sgtz_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "sgtz"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6385 "merged_parser_gen.cpp"
    break;

  case 474: /* MI11i_sgt_aliasIH1_13default_start: "s" "g" "t" WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1  */
#line 3124 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_sgt_aliasIH1_13default_start", "i_sgt_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yyloc)), "sgt"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6404 "merged_parser_gen.cpp"
    break;

  case 475: /* MI12i_beqz_aliasIH1_13default_start: "b" "e" "q" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3142 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_beqz_aliasIH1_13default_start", "i_beqz_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "beqz"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6421 "merged_parser_gen.cpp"
    break;

  case 476: /* MI12i_bnez_aliasIH1_13default_start: "b" "n" "e" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3158 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_bnez_aliasIH1_13default_start", "i_bnez_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "bnez"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6438 "merged_parser_gen.cpp"
    break;

  case 477: /* MI12i_blez_aliasIH1_13default_start: "b" "l" "e" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS Attribute  */
#line 3174 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_blez_aliasIH1_13default_start", "i_blez_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "blez"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6455 "merged_parser_gen.cpp"
    break;

  case 478: /* MI12i_bltz_aliasIH1_13default_start: "b" "l" "t" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3190 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_bltz_aliasIH1_13default_start", "i_bltz_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "bltz"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6472 "merged_parser_gen.cpp"
    break;

  case 479: /* MI12i_bgez_aliasIH1_13default_start: "b" "g" "e" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3206 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_bgez_aliasIH1_13default_start", "i_bgez_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "bgez"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6489 "merged_parser_gen.cpp"
    break;

  case 480: /* MI12i_bgtz_aliasIH1_13default_start: "b" "g" "t" "z" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS Attribute  */
#line 3222 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_bgtz_aliasIH1_13default_start", "i_bgtz_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), "bgtz"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6506 "merged_parser_gen.cpp"
    break;

  case 481: /* MI11i_bgt_aliasIH1_13default_start: "b" "g" "t" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3238 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_bgt_aliasIH1_13default_start", "i_bgt_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yyloc)), "bgt"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6527 "merged_parser_gen.cpp"
    break;

  case 482: /* MI11i_ble_aliasIH1_13default_start: "b" "l" "e" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3258 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI11i_ble_aliasIH1_13default_start", "i_ble_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yyloc)), "ble"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6548 "merged_parser_gen.cpp"
    break;

  case 483: /* MI12i_bgtu_aliasIH1_13default_start: "b" "g" "t" "u" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3278 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_bgtu_aliasIH1_13default_start", "i_bgtu_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yyloc)), "bgtu"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6569 "merged_parser_gen.cpp"
    break;

  case 484: /* MI12i_bleu_aliasIH1_13default_start: "b" "l" "e" "u" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ',' MWS Attribute  */
#line 3298 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI12i_bleu_aliasIH1_13default_start", "i_bleu_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yyloc)), "bleu"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI15relative_addr12IH1_13default_start18_15relative_addr124simm", "relative_addr12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), "MI6addr12IH1_13default_start18_15relative_addr124simm1_15relative_addr12", "addr12", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode), 12, 1));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6590 "merged_parser_gen.cpp"
    break;

  case 485: /* MI10i_jr_aliasIH1_13default_start: "j" "r" WS MI7xpr_allIH1_13default_start9_7xpr_all3rs1  */
#line 3318 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI10i_jr_aliasIH1_13default_start", "i_jr_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "jr"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6601 "merged_parser_gen.cpp"
    break;

  case 486: /* MI13default_start_identifier_non_identifier: MI19roots_default_start_identifier_non_identifier  */
#line 3328 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI13default_start_identifier_non_identifier", "", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6610 "merged_parser_gen.cpp"
    break;

  case 487: /* MI19roots_default_start_identifier_non_identifier: MI3isaIH1_13default_start_identifier_non_identifier  */
#line 3336 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI19roots_default_start_identifier_non_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6619 "merged_parser_gen.cpp"
    break;

  case 488: /* MI3isaIH1_13default_start_identifier_non_identifier: MI13i_itype_loadsIH1_13default_start  */
#line 3344 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6628 "merged_parser_gen.cpp"
    break;

  case 489: /* MI3isaIH1_13default_start_identifier_non_identifier: MI13i_stype_storeIH1_13default_start  */
#line 3349 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6637 "merged_parser_gen.cpp"
    break;

  case 490: /* MI3isaIH1_13default_start_identifier_non_identifier: MI13i_itype_jlregIH1_13default_start  */
#line 3354 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6646 "merged_parser_gen.cpp"
    break;

  case 491: /* MI3isaIH1_13default_start_identifier_non_identifier: MI16i_call_reg_aliasIH1_13default_start  */
#line 3359 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI3isaIH1_13default_start_identifier_non_identifier", "", 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.assemblerNode));
    }
#line 6655 "merged_parser_gen.cpp"
    break;

  case 492: /* MI13i_itype_loadsIH1_13default_start: MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')'  */
#line 3367 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI13i_itype_loadsIH1_13default_start", "i_itype_loads", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.assemblerNode), 12, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), "("));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), ")"));
    }
#line 6678 "merged_parser_gen.cpp"
    break;

  case 493: /* MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc: "l" "b"  */
#line 3389 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6opc_lbIH1_13default_start18_15opc_itype_loads3opc", "opc_lb", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "lb"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6689 "merged_parser_gen.cpp"
    break;

  case 494: /* MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc: "l" "h"  */
#line 3396 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6opc_lhIH1_13default_start18_15opc_itype_loads3opc", "opc_lh", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "lh"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6700 "merged_parser_gen.cpp"
    break;

  case 495: /* MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc: "l" "w"  */
#line 3403 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6opc_lwIH1_13default_start18_15opc_itype_loads3opc", "opc_lw", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "lw"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6711 "merged_parser_gen.cpp"
    break;

  case 496: /* MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc: "l" "b" "u"  */
#line 3410 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_lbuIH1_13default_start18_15opc_itype_loads3opc", "opc_lbu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "lbu"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6722 "merged_parser_gen.cpp"
    break;

  case 497: /* MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc: "l" "h" "u"  */
#line 3417 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_itype_loadsIH1_13default_start18_15opc_itype_loads3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI7opc_lhuIH1_13default_start18_15opc_itype_loads3opc", "opc_lhu", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc)), "lhu"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6733 "merged_parser_gen.cpp"
    break;

  case 498: /* MI13i_stype_storeIH1_13default_start: MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc WS MI7xpr_allIH1_13default_start9_7xpr_all3rs2 MWS ',' ' ' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')'  */
#line 3427 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI13i_stype_storeIH1_13default_start", "i_stype_store", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.assemblerNode), 12, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), "("));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), ")"));
    }
#line 6756 "merged_parser_gen.cpp"
    break;

  case 499: /* MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc: "s" "b"  */
#line 3449 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6opc_sbIH1_13default_start18_15opc_stype_store3opc", "opc_sb", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "sb"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6767 "merged_parser_gen.cpp"
    break;

  case 500: /* MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc: "s" "h"  */
#line 3456 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6opc_shIH1_13default_start18_15opc_stype_store3opc", "opc_sh", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "sh"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6778 "merged_parser_gen.cpp"
    break;

  case 501: /* MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc: "s" "w"  */
#line 3463 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_stype_storeIH1_13default_start18_15opc_stype_store3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6opc_swIH1_13default_start18_15opc_stype_store3opc", "opc_sw", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), "sw"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6789 "merged_parser_gen.cpp"
    break;

  case 502: /* MI13i_itype_jlregIH1_13default_start: MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc WS MI7xpr_allIH1_13default_start9_7xpr_all2rd MWS ',' ' ' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')'  */
#line 3473 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI13i_itype_jlregIH1_13default_start", "i_itype_jlreg", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-13)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval.num))); // WS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), ", "));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.assemblerNode), 12, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), "("));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), ")"));
    }
#line 6812 "merged_parser_gen.cpp"
    break;

  case 503: /* MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc: "j" "a" "l" "r"  */
#line 3495 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateSet(GetLocation((*yylocp)), "MI15opc_itype_jlregIH1_13default_start18_15opc_itype_jlreg3opc", "", 0);
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI8opc_jalrIH1_13default_start18_15opc_itype_jlreg3opc", "opc_jalr", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), "jalr"));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
    }
#line 6823 "merged_parser_gen.cpp"
    break;

  case 504: /* MI16i_call_reg_aliasIH1_13default_start: "c" "a" "l" "l" '_' "r" "e" "g" MWS ',' MWS Attribute MWS '(' MWS MI7xpr_allIH1_13default_start9_7xpr_all3rs1 MWS ')'  */
#line 3505 "merged_parser_gen.yy"
    {
        ((*yyvalp).assemblerNode) = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI16i_call_reg_aliasIH1_13default_start", "i_call_reg_alias", 0, 0);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-17)].yystate.yyloc)), "call_reg"));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yyloc)), ","));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.num))); // MWS
        ast::assembler::Node* x1 = &ast::assembler::Builder::CreateElement(GetLocation((*yylocp)), "MI6simm12IH1_13default_start8_6simm124simm", "simm12", 0, 0);
        x1->AddChild(ast::assembler::Builder::CreateAttribute(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc)), "MI5valueIH1_13default_start8_6simm124simm1_6simm12", "value", *(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.assemblerNode), 12, 0));
        ((*yyvalp).assemblerNode)->AddChild(*x1);
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc)), "("));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(*(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.assemblerNode));
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateSpace(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.num))); // MWS
        ((*yyvalp).assemblerNode)->AddChild(ast::assembler::Builder::CreateConstant(GetLocation((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc)), ")"));
    }
#line 6844 "merged_parser_gen.cpp"
    break;


#line 6848 "merged_parser_gen.cpp"

      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YY_USE (yy0);
  YY_USE (yy1);

  switch (yyn)
    {
  case 1:
    yy0->assemblerNode = MergeCode (*yy0, *yy1);
#line 6874 "merged_parser_gen.cpp"
    break;
  case 2:
    yy0->assemblerNode = MergeNode (*yy0, *yy1);
#line 6878 "merged_parser_gen.cpp"
    break;

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (parser);
  YY_USE (base);
  YY_USE (ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yy_accessing_symbol (yys->yylrState),
                &yys->yysemantics.yysval, &yys->yyloc, scanner, parser, base, ast);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YY_FPRINTF ((stderr, "%s unresolved", yymsg));
          else
            YY_FPRINTF ((stderr, "%s incomplete", yymsg));
          YY_SYMBOL_PRINT ("", yy_accessing_symbol (yys->yylrState), YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, scanner, parser, base, ast);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yysymbol_kind_t
yylhsNonterm (yyRuleNum yyrule)
{
  return YY_CAST (yysymbol_kind_t, yyr1[yyrule]);
}

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yy_state_t yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yy_state_t yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yyn) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int
yygetLRActions (yy_state_t yystate, yysymbol_kind_t yytoken, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yytoken == YYSYMBOL_YYerror)
    {
      // This is the error token.
      *yyconflicts = yyconfl;
      return 0;
    }
  else if (yyisDefaultedState (yystate)
           || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyconflicts = yyconfl;
      return -yydefact[yystate];
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return yytable[yyindex];
    }
  else
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return 0;
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_t
yyLRgotoState (yy_state_t yystate, yysymbol_kind_t yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YY_ASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates
    = YY_CAST (yyGLRState**,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yystates[0]));
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds
    = YY_CAST (yybool*,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yylookaheadNeeds[0]));
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  memset (yyset->yylookaheadNeeds,
          0,
          YY_CAST (YYSIZE_T, yyset->yycapacity) * sizeof yyset->yylookaheadNeeds[0]);
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, YYPTRDIFF_T yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yysize)
                         * sizeof yystackp->yynextFree[0]));
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS, YYTOITEMS, YYX, YYTYPE)                   \
  &((YYTOITEMS)                                                         \
    - ((YYFROMITEMS) - YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX))))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  YYPTRDIFF_T yynewSize;
  YYPTRDIFF_T yyn;
  YYPTRDIFF_T yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yynewSize)
                         * sizeof yynewItems[0]));
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*YY_REINTERPRET_CAST (yybool *, yyp0))
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YY_DPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  YYPTRDIFF_T yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            YY_DPRINTF ((stderr, "Removing dead stacks.\n"));
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            YY_DPRINTF ((stderr, "Rename stack %ld -> %ld.\n",
                        YY_CAST (long, yyi), YY_CAST (long, yyj)));
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
            YYPTRDIFF_T yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
                 YYPTRDIFF_T yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YY_ASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
  do {                                  \
    if (yydebug)                        \
      yy_reduce_print Args;             \
  } while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YY_FPRINTF ((stderr, "Reducing stack %ld by rule %d (line %d):\n",
               YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YY_FPRINTF ((stderr, "   $%d = ", yyi + 1));
      yy_symbol_print (stderr,
                       yy_accessing_symbol (yyvsp[yyi - yynrhs + 1].yystate.yylrState),
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval,
                       &(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       , scanner, parser, base, ast);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YY_FPRINTF ((stderr, " (unresolved)"));
      YY_FPRINTF ((stderr, "\n"));
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs
        = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yytops.yystates[yyk]);
      YY_ASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((yytrue, yyrhs, yyk, yyrule, scanner, parser, base, ast));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp, yylocp, scanner, parser, base, ast);
    }
  else
    {
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yyGLRState* yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      int yyi;
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((yyfalse, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule, scanner, parser, base, ast));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp, scanner, parser, base, ast);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
             yybool yyforceEval, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  YYPTRDIFF_T yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval, &yyloc, scanner, parser, base, ast);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        YY_DPRINTF ((stderr,
                     "Parse on stack %ld rejected by rule %d (line %d).\n",
                     YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule - 1]));
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yylhsNonterm (yyrule), &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval, &yyloc);
    }
  else
    {
      YYPTRDIFF_T yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yy_state_t yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YY_DPRINTF ((stderr,
                   "Reduced stack %ld by rule %d (line %d); action deferred.  "
                   "Now in state %d.\n",
                   YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule - 1],
                   yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YY_DPRINTF ((stderr, "Merging stack %ld into stack %ld.\n",
                                 YY_CAST (long, yyk), YY_CAST (long, yyi)));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static YYPTRDIFF_T
yysplitStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YY_ASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yycapacity <= yystackp->yytops.yysize)
    {
      YYPTRDIFF_T state_size = YYSIZEOF (yystackp->yytops.yystates[0]);
      YYPTRDIFF_T half_max_capacity = YYSIZE_MAXIMUM / 2 / state_size;
      if (half_max_capacity < yystackp->yytops.yycapacity)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      {
        yyGLRState** yynewStates
          = YY_CAST (yyGLRState**,
                     YYREALLOC (yystackp->yytops.yystates,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewStates[0])));
        if (yynewStates == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yystates = yynewStates;
      }

      {
        yybool* yynewLookaheadNeeds
          = YY_CAST (yybool*,
                     YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewLookaheadNeeds[0])));
        if (yynewLookaheadNeeds == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
      }
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize - 1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       0 < yyn;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  if (0 < yyn)
    {
      YY_ASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, scanner, parser, base, ast));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, scanner, parser, base, ast));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, scanner, parser, base, ast);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, scanner, parser, base, ast);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp, scanner, parser, base, ast);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, empty>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1));
  else
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, tokens %ld .. %ld>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1, YY_CAST (long, yys->yyposn + 1),
                 YY_CAST (long, yyx->yystate->yyposn)));
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YY_FPRINTF ((stderr, "%*s%s <empty>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState))));
          else
            YY_FPRINTF ((stderr, "%*s%s <tokens %ld .. %ld>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState)),
                         YY_CAST (long, yystates[yyi-1]->yyposn + 1),
                         YY_CAST (long, yystates[yyi]->yyposn)));
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, YYLTYPE *yylocp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  YY_USE (yyx0);
  YY_USE (yyx1);

#if YYDEBUG
  YY_FPRINTF ((stderr, "Ambiguity detected.\n"));
  YY_FPRINTF ((stderr, "Option 1,\n"));
  yyreportTree (yyx0, 2);
  YY_FPRINTF ((stderr, "\nOption 2,\n"));
  yyreportTree (yyx1, 2);
  YY_FPRINTF ((stderr, "\n"));
#endif

  yyerror (yylocp, scanner, parser, base, ast, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState *yys1, int yyn1,
                    yyGLRStack *yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp, scanner, parser, base, ast);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YY_ASSERT (yyoption);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (0 < yynrhs)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp, scanner, parser, base, ast);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp, scanner, parser, base, ast);
              return yyreportAmbiguity (yybest, yyp, yylocp, scanner, parser, base, ast);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YY_ASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp, scanner, parser, base, ast);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other, &yydummy, scanner, parser, base, ast);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yy_accessing_symbol (yys->yylrState),
                                &yysval, yylocp, scanner, parser, base, ast);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp, scanner, parser, base, ast);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , scanner, parser, base, ast));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk,
                   YYPTRDIFF_T yyposn, YYLTYPE *yylocp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_t yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YY_DPRINTF ((stderr, "Stack %ld Entering state %d\n",
                   YY_CAST (long, yyk), yystate));

      YY_ASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], scanner, parser, base, ast);
          if (yyflag == yyerr)
            {
              YY_DPRINTF ((stderr,
                           "Stack %ld dies "
                           "(predicate failure or explicit user error).\n",
                           YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, scanner, parser, base, ast);
          const short* yyconflicts;
          const int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;

          for (/* nothing */; *yyconflicts; yyconflicts += 1)
            {
              YYRESULTTAG yyflag;
              YYPTRDIFF_T yynewStack = yysplitStack (yystackp, yyk);
              YY_DPRINTF ((stderr, "Splitting off stack %ld from %ld.\n",
                           YY_CAST (long, yynewStack), YY_CAST (long, yyk)));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], scanner, parser, base, ast);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, yylocp, scanner, parser, base, ast));
              else if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yynewStack)));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], scanner, parser, base, ast);
              if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr,
                               "Stack %ld dies "
                               "(predicate failure or explicit user error).\n",
                               YY_CAST (long, yyk)));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYSTACKP, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  */
static int
yypcontext_expected_tokens (const yyGLRStack* yystackp,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}

static int
yy_syntax_error_arguments (const yyGLRStack* yystackp,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  yysymbol_kind_t yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.b4_lac_if([
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.], [
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.])
  */
  if (yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yystackp,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}



static void
yyreportSyntaxError (yyGLRStack* yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  if (yystackp->yyerrState != 0)
    return;
  {
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount
    = yy_syntax_error_arguments (yystackp, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    yyMemoryExhausted (yystackp);

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysz
          = yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (YYSIZE_MAXIMUM - yysize < yysz)
          yysize_overflow = yytrue;
        else
          yysize += yysz;
      }
  }

  if (!yysize_overflow)
    yymsg = YY_CAST (char *, YYMALLOC (YY_CAST (YYSIZE_T, yysize)));

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
              yyformat += 2;
            }
          else
            {
              ++yyp;
              ++yyformat;
            }
        }
      yyerror (&yylloc, scanner, parser, base, ast, yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (&yylloc, scanner, parser, base, ast, YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yysymbol_kind_t yytoken;
        int yyj;
        if (yychar == YYEOF)
          yyFail (yystackp, &yylloc, scanner, parser, base, ast, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc, scanner, parser, base, ast);
            yychar = YYEMPTY;
          }
        yytoken = yygetToken (&yychar, yystackp, scanner, parser, base, ast);
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  {
    YYPTRDIFF_T yyk;
    for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
      if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yystackp->yytops.yysize)
      yyFail (yystackp, &yylloc, scanner, parser, base, ast, YY_NULLPTR);
    for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
      yymarkStackDeleted (yystackp, yyk);
    yyremoveDeletes (yystackp);
    yycompressStack (yystackp);
  }

  /* Pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      int yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYSYMBOL_YYerror;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYSYMBOL_YYerror
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              int yyaction = yytable[yyj];
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yy_accessing_symbol (yyaction),
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yyaction,
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, scanner, parser, base, ast);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, &yylloc, scanner, parser, base, ast, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  YYPTRDIFF_T yyposn;

  YY_DPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  /* User initialization code.  */
#line 56 "merged_parser_gen.yy"
{
    // Initialize Codasip lexical analyzer
    InitializeScanner(scanner, parser, base);
    // Initialize first location object
    yylloc.initialize();
}

#line 8358 "merged_parser_gen.cpp"


  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode. */
      while (yytrue)
        {
          yy_state_t yystate = yystack.yytops.yystates[0]->yylrState;
          YY_DPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyRuleNum yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack, scanner, parser, base, ast);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, scanner, parser, base, ast));
            }
          else
            {
              yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, scanner, parser, base, ast);
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
              if (*yyconflicts)
                /* Enter nondeterministic mode.  */
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  /* Issue an error message unless the scanner already
                     did. */
                  if (yychar != YYerror)
                    yyreportSyntaxError (&yystack, scanner, parser, base, ast);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, scanner, parser, base, ast));
            }
        }

      /* Nondeterministic mode. */
      while (yytrue)
        {
          yysymbol_kind_t yytoken_to_shift;
          YYPTRDIFF_T yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, &yylloc, scanner, parser, base, ast));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, &yylloc, scanner, parser, base, ast, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, scanner, parser, base, ast));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack, scanner, parser, base, ast);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              yy_state_t yystate = yystack.yytops.yystates[yys]->yylrState;
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken_to_shift,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YY_DPRINTF ((stderr, "On stack %ld, ", YY_CAST (long, yys)));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YY_DPRINTF ((stderr, "Stack %ld now in state #%d\n",
                           YY_CAST (long, yys),
                           yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, scanner, parser, base, ast));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, scanner, parser, base, ast);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YY_ASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (&yylloc, scanner, parser, base, ast, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc, scanner, parser, base, ast);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          YYPTRDIFF_T yysize = yystack.yytops.yysize;
          YYPTRDIFF_T yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                    yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                    if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, scanner, parser, base, ast);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YY_FPRINTF ((stderr, " -> "));
    }
  YY_FPRINTF ((stderr, "%d@%ld", yys->yylrState, YY_CAST (long, yys->yyposn)));
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YY_FPRINTF ((stderr, "<null>"));
  else
    yy_yypstack (yyst);
  YY_FPRINTF ((stderr, "\n"));
}

static void
yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

static void
yypdumpstack (yyGLRStack* yystackp)
{
#define YYINDEX(YYX)                                                    \
  YY_CAST (long,                                                        \
           ((YYX)                                                       \
            ? YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX)) - yystackp->yyitems \
            : -1))

  yyGLRStackItem* yyp;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YY_FPRINTF ((stderr, "%3ld. ",
                   YY_CAST (long, yyp - yystackp->yyitems)));
      if (*YY_REINTERPRET_CAST (yybool *, yyp))
        {
          YY_ASSERT (yyp->yystate.yyisState);
          YY_ASSERT (yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Res: %d, LR State: %d, posn: %ld, pred: %ld",
                       yyp->yystate.yyresolved, yyp->yystate.yylrState,
                       YY_CAST (long, yyp->yystate.yyposn),
                       YYINDEX (yyp->yystate.yypred)));
          if (! yyp->yystate.yyresolved)
            YY_FPRINTF ((stderr, ", firstVal: %ld",
                         YYINDEX (yyp->yystate.yysemantics.yyfirstVal)));
        }
      else
        {
          YY_ASSERT (!yyp->yystate.yyisState);
          YY_ASSERT (!yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Option. rule: %d, state: %ld, next: %ld",
                       yyp->yyoption.yyrule - 1,
                       YYINDEX (yyp->yyoption.yystate),
                       YYINDEX (yyp->yyoption.yynext)));
        }
      YY_FPRINTF ((stderr, "\n"));
    }

  YY_FPRINTF ((stderr, "Tops:"));
  {
    YYPTRDIFF_T yyi;
    for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
      YY_FPRINTF ((stderr, "%ld: %ld; ", YY_CAST (long, yyi),
                   YYINDEX (yystackp->yytops.yystates[yyi])));
    YY_FPRINTF ((stderr, "\n"));
  }
#undef YYINDEX
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc




#line 3523 "merged_parser_gen.yy"



/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*---------------------------------- end of user-modifiable section ------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * \brief This function is called when syntactic error was encountered.
 * \param[in] s message
 */
int yyerror(YYLTYPE* location, yyscan_t, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*&, const char* s)
{
    llvm::SMLoc S = llvm::SMLoc::getFromPointer(base.getPointer() + location->first);
    return parser.Error(S, "Syntactic analysis error: " + std::string(s) + ".");
}

static Location GetLocation(YYLTYPE location)
{
    // Location is used as offset into LLVM buffer
    return Location(inputFileName, location.first, location.last);
}

/**
 * \brief Handle ambiguity by matching two AST. AST with less Attribute nodes is returned.
 * \param[in] x1 first AST
 * \param[in] x2 second AST
 */
ast::assembler::Node* MergeNode(YYSTYPE x1, YYSTYPE x2)
{
    return ParserUtility::MergeNode(x1.assemblerNode, x2.assemblerNode);
}

/**
 *  \brief  Handle ambiguity by matching two conditional sections.
 *  \param[in]  x1 first AST
 *  \param[in]  x2 second AST
 */
ast::assembler::Node* MergeConditionalSections(YYSTYPE x1, YYSTYPE x2)
{
    return ParserUtility::MergeConditionalSections(x1.assemblerNode, x2.assemblerNode);
}

/**
 * \brief Handle ambiguity by matching two parser commands.
 *        GenerateInstructionCommand is returned. Other is deleted.
 * \param[in] x1 first command
 * \param[in] x1 second command
 */
ast::assembler::Node* MergeCode(YYSTYPE x1, YYSTYPE x2)
{
    return ParserUtility::MergeCode(x1.assemblerNode, x2.assemblerNode);
}

