/*! 	
	\file   symbol.hpp
	\brief  Declaration of Symbol class
	\author 
	\date    2017-12-1
	\version 1.0
*/

#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

#include <string>

#include "symbolInterface.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!
  \class      Symbol
  \brief      Definition of the class Symbol
*/
class Symbol:public lp::SymbolInterface
{

/*!		
\name Protected atributes of Symbol class
*/
	protected:
		std::string _name;    //!< \brief Name of the Symbol
		int      	_token;   //!< \brief Token of the Symbol
        int         _type;    //!< \brief Type of the Symbol

/*!	
\name Public methods of Symbol class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function
	\param name: name of the Symbol
	\param token: token of the Symbol
	\param type: type of the Symbol
	\pre   None
	\post  A new Symbol is created with the values of the parameters
	\sa   setName, setToken, setType
*/
	inline Symbol(std::string name="", int token = 0, int type = -1)
	{
		this->setName(name);
		this->setToken(token);
        this->setType(type);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param s: object of Symbol class
	\pre   None
	\post  A new Symbol is created with the values of an existent Symbol
	\sa    setName, setToken, setType
*/
	inline Symbol(const Symbol & s)
	{
		this->setName(s.getName());
		this->setToken(s.getToken());
        this->setType(s.getType());
	}


/*!
	\name Observers
*/

/*!	
	\brief  Public method that returns the name of the Symbol
	\note   Inline Function
	\pre    None
	\post   None
    \return The name of the Symbol
	\sa		getToken, getType
*/
	inline const std::string & getName() const
	{
		return this->_name;
	}


/*!	
	\brief   Public method that returns the token of the Symbol
	\note    Inline function
	\pre     None
	\post    None
	\return  The token of the Symbol
	\sa		 getName, getType
*/
	inline int getToken() const
	{
		return this->_token;
	}

/*!	
	\brief   Public method that returns the type of the Symbol
	\note    Inline function
	\pre     None
	\post    None
	\return  The type of the Symbol
	\sa		 getName, getToken
*/
	inline int getType() const
	{
		return this->_type;
	}

	
/*!
	\name Modifiers
*/
	
/*!	
	\brief   This functions modifies the name of the Symbol
	\note    Inline function
	\param   name: new name of the Symbol
	\pre     None
	\post    The name of the Symbol is equal to the parameter 
	\return  void
	\sa 	 setToken, setType
*/
	inline void setName(const std::string & name)
	{
		this->_name = name;
	}


/*!	
	\brief   This functions modifies the token of the Symbol
	\note    Inline function
	\param   token: new value of the Variable
	\pre     None
	\post    The token of the Symbol is equal to the parameter 
	\return  void
	\sa 	 setName, setType
*/
	inline void setToken(int token) 
	{
	    this->_token = token;
	}

/*!	
	\brief   This functions modifies the type of the Symbol
	\note    Inline function
	\param   type: new type of the Symbol
	\pre     None
	\post    The type of the Symbol is equal to the parameter 
	\return  void
	\sa 	 setName, setToken
*/
	inline void setType(int type) 
	{
	    this->_type = type;
	}

/*!	
	\name Relational operators
*/
	
/*!		
	\brief  Comparison operator that compares the lexicographic equality of two Symbols
	\param  s: object of Symbol class
	\pre    nome
	\post   None
	\return true if the object are equal; false, otherwise
*/
	bool operator==(const Symbol & s) const;

		
/*!		
	\brief  Comparison operator that compares the lexicographic inequality of two objects
	\param  s: object of Variable class
	\pre    nome
	\post   None
	\return true if this object lexicographically precedes to the object passed as a parameter
*/
	bool operator <(const Symbol & s) const;


// End of definition of Symbol class
};

/////////////////////////////////////////////////////////////////////////////////////


// End of name space lp
}

// End of _SYMBOL_HPP_
#endif  