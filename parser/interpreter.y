/*! 
  \file interpreter.y
  \brief Grammar file
*/


%{
#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"


/*******************************************/
/* 
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"


/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/

/* NEW in example 15 */
#include "../table/logicalVariable.hpp"
#include "../table/alphanumericVariable.hpp"


/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 15 */
#include "../table/logicalConstant.hpp"
#include "../table/alphanumericConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();


extern int lineNumber; //!< External line counter


/* NEW in example 15 */
extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

/* New in example 17 */
extern int control; //!< External: to control the interactive mode in "if" and "while" sentences 




/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Extern Table of Symbols

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST

%}

/* In case of a syntactic error, more information is shown */
/* DEPRECATED */
/* %error-verbose */

/* ALTERNATIVA a %error-verbose */
%define parse.error verbose


/* Initial grammar symbol */
%start program

/*******************************************/
/* Data type YYSTYPE  */
/* NEW in example 4 */
%union {
  double number;
  char * string; 				 /* NEW in example 7 */
  bool logic;						 /* NEW in example 15 */
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

  lp::Case *caseptr;                             /* NUEVO para switch */
  std::list<lp::Case *> *caselist; 
}

/* Type of the non-terminal symbols */
// New in example 17: cond
%type <expNode> exp cond 

/* New in example 14 */
// NUEVO: IMPORTANTE: NO SÉ SI listOfExp y restOfListOfExp SE VAN A USAR, A LO MEJOR HAY QUE QUITARLOS
%type <parameters> listOfExp  restOfListOfExp

%type <stmts> stmtlist

// New in example 17: if, while, block
// NUEVO: AÑADIDAS NUEVAS SENTENCIAS (A PARTIR DE read_string) Y ELIMINADA SENTENCIA block
%type <st> stmt asgn asgn_plus asgn_minus print read if while read_string repeat for switch increment decrement

%type <prog> program

%type <caseptr> case_stmt
%type <caselist> case_list


/* Defined tokens */

/* Minimum precedence */

%token SEMICOLON

%token PRINT READ IF ELSE WHILE READ_STRING THEN END_IF DO END_WHILE REPEAT UNTIL FOR END_FOR FROM STEP TO SWITCH CASE DEFAULT END_SWITCH CLEAR_SCREEN_X PLACE_X  

// NUEVO: SE HA SUPRIMIDO { Y } DEBIDO A QUE LA SENTENCIA block YA NO ES NECESARIA

%right QUESTION_MARK
%right ASIGNACION
%right ASIGNACIONPLUS
%right ASIGNACIONMINUS

%token <number> NUMBER
%token <logic> BOOL
%token <string> STRING // NUEVO

%token <string> VARIABLE UNDEFINED CONSTANT BUILTIN
/*******************************************/

/*******************************************/
/* Anadidos para el trabajo final */
%token COLON COMMA QUESTION

/* Left associativity to avoid conflictos desplazamiento/reducción*/
%left OR
%left AND
%left NOT
%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL // NUEVO
%left CONCATENACION   
%left PLUS MINUS 
%left MULTIPLICATION DIVISION DIVISION_ENTERA MODULO
%left PLUSPLUS MINUSMINUS
%right POWER

%left LPAREN RPAREN

%nonassoc  UNARY

%%
 //! \name Grammar rules

/* MODIFIED  Grammar in example 16 */

program : stmtlist
		  { 
		    // Create a new AST
			$$ = new lp::AST($1); 

			// Assign the AST to the root
			root = $$; 

			// End of parsing
			//	return 1;
		  }
;

stmtlist:  /* empty: epsilon rule */
		  { 
			// create a empty list of statements
			$$ = new std::list<lp::Statement *>(); 
		  }  

        | stmtlist stmt 
		  { 
			// copy up the list and add the stmt to it
			$$ = $1;
			$$->push_back($2);

			// Control the interative mode of execution of the interpreter
			if (interactiveMode == true && control == 0)
 			{
				for(std::list<lp::Statement *>::iterator it = $$->begin(); 
						it != $$->end(); 
						it++)
				{
					//(*it)->printAST();
					(*it)->evaluate();
					
				}

				// Delete the AST code, because it has already run in the interactive mode.
				$$->clear();
			}
		}

    | stmtlist error 
      { 
			 // just copy up the stmtlist when an error occurs
			 $$ = $1;

			 // The previous look-ahead token ought to be discarded with `yyclearin;'
			 yyclearin; 
       } 
