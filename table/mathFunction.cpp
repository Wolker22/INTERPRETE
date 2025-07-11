/*!
  \file    mathFunction.cpp
  \brief   Implementación de funciones matemáticas con control de errores
*/

#include <iostream>
#include <string>
#include <cstdlib>   // rand, srand, RAND_MAX
#include <ctime>     // time
#include <cmath>     // funciones matemáticas: log, sqrt, atan, etc.

#include "mathFunction.hpp"
#include "../error/error.hpp"  // Función errcheck

// Logaritmo neperiano con control de errores
double Log(double x)
{
  std::string msg("Logaritmo neperiano");
  return errcheck(log(x), msg);
}

// Logaritmo en base 10 con control de errores
double Log10(double x)
{
  std::string msg("Logaritmo decimal");
  return errcheck(log10(x), msg);
}

// Exponencial con control de errores
double Exp(double x)
{
  std::string msg("Exponencial");
  return errcheck(exp(x), msg);
}

// Raíz cuadrada con control de errores
double Sqrt(double x)
{
  std::string msg("Raíz cuadrada");
  return errcheck(sqrt(x), msg);
}

// Parte entera de un número (truncamiento)
double integer(double x)
{
  return static_cast<double>(static_cast<long>(x));
}

// Generador de número aleatorio entre 0 y 1
double Random()
{
  srand(time(NULL)); // Inicializa semilla (puede repetirse si se llama rápidamente)
  return static_cast<double>(rand()) / RAND_MAX;
}

// Arcotangente del cociente y/x (versión simplificada)
double Atan2(double x, double y)
{
  return errcheck(atan(x / y), "Arcotangente del cociente (atan2 simplificado)");
}
