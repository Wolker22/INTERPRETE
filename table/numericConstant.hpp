/*!
  \file    numericConstant.hpp
  \brief   Declaración de la clase NumericConstant
*/

#ifndef _NUMERICCONSTANT_HPP_
#define _NUMERICCONSTANT_HPP_

#include <string>
#include <iostream>

#include "constant.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp {

/*!
  \class NumericConstant
  \brief Representa una constante numérica
  \note  Hereda de la clase Constant
*/
class NumericConstant : public lp::Constant
{
private:
  double _value; //!< Valor numérico de la constante

public:

  //! Constructor con valores por defecto
  inline NumericConstant(std::string name = "", int token = 0, int type = 0, double value = 0.0)
    : Constant(name, token, type)
  {
    this->setValue(value);
  }

  //! Constructor de copia
  NumericConstant(const NumericConstant &n)
  {
    this->setName(n.getName());
    this->setToken(n.getToken());
    this->setType(n.getType());
    this->setValue(n.getValue());
  }

  //! Devuelve el valor numérico
  inline double getValue() const
  {
    return this->_value;
  }

  //! Establece el valor numérico
  inline void setValue(const double &value)
  {
    this->_value = value;
  }

  //! Lee los atributos desde entrada estándar
  void read();

  //! Escribe los atributos por salida estándar
  void write() const;

  //! Operador de asignación
  NumericConstant &operator=(const NumericConstant &n);

  //! Operador de entrada desde flujo (friend)
  friend std::istream &operator>>(std::istream &i, NumericConstant &n);

  //! Operador de salida a flujo (friend)
  friend std::ostream &operator<<(std::ostream &o, NumericConstant const &n);
};

} // namespace lp

#endif // _NUMERICCONSTANT_HPP_
