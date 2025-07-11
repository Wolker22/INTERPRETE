/*!
  \file    symbolInterface.hpp
  \brief   Declaración de la clase abstracta SymbolInterface
*/

#ifndef _SYMBOLINTERFACE_HPP_
#define _SYMBOLINTERFACE_HPP_

#include <string>

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp {

/*!
  \class SymbolInterface
  \brief Interfaz abstracta para símbolos del lenguaje
*/
class SymbolInterface
{
public:
  //! Devuelve el nombre del símbolo
  virtual const std::string &getName() const = 0;

  //! Devuelve el token asociado al símbolo
  virtual int getToken() const = 0;

  //! Modifica el nombre del símbolo
  virtual void setName(const std::string &name) = 0;

  //! Modifica el token del símbolo
  virtual void setToken(int token) = 0;
};

} // namespace lp

#endif // _SYMBOLINTERFACE_HPP_
