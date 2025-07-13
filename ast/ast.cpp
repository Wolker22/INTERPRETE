/*!	
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author  
	\date    2018-12-13
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <limits>

// Para usar la funciones pow y std::abs
#include <cmath>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

// 
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/alphanumericVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"
#include "../table/alphanumericConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType() 
{ 
	// Get the identifier in the table of symbols as Variable
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Return the type of the Variable
	return var->getType();
}


void lp::VariableNode::printAST() 
{
  std::cout << "VariableNode: " << this->_id;
  std::cout << " (Type: " << this->getType() << ")" << std::endl;
}


double lp::VariableNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable *var = (lp::NumericVariable *) table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateNumber(): la variable no es numérica", this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::VariableNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable *var = (lp::LogicalVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateBool(): la variable no es booleana", this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}


std::string lp::VariableNode::evaluateString() 
{ 
	std::string result = "";

	if (this->getType() == STRING)
	{
		// Get the identifier in the table of symbols as AlphanumericVariable
		lp::AlphanumericVariable *var = (lp::AlphanumericVariable *) table.getSymbol(this->_id);

		// Copy the value of the AlphanumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateString(): la variable no es alfanumérica", this->_id);
	}

	// Return the value of the AlphanumericVariable
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConstantNode::printAST() 
{
  std::cout << "ConstantNode: " << this->_id;
  std::cout << " (Type: " << this->getType() << ")" << std::endl;
}

int lp::ConstantNode::getType() 
{ 
	// Get the identifier in the table of symbols as Constant
	lp::Constant *var = (lp::Constant *) table.getSymbol(this->_id);

	// Return the type of the Constant
	return var->getType();
}


double lp::ConstantNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant *constant = (lp::NumericConstant *) table.getSymbol(this->_id);

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateNumber(): la constante no es numérica", this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::ConstantNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant *constant = (lp::LogicalConstant *) table.getSymbol(this->_id);

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateBool(): la constante no es booleana", this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}

/* EJERCICIO 2 */

