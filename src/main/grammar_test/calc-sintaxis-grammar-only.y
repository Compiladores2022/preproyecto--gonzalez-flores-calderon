%{

#include <stdlib.h>
#include <stdio.h>

void yyerror();
int yylex();

%}

%union {int i;
        char *s;}

%token INT
%token ID
%token TMENOS
%token TBOOL
%token TINT
%token TOR
%token TAND
%token TTRUE
%token TFALSE
%token TReturn
%token TVOID
%token TIf
%token TElse
%token TWhile
%token TExtern
%token TThen
%token TProgram
%token TIGUAL

%type inil
%type prog
%type methodDeclList
%type methodDecl
%type body
%type block
%type statement
%type statementList
%type methodCall
%type exprList
%type listParameters
%type parameter
%type declList
%type decl
%type expr
%type VALORINT
%type VALORBOOL
%type type
%type ID
%type literal



%left TAND
%left TOR
%nonassoc '<' '>' TIGUAL
%left '+' TMENOS
%left '*' '%' '/'
%right UNARYPREC

%%

inil: prog 
    ;    

prog: TProgram '{' declList methodDeclList '}' 

    | TProgram '{' methodDeclList '}'
    ;

methodDeclList: methodDeclList methodDecl

    | methodDecl
    ;

methodDecl: type ID '('  ')' body

    | TVOID ID '('  ')' body

    | type ID '(' listParameters ')' body

    | TVOID ID '(' listParameters ')' body 
    ;

body: block
    
    | TExtern ';'
    ;

listParameters: parameter
    
    | listParameters ',' parameter
    ;

parameter: type ID
    ;

block: '{' '}'

    | '{' declList statementList '}'

    | '{' statementList '}'
    ;

declList: decl

    | declList decl
    ;

decl: type ID '=' expr ';'
    ;

statementList:  statement
    
    | statementList statement
    ;
    
statement: ID '=' expr ';'
    
    | methodCall ';'
    
    | TIf '(' expr ')' TThen block
    
    | TIf '(' expr ')' TThen block TElse block

    | TWhile '(' expr ')' block

    | TReturn expr ';'

    | TReturn ';'

    | ';'

    | block
    ; 
    
methodCall: ID '(' exprList ')'

    | ID '(' ')'
    ;

exprList: expr

    | expr ',' exprList
    ;

expr: ID

    | methodCall

    | literal

    | expr '+' expr

    | expr TMENOS expr

    | expr '*' expr

    | expr '/' expr

    | expr '%' expr

    | expr '>' expr

    | expr '<' expr

    | expr TIGUAL expr

    | expr TAND expr

    | expr TOR expr

    | TMENOS expr %prec UNARYPREC

    | '!' expr %prec UNARYPREC

    | '(' expr ')'
    ;

literal: VALORINT

    | VALORBOOL
    ;

VALORINT: INT
    ;

VALORBOOL: TFALSE

    | TTRUE
    ;

type: TINT

    | TBOOL
    ;

%%
