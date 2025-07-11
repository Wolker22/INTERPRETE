/*!
	\file    builtinString1Parameter.cpp
	\brief   Implementación de la clase BuiltinString1Parameter
*/

#include "builtinString1Parameter.hpp"

lp::BuiltinString1Parameter &lp::BuiltinString1Parameter::operator=(const lp::BuiltinString1Parameter &f)
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
