/*!
  \file    variable.hpp
  \brief   Declaración de la clase abstracta Variable
*/

#ifndef _VARIABLE_HPP_
#define _VARIABLE_HPP_

#include <string>
#include <iostream>
#include "symbol.hpp"

namespace lp {

/*!
  \class Variable
  \brief Clase base para representar variables del lenguaje
  \note  Hereda públicamente de lp::Symbol
*/
class Variable : public lp::Symbol
{
protected:
  int _type;  //!< Tipo de variable: UNDEFINED, NUMERICVAR, STRINGVAR, LOGICALVAR

public:
  //! Constructor con parámetros opcionales
  inline Variable(std::string name = "", int token = 0, int type = 0)
    : Symbol(name, token)
  {
    this->setType(type);
  }

  //! Constructor de copia
  inline Variable(const Variable &s)
  {
    this->setName(s.getName());
    this->setToken(s.getToken());
    this->setType(s.getType());
  }

  //! Devuelve el tipo de la variable
  inline int getType() const
  {
    return this->_type;
  }

  //! Modifica el tipo de la variable
  inline void setType(int type)
  {
    this->_type = type;
  }

  //! Operador de asignación
  virtual Variable &operator=(const Variable &v);

  //! Imprime por pantalla los atributos de la variable
  virtual void write() const;

  //! Lee los atributos de la variable desde entrada estándar
  virtual void read();
};

} // namespace lp

#endif // _VARIABLE_HPP_
