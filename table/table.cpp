/*!
  \file    table.cpp
  \brief   Implementación de los métodos de la clase Table
*/

#include <map>
#include <cassert>
#include <iostream>
#include "table.hpp"

namespace lp {

// Comprueba si un símbolo existe en la tabla
bool Table::lookupSymbol(const std::string &name) const
{
  return this->_table.find(name) != this->_table.end();
}

// Devuelve un puntero al símbolo asociado a un nombre
Symbol *Table::getSymbol(const std::string &name)
{
#ifndef NDEBUG
  assert(this->lookupSymbol(name) == true); // Precondición
#endif
  return this->_table[name];
}

// Inserta un nuevo símbolo en la tabla
void Table::installSymbol(Symbol *s)
{
#ifndef NDEBUG
  assert(this->lookupSymbol(s->getName()) == false); // Precondición
#endif

  this->_table[s->getName()] = s;

#ifndef NDEBUG
  assert(this->lookupSymbol(s->getName()) == true); // Postcondición
#endif
}

// Elimina un símbolo de la tabla
void Table::eraseSymbol(const std::string &name)
{
#ifndef NDEBUG
  assert(this->lookupSymbol(name) == true); // Precondición
#endif

  this->_table.erase(name);

#ifndef NDEBUG
  assert(this->lookupSymbol(name) == false); // Postcondición
#endif
}

// Imprime todos los símbolos de la tabla
void Table::printTable()
{
  for (std::map<std::string, lp::Symbol *>::const_iterator it = this->_table.begin();
       it != this->_table.end();
       ++it)
  {
    std::cout << it->first << ", " << getSymbol(it->first)->getToken() << std::endl;
  }
}

} // namespace lp
