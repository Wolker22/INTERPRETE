/*!
  \file    builtinParameter0.hpp
  \brief   Declaración de la clase BuiltinParameter0
*/

#ifndef _BUILTINPARAMETER0_HPP_
#define _BUILTINPARAMETER0_HPP_

#include <string>
#include <iostream>

#include "builtin.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp{

// Definición de tipo para funciones numéricas sin parámetros
typedef double (*TypePointerDoubleFunction_0)();

/*!
  \class BuiltinParameter0
  \brief Clase que representa una función predefinida sin parámetros
  \note Hereda de la clase Builtin
*/
class BuiltinParameter0 : public lp::Builtin
{
private:
  // Puntero a la función numérica sin parámetros
  lp::TypePointerDoubleFunction_0 _function;

public:

  //! Constructor: inicializa usando el constructor de Builtin y guarda la función
  inline BuiltinParameter0(std::string name, int token, int nParameters,
                           lp::TypePointerDoubleFunction_0 function) :
          Builtin(name, token, nParameters)
  {
    this->setFunction(function);
  }

  //! Constructor de copia: clona los atributos de otra función predefinida
  BuiltinParameter0(const BuiltinParameter0 & f)
  {
    this->setName(f.getName());
    this->setToken(f.getToken());
    this->setNParameters(f.getNParameters());
    this->setFunction(f.getFunction());
  }

  //! Devuelve la función asociada
  lp::TypePointerDoubleFunction_0 getFunction() const
  {
    return this->_function;
  }

  //! Asigna una nueva función
  inline void setFunction(const lp::TypePointerDoubleFunction_0 & function)
  {
    this->_function = function;
  }

  //! Operador de asignación
  BuiltinParameter0 &operator=(const BuiltinParameter0 &f);
};

} // namespace lp

#endif // _BUILTINPARAMETER0_HPP_
