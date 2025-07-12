#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <limits>
#include <cmath>
#include <cassert>
#include <cctype>
#include <algorithm>
#include "ast.hpp"
#include "../table/table.hpp"
#include "../error/error.hpp"
#include "../includes/macros.hpp"
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"
#include "../parser/interpreter.tab.h"

namespace lp
{
    bool approximatelyEqual(double a, double b)
    {
        return std::abs(a - b) <= ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * ERROR_BOUND);
    }
    
    // Función toLower para manejo de nombres de símbolos
    inline std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c){ return std::tolower(c); });
        return result;
    }
}

extern lp::Table table;
extern lp::AST *root;

////////////////////////////////////////////////////////////////////////////////
// VariableNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType()
{
    lp::Symbol* symbol = table.getSymbol(this->_id);
    if (symbol == nullptr) {
        warning("Undefined variable", this->_id);
        return UNKNOWN;
    }
    return symbol->getType();
}

void lp::VariableNode::printAST()
{
    std::cout << "VariableNode: " << this->_id;
    std::cout << " (Type: " << this->getType() << ")" << std::endl;
}

double lp::VariableNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expected numeric variable", this->_id);
        return 0.0;
    }
    lp::NumericVariable *var = (lp::NumericVariable *)table.getSymbol(this->_id);
    return var->getValue();
}

bool lp::VariableNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: expected boolean variable", this->_id);
        return false;
    }
    lp::LogicalVariable *var = (lp::LogicalVariable *)table.getSymbol(this->_id);
    return var->getValue();
}

std::string lp::VariableNode::evaluateString()
{
    if (this->getType() != STRING)
    {
        warning("Runtime error: expected string variable", this->_id);
        return "";
    }
    lp::StringVariable *var = (lp::StringVariable *)table.getSymbol(this->_id);
    return var->getValue();
}

////////////////////////////////////////////////////////////////////////////////
// ConstantNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::ConstantNode::getType()
{
    lp::Symbol* symbol = table.getSymbol(this->_id);
    if (symbol == nullptr) {
        warning("Undefined constant", this->_id);
        return UNKNOWN;
    }
    return symbol->getType();
}

void lp::ConstantNode::printAST()
{
    std::cout << "ConstantNode: " << this->_id;
    std::cout << " (Type: " << this->getType() << ")" << std::endl;
}

double lp::ConstantNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expected numeric constant", this->_id);
        return 0.0;
    }
    lp::NumericConstant *constant = (lp::NumericConstant *)table.getSymbol(this->_id);
    return constant->getValue();
}

bool lp::ConstantNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: expected boolean constant", this->_id);
        return false;
    }
    lp::LogicalConstant *constant = (lp::LogicalConstant *)table.getSymbol(this->_id);
    return constant->getValue();
}

std::string lp::ConstantNode::evaluateString()
{
    if (this->getType() != STRING)
    {
        warning("Runtime error: expected string constant", this->_id);
        return "";
    }
    lp::StringConstant *constant = (lp::StringConstant *)table.getSymbol(this->_id);
    return constant->getValue();
}

////////////////////////////////////////////////////////////////////////////////
// NumberNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::NumberNode::getType() { return NUMBER; }
void lp::NumberNode::printAST() { std::cout << "NumberNode: " << this->_number << std::endl; }
double lp::NumberNode::evaluateNumber() { return this->_number; }

////////////////////////////////////////////////////////////////////////////////
// StringNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::StringNode::getType() { return STRING; }
void lp::StringNode::printAST() { std::cout << "StringNode: " << this->_string << std::endl; }
std::string lp::StringNode::evaluateString() { return this->_string; }

