/*!
  \file    logicalVariable.cpp
  \brief   Implementación de funciones de la clase LogicalVariable
*/

#include <iostream>
#include "logicalVariable.hpp"

// Operador de asignación
lp::LogicalVariable &lp::LogicalVariable::operator=(const lp::LogicalVariable &n)
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
void lp::LogicalVariable::read()
{
  std::cout << "Nombre de la variable lógica: ";
  std::cin >> this->_name;

  std::cout << "Token asociado: ";
  std::cin >> this->_token;
  std::cin.ignore();

  std::cout << "Tipo (ej. BOOL): ";
  std::cin >> this->_type;
  std::cin.ignore();

  std::cout << "Valor lógico (0 o 1): ";
  std::cin >> this->_value;
  std::cin.ignore();
}

// Escritura por salida estándar
void lp::LogicalVariable::write() const
{
  std::cout << "Nombre: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
  std::cout << "Tipo: " << this->getType() << std::endl;
  std::cout << "Valor: " << this->getValue() << std::endl;
}

namespace lp {

// Operador de entrada (>>) para leer desde flujo
std::istream &operator>>(std::istream &i, lp::LogicalVariable &n)
{
  i >> n._name;
  i >> n._token;  i.ignore();
  i >> n._type;   i.ignore();
  i >> n._value;  i.ignore();

  return i;
}

// Operador de salida (<<) para escribir en flujo
std::ostream &operator<<(std::ostream &o, lp::LogicalVariable const &n)
{
  o << n._name  << std::endl;
  o << n._token << std::endl;
  o << n._type  << std::endl;
  o << n._value << std::endl;

  return o;
}

} // namespace lp
