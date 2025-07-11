/*!
  \file    variable.cpp
  \brief   Implementación de los métodos de la clase Variable
*/

#include <iostream>
#include "variable.hpp"

// Operador de asignación
lp::Variable &lp::Variable::operator=(const lp::Variable &v)
{
  if (this != &v)
  {
    this->setName(v.getName());
    this->setToken(v.getToken());
    this->setType(v.getType());
  }
  return *this;
}

// Lectura de atributos desde consola
void lp::Variable::read()
{
  std::cout << "Nombre de la variable: ";
  std::cin >> this->_name;

  std::cout << "Token de la variable: ";
  std::cin >> this->_token;
  std::cin.ignore(); // Consumir '\n'

  std::cout << "Tipo de la variable: ";
  std::cin >> this->_type;
  std::cin.ignore(); // Consumir '\n'
}

// Escritura de atributos en consola
void lp::Variable::write() const
{
  std::cout << "Nombre: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
  std::cout << "Tipo: " << this->getType() << std::endl;
}
