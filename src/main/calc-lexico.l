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
minuscula [a-z]
digito [0-9]   

%%

{digito}+                   { 
								yylval.i = atoi(yytext);
                            	printf("INT : %d\n",atoi(yytext)); 
                            	return INT;}

"return"					{ 
								printf("Return : %s\n",yytext);
								return TReturn;}

"program"					{ 
								printf("Program : %s\n",yytext);
								return TProgram;}

"if"					{ 
								printf("If : %s\n",yytext);
								return TIf;}

"then"					{ 
								printf("Then : %s\n",yytext);
								return TThen;}

"else"					{ 
								printf("Else : %s\n",yytext);
								return TElse;}

"while"					{ 
								printf("While : %s\n",yytext);
								return TWhile;}

"extern"					{ 
							    printf("TExtern : %s\n",yytext);
								return TExtern;}

"true"                      { 
								yylval.i = 1;
							    printf("TTRUE : %s\n",yytext);
								return TTRUE;}

"false"                     { 
								yylval.i = 0;
							    printf("TFALSE : %s\n",yytext);
								return TFALSE;}

"int"                      	{	 
							    printf("TINT : %s\n",yytext);
								return TINT;}

"bool"                      { 
							    printf("TBOOL : %s\n",yytext);
								return TBOOL;}

"void"						{
							    printf("TVOID : %s\n",yytext);
								return TVOID;}

"//".*"\n"                 	; /* ignore comments */

"\*/".*"\*/"    			{	printf("-> ERROR Simbolo invalido: %s: En linea : %d\n", yytext, yylineno); 
							 	exit(0);} 

"/\*"(.*|.*\n|\n)*"\*/"     ; /* ignore comments */

{minuscula}({letra}|{digito}|_)* { 
								printf("ID : %s\n",yytext);
								yylval.s = (char *) malloc(sizeof(yytext)*yyleng);
    							strcpy(yylval.s, yytext);
    							return ID;}

"&&"						{	printf("%s\n",yytext);
                            	return TAND;}

"||"						{	printf("%s\n",yytext);
                            	return TOR;}

"=="						{	printf("%s\n",yytext);
                            	return TIGUAL;}

"-"                       	{	printf("%s\n",yytext);
                            	return TMENOS;}    

[+*%/=;()<>!{},]             {	printf("%s\n",yytext);
                                return *yytext;}

\n|" "|\t                        ; /* ignore all the rest */


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
