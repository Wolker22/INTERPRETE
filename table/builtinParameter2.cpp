/*!
  \file    builtinParameter2.cpp
  \brief   Implementación de funciones de la clase BuiltinParameter2
*/

#include <iostream>

// Descomenta esta línea si necesitas usar atof en sobrecarga de operadores
// #include <stdlib.h>

#include "builtinParameter2.hpp"

// Definición del operador de asignación para BuiltinParameter2
lp::BuiltinParameter2 &lp::BuiltinParameter2::operator=(const lp::BuiltinParameter2 &f)
{
  // Evitar autoasignación
  if (this != &f)
  {
    // Copia de atributos heredados
    this->setName(f.getName());
    this->setToken(f.getToken());
    this->setNParameters(f.getNParameters());

    // Copia del atributo propio
    this->setFunction(f.getFunction());
  }

  // Devolver referencia al objeto actual
  return *this;
}
