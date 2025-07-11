/*!
  \file    builtinString2Parameter.hpp
  \brief   Declaration of BuiltinString2Parameter class
*/

#ifndef _BUILTINSTRING2PARAMETER_HPP_
#define _BUILTINSTRING2PARAMETER_HPP_

#include "builtin.hpp"

namespace lp
{
  typedef std::string (*TypePointerStringFunction_2)(std::string, std::string);

  class BuiltinString2Parameter : public lp::Builtin
  {
  private:
    TypePointerStringFunction_2 _function;

  public:
    BuiltinString2Parameter(std::string name = "", int token = 0, int nParameters = 2,
                            TypePointerStringFunction_2 function = nullptr)
        : Builtin(name, token, nParameters)
    {
      this->setFunction(function);
    }

    BuiltinString2Parameter(const BuiltinString2Parameter &f)
    {
      this->setName(f.getName());
      this->setToken(f.getToken());
      this->setNParameters(f.getNParameters());
      this->setFunction(f.getFunction());
    }

    TypePointerStringFunction_2 getFunction() const
    {
      return this->_function;
    }

    void setFunction(TypePointerStringFunction_2 function)
    {
      this->_function = function;
    }

    BuiltinString2Parameter &operator=(const BuiltinString2Parameter &f);

    void read();
    void write() const;
  };
}

#endif
