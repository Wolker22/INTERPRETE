#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <limits>

// Para usar la funciones pow y std::abs
#include <cmath>
#include <cassert>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

//
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"
#include "../table/stringVariable.hpp"
#include "../table/stringConstant.hpp"
#include "../table/builtinString1Parameter.hpp"

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
	lp::Variable *var = (lp::Variable *)table.getSymbol(this->_id);

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

	if (this->getType() == TYPE_NUMBER)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable *var = (lp::NumericVariable *)table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateNumber(): the variable is not numeric",
				this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::VariableNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == TYPE_BOOL)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable *var = (lp::LogicalVariable *)table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Runtime error in evaluateBool(): the variable is not boolean",
				this->_id);
	}
	// Return the value of the LogicalVariable
	return result;
}

std::string lp::VariableNode::evaluateString()
{
	switch (this->getType())
	{
	case TYPE_STRING:
	{
		lp::StringVariable *var = (lp::StringVariable *)table.getSymbol(this->_id);
		return var->getValue();
	}
	case TYPE_NUMBER:
	{
		lp::NumericVariable *var = (lp::NumericVariable *)table.getSymbol(this->_id);
		std::ostringstream oss;
		oss << var->getValue();
		return oss.str();
	}
	case TYPE_BOOL:
	{
		lp::LogicalVariable *var = (lp::LogicalVariable *)table.getSymbol(this->_id);
		return var->getValue() ? "true" : "false";
	}
	default:
		warning("Runtime error in evaluateString(): incompatible variable type", this->_id);
		return "";
	}
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
	lp::Constant *var = (lp::Constant *)table.getSymbol(this->_id);

	// Return the type of the Constant
	return var->getType();
}

