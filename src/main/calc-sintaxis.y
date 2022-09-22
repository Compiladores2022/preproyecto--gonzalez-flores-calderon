%{

#include <stdlib.h>
#include <stdio.h>
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "utils.h"
#include "symbol_list/symbol_list.h"

SymbolList list;
SintacticAnalysisTree sat;
void yyerror();
int yylex();

%}

%union {int i;
        char *s;
        struct TreeNode *n;}

%token<i> INT
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
%token TReturn

%type<n> inil
%type<n> prog
%type<n> declList
%type<n> decl
%type<n> sentList
%type<n> sent
%type<n> expr
%type<i> VALORINT
%type<i> VALORBOOL
%type<i> type
%type<s> ID

%left '+' TMENOS 
%left '*' 
%left TAND
%left TOR

%%


inil: { initialize(&list);} prog {  printTree($2); }
    ;
 

prog: declList sentList { $$ = createNextTree($1, $2); }

    | sentList { $$ = $1; }
    ;

declList: decl          { $$ = createNextTree(NULL, $1); }

    | decl declList     { $$ = createNextTree($2, $1); }
    ;
//check
decl: type ID '=' expr ';'  {   if (searchInLevel(list.head->levelSymbols, $2) != NULL) {
                                    printf("Multiple definitions of: %s", $2);
                                    yyerror();
                                }

                                Symbol *newID = createSymbol($1, $2, NULL);
                                insert(&list, newID);
                                struct TreeNode * idNode = createNode(newID);
                                $$ = createNewTree(UNDEFINED, idNode, $4, "="); }
    ;

sentList: sent { $$ = $1; } 
    |  sent sentList     {   $$ = createNextTree($2, $1); }
    ;

sent: ID '=' expr ';'   {   Symbol * idSymbol = search(&list, $1);
                            if (idSymbol == NULL) { 
                                printf("Undefined Symbol %s", $1);
                                yyerror();
                            }
                            struct TreeNode * idNode = createNode(idSymbol);
                            $$ = createNewTree(UNDEFINED, idNode, $3, "="); }

    | expr ';' { $$ = $1; }

    | TReturn expr ';'  { $$ = createNewTree(UNDEFINED, NULL, $2, "return"); }
    ;

expr: VALORINT  {   char *str = malloc(sizeof(char *));
                    sprintf(str, "%d", $1);
                    Symbol *s = createSymbol(INT, str, &$1);
                    
                    struct TreeNode *newNode = createNode(s);
                    $$ = newNode; }

    | VALORBOOL {   char * boolValue = $1 == 1 ? "true" : "false";
                    Symbol *s = createSymbol(BOOL, boolValue, &$1);
                    $$ = createNode(s); }
    
    | ID {  Symbol *s = search(&list, $1);
            if (s == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }
            $$ = createNode(s); }

    | expr '+' expr { $$ = createNewTree(TYPEINT, $1, $3, "+"); }
    
    | expr '*' expr { $$ = createNewTree(TYPEINT, $1, $3, "*"); }

    | expr TMENOS expr  { $$ = createNewTree(TYPEINT, $1, $3, "-"); }

    | '(' expr ')' { $$ = $2; }

    | expr TOR expr     { $$ = createNewTree(TYPEBOOL, $1, $3, "||"); }
    
    | expr TAND expr    { $$ = $$ = createNewTree(TYPEBOOL, $1, $3, "&&"); }
    ;   

VALORINT: INT { $$ = $1; }
    ;

VALORBOOL: TFALSE    { $$ = 1; }

    | TTRUE { $$ = 1; }
    ;

type: TINT {/*Type int */ $$ = TYPEINT;}

    | TBOOL {/*Type bool */$$ = TYPEBOOL;}
    ;

%%
