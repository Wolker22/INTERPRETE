%{

#include <stdlib.h>
#include <string.h>

#include "../includes/macros.hpp"
#include "../ast/ast.hpp"
#include "interpreter.tab.h"
#include "../error/error.hpp"
#define YY_DECL extern "C" int yylex(void)

#include "../table/table.hpp"
#include "../table/numericVariable.hpp"

extern lp::Table table;
extern int lineNumber;



char* process_string(const char* raw);

%}


DIGIT      [0-9] 
EXPONENT   ([eE][+-]?{DIGIT}+)

LETTER     [a-zA-Z]

NUMBER1    {DIGIT}+(\.{DIGIT}*)?{EXPONENT}?

IDENTIFIER {LETTER}({LETTER}|{DIGIT}|(_{LETTER}|{DIGIT}))* 

%x ERROR
%x COMMENT
%x STRING_MODE

%%


"(*"        { BEGIN(COMMENT); }  /* Inicio comentario multilínea */

<COMMENT>{
    "*)"    { BEGIN(INITIAL); }  /* Fin comentario multilínea */
    "\n"    { lineNumber++; }     /* Contar líneas dentro del comentario */
    .       { /* Ignorar cualquier otro carácter dentro del comentario multilínea */ }
}

"#".*       { /* Comentario de línea: ignorar desde # hasta fin de línea */ }

"'"              { BEGIN(STRING_MODE); yymore(); } /*** INICIO DE CADENA: CAMBIA A ESTADO STRING_MODE ***/

<STRING_MODE>[^\\\'\n]+    { yymore(); }          /*** CUALQUIER CARACTER EXCEPTO \ ' \n ***/

<STRING_MODE>\\n           { yymore(); }          /*** ESCAPE SALTO DE LINEA ***/

<STRING_MODE>\\t           { yymore(); }          /*** ESCAPE TABULADOR ***/

<STRING_MODE>\\\'          { yymore(); }          /*** ESCAPE COMILLA SIMPLE ***/

<STRING_MODE>"'"            {                         /*** FIN DE CADENA ***/
                        yymore();
                        BEGIN(INITIAL);

                        /*** PROCESAMIENTO DE LA CADENA (limpiar comillas y escapes) ***/

                        yylval.string = strdup(process_string(yytext));
                        return STRING;
                      }

'[^']*\n {                      /*** CADENA NO TERMINADA ***/
                        warning("UNTERMINATED STRING LITERAL", yytext);
                      }


[ \t] 	 { ; } /*** IGNORAR ESPACIOS Y TABULADORES ***/

\n        { 
             /*** INCREMENTAR CONTADOR DE LÍNEAS AL ENCONTRAR SALTO DE LÍNEA ***/
             lineNumber++; 
          }

";"       { return SEMICOLON; } /*** DEVOLVER TOKEN PUNTO Y COMA ***/
":"       { return COLON; } /*** DEVOLVER TOKEN DOS PUNTOS ***/

","       { return COMMA; } /*** DEVOLVER TOKEN COMA ***/

{NUMBER1}  {
               /*** CONVERTIR TEXTO A NÚMERO Y ASIGNARLO A YYLVAL PARA BISON ***/
               yylval.number = atof(yytext); 
               return NUMBER; 
            }



"read"           { return READ; }
"read_string"    { return READ_STRING; }
"print"          { return PRINT; }
"if"             { return IF; }
"then"           { return THEN; }
"else"           { return ELSE; }
"end_if"         { return END_IF; }
"while"          { return WHILE; }
"do"             { return DO; }
"end_while"      { return END_WHILE; }
"clear_screen"   { return CLEAR_SCREEN; }
"place"          { return PLACE; }
"repeat"        { return REPEAT; }
"until"         { return UNTIL; }
"for"           { return FOR; }
"end_for"       { return END_FOR; }
"from"          { return FROM; }
"step"          { return STEP; }
"to"            { return TO; }
"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }
"end_switch"    { return END_SWITCH; }
"true"           { yylval.string = strdup("true"); return CONSTANT; }
"false"          { yylval.string = strdup("false"); return CONSTANT; }
"or"             { return OR; }
"and"            { return AND; }
"not"            { return NOT; }
"mod"    { return MODULO; }

{IDENTIFIER}  {
                std::string identifier(yytext);
                yylval.string = strdup(yytext);

                /*** SI EL IDENTIFICADOR NO ESTÁ EN LA TABLA, SE INSERTA COMO VARIABLE INDEFINIDA ***/
                if (table.lookupSymbol(identifier) == false)
                {
                    lp::NumericVariable *n = new lp::NumericVariable(identifier, VARIABLE, UNDEFINED, 0.0);
                    table.installSymbol(n);
                    return VARIABLE;
                }
                /*** SI EXISTE, SE DEVUELVE SU TOKEN ASOCIADO ***/
                else
                {
                    lp::Symbol *s = table.getSymbol(identifier);
                    return s->getToken();
                }
           }


":"[ \t]*"="     { return ASSIGNMENT; }
"||"     { return CONCAT; }

"="      { return EQUAL; }
"<>"     { return NOT_EQUAL; }

">="     { return GREATER_OR_EQUAL; }
"<="     { return LESS_OR_EQUAL; }
">"      { return GREATER_THAN; }
"<"      { return LESS_THAN; }

"+"      { return PLUS; }
"-"      { return MINUS; }
"*"      { return MULTIPLICATION; }
"/"      { return DIVISION; }
"//"    { return INTDIV; }


"%"      { return MODULO; }
"^"      { return POWER; }

"!"      { return NOT; }

"("      { return LPAREN; }
")"      { return RPAREN; }

"{"      { return LETFCURLYBRACKET; }
"}"      { return RIGHTCURLYBRACKET; }

<<EOF>>  { return 0; }

.       { 
            /*** CUALQUIER CARACTER NO RECONOCIDO CAMBIA EL ESTADO A ERROR ***/
            BEGIN(ERROR); 
            yymore();  
        }

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&] { 
            /*** CONCATENA CARACTERES MIENTRAS PERMANECE EN ESTADO ERROR ***/
            yymore(); 
        }

<ERROR>(.|\n) { 
                /*** RETROCEDE UN CARACTER PARA NO PERDER DATOS ***/
                yyless(yyleng-1); 

                /*** IMPRIME MENSAJE DE ERROR LÉXICO CON EL TEXTO RECOGIDO ***/
                warning("LEXICAL ERROR", yytext);

                /*** VUELVE AL ESTADO INICIAL PARA CONTINUAR EL ANÁLISIS ***/
                BEGIN(INITIAL);
             }

%%
char* process_string(const char* raw)
{
    size_t len = strlen(raw);
    const char *p = raw;
    if(len >= 2 && raw[0]=='\'' && raw[len-1]=='\'')
    {
        p = raw + 1;
        len -= 2;
    }
    char *out = (char *)malloc(len + 1);
    size_t j = 0;
    for(size_t i = 0; i < len; ++i)
    {
        if(p[i]=='\\' && i+1 < len)
        {
            char c = p[++i];
            if(c=='n') out[j++]='\n';
            else if(c=='t') out[j++]='\t';
            else if(c=='\'') out[j++]='\'';
            else out[j++]=c;
        }
        else
        {
            out[j++] = p[i];
        }
    }
    out[j] = '\0';
    return out;
}

