/*!
  \file    constant.hpp
  \brief   Declaración de la clase Constant
*/

#ifndef _CONSTANT_HPP_
#define _CONSTANT_HPP_

#include <string>
#include <iostream>

#include "symbol.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp{

/*!
  \class Constant
  \brief Clase abstracta que representa una constante del lenguaje
  \note Hereda públicamente de la clase Symbol
*/
class Constant : public lp::Symbol
{
protected:
  int _type; //!< Tipo de la constante: NUMERICVAR, STRINGVAR, etc.

public:

  //! Constructor con valores por defecto
  inline Constant(std::string name = "", int token = 0, int type = 0)
    : Symbol(name, token)
  {
    this->setType(type);
  }

  //! Constructor de copia
  inline Constant(const Constant & c)
  {
    this->setName(c.getName());
    this->setToken(c.getToken());
    this->setType(c.getType());
  }

  //! Devuelve el tipo de la constante
  inline int getType() const
  {
    return this->_type;
  }

  //! Modifica el tipo de la constante
  inline void setType(int type)
  {
    this->_type = type;
  }

  //! Operador de asignación (virtual)
  virtual Constant &operator=(const Constant &c);

  //! Escribe los atributos de la constante por salida estándar
  virtual void write() const;

  //! Lee los atributos de la constante desde entrada estándar
  virtual void read();
};

} // namespace lp

#endif // _CONSTANT_HPP_
