/*!	
	\file    ast.hpp
	\brief   Declaration of AST class
	\author  
	\date    2022-10-07
	\version 1.0
*/

#ifndef _AST_HPP_
#define _AST_HPP_

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <cmath>
#include <cfloat>

// Simple type identifiers for AST nodes
enum {
  NUMBER = 0,
  BOOL = 1,
  STRING = 2,
  UNKNOWN = -1
};

#define ERROR_BOUND 1.0e-6  //!< Error bound for the comparison of real numbers.

namespace lp
{
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*!	
  \class   ExpNode
  \brief   Definition of atributes and methods of ExpNode class
  \warning Abstract class
*/
 class ExpNode 
{
  public:
	/*!	
		\brief   Type of the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  int
		\sa		   printAST, evaluateNumber, evaluateBool
	*/
    virtual int getType() = 0;

	/*!	
		\brief   Print the AST for expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		   getType, evaluateNumber, evaluateBool
	*/
    virtual void printAST() = 0;

	/*!	
		\brief   Evaluate the expression as NUMBER
		\warning Virtual function: could be redefined in the heir classes
		\return  double
		\sa		   getType, printAST, evaluateBool
	*/
    virtual double evaluateNumber()
	{
		return 0.0;
	}		

	/*!	
		\brief   Evaluate the expression as BOOL
		\warning Virtual function: could be redefined in the heir classes
		\return  bool
		\sa		   getType, printAST, evaluateNumber
	*/
    virtual bool evaluateBool()
    {
        return false;
    }

