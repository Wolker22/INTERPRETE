/*!
  \file    symbol.hpp
  \brief   Declaración de la clase Symbol
*/

#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

#include <string>
#include "symbolInterface.hpp"

/*!
  \namespace lp
  \brief Espacio de nombres para el intérprete de pseudocódigo
*/
namespace lp {

/*!
  \class Symbol
  \brief Clase base para representar un símbolo con nombre y token
  \note  Hereda de SymbolInterface
*/
class Symbol : public lp::SymbolInterface
{
protected:
  std::string _name; //!< Nombre del símbolo
  int _token;        //!< Token asociado al símbolo

public:

  //! Constructor con valores por defecto
  inline Symbol(std::string name = "", int token = 0)
  {
    this->setName(name);
    this->setToken(token);
  }

  //! Constructor de copia
  inline Symbol(const Symbol &s)
  {
    this->setName(s.getName());
    this->setToken(s.getToken());
  }

  //! Devuelve el nombre del símbolo
  inline const std::string &getName() const
  {
    return this->_name;
  }

  //! Devuelve el token asociado al símbolo
  inline int getToken() const
  {
    return this->_token;
  }

  //! Modifica el nombre del símbolo
  inline void setName(const std::string &name)
  {
    this->_name = name;
  }

  //! Modifica el token del símbolo
  inline void setToken(int token)
  {
    this->_token = token;
  }

  //! Operador de igualdad: compara por nombre
  bool operator==(const Symbol &s) const;

  //! Operador menor: ordena por nombre (orden lexicográfico)
  bool operator<(const Symbol &s) const;
};

} // namespace lp

#endif // _SYMBOL_HPP_
