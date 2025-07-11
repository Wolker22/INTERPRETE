/*!
  \file    logicalConstant.cpp
  \brief   Implementación de funciones de la clase LogicalConstant
*/

#include <iostream>
#include "logicalConstant.hpp"

// Operador de asignación
lp::LogicalConstant &lp::LogicalConstant::operator=(const lp::LogicalConstant &n)
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
void lp::LogicalConstant::read()
{
  std::cout << "Nombre de la constante lógica: ";
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
void lp::LogicalConstant::write() const
{
  std::cout << "Nombre: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
  std::cout << "Tipo: " << this->getType() << std::endl;
  std::cout << "Valor: " << this->getValue() << std::endl;
}

namespace lp {

// Sobrecarga del operador de entrada >>
std::istream &operator>>(std::istream &i, lp::LogicalConstant &n)
{
  i >> n._name;
  i >> n._token;  i.ignore();
  i >> n._type;   i.ignore();
  i >> n._value;  i.ignore();
  return i;
}

// Sobrecarga del operador de salida <<
std::ostream &operator<<(std::ostream &o, lp::LogicalConstant const &n)
{
  o << n._name  << std::endl;
  o << n._token << std::endl;
  o << n._type  << std::endl;
  o << n._value << std::endl;
  return o;
}

} // namespace lp
