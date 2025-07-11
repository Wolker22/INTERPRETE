/*!
  \file    builtinParameter0.cpp
  \brief   Implementación de funciones de la clase BuiltinParameter0
*/

#include <iostream>

// Descomentar si se necesita usar atof en el futuro
// #include <stdlib.h>

#include "builtinParameter0.hpp"

// Definición del operador de asignación para BuiltinParameter0
lp::BuiltinParameter0 &lp::BuiltinParameter0::operator=(const lp::BuiltinParameter0 &f)
{
  // Evitar la autoasignación
  if (this != &f)
  {
    // Asignación de los atributos heredados
    this->setName(f.getName());
    this->setToken(f.getToken());
    this->setNParameters(f.getNParameters());

    // Asignación del atributo propio
    this->setFunction(f.getFunction());
  }

  // Devolver la referencia al objeto actual
  return *this;
}
