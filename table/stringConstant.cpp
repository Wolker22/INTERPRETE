/*!
	\file    stringConstant.cpp
	\brief   Implementación de métodos de la clase StringConstant
	\author  
	\date    2025-06-20
	\version 1.0
*/

#include <iostream>
#include "stringConstant.hpp"

void lp::StringConstant::read()
{
	std::cout << "Name of the StringConstant: ";
	std::cin >> this->_name;

	std::cout << "Token of the StringConstant: ";
	std::cin >> this->_token;
	std::cin.ignore();

	std::cout << "Type of the StringConstant: ";
	std::cin >> this->_type;
	std::cin.ignore();

	std::cout << "Value of the StringConstant: ";
	std::getline(std::cin, this->_value);
}

void lp::StringConstant::write() const
{
	std::cout << "Name: " << this->getName() << std::endl;
	std::cout << "Token: " << this->getToken() << std::endl;
	std::cout << "Type: " << this->getType() << std::endl;
	std::cout << "Value: " << this->getValue() << std::endl;
}

lp::StringConstant &lp::StringConstant::operator=(const lp::StringConstant &s)
{
	if (this != &s)
	{
		this->setName(s.getName());
		this->setToken(s.getToken());
		this->setType(s.getType());
		this->setValue(s.getValue());
	}
	return *this;
}

std::istream &lp::operator>>(std::istream &i, lp::StringConstant &s)
{
	std::getline(i, s._name);
	i >> s._token;
	i.ignore();
	i >> s._type;
	i.ignore();
	std::getline(i, s._value);
	return i;
}

std::ostream &lp::operator<<(std::ostream &o, const lp::StringConstant &s)
{
	o << s._name << std::endl;
	o << s._token << std::endl;
	o << s._type << std::endl;
	o << s._value << std::endl;
	return o;
}
