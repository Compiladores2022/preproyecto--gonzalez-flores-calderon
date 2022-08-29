%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "calc-sintaxis.tab.h"

void yyerror();
%}

%option noyywrap
%option yylineno

letra [a-zA-Z]      
digito [0-9]   

%%

{digito}+                   { 
                            	printf("INT : %d\n",atoi(yytext)); 
                            	return INT;}

"return"					{ 
								printf("Return : %s\n",yytext);
								return TReturn;}

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

"//".*"\n"                      { 
							    printf("COMMENT : %s\n",yytext);
								return COMMENT;}

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

\n|" "                        ; /* ignore all the rest */


.							{	printf("-> ERROR Simbolo invalido: %s: En linea : %d\n", yytext, yylineno); 
							 	exit(0);} 
%%

void yyerror(){
	printf("%s%d\n","-> ERROR Sintactico en la linea: ",yylineno); 
	exit(0);
}

int main(int argc,char *argv[]) {
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}