////////////////////////////////////////////////////////////////////////////////
// NumericUnaryOperatorNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::NumericUnaryOperatorNode::getType()
{
    if (this->_exp->getType() == NUMBER)
        return NUMBER;
    warning("Runtime error: incompatible types for", "Numeric Unary Operator");
    return UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////
// LogicalUnaryOperatorNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
    if (this->_exp->getType() == BOOL)
        return BOOL;
    warning("Runtime error: incompatible types for", "Logical Unary Operator");
    return UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////
// NumericOperatorNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
    if ((this->_left->getType() == NUMBER) && (this->_right->getType() == NUMBER))
        return NUMBER;
    warning("Runtime error: incompatible types for", "Numeric Operator");
    return UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////
// RelationalOperatorNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::RelationalOperatorNode::getType()
{
    if ((this->_left->getType() == NUMBER) && (this->_right->getType() == NUMBER))
        return BOOL;
    if ((this->_left->getType() == BOOL) && (this->_right->getType() == BOOL))
        return BOOL;
    if ((this->_left->getType() == STRING) && (this->_right->getType() == STRING))
        return BOOL;
    warning("Runtime error: incompatible types for", "Relational Operator");
    return UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////
// LogicalOperatorNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode::getType()
{
    if ((this->_left->getType() == BOOL) && (this->_right->getType() == BOOL))
        return BOOL;
    warning("Runtime error: incompatible types for", "Logical Operator");
    return UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////
// AlphanumericOperatorNode Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::AlphanumericOperatorNode::getType()
{
    if ((this->_left->getType() == STRING) && (this->_right->getType() == STRING))
        return STRING;
    warning("Runtime error: incompatible types for", "Alphanumeric Operator");
    return UNKNOWN;
}

////////////////////////////////////////////////////////////////////////////////
// ConcatenationNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::ConcatenationNode::printAST()
{
    std::cout << "ConcatenationNode: ||" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

std::string lp::ConcatenationNode::evaluateString()
{
    if (this->getType() != STRING)
    {
        warning("Runtime error: expressions not alphanumeric", "Concatenation");
        return "";
    }
    return this->_left->evaluateString() + this->_right->evaluateString();
}

////////////////////////////////////////////////////////////////////////////////
// UnaryMinusNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::UnaryMinusNode::printAST()
{
    std::cout << "UnaryMinusNode: -" << std::endl;
    this->_exp->printAST();
}

double lp::UnaryMinusNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expression not numeric", "UnaryMinus");
        return 0.0;
    }
    return -this->_exp->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// UnaryPlusNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::UnaryPlusNode::printAST()
{
    std::cout << "UnaryPlusNode: +" << std::endl;
    this->_exp->printAST();
}

double lp::UnaryPlusNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expression not numeric", "UnaryPlus");
        return 0.0;
    }
    return this->_exp->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// PlusNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::printAST()
{
    std::cout << "PlusNode: +" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

double lp::PlusNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Plus");
        return 0.0;
    }
    return this->_left->evaluateNumber() + this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// MinusNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::printAST()
{
    std::cout << "MinusNode: -" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

double lp::MinusNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Minus");
        return 0.0;
    }
    return this->_left->evaluateNumber() - this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// MultiplicationNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::MultiplicationNode::printAST()
{
    std::cout << "MultiplicationNode: *" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

double lp::MultiplicationNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Multiplication");
        return 0.0;
    }
    return this->_left->evaluateNumber() * this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// DivisionNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::printAST()
{
    std::cout << "DivisionNode: /" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

double lp::DivisionNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Division");
        return 0.0;
    }

    double denominator = this->_right->evaluateNumber();
    if (std::abs(denominator) < ERROR_BOUND)
    {
        warning("Runtime error", "Division by zero");
        return std::numeric_limits<double>::infinity();
    }
    return this->_left->evaluateNumber() / denominator;
}

////////////////////////////////////////////////////////////////////////////////
// IntDivNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::IntDivNode::printAST()
{
    std::cout << "IntDivNode: //" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

double lp::IntDivNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Integer Division");
        return 0.0;
    }

    int denominator = static_cast<int>(this->_right->evaluateNumber());
    if (denominator == 0)
    {
        warning("Runtime error", "Integer division by zero");
        return 0;
    }
    return static_cast<int>(this->_left->evaluateNumber()) / denominator;
}

////////////////////////////////////////////////////////////////////////////////
// ModuloNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::printAST()
{
    std::cout << "ModuloNode: %" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

double lp::ModuloNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Modulo");
        return 0.0;
    }

    int denominator = static_cast<int>(this->_right->evaluateNumber());
    if (denominator == 0)
    {
        warning("Runtime error", "Modulo by zero");
        return 0;
    }
    return static_cast<int>(this->_left->evaluateNumber()) % denominator;
}

