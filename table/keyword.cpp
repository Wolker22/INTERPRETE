/*!
  \file    keyword.cpp
  \brief   Implementación de funciones de la clase Keyword
*/

#include <iostream>
#include "keyword.hpp"

// Operador de asignación
lp::Keyword &lp::Keyword::operator=(const lp::Keyword &k)
{
  // Evitar autoasignación
  if (this != &k)
  {
    // Copiar atributos heredados
    this->setName(k.getName());
    this->setToken(k.getToken());
  }

  // Devolver referencia al objeto actual
  return *this;
}

// Leer atributos desde la entrada estándar
void lp::Keyword::read()
{
  std::cout << "Nombre de la palabra clave: ";
  std::cin >> this->_name;

  std::cout << "Token asociado: ";
  std::cin >> this->_token;
  std::cin.ignore(); // Ignorar salto de línea
}

// Escribir atributos por salida estándar
void lp::Keyword::write() const
{
  std::cout << "Nombre: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
}
