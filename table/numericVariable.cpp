/*!
  \file    numericVariable.cpp
  \brief   Implementación de funciones de la clase NumericVariable
*/

#include <iostream>
#include "numericVariable.hpp"

// Operador de asignación
lp::NumericVariable &lp::NumericVariable::operator=(const lp::NumericVariable &n)
{
  if (this != &n)
  {
    this->setName(n.getName());
    this->setToken(n.getToken());
    this->setType(n.getType());
    this->setValue(n.getValue());
  }

  return *this;
}

// Lectura desde entrada estándar
void lp::NumericVariable::read()
{
  std::cout << "Nombre de la variable numérica: ";
  std::cin >> this->_name;

  std::cout << "Token asociado: ";
  std::cin >> this->_token;
  std::cin.ignore();

  std::cout << "Tipo (ej. NUMBER): ";
  std::cin >> this->_type;
  std::cin.ignore();

  std::cout << "Valor numérico: ";
  std::cin >> this->_value;
  std::cin.ignore();
}

// Escritura por salida estándar
void lp::NumericVariable::write() const
{
  std::cout << "Nombre: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
  std::cout << "Tipo: " << this->getType() << std::endl;
  std::cout << "Valor: " << this->getValue() << std::endl;
}

namespace lp {

// Operador de entrada (>>) desde flujo
std::istream &operator>>(std::istream &i, lp::NumericVariable &n)
{
  i >> n._name;
  i >> n._token;  i.ignore();
  i >> n._type;   i.ignore();
  i >> n._value;  i.ignore();

  return i;
}

// Operador de salida (<<) hacia flujo
std::ostream &operator<<(std::ostream &o, lp::NumericVariable const &n)
{
  o << n._name  << std::endl;
  o << n._token << std::endl;
  o << n._type  << std::endl;
  o << n._value << std::endl;

  return o;
}

} // namespace lp