////////////////////////////////////////////////////////////////////////////////
// PowerNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::printAST()
{
    std::cout << "PowerNode: ^" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

double lp::PowerNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Power");
        return 0.0;
    }
    return pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
}

////////////////////////////////////////////////////////////////////////////////
// AlternativeNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::AlternativeNode::printAST()
{
    std::cout << "AlternativeNode: ?" << std::endl;
    this->_cond->printAST();
    this->_left->printAST();
    this->_right->printAST();
}

double lp::AlternativeNode::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: expressions not numeric", "Alternative");
        return 0.0;
    }

    if (this->_cond->getType() != BOOL)
    {
        warning("Runtime error: condition not boolean", "Alternative");
        return 0.0;
    }

    return this->_cond->evaluateBool()
               ? this->_left->evaluateNumber()
               : this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// BuiltinFunctionNode_0 Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_0::getType() { return NUMBER; }

void lp::BuiltinFunctionNode_0::printAST()
{
    std::cout << "BuiltinFunctionNode_0: " << this->_id << std::endl;
}

double lp::BuiltinFunctionNode_0::evaluateNumber()
{
    lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *)table.getSymbol(this->_id);
    return f->getFunction()();
}

////////////////////////////////////////////////////////////////////////////////
// BuiltinFunctionNode_1 Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
    if (this->_exp->getType() == NUMBER)
        return NUMBER;
    warning("Runtime error: incompatible type for", "BuiltinFunctionNode_1");
    return UNKNOWN;
}

void lp::BuiltinFunctionNode_1::printAST()
{
    std::cout << "BuiltinFunctionNode_1: " << this->_id << std::endl;
    this->_exp->printAST();
}

double lp::BuiltinFunctionNode_1::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: incompatible parameter type", this->_id);
        return 0.0;
    }
    lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *)table.getSymbol(this->_id);
    return f->getFunction()(this->_exp->evaluateNumber());
}

////////////////////////////////////////////////////////////////////////////////
// BuiltinFunctionNode_2 Implementation
////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
    if (this->_exp1->getType() == this->_exp2->getType())
        return this->_exp1->getType();
    warning("Runtime error: incompatible types for", "BuiltinFunctionNode_2");
    return UNKNOWN;
}

void lp::BuiltinFunctionNode_2::printAST()
{
    std::cout << "BuiltinFunctionNode_2: " << this->_id << std::endl;
    this->_exp1->printAST();
    this->_exp2->printAST();
}

double lp::BuiltinFunctionNode_2::evaluateNumber()
{
    if (this->getType() != NUMBER)
    {
        warning("Runtime error: incompatible parameter types", this->_id);
        return 0.0;
    }
    lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *)table.getSymbol(this->_id);
    return f->getFunction()(this->_exp1->evaluateNumber(), this->_exp2->evaluateNumber());
}

////////////////////////////////////////////////////////////////////////////////
// GreaterThanNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::printAST()
{
    std::cout << "GreaterThanNode: >" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::GreaterThanNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "operator Greater than");
        return false;
    }
    return this->_left->evaluateNumber() > this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// GreaterOrEqualNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::printAST()
{
    std::cout << "GreaterOrEqualNode: >= " << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::GreaterOrEqualNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "operator Greater or equal than");
        return false;
    }
    return this->_left->evaluateNumber() >= this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// LessThanNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::printAST()
{
    std::cout << "LessThanNode: <" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::LessThanNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "operator Less than");
        return false;
    }
    return this->_left->evaluateNumber() < this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// LessOrEqualNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::printAST()
{
    std::cout << "LessOrEqualNode: <=" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::LessOrEqualNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "operator Less or equal than");
        return false;
    }
    return this->_left->evaluateNumber() <= this->_right->evaluateNumber();
}

