#include "init.hpp"
#include "numericConstant.hpp"
#include "logicalConstant.hpp"
#include "keyword.hpp"
#include "builtinParameter0.hpp"
#include "builtinParameter1.hpp"
#include "builtinParameter2.hpp"

namespace lp {

// Implementaciones de funciones matemáticas personalizadas
double Log(double x) { return log(x); }
double Log10(double x) { return log10(x); }
double Exp(double x) { return exp(x); }
double Sqrt(double x) { return sqrt(x); }
double integer(double x) { return floor(x); }
double Random() { return static_cast<double>(rand()) / RAND_MAX; }
double Atan2(double x, double y) { return atan2(x, y); }

// Definición de constantes numéricas
NumericConstantDef numericConstants[] = {
    {"PI",    3.14159265358979323846},
    {"E",     2.71828182845904523536},
    {"GAMMA", 0.57721566490153286060},
    {"DEG",  57.29577951308232087680},
    {"PHI",   1.61803398874989484820},
    {"",      0}
};

// Definición de constantes lógicas
LogicalConstantDef logicalConstants[] = {
    {"true", true},
    {"false", false},
    {"", false}
};

// Definición de palabras clave
KeywordDef keywords[] = {
    {"print", PRINT},
    {"read", READ},
    {"read_string", READ_STRING},
    {"if", IF},
    {"then", THEN},
    {"else", ELSE},
    {"end_if", END_IF},
    {"while", WHILE},
    {"do", DO},
    {"end_while", END_WHILE},
    {"repeat", REPEAT},
    {"until", UNTIL},
    {"for", FOR},
    {"end_for", END_FOR},
    {"from", FROM},
    {"step", STEP},
    {"to", TO},
    {"switch", SWITCH},
    {"case", CASE},
    {"default", DEFAULT},
    {"end_switch", END_SWITCH},
    {"clear_screen", CLEAR_SCREEN},
    {"place", PLACE},
    {"or", OR},
    {"and", AND},
    {"not", NOT},
    {"mod", MODULO},
    {"", 0}
};

// Definición de funciones con 0 parámetros
Function0Def functions0[] = {
    {"random", Random},
    {"", nullptr}
};

// Definición de funciones con 1 parámetro
Function1Def functions1[] = {
    {"sin", sin},
    {"cos", cos},
    {"atan", atan},
    {"log", Log},
    {"log10", Log10},
    {"exp", Exp},
    {"sqrt", Sqrt},
    {"integer", integer},
    {"abs", fabs},
    {"", nullptr}
};

// Definición de funciones con 2 parámetros
Function2Def functions2[] = {
    {"atan2", Atan2},
    {"", nullptr}
};

void init(lp::Table &t) {
    // Instalar constantes numéricas
    for (int i = 0; !numericConstants[i].name.empty(); i++) {
        t.installSymbol(new NumericConstant(
            numericConstants[i].name,
            CONSTANT,
            NUMBER,
            numericConstants[i].value
        ));
    }

    // Instalar constantes lógicas
    for (int i = 0; !logicalConstants[i].name.empty(); i++) {
        t.installSymbol(new LogicalConstant(
            logicalConstants[i].name,
            CONSTANT,
            BOOL,
            logicalConstants[i].value
        ));
    }

    // Instalar palabras clave
    for (int i = 0; !keywords[i].name.empty(); i++) {
        t.installSymbol(new Keyword(
            keywords[i].name,
            keywords[i].token
        ));
    }

    // Instalar funciones con 0 parámetros
    for (int i = 0; !functions0[i].name.empty(); i++) {
        t.installSymbol(new BuiltinParameter0(
            functions0[i].name,
            BUILTIN,
            0,
            functions0[i].function
        ));
    }

    // Instalar funciones con 1 parámetro
    for (int i = 0; !functions1[i].name.empty(); i++) {
        t.installSymbol(new BuiltinParameter1(
            functions1[i].name,
            BUILTIN,
            1,
            functions1[i].function
        ));
    }

    // Instalar funciones con 2 parámetros
    for (int i = 0; !functions2[i].name.empty(); i++) {
        t.installSymbol(new BuiltinParameter2(
            functions2[i].name,
            BUILTIN,
            2,
            functions2[i].function
        ));
    }
}

} // namespace lp