/**
 * Codasip s.r.o.
 *
 * CONFIDENTIAL
 *
 * Copyright 2022 Codasip s.r.o.
 *
 * All Rights Reserved.
 * This file is part of the Codasip Studio product. No part of the Studio product, including this
 * file, may be use, copied, modified, or distributed except in accordance with the terms contained
 * in Codasip license agreement under which you obtained this file.
 *
 * \file
 * \date    2022-09-10
 * \author  Codasip (c) Assembler generator
 * \version 9.1.1-1255
 * \brief   Source for assembler
 */
%{
#ifdef _WIN32
#define YY_NO_UNISTD_H
#include <io.h>
#endif

#include <map>
#include <string>
#include <vector>

#include "os/filesysteml/codasip_io.h"
#include "utility/check_condition.h"
#include "utility/codasip_log.h"
#include "utility/number_cast.h"

#include "instrset/assembler/asmbasel/parser_utility.h"

codasip::fs::Path inputFileName;

extern int yydebug;
#define yyfilename inputFileName
#define RETURN(x) return(x)

using namespace codasip::assembler;

%}

%top{
    #include "merged_parser_gen.hpp"
    #define YY_EXTERN_C extern "C"
%}

%option noyywrap
%option stack
%option yylineno
%option flex bison
%option reentrant bison-bridge bison-locations
%array
%option case-insensitive
%option yyclass="CodasipLexer"
%{
    class CodasipLexer : public yyFlexLexer
    {
    public:
        CodasipLexer(llvm::MCAsmParser* parser = nullptr, const llvm::SMLoc& base = llvm::SMLoc())
          : m_Parser(parser),
            m_Base(base)
        {}
        void Initialize(llvm::MCAsmParser& parser, const llvm::SMLoc& base)
        {
            m_Parser = &parser;
            m_Base = base;
        }
        int yylex(YYSTYPE& yylval, YYLTYPE& yylloc) override;
        void yylloc_update(YYLTYPE& yylloc) override
        {
            yyFlexLexer::yylloc_update(yylloc);
            yylloc.first = matcher().first();
            yylloc.last = matcher().last();
        }

    private:
        /// LLVM MC ASM parser
        llvm::MCAsmParser* m_Parser;
        /// Base location of the LLVM buffer
        llvm::SMLoc m_Base;
        /// Determines whether EOF was already read
        bool m_EofRead = false;
    };
%}

D                   [0-9]
H                   [a-fA-F0-9]

%%

[_] { RETURN('_'); }
[$] { RETURN('$'); }
[@] { RETURN('@'); }
[#] { RETURN('#'); }
[{] { RETURN('{'); }
[}] { RETURN('}'); }
[\"] { RETURN('\"'); }
[\'] { RETURN('\''); }
[\\] { RETURN('\\'); }
[`] { RETURN('`'); }
[|] { RETURN('|'); }
[&] { RETURN('&'); }
[\\^] { RETURN('^'); }
[:] { RETURN(':'); }
[,] { RETURN(','); }
[(] { RETURN('('); }
[)] { RETURN(')'); }
[[] { RETURN('['); }
[]] { RETURN(']'); }
[.] { RETURN('.'); }
[~] { RETURN('~'); }
[-] { RETURN('-'); }
[+] { RETURN('+'); }
[*] { RETURN('*'); }
[/] { RETURN('/'); }
[%] { RETURN('%'); }
[<] { RETURN('<'); }
[>] { RETURN('>'); }
[!] { RETURN('!'); }
[?] { RETURN('?'); }
[;] { 
    BEGIN(INITIAL);
    RETURN(';');
 }
[=] { RETURN('='); }
[\n] { RETURN('\n'); }
[0] { RETURN('0'); }
[1] { RETURN('1'); }
[2] { RETURN('2'); }
[3] { RETURN('3'); }
[4] { RETURN('4'); }
[5] { RETURN('5'); }
[6] { RETURN('6'); }
[7] { RETURN('7'); }
[8] { RETURN('8'); }
[9] { RETURN('9'); }
[a] { yylval.character = yytext[0]; RETURN(A); }
[b] { yylval.character = yytext[0]; RETURN(B); }
[c] { yylval.character = yytext[0]; RETURN(C); }
[d] { yylval.character = yytext[0]; RETURN(D); }
[e] { yylval.character = yytext[0]; RETURN(E); }
[f] { yylval.character = yytext[0]; RETURN(F); }
[g] { yylval.character = yytext[0]; RETURN(G); }
[h] { yylval.character = yytext[0]; RETURN(H); }
[i] { yylval.character = yytext[0]; RETURN(I); }
[j] { yylval.character = yytext[0]; RETURN(J); }
[k] { yylval.character = yytext[0]; RETURN(K); }
[l] { yylval.character = yytext[0]; RETURN(L); }
[m] { yylval.character = yytext[0]; RETURN(M); }
[n] { yylval.character = yytext[0]; RETURN(N); }
[o] { yylval.character = yytext[0]; RETURN(O); }
[p] { yylval.character = yytext[0]; RETURN(P); }
[q] { yylval.character = yytext[0]; RETURN(Q); }
[r] { yylval.character = yytext[0]; RETURN(R); }
[s] { yylval.character = yytext[0]; RETURN(S); }
[t] { yylval.character = yytext[0]; RETURN(T); }
[u] { yylval.character = yytext[0]; RETURN(U); }
[v] { yylval.character = yytext[0]; RETURN(V); }
[w] { yylval.character = yytext[0]; RETURN(W); }
[x] { yylval.character = yytext[0]; RETURN(X); }
[y] { yylval.character = yytext[0]; RETURN(Y); }
[z] { yylval.character = yytext[0]; RETURN(Z); }
[ ] { RETURN(' '); }
[\t] { RETURN('\t'); }
[\r] { RETURN('\r'); }

\"(\\\"|\\\\|\\a|\\b|\\t|\\f|\\n|\\r|\'|\\x{H}|\\{D}|[^\"\\])*\" {
    yylval.text = new std::string(yytext);
    RETURN(STRING);
}

"#"[^\n]*
"//"[^\n]*

"/*"(.|\n)*?"*/"

<<EOF>> {
    if (m_EofRead)
    {
        RETURN(EOF);
    }
    else
    {
        m_EofRead = true;
        RETURN('\n');
    }
}

. {
    std::stringstream ss;
    ss << "Unexpected character '" << *YY_SCANNER.matcher().begin() << "' (" << std::hex << "0x" << (int)*YY_SCANNER.matcher().begin() << std::dec << ").";
    CHECK_NOT_NULL(m_Parser) << ss.str();
    llvm::SMLoc S = llvm::SMLoc::getFromPointer(m_Base.getPointer() + YY_SCANNER.matcher().first())
;    return m_Parser->Error(S, ss.str());
}

%%

void yyinit(const std::string& filename, yyscan_t scanner)
{
    yyfilename = filename;
}

void SetInputFile(FILE* fin, yyscan_t scanner)
{
    static_cast<yyscanner_t*>(scanner)->in() = fin;
}

void ScanBuffer(const char* buffer, yyscan_t scanner)
{
    yy_scan_string(buffer, scanner);
}

void DeleteCurrentBuffer(yyscan_t scanner)
{
    yy_delete_buffer(static_cast<yyscanner_t*>(scanner)->ptr_matcher(), scanner);
}
void InitializeScanner(yyscan_t scanner, llvm::MCAsmParser& parser, const llvm::SMLoc& base)
{
    static_cast<yyscanner_t*>(scanner)->Initialize(parser, base);
}
