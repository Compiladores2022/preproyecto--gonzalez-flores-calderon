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
 

prog: declList sentList { $$ = newDeclarationTree($1, $2); }
    
    | sentList { $$ = $1; }
    ;

declList: decl          { $$ = newDeclarationTree(NULL, $1); }

    | decl declList     { $$ = newDeclarationTree($2, $1); }
    ;

decl: type ID '=' expr ';'  {   if (searchInLevel(list.head->levelSymbols, $2) != NULL) {
                                    printf("Multiple definitions of: %s", $2);
                                    yyerror();
                                }
                                Symbol *newID = createSymbol($1, $2, NULL);
                                insert(&list, newID);
                                struct TreeNode * idNode = createNode(newID);
                                Symbol *assignation = createSymbol(UNDEFINED, "=", NULL);
                                struct TreeNode * newTree = createTree(assignation, idNode, $4);
                                $$ = newTree; }
    ;

sentList: sent { $$ = $1; } 
    
    | sent sentList     {   Symbol *s = createSymbol(UNDEFINED, "next", NULL);
                            struct TreeNode * newTree = createTree(s, $2, $1);
                            $$ = newTree; }
    ;

sent: ID '=' expr ';'   {   Symbol * idSymbol = search(&list, $1);
                            if (idSymbol == NULL) { 
                                printf("Undefined Symbol %s", $1);
                                yyerror();
                            }
                            Symbol *s = createSymbol(UNDEFINED, "=", NULL);
                            struct TreeNode * idNode = createNode(idSymbol);
                            struct TreeNode * newTree = createTree(s, idNode, $3);
                            $$ = newTree; }

    | expr ';' { $$ = $1; }

    | TReturn expr ';'  {   Symbol *s = createSymbol(UNDEFINED, "return", NULL);
                            struct TreeNode * newTree = createTree(s, NULL, $2);
                            $$ = newTree; }
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

    | expr '+' expr {   Symbol *s = createSymbol(INT, "+", NULL);
                        struct TreeNode * newTree = createTree(s, $1, $3);
                        $$ = newTree; }
    
    | expr '*' expr {   Symbol *s = createSymbol(INT, "*", NULL);
                        struct TreeNode * newTree = createTree(s, $1, $3);
                        $$ = newTree; }

    | expr TMENOS expr  {   Symbol *s = createSymbol(INT, "-", NULL);
                            struct TreeNode * newTree = createTree(s, $1, $3);
                            $$ = newTree; }

    | '(' expr ')' { $$ = $2; }

    | expr TOR expr     {   Symbol *s = createSymbol(BOOL, "||", NULL);
                            struct TreeNode * newTree = createTree(s, $1, $3);
                            $$ = newTree; }
    
    | expr TAND expr    {   Symbol *s = createSymbol(BOOL, "&&", NULL);
                            struct TreeNode * newTree = createTree(s, $1, $3);
                            $$ = newTree; }
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