;
 

stmt: SEMICOLON  /* Empty statement: ";" */
	  {
		// Create a new empty statement node
		$$ = new lp::EmptyStmt(); 
	  }
	| asgn SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| asgn_plus SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| asgn_minus SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| print SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| read SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  } // NUEVO: AÑADIDO read_string
	| read_string SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| increment SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| decrement SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	/*  NEW in example 17 */
	| if 
	 {
		// Default action
		// $$ = $1;
	 }
	/*  NEW in example 17 */
	| while 
	 {
		// Default action
		// $$ = $1;
	 } // NUEVO: AÑADIDOS repeat, for y switch
	| repeat
	 {
		// Default action
		// $$ = $1;
	 }
	| for
	 {
		// Default action
		// $$ = $1;
	 }
	| switch
	 {
		// Default action
		// $$ = $1;
	 }
	| CLEAR_SCREEN_X SEMICOLON
	 {
		$$ = new lp::ClearScreenStmt();
	 }
	| PLACE_X LPAREN exp COMMA exp RPAREN SEMICOLON
  	 {
    	$$ = new lp::PlaceStmt($3, $5);
  	 }
;

// NUEVO: SE HA SUPRIMIDO LA SENTENCIA block

controlSymbol:  /* Epsilon rule*/
		{
			// To control the interactive mode in "if" and "while" sentences
			control++;
		}
	;

	/*  NEW in example 17 */
if:	/* Simple conditional statement */
	IF controlSymbol cond THEN stmtlist END_IF 
    {
		// Create a new if statement node
		$$ = new lp::IfStmt($3, $5);

		// To control the interactive mode
		control--;
	}

	/* Compound conditional statement */
	| IF controlSymbol cond THEN stmtlist ELSE stmtlist END_IF
	 {
		// Create a new if statement node
		$$ = new lp::IfStmt($3, $5, $7);

		// To control the interactive mode
		control--;
	 }
;

	/*  NEW in example 17 */
while: WHILE controlSymbol cond DO stmtlist END_WHILE
	{
		$$ = new lp::WhileStmt($3, $5);
		control--;
	}
;

repeat:  REPEAT controlSymbol stmtlist UNTIL cond
    {
		// Create a new repeat statement node
		$$ = new lp::RepeatStmt(new lp::AST($3), $5);

		// To control the interactive mode
		control--;
	}
;

for:  /* For loop statement */
    FOR controlSymbol VARIABLE FROM exp TO exp STEP exp DO stmtlist END_FOR
    {
        // Create a new for statement node with step
        $$ = new lp::ForStmt(std::string($3), $5, $7, $9, new lp::AST($11));
        control--;
    }
  | FOR controlSymbol VARIABLE FROM exp TO exp DO stmtlist END_FOR
    {
        // Create a new for statement node with default step = 1
        $$ = new lp::ForStmt(std::string($3), $5, $7, new lp::AST($9));
        control--;
    }
	  /* SEMANTIC ERRORS */
  | FOR CONSTANT FROM exp TO exp STEP exp DO stmtlist END_FOR
    {
 			execerror("Error semántico en FOR: no está permitido modificar una constante ", $2);
    }
  | FOR CONSTANT FROM exp TO exp DO stmtlist END_FOR
    {
 			execerror("Error semántico en FOR: no está permitido modificar una constante ", $2);
    }
;

switch:
	SWITCH controlSymbol LPAREN exp RPAREN case_list END_SWITCH
	{
		$$ = new lp::SwitchStmt($4, $6);
        control--;
	}
  | SWITCH controlSymbol LPAREN exp RPAREN case_list DEFAULT COLON stmtlist END_SWITCH
	{
		$$ = new lp::SwitchStmt($4, $6, new lp::AST($9));
        control--;
	}
	;

