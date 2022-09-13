%code requires {
    #include "types/symbol.h"    
}

%{

#include <stdlib.h>
#include <stdio.h>
#include "symbol_list/symbol_list.h"
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"

void yyerror();
int yylex();

SymbolList *list;

%}

%union {int i;
        char *s;
        struct TreeNode *n;
        types t;}

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
%type<i> VALORINT
%type<i> VALORBOOL
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

decl: type ID '=' expr ';' { Symbol s = createSymbol($1, $2, NULL); insert(list, &s); }
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

expr: VALORINT

    | VALORBOOL
    
    | ID { if (search(list, $1) == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }}

    | expr '+' expr    
    
    | expr '*' expr

    | expr TMENOS expr  

    | '(' expr ')' { $$ = $2; }

    | expr TOR expr    
    
    | expr TAND expr    
    ;   

VALORINT: INT
    ;

VALORBOOL: TFALSE
    
    | TTRUE              
    ;

type: TINT {/*Type int */ $$ = TYPEINT;}

    | TBOOL {/*Type bool */$$ = TYPEBOOL;}
    ;

%%


