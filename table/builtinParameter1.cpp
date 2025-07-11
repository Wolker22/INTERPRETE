/*!
  \file    builtinParameter1.cpp
  \brief   Implementación de funciones de la clase BuiltinParameter1
*/

#include <iostream>

// Descomenta esta línea si necesitas usar atof en sobrecarga de operadores
// #include <stdlib.h>

#include "builtinParameter1.hpp"

// Implementación del operador de asignación
lp::BuiltinParameter1 &lp::BuiltinParameter1::operator=(const lp::BuiltinParameter1 &f)
{
  // Evitar la autoasignación
  if (this != &f)
  {
    // Copia de atributos heredados
    this->setName(f.getName());
    this->setToken(f.getToken());
    this->setNParameters(f.getNParameters());

    // Copia del atributo propio
    this->setFunction(f.getFunction());
  }

  // Devuelve una referencia al objeto actual
  return *this;
}
