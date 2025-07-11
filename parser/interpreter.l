/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/*********************/
/* NEW in example 4 */
/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*********************/
/* 
  NEW in example 16 
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

/********************/
/* NEW in example 3 */
#include "../error/error.hpp"
/********************/


/*********************************************/
/* NEW in example 7 */
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

/* uso de strdup */
#include <string.h>


%}


/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-ZáéíóúÁÉÍÓÚñÑ]

NUMBER1 {DIGIT}+\.?

NUMBER2 {DIGIT}*\.{DIGIT}+

/* EJERCICIO 1 */
NUMBER3 {DIGIT}+(\.{DIGIT}+)?([eE][+-]?{DIGIT}+)? 

/* EJERCICIO 1 */
IDENTIFIER  {LETTER}({LETTER}|{DIGIT}|(_({LETTER}|{DIGIT})))*


/* NEW in example 3 */
/* STATE  */
%x ERROR COMMENT

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabular */

\n      { 
			/* Line counter */
           	lineNumber++; 
	
			/* MODIFIED in example 3 */
			/* COMMENTED in example 5 */
        	/* return NEWLINE; */
        }

";"		{
			/* NEW in example 5 */
			return SEMICOLON;
		}


","		{
			/* NEW in example 14 */
			return COMMA;
		}

{NUMBER1}|{NUMBER2}|{NUMBER3}  {
									/* EJERCICIO 1 */
									/* MODIFIED in example 4 */
									/* Conversion of type and sending of the numerical value to the parser */
									yylval.number = atof(yytext); 

									return NUMBER; 
								}


{IDENTIFIER}   		 {
						 /* NEW in example 7 */
						 std::string identifier(yytext);

						/* 
                          strdup() function returns a pointer to a new string 
                          which  is a duplicate of the string yytext
                        */
						  yylval.string =  strdup(yytext);

						/* If the identifier is not in the table of symbols then it is inserted */	
						 if (table.lookupSymbol(identifier) == false)
							{
								/* 
								 The identifier is inserted into the symbol table 
								 as undefined Variable with value 0.0
								*/
								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);

								/* A pointer to the new NumericVariable is inserted into the table of symbols */
								table.installSymbol(n);

								return VARIABLE;
							}

						/* MODIFIED in example 11 */
						/* 
							If the identifier is in the table of symbols then its token is returned 
								The identifier can be a variable or a numeric constant
						*/
						else 
							{
								lp::Symbol	*s = table.getSymbol(identifier);

/*
								std::cout << "lex: "<< s->getName() 
										  << "token " << s->getToken()
  										  << std::endl; 
*/

								/*  If the identifier is in the table then its token is returned  */
								return s->getToken();
							}
                     }

":="    { return ASIGNACION;  } 	/* EJERCICIO 1 */
"+:="    { return ASIGNACIONPLUS;  } 	/* ADICIONAL */
"-:="    { return ASIGNACIONMINUS;  } 	/* ADICIONAL */


"--"	{ return MINUSMINUS;  } 	/* ADICIONAL */
"++"	{ return PLUSPLUS;   } 		/* ADICIONAL */	
"-"		{ return MINUS;  } 			/* NEW in example 3 */
"+"		{ return PLUS;   } 			/* NEW in example 3 */
"*"	    { return MULTIPLICATION; } 	/* NEW in example 3 */
"/"     { return DIVISION; } 		/* NEW in example 3 */
"//"    { return DIVISION_ENTERA; } /* EJERCICIO 1 */
"^"	    { return POWER; }			/* NEW in example 5 */


"||"	{ return CONCATENACION; }				/* EJERCICIO 1 */


"=" 	{ return EQUAL; }		/* EJERCICIO 1 */
">="	{ return GREATER_OR_EQUAL; }/* NEW in example 15 */
"<="	{ return LESS_OR_EQUAL; }	/* NEW in example 15 */
">"		{ return GREATER_THAN; }	/* NEW in example 15 */
"<"		{ return LESS_THAN; }		/* NEW in example 15 */
"<>"	{ return NOT_EQUAL; }	/* EJERCICIO 1 */


"(*"            { BEGIN(COMMENT); }
<COMMENT>"*)"   { BEGIN(INITIAL); }
<COMMENT>.|\n   { /* consumir todo hasta encontrar "*)" */ }


"#".*    { /* Comentario de una línea, ignorar */ }


"("     { return LPAREN; } 			/* NEW in example 3 */
")"	    { return RPAREN; } 			/* NEW in example 3 */


":"      { return COLON; }  /* Necesario para switch/case */
"?"		 { return QUESTION; } /*Necesario para el operador alternativa*/

\'([^'\\]|\\.)*\'  {
    // Eliminar comillas exteriores
    std::string str(yytext + 1);
    str = str.substr(0, str.length() - 1); // equivalente a pop_back()
	std::string processed;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '\\' && i + 1 < str.size()) {
            ++i;
            switch (str[i]) {
                case 'n': processed += '\n'; break; //Para el salto de linea
                case 't': processed += '\t'; break; //Para tabular
                case '\'': processed += '\''; break; //Para poder poner una comilla dentro
                case '\\': processed += '\\'; break; //Para poder poner una barra \ asi suelta
                default: processed += str[i]; break;
            }
        } else {
            processed += str[i];
        }
    }
    yylval.string = strdup(processed.c_str());
    return STRING;
}


<<EOF>> { /* The interpreter finishes when finds the end of file character */
		/*  PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of program <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  PLACE(25,1);
		*/
	  	  return 0;
	}


.								{ 	
									/* Any other character */
									/* MODIFIIED in example 3 */
									/* Change to error state */
									BEGIN(ERROR); 

									/* 
										The current value of yytext 
										will be concatenated with the next character
									*/
									yymore();  
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ /* MODIFIED in examples 5, 7, 15 */
								  /* NEW in example 3 */
								  /* 
									The current value of yytext 
									will be concatenated with the next character
								  */
									yymore(); 
								}

<ERROR>(.|\n)                { 
								/* NEW in example 3 */
								/* Rewind one position */
								yyless(yyleng-1); 

								/* Display the error message */
								warning("Lexical error", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%

