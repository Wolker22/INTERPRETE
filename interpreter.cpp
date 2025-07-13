/*!
  \file interpreter.cpp
  \brief Main program
*/

/*!
 \mainpage Flex and Bison: example 17
 \author   
 \date     2018 - 4 - 26
 \version  1.0
 \note Novelties
  + AST: intermediate code
  + New statements: if, while, block
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

// Definición global de `begin` para manejo de errores
jmp_buf begin; //!< Enables recovery of runtime errors

// Contador de línea y nombre del programa
int lineNumber = 1; //!< Line counter
std::string progname; //!< Program name

// Control del modo interactivo
bool interactiveMode; //!< Control the interactive mode of execution of the interpreter
int control = 0; //!< To control the interactive mode in "if" and "while" sentences

// AST (debe ir antes del parser)
#include "ast/ast.hpp"
lp::AST *root; //!< Root of the abstract syntax tree AST

// Parser generado por Bison
#include "./parser/interpreter.tab.h"

// Inicialización de la tabla de símbolos
#include "table/init.hpp"
#include "table/table.hpp"
lp::Table table; //!< Table of Symbols

// Manejo de errores
#include "error/error.hpp"

// Entrada de análisis léxico
extern FILE *yyin; //!< Input for the lexer
extern int yy_flex_debug;
extern int yydebug;

//! \name Main program
/*!
  \brief  Main function
  \param  argc: number of command line parameters
  \param  argv: values of command line parameters
  \return int
  \sa     yyparse, yylex
*/
int main(int argc, char *argv[])
{
  // Desactivar debug del parser y lexer
  yydebug = 0;
  yy_flex_debug = 0;

  // Configurar entrada: archivo o teclado
  if (argc == 2)
  {
    yyin = fopen(argv[1], "r");
    interactiveMode = false;
  }
  else
  {
    interactiveMode = true;
  }

  // Guardar nombre del programa
  progname = argv[0];

  // Precisión de decimales
  std::cout.precision(7);

  // Inicializar tabla de símbolos
  init(table);

  // Establecer punto de recuperación por errores en tiempo de ejecución
  setjmp(begin);

  // Capturar errores de coma flotante
  signal(SIGFPE, fpecatch);

  // Iniciar análisis sintáctico
  yyparse();

  // Evaluar AST si no es interactivo
  if (!interactiveMode)
  {
    root->evaluate();
  }

  return 0;
}
