/*!
  \file    symbol.cpp
  \brief   Implementación de funciones de la clase Symbol
*/

#include "symbol.hpp"

namespace lp {

// Operador de igualdad: compara símbolos por nombre
bool Symbol::operator==(const lp::Symbol &s) const
{
  return this->getName() == s.getName();
}

// Operador menor: ordena símbolos alfabéticamente por nombre
bool Symbol::operator<(const lp::Symbol &s) const
{
  return this->getName() < s.getName();
}

} // namespace lp
