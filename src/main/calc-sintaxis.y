%{

#include <stdlib.h>
#include <stdio.h>
#include "types/parameter.h"
#include "types/enumeration.h"
#include "parameter_list/parameter_list.h"
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "intermediate_code_generator/instruction.h"
#include "intermediate_code_generator/intermediate_code_generator.h"
#include "assembler_code_generator/assembler_generator.h"
#include "utils/utils.h"
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
        struct TreeNode *n;
        struct Parameter *p;
        struct ParameterList *plist;}

%token<i> INT
%token ID
%token TMENOS
%token TBOOL
%token TINT
%token TOR
%token TAND
%token TTRUE
%token TFALSE
%token TReturn
%token TVOID
%token TIf
%token TElse
%token TWhile
%token TExtern
%token TThen
%token TProgram
%token TIGUAL

%type inil
%type<n> prog
%type<n> methodDeclList
%type<n> methodDecl
%type<n> body
%type<n> block
%type<n> statement
%type<n> statementList
%type<n> methodCall
%type<n> exprList
%type<plist> listParameters
%type<p> parameter
%type<n> declList
%type<n> decl
%type<n> expr
%type<i> VALORINT
%type<i> VALORBOOL
%type<i> type
%type<s> ID
%type<n> literal

%left TAND
%left TOR
%nonassoc '<' '>' TIGUAL
%left '+' TMENOS
%left '*' '%' '/'
%right UNARYPREC

%%

inil: {initialize(&list);} prog {   checkMain(&list);
                                    printTree($2); 
                                    checkTypeTree($2);
                                    InstructionList * intermediateCode = generateIntermediateCode($2);
                                    printInstructionList(intermediateCode);
                                }
    ;    

prog: TProgram '{' declList  methodDeclList '}' {   linkTreeRight($3, $4);
                                                    $$ = $3; }

    | TProgram '{' methodDeclList '}'   { $$ = $3; }
    ;

methodDeclList: methodDecl methodDeclList    { $$ = createNextTree($1, $2); }
    
    | methodDecl          { $$ = createNextTree($1, NULL); }
    ;

methodDecl: type ID '('  ')' body   {   if(search(&list, $2) != NULL){
                                            printf("Already defined method: %s", $2);
                                            yyerror();
                                        }
                                        if($5 == NULL){                                        
                                            Symbol *symbol = createSymbol($1, $2, 0, 0);
                                            addIdentifierType(symbol, METHOD);
                                            struct TreeNode * node = createNode(symbol);
                                            insert(&list, node->info);
                                            $$ = node;    
                                        } 
                                        else{
                                            struct TreeNode *treeMethod = createNewTree($1, $5, NULL, $2, 0, METHOD);
                                            insert(&list, treeMethod->info);
                                            $$ = treeMethod;    
                                        }
                                    }

    | TVOID ID '('  ')' body    {   if(search(&list, $2) != NULL){
                                        printf("Already defined method: %s", $2);
                                        yyerror();
                                    }
                                    if($5 == NULL){
                                            Symbol *symbol = createSymbol(TYPEVOID, $2, 0, 0);
                                            addIdentifierType(symbol, METHOD);
                                            struct TreeNode * node = createNode(symbol);
                                            insert(&list, node->info);
                                            $$ = node;    
                                    } 
                                    else{
                                        struct TreeNode *treeMethod = createNewTree(TYPEVOID, $5, NULL, $2, 0, METHOD);
                                        insert(&list, treeMethod->info);
                                        $$ = treeMethod;
                                    }
                                }

    | type ID '(' { openLevel(&list); } listParameters ')' body {   closeLevel(&list);   
                                                                    if(search(&list, $2) != NULL){
                                                                        yyerror();
                                                                    }
                                                                    if($7 == NULL){
                                                                        struct TreeNode *tree =  createNewNodeWithParameters($1, $2, METHOD, $5);
                                                                        insert(&list, tree->info);
                                                                        $$ = tree;    
                                                                    }
                                                                    else{
                                                                        struct TreeNode *treeMethod = createNewTreeWithParameters($1, $7, NULL, $2, 0, $5, METHOD);
                                                                        insert(&list, treeMethod->info);
                                                                        $$ = treeMethod;
                                                                    }
                                                                }

    | TVOID ID '(' { openLevel(&list);} listParameters ')' body {   closeLevel(&list);   
                                                                    if(search(&list, $2) != NULL){
                                                                        yyerror();
                                                                    }
                                                                    if($7 == NULL){
                                                                        struct TreeNode *tree =  createNewNodeWithParameters(TYPEVOID, $2, METHOD, $5);
                                                                        insert(&list, tree->info);
                                                                        $$ = tree;    
                                                                    } 
                                                                    else{                                                                   
                                                                        struct TreeNode *treeMethod = createNewTreeWithParameters(TYPEVOID, $7, NULL, $2, 0, $5, METHOD);
                                                                        insert(&list, treeMethod->info);
                                                                        $$ = treeMethod;
                                                                    }
                                                                }
    ;

