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

{digito}+                   { 
                            	printf("INT : %d\n",atoi(yytext)); 
                            	return INT;}

"true"                      { 
							    printf("TTRUE : %s\n",yytext);
								return TTRUE;}

"false"                      { 
							    printf("TFALSE : %s\n",yytext);
								return TFALSE;}

"int"                      { 
							    printf("TINT : %s\n",yytext);
								return TINT;}

"bool"                      { 
							    printf("TBOOL : %s\n",yytext);
								return TBOOL;}

{letra}({letra}|{digito})*  { 
								printf("ID : %s\n",yytext);
								return ID;}

"&&"						{	printf("%s\n",yytext);
                            	return TAND;}

"||"						{	printf("%s\n",yytext);
                            	return TOR;}

"-"                       	{	printf("%s\n",yytext);
                            	return TMENOS;}    

[+*=;()]                    {	printf("%s\n",yytext);
                                return *yytext;}

.|\n                        ; /* ignore all the rest */

%%

void yyerror(){
	printf("%s%d\n","-> ERROR Sintactico en la linea: ",yylineno);
}

int main(int argc,char *argv[]) {
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}