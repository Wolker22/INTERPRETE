#ifndef _INIT_HPP_
#define _INIT_HPP_

#include <string>
#include <cmath>
#include "table.hpp"
#include "../ast/ast.hpp"
#include "../parser/interpreter.tab.h"

namespace lp {

// Tipos de punteros a funciones compatibles
typedef double (*TypePointerDoubleFunction_0)();
typedef double (*TypePointerDoubleFunction_1)(double);
typedef double (*TypePointerDoubleFunction_2)(double, double);

// Declaraciones de funciones matemáticas personalizadas
double Log(double x);
double Log10(double x);
double Exp(double x);
double Sqrt(double x);
double integer(double x);
double Random();
double Atan2(double x, double y);

// Estructuras para constantes y funciones predefinidas
struct NumericConstantDef {
    std::string name;
    double value;
};

struct LogicalConstantDef {
    std::string name;
    bool value;
};

struct KeywordDef {
    std::string name;
    int token;
};

struct Function0Def {
    std::string name;
    TypePointerDoubleFunction_0 function;
};

struct Function1Def {
    std::string name;
    TypePointerDoubleFunction_1 function;
};

struct Function2Def {
    std::string name;
    TypePointerDoubleFunction_2 function;
};

// Arreglos predefinidos
extern NumericConstantDef numericConstants[];
extern LogicalConstantDef logicalConstants[];
extern KeywordDef keywords[];
extern Function0Def functions0[];
extern Function1Def functions1[];
extern Function2Def functions2[];

// Función de inicialización
void init(lp::Table &t);

} // namespace lp

#endif