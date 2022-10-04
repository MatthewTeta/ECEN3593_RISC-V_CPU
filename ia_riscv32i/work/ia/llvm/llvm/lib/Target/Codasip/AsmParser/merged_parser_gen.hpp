/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Skeleton interface for Bison GLR parsers in C

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

#ifndef YY_YY_MERGED_PARSER_GEN_HPP_INCLUDED
# define YY_YY_MERGED_PARSER_GEN_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 63 "merged_parser_gen.yy"

    #include "instrset/assembler/asmbasel/ast/assembler/node.h"
    #include "llvm/MC/MCParser/MCAsmParser.h"

    // reentrant parser
    typedef void* yyscan_t;
    union YYSTYPE;
    struct CODASIP_YYLTYPE
    {
      void initialize()
      {
          first_line = 1;
          first_column = 1;
          last_line = 1;
          last_column = 1;
          first = 0;
          last = 0;
      }
      // First four are useless in Codasip ASM parser for LLVM, present only for compatibility with bison code
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      // Offset of the first character in LLVM buffer
      int first;
      // Offset of the last character in LLVM buffer
      int last;
    };
    #define YYLTYPE struct CODASIP_YYLTYPE
    #define YYLTYPE_IS_DECLARED 1 /* alert the parser that we have our own definition */
    #define YYLLOC_DEFAULT(Current, Rhs, N)                                 \
        do                                                                  \
          if (N)                                                            \
            {                                                               \
              (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
              (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
              (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
              (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
              (Current).first        = YYRHSLOC (Rhs, 1).first;             \
              (Current).last         = YYRHSLOC (Rhs, N).last;              \
            }                                                               \
          else                                                              \
            {                                                               \
              (Current).first_line   = (Current).last_line   =              \
                YYRHSLOC (Rhs, 0).last_line;                                \
              (Current).first_column = (Current).last_column =              \
                YYRHSLOC (Rhs, 0).last_column;                              \
              (Current).first        = (Current).last =                     \
                YYRHSLOC (Rhs, 0).last;                                     \
            }                                                               \
        while (0)
    #define YY_DECL \
        extern "C" int yylex(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner)
    YY_DECL;
    extern "C" void InitializeScanner(yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base);
    int yyerror(YYLTYPE* loc, yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast, const char* msg);

#line 102 "merged_parser_gen.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    UNICODE_LETTER = 258,          /* "unicode letter"  */
    UNICODE_MARK = 259,            /* "unicode mark"  */
    UNICODE_NUMBER = 260,          /* "unicode number"  */
    STRING = 261,                  /* "string"  */
    A = 262,                       /* "a"  */
    B = 263,                       /* "b"  */
    C = 264,                       /* "c"  */
    D = 265,                       /* "d"  */
    E = 266,                       /* "e"  */
    F = 267,                       /* "f"  */
    G = 268,                       /* "g"  */
    H = 269,                       /* "h"  */
    I = 270,                       /* "i"  */
    J = 271,                       /* "j"  */
    K = 272,                       /* "k"  */
    L = 273,                       /* "l"  */
    M = 274,                       /* "m"  */
    N = 275,                       /* "n"  */
    O = 276,                       /* "o"  */
    P = 277,                       /* "p"  */
    Q = 278,                       /* "q"  */
    R = 279,                       /* "r"  */
    S = 280,                       /* "s"  */
    T = 281,                       /* "t"  */
    U = 282,                       /* "u"  */
    V = 283,                       /* "v"  */
    W = 284,                       /* "w"  */
    X = 285,                       /* "x"  */
    Y = 286,                       /* "y"  */
    Z = 287                        /* "z"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 148 "merged_parser_gen.yy"

    std::string* text;
    char character;
    codasip::ast::assembler::Node* assemblerNode;
    int num;

#line 158 "merged_parser_gen.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base, codasip::ast::assembler::Node*& ast);

#endif /* !YY_YY_MERGED_PARSER_GEN_HPP_INCLUDED  */