////////////////////////////////////////////////////////////////////////////////
// EqualNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::printAST()
{
    std::cout << "EqualNode: ==" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::EqualNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "Equal operator");
        return false;
    }

    switch (this->_left->getType())
    {
    case NUMBER:
        return lp::approximatelyEqual(
            this->_left->evaluateNumber(),
            this->_right->evaluateNumber());
    case BOOL:
        return this->_left->evaluateBool() == this->_right->evaluateBool();
    case STRING:
        return this->_left->evaluateString() == this->_right->evaluateString();
    default:
        warning("Runtime error: incompatible types", "Equal operator");
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////
// NotEqualNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::printAST()
{
    std::cout << "NotEqualNode: !=" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::NotEqualNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "Not Equal operator");
        return false;
    }

    switch (this->_left->getType())
    {
    case NUMBER:
        return !lp::approximatelyEqual(
            this->_left->evaluateNumber(),
            this->_right->evaluateNumber());
    case BOOL:
        return this->_left->evaluateBool() != this->_right->evaluateBool();
    case STRING:
        return this->_left->evaluateString() != this->_right->evaluateString();
    default:
        warning("Runtime error: incompatible types", "Not Equal operator");
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////
// AndNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::printAST()
{
    std::cout << "AndNode: &&" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::AndNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "operator And");
        return false;
    }
    return this->_left->evaluateBool() && this->_right->evaluateBool();
}

////////////////////////////////////////////////////////////////////////////////
// OrNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::printAST()
{
    std::cout << "OrNode: ||" << std::endl;
    this->_left->printAST();
    this->_right->printAST();
}

bool lp::OrNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "operator Or");
        return false;
    }
    return this->_left->evaluateBool() || this->_right->evaluateBool();
}

////////////////////////////////////////////////////////////////////////////////
// NotNode Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::printAST()
{
    std::cout << "NotNode: !" << std::endl;
    this->_exp->printAST();
}

bool lp::NotNode::evaluateBool()
{
    if (this->getType() != BOOL)
    {
        warning("Runtime error: incompatible types", "operator Not");
        return false;
    }
    return !this->_exp->evaluateBool();
}

////////////////////////////////////////////////////////////////////////////////
// AssignmentStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::printAST()
{
    std::cout << "assignment_node: =" << std::endl;
    std::cout << "\t" << this->_id << std::endl;
    if (this->_exp)
        this->_exp->printAST();
    else if (this->_asgn)
        this->_asgn->printAST();
}

