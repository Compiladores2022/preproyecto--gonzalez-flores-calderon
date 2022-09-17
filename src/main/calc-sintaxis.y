%{

#include <stdlib.h>
#include <stdio.h>
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "utils.h"
#include "symbol_list/symbol_list.h"
SymbolList list;
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


inil: { initialize(&list);} prog { printTreeInOrder($2); }
    ;
 
// SintacticAnalysisTree sat;

prog: declList sentList {   Symbol s = createSymbol(UNDEFINED, "next", NULL);
                            struct TreeNode * newTree = createTree(&s, $1, $2);
                            $$ = newTree; }
    
    | sentList { $$ = $1; }
    ;

declList: decl          {   Symbol s = createSymbol(UNDEFINED, "next", NULL);
                            struct TreeNode * newTree = createTree(&s, NULL, $1); }

    | decl declList     {   Symbol s = createSymbol(UNDEFINED, "next", NULL);
                            struct TreeNode * newTree = createTree(&s, $3, $1); }
    ;

decl: type ID '=' expr ';'  {   if (search(&list, $2) != NULL) {
                                    printf("Multiple definitions of: %s", $2);
                                    yyerror();
                                }
                                Symbol newID = createSymbol($1, $2, NULL); insert(&list, &newID);
                                struct TreeNode * idNode = createNode(&newID);
                                Symbol assignation = createSymbol(UNDEFINED, "=", NULL);
                                struct TreeNode * newTree = createTree(&assignation, idNode, $4);
                                $$ = newTree; }
    ;

sentList: sent { $$ = $1; } 
    
    | sent sentList     {   Symbol s = createSymbol(UNDEFINED, "next", NULL);
                            struct TreeNode * newTree = createTree(&s, $2, $1);
                            $$ = newTree; }
    ;

sent: ID '=' expr ';'   {   Symbol * idSymbol = search(&list, $1);
                            if (idSymbol == NULL) { 
                                printf("Undefined Symbol %s", $1);
                                yyerror();
                            }
                            Symbol s = createSymbol(UNDEFINED, "=", NULL);
                            struct TreeNode * idNode = createNode(&s);
                            struct TreeNode * newTree = createTree(&s, idNode, $3);
                            $$ = newTree; }

    | expr ';' { $$ = $1; }

    | TReturn expr ';'  {   Symbol s = createSymbol(UNDEFINED, "return", NULL);
                            struct TreeNode * newTree = createTree(&s, NULL, $2);
                            $$ = newTree; }
    ;

expr: VALORINT  {   Symbol s = createSymbol(INT, NULL, &$1);
                    $$ = createNode(&s); }

    | VALORBOOL {   Symbol s = createSymbol(BOOL, NULL, &$1);
                    $$ = createNode(&s); }
    
    | ID {  Symbol *s = search(&list, $1);
            if (s == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }
            $$ = createNode(s); }

    | expr '+' expr {   Symbol s = createSymbol(INT, "+", NULL);
                        struct TreeNode * newTree = createTree(&s, $1, $3);
                        $$ = newTree; }
    
    | expr '*' expr {   Symbol s = createSymbol(INT, "*", NULL);
                        struct TreeNode * newTree = createTree(&s, $1, $3);
                        $$ = newTree; }

    | expr TMENOS expr  {   Symbol s = createSymbol(INT, "-", NULL);
                            struct TreeNode * newTree = createTree(&s, $1, $3);
                            $$ = newTree; }

    | '(' expr ')' { $$ = $2; }

    | expr TOR expr     {   Symbol s = createSymbol(BOOL, "||", NULL);
                            struct TreeNode * newTree = createTree(&s, $1, $3);
                            $$ = newTree; }
    
    | expr TAND expr    {   Symbol s = createSymbol(BOOL, "&&", NULL);
                            struct TreeNode * newTree = createTree(&s, $1, $3);
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