    /*!
        \brief   Evaluate the expression as STRING
        \warning Virtual function: could be redefined in the heir classes
        \return  std::string
        \sa      getType, printAST
    */
    virtual std::string evaluateString()
    {
        return "";
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class VariableNode
  \brief Definition of atributes and methods of VariableNode class
  \note  VariableNode Class publicly inherits from ExpNode class
*/
class VariableNode : public ExpNode 
{
	private:
	  std::string _id; //!< Name of the VariableNode

	public:
	/*!		
		\brief Constructor of VariableNode
		\param value: std::string
		\post  A new VariableNode is created with the name of the parameter
	*/
	  VariableNode(std::string const & value) : _id(value) {}

	/*!	
		\brief   Type of the Variable
		\return  int
		\sa		   printAST
	*/
	int getType();

	/*!
		\brief   Print the AST for Variable
		\return  void
		\sa		   getType, evaluateNumber, evaluateBool
	*/
	void printAST();

	/*!	
		\brief   Evaluate the Variable as NUMBER
		\return  double
		\sa		   printAST
	*/
	double evaluateNumber();

	/*!	
		\brief   Evaluate the Variable as BOOL
		\return  bool
		\sa		   getType, printAST, evaluateNumber
	*/
	bool evaluateBool();
    
    /*!
        \brief   Evaluate the Variable as STRING
        \return  std::string
        \sa      getType, printAST
    */
    std::string evaluateString();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class ConstantNode
  \brief Definition of atributes and methods of ConstantNode class
  \note  ConstantNode Class publicly inherits from ExpNode class
*/
class ConstantNode : public ExpNode 
{
	private:
	  std::string _id; //!< Name of the ConstantNode

	public:
	/*!		
		\brief Constructor of ConstantNode
		\param value: std::string
		\post  A new ConstantNode is created with the name of the parameter
	*/
	  ConstantNode(std::string value) : _id(value) {}

	/*!	
		\brief   Type of the Constant
		\return  int
		\sa		   printAST, evaluateNumber, evaluateBool
	*/
	int getType();

	/*!
		\brief   Print the AST for Constant
		\return  void
		\sa		   getType, evaluateNumber, evaluateBool
	*/
	void printAST();

	/*!	
		\brief   Evaluate the Constant as NUMBER
		\return  double
		\sa		   getType, printAST
	*/
	double evaluateNumber();

	/*!	
		\brief   Evaluate the Constant as BOOL
		\return  bool
		\sa		   getType, printAST, evaluateNumber
	*/
	bool evaluateBool();
    
    /*!
        \brief   Evaluate the Constant as STRING
        \return  std::string
        \sa      getType, printAST
    */
    std::string evaluateString();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumberNode
  \brief Definition of atributes and methods of NumberNode class
  \note  NumberNode Class publicly inherits from ExpNode class
*/
class NumberNode : public ExpNode 
{
 private: 	
   double _number; //!< \brief number of the NumberNode
 
 public:
	/*!		
		\brief Constructor of NumberNode
		\param value: double
		\post  A new NumberNode is created with the value of the parameter
	*/
    NumberNode(double value) : _number(value) {}

	/*!	
		\brief   Get the type of the expression: NUMBER
		\return  int
		\sa		   printAST, evaluateNumber
	*/
	int getType();

	/*!
		\brief   Print the AST for expression
		\return  void
		\sa		   getType, evaluateNumber
	*/
	void printAST();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		   getType, printAST
	*/
	double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class StringNode
  \brief Definition of atributes and methods of StringNode class
  \note  StringNode Class publicly inherits from ExpNode class
*/
class StringNode : public ExpNode 
{
 private: 	
   std::string _string; //!< \brief string value
 
 public:
	/*!		
		\brief Constructor of StringNode
		\param value: std::string
		\post  A new StringNode is created with the value of the parameter
	*/
    StringNode(std::string value) : _string(value) {}

	/*!	
		\brief   Get the type of the expression: STRING
		\return  int
		\sa		   printAST, evaluateString
	*/
	int getType();

	/*!
		\brief   Print the AST for expression
		\return  void
		\sa		   getType, evaluateString
	*/
	void printAST();

	/*!	
		\brief   Evaluate the expression
		\return  std::string
		\sa		   getType, printAST
	*/
	std::string evaluateString();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from ExpNode class 
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class UnaryOperatorNode : public ExpNode 
{
 protected:
  ExpNode *_exp;  //!< Child expression

 public:
	/*!		
		\brief Constructor of UnaryOperatorNode links the node to it child
		\param expression: pointer to ExpNode
		\post  A new OperatorNode is created with the parameters
	*/
    UnaryOperatorNode(ExpNode *expression) : _exp(expression) {}

	/*!	
		\brief   Get the type of the child expression
		\return  int
		\sa		   printAST
	*/
	int getType();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NumericUnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from UnaryOperatorNode class 
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class NumericUnaryOperatorNode : public UnaryOperatorNode 
{
 public:
	/*!		
		\brief Constructor of NumericUnaryOperatorNode
		\param expression: pointer to ExpNode
		\post  A new NumericUnaryOperatorNode is created
	*/
    NumericUnaryOperatorNode(ExpNode *expression) : UnaryOperatorNode(expression) {}

	/*!	
		\brief   Get the type of the child expression
		\return  int
		\sa		   printAST
	*/
	int getType();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LogicalUnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from UnaryOperatorNode class 
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class LogicalUnaryOperatorNode : public UnaryOperatorNode 
{
 public:
	/*!		
		\brief Constructor of LogicalUnaryOperatorNode
		\param expression: pointer to ExpNode
		\post  A new LogicalUnaryOperatorNode is created
	*/
    LogicalUnaryOperatorNode(ExpNode *expression) : UnaryOperatorNode(expression) {}

	/*!	
		\brief   Get the type of the child expression
		\return  int
		\sa		   printAST
	*/
	int getType();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryMinusNode
  \brief   Definition of atributes and methods of UnaryMinusNode class
  \note    UnaryMinusNode Class publicly inherits from NumericUnaryOperatorNode class 
*/
class UnaryMinusNode : public NumericUnaryOperatorNode 
{
 public:
	/*!		
		\brief Constructor of UnaryMinusNode
		\param expression: pointer to ExpNode
		\post  A new UnaryMinusNode is created
	*/
    UnaryMinusNode(ExpNode *expression) : NumericUnaryOperatorNode(expression) {}

	/*!
		\brief   Print the AST for expression
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryPlusNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    UnaryPlusNode Class publicly inherits from NumericUnaryOperatorNode class 
*/
class UnaryPlusNode : public NumericUnaryOperatorNode 
{
 public:
	/*!		
		\brief Constructor of UnaryPlusNode
		\param expression: pointer to ExpNode
		\post  A new UnaryPlusNode is created
	*/
    UnaryPlusNode(ExpNode *expression) : NumericUnaryOperatorNode(expression) {}

	/*!
		\brief   Print the AST for expression
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   OperatorNode
  \brief   Definition of atributes and methods of OperatorNode class
  \note    OperatorNode Class publicly inherits from ExpNode class 
  \warning Abstract class, because it does not redefine the printAST and getType methods of ExpNode
*/
class OperatorNode : public ExpNode 
{
	protected:
		ExpNode *_left;    //!< Left expression
		ExpNode *_right;   //!< Right expression

	public:
	/*!		
		\brief Constructor of OperatorNode links the node to its children
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new OperatorNode is created with the parameters
	*/
    OperatorNode(ExpNode *L, ExpNode *R) : _left(L), _right(R) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NumericOperatorNode
  \brief   Definition of atributes and methods of NumericOperatorNode class
  \note    NumericOperatorNode Class publicly inherits from OperatorNode class 
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class NumericOperatorNode : public OperatorNode 
{
	public:
	/*!		
		\brief Constructor of NumericOperatorNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new NumericOperatorNode is created
	*/
    NumericOperatorNode(ExpNode *L, ExpNode *R) : OperatorNode(L,R) {}

	/*!	
		\brief   Get the type of the children expressions
		\return  int
	*/
	int getType();
};

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   RelationalOperatorNode
  \brief   Definition of atributes and methods of RelationalOperatorNode class
  \note    RelationalOperatorNode Class publicly inherits from OperatorNode class 
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class RelationalOperatorNode : public OperatorNode 
{
public:
	/*!		
		\brief Constructor of RelationalOperatorNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new RelationalOperatorNode is created
	*/
    RelationalOperatorNode(ExpNode *L, ExpNode *R) : OperatorNode(L,R) {}

	/*!	
		\brief   Get the type of the children expressions
		\return  int
	*/
	int getType();
};

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LogicalOperatorNode
  \brief   Definition of atributes and methods of LogicalOperatorNode class
  \note    NumericOperatorNode Class publicly inherits from OperatorNode class 
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class LogicalOperatorNode : public OperatorNode 
{
	public:
	/*!		
		\brief Constructor of LogicalOperatorNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new LogicalOperatorNode is created
	*/
    LogicalOperatorNode(ExpNode *L, ExpNode *R) : OperatorNode(L,R) {}

	/*!	
		\brief   Get the type of the children expressions
		\return  int
	*/
	int getType();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AlphanumericOperatorNode
  \brief   Definition of atributes and methods of AlphanumericOperatorNode class
  \note    AlphanumericOperatorNode Class publicly inherits from OperatorNode class 
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class AlphanumericOperatorNode : public OperatorNode 
{
	public:
	/*!		
		\brief Constructor of AlphanumericOperatorNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new AlphanumericOperatorNode is created
	*/
    AlphanumericOperatorNode(ExpNode *L, ExpNode *R) : OperatorNode(L,R) {}

	/*!	
		\brief   Get the type of the children expressions
		\return  int
	*/
	int getType();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PlusNode
  \brief   Definition of atributes and methods of PlusNode class
  \note    PlusNode Class publicly inherits from NumericOperatorNode class 
*/
class PlusNode : public NumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of PlusNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new PlusNode is created
	*/
    PlusNode(ExpNode *L, ExpNode *R) : NumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for PlusNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the PlusNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   MinusNode
  \brief   Definition of atributes and methods of MinusNode class
  \note    MinusNode Class publicly inherits from NumericOperatorNode class 
*/
class MinusNode : public NumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of MinusNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new MinusNode is created
	*/
    MinusNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for MinusNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the MinusNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   MultiplicationNode
  \brief   Definition of atributes and methods of MultiplicationNode class
  \note    MultiplicationNode Class publicly inherits from NumericOperatorNode class 
*/
class MultiplicationNode : public NumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of MultiplicationNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new MultiplicationNode is created
	*/
    MultiplicationNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for MultiplicationNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the MultiplicationNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DivisionNode
  \brief   Definition of atributes and methods of DivisionNode class
  \note    DivisionNode Class publicly inherits from NumericOperatorNode class 
*/
class DivisionNode : public NumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of DivisionNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new DivisionNode is created
	*/
    DivisionNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for DivisionNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the DivisionNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   IntDivNode
  \brief   Definition of atributes and methods of IntDivNode class
  \note    IntDivNode Class publicly inherits from NumericOperatorNode class 
*/
class IntDivNode : public NumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of IntDivNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new IntDivNode is created
	*/
    IntDivNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for IntDivNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the IntDivNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ModuloNode
  \brief   Definition of atributes and methods of ModuloNode class
  \note    ModuloNode Class publicly inherits from NumericOperatorNode class 
*/
class ModuloNode : public NumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of ModuloNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new ModuloNode is created
	*/
    ModuloNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for ModuloNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the ModuloNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PowerNode
  \brief   Definition of atributes and methods of PowerNode class
  \note    PowerNode Class publicly inherits from NumericOperatorNode class 
*/
class PowerNode : public NumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of PowerNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new PowerNode is created
	*/
    PowerNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for PowerNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the PowerNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AlternativeNode
  \brief   Definition of atributes and methods of AlternativeNode class
  \note    AlternativeNode Class publicly inherits from ExpNode class 
*/
class AlternativeNode : public ExpNode 
{
 private:
  ExpNode *_cond; //!< Condition expression
  ExpNode *_left; //!< Left expression
  ExpNode *_right; //!< Right expression

 public:
	/*!		
		\brief Constructor of AlternativeNode
		\param cond: pointer to ExpNode
		\param left: pointer to ExpNode
		\param right: pointer to ExpNode
		\post  A new AlternativeNode is created
	*/
    AlternativeNode(ExpNode *cond, ExpNode *left, ExpNode *right) 
        : _cond(cond), _left(left), _right(right) {}

	/*!	
		\brief   Get the type of the expression
		\return  int
		\sa		   printAST
	*/
    int getType();

	/*!
		\brief   Print the AST for AlternativeNode
		\return  void
		\sa		   evaluateNumber
	*/
    void printAST();

	/*!	
		\brief   Evaluate the AlternativeNode
		\return  double
		\sa		   printAST
	*/
    double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ConcatenationNode
  \brief   Definition of atributes and methods of ConcatenationNode class
  \note    ConcatenationNode Class publicly inherits from AlphanumericOperatorNode class 
*/
class ConcatenationNode : public AlphanumericOperatorNode 
{
  public:
	/*!		
		\brief Constructor of ConcatenationNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new ConcatenationNode is created
	*/
    ConcatenationNode(ExpNode *L, ExpNode *R) : AlphanumericOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for ConcatenationNode
		\return  void
		\sa		   evaluateString
	*/
    void printAST();

	/*!	
		\brief   Evaluate the ConcatenationNode
		\return  std::string
		\sa		   printAST
	*/
    std::string evaluateString();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   BuiltinFunctionNode
  \brief   Definition of atributes and methods of BuiltinFunctionNode class
  \note    BuiltinFunctionNode Class publicly inherits from ExpNode class 
*/
class BuiltinFunctionNode : public ExpNode 
{
  protected: 
	std::string _id; //!< Name of the BuiltinFunctionNode
	
  public:
	/*!		
		\brief Constructor of BuiltinFunctionNode
		\param id: string, name of the BuiltinFunction
		\post  A new BuiltinFunctionNode is created with the parameter
	*/
    BuiltinFunctionNode(std::string id) : _id(id) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   BuiltinFunctionNode_0
  \brief   Definition of atributes and methods of BuiltinFunctionNode_0 class
  \note    BuiltinFunctionNode_0 Class publicly inherits from BuiltinFunctionNode class 
*/
class BuiltinFunctionNode_0 : public BuiltinFunctionNode 
{
  public:
	/*!		
		\brief Constructor of BuiltinFunctionNode_0
		\param id: string, name of the BuiltinFunction
		\post  A new BuiltinFunctionNode_0 is created
	*/
    BuiltinFunctionNode_0(std::string id): BuiltinFunctionNode(id) {}

	/*!	
		\brief   Get the type of the child expression
		\return  int
		\sa		   printAST, evaluateNumber
	*/
	int getType();

	/*!
		\brief   Print the AST for BuiltinFunctionNode_0
		\return  void
		\sa		   getType, evaluateNumber
	*/
	void printAST();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_0
		\return  double
		\sa		   getType, printAST
	*/
	double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   BuiltinFunctionNode_1
  \brief   Definition of atributes and methods of BuiltinFunctionNode_1 class
  \note    BuiltinFunctionNode_1 Class publicly inherits from BuiltinFunctionNode class 
*/
class BuiltinFunctionNode_1: public BuiltinFunctionNode 
{
  private:
	ExpNode *_exp;  //!< Argument of the BuiltinFunctionNode_1

  public:
	/*!		
		\brief Constructor of BuiltinFunctionNode_1
		\param id: string, name of the BuiltinFunction
		\param expression: pointer to ExpNode, argument of the BuiltinFunctionNode_1
		\post  A new BuiltinFunctionNode_1 is created
	*/
    BuiltinFunctionNode_1(std::string id, ExpNode *expression): BuiltinFunctionNode(id), _exp(expression) {}

	/*!	
		\brief   Get the type of the child expression
		\return  int
		\sa		   printAST, evaluateNumber
	*/
	int getType();

	/*!
		\brief   Print the AST for BuiltinFunctionNode_1
		\return  void
		\sa		   getType, evaluateNumber
	*/
	void printAST();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_1
		\return  double
		\sa		   getType, printAST
	*/
	double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   BuiltinFunctionNode_2
  \brief   Definition of atributes and methods of BuiltinFunctionNode_2 class 
  \note    BuiltinFunctionNode_2 Class publicly inherits from BuiltinFunctionNode class 
*/
class BuiltinFunctionNode_2 : public BuiltinFunctionNode 
{
	private:
		ExpNode *_exp1; //!< First argument
		ExpNode *_exp2; //!< Second argument

	public:
	/*!		
		\brief Constructor of BuiltinFunctionNode_2
		\param id: string, name of the BuiltinFunction_2
		\param expression1: pointer to ExpNode, first argument
		\param expression2: pointer to ExpNode, second argument
		\post  A new BuiltinFunctionNode_2 is created
	*/
    BuiltinFunctionNode_2(std::string id, ExpNode *expression1, ExpNode *expression2) 
        : BuiltinFunctionNode(id), _exp1(expression1), _exp2(expression2) {}

	/*!	
		\brief   Get the type of the children expressions
		\return  int
		\sa		   printAST, evaluateNumber
	*/
	int getType();

	/*!
		\brief   Print the AST for BuiltinFunctionNode_2
		\return  void
		\sa		   getType, evaluateNumber
	*/
	void printAST();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_2
		\return  double
		\sa		   getType, printAST
	*/
	double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   GreaterThanNode
  \brief   Definition of atributes and methods of GreaterThanNode class
  \note    GreaterThanNode Class publicly inherits from RelationalOperatorNode class 
*/
class GreaterThanNode : public RelationalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of GreaterThanNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new GreaterThanNode is created
	*/
    GreaterThanNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for GreaterThanNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the GreaterThanNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   GreaterOrEqualNode
  \brief   Definition of atributes and methods of GreaterOrEqualNode class
  \note    GreaterOrEqualNode Class publicly inherits from RelationalOperatorNode class 
*/
class GreaterOrEqualNode : public RelationalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of GreaterOrEqualNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new GreaterOrEqualNode is created
	*/
    GreaterOrEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for GreaterOrEqualNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the GreaterOrEqualNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LessThanNode
  \brief   Definition of atributes and methods of LessThanNode class
  \note    LessThanNode Class publicly inherits from RelationalOperatorNode class 
*/
class LessThanNode : public RelationalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of LessThanNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new LessThanNode is created
	*/
    LessThanNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for LessThanNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the LessThanNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LessOrEqualNode
  \brief   Definition of atributes and methods of LessOrEqualNode class
  \note    LessThanNode Class publicly inherits from RelationalOperatorNode class 
*/
class LessOrEqualNode : public RelationalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of LessOrEqualNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new LessOrEqualNode is created
	*/
    LessOrEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for LessOrEqualNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the LessOrEqualNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   EqualNode
  \brief   Definition of atributes and methods of EqualNode class
  \note    EqualNode Class publicly inherits from RelationalOperatorNode class 
*/
class EqualNode : public RelationalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of EqualNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new EqualNode is created
	*/
    EqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for EqualNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the EqualNode
		\return  bool
		\sa		  printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NotEqualNode
  \brief   Definition of atributes and methods of NotEqualNode class
  \note    NotEqualNode Class publicly inherits from RelationalOperatorNode class 
*/
class NotEqualNode : public RelationalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of NotEqualNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new NotEqualNode is created
	*/
    NotEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for NotEqualNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the NotEqualNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AndNode
  \brief   Definition of atributes and methods of AndNode class
  \note    AndNode Class publicly inherits from LogicalOperatorNode class 
*/
class AndNode : public LogicalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of AndNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new AndNode is created
	*/
    AndNode(ExpNode *L, ExpNode *R): LogicalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for AndNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the AndNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   OrNode
  \brief   Definition of atributes and methods of OrNode class
  \note    OrNode Class publicly inherits from LogicalOperatorNode class 
*/
class OrNode : public LogicalOperatorNode 
{
  public:
	/*!		
		\brief Constructor of OrNode
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new OrNode is created
	*/
    OrNode(ExpNode *L, ExpNode *R): LogicalOperatorNode(L,R) {}

	/*!
		\brief   Print the AST for OrNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the OrNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NotNode
  \brief   Definition of atributes and methods of NotNode class
  \note    NotNode Class publicly inherits from LogicalUnaryOperatorNode class
*/
class NotNode : public LogicalUnaryOperatorNode 
{
 public:
	/*!		
		\brief Constructor of NotNode
		\param expression: pointer to ExpNode
		\post  A new NotNode is created
	*/
    NotNode(ExpNode *expression): LogicalUnaryOperatorNode(expression) {}

	/*!
		\brief   Print the AST for NotNode
		\return  void
		\sa		   evaluateBool
	*/
    void printAST();

	/*!	
		\brief   Evaluate the NotNode
		\return  bool
		\sa		   printAST
	*/
    bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   Statement
  \brief   Definition of atributes and methods of Statement class
  \warning Abstract class
*/
class Statement {
 public:
	/*!	
		\brief   Print the AST for Statement
		\return  void
	*/
    virtual void printAST() = 0;

	/*!	
		\brief   Evaluate the Statement
		\return  void
	*/
    virtual void evaluate() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AssignmentStmt
  \brief   Definition of atributes and methods of AssignmentStmt class
  \note    AssignmentStmt Class publicly inherits from Statement class 
*/
class AssignmentStmt : public Statement 
{
 private:
  std::string _id;    //!< Name of the variable
  ExpNode *_exp;      //!< Expression to assign
  AssignmentStmt *_asgn;  //!< For multiple assignment

 public:
	/*!		
		\brief Constructor for expression assignment
		\param id: string, variable name
		\param expression: pointer to ExpNode
		\post  A new AssignmentStmt is created
	*/
    AssignmentStmt(std::string id, ExpNode *expression) 
        : _id(id), _exp(expression), _asgn(nullptr) {}

	/*!		
		\brief Constructor for multiple assignment
		\param id: string, variable name
		\param asgn: pointer to AssignmentStmt
		\post  A new AssignmentStmt is created
	*/
    AssignmentStmt(std::string id, AssignmentStmt *asgn) 
        : _id(id), _exp(nullptr), _asgn(asgn) {}

	/*!
		\brief   Print the AST for AssignmentStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the AssignmentStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AssignmentPlusStmt
  \brief   Definition of atributes and methods of AssignmentPlusStmt class
  \note    AssignmentPlusStmt Class publicly inherits from Statement class 
*/
class AssignmentPlusStmt : public Statement 
{
 private:
  std::string _id; //!< Name of the variable
  ExpNode *_exp;   //!< Expression to add

 public:
	/*!		
		\brief Constructor of AssignmentPlusStmt 
		\param id: string, variable name
		\param expression: pointer to ExpNode
		\post  A new AssignmentPlusStmt is created
	*/
    AssignmentPlusStmt(std::string id, ExpNode *expression) 
        : _id(id), _exp(expression) {}

	/*!
		\brief   Print the AST for AssignmentPlusStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the AssignmentPlusStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AssignmentMinusStmt
  \brief   Definition of atributes and methods of AssignmentMinusStmt class
  \note    AssignmentMinusStmt Class publicly inherits from Statement class 
*/
class AssignmentMinusStmt : public Statement 
{
 private:
  std::string _id; //!< Name of the variable
  ExpNode *_exp;   //!< Expression to subtract

 public:
	/*!		
		\brief Constructor of AssignmentMinusStmt 
		\param id: string, variable name
		\param expression: pointer to ExpNode
		\post  A new AssignmentMinusStmt is created
	*/
    AssignmentMinusStmt(std::string id, ExpNode *expression) 
        : _id(id), _exp(expression) {}

	/*!
		\brief   Print the AST for AssignmentMinusStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the AssignmentMinusStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   IncrementStmt
  \brief   Definition of atributes and methods of IncrementStmt class
  \note    IncrementStmt Class publicly inherits from Statement class 
*/
class IncrementStmt : public Statement 
{
 private:
  std::string _id; //!< Name of the variable

 public:
	/*!		
		\brief Constructor of IncrementStmt 
		\param id: string, variable name
		\post  A new IncrementStmt is created
	*/
    IncrementStmt(std::string id) : _id(id) {}

	/*!
		\brief   Print the AST for IncrementStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the IncrementStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DecrementStmt
  \brief   Definition of atributes and methods of DecrementStmt class
  \note    DecrementStmt Class publicly inherits from Statement class 
*/
class DecrementStmt : public Statement 
{
 private:
  std::string _id; //!< Name of the variable

 public:
	/*!		
		\brief Constructor of DecrementStmt 
		\param id: string, variable name
		\post  A new DecrementStmt is created
	*/
    DecrementStmt(std::string id) : _id(id) {}

	/*!
		\brief   Print the AST for DecrementStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the DecrementStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PrintStmt
  \brief   Definition of atributes and methods of PrintStmt class
  \note    PrintStmt Class publicly inherits from Statement class 
*/
class PrintStmt: public Statement 
{
 private:
  ExpNode *_exp; //!< Expression to print

 public:
	/*!		
		\brief Constructor of PrintStmt 
		\param expression: pointer to ExpNode
		\post  A new PrintStmt is created
	*/
    PrintStmt(ExpNode *expression) : _exp(expression) {}

	/*!
		\brief   Print the AST for PrintStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the PrintStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PrintStringStmt
  \brief   Definition of atributes and methods of PrintStringStmt class
  \note    PrintStringStmt Class publicly inherits from Statement class 
*/
class PrintStringStmt : public Statement 
{
 private:
  ExpNode *_exp; //!< Expression to print

 public:
	/*!		
		\brief Constructor of PrintStringStmt 
		\param expression: pointer to ExpNode
		\post  A new PrintStringStmt is created
	*/
    PrintStringStmt(ExpNode *expression) : _exp(expression) {}

	/*!
		\brief   Print the AST for PrintStringStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the PrintStringStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ReadStmt
  \brief   Definition of atributes and methods of ReadStmt class
  \note    ReadStmt Class publicly inherits from Statement class 
*/
class ReadStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the variable

  public:
	/*!		
		\brief Constructor of ReadStmt
		\param id: string, variable name
		\post  A new ReadStmt is created
	*/
    ReadStmt(std::string id) : _id(id) {}

	/*!
		\brief   Print the AST for ReadStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the ReadStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ReadStringStmt
  \brief   Definition of atributes and methods of ReadStringStmt class
  \note    ReadStringStmt Class publicly inherits from Statement class 
*/
class ReadStringStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the variable

  public:
	/*!		
		\brief Constructor of ReadStringStmt
		\param id: string, variable name
		\post  A new ReadStringStmt is created
	*/
    ReadStringStmt(std::string id) : _id(id) {}

	/*!
		\brief   Print the AST for ReadStringStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the ReadStringStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   EmptyStmt
  \brief   Definition of atributes and methods of EmptyStmt class
  \note    EmptyStmt Class publicly inherits from Statement class 
*/
class EmptyStmt : public Statement 
{
  public:
	/*!		
		\brief Constructor of EmptyStmt
		\post  A new EmptyStmt is created 
	*/
    EmptyStmt() {}

	/*!
		\brief   Print the AST for EmptyStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the EmptyStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   IfStmt
  \brief   Definition of atributes and methods of IfStmt class
  \note    IfStmt Class publicly inherits from Statement class 
*/
class IfStmt : public Statement 
{
 private:
  ExpNode *_cond;    //!< Condition expression
  Statement *_stmt1; //!< Consequent statement
  Statement *_stmt2; //!< Alternative statement

  public:
	/*!		
		\brief Constructor without alternative
		\param condition: ExpNode of the condition
		\param statement1: Statement of the consequent
		\post  A new IfStmt is created
	*/
    IfStmt(ExpNode *condition, Statement *statement1) 
        : _cond(condition), _stmt1(statement1), _stmt2(nullptr) {}

	/*!		
		\brief Constructor with alternative
		\param condition: ExpNode of the condition
		\param statement1: Statement of the consequent
		\param statement2: Statement of the alternative
		\post  A new IfStmt is created
	*/
    IfStmt(ExpNode *condition, Statement *statement1, Statement *statement2) 
        : _cond(condition), _stmt1(statement1), _stmt2(statement2) {}

	/*!
		\brief   Print the AST for IfStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the IfStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   WhileStmt
  \brief   Definition of atributes and methods of WhileStmt class
  \note    WhileStmt Class publicly inherits from Statement class 
*/
class WhileStmt : public Statement 
{
 private:
  ExpNode *_cond;   //!< Condition expression
  Statement *_stmt; //!< Body statement

  public:
	/*!		
		\brief Constructor of WhileStmt
		\param condition: ExpNode of the condition
		\param statement: Statement of the body
		\post  A new WhileStmt is created
	*/
    WhileStmt(ExpNode *condition, Statement *statement) 
        : _cond(condition), _stmt(statement) {}

	/*!
		\brief   Print the AST for WhileStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the WhileStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   RepeatStmt
  \brief   Definition of atributes and methods of RepeatStmt class
  \note    RepeatStmt Class publicly inherits from Statement class 
*/
class RepeatStmt : public Statement 
{
 private:
  Statement *_body; //!< Body statement
  ExpNode *_cond;   //!< Condition expression

  public:
	/*!		
		\brief Constructor of RepeatStmt
		\param body: Statement of the body
		\param cond: ExpNode of the condition
		\post  A new RepeatStmt is created
	*/
    RepeatStmt(Statement *body, ExpNode *cond) 
        : _body(body), _cond(cond) {}

	/*!
		\brief   Print the AST for RepeatStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the RepeatStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ForStmt
  \brief   Definition of atributes and methods of ForStmt class
  \note    ForStmt Class publicly inherits from Statement class 
*/
class ForStmt : public Statement 
{
 private:
  std::string _id;  //!< Loop variable name
  ExpNode *_start;  //!< Start expression
  ExpNode *_end;    //!< End expression
  ExpNode *_step;   //!< Step expression
  Statement *_body; //!< Body statement

  public:
	/*!		
		\brief Constructor of ForStmt
		\param id: string, loop variable name
		\param start: ExpNode, start value
		\param end: ExpNode, end value
		\param step: ExpNode, step value
		\param body: Statement, body of the loop
		\post  A new ForStmt is created
	*/
    ForStmt(std::string id, ExpNode *start, ExpNode *end, ExpNode *step, Statement *body) 
        : _id(id), _start(start), _end(end), _step(step), _body(body) {}

	/*!
		\brief   Print the AST for ForStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the ForStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ClearScreenStmt
  \brief   Definition of atributes and methods of ClearScreenStmt class
  \note    ClearScreenStmt Class publicly inherits from Statement class 
*/
class ClearScreenStmt : public Statement 
{
  public:
	/*!		
		\brief Constructor of ClearScreenStmt
		\post  A new ClearScreenStmt is created
	*/
    ClearScreenStmt() {}

	/*!
		\brief   Print the AST for ClearScreenStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the ClearScreenStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PlaceStmt
  \brief   Definition of atributes and methods of PlaceStmt class
  \note    PlaceStmt Class publicly inherits from Statement class 
*/
class PlaceStmt : public Statement 
{
 private:
  ExpNode *_row; //!< Row position
  ExpNode *_col; //!< Column position

  public:
	/*!		
		\brief Constructor of PlaceStmt
		\param row: ExpNode, row position
		\param col: ExpNode, column position
		\post  A new PlaceStmt is created
	*/
    PlaceStmt(ExpNode *row, ExpNode *col) : _row(row), _col(col) {}

	/*!
		\brief   Print the AST for PlaceStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the PlaceStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   BlockStmt
  \brief   Definition of atributes and methods of BlockStmt class
  \note    BlockStmt Class publicly inherits from Statement class 
*/
class BlockStmt : public Statement 
{
 private:
   std::list<Statement *> *_stmts;  //!< List of statements

  public:
	/*!		
		\brief Constructor of BlockStmt
		\param stmtList: list of Statement pointers
		\post  A new BlockStmt is created
	*/
    BlockStmt(std::list<Statement *> *stmtList) : _stmts(stmtList) {}

	/*!
		\brief   Print the AST for BlockStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the BlockStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   SwitchStmt
  \brief   Definition of atributes and methods of SwitchStmt class
  \note    SwitchStmt Class publicly inherits from Statement class 
*/
class SwitchStmt : public Statement 
{
 private:
  ExpNode *_exp; //!< Expression to switch on
  std::list<struct Case *> *_cases; //!< List of cases
  Statement *_default; //!< Default case

  public:
	/*!		
		\brief Constructor of SwitchStmt
		\param exp: ExpNode, expression to switch on
		\param cases: list of Case pointers
		\param defaultStmt: Statement for default case
		\post  A new SwitchStmt is created
	*/
    SwitchStmt(ExpNode *exp, std::list<struct Case *> *cases, Statement *defaultStmt = nullptr) 
        : _exp(exp), _cases(cases), _default(defaultStmt) {}

	/*!
		\brief   Print the AST for SwitchStmt
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the SwitchStmt
		\return  void
	*/
    void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \struct  Case
  \brief   Definition of atributes of Case struct
*/
struct Case 
{
  ExpNode *value; //!< Case value expression
  Statement *body; //!< Case body statement

  /*!		
		\brief Constructor of Case
		\param val: ExpNode, case value
		\param b: Statement, case body
		\post  A new Case is created
  */
  Case(ExpNode *val, Statement *b) : value(val), body(b) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AST
  \brief   Definition of atributes and methods of AST class
*/
class AST {
 private:
  std::list<Statement *> *stmts;  //!< List of statements

 public:
	/*!		
		\brief Constructor of AST 
		\param stmtList: list of Statement pointers
		\post  A new AST is created
	*/
    AST(std::list<Statement *> *stmtList) : stmts(stmtList) {}

	/*!
		\brief   Print the AST
		\return  void
	*/
    void printAST();

	/*!	
		\brief   Evaluate the AST
		\return  void
	*/
    void evaluate();
};

// End of name space lp
}

#endif