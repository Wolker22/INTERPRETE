/*!
  \file    builtinParameter2.hpp
  \brief   Declaración de la clase BuiltinParameter2
*/

#ifndef _BUILTIN2PARAMETERS_HPP_
#define _BUILTIN2PARAMETERS_HPP_

#include <string>
#include <iostream>

#include "builtin.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp{

// Tipo de puntero a función con dos parámetros de tipo double
typedef double (*TypePointerDoubleFunction_2)(double x, double y);

/*!
  \class BuiltinParameter2
  \brief Representa una función predefinida con dos parámetros
  \note Hereda públicamente de la clase Builtin
*/
class BuiltinParameter2 : public lp::Builtin
{
private:
  // Puntero a la función asociada
  lp::TypePointerDoubleFunction_2 _function;

public:

  //! Constructor: inicializa nombre, token, número de parámetros y función
  inline BuiltinParameter2(std::string name,
                           int token,
                           int nParameters,
                           lp::TypePointerDoubleFunction_2 function) :
          Builtin(name, token, nParameters)
  {
    this->setFunction(function);
  }

  //! Constructor de copia: clona los atributos de otro BuiltinParameter2
  BuiltinParameter2(const BuiltinParameter2 & f)
  {
    this->setName(f.getName());
    this->setToken(f.getToken());
    this->setNParameters(f.getNParameters());
    this->setFunction(f.getFunction());
  }

  //! Devuelve la función asociada
  lp::TypePointerDoubleFunction_2 getFunction() const
  {
    return this->_function;
  }

  //! Asigna una nueva función al objeto
  inline void setFunction(const lp::TypePointerDoubleFunction_2 & function)
  {
    this->_function = function;
  }

  //! Operador de asignación
  BuiltinParameter2 &operator=(const BuiltinParameter2 &f);
};

} // namespace lp

#endif // _BUILTIN2PARAMETERS_HPP_
