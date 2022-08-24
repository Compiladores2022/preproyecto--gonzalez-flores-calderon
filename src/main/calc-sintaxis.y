%{

#include <stdlib.h>
#include <stdio.h>

%}

 
%token INT
%token END
%token ID
%token BOOL 
%token TMENOS
%token TBOOL
%token TINT
%token TOR
%token TAND
%token TTRUE
%token TFALSE

%type expr
%type VALOR
    
%left '+' TMENOS 
%left '*' 
%left TAND
%left TOR
 
%%
 
prog: declList sentList
    
    | sentList
    ;

declList: decl

    | decl declList
    ;

decl: type ID '=' expr ';'
    ;

sentList: sent
    | sentList  sent
    ;

sent: ID "=" expr ";"

    | expr ";"

    | Return expr ";"
    ;
expr: VALOR               

    | expr '+' expr    
    
    | expr '*' expr

    | expr TMENOS expr  

    | '(' expr ')'

    | expr TOR expr    
    
    | expr TAND expr    
    ;   

VALOR: INT
    
    | TFALSE
    
    | TTRUE              
    ;

type: TINT

    | TBOOL
    ;

%%


