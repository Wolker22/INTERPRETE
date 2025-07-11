/*!
	\file    stringConstant.hpp
	\brief   Declaración de la clase StringConstant
	\author  
	\date    2025-06-20
	\version 1.0
*/

#ifndef _STRINGCONSTANT_HPP_
#define _STRINGCONSTANT_HPP_

#include <string>
#include <iostream>
#include "constant.hpp"

namespace lp
{
	/*!
	  \class StringConstant
	  \brief Clase que representa constantes de tipo cadena
	  \note  Hereda públicamente de Constant
	*/
	class StringConstant : public lp::Constant
	{
	private:
		std::string _value; //!< Valor de la constante de tipo string

	public:
		// Constructor con parámetros por defecto
		inline StringConstant(std::string name = "", int token = 0, int type = 0, std::string value = "") :
			Constant(name, token, type)
		{
			this->setValue(value);
		}

		// Constructor copia
		StringConstant(const StringConstant &s)
		{
			this->setName(s.getName());
			this->setToken(s.getToken());
			this->setType(s.getType());
			this->setValue(s.getValue());
		}

		// Getter
		inline std::string getValue() const
		{
			return this->_value;
		}

		// Setter
		inline void setValue(const std::string &value)
		{
			this->_value = value;
		}

		// Lectura desde teclado
		void read();

		// Escritura por pantalla
		void write() const;

		// Operador de asignación
		StringConstant &operator=(const StringConstant &s);

		// Operadores friend para I/O de ficheros
		friend std::istream &operator>>(std::istream &i, StringConstant &s);
		friend std::ostream &operator<<(std::ostream &o, const StringConstant &s);
	};
}

#endif
