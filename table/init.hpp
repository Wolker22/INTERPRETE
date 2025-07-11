/*!
  \file    init.hpp
  \brief   Prototipo de la función de inicialización de la tabla de símbolos
*/

#ifndef _INIT_HPP_
#define _INIT_HPP_

#include <math.h>        // sin, cos, atan, fabs, etc.

#include "table.hpp"
#include "../ast/ast.hpp" // Debe incluirse antes del parser

#include "../parser/interpreter.tab.h" // Tokens generados por Bison

#include "mathFunction.hpp"
#include "builtinParameter0.hpp"
#include "builtinParameter1.hpp"
#include "builtinParameter2.hpp"
/* String builtins not currently used */

//////////////////////////////////////////////////////////////
// Funciones predefinidas con 1 parámetro de tipo string
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// Constantes numéricas predefinidas (PI, E, etc.)
//////////////////////////////////////////////////////////////
static struct {
  std::string name;
  double value;
} numericConstant[] = {
  {"PI",    3.14159265358979323846},
  {"E",     2.71828182845904523536},
  {"GAMMA", 0.57721566490153286060},
  {"DEG",  57.29577951308232087680},
  {"PHI",   1.61803398874989484820},
  {"",      0} // Centinela de fin
};

//////////////////////////////////////////////////////////////
// Constantes lógicas predefinidas (true, false)
//////////////////////////////////////////////////////////////
static struct {
  std::string name;
  bool value;
} logicalConstant[] = {
  {"true",  true},
  {"false", false},
  {"",      false} // Centinela de fin
};

//////////////////////////////////////////////////////////////
// Palabras clave del lenguaje
//////////////////////////////////////////////////////////////
static struct {
  std::string name;
  int token;
} keyword[] = {
  {"print", PRINT},
  {"read",  READ},
  {"if",    IF},
  {"else",  ELSE},
  {"while", WHILE},
  {"",      0} // Centinela de fin
};

//////////////////////////////////////////////////////////////
// Funciones predefinidas con 1 parámetro
//////////////////////////////////////////////////////////////
static struct {
  std::string name;
  lp::TypePointerDoubleFunction_1 function;
} function_1[] = {
  {"sin",     sin},
  {"cos",     cos},
  {"atan",    atan},
  {"log",     Log},
  {"log10",   Log10},
  {"exp",     Exp},
  {"sqrt",    Sqrt},
  {"integer", integer},
  {"abs",     fabs},
  {"",        0} // Centinela de fin
};

//////////////////////////////////////////////////////////////
// Funciones predefinidas con 0 parámetros
//////////////////////////////////////////////////////////////
static struct {
  std::string name;
  lp::TypePointerDoubleFunction_0 function;
} function_0[] = {
  {"random", Random},
  {"",       0} // Centinela de fin
};

//////////////////////////////////////////////////////////////
// Funciones predefinidas con 2 parámetros
//////////////////////////////////////////////////////////////
static struct {
  std::string name;
  lp::TypePointerDoubleFunction_2 function;
} function_2[] = {
  {"atan2", Atan2},
  {"",      0} // Centinela de fin
};

//////////////////////////////////////////////////////////////
// Prototipo de la función de inicialización
//////////////////////////////////////////////////////////////
/*!
  \brief   Inicializa la tabla de símbolos con constantes, palabras clave y funciones predefinidas
  \param   t Referencia a la tabla de símbolos
  \return  void
*/
void init(lp::Table &t);

#endif // _INIT_HPP_
