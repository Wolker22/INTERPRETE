/*!
  \file    constant.cpp
  \brief   Implementación de funciones de la clase Constant
*/

#include <iostream>
#include "constant.hpp"

// Operador de asignación
lp::Constant &lp::Constant::operator=(const lp::Constant &c)
{
  // Evitar autoasignación
  if (this != &c)
  {
    // Copiar atributos heredados
    this->setName(c.getName());
    this->setToken(c.getToken());

    // Copiar atributo propio
    this->setType(c.getType());
  }

  // Devolver referencia al objeto actual
  return *this;
}

// Lectura de los atributos desde entrada estándar
void lp::Constant::read()
{
  std::cout << "Nombre de la constante: ";
  std::cin >> this->_name;

  std::cout << "Token asociado: ";
  std::cin >> this->_token;
  std::cin.ignore(); // Ignorar salto de línea

  std::cout << "Tipo de la constante (entero, real, etc.): ";
  std::cin >> this->_type;
  std::cin.ignore(); // Ignorar salto de línea
}

// Escritura de los atributos por salida estándar
void lp::Constant::write() const
{
  std::cout << "Nombre: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
  std::cout << "Tipo: " << this->getType() << std::endl;
}
