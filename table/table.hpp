/*!
  \file    table.hpp
  \brief   Declaración de la clase Table
*/

#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <string>
#include <map>

#include "tableInterface.hpp"

namespace lp {

/*!
  \class Table
  \brief Clase que representa una tabla de símbolos
  \note  Hereda de TableInterface
*/
class Table : public lp::TableInterface
{
private:
  std::map<std::string, lp::Symbol *> _table; //!< Mapa de nombres a punteros de símbolos

public:
  //! Constructor: inicializa la tabla vacía
  Table()
  {
    this->_table.clear();
  }

  //! Destructor: limpia la tabla
  inline ~Table()
  {
    this->_table.clear();
  }

  //! Comprueba si existe un símbolo con el nombre dado
  bool lookupSymbol(const std::string &name) const;

  //! Devuelve un puntero al símbolo con el nombre dado (debe existir)
  lp::Symbol *getSymbol(const std::string &name);

  //! Indica si la tabla está vacía
  inline bool isEmpty() const
  {
    return _table.empty();
  }

  //! Devuelve el número de símbolos almacenados
  inline int getNumberOfSymbols() const
  {
    return _table.size();
  }

  //! Inserta un nuevo símbolo en la tabla (debe no existir previamente)
  void installSymbol(Symbol *s);

  //! Elimina un símbolo por su nombre (debe existir)
  void eraseSymbol(const std::string &name);

  //! Muestra por consola el contenido de la tabla
  void printTable();
};

} // namespace lp

#endif // _TABLE_HPP_