case_list:
  case_list case_stmt
    {
      $1->push_back($2);
      $$ = $1;
    }
  | case_stmt
		{
		$$ = new std::list<lp::Case *>();
		$$->push_back($1);
		}
	;

case_stmt:
  CASE exp COLON stmtlist
    {
      $$ = new lp::Case();
      $$->value = $2;
      $$->body = new lp::AST($4);
    }
;

	/*  NEW in example 17 */
cond: 	LPAREN exp RPAREN
		{ 
			$$ = $2;
		}
;


asgn:   VARIABLE ASIGNACION exp 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, $3);
		}

	|  VARIABLE ASIGNACION asgn 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, (lp::AssignmentStmt *) $3);
		}

	   /* NEW in example 11 */ 
	| CONSTANT ASIGNACION exp 
		{   
 			execerror("Error semántico en ASSIGNMENT: no está permitido modificar una constante ", $1);
		}
	   /* NEW in example 11 */ 
	| CONSTANT ASIGNACION asgn 
		{   
 			execerror("Error semántico en MULTIPLE ASSIGNMENT: no está permitido modificar una constante ", $1);
		}
;

asgn_plus:  VARIABLE ASIGNACIONPLUS exp
		{
			// Create a new print node
			 $$ = new lp::AssignmentPlusStmt($1, $3);
		}
	| CONSTANT ASIGNACIONPLUS exp 
		{   
 			execerror("Error semántico en ASSIGNMENT_PLUS: no está permitido modificar una constante ", $1);
		}
;	

asgn_minus:  VARIABLE ASIGNACIONMINUS exp
		{
			 $$ = new lp::AssignmentMinusStmt($1, $3);
		}
	| CONSTANT ASIGNACIONMINUS exp 
		{   
 			execerror("Error semántico en ASSIGNMENT_MINUS: no está permitido modificar una constante ", $1);
		}
;	

print:  PRINT LPAREN exp RPAREN
		{
			 $$ = new lp::PrintStmt($3);
		}
;	

read:  READ LPAREN VARIABLE RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmt($3);
		}

  	  /* NEW rule in example 11 */
	| READ LPAREN CONSTANT RPAREN  
		{   
 			execerror("Error semántico en READ: no está permitido modificar una constante ", $3);
		}
;

read_string:  READ_STRING LPAREN VARIABLE RPAREN  
		{
			// Create a new read_string node
			 $$ = new lp::ReadStringStmt($3);
		}

  	  /* NEW rule in example 11 */
		| READ_STRING LPAREN CONSTANT RPAREN  
		{   
 			execerror("Error semántico en READ_STRING: no está permitido modificar una constante ", $3);
		}
;

increment:  VARIABLE PLUSPLUS %prec UNARY
		{
			// Create a new increment node
			 $$ = new lp::IncrementStmt($1);
		}
;	

decrement:  VARIABLE MINUSMINUS %prec UNARY
		{
			// Create a new decrement node
			 $$ = new lp::DecrementStmt($1);
		}
;	

