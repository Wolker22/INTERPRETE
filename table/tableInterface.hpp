/*!
  \file    tableInterface.hpp
  \brief   Declaración de la clase abstracta TableInterface
*/

#ifndef _TABLEINTERFACE_HPP_
#define _TABLEINTERFACE_HPP_

#include <string>
#include "symbol.hpp"

namespace lp {

/*!
  \class TableInterface
  \brief Interfaz abstracta para una tabla de símbolos
*/
class TableInterface
{
public:
  //! Comprueba si un símbolo con el nombre dado existe en la tabla
  virtual bool lookupSymbol(const std::string &name) const = 0;

  //! Devuelve un puntero al símbolo con el nombre dado (debe existir)
  virtual lp::Symbol *getSymbol(const std::string &name) = 0;

  //! Indica si la tabla está vacía
  virtual bool isEmpty() const = 0;

  //! Devuelve el número de símbolos almacenados en la tabla
  virtual int getNumberOfSymbols() const = 0;

  //! Inserta un nuevo símbolo en la tabla (debe no existir previamente)
  virtual void installSymbol(Symbol *s) = 0;
};

} // namespace lp

#endif // _TABLEINTERFACE_HPP_
