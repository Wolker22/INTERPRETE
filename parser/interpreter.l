%{
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>

#include "../includes/macros.hpp"
#include "../ast/ast.hpp"
#include "interpreter.tab.h"
#include "../error/error.hpp"
#include "../table/table.hpp"
#include "../table/numericVariable.hpp"

extern lp::Table table;
extern int lineNumber;

%}

DIGIT     [0-9] 
LETTER    [a-zA-ZáéíóúÁÉÍÓÚñÑ]
NUMBER1   {DIGIT}+\.?
NUMBER2   {DIGIT}*\.{DIGIT}+
NUMBER3   {DIGIT}+(\.{DIGIT}+)?([eE][+-]?{DIGIT}+)?
IDENTIFIER {LETTER}({LETTER}|{DIGIT}|(_({LETTER}|{DIGIT})))*

%x ERROR COMMENT

%%

[ \t]    ;   // Ignorar espacios y tabuladores

\n       { lineNumber++; }

";"      { return SEMICOLON; }
","      { return COMMA; }
":="     { return ASSIGNACION; }
"+:="    { return ASSIGNACIONPLUS; }
"-:="    { return ASSIGNACIONMINUS; }
"--"     { return MINUSMINUS; }
"++"     { return PLUSPLUS; }
"-"      { return MINUS; }
"+"      { return PLUS; }
"*"      { return MULTIPLICATION; }
"/"      { return DIVISION; }
"//"     { return DIVISION_ENTERA; }
"^"      { return POWER; }
"||"     { return CONCATENACION; }
"="      { return EQUAL; }
">="     { return GREATER_OR_EQUAL; }
"<="     { return LESS_OR_EQUAL; }
">"      { return GREATER_THAN; }
"<"      { return LESS_THAN; }
"<>"     { return NOT_EQUAL; }
"(*"     { BEGIN(COMMENT); }
<COMMENT>"*)" { BEGIN(INITIAL); }
<COMMENT>.|\n { /* Ignorar contenido de comentarios */ }
"#".*    { /* Ignorar comentarios de línea */ }
"("      { return LPAREN; }
")"      { return RPAREN; }
":"      { return COLON; }
"?"      { return QUESTION; }

{NUMBER1}|{NUMBER2}|{NUMBER3} {
    yylval.number = atof(yytext); 
    return NUMBER; 
}

{IDENTIFIER} {
    std::string identifier(yytext);
    yylval.string = strdup(yytext);
    
    if (!table.lookupSymbol(identifier)) {
        // Usar constructor correcto para variable no inicializada
        lp::NumericVariable *var = new lp::NumericVariable(identifier, VARIABLE);
        table.installSymbol(var);
        return VARIABLE;
    }
    else {
        lp::Symbol* s = table.getSymbol(identifier);
        return s->getToken();
    }
}

\'([^'\\]|\\.)*\' {
    std::string str(yytext + 1);
    str.pop_back(); // Eliminar comilla final
    std::string processed;
    
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '\\' && i + 1 < str.size()) {
            i++;
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

<<EOF>> { 
    return 0; 
}

. {
    BEGIN(ERROR);
    yymore();  
}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&] {
    yymore(); 
}

<ERROR>(.|\n) {
    yyless(yyleng - 1);
    warning("Lexical error", yytext);
    BEGIN(INITIAL);
}

%%