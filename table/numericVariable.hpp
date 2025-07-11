/*!
  \file    numericVariable.hpp
  \brief   Declaración de la clase NumericVariable
*/

#ifndef _NUMERICVARIABLE_HPP_
#define _NUMERICVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp {

/*!
  \class NumericVariable
  \brief Representa una variable numérica
  \note  Hereda de la clase Variable
*/
class NumericVariable : public lp::Variable
{
private:
  double _value; //!< Valor numérico de la variable

public:

  //! Constructor con valores por defecto
  inline NumericVariable(std::string name = "", int token = 0, int type = 0, double value = 0.0)
    : Variable(name, token, type)
  {
    this->setValue(value);
  }

  //! Constructor de copia
  NumericVariable(const NumericVariable &n)
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
  NumericVariable &operator=(const NumericVariable &n);

  //! Operador de entrada desde flujo (friend)
  friend std::istream &operator>>(std::istream &i, NumericVariable &n);

  //! Operador de salida hacia flujo (friend)
  friend std::ostream &operator<<(std::ostream &o, NumericVariable const &n);
};

} // namespace lp

#endif // _NUMERICVARIABLE_HPP_
