/*!
  \file    builtin.cpp
  \brief   Implementación de funciones de la clase Builtin
*/

#include <iostream>
#include "builtin.hpp"

// Operador de asignación
lp::Builtin &lp::Builtin::operator=(const lp::Builtin &b)
{
  // Evitar autoasignación
  if (this != &b)
  {
    // Copiar atributos heredados
    this->setName(b.getName());
    this->setToken(b.getToken());

    // Copiar atributo propio
    this->setNParameters(b.getNParameters());
  }

  // Devolver referencia al objeto actual
  return *this;
}

// Función para leer los datos de un objeto Builtin desde entrada estándar
void lp::Builtin::read()
{
  std::cout << "Nombre de la función predefinida: ";
  std::cin >> this->_name;

  std::cout << "Token asociado: ";
  std::cin >> this->_token;
  std::cin.ignore(); // Ignorar salto de línea

  std::cout << "Número de parámetros: ";
  std::cin >> this->_nParameters;
  std::cin.ignore(); // Ignorar salto de línea
}

// Función para mostrar los datos del objeto Builtin por salida estándar
void lp::Builtin::write() const
{
  std::cout << "Nombre: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
  std::cout << "Número de parámetros: " << this->getNParameters() << std::endl;
}
