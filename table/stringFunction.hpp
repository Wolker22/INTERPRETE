/*!
  \file    stringFunction.hpp
  \brief   Implementación de funciones para manipulación de cadenas
*/

#ifndef _STRINGFUNCTION_HPP_
#define _STRINGFUNCTION_HPP_

#include <string>

namespace lp
{
  // Devuelve la longitud de una cadena
  int length(const std::string &s);

  // Concatena dos cadenas
  std::string concat(const std::string &s1, const std::string &s2);

  // Devuelve una subcadena desde la posición "start" con longitud "len"
  std::string substring(const std::string &s, int start, int len);

  // Convierte a mayúsculas
  std::string to_upper(const std::string &s);

  // Convierte a minúsculas
  std::string to_lower(const std::string &s);
}

#endif // _STRINGFUNCTION_HPP_
