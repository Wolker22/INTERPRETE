/*!
  \file    builtinParameter1.hpp
  \brief   Declaración de la clase BuiltinParameter1
*/

#ifndef _BUILTINPARAMETER1_HPP_
#define _BUILTINPARAMETER1_HPP_

#include <string>
#include <iostream>

#include "builtin.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp{

// Definición de tipo para funciones numéricas con un parámetro
typedef double (*TypePointerDoubleFunction_1)(double x);

/*!
  \class BuiltinParameter1
  \brief Representa una función predefinida con un único parámetro
  \note Hereda públicamente de la clase Builtin
*/
class BuiltinParameter1 : public lp::Builtin
{
private:
  // Puntero a la función asociada
  lp::TypePointerDoubleFunction_1 _function;

public:

  //! Constructor: inicializa nombre, token, número de parámetros y función
  inline BuiltinParameter1(std::string name,
                           int token,
                           int nParameters,
                           lp::TypePointerDoubleFunction_1 function) :
                           Builtin(name, token, nParameters)
  {
    this->setFunction(function);
  }

  //! Constructor de copia: clona los atributos de otro BuiltinParameter1
  BuiltinParameter1(const BuiltinParameter1 & f)
  {
    this->setName(f.getName());
    this->setToken(f.getToken());
    this->setNParameters(f.getNParameters());
    this->setFunction(f.getFunction());
  }

  //! Devuelve la función asociada
  lp::TypePointerDoubleFunction_1 getFunction() const
  {
    return this->_function;
  }

  //! Asigna una nueva función al objeto
  inline void setFunction(const lp::TypePointerDoubleFunction_1 & function)
  {
    this->_function = function;
  }

  //! Operador de asignación
  BuiltinParameter1 &operator=(const BuiltinParameter1 &f);
};

} // namespace lp

#endif // _BUILTINPARAMETER1_HPP_
