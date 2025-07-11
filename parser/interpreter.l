/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>
#include <stdlib.h>
#include "../includes/macros.hpp"
#include "../ast/ast.hpp"
#include "interpreter.tab.h"
#include "../error/error.hpp"
#include "../table/table.hpp"
#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
extern int lineNumber; //!< External line counter
#include <string.h>
%}

DIGIT  [0-9] 
LETTER [a-zA-ZáéíóúÁÉÍÓÚñÑ]
NUMBER1 {DIGIT}+\.?
NUMBER2 {DIGIT}*\.{DIGIT}+
NUMBER3 {DIGIT}+(\.{DIGIT}+)?([eE][+-]?{DIGIT}+)? 
IDENTIFIER  {LETTER}({LETTER}|{DIGIT}|(_({LETTER}|{DIGIT})))*

%x ERROR COMMENT
%%

[ \t]   { ; }

\n      { lineNumber++; }

";"     { return SEMICOLON; }
","     { return COMMA; }

{NUMBER1}|{NUMBER2}|{NUMBER3}  {
    yylval.number = atof(yytext); 
    return NUMBER; 
}

{IDENTIFIER} {
    std::string identifier(yytext);
    yylval.string = strdup(yytext);

    if (table.lookupSymbol(identifier) == false)
    {
        lp::NumericVariable *n = new lp::NumericVariable(identifier, VARIABLE, UNDEFINED, 0.0);
        table.installSymbol(n);
        return VARIABLE;
    }
    else 
    {
        lp::Symbol *s = table.getSymbol(identifier);
        return s->getToken();
    }
}

":="        { return ASIGNACION; }
"+:="       { return ASIGNACIONPLUS; }
"-:="       { return ASIGNACIONMINUS; }
"--"        { return MINUSMINUS; }
"++"        { return PLUSPLUS; }
"-"         { return MINUS; }
"+"         { return PLUS; }
"*"         { return MULTIPLICATION; }
"/"         { return DIVISION; }
"//"        { return DIVISION_ENTERA; }
"^"         { return POWER; }
"||"        { return CONCATENACION; }
"="         { return EQUAL; }
">="        { return GREATER_OR_EQUAL; }
"<="        { return LESS_OR_EQUAL; }
">"         { return GREATER_THAN; }
"<"         { return LESS_THAN; }
"<>"        { return NOT_EQUAL; }

"(*"            { BEGIN(COMMENT); }
<COMMENT>"*)"   { BEGIN(INITIAL); }
<COMMENT>.|\n   { }

"#".*    { }

"("     { return LPAREN; }
")"     { return RPAREN; }
":"     { return COLON; }
"?"     { return QUESTION; }

\'([^'\\]|\\.)*\'  {
    std::string str(yytext + 1);
    str = str.substr(0, str.length() - 1);
    std::string processed;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '\\' && i + 1 < str.size()) {
            ++i;
            switch (str[i]) {
                case 'n': processed += '\n'; break;
                case 't': processed += '\t'; break;
                case '\'': processed += '\''; break;
                case '\\': processed += '\\'; break;
                default: processed += str[i]; break;
            }
        } else {
            processed += str[i];
        }
    }
    yylval.string = strdup(processed.c_str());
    return STRING;
}

<<EOF>> { return 0; }

. {
    BEGIN(ERROR);
    yymore();
}

<ERROR>[^ \t\n0-9a-zA-Z_+\-*/^%=()<>:;,"'\[\]{}\\|&!?¡¿~°·#]+ {
    yymore();
}

<ERROR>\n {
    lineNumber++;
    yyless(yyleng - 1);
    warning("Lexical error", yytext);
    BEGIN(INITIAL);
}

<ERROR>. {
    yyless(yyleng - 1);
    warning("Lexical error", yytext);
    BEGIN(INITIAL);
}
%%
