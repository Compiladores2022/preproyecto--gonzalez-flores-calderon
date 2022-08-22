%{

#include <stdlib.h>
#include <stdio.h>

%}
 
%token INT
%token END
%token ID
%token TMENOS

%type expr
%type VALOR
    
%left '+' TMENOS 
%left '*'
 
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
    ;


VALOR : INT              
       ;
 
%%


