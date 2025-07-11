/*!
  \file    stringFunction.hpp
  \brief   Implementation of string manipulation functions
*/

#include "stringFunction.hpp"

#include <algorithm> // for std::transform

namespace lp
{
  int length(const std::string &s)
  {
    return static_cast<int>(s.length());
  }

  std::string concat(const std::string &s1, const std::string &s2)
  {
    return s1 + s2;
  }

  std::string substring(const std::string &s, int start, int len)
  {
    if (start < 0 || start >= static_cast<int>(s.length()) || len < 0)
      return "";
    return s.substr(start, len);
  }

  std::string to_upper(const std::string &s)
  {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
  }

  std::string to_lower(const std::string &s)
  {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
  }
} // namespace lp