void lp::AssignmentStmt::evaluate()
{
    lp::Variable *var = (lp::Variable *)table.getSymbol(this->_id);
    int varType = var ? var->getType() : UNKNOWN;

    if (this->_exp)
    {
        int expType = this->_exp->getType();
        if (varType != expType)
        {
            if (var)
                table.eraseSymbol(this->_id);
            var = nullptr;
        }

        switch (expType)
        {
        case NUMBER:
        {
            double value = this->_exp->evaluateNumber();
            if (!var)
            {
                var = new lp::NumericVariable(this->_id, VARIABLE, NUMBER, value);
                table.installSymbol(var);
            }
            else
            {
                ((lp::NumericVariable *)var)->setValue(value);
            }
            break;
        }
        case BOOL:
        {
            bool value = this->_exp->evaluateBool();
            if (!var)
            {
                var = new lp::LogicalVariable(this->_id, VARIABLE, BOOL, value);
                table.installSymbol(var);
            }
            else
            {
                ((lp::LogicalVariable *)var)->setValue(value);
            }
            break;
        }
        case STRING:
        {
            std::string value = this->_exp->evaluateString();
            if (!var)
            {
                var = new lp::StringVariable(this->_id, VARIABLE, STRING, value);
                table.installSymbol(var);
            }
            else
            {
                ((lp::StringVariable *)var)->setValue(value);
            }
            break;
        }
        default:
            warning("Runtime error: incompatible type", "Assignment");
        }
    }
    else if (this->_asgn)
    {
        this->_asgn->evaluate();
        lp::Variable *srcVar = (lp::Variable *)table.getSymbol(this->_asgn->_id);

        if (!srcVar)
        {
            warning("Runtime error: undefined variable", this->_asgn->_id);
            return;
        }

        int srcType = srcVar->getType();
        if (varType != srcType)
        {
            if (var)
                table.eraseSymbol(this->_id);
            var = nullptr;
        }

        switch (srcType)
        {
        case NUMBER:
        {
            double value = ((lp::NumericVariable *)srcVar)->getValue();
            if (!var)
            {
                var = new lp::NumericVariable(this->_id, VARIABLE, NUMBER, value);
                table.installSymbol(var);
            }
            else
            {
                ((lp::NumericVariable *)var)->setValue(value);
            }
            break;
        }
        case BOOL:
        {
            bool value = ((lp::LogicalVariable *)srcVar)->getValue();
            if (!var)
            {
                var = new lp::LogicalVariable(this->_id, VARIABLE, BOOL, value);
                table.installSymbol(var);
            }
            else
            {
                ((lp::LogicalVariable *)var)->setValue(value);
            }
            break;
        }
        case STRING:
        {
            std::string value = ((lp::StringVariable *)srcVar)->getValue();
            if (!var)
            {
                var = new lp::StringVariable(this->_id, VARIABLE, STRING, value);
                table.installSymbol(var);
            }
            else
            {
                ((lp::StringVariable *)var)->setValue(value);
            }
            break;
        }
        default:
            warning("Runtime error: incompatible type", "Assignment");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// PrintStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::printAST()
{
    std::cout << "printASTStmt: printAST" << std::endl;
    this->_exp->printAST();
}

void lp::PrintStmt::evaluate()
{
    switch (this->_exp->getType())
    {
    case NUMBER:
        std::cout << this->_exp->evaluateNumber() << std::endl;
        break;
    case BOOL:
        std::cout << (this->_exp->evaluateBool() ? "true" : "false") << std::endl;
        break;
    case STRING:
        std::cout << this->_exp->evaluateString() << std::endl;
        break;
    default:
        warning("Runtime error: incompatible type", "print");
    }
}

////////////////////////////////////////////////////////////////////////////////
// ReadStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::printAST()
{
    std::cout << "ReadStmt: read" << std::endl;
    std::cout << "\t" << this->_id << std::endl;
}

void lp::ReadStmt::evaluate()
{
    if (std::cin.peek() == '\n')
        std::cin.ignore();

    double value;
    if (!(std::cin >> value))
    {
        warning("Runtime error: invalid numeric input", this->_id);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    lp::Variable *var = table.getSymbol(this->_id);
    if (var && var->getType() == NUMBER)
    {
        ((lp::NumericVariable *)var)->setValue(value);
    }
    else
    {
        if (var)
            table.eraseSymbol(this->_id);
        table.installSymbol(new lp::NumericVariable(this->_id, VARIABLE, NUMBER, value));
    }
}

////////////////////////////////////////////////////////////////////////////////
// PrintStringStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::PrintStringStmt::printAST()
{
    std::cout << "printStringStmt: print" << std::endl;
    _exp->printAST();
}

void lp::PrintStringStmt::evaluate()
{
    std::cout << _exp->evaluateString() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// ReadStringStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::ReadStringStmt::printAST()
{
    std::cout << "ReadStringStmt: read" << std::endl;
    std::cout << "\t" << _id << std::endl;
}

void lp::ReadStringStmt::evaluate()
{
    if (std::cin.peek() == '\n')
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string input;
    std::getline(std::cin, input);

    lp::Variable *var = table.getSymbol(this->_id);
    if (var && var->getType() == STRING)
    {
        ((lp::StringVariable *)var)->setValue(input);
    }
    else
    {
        if (var)
            table.eraseSymbol(this->_id);
        table.installSymbol(new lp::StringVariable(this->_id, VARIABLE, STRING, input));
    }
}

////////////////////////////////////////////////////////////////////////////////
// EmptyStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::printAST() { std::cout << "EmptyStmt" << std::endl; }
void lp::EmptyStmt::evaluate() { /* Do nothing */ }

////////////////////////////////////////////////////////////////////////////////
// IfStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::IfStmt::printAST()
{
    std::cout << "IfStmt: " << std::endl;
    this->_cond->printAST();
    this->_stmt1->printAST();
    if (this->_stmt2)
        this->_stmt2->printAST();
}

void lp::IfStmt::evaluate()
{
    if (this->_cond->evaluateBool())
    {
        this->_stmt1->evaluate();
    }
    else if (this->_stmt2)
    {
        this->_stmt2->evaluate();
    }
}

////////////////////////////////////////////////////////////////////////////////
// WhileStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::WhileStmt::printAST()
{
    std::cout << "WhileStmt: " << std::endl;
    this->_cond->printAST();
    this->_stmt->printAST();
}

void lp::WhileStmt::evaluate()
{
    while (this->_cond->evaluateBool())
    {
        this->_stmt->evaluate();
    }
}

////////////////////////////////////////////////////////////////////////////////
// RepeatStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::RepeatStmt::printAST()
{
    std::cout << "RepeatStmt:" << std::endl;
    this->_body->printAST();
    this->_cond->printAST();
}

void lp::RepeatStmt::evaluate()
{
    do
    {
        this->_body->evaluate();
        if (this->_cond->getType() != BOOL)
        {
            warning("Runtime error: condition not boolean", "repeat");
            break;
        }
    } while (!this->_cond->evaluateBool());
}

////////////////////////////////////////////////////////////////////////////////
// ForStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::ForStmt::printAST()
{
    std::cout << "ForStmt:" << std::endl;
    std::cout << "\tVariable: " << this->_var << std::endl;
    this->_start->printAST();
    this->_end->printAST();
    this->_step->printAST();
    this->_body->printAST();
}

void lp::ForStmt::evaluate()
{
    if (this->_start->getType() != NUMBER ||
        this->_end->getType() != NUMBER ||
        this->_step->getType() != NUMBER)
    {
        warning("Runtime error: incompatible types", "For loop");
        return;
    }

    double startVal = _start->evaluateNumber();
    double endVal = _end->evaluateNumber();
    double stepVal = _step->evaluateNumber();

    if (stepVal == 0)
    {
        warning("Runtime error: zero step value", "For loop");
        return;
    }

    bool increasing = stepVal > 0;
    for (double i = startVal;
         increasing ? (i <= endVal) : (i >= endVal);
         i += stepVal)
    {
        lp::AssignmentStmt assignment(_var, new lp::NumberNode(i));
        assignment.evaluate();
        _body->evaluate();
    }
}

////////////////////////////////////////////////////////////////////////////////
// SwitchStmt Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::SwitchStmt::printAST()
{
    std::cout << "SwitchStmt:" << std::endl;
    this->_exp->printAST();
    for (auto &caseItem : *this->_cases)
    {
        if (caseItem->value) {
            caseItem->value->printAST();
        }
        caseItem->body->printAST();
    }
    if (this->_default)
        this->_default->printAST();
}

void lp::SwitchStmt::evaluate()
{
    bool matched = false;
    int exprType = this->_exp->getType();

    for (auto &caseItem : *this->_cases)
    {
        // Skip default case (handled later)
        if (caseItem->value == nullptr) continue;

        if (caseItem->value->getType() != exprType)
        {
            warning("Runtime error: type mismatch in case", "Switch");
            continue;
        }

        bool condition = false;
        switch (exprType)
        {
        case NUMBER:
            condition = lp::approximatelyEqual(
                _exp->evaluateNumber(),
                caseItem->value->evaluateNumber());
            break;
        case BOOL:
            condition = _exp->evaluateBool() == caseItem->value->evaluateBool();
            break;
        case STRING:
            condition = _exp->evaluateString() == caseItem->value->evaluateString();
            break;
        default:
            warning("Runtime error: unsupported type in switch", "Switch");
            continue;
        }

        if (condition)
        {
            caseItem->body->evaluate();
            matched = true;
            break;
        }
    }

    if (!matched && _default)
    {
        _default->evaluate();
    }
}

////////////////////////////////////////////////////////////////////////////////
// ClearScreenStmt Implementation
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
// PlaceStmt Implementation
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
// AST Implementation
////////////////////////////////////////////////////////////////////////////////

void lp::AST::printAST()
{
    for (auto stmt : *stmts)
    {
        stmt->printAST();
    }
}

void lp::AST::evaluate()
{
    for (auto stmt : *stmts)
    {
        stmt->evaluate();
    }
}