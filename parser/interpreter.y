%{
#include <iostream>
#include <string>
#include <cmath>
#include <setjmp.h>
#include <signal.h>
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

%parse-param { int &control }
%lex-param { int &lineNumber }

%union {
    double number;
    char* string;
    bool logic;
    lp::ExpNode* expNode;
    std::list<lp::ExpNode*>* parameters;
    std::list<lp::Statement*>* stmts;
    lp::Statement* st;
    lp::Case* caseptr;
    std::list<lp::Case*>* caselist;
    lp::AST* prog;
}

%token SEMICOLON COMMA
%token PRINT READ READ_STRING
%token IF THEN ELSE END_IF
%token WHILE DO END_WHILE
%token CLEAR_SCREEN PLACE
%token REPEAT UNTIL FOR END_FOR FROM STEP TO
%token SWITCH CASE DEFAULT END_SWITCH
%token COLON
%token PLUSPLUS MINUSMINUS
%token ASSIGNACION ASSIGNACIONPLUS ASSIGNACIONMINUS
%token QUESTION

%token PLUS MINUS MULTIPLICATION DIVISION MODULO POWER
%token DIVISION_ENTERA
%token CONCATENACION
%token LPAREN RPAREN
%token GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL
%token OR AND NOT

%token <number> NUMBER
%token <logic> BOOL
%token <string> STRING
%token <string> VARIABLE CONSTANT BUILTIN

%nonassoc THEN
%nonassoc ELSE

%right ASSIGNACION
%right ASSIGNACIONPLUS
%right ASSIGNACIONMINUS
%left OR
%left AND
%right NOT
%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL
%left CONCATENACION
%left PLUS MINUS
%left MULTIPLICATION DIVISION DIVISION_ENTERA MODULO
%right POWER
%left UNARY
%right QUESTION

%type <expNode> exp cond
%type <parameters> listOfExp restOfListOfExp
%type <stmts> stmtlist
%type <st> stmt asgn asgn_plus asgn_minus print read read_string increment decrement if while repeat for switch
%type <prog> program
%type <caseptr> case_stmt
%type <caselist> case_list
%type <string> for_variable  <!-- CORRECCIÓN CLAVE: Nuevo tipo añadido -->

%start program

%%

program : stmtlist
{
    $$ = new lp::AST($1);
    root = $$;
}
;

stmtlist : 
{
    $$ = new std::list<lp::Statement*>();
}
| stmtlist stmt
{
    $$ = $1;
    $$->push_back($2);
    
    if (interactiveMode && control == 0) {
        for(auto stmt : *$$) {
            stmt->evaluate();
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

stmt : SEMICOLON
{
    $$ = new lp::EmptyStmt();
}
| asgn SEMICOLON
| asgn_plus SEMICOLON
| asgn_minus SEMICOLON
| print SEMICOLON
| read SEMICOLON
| read_string SEMICOLON
| increment SEMICOLON
| decrement SEMICOLON
| if
| while
| repeat
| for
| switch
| CLEAR_SCREEN SEMICOLON
{
    $$ = new lp::ClearScreenStmt();
}
| PLACE LPAREN exp COMMA exp RPAREN SEMICOLON
{
    $$ = new lp::PlaceStmt($3, $5);
}
;

controlSymbol : /* empty */
{
    control++;
}
;

if : IF controlSymbol cond THEN stmtlist END_IF
{
    $$ = new lp::IfStmt($3, new lp::AST($5));
    control--;
}
| IF controlSymbol cond THEN stmtlist ELSE stmtlist END_IF
{
    $$ = new lp::IfStmt($3, new lp::AST($5), new lp::AST($7));
    control--;
}
;

while : WHILE controlSymbol cond DO stmtlist END_WHILE
{
    $$ = new lp::WhileStmt($3, new lp::AST($5));
    control--;
}
;

repeat : REPEAT controlSymbol stmtlist UNTIL cond
{
    $$ = new lp::RepeatStmt(new lp::AST($3), $5);
    control--;
}
;

<!-- SECCIÓN CORREGIDA: Nuevo no terminal for_variable -->
for_variable : VARIABLE { $$ = $1; }
             | CONSTANT {
                 lp::execerror("No se puede modificar constante en FOR", $1);
                 $$ = $1;  // Continuar con el análisis
               }
             ;

for : FOR controlSymbol for_variable FROM exp TO exp DO stmtlist END_FOR
{
    $$ = new lp::ForStmt($3, $5, $7, new lp::AST($9));
    control--;
}
| FOR controlSymbol for_variable FROM exp TO exp STEP exp DO stmtlist END_FOR
{
    $$ = new lp::ForStmt($3, $5, $7, $9, new lp::AST($11));
    control--;
}
;

switch : SWITCH controlSymbol LPAREN exp RPAREN case_list END_SWITCH
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

case_list : case_list case_stmt
{
    $1->push_back($2);
    $$ = $1;
}
| case_stmt
{
    $$ = new std::list<lp::Case*>();
    $$->push_back($1);
}
;

case_stmt : CASE exp COLON stmtlist
{
    $$ = new lp::Case($2, new lp::AST($4));
}
;

cond : LPAREN exp RPAREN
{
    $$ = $2;
}
;

asgn : VARIABLE ASSIGNACION exp
{
    $$ = new lp::AssignmentStmt($1, $3);
}
| CONSTANT ASSIGNACION exp
{
    lp::execerror("No se puede modificar constante", $1);
}
;

asgn_plus : VARIABLE ASSIGNACIONPLUS exp
{
    $$ = new lp::AssignmentPlusStmt($1, $3);
}
| CONSTANT ASSIGNACIONPLUS exp
{
    lp::execerror("No se puede modificar constante", $1);
}
;

asgn_minus : VARIABLE ASSIGNACIONMINUS exp
{
    $$ = new lp::AssignmentMinusStmt($1, $3);
}
| CONSTANT ASSIGNACIONMINUS exp
{
    lp::execerror("No se puede modificar constante", $1);
}
;

print : PRINT LPAREN exp RPAREN
{
    $$ = new lp::PrintStmt($3);
}
;

read : READ LPAREN VARIABLE RPAREN
{
    $$ = new lp::ReadStmt($3);
}
| READ LPAREN CONSTANT RPAREN
{
    lp::execerror("No se puede leer en constante", $3);
}
;

read_string : READ_STRING LPAREN VARIABLE RPAREN
{
    $$ = new lp::ReadStringStmt($3);
}
| READ_STRING LPAREN CONSTANT RPAREN
{
    lp::execerror("No se puede leer en constante", $3);
}
;

increment : VARIABLE PLUSPLUS
{
    $$ = new lp::IncrementStmt($1);
}
;

decrement : VARIABLE MINUSMINUS
{
    $$ = new lp::DecrementStmt($1);
}
;

exp : NUMBER
{
    $$ = new lp::NumberNode($1);
}
| STRING
{
    $$ = new lp::StringNode($1);
}
| BOOL
{
    $$ = new lp::BoolNode($1);
}
| VARIABLE
{
    $$ = new lp::VariableNode($1);
}
| CONSTANT
{
    $$ = new lp::ConstantNode($1);
}
| BUILTIN LPAREN listOfExp RPAREN
{
    lp::Builtin* f = (lp::Builtin*)table.getSymbol($1);
    if (f->getNParameters() == (int)$3->size()) {
        switch($3->size()) {
            case 0: $$ = new lp::BuiltinFunctionNode_0($1); break;
            case 1: $$ = new lp::BuiltinFunctionNode_1($1, $3->front()); break;
            case 2: {
                auto it = $3->begin();
                lp::ExpNode* p1 = *it++;
                lp::ExpNode* p2 = *it;
                $$ = new lp::BuiltinFunctionNode_2($1, p1, p2);
                break;
            }
            default: 
                lp::execerror("Demasiados parámetros", $1);
        }
    } else {
        lp::execerror("Número incorrecto de parámetros", $1);
    }
}
| exp PLUS exp { $$ = new lp::PlusNode($1, $3); }
| exp MINUS exp { $$ = new lp::MinusNode($1, $3); }
| exp MULTIPLICATION exp { $$ = new lp::MultiplicationNode($1, $3); }
| exp DIVISION exp { $$ = new lp::DivisionNode($1, $3); }
| exp DIVISION_ENTERA exp { $$ = new lp::WholeDivisionNode($1, $3); }
| exp MODULO exp { $$ = new lp::ModuloNode($1, $3); }
| exp POWER exp { $$ = new lp::PowerNode($1, $3); }
| exp CONCATENACION exp { $$ = new lp::ConcatenationNode($1, $3); }
| exp GREATER_THAN exp { $$ = new lp::GreaterThanNode($1, $3); }
| exp GREATER_OR_EQUAL exp { $$ = new lp::GreaterOrEqualNode($1, $3); }
| exp LESS_THAN exp { $$ = new lp::LessThanNode($1, $3); }
| exp LESS_OR_EQUAL exp { $$ = new lp::LessOrEqualNode($1, $3); }
| exp EQUAL exp { $$ = new lp::EqualNode($1, $3); }
| exp NOT_EQUAL exp { $$ = new lp::NotEqualNode($1, $3); }
| exp AND exp { $$ = new lp::AndNode($1, $3); }
| exp OR exp { $$ = new lp::OrNode($1, $3); }
| NOT exp { $$ = new lp::NotNode($2); }
| PLUS exp %prec UNARY { $$ = new lp::UnaryPlusNode($2); }
| MINUS exp %prec UNARY { $$ = new lp::UnaryMinusNode($2); }
| cond QUESTION exp COLON exp %prec QUESTION { $$ = new lp::AlternativeNode($1, $3, $5); }
| LPAREN exp RPAREN { $$ = $2; }
| VARIABLE PLUSPLUS %prec UNARY { $$ = new lp::IncrementExpNode($1); }
| VARIABLE MINUSMINUS %prec UNARY { $$ = new lp::DecrementExpNode($1); }
;

listOfExp : 
{
    $$ = new std::list<lp::ExpNode*>();
}
| exp restOfListOfExp
{
    $2->push_front($1);
    $$ = $2;
}
;

restOfListOfExp : 
{
    $$ = new std::list<lp::ExpNode*>();
}
| COMMA exp restOfListOfExp
{
    $3->push_front($2);
    $$ = $3;
}
;

%%

void yyerror(const char* s) {
    std::cerr << progname << ":" << lineNumber << ": Error: " << s << std::endl;
}