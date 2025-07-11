/*!	
	\file    alphanumericConstant.hpp
	\brief   Declaration of AlphanumericConstant class
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _ALPHANUMERICCONSTANT_HPP_
#define _ALPHANUMERICCONSTANT_HPP_

#include <string>
#include <iostream>

#include "constant.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class AlphanumericConstant
  \brief Definition of atributes and methods of AlphanumericConstant class
  \note  AlphanumericConstant Class publicly inherits from Constant class
*/
class AlphanumericConstant:public lp::Constant
{
/*!		
\name Private atributes of AlphanumericConstant class
*/
	private:
		std::string      _value;   //!< \brief String value of the AlphanumericConstant

/*!		
\name Public methods of AlphanumericConstant class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Constant's constructor as members initializer
	\param name: name of the AlphanumericConstant
	\param token: token of the AlphanumericConstant
	\param type: type of the AlphanumericConstant
	\param value: String value of the AlphanumericConstant
	\pre   None
	\post  A new AlphanumericConstant is created with the values of the parameters
	\sa   setName, setValue
*/
	inline AlphanumericConstant(std::string name="", int token = 0, int type = 0, std::string value=""): 
 	Constant(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of AlphanumericConstant class
	\pre   None
	\post  A new AlphanumericConstant is created with the values of an existent AlphanumericConstant
	\sa    setName, setValue
*/
	AlphanumericConstant(const AlphanumericConstant & n)
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
	\brief  Public method that returns the value of the AlphanumericConstant
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the AlphanumericConstant
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
	\brief   This functions modifies the value of the AlphanumericConstant
	\note    Inline function
	\param   value: new value of the AlphanumericConstant
	\pre     None
	\post    The value of the AlphanumericConstant is equal to the parameter 
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
	\brief Read an AlphanumericConstant
	\pre   None
	\post  The atributes of the AlphanumericConstant are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write an AlphanumericConstant
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
	\param  n: objectoof AlphanumericConstant class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	AlphanumericConstant &operator=(const AlphanumericConstant &n);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  n: object of AlphanumericConstant class
	\pre    nome
	\post   The atributes of the AlphanumericConstant are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, AlphanumericConstant &n);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  n: object of AlphanumericConstant class
	\pre    nome
	\post   The atributes of the AlphanumericConstant are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, AlphanumericConstant const &n);
	
// End of AlphanumericConstant class
};

// End of name space lp
}

// End of _ALPHANUMERICCONSTANT_HPP_
#endif