body: block         { $$ = $1; }
    
    | TExtern ';'   { $$ = NULL; }
    ; 

listParameters: parameter           {   struct ParameterList pList;
                                        initializeP(&pList);
                                        insertParameter(&pList, $1);
                                        $$ = &pList;
                                    }
    
    | listParameters ',' parameter  {   insertParameter($1, $3); 
                                        $$ = $1;
                                    }
    ;

parameter: type ID  {   struct Parameter *parameter = createParameter($1, $2);
                        insert(&list, createSymbol($1, $2, NULL, 0));
                        $$ = parameter;
                    }
    ;

block: '{' '}' { $$ = NULL; }

    | '{' { openLevel(&list); } declList statementList '}'  {   closeLevel(&list); 
                                                                //VER ESTE CASO
                                                                $$ = createNextTree($3, $4);
                                                                //linkTreeRight($3, $4);
                                                                //$$ = $3;
                                                            }

    | '{' statementList '}' { $$ = $2; }
    ;

declList: decl          {   $$ = createNextTree($1, NULL); }

    | declList decl     { $$ = createNextTree($1, $2); }
    ;

decl: type ID '=' expr ';'  {   if (searchInLevel(list.head->levelSymbols, $2) != NULL) {
                                    printf("Multiple definitions of: %s", $2);
                                    yyerror();
                                }
                                offset += 8;
                                Symbol *newID = createSymbol($1, $2, NULL, offset);
                                insert(&list, newID);
                                struct TreeNode * idNode = createNode(newID);
                                $$ = createNewTree(UNDEFINED, idNode, $4, "=", 0, TYPELESS); 
                            }   
    ;
statementList:  statement       {   $$ = createNextTree($1, NULL); }
                                
    | statementList statement   { $$ = createNextTree($2, $1); }
    ;
    
statement: ID '=' expr ';'  {   Symbol * idSymbol = search(&list, $1);
                                if (idSymbol == NULL) { 
                                    printf("Undefined Symbol %s", $1);
                                    yyerror();
                                }
                                struct TreeNode * idNode = createNode(idSymbol);
                                $$ = createNewTree(UNDEFINED, idNode, $3, "=", 0, TYPELESS); 
                            }
    
    | methodCall { $$ = $1; }
    
    | TIf '(' expr ')' TThen block { $$ = createNewTree(UNDEFINED, $3, $6, "if", 0, TYPELESS); }
    
    | TIf '(' expr ')' TThen block TElse block  {   struct TreeNode *ifElse = createNewTree(UNDEFINED, $6, $8, "ifelse", 0, TYPELESS);
                                                    $$ = createNewTree(UNDEFINED, $3, ifElse, "if", 0, TYPELESS); 
                                                }

    | TWhile '(' expr ')' block     { $$ = createNewTree(UNDEFINED, $3, $5, "while", 0, TYPELESS); }

    | TReturn expr ';'  { $$ = createNewTree(UNDEFINED, NULL, $2, "return", 0, TYPELESS); }

    | TReturn ';'       {   $$ = NULL   }

    | ';'           { $$ = NULL; }

    | block         { $$ = $1; }
    ; 
    
