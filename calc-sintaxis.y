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
 
prog: expr ';' nextLine { printf("No hay errores \n"); } 
    ;
  
nextLine: expr ';' nextLine

    | END
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

%%