double lp::ConstantNode::evaluateNumber()
{
	double result = 0.0;

	if (this->getType() == TYPE_NUMBER)
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant *constant = (lp::NumericConstant *)table.getSymbol(this->_id);

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		warning("Runtime error in evaluateNumber(): the constant is not numeric",
				this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::ConstantNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == TYPE_BOOL)
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant *constant = (lp::LogicalConstant *)table.getSymbol(this->_id);

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		warning("Runtime error in evaluateBool(): the constant is not boolean",
				this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumberNode::getType()
{
	return TYPE_NUMBER;
}

void lp::NumberNode::printAST()
{
	std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber()
{
	return this->_number;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if (this->_exp->getType() == TYPE_NUMBER)
	{
		result = TYPE_NUMBER;
	}
	else
	{
		warning("Runtime error: incompatible types for", "Numeric Unary Operator");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if (this->_exp->getType() == TYPE_BOOL)
	{
		result = TYPE_BOOL;
	}
	else
	{
		warning("Runtime error: incompatible types for", "Logical Unary Operator");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;

	if ((this->_left->getType() == TYPE_NUMBER) and (this->_right->getType() == TYPE_NUMBER))
		result = TYPE_NUMBER;
	else
		warning("Runtime error: incompatible types for", "Numeric Operator");

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::RelationalOperatorNode::getType()
{
	int result = 0;

	if ((this->_left->getType() == TYPE_NUMBER) and (this->_right->getType() == TYPE_NUMBER))
		result = TYPE_BOOL;
	else if ((this->_left->getType() == TYPE_BOOL) and (this->_right->getType() == TYPE_BOOL))
		result = TYPE_BOOL;
	else if ((this->_left->getType() == TYPE_STRING) and (this->_right->getType() == TYPE_STRING))
		result = TYPE_BOOL;
	else
		warning("Runtime error: incompatible types for", "Relational Operator");

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode::getType()
{
	int result = 0;

	if ((this->_left->getType() == TYPE_BOOL) and (this->_right->getType() == TYPE_BOOL))
	{
		//
		result = TYPE_BOOL;
	}
	else
		warning("Runtime error: incompatible types for", "Logical Operator");

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::UnaryMinusNode::printAST()
{
	std::cout << "UnaryMinusNode: -" << std::endl;
	std::cout << "\t";
	this->_exp->printAST();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == TYPE_NUMBER)
	{
		// Minus
		result = -this->_exp->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "UnaryMinus");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::UnaryPlusNode::printAST()
{
	std::cout << "UnaryPlusNode: +" << std::endl;
	std::cout << "\t";
	this->_exp->printAST();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == TYPE_NUMBER)
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "UnaryPlus");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::printAST()
{
	std::cout << "PlusNode: +" << std::endl;
	std::cout << "\t";
	this->_left->printAST();
	std::cout << "\t";
	this->_right->printAST();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == TYPE_NUMBER)
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Plus");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::printAST()
{
	std::cout << "MinusNode: -" << std::endl;
	std::cout << "\t";
	this->_left->printAST();
	std::cout << "\t";
	this->_right->printAST();
}

double lp::MinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == TYPE_NUMBER)
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Minus");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MultiplicationNode::printAST()
{
	std::cout << "MultiplicationNode: *" << std::endl;
	std::cout << "\t";
	this->_left->printAST();
	std::cout << "\t";
	this->_right->printAST();
}

double lp::MultiplicationNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == TYPE_NUMBER)
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for ", "Multiplication");
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
	if (this->getType() == TYPE_NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		// The divisor is not zero
		if (std::abs(rightNumber) > ERROR_BOUND)
		{
			result = leftNumber / rightNumber;
		}
		else
		{
			warning("Runtime error", "Division by zero");
		}
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Division");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::printAST()
{
	std::cout << "ModuloNode: %" << std::endl;
	std::cout << "\t";
	this->_left->printAST();
	std::cout << "\t";
	this->_right->printAST();
}

double lp::ModuloNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == TYPE_NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		if (std::abs(rightNumber) > ERROR_BOUND)
			result = (int)leftNumber % (int)rightNumber;
		else
			warning("Runtime error", "Division by zero");
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Modulo");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::printAST()
{
	std::cout << "PowerNode: ^" << std::endl;
	std::cout << "\t";
	this->_left->printAST();
	std::cout << "\t";
	this->_right->printAST();
}

double lp::PowerNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == TYPE_NUMBER)
	{
		result = pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Power");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_0::getType()
{
	return TYPE_NUMBER;
}

void lp::BuiltinFunctionNode_0::printAST()
{
	std::cout << "BuiltinFunctionNode_0: " << std::endl;
	std::cout << "\t";
	std::cout << this->_id << std::endl;
}

double lp::BuiltinFunctionNode_0::evaluateNumber()
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *)table.getSymbol(this->_id);

	// Apply the function and copy the result
	return f->getFunction()();
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;

	if (this->_exp->getType() == TYPE_NUMBER)
		result = TYPE_NUMBER;
	else
		warning("Runtime error: incompatible type for", "BuiltinFunctionNode_1");

	return result;
}

void lp::BuiltinFunctionNode_1::printAST()
{
	std::cout << "BuiltinFunctionNode_1: " << std::endl;
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
	if (this->getType() == TYPE_NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *)table.getSymbol(this->_id);

		// Apply the function to the parameter and copy the result
		result = f->getFunction()(this->_exp->evaluateNumber());
	}
	else
	{
		warning("Runtime error: incompatible type of parameter for ", this->_id);
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
		warning("Runtime error: incompatible types for", "BuiltinFunctionNode_2");

	return result;
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
	if (this->getType() == TYPE_NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *)table.getSymbol(this->_id);

		// Apply the function to the parameters and copy the result
		result = f->getFunction()(this->_exp1->evaluateNumber(), this->_exp2->evaluateNumber());
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", this->_id);
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

	if (this->getType() == TYPE_BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber > rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Greater than");
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

	if (this->getType() == TYPE_BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber >= rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Greater or equal than");
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

	if (this->getType() == TYPE_BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber < rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Less than");
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

	if (this->getType() == TYPE_BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber <= rightNumber);
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Less or equal than");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::printAST()
{
	std::cout << "EqualNode: ==" << std::endl;
	std::cout << "\t";
	this->_left->printAST();
	std::cout << "\t";
	this->_right->printAST();
}

bool lp::EqualNode::evaluateBool()
{
	bool result = false;

	if (this->getType() == TYPE_BOOL)
	{
		switch (this->_left->getType())
		{
		case TYPE_NUMBER:
		{
			double leftNumber = this->_left->evaluateNumber();
			double rightNumber = this->_right->evaluateNumber();
			// CORRECCIÓN: Implementación correcta de igualdad numérica
			result = (std::abs(leftNumber - rightNumber) < ERROR_BOUND);
			break;
		}

		case TYPE_BOOL:
		{
			bool leftBoolean, rightBoolean;
			leftBoolean = this->_left->evaluateBool();
			rightBoolean = this->_right->evaluateBool();

			result = (leftBoolean == rightBoolean);
		}
		break;
		case TYPE_STRING:
		{
			std::string leftStr = this->_left->evaluateString();
			std::string rightStr = this->_right->evaluateString();
			result = (leftStr == rightStr);
		}
		break;
		default:
			warning("Runtime error: incompatible types of parameters for ",
					"Equal operator");
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ",
				"Equal operator");
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

	if (this->getType() == TYPE_BOOL)
	{
		switch (this->_left->getType())
		{
		case TYPE_NUMBER:
		{
			double leftNumber = this->_left->evaluateNumber();
			double rightNumber = this->_right->evaluateNumber();
			result = (leftNumber != rightNumber); // comparación exacta
			break;
		}

		break;
		case TYPE_BOOL:
		{
			bool leftBoolean, rightBoolean;
			leftBoolean = this->_left->evaluateBool();
			rightBoolean = this->_right->evaluateBool();
			result = (leftBoolean != rightBoolean);
		}
		break;
		case TYPE_STRING:
		{
			std::string leftStr = this->_left->evaluateString();
			std::string rightStr = this->_right->evaluateString();
			result = (leftStr != rightStr);
		}
		break;
		default:
			warning("Runtime error: incompatible types of parameters for ",
					"Not Equal operator");
		}
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "Not Equal operator");
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

	if (this->getType() == TYPE_BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool and rightBool;
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator And");
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

	if (this->getType() == TYPE_BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool or rightBool;
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Or");
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

	if (this->getType() == TYPE_BOOL)
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		warning("Runtime error: incompatible types of parameters for ", "operator Not");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::printAST()
{
	std::cout << "assignment_node: =" << std::endl;
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
	lp::Variable *firstVar = (lp::Variable *)table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch (this->_exp->getType())
		{
		case TYPE_NUMBER:
		{
			double value;
			// evaluate the expression as TYPE_NUMBER
			value = this->_exp->evaluateNumber();

			// Check the type of the first varible
			if (firstVar->getType() == TYPE_NUMBER)
			{
				// Get the identifier in the table of symbols as NumericVariable
				lp::NumericVariable *v = (lp::NumericVariable *)table.getSymbol(this->_id);

				// Assignment the value to the identifier in the table of symbols
				v->setValue(value);
			}
			// The type of variable is not TYPE_NUMBER
			else
			{
				// Delete the variable from the table of symbols
				table.eraseSymbol(this->_id);

				// Insert the variable in the table of symbols as NumericVariable
				// with the type TYPE_NUMBER and the value
				lp::NumericVariable *v = new lp::NumericVariable(this->_id,
																 VARIABLE, TYPE_NUMBER, value);
				table.installSymbol(v);
			}
		}
		break;

		case TYPE_BOOL:
		{
			bool value;
			// evaluate the expression as TYPE_BOOL
			value = this->_exp->evaluateBool();

			if (firstVar->getType() == TYPE_BOOL)
			{
				// Get the identifier in the table of symbols as LogicalVariable
				lp::LogicalVariable *v = (lp::LogicalVariable *)table.getSymbol(this->_id);

				// Assignment the value to the identifier in the table of symbols
				v->setValue(value);
			}
			// The type of variable is not TYPE_BOOL
			else
			{
				// Delete the variable from the table of symbols
				table.eraseSymbol(this->_id);

				// Insert the variable in the table of symbols as NumericVariable
				// with the type TYPE_BOOL and the value
				lp::LogicalVariable *v = new lp::LogicalVariable(this->_id,
																 VARIABLE, TYPE_BOOL, value);
				table.installSymbol(v);
			}
		}

		break;

		case TYPE_STRING:
		{
			std::string value = this->_exp->evaluateString();

			if (firstVar->getType() == TYPE_STRING)
			{
				lp::StringVariable *v = (lp::StringVariable *)table.getSymbol(this->_id);
				v->setValue(value);
			}
			else
			{
				table.eraseSymbol(this->_id);
				lp::StringVariable *v = new lp::StringVariable(this->_id,
															   VARIABLE, TYPE_STRING, value);
				table.installSymbol(v);
			}
		}
		break;

		default:
			warning("Runtime error: incompatible type of expression for ", "Assigment");
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
		lp::Variable *secondVar = (lp::Variable *)table.getSymbol(this->_asgn->_id);

		// Get the type of the variable of the previous asgn
		switch (secondVar->getType())
		{
		case TYPE_NUMBER:
		{
			/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
			lp::NumericVariable *secondVar = (lp::NumericVariable *)table.getSymbol(this->_asgn->_id);
			// Check the type of the first variable
			if (firstVar->getType() == TYPE_NUMBER)
			{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::NumericVariable *firstVar = (lp::NumericVariable *)table.getSymbol(this->_id);
				// Get the identifier o f the in the table of symbols as NumericVariable
				//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

				// Assignment the value of the second variable to the first variable
				firstVar->setValue(secondVar->getValue());
			}
			// The type of variable is not TYPE_NUMBER
			else
			{
				// Delete the first variable from the table of symbols
				table.eraseSymbol(this->_id);

				// Insert the first variable in the table of symbols as NumericVariable
				// with the type TYPE_NUMBER and the value of the previous variable
				lp::NumericVariable *firstVar = new lp::NumericVariable(this->_id,
																		VARIABLE, TYPE_NUMBER, secondVar->getValue());
				table.installSymbol(firstVar);
			}
		}
		break;

		case TYPE_BOOL:
		{
			/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
			lp::LogicalVariable *secondVar = (lp::LogicalVariable *)table.getSymbol(this->_asgn->_id);
			// Check the type of the first variable
			if (firstVar->getType() == TYPE_BOOL)
			{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::LogicalVariable *firstVar = (lp::LogicalVariable *)table.getSymbol(this->_id);
				// Get the identifier o f the in the table of symbols as NumericVariable
				//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

				// Assignment the value of the second variable to the first variable
				firstVar->setValue(secondVar->getValue());
			}
			// The type of variable is not TYPE_BOOL
			else
			{
				// Delete the first variable from the table of symbols
				table.eraseSymbol(this->_id);

				// Insert the first variable in the table of symbols as NumericVariable
				// with the type TYPE_BOOL and the value of the previous variable
				lp::LogicalVariable *firstVar = new lp::LogicalVariable(this->_id,
																		VARIABLE, TYPE_BOOL, secondVar->getValue());
				table.installSymbol(firstVar);
			}
		}
		break;

		case TYPE_STRING:
		{
			lp::StringVariable *secondVar = (lp::StringVariable *)table.getSymbol(this->_asgn->_id);

			if (firstVar->getType() == TYPE_STRING)
			{
				lp::StringVariable *firstVar = (lp::StringVariable *)table.getSymbol(this->_id);
				firstVar->setValue(secondVar->getValue());
			}
			else
			{
				table.eraseSymbol(this->_id);
				lp::StringVariable *firstVar = new lp::StringVariable(this->_id,
																	  VARIABLE, TYPE_STRING, secondVar->getValue());
				table.installSymbol(firstVar);
			}
		}
		break;

		default:
			warning("Runtime error: incompatible type of expression for ", "Assigment");
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::printAST()
{
	std::cout << "printASTStmt: printAST" << std::endl;
	std::cout << "\t";
	this->_exp->printAST();
	std::cout << std::endl;
}

void lp::PrintStmt::evaluate()
{
	switch (this->_exp->getType())
	{
	case TYPE_NUMBER:
		std::cout << this->_exp->evaluateNumber() << std::endl;
		break;
	case TYPE_BOOL:
		if (this->_exp->evaluateBool())
			std::cout << "true" << std::endl;
		else
			std::cout << "false" << std::endl;
		break;
	case TYPE_STRING:
		std::cout << this->_exp->evaluateString() << std::endl;
		break;
	default:
		warning("Runtime error: incompatible type for ", "print");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::printAST()
{
	std::cout << "ReadStmt: read" << std::endl;
	std::cout << "\t";
	std::cout << this->_id;
	std::cout << std::endl;
}

void lp::ReadStmt::evaluate()
{
	double value;

	std::cout << BIYELLOW;
	std::cout << "Insert a numeric value --> ";
	std::cout << RESET;

	// Solo limpiar si hay un salto de línea pendiente
	if (std::cin.peek() == '\n')
		std::cin.ignore();

	std::cin >> value;

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *)table.getSymbol(this->_id);

	if (var->getType() == TYPE_NUMBER)
	{
		lp::NumericVariable *n = (lp::NumericVariable *)var;
		n->setValue(value);
	}
	else
	{
		table.eraseSymbol(this->_id);
		lp::NumericVariable *n = new lp::NumericVariable(this->_id, VARIABLE, TYPE_NUMBER, value);
		table.installSymbol(n);
	}
}

////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
//////

void lp::PrintStringStmt::printAST()
{
	std::cout << "printStringStmt: print" << std::endl;
	std::cout << "\t";
	_exp->printAST();
	std::cout << std::endl;
}

void lp::PrintStringStmt::evaluate()
{
	std::cout << _exp->evaluateString() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
//////

void lp::ReadStringStmt::printAST()
{
	std::cout << "ReadStringStmt: read" << std::endl;
	std::cout << "\t" << _id << std::endl;
}

void lp::ReadStringStmt::evaluate()
{
    std::string input;

    std::cout << BIYELLOW;
    std::cout << "Insert a string value --> ";
    std::cout << RESET;

    // Solo limpiar si hay un salto de línea pendiente
    if (std::cin.peek() == '\n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::getline(std::cin, input);

    // Obtener variable
    lp::Variable *var = (lp::Variable *)table.getSymbol(this->_id);

    if (var != NULL && var->getType() == TYPE_STRING) {
        lp::StringVariable *s = (lp::StringVariable *)var;
        s->setValue(input);
    } else {
        if (var != NULL) {
            table.eraseSymbol(this->_id);
        }
        lp::StringVariable *s = new lp::StringVariable(this->_id, VARIABLE, TYPE_STRING, input);
        table.installSymbol(s);
    }
}

////////////////////////////////////////////////////////////////////////////////
//////
////////////////////////////////////////////////////////////////////////////////
//////

void lp::AssignmentStmtStringNode::printAST()
{
	std::cout << "assignment_string_node: =" << std::endl;
	std::cout << "\t" << this->_id << std::endl;
	std::cout << "\t";
	if (_exp)
		_exp->printAST();
	std::cout << std::endl;
}

void lp::AssignmentStmtStringNode::evaluate()
{
	std::string value = _exp->evaluateString();

	lp::Variable *var = (lp::Variable *)table.getSymbol(this->_id);
	if (var->getType() == TYPE_STRING)
	{
		lp::StringVariable *s = (lp::StringVariable *)table.getSymbol(this->_id);
		s->setValue(value);
	}
	else
	{
		table.eraseSymbol(this->_id);
		lp::StringVariable *s = new lp::StringVariable(this->_id, VARIABLE, TYPE_STRING, value);
		table.installSymbol(s);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::printAST()
{
	std::cout << "EmptyStmt " << std::endl;
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
	std::cout << "IfStmt: " << std::endl;
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
	// If the condition is true,
	if (this->_cond->evaluateBool() == true)
		// the consequent is run
		this->_stmt1->evaluate();

	// Otherwise, the alternative is run if exists
	else if (this->_stmt2 != NULL)
		this->_stmt2->evaluate();
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::WhileStmt::printAST()
{
	std::cout << "WhileStmt: " << std::endl;
	// Condition
	std::cout << "\t";
	this->_cond->printAST();

	// Body of the while loop
	std::cout << "\t";
	this->_stmt->printAST();

	std::cout << std::endl;
}

void lp::WhileStmt::evaluate()
{
	// While the condition is true. the body is run
	while (this->_cond->evaluateBool() == true)
	{
		this->_stmt->evaluate();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BlockStmt::printAST()
{
	std::list<Statement *>::iterator stmtIter;

	std::cout << "BlockStmt: " << std::endl;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
	{
		(*stmtIter)->printAST();
	}
}

void lp::BlockStmt::evaluate()
{
	std::list<Statement *>::iterator stmtIter;

	for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++)
	{
		(*stmtIter)->evaluate();
	}
}

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

// ====================
// TYPE_STRING CONSTANT NODE
// ====================
std::string lp::StringNode::evaluateString()
{
	return _value;
}

void lp::StringNode::printAST()
{
	std::cout << _value;
}

// ====================
// TYPE_STRING VARIABLE NODE
// ====================
std::string lp::StringVariableNode::evaluateString()
{
	lp::Symbol *symbol = table.getSymbol(_id);
	if (symbol == NULL)
		return "";

	lp::StringVariable *var = dynamic_cast<lp::StringVariable *>(symbol);
	if (var)
		return var->getValue();

	lp::NumericVariable *nvar = dynamic_cast<lp::NumericVariable *>(symbol);
	if (nvar)
	{
		std::ostringstream oss;
		oss << nvar->getValue();
		return oss.str();
	}

	lp::LogicalVariable *bvar = dynamic_cast<lp::LogicalVariable *>(symbol);
	if (bvar)
		return bvar->getValue() ? "true" : "false";

	return "";
}

void lp::StringVariableNode::printAST()
{
	std::cout << evaluateString();
}

// ====================
// BUILTIN TYPE_STRING FUNC (1 param)
// ====================
std::string lp::BuiltinStringFunctionNode_1::evaluateString()
{
	std::string s = _exp->evaluateString();

	lp::Symbol *symbol = table.getSymbol(_id);
	assert(symbol != NULL);

	lp::BuiltinString1Parameter *f = dynamic_cast<lp::BuiltinString1Parameter *>(symbol);
	assert(f != NULL);

	lp::TypePointerStringFunction_1 fun = f->getFunction();
	assert(fun != NULL);

	return fun(s);
}

void lp::BuiltinStringFunctionNode_1::printAST()
{
	std::cout << evaluateString();
}

// ====================
// TYPE_STRING CONCATENATION
// ====================
std::string lp::ConcatNode::evaluateString()
{
	std::string left = _left->evaluateString();
	std::string right = _right->evaluateString();

	return left + right;
}

void lp::ConcatNode::printAST()
{
	std::cout << "ConcatNode: ||" << std::endl;
	std::cout << "\t";
	_left->printAST();
	std::cout << std::endl
			  << "\t";
	_right->printAST();
}

////////////////////////////////////////////////////////////////////////////////
//////
// CLEAR_SCREEN STATEMENT
////////////////////////////////////////////////////////////////////////////////
void lp::ClearScreenStmt::printAST()
{
	std::cout << "clear_screen" << std::endl;
}

void lp::ClearScreenStmt::evaluate()
{
	std::cout << CLEAR_SCREEN_SEQ;
	PLACE_CURSOR(1, 1);
}

////////////////////////////////////////////////////////////////////////////////
//////
// PLACE CURSOR STATEMENT
////////////////////////////////////////////////////////////////////////////////
void lp::PlaceStmt::printAST()
{
	std::cout << "place" << std::endl;
}

void lp::PlaceStmt::evaluate()
{
	int r = static_cast<int>(_row->evaluateNumber());
	int c = static_cast<int>(_col->evaluateNumber());
	PLACE_CURSOR(r, c);
}

////////////////////////////////////////////////////////////////////////////////
//////
// REPEAT STATEMENT
////////////////////////////////////////////////////////////////////////////////
void lp::RepeatStmt::printAST()
{
	std::cout << "repeat" << std::endl;
}

void lp::RepeatStmt::evaluate()
{
	do
	{
		_body->evaluate();
	} while (!_cond->evaluateBool());
}

////////////////////////////////////////////////////////////////////////////////
//////
// FOR STATEMENT
////////////////////////////////////////////////////////////////////////////////
void lp::ForStmt::printAST()
{
	std::cout << "for" << std::endl;
}

void lp::ForStmt::evaluate()
{
	double start = _start->evaluateNumber();
	double end = _end->evaluateNumber();
	double step = _step ? _step->evaluateNumber() : 1.0;

	lp::Variable *var = (lp::Variable *)table.getSymbol(_id);
	if (!var || var->getType() != TYPE_NUMBER)
	{
		table.eraseSymbol(_id);
		lp::NumericVariable *n = new lp::NumericVariable(_id, VARIABLE, TYPE_NUMBER, start);
		table.installSymbol(n);
		var = n;
	}
	else
	{
		((lp::NumericVariable *)var)->setValue(start);
	}

	while ((step >= 0 && ((lp::NumericVariable *)table.getSymbol(_id))->getValue() <= end) ||
		   (step < 0 && ((lp::NumericVariable *)table.getSymbol(_id))->getValue() >= end))
	{
		_body->evaluate();
		double v = ((lp::NumericVariable *)table.getSymbol(_id))->getValue() + step;
		((lp::NumericVariable *)table.getSymbol(_id))->setValue(v);
	}
}

////////////////////////////////////////////////////////////////////////////////
//////
// SWITCH STATEMENT
////////////////////////////////////////////////////////////////////////////////
void lp::SwitchStmt::printAST()
{
	std::cout << "switch" << std::endl;
}

void lp::SwitchStmt::evaluate()
{
	double key = _exp->evaluateNumber();
	bool executed = false;

	for (std::list<SwitchCase *>::iterator it = _cases->begin(); it != _cases->end(); ++it)
	{
		SwitchCase *c = *it;
		if (c->cond == NULL)
		{
			if (!executed)
				c->stmt->evaluate();
		}
		else if (!executed && c->cond->evaluateNumber() == key)
		{
			c->stmt->evaluate();
			executed = true;
		}
	}
}

void lp::IntDivNode::printAST()
{
	std::cout << "IntDivNode: //" << std::endl;
	std::cout << "\t";
	this->_left->printAST();
	std::cout << "\t";
	this->_right->printAST();
}

double lp::IntDivNode::evaluateNumber()
{
	double result = 0.0;

	// Check the type of the expressions
	if (this->getType() == TYPE_NUMBER)
	{
		double leftNumber = this->_left->evaluateNumber();
		double rightNumber = this->_right->evaluateNumber();

		if (static_cast<int>(rightNumber) != 0)
		{
			result = static_cast<int>(leftNumber) / static_cast<int>(rightNumber);
		}
		else
		{
			warning("Runtime error", "Integer division by zero");
		}
	}
	else
	{
		warning("Runtime error: the expressions are not numeric for", "Integer Division");
	}

	return result;
}
