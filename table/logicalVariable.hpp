/*!
  \file    logicalVariable.hpp
  \brief   Declaración de la clase LogicalVariable
*/

#ifndef _LOGICALVARIABLE_HPP_
#define _LOGICALVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp{

/*!
  \class LogicalVariable
  \brief Representa una variable lógica (true o false)
  \note Hereda públicamente de la clase Variable
*/
class LogicalVariable : public lp::Variable
{
private:
  bool _value; //!< Valor lógico de la variable

public:

  //! Constructor con valores por defecto
  inline LogicalVariable(std::string name = "", int token = 0, int type = 0, bool value = false)
    : Variable(name, token, type)
  {
    this->setValue(value);
  }

  //! Constructor de copia
  LogicalVariable(const LogicalVariable &n)
  {
    this->setName(n.getName());
    this->setToken(n.getToken());
    this->setType(n.getType());
    this->setValue(n.getValue());
  }

  //! Devuelve el valor lógico
  inline bool getValue() const
  {
    return this->_value;
  }

  //! Establece el valor lógico
  inline void setValue(bool value)
  {
    this->_value = value;
  }

  //! Lee los atributos desde entrada estándar
  void read();

  //! Escribe los atributos por salida estándar
  void write() const;

  //! Operador de asignación
  LogicalVariable &operator=(const LogicalVariable &n);

  //! Operador de extracción (entrada)
  friend std::istream &operator>>(std::istream &i, LogicalVariable &n);

  //! Operador de inserción (salida)
  friend std::ostream &operator<<(std::ostream &o, LogicalVariable const &n);
};

} // namespace lp

#endif // _LOGICALVARIABLE_HPP_
