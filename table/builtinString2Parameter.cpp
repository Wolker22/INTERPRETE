/*!
  \file    builtinString2Parameter.cpp
  \brief   Code of BuiltinString2Parameter class
*/

#include <iostream>
#include "builtinString2Parameter.hpp"

lp::BuiltinString2Parameter &lp::BuiltinString2Parameter::operator=(const lp::BuiltinString2Parameter &f)
{
  if (this != &f)
  {
    this->setName(f.getName());
    this->setToken(f.getToken());
    this->setNParameters(f.getNParameters());
    this->setFunction(f.getFunction());
  }

  return *this;
}

void lp::BuiltinString2Parameter::read()
{
  std::cout << "Name of the Builtin (String 2 param): ";
  std::cin >> this->_name;

  std::cout << "Token of the Builtin: ";
  std::cin >> this->_token;
  std::cin.ignore();

  std::cout << "Number of parameters: ";
  std::cin >> this->_nParameters;
  std::cin.ignore();
}

void lp::BuiltinString2Parameter::write() const
{
  std::cout << "Name: " << this->getName() << std::endl;
  std::cout << "Token: " << this->getToken() << std::endl;
  std::cout << "Number of parameters: " << this->getNParameters() << std::endl;
}