exp:	NUMBER 
		{ 
			// Create a new number node
			$$ = new lp::NumberNode($1);
		}

	| 	STRING 
		{ 
			// Create a new string node
			$$ = new lp::StringNode($1);
		}

	| 	exp PLUS exp 
		{ 
			// Create a new plus node
			 $$ = new lp::PlusNode($1, $3);
		 }

	| 	exp MINUS exp
      	{
			// Create a new minus node
			$$ = new lp::MinusNode($1, $3);
		}

	| 	exp MULTIPLICATION exp 
		{ 
			// Create a new multiplication node
			$$ = new lp::MultiplicationNode($1, $3);
		}

	| 	exp DIVISION exp
		{
		  // Create a new division node	
		  $$ = new lp::DivisionNode($1, $3);
	   }

	| 	exp DIVISION_ENTERA exp
		{
		  // Create a new wholedivision node	
		  $$ = new lp::WholeDivisionNode($1, $3);
	   }

	| 	LPAREN exp RPAREN
       	{ 
		    // just copy up the expression node 
			$$ = $2;
		 }

  	| 	PLUS exp %prec UNARY
		{ 
		  // Create a new unary plus node	
  		  $$ = new lp::UnaryPlusNode($2);
		}

	| 	MINUS exp %prec UNARY
		{ 
		  // Create a new unary minus node	
  		  $$ = new lp::UnaryMinusNode($2);
		}

	|	exp MODULO exp 
		{
		  // Create a new modulo node	
		  $$ = new lp::ModuloNode($1, $3);
       }

	|	exp POWER exp 
     	{ 
		  // Create a new power node	
  		  $$ = new lp::PowerNode($1, $3);
		}

	|	exp CONCATENACION exp 
     	{ 
		  // Create a new power node	
  		  $$ = new lp::ConcatenationNode($1, $3);
		}

	|	cond QUESTION exp COLON exp %prec QUESTION_MARK
     	{ 
		  // Create a new power node	
  		  $$ = new lp::AlternativeNode($1, $3, $5);
		}


	 | VARIABLE
		{
		  // Create a new variable node	
		  $$ = new lp::VariableNode($1);
		}

	 | CONSTANT
		{
		  // Create a new constant node	
		  $$ = new lp::ConstantNode($1);

		}

	| BUILTIN LPAREN listOfExp RPAREN
		{
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol($1);

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) $3->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							$$ = new lp::BuiltinFunctionNode_0($1);
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = $3->front();

							// Create a new Builtin Function with 1 parameter node	
							$$ = new lp::BuiltinFunctionNode_1($1,e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = $3->front();
							$3->pop_front();
							lp::ExpNode *e2 = $3->front();

							// Create a new Builtin Function with 2 parameters node	
							$$ = new lp::BuiltinFunctionNode_2($1,e1,e2);
						}
						break;

					default:
				  			 execerror("Error sintáctico: demasiados parámetros para la función ", $1);
				} 
			}
			else
	  			 execerror("Error sintáctico: número incompatible de parámetros para la función ", $1);
		}

	| exp GREATER_THAN exp
	 	{
		  // Create a new "greater than" node	
 			$$ = new lp::GreaterThanNode($1,$3);
		}

	| exp GREATER_OR_EQUAL exp 
	 	{
		  // Create a new "greater or equal" node	
 			$$ = new lp::GreaterOrEqualNode($1,$3);
		}

	| exp LESS_THAN exp 	
	 	{
		  // Create a new "less than" node	
 			$$ = new lp::LessThanNode($1,$3);
		}

	| exp LESS_OR_EQUAL exp 
	 	{
		  // Create a new "less or equal" node	
 			$$ = new lp::LessOrEqualNode($1,$3);
		}

	| exp EQUAL exp 	
	 	{
		  // Create a new "equal" node	
 			$$ = new lp::EqualNode($1,$3);
		}

    | exp NOT_EQUAL exp 	
	 	{
		  // Create a new "not equal" node	
 			$$ = new lp::NotEqualNode($1,$3);
		}

    | exp AND exp 
	 	{
		  // Create a new "logic and" node	
 			$$ = new lp::AndNode($1,$3);
		}

    | exp OR exp 
	 	{
		  // Create a new "logic or" node	
 			$$ = new lp::OrNode($1,$3);
		}

    | NOT exp 
	 	{
		  // Create a new "logic negation" node	
 			$$ = new lp::NotNode($2);
		}
;


listOfExp: 
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

	|  exp restOfListOfExp
			{
				$$ = $2;

				// Insert the expression in the list of expressions
				$$->push_front($1);
			}
;

restOfListOfExp:
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

		|	COMMA exp restOfListOfExp
			{
				// Get the list of expressions
				$$ = $3;

				// Insert the expression in the list of expressions
				$$->push_front($2);
			}
;



%%



