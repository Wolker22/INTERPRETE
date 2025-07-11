/*!
  \file    keyword.hpp
  \brief   Declaración de la clase Keyword
*/

#ifndef _KEYWORD_HPP_
#define _KEYWORD_HPP_

#include <string>
#include <iostream>

#include "symbol.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp{

/*!
  \class Keyword
  \brief Clase que representa una palabra clave del lenguaje
  \note Hereda públicamente de la clase Symbol
*/
class Keyword : public lp::Symbol
{
public:

  //! Constructor con valores por defecto
  inline Keyword(std::string name = "", int token = 0)
    : Symbol(name, token)
  {
    // Sin atributos propios
  }

  //! Constructor de copia
  inline Keyword(const Keyword &k)
  {
    this->setName(k.getName());
    this->setToken(k.getToken());
  }

  //! Operador de asignación
  Keyword &operator=(const Keyword &k);

  //! Escribe los atributos por salida estándar
  void write() const;

  //! Lee los atributos desde la entrada estándar
  void read();
};

} // namespace lp

#endif // _KEYWORD_HPP_
