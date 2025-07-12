%{
#include <iostream>
#include <string>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <cstring>
#include <list>

#include "../error/error.hpp"
#include "../includes/macros.hpp"
#include "../ast/ast.hpp"
#include "../table/table.hpp"
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"
#include "../table/init.hpp"

extern "C" int yylex();
extern int lineNumber;
extern bool interactiveMode;
extern int control;
extern std::string progname;
extern jmp_buf begin;
extern lp::Table table;
extern lp::AST *root;

void yyerror(const char *s);
%}

%code requires {
#include "../ast/ast.hpp"
#include <list>
}

%define parse.error verbose
%start program

%union {
  double number;
  char * string;
  bool logic;
  lp::ExpNode *expNode;
  std::list<lp::ExpNode *> *parameters;
  std::list<lp::Statement *> *stmts;
  lp::Statement *st;
  lp::Case *switchcase;
  std::list<lp::Case *> *switchcases;
  lp::AST *prog;
}

%token <number> NUMBER
%token <logic> BOOL
%token <string> STRINGLITERAL 

%token PRINT READ READ_STRING
%token IF THEN ELSE END_IF
%token WHILE DO END_WHILE
%token CLEAR_SCREEN PLACE
%token REPEAT UNTIL FOR END_FOR FROM STEP TO
%token SWITCH CASE DEFAULT END_SWITCH
%token COLON

%token SEMICOLON COMMA ASSIGNMENT
%token PLUS MINUS MULTIPLICATION DIVISION MODULO POWER
%token INTDIV
%token CONCAT
%token LPAREN RPAREN
%token GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL
%token OR AND NOT

%token <string> VARIABLE
%token <string> CONSTANT
%token <string> BUILTIN

%right ASSIGNMENT
%left OR
%left AND
%right NOT
%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL
%left CONCAT
%left PLUS MINUS
%left MULTIPLICATION DIVISION MODULO
%left LPAREN RPAREN
%nonassoc UNARY
%right POWER

%type <expNode> exp cond stepOpt
%type <switchcases> switchcases
%type <switchcase> switchcase
%type <stmts> stmtlist
%type <st> stmt asgn print read
%type <prog> program

%%


program
    : stmtlist
      {
          $$ = new lp::AST($1);
          root = $$;
      }
    ;

stmtlist
    : /* vacío */
      {
          $$ = new std::list<lp::Statement *>();
      }
    | stmtlist stmt
      {
          $$ = $1;
          if($2 != NULL)
            $$->push_back($2);

          if (interactiveMode && control == 0) {
              std::list<lp::Statement *>::iterator it;
              for (it = $$->begin(); it != $$->end(); it++) {
                  (*it)->evaluate();
              }
              $$->clear();
          }
      }
    | stmtlist error SEMICOLON
      {
          yyerrok;
          $$ = $1;
      }
    ;

stmt
    : SEMICOLON
      {
          $$ = new lp::EmptyStmt();
      }
    | asgn SEMICOLON
      {
          $$ = $1;
      }
    | print SEMICOLON
      {
          $$ = $1;
      }
    | read SEMICOLON
      {
          $$ = $1;
      }
    | CLEAR_SCREEN SEMICOLON
      {
          $$ = new lp::ClearScreenStmt();
      }
    | PLACE LPAREN exp COMMA exp RPAREN SEMICOLON
      {
          $$ = new lp::PlaceStmt($3,$5);
      }
    | REPEAT stmtlist UNTIL cond
      {
          $$ = new lp::RepeatStmt(new lp::BlockStmt($2), $4);
      }
    | FOR VARIABLE FROM exp TO exp stepOpt DO stmtlist END_FOR
      {
          if (table.getSymbol($2) == NULL) {
              lp::execerror("Variable del bucle 'for' no declarada previamente", $2);
          }
          $$ = new lp::ForStmt($2, $4, $6, $7, new lp::BlockStmt($9));
      }
    | SWITCH LPAREN exp RPAREN switchcases END_SWITCH
      {
          $$ = new lp::SwitchStmt($3, $5);
      }
    | SWITCH LPAREN exp RPAREN switchcases DEFAULT COLON stmtlist END_SWITCH
      {
          $$ = new lp::SwitchStmt($3, $5, new lp::BlockStmt($8));
      }
    | WHILE cond DO stmtlist END_WHILE
      {
          $$ = new lp::WhileStmt($2, new lp::BlockStmt($4));
      }
    | IF cond THEN stmtlist END_IF
      {
          $$ = new lp::IfStmt($2, new lp::BlockStmt($4));
      }
    | IF cond THEN stmtlist ELSE stmtlist END_IF
      {
          $$ = new lp::IfStmt($2, new lp::BlockStmt($4), new lp::BlockStmt($6));
      }
    ;

