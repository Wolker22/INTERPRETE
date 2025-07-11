/*!
	\file    builtinString1Parameter.hpp
	\brief   Declaración de la clase BuiltinString1Parameter
	\author  
	\date    2025-06-20
	\version 1.0
*/

#ifndef _BUILTINSTRING1PARAMETER_HPP_
#define _BUILTINSTRING1PARAMETER_HPP_

#include <string>
#include "builtin.hpp"

namespace lp
{
	//! Definición de tipo de función de 1 parámetro string
	typedef std::string (*TypePointerStringFunction_1)(const std::string &);

	class BuiltinString1Parameter : public lp::Builtin
	{
	private:
		lp::TypePointerStringFunction_1 _function;

	public:
                inline BuiltinString1Parameter(std::string name = "", int token = 0, int nParameters = 1,
                                                                           lp::TypePointerStringFunction_1 function = 0) :
			Builtin(name, token, nParameters)
		{
			this->setFunction(function);
		}

		BuiltinString1Parameter(const BuiltinString1Parameter &f)
		{
			this->setName(f.getName());
			this->setToken(f.getToken());
			this->setNParameters(f.getNParameters());
			this->setFunction(f.getFunction());
		}

		inline lp::TypePointerStringFunction_1 getFunction() const
		{
			return this->_function;
		}

		inline void setFunction(const lp::TypePointerStringFunction_1 &function)
		{
			this->_function = function;
		}

		BuiltinString1Parameter &operator=(const BuiltinString1Parameter &f);
	};
}

#endif
