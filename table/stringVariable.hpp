/*!
	\file    stringVariable.hpp
	\brief   Declaración de la clase StringVariable
*/

#ifndef _STRINGVARIABLE_HPP_
#define _STRINGVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

namespace lp
{
	/*!
	  \class StringVariable
	  \brief Representa una variable de tipo string
	  \note  Hereda de la clase Variable
	*/
	class StringVariable : public lp::Variable
	{
	private:
		std::string _value; //!< Valor de la variable de tipo string

	public:
		// Constructor con parámetros por defecto
		inline StringVariable(std::string name = "", int token = 0, int type = 0, std::string value = "") :
			Variable(name, token, type)
		{
			this->setValue(value);
		}

		// Constructor copia
		StringVariable(const StringVariable &s)
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
		StringVariable &operator=(const StringVariable &s);

		// Operadores friend para I/O de ficheros
		friend std::istream &operator>>(std::istream &i, StringVariable &s);
		friend std::ostream &operator<<(std::ostream &o, const StringVariable &s);
	};
}

#endif