asgn
    : VARIABLE ASSIGNMENT exp
      {
          $$ = new lp::AssignmentStmt($1, $3);
      }
    | CONSTANT ASSIGNMENT exp
      {
          lp::execerror("No se puede modificar una constante", $1);
          $$ = NULL;
      }
    ;

print
    : PRINT LPAREN exp RPAREN
      {
          $$ = new lp::PrintStmt($3);
      }
    | PRINT LPAREN STRINGLITERAL RPAREN
      {
          $$ = new lp::PrintStringStmt(new lp::StringNode($3));
      }
    ;

read
    : READ LPAREN VARIABLE RPAREN
      {
          $$ = new lp::ReadStmt($3);
      }
    | READ_STRING LPAREN VARIABLE RPAREN
      {
          $$ = new lp::ReadStringStmt($3);
      }
    | READ LPAREN CONSTANT RPAREN
      {
          lp::execerror("No se puede leer en una constante", $3);
          $$ = NULL;
      }
    | READ_STRING LPAREN CONSTANT RPAREN
      {
          lp::execerror("No se puede leer en una constante", $3);
          $$ = NULL;
      }
    ;

exp
    : NUMBER
      {
          $$ = new lp::NumberNode($1);
      }
    | BOOL
      {
          $$ = new lp::BoolNode($1);
      }
    | STRINGLITERAL
      {
          $$ = new lp::StringNode($3);
      }
    | VARIABLE
      {
          $$ = new lp::VariableNode($1);
      }
    | CONSTANT
      {
          $$ = new lp::ConstantNode($1);
      }
    | exp CONCAT exp
      {
          $$ = new lp::ConcatenationNode($1, $3);
      }
    | BUILTIN LPAREN exp RPAREN
      {
          $$ = new lp::BuiltinFunctionNode1($1, $3);
      }
    | PLUS exp %prec UNARY
      {
          $$ = new lp::UnaryPlusNode($2);
      }
    | MINUS exp %prec UNARY
      {
          $$ = new lp::UnaryMinusNode($2);
      }
    | exp PLUS exp
      {
          $$ = new lp::PlusNode($1, $3);
      }
    | exp MINUS exp
      {
          $$ = new lp::MinusNode($1, $3);
      }
    | exp MULTIPLICATION exp
      {
          $$ = new lp::MultiplicationNode($1, $3);
      }
    | exp DIVISION exp
      {
          $$ = new lp::DivisionNode($1, $3);
      }
    | exp MODULO exp
      {
          $$ = new lp::ModuloNode($1, $3);
      }
    | exp POWER exp
      {
          $$ = new lp::PowerNode($1, $3);
      }
    | LPAREN exp RPAREN
      {
          $$ = $2;
      }
    | exp GREATER_THAN exp
      {
          $$ = new lp::GreaterThanNode($1, $3);
      }
    | exp GREATER_OR_EQUAL exp
      {
          $$ = new lp::GreaterOrEqualNode($1, $3);
      }
    | exp LESS_THAN exp
      {
          $$ = new lp::LessThanNode($1, $3);
      }
    | exp LESS_OR_EQUAL exp
      {
          $$ = new lp::LessOrEqualNode($1, $3);
      }
    | exp EQUAL exp
      {
          $$ = new lp::EqualNode($1, $3);
      }
    | exp NOT_EQUAL exp
      {
          $$ = new lp::NotEqualNode($1, $3);
      }
    | exp AND exp
      {
          $$ = new lp::AndNode($1, $3);
      }
    | exp OR exp
      {
          $$ = new lp::OrNode($1, $3);
      }
    | NOT exp
      {
          $$ = new lp::NotNode($2);
      }
    | exp INTDIV exp
      {
          $$ = new lp::IntDivNode($1, $3);
      }
    ;

cond
    : LPAREN exp RPAREN
      {
          $$ = $2;
      }
    ;

stepOpt
    : /* vacío */
      {
          $$ = new lp::NumberNode(1);
      }
    | STEP exp
      {
          $$ = $2;
      }
    ;

switchcases
    : switchcases switchcase
      {
          $$ = $1;
          $$->push_back($2);
      }
    | switchcase
      {
          $$ = new std::list<lp::Case *>();
          $$->push_back($1);
      }
    ;

switchcase
    : CASE exp COLON stmtlist
      {
          $$ = new lp::Case($2, new lp::BlockStmt($4));
      }
    | DEFAULT COLON stmtlist
      {
          $$ = new lp::Case(nullptr, new lp::BlockStmt($3));
      }
    ;

%%

void yyerror(const char *s) {
    std::cerr << progname << ":" << lineNumber << ": error: " << s << std::endl;
}