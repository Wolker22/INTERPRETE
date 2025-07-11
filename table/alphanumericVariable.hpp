/*!	
	\file    alphanumericVariable.hpp
	\brief   Declaration of AlphanumericVariable class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _ALPHANUMERICVARIABLE_HPP_
#define _NUMERICVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class AlphanumericVariable
  \brief Definition of atributes and methods of AlphanumericVariable class
  \note  AlphanumericVariable Class publicly inherits from Variable class
*/
class AlphanumericVariable:public lp::Variable
{
/*!		
\name Private atributes of AlphanumericVariable class
*/
	private:
		std::string      _value;   //!< \brief Alphanumeric value of the AlphanumericVariable

/*!		
\name Public methods of AlphanumericVariable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Variable's constructor as members initializer
	\param name: name of the AlphanumericVariable
	\param token: token of the AlphanumericVariable
	\param type: type of the AlphanumericVariable
	\param value: string value of the AlphanumericVariable
	\pre   None
	\post  A new AlphanumericVariable is created with the values of the parameters
	\sa   setName, setValue
*/
	inline AlphanumericVariable(std::string name="", int token = 0, int type = 0, std::string value=""): 
 	Variable(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of AlphanumericVariable class
	\pre   None
	\post  A new AlphanumericVariable is created with the values of an existent AlphanumericVariable
	\sa    setName, setValue
*/
	AlphanumericVariable(const AlphanumericVariable & n)
	{
		// Inherited methods
		this->setName(n.getName());

		this->setToken(n.getToken());

		this->setType(n.getType());
		
		// Own method
		this->setValue(n.getValue());
	}


/*!	
	\name Observer
*/
	
/*!	
	\brief  Public method that returns the value of the AlphanumericVariable
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the AlphanumericVariable
	\sa		getValue
*/
	inline std::string getValue() const
	{
		return this->_value;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the value of the AlphanumericVariable
	\note    Inline function
	\param   value: new value of the AlphanumericVariable
	\pre     None
	\post    The value of the AlphanumericVariable is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(const std::string & value)
	{
	    this->_value = value;
	}



		
/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a AlphanumericVariable
	\pre   None
	\post  The atributes of the AlphanumericVariable are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a AlphanumericVariable
	\pre   None
	\post  None
    \sa    read
*/
	void write() const;


/*!	
	\name Operators
*/
	
/*!		
	\brief  Assignment Operator
	\param  n: objectoof AlphanumericVariable class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	AlphanumericVariable &operator=(const AlphanumericVariable &n);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  n: object of AlphanumericVariable class
	\pre    nome
	\post   The atributes of the AlphanumericVariable are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, AlphanumericVariable &n);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  n: object of AlphanumericVariable class
	\pre    nome
	\post   The atributes of the AlphanumericVariable are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, AlphanumericVariable const &n);
	
// End of AlphanumericVariable class
};

// End of name space lp
}

// End of _ALPHANUMERICVARIABLE_HPP_
#endif
