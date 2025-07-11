/*!	
	\file    stringVariable.cpp
	\brief   Code of some functions of StringVariable class
*/

#include <iostream>
#include "stringVariable.hpp"

void lp::StringVariable::read()
{
	std::cout << "Name of the StringVariable: ";
	std::cin >> this->_name;

	std::cout << "Token of the StringVariable: ";
	std::cin >> this->_token;
	std::cin.ignore();

	std::cout << "Type of the StringVariable: ";
	std::cin >> this->_type;
	std::cin.ignore();

	std::cout << "Value of the StringVariable: ";
	std::getline(std::cin, this->_value);
}

void lp::StringVariable::write() const
{
	std::cout << "Name: " << this->getName() << std::endl;
	std::cout << "Token: " << this->getToken() << std::endl;
	std::cout << "Type: " << this->getType() << std::endl;
	std::cout << "Value: " << this->getValue() << std::endl;
}

lp::StringVariable &lp::StringVariable::operator=(const lp::StringVariable &s)
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

std::istream &lp::operator>>(std::istream &i, lp::StringVariable &s)
{
	std::getline(i, s._name);
	i >> s._token;
	i.ignore();
	i >> s._type;
	i.ignore();
	std::getline(i, s._value);
	return i;
}

std::ostream &lp::operator<<(std::ostream &o, const lp::StringVariable &s)
{
	o << s._name << std::endl;
	o << s._token << std::endl;
	o << s._type << std::endl;
	o << s._value << std::endl;
	return o;
}