methodCall: ID '(' exprList ')' {   Symbol * methodSymb = search(&list, $1);
                                    if ( methodSymb == NULL) {
                                        printf("Undefined method: %s", $1);
                                        yyerror();
                                    }else if(methodSymb->it != METHOD){
                                        printf("This name not a method: %s", $1);
                                        yyerror();
                                    }else if(methodSymb->parameterList == NULL){
                                        printf("Method %s cannot be applied to given types\n", $1);
                                        yyerror();
                                    }
                                    $$ = createNewTreeWithParameters(methodSymb->type, $3, NULL, methodSymb->name, 0, methodSymb->parameterList, METHODCALL);
                                }

    | ID '(' ')'                {   Symbol * methodSymb = search(&list, $1);
                                    if ( methodSymb == NULL) {
                                        printf("Undefined method: %s", $1);
                                        yyerror();
                                    }else if(methodSymb->it != METHOD){
                                        printf("This name not a method: %s", $1);
                                        yyerror();
                                    }
                                    if(methodSymb->parameterList != NULL){
                                        $$ = createNewNodeWithParameters(methodSymb->type, methodSymb->name, METHODCALL, methodSymb->parameterList);
                                    }
                                    else{
                                        $$ = createNewNode(methodSymb->type, methodSymb->name, METHODCALL); 
                                    }
                                }
    ;

exprList: expr      { $$ = createNextTree($1, NULL); }

    | expr ',' exprList { $$ = createNextTree($1, $3); }
    ;

expr: ID    {   Symbol *s = search(&list, $1);
                if (s == NULL) {
                    printf("Undefined symbol %s\n", $1);
                    yyerror();
                }
                $$ = createNode(s); 
            }

    | methodCall        {   if($1->info->type == TYPEVOID){
                                printf("Method void not use to expr: %s", $1->info->name);
                                yyerror();
                            }    
                            $$ = $1; 
                        } 

    | literal           { $$ = $1; }

    | expr '+' expr     {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "+", offset, TYPELESS); }

    | expr TMENOS expr  {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "-", offset, TYPELESS); }

    | expr '*' expr     {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "*", offset, TYPELESS); }

    | expr '/' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "/", offset, TYPELESS); }

    | expr '%' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "%", offset, TYPELESS); }

    | expr '>' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, ">", offset, TYPELESS); }

    | expr '<' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "<", offset, TYPELESS); }

    | expr TIGUAL expr  {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "==", offset, TYPELESS); }

    | expr TAND expr    {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "&&", offset, TYPELESS); }

    | expr TOR expr     {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "||", offset, TYPELESS); }

    | TMENOS expr %prec UNARYPREC   {   offset += 8;
                                        $$ = createNewTree(UNDEFINED, $2, NULL, "-", offset, TYPELESS); }

    | '!' expr %prec UNARYPREC {
                        offset += 8;
                        $$ = createNewTree(UNDEFINED, $2, NULL, "!", offset, TYPELESS); }

    | '(' expr ')' { $$ = $2; }
    ;

literal: VALORINT   {   char *str = intToString($1);
                        int * a = (int*) malloc(sizeof(int));
                        *a = $1;  
                        Symbol *s = createSymbol(TYPEINT, str, a, 0);
                        struct TreeNode *newNode = createNode(s);
                        $$ = newNode; 
                    }

    | VALORBOOL {   char * boolValue = $1 == 1 ? "true" : "false";
                    int * a = (int*) malloc(sizeof(int));
                    *a = $1;  
                    Symbol *s = createSymbol(TYPEBOOL, boolValue, a, 0);
                    $$ = createNode(s); 
                }
    ;

VALORINT: INT { $$ = $1; }
    ;

VALORBOOL: TFALSE    { $$ = 1; }

    | TTRUE { $$ = 1; }
    ;

type: TINT { $$ = TYPEINT; }

    | TBOOL { $$ = TYPEBOOL; }
    ;

%%