std::string lp::ConstantNode::evaluateString() 
{ 
	std::string result = "";

	if (this->getType() == STRING)
	{
		// Get the identifier in the table of symbols as AlphanumericConstant
		lp::AlphanumericConstant *constant = (lp::AlphanumericConstant *) table.getSymbol(this->_id);

		// Copy the value of the AlphanumericConstant
		result = constant->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateString(): la constante no es alfanumérica", this->_id);
	}

	// Return the value of the AlphanumericConstant
	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 

int lp::NumberNode::getType()
{
	return NUMBER;
}


void lp::NumberNode::printAST()
{
  std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber() 
{ 
    return this->_number; 
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 

int lp::StringNode::getType()
{
	return STRING;
}


void lp::StringNode::printAST()
{
  std::cout << "StringNode: " << this->_string << std::endl;
}

std::string lp::StringNode::evaluateString() 
{ 
    return this->_string; 
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == NUMBER)
	{
		result = NUMBER;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles para", "Numeric Unary Operator");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == BOOL)
	{
		result = BOOL;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles para", "Logical Unary Operator");
	}
	
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = NUMBER;
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para", "Numeric Operator");

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::RelationalOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = BOOL;
	else if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
		result = BOOL;
	else if ( (this->_left->getType() == STRING) and (this->_right->getType() == STRING))
		result = BOOL;
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para", "Relational Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode:: getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
	{
		// 
		result = BOOL;
	}
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para", "Logical Operator");

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------- EJERCICIO 2 -------------------------------------- //

int lp::AlphanumericOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == STRING) and (this->_right->getType() == STRING))
		result = STRING;
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para", "Alphanumeric Operator");

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConcatenationNode::printAST() 
{
	std::cout << "ConcatenationNode: ||"  << std::endl;
	std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

std::string lp::ConcatenationNode::evaluateString() 
{
	std::string result = "";

	// Ckeck the types of the expressions
	if (this->getType() == STRING)
	{
		result = this->_left->evaluateString() + this->_right->evaluateString();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son alfanuméricas para ", "Concatenation");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::printAST() 
{
  std::cout << "UnaryMinusNode: -"  << std::endl;
  std::cout << "\t"; 
  this->_exp->printAST();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Minus
		result = - this->_exp->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "UnaryMinus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::printAST() 
{
  std::cout << "UnaryPlusNode: +"  << std::endl;
  std::cout << "\t"; 
  this->_exp->printAST();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ","UnaryPlus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::printAST() 
{
  std::cout << "PlusNode: +"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Plus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::printAST() 
{
  std::cout << "MinusNode: -"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::MinusNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Minus");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::printAST() 
{
  std::cout << "MultiplicationNode: *"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::MultiplicationNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ","Multiplication");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::printAST()
{
  std::cout << "DivisionNode: /" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::DivisionNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			warning("Error en tiempo de ejecución", "División por cero");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Division");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::WholeDivisionNode::printAST()
{
  std::cout << "WholeDivisionNode: //" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::WholeDivisionNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				int leftInt = static_cast<int>(leftNumber);
				int rightInt = static_cast<int>(rightNumber);
				int intResult = leftInt / rightInt;
				
				result = static_cast<double>(intResult);
		}
		else
		{
			warning("Error en tiempo de ejecución", "WholeDivision");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "WholeDivision");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::printAST()
{
  std::cout << "ModuloNode: mod" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::ModuloNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
    	if(std::abs(rightNumber) > ERROR_BOUND)
				result = (int) leftNumber % (int) rightNumber;
		else
		warning("Error en tiempo de ejecución", "División por cero");
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para", "Modulo");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::printAST() 
{
  std::cout << "PowerNode: ^"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::PowerNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para", "Power");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AlternativeNode::printAST() 
{
  std::cout << "AlternativeNode: ?"  << std::endl;
  std::cout << "\t"; 
	this->_cond->printAST();
  std::cout << "\t"; 
	this->_left->printAST();
  std::cout << "\t"; 
	this->_right->printAST();
}

double lp::AlternativeNode::evaluateNumber() 
{
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		if(this->_cond->getType()==BOOL) {
			if(this->_cond->evaluateBool()==true) {
				result = this->_left->evaluateNumber();
        return result;
        
			}
			else {
				result = this->_right->evaluateNumber();
        return result;
			}
		}
		else {
			warning("Error en tiempo de ejecución: las condición no es booleana para", "Alternative");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para", "Alternative");
	}

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::BuiltinFunctionNode_0::getType()
{
	return	NUMBER;
}


void lp::BuiltinFunctionNode_0::printAST() 
{
  std::cout << "BuiltinFunctionNode_0: "  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
}

double lp::BuiltinFunctionNode_0::evaluateNumber() 
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
   	return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;
		
	if (this->_exp->getType() == NUMBER)
		result = NUMBER;
	else
		warning("Error en tiempo de ejecución: tipo incompatible para", "BuiltinFunctionNode_1");

	return	result;
}

void lp::BuiltinFunctionNode_1::printAST() 
{
  std::cout << "BuiltinFunctionNode_1: "  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;  
  std::cout << "\t";
	this->_exp->printAST();
	std::cout << std::endl;
}

double lp::BuiltinFunctionNode_1::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);

		// Apply the function to the parameter and copy the result
		result = f->getFunction()(this->_exp->evaluateNumber());
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible del parámetro para ", this->_id);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
	int result = 0;
		
	if (this->_exp1->getType() == this->_exp2->getType())
		result = this->_exp1->getType();
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para", "BuiltinFunctionNode_2");

	return	result;
}


void lp::BuiltinFunctionNode_2::printAST() 
{
  std::cout << "BuiltinFunctionNode_2: " << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";
  this->_exp1->printAST();
  std::cout << "\t";
	this->_exp2->printAST();
	std::cout << std::endl;
}

double lp::BuiltinFunctionNode_2::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

		// Apply the function to the parameters and copy the result
	  	result = f->getFunction()(this->_exp1->evaluateNumber(),this->_exp2->evaluateNumber());
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", this->_id);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::printAST()
{
  std::cout << "GreaterThanNode: >" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::GreaterThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber > rightNumber);
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador Greater than");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::printAST()
{
  std::cout << "GreaterOrEqualNode: >= " << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::GreaterOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber >= rightNumber);
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador Greater or equal than");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::printAST()
{
  std::cout << "LessThanNode: <" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::LessThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber < rightNumber);
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador Less than");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::printAST()
{
  std::cout << "LessOrEqualNode: <=" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::LessOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber <= rightNumber);
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador Less or equal than");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::printAST()
{
  std::cout << "EqualNode: =" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::EqualNode::evaluateBool() 
{
	bool result = false;
	std::string leftString, rightString; // Hay que declararlos fuera del switch

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) < ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				// 
				result = (leftBoolean == rightBoolean);
				break;
			
			case STRING:
				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				// 
				result = (leftString == rightString);
				break;
		  default:
				warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", 
								"operador Equal");				
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", 
						"operador Equal");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::printAST()
{
  std::cout << "NotEqualNode: !=" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::NotEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) >= ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				// 
				result = (leftBoolean != rightBoolean);
				break;
		  default:
				warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", 
								"operador Not Equal");					
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador Not Equal");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::printAST()
{
  std::cout << "AndNode: &&" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::AndNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool and rightBool;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador And");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::printAST()
{
  std::cout << "OrNode: ||" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::OrNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool or rightBool;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador Or");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::printAST()
{
  std::cout << "NotNode: !" << std::endl;
  std::cout << "\t";
  this->_exp->printAST();
}

bool lp::NotNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles de parámetros para ", "operador Not");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::printAST() 
{
  std::cout << "assignment_node: ="  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";

  // Check the expression
	if (this->_exp != NULL)
	{
	  this->_exp->printAST();
    std::cout << std::endl;
  }
  // this->_asgn is not NULL: multiple assingment
  else 
    this->_asgn->printAST();

}

void lp::AssignmentStmt::evaluate() 
{
	/* Get the identifier in the table of symbols as Variable */
	/* 
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value 
					lp::NumericVariable *v = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,value);
					table.installSymbol(v);
				}
			}
			break;

			case BOOL:
			{
				bool value;
				// evaluate the expression as BOOL
			 	value = this->_exp->evaluateBool();

				if (firstVar->getType() == BOOL)
				{
				  	// Get the identifier in the table of symbols as LogicalVariable
					lp::LogicalVariable *v = (lp::LogicalVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not BOOL
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value 
					lp::LogicalVariable *v = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,value);
					table.installSymbol(v);
				}
			}
			break;

			case STRING: // NUEVO
			{
				std::string value;
				// evaluate the expression as STRING
			 	value = this->_exp->evaluateString();

				// Check the type of the first varible
				if (firstVar->getType() == STRING)
				{
				  	// Get the identifier in the table of symbols as AlphanumericVariable
					lp::AlphanumericVariable *v = (lp::AlphanumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not STRING
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as AlphanumericVariable 
					// with the type STRING and the value 
					lp::AlphanumericVariable *v = new lp::AlphanumericVariable(this->_id,
											VARIABLE,STRING,value);
					table.installSymbol(v);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible de expresión para ", "Assignment");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else // this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->_id);

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value of the previous variable 
					lp::NumericVariable *firstVar = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case BOOL:
			{
				/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
				lp::LogicalVariable *secondVar = (lp::LogicalVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == BOOL)
				{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::LogicalVariable *firstVar = (lp::LogicalVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not BOOL
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value of the previous variable 
					lp::LogicalVariable *firstVar = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case STRING:
			{
				/* Get the identifier of the previous asgn in the table of symbols as AlphanumericVariable */
				lp::AlphanumericVariable *secondVar = (lp::AlphanumericVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == STRING)
				{
				/* Get the identifier of the first variable in the table of symbols as AlphanumericVariable */
				lp::AlphanumericVariable *firstVar = (lp::AlphanumericVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as AlphanumericVariable
//					lp::AlphanumericVariable *n = (lp::AlphanumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not STRING
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as AlphanumericVariable 
					// with the type STRING and the value of the previous variable 
					lp::AlphanumericVariable *firstVar = new lp::AlphanumericVariable(this->_id,
											VARIABLE,STRING,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible de expresión para ", "Assignment");
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentPlusStmt::printAST() 
{
  std::cout << "AssignmentPlusStmt: +:="  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";
  this->_exp->printAST();
  std::cout << std::endl;
}

void lp::AssignmentPlusStmt::evaluate() 
{
	lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);
	
	if (n->getType() == NUMBER)
	{
		double result = n->getValue() + this->_exp->evaluateNumber();
		n->setValue(result);
	}
	else
	{
		warning("Error en tiempo de ejecución: la expresión no es numérica para ","Assignment_plus");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentMinusStmt::printAST() 
{
  std::cout << "AssignmentPlusStmt: -:="  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";
  this->_exp->printAST();
  std::cout << std::endl;
}

void lp::AssignmentMinusStmt::evaluate() 
{
	lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);
	
	if (n->getType() == NUMBER)
	{
		double result = n->getValue() - this->_exp->evaluateNumber();
		n->setValue(result);
	}
	else
	{
		warning("Error en tiempo de ejecución: la expresión no es numérica para ","Assignment_minus");
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::printAST() 
{
  std::cout << "printASTStmt: printAST"  << std::endl;
  std::cout << "\t";
  this->_exp->printAST();
  std::cout << std::endl;
}


void lp::PrintStmt::evaluate() 
{

	switch(this->_exp->getType())
	{
		case NUMBER:
				std::cout << this->_exp->evaluateNumber();
				break;
		case BOOL:
			if (this->_exp->evaluateBool())
				std::cout << "true";
			else
				std::cout << "false";
		
			break;
		case STRING: // NUEVO
				std::cout << this->_exp->evaluateString();
				break;

		default:
			warning("Error en tiempo de ejecución: tipo incompatible para ", "print");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IncrementStmt::printAST() 
{
  std::cout << "IncrementStmt: ++"  << std::endl;
  std::cout << "\t";
  std::cout << this->_id;
  std::cout << std::endl;
}


void lp::IncrementStmt::evaluate() 
{
	
	lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

	if (n->getType() == NUMBER)
	{
		n->setValue(n->getValue() + 1);
	}
	else
	{
		warning("Error en tiempo de ejecución: la expresión no es numérica para ","increment");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DecrementStmt::printAST() 
{
  std::cout << "DecrementStmt: --"  << std::endl;
  std::cout << "\t";
  std::cout << this->_id;
  std::cout << std::endl;
}


void lp::DecrementStmt::evaluate() 
{
	
	lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

	if (n->getType() == NUMBER)
	{
		n->setValue(n->getValue() - 1);
	}
	else
	{
		warning("Error en tiempo de ejecución: la expresión no es numérica para ","decrement");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::printAST() 
{
  std::cout << "ReadStmt: read"  << std::endl;
  std::cout << "\t";
  std::cout << this->_id;
  std::cout << std::endl;
}


void lp::ReadStmt::evaluate() 
{   
	double value;
	std::cin >> value;

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is NUMBER
	if (var->getType() == NUMBER)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);
						
		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable 
		// with the type NUMBER and the read value 
		lp::NumericVariable *n = new lp::NumericVariable(this->_id, 
									  VARIABLE,NUMBER,value);

		table.installSymbol(n);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStringStmt::printAST() 
{
  std::cout << "ReadStringStmt: read_string"  << std::endl;
  std::cout << "\t";
  std::cout << this->_id;
  std::cout << std::endl;
}

void lp::ReadStringStmt::evaluate() 
{   
	std::string value;
	//std::cin >> value;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, value); // Lee varias palabras

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is STRING
	if (var->getType() == STRING)
	{
		/* Get the identifier in the table of symbols as AlphanumericVariable */
		lp::AlphanumericVariable *n = (lp::AlphanumericVariable *) table.getSymbol(this->_id);
						
		/* Assignment the read_string value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not STRING
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as AlphanumericVariable 
		// with the type STRING and the read_string value 
		lp::AlphanumericVariable *n = new lp::AlphanumericVariable(this->_id, 
									  VARIABLE,STRING,value);

		table.installSymbol(n);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::printAST() 
{
  std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate() 
{
  // Empty
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::IfStmt::printAST() 
{
  std::cout << "IfStmt: "  << std::endl;
  // Condition
  std::cout << "\t";
  this->_cond->printAST();

  // Consequent
  std::cout << "\t";
  this->_stmt1->printAST();

 // The alternative is printASTed if exists
  if (this->_stmt2 != NULL)
     {  
       std::cout << "\t";
	   this->_stmt2->printAST();
     }

  std::cout << std::endl;
}


void lp::IfStmt::evaluate() 
{
	if (this->_cond->getType() == BOOL) {
		// If the condition is true,
		if (this->_cond->evaluateBool() == true )
		// the consequent is run 
		this->_stmt1->evaluate();

		// Otherwise, the alternative is run if exists
		else if (this->_stmt2 != NULL)
			this->_stmt2->evaluate();
	}
	else {
		warning("Error en tiempo de ejecución: tipo incompatible de condición para ", "if");
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::WhileStmt::printAST() 
{
  std::cout << "WhileStmt: "  << std::endl;

  // Print the condition
  std::cout << "\t";
  this->_cond->printAST();

  // Print the body of the while loop
  std::cout << "\t";
  this->_body->printAST();

  std::cout << std::endl;
}



void lp::WhileStmt::evaluate()
{
  if (this->_cond->getType() == BOOL) {
	while (_cond->evaluateBool())
	{
		_body->evaluate();  // AST ya sabe ejecutar todas las sentencias
	}
  }
  else {
	warning("Error en tiempo de ejecución: tipo incompatible de condición para ", "while");
  }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

// NUEVO: SE HA ELIMINADO BlockStmt DEBIDO A QUE LA SENTENCIA block YA NO ES NECESARIA

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::printAST() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
     (*stmtIter)->printAST();
  }
}



void lp::AST::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::RepeatStmt::printAST() 
{
  std::cout << "RepeatStmt:" << std::endl;

  // Body of the repeat loop
  std::cout << "\t";
  this->_body->printAST();

  // Condition of the repeat loop
  std::cout << "\t";
  this->_cond->printAST();

  std::cout << std::endl;
}


void lp::RepeatStmt::evaluate() 
{
  // Do the body until the condition becomes true

	do {
		this->_body->evaluate();
		if (this->_cond->getType() != BOOL) {
			warning("Error en tiempo de ejecución: la condición cambió a un tipo incompatible durante ", "repeat");
			break;
		}
	} while (this->_cond->evaluateBool() == false);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::ForStmt::printAST()
{
  std::cout << "ForStmt:" << std::endl;

  // Loop control variable
  std::cout << "\tVariable: " << this->_var << std::endl;

  // Start value
  std::cout << "\t";
  this->_start->printAST();

  // End value
  std::cout << "\t";
  this->_end->printAST();

  // Step value
  std::cout << "\t";
  this->_step->printAST();

  // Body of the for loop
  std::cout << "\t";
  this->_body->printAST();

  std::cout << std::endl;
}


void lp::ForStmt::evaluate()
{
	if (this->_start->getType() != NUMBER || this->_end->getType() != NUMBER || this->_step->getType() != NUMBER) {
		warning("Error en tiempo de ejecución: tipo incompatible para ", "for");
		return;
	}
	
	double startValue = _start->evaluateNumber();
	double endValue = _end->evaluateNumber();
	double stepValue = _step->evaluateNumber();

    if (stepValue == 0.0) {
        warning("Error en tiempo de ejecución: el valor del paso no puede ser cero en ", "for");
        return;
    }
	if (startValue == endValue && ((stepValue > 0 && startValue > endValue) || (stepValue < 0 && startValue < endValue))) {
        warning("Error en tiempo de ejecución: bucle infinito detectado en ", "for");
        return;
    }
    if ((stepValue > 0 && startValue > endValue) || (stepValue < 0 && startValue < endValue)) {
        warning("Advertencia: rango vacío del bucle en ", "for");
        return; // O podrías simplemente continuar sin ejecutar el bucle
    }

	for (double i = startValue; (stepValue > 0) ? (i <= endValue) : (i >= endValue); i += stepValue)
	{
		// Crear un nuevo nodo de número para asignar
		lp::NumberNode *numNode = new lp::NumberNode(i);

		// Crear una sentencia de asignación que actualiza la variable de control
		lp::AssignmentStmt *asgn = new lp::AssignmentStmt(_var, numNode);
		asgn->evaluate();  // Esto crea o actualiza la variable correctamente

		// Ejecutar el cuerpo del bucle
		_body->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::SwitchStmt::printAST()
{
  std::cout << "SwitchStmt:" << std::endl;
  
  std::cout << "\tExpression: ";
  this->_expression->printAST();
  
  for (std::list<lp::Case *>::iterator caseIt = this->_cases->begin(); caseIt != this->_cases->end(); ++caseIt) {
    lp::Case *caseItem = *caseIt;
    std::cout << "\tCase value: ";
    caseItem->value->printAST();
    std::cout << "\tCase body: ";
    caseItem->body->printAST();
  }
  
  // The default case is printed if exists
  if (this->_default != NULL)
  {  
    std::cout << "\t";
    this->_default->printAST();
  }
  
  std::cout << std::endl;
}

void lp::SwitchStmt::evaluate()
{
    bool caseMatched = false;
    
    switch(this->_expression->getType()) {
        case NUMBER: {
            double switchValue = this->_expression->evaluateNumber();
            
            for (std::list<lp::Case *>::iterator caseIt = this->_cases->begin(); caseIt != this->_cases->end(); ++caseIt) {
                lp::Case *caseItem = *caseIt;
                if (caseItem->value->getType() == NUMBER) {
                    double caseValue = caseItem->value->evaluateNumber();
                    if (switchValue == caseValue) {
                        caseMatched = true;
                        caseItem->body->evaluate();
                        break;
                    }
                } else {
                    warning("Error en tiempo de ejecución: desajuste de tipo en el valor de 'case' para ", "switch");
                }
            }
            break;
        }
        case STRING: {
            std::string switchValue = this->_expression->evaluateString();
            
            for (std::list<lp::Case *>::iterator caseIt = this->_cases->begin(); caseIt != this->_cases->end(); ++caseIt) {
                lp::Case *caseItem = *caseIt;
                if (caseItem->value->getType() == STRING) {
                    std::string caseValue = caseItem->value->evaluateString();
                    if (switchValue == caseValue) {
                        caseMatched = true;
                        caseItem->body->evaluate();
                        break;
                    }
                } else {
                    warning("Error en tiempo de ejecución: desajuste de tipo en el valor de 'case' para ", "switch");
                }
            }
            break;
        }
        case BOOL: {
            bool switchValue = this->_expression->evaluateBool();
            
            for (std::list<lp::Case *>::iterator caseIt = this->_cases->begin(); caseIt != this->_cases->end(); ++caseIt) {
                lp::Case *caseItem = *caseIt;
                if (caseItem->value->getType() == BOOL) {
                    bool caseValue = caseItem->value->evaluateBool();
                    if (switchValue == caseValue) {
                        caseMatched = true;
                        caseItem->body->evaluate();
                        break;
                    }
                } else {
                    warning("Error en tiempo de ejecución: desajuste de tipo en el valor de 'case' para ", "switch");
                }
            }
            break;
        }
        default:
            warning("Error en tiempo de ejecución: tipo incompatible para ", "switch");
            return;
    }
    
    if (!caseMatched && this->_default != NULL) {
        this->_default->evaluate();
    }
}