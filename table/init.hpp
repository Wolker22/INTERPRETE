/*!	
	\file   init.hpp
	\brief   Prototype of the function for the initialization of table of symbols
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _INIT_HPP_
#define _INIT_HPP_

// sin, cos, atan, fabs, ...
#include <math.h>

#include "table.hpp"

// IMPORTANT: This file must be before y.tab.h
#include "../ast/ast.hpp"
///////////////////////////////////////

//  interpreter.tab.h contains the number values of the tokens produced by the parser
#include "../parser/interpreter.tab.h"

///////////////////////////////////////
// NEW in example 13
#include "mathFunction.hpp"
#include "builtinParameter1.hpp"
///////////////////////////////////////

///////////////////////////////////////
// NEW in example 14
#include "builtinParameter0.hpp"
#include "builtinParameter2.hpp"
///////////////////////////////////////

/*!
  \ brief Predefined numeric constants
*/
static struct {
          std::string name ;
	      double value;
	      } numericConstant[] = {
	                    {"PI",    3.14159265358979323846},
	                    {"E",     2.71828182845904523536},
	                    {"GAMMA", 0.57721566490153286060},
	                    {"DEG",  57.29577951308232087680},
	                    {"PHI",   1.61803398874989484820},
	                    {"",      0}
	                   };

/*!
  \ brief Predefined logical constants
*/
// NEW in example 16
static struct {
          std::string name ;
	      bool value;
	      } logicalConstant[] = { 
	                    {"true", true},
	                    {"false", false},
	                    {"",      0}
	                   };


// NEW in example 12 
/*!
  \ brief Predefined keywords
*/

static struct {
          std::string name ;
	      int token;
	      } keyword[] = { 
						{"print", PRINT},
						{"read", READ},
						{"read_string", READ_STRING},
						{"if", IF}, // NEW in example 17
						{"then", THEN}, // EJERCICIO 1
						{"else", ELSE}, // NEW in example 17
						{"end_if", END_IF}, // EJERCICIO 1
						{"while", WHILE}, // NEW in example 17
						{"do", DO}, // EJERCICIO 1
						{"end_while", END_WHILE}, // EJERCICIO 1
						{"repeat", REPEAT}, // EJERCICIO 1
						{"until", UNTIL}, // EJERCICIO 1
						{"for", FOR}, // EJERCICIO 1
						{"end_for", END_FOR}, // EJERCICIO 1
						{"from", FROM}, // EJERCICIO 1
						{"step", STEP}, // EJERCICIO 1
						{"to", TO}, // EJERCICIO 1 
						{"switch", SWITCH}, // EJERCICIO 1
						{"case", CASE}, // EJERCICIO 1
						{"default", DEFAULT}, // EJERCICIO 1
						{"end_switch", END_SWITCH}, // EJERCICIO 1
						{"clear_screen", CLEAR_SCREEN_X}, // EJERCICIO 1
						{"place", PLACE_X}, // NUEVO: LOS HE TENIDO QUE LLAMAR CON UNA X AL FINAL PORQUE SI NO ENTRA EN CONFLICTO CON SU MACRO
						{"or", OR}, // EJERCICIO 1
						{"and", AND}, // EJERCICIO 1
						{"not", NOT}, // EJERCICIO 1
						{"mod", MODULO}, // EJERCICIO 1
						{"", 0}, // EJERCICIO 1
	                   };



// NEW in example 13

static struct {    /* Predefined functions names */ 
                std::string name ;
				lp::TypePointerDoubleFunction_1 function;
              } function_1 [] = {
	                   {"sin",     sin},
		               {"cos",     cos},
		               {"atan",    atan},
		               {"log",     Log},
		               {"log10",   Log10},
		               {"exp",     Exp},
		               {"sqrt",    Sqrt},
		               {"integer", integer},
		               {"abs",     fabs},   
		               {"",        0}
		              };

// NEW in example 14
static struct {   
                std::string name ;
				lp::TypePointerDoubleFunction_0 function;
              } function_0 [] = {
						{"random", Random},
		                {"",       0}
		              };


// NEW in example 14

static struct {    /* Nombres predefinidos de funciones con 2 argumentos */ 
                std::string name ;
				lp::TypePointerDoubleFunction_2 function;
              } function_2 [] = {
	                   {"atan2",   Atan2},
		               {"",       0}
		              };







/*!		
	\brief   Initialize the table of symbols
	\return  void 
*/

void init(lp::Table &t);

// End of _INIT_HPP_
#endif
