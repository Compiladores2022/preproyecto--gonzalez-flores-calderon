%{

#include <stdlib.h>
#include <stdio.h>

%}
 
%token INT
%token ID
%token TMENOS

%type expr
%type VALOR
    
%left '+' TMENOS 
%left '*'
 
%%
 
prog: expr ';'  { printf("No hay errores \n"); } 
    ;
  
expr: VALOR               

    | expr '+' expr    
    
    | expr '*' expr

    | expr TMENOS expr  

    | '(' expr ')'      
    ;


VALOR : INT              
       ;
 
%%


