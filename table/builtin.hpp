/*!
  \file    builtin.hpp
  \brief   Declaración de la clase Builtin (función predefinida)
*/

#ifndef _BUILTIN_HPP_
#define _BUILTIN_HPP_

#include <string>
#include <iostream>

#include "symbol.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp{

/*!
  \class Builtin
  \brief Clase abstracta que representa una función predefinida
  \note Hereda públicamente de la clase Symbol
*/
class Builtin : public lp::Symbol
{
protected:
  int _nParameters; //!< Número de parámetros que recibe la función

public:

  //! Constructor con valores por defecto
  inline Builtin(std::string name = "", int token = 0, int nParameters = 0)
    : Symbol(name, token)
  {
    this->setNParameters(nParameters);
  }

  //! Constructor de copia
  inline Builtin(const Builtin & b)
  {
    this->setName(b.getName());
    this->setToken(b.getToken());
    this->setNParameters(b.getNParameters());
  }

  //! Devuelve el número de parámetros
  inline int getNParameters() const
  {
    return this->_nParameters;
  }

  //! Modifica el número de parámetros
  inline void setNParameters(int nParameters)
  {
    this->_nParameters = nParameters;
  }

  //! Operador de asignación (virtual)
  virtual Builtin &operator=(const Builtin &b);

  //! Método virtual para mostrar por pantalla
  virtual void write() const;

  //! Método virtual para leer desde entrada estándar
  virtual void read();
};

} // namespace lp

#endif // _BUILTIN_HPP_
