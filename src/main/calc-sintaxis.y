%code requires {
    #include <stdlib.h>
    #include <stdio.h>
    #include "sintactic_analysis_tree/sintactic_analysis_tree.h"
    #include "utils.h"
    #include "symbol_list/symbol_list.h"
}

%{


void yyerror();
int yylex();
SymbolList *list;


%}

%union {int i;
        char *s;
        struct TreeNode *n;
        types t;}

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

%type<n> declList
%type<n> decl
%type<n> sentList
%type<n> sent
%type<n> expr
%type<i> VALORINT
%type<i> VALORBOOL
%type<t> type
%type<s> ID
%type<n> declList
%type<n> decl

%left '+' TMENOS 
%left '*' 
%left TAND
%left TOR

%%


inil: prog {initialize(list);}
    ;
 
// SintacticAnalysisTree sat;

prog: declList sentList
    
    | sentList
    ;

declList: decl          {   Symbol s = createSymbol($1->info->type, "next", NULL);
                            struct TreeNode * newNode = createTree(&s, NULL, $1);    
                        }

    | decl declList     {   Symbol s = createSymbol($1->info->type, "next", NULL);
                            struct TreeNode * newNode = createTree(&s, $2, $1);    
                        }
    ;

decl: type ID '=' expr ';'  {   if (search(list, $2) != NULL) {
                                    printf("Multiple definitions of: %s", $2);
                                    yyerror();
                                }
                                Symbol s = createSymbol($1, $2, NULL); insert(list, &s);
                            }
    ;

sentList: sent { $$ = $1; } 
    
    | sent sentList     {   Symbol s = createSymbol($1->info->type, "next", NULL);
                            struct TreeNode * newNode = createTree(&s, $2, $1);    
                        }
    ;

sent: ID '=' expr ';'   {   Symbol * idSymbol = search(list, $1);
                            if (idSymbol == NULL) { 
                                printf("Undefined Symbol %s", $1);
                                yyerror();
                            }
                            if(idSymbol->type != $3->info->type){
                                printf("Incompatible types");
                                yyerror();
                            }
                            Symbol s = createSymbol(idSymbol->type, "=", $3->info->value);
                            struct TreeNode * idNode = createNode(&s);
                            struct TreeNode * newNode = createTree(&s, idNode, $3);
                            $$ = newNode; 
                        }

    | expr ';' { $$ = $1; }

    | TReturn expr ';'  {   Symbol s = createSymbol($2->info->type, "return", $2->info->value);
                            struct TreeNode * newNode = createTree(&s, NULL, $2);
                            $$ = newNode; 
                        }
    ;

expr: VALORINT  { Symbol s = createSymbol(INT, NULL, &$1);
                    $$ = createNode(&s); }

    | VALORBOOL { Symbol s = createSymbol(BOOL, NULL, &$1);
                    $$ = createNode(&s); }
    
    | ID { Symbol *s = search(list, $1);
            if (s == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }Symbol s = createSymbol(idSymbol->type, "=", $3->info->value);
                            struct TreeNode * idNode = createNode(&s);
                            struct TreeNode * newNode = createTree(&s, idNode, $3);
                            $$ = newNode;
            $$ = createNode(s); }

    | expr '+' expr { if ($1->info->type != INT || $3->info->type != INT) {
                            printf("Incompatible types for + operation\nexpected: INT + INT\nfound:  %s + %s", enumToString($1->info->type), enumToString($3->info->type));
                            yyerror();
                        }
                        int sum = *(int *)$1->info->value + *(int *)$3->info->value;
                        Symbol s = createSymbol(INT, "+", &sum);
                        struct TreeNode * newNode = createTree(&s, $1, $3);
                        $$ = newNode; 
                    }
    
    | expr '*' expr { if ($1->info->type != INT || $3->info->type != INT) {
                            printf("Incompatible types for * operation\nexpected: INT * INT\nfound:  %s * %s", enumToString($1->info->type), enumToString($3->info->type));
                            yyerror();
                        }
                        int mult = *(int *)$1->info->value * *(int *)$3->info->value;
                        Symbol s = createSymbol(INT, "*", &mult);
                        struct TreeNode * newNode = createTree(&s, $1, $3);
                        $$ = newNode; 
                    }

    | expr TMENOS expr  {    if ($1->info->type != INT || $3->info->type != INT) {
                                printf("Incompatible types for - operation\nexpected: INT - INT\nfound:  %s - %s", enumToString($1->info->type), enumToString($3->info->type));
                                yyerror();
                            }
                            int subs = *(int *)$1->info->value - *(int *)$3->info->value;
                            Symbol s = createSymbol(INT, "-", &subs);
                            struct TreeNode * newNode = createTree(&s, $1, $3);
                            $$ = newNode; 
                        }

    | '(' expr ')' { $$ = $2; }

    | expr TOR expr     {   if ($1->info->type != BOOL || $3->info->type != BOOL) {
                                printf("Incompatible types for || operation\nexpected: BOOL || BOOL\nfound:  %s || %s", enumToString($1->info->type), enumToString($3->info->type));
                                yyerror();
                            }
                            int orResult = *(int *)$1->info->value || *(int *)$3->info->value;
                            Symbol s = createSymbol(BOOL, "||", &orResult);
                            struct TreeNode * newNode = createTree(&s, $1, $3);
                            $$ = newNode; 
                        }
    
    | expr TAND expr    {   if ($1->info->type != BOOL && $3->info->type != BOOL) {
                                printf("Incompatible types for && operation\nexpected: BOOL && BOOL\nfound:  %s && %s", enumToString($1->info->type), enumToString($3->info->type));
                                yyerror();
                            }
                            int andResult = *(int *)$1->info->value && *(int *)$3->info->value;
                            Symbol s = createSymbol(BOOL, "&&", &andResult);
                            struct TreeNode * newNode = createTree(&s, $1, $3);
                            $$ = newNode; 
                        }
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
