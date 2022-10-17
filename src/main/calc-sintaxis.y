%{

#include <stdlib.h>
#include <stdio.h>
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "intermediate_code_generator/instruction.h"
#include "intermediate_code_generator/intermediate_code_generator.h"
#include "utils.h"
#include "symbol_list/symbol_list.h"

SymbolList list;
SintacticAnalysisTree sat;
InstructionList instructionlist;
int offset = 0;
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


inil: { initialize(&list);} prog { printTree($2); //checkTypeTree($2); 
        printf("Tree padre $2: %s\n", $2->info->name);
        InstructionList *instructList = generateIntermediateCode($2);
        //printInstructionList(instructList);
        //printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
        }
    ;
 
prog: declList sentList {   
                            printf("$1: %s $2: %s \n", $1->info->name, $2->info->name);
                            $$ = linkTreeRight($1, $2);
                        }

    | sentList { $$ = $1; }
    ;

declList: decl          {   //printf("$1: %s \n", $1->info->name);
                            $$ = createNextTree($1, NULL); }

    | decl declList     { $$ = createNextTree($2, $1); }
    ;

decl: type ID '=' expr ';'  {   if (searchInLevel(list.head->levelSymbols, $2) != NULL) {
                                    printf("Multiple definitions of: %s", $2);
                                    yyerror();
                                }
                                offset += 8;
                                Symbol *newID = createSymbol($1, $2, NULL, offset);
                                insert(&list, newID);
                                struct TreeNode * idNode = createNode(newID);
                                $$ = createNewTree(UNDEFINED, idNode, $4, "=", 0); 
                            }
    ;

sentList: sent { $$ = createNextTree($1, NULL); } 
    |  sent sentList     {   $$ = createNextTree($2, $1); }
    ;

sent: ID '=' expr ';'   {   Symbol * idSymbol = search(&list, $1);
                            if (idSymbol == NULL) { 
                                printf("Undefined Symbol %s", $1);
                                yyerror();
                            }
                            struct TreeNode * idNode = createNode(idSymbol);
                            $$ = createNewTree(UNDEFINED, idNode, $3, "=", 0); }

    | expr ';' {     
                    $$ = createNextTree($1, NULL);
                    //$$ = $1; 
                    }

    | TReturn expr ';'  {   $$ = createNewTree(UNDEFINED, NULL, $2, "return", 0); }
    ;

expr: VALORINT  {   char *str = intToString($1);
                    int * a = (int*) malloc(sizeof(int));
                    *a = $1;  
                    Symbol *s = createSymbol(TYPEINT, str, a, 0);
                    struct TreeNode *newNode = createNode(s);
                    $$ = newNode; }

    | VALORBOOL {   char * boolValue = $1 == 1 ? "true" : "false";
                    Symbol *s = createSymbol(TYPEBOOL, boolValue, &$1, 0);
                    $$ = createNode(s); }
    
    | ID {  Symbol *s = search(&list, $1);
            if (s == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }
            $$ = createNode(s); }

    | expr '+' expr {   
                        offset += 8;
                        $$ = createNewTree(UNDEFINED, $1, $3, "+", offset); }
    
    | expr '*' expr {   offset += 8;
                        $$ = createNewTree(UNDEFINED, $1, $3, "*", offset); }

    | expr TMENOS expr  {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "-", offset); }

    | '(' expr ')' { $$ = $2; }

    | expr TOR expr     {   offset += 8;
                            $$ = createNewTree(TYPEBOOL, $1, $3, "||", offset); }
    
    | expr TAND expr    {   offset += 8;
                            $$ = $$ = createNewTree(TYPEBOOL, $1, $3, "&&", offset); }
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
