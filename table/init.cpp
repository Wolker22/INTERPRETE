/*!
  \file    init.cpp
  \brief   Inicialización de la tabla de símbolos con constantes, palabras clave y funciones predefinidas
*/

#include <list>
#include "init.hpp"
#include "table.hpp"

// Constantes
#include "numericConstant.hpp"
#include "logicalConstant.hpp"

// Palabras clave
#include "keyword.hpp"

// Funciones
#include "builtinParameter0.hpp"
#include "builtinParameter1.hpp"
#include "builtinParameter2.hpp"

// Tokens del parser
#include "../parser/interpreter.tab.h"

//////////////////////////////////////////////////////////////////////////////////

void init(lp::Table &t)
{
	int i;

	//-----------------------------------
	// Constantes numéricas
        lp::NumericConstant *n;
        for (i = 0; numericConstant[i].name.compare("") != 0; i++)
        {
                n = new lp::NumericConstant(numericConstant[i].name,
                                                                        CONSTANT,
                                                                        TYPE_NUMBER,
                                                                        numericConstant[i].value);

		t.installSymbol(n);
	}

	//-----------------------------------
	// Constantes lógicas
        lp::LogicalConstant *l;
        for (i = 0; logicalConstant[i].name.compare("") != 0; i++)
        {
                l = new lp::LogicalConstant(logicalConstant[i].name,
                                                                        CONSTANT,
                                                                        TYPE_BOOL,
                                                                        logicalConstant[i].value);

		t.installSymbol(l);
	}

       //-----------------------------------
       // Palabras clave
	lp::Keyword *k;
	for (i = 0; keyword[i].name.compare("") != 0; i++)
	{
		k = new lp::Keyword(keyword[i].name,
							keyword[i].token);

		t.installSymbol(k);
	}

	//-----------------------------------
	// Funciones predefinidas con 1 parámetro
	lp::BuiltinParameter1 *f1;
	for (i = 0; function_1[i].name.compare("") != 0; i++)
	{
		f1 = new lp::BuiltinParameter1(function_1[i].name,
									   BUILTIN,
									   1,
									   function_1[i].function);

		t.installSymbol(f1);
	}

	//-----------------------------------
	// Funciones predefinidas con 0 parámetros
	lp::BuiltinParameter0 *f0;
	for (i = 0; function_0[i].name.compare("") != 0; i++)
	{
		f0 = new lp::BuiltinParameter0(function_0[i].name,
									   BUILTIN,
									   0,
									   function_0[i].function);

		t.installSymbol(f0);
	}

	//-----------------------------------
	// Funciones predefinidas con 2 parámetros
	lp::BuiltinParameter2 *f2;
	for (i = 0; function_2[i].name.compare("") != 0; i++)
	{
		f2 = new lp::BuiltinParameter2(function_2[i].name,
									   BUILTIN,
									   2,
									   function_2[i].function);

		t.installSymbol(f2);
	}
        //-----------------------------------
        // Funciones predefinidas string con 1 parámetro (sin uso)
}
