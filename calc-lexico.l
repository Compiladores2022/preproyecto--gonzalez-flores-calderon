%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "calc-sintaxis.tab.h"

%}

%option noyywrap
%option yylineno

letra [a-zA-Z]      
digito [0-9]   


%%

{digito}+                     { 
                                printf("INT : %d\n",atoi(yytext)); 
                                return INT;}

"end"						  { 
                                printf("PROGRAM END : %s\n",yytext);
                                return ;}

{letra}({letra}|{digito})*    { 
                                printf("ID : %s\n",yytext);
                                return END;}

"-"                       {  printf("%s\n",yytext);
                                  return TMENOS;}    

[+*;()]                   {  printf("%s\n",yytext);
                                  return *yytext;}

.|\n                          ; /* ignore all the rest */

%%

void yyerror(){
	printf("%s%d\n","-> ERROR Sintactico en la linea: ",yylineno);
}

int main(int argc,char *argv[]){
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}
