%{

#include <stdlib.h>
#include <stdio.h>
#include "symbol_list/symbol_list.h"
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "types/symbol.h"

void yyerror();
int yylex();

SymbolList *list;

%}

%union {int i;
        char *s;
        struct Node *n;
        enum types t;} 

%token INT
%token END
%token ID
%token BOOL 
%token COMMENT
%token TMENOS
%token TBOOL
%token TINT
%token TOR
%token TAND
%token TTRUE
%token TFALSE
%token TReturn

%type<n> expr
%type<i> VALOR
%type<t> type
%type<s> ID

%left '+' TMENOS 
%left '*' 
%left TAND
%left TOR
 
%%


inil: prog {initialize(list);}
    ;

prog: declList sentList
    
    | sentList
    ;

declList: decl

    | decl declList
    ;

decl: type ID '=' expr ';' { Symbol *s = createSymbol($1, $2); insert(list, s); }
    ;

sentList: sent

    | sentList COMMENT
    
    | sentList  sent
    ;

sent: ID '=' expr ';' { if (search(list, $1) == NULL) {
                            printf("Undefined symbol %s\n", $1);
                            yyerror();
                        }}

    | expr ';'

    | TReturn expr ';'
    ;

expr: VALOR
    
    | ID { if (search(list, $1) == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }}

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

type: TINT {/*Type int */ $$ = INT;}

    | TBOOL {/*Type bool */$$ = BOOL;}
    ;

%%


