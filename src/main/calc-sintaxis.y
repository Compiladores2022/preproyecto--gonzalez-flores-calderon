%{

#include <stdlib.h>
#include <stdio.h>
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
        struct TreeNode *n;}

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

%type<n> inil
%type<n> prog
%type<n> methodDecl
%type<n> body
%type<n> block
%type<n> statement
%type<n> methodCall
%type<n> exprList
%type<n> listParameters
%type<n> parameter
%type<n> declList
%type<n> decl
%type<n> expr
%type<i> VALORINT
%type<i> VALORBOOL
%type<i> type
%type<s> ID
%type<n> literal



%left '+' TMENOS 
%left '*' '%' '/' 
%left TAND
%left TOR
%nonassoc '<' '>' TIGUAL 
%right UNARYPREC

%%



inil: prog
    ;    

prog: TProgram '{' declList  methodDecl '}'
    
    | TProgram '{' methodDecl '}'
    ;

methodDecl: type ID '('  ')' body  

    | TVOID ID '('  ')' body

    | type ID '(' listParameters ')' body 

    | TVOID ID '(' listParameters ')' body  
    ;

body: block         { $$ = $1; }
    
    | TExtern ';'   { $$ = NULL; }
    ;

listParameters: parameter           { $$ = $1; }
    
    | listParameters ',' parameter  { $$ = createNextTree($2, $1); }
    ;

parameter: type ID  { offset += 8;
                        $$ = createNewTree($1, NULL, NULL, $2, offset); }
    ;

block: { openLevel(&list); } '{' '}' { closeLevel(&list); }

    | { openLevel(&list); } '{' declList statement '}'  { closeLevel(&list); }

    | { openLevel(&list); } '{' declList '}' { closeLevel(&list); }

    | { openLevel(&list); } '{' statement '}' { closeLevel(&list); }
    ;

declList: decl          { $$ = createNextTree($1, NULL); }

    | decl declList     { $$ = createNextTree($1, $2); }
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

statement: ID '=' expr ';'   {   Symbol * idSymbol = search(&list, $1);
                            if (idSymbol == NULL) { 
                                printf("Undefined Symbol %s", $1);
                                yyerror();
                            }
                            struct TreeNode * idNode = createNode(idSymbol);
                            $$ = createNewTree(UNDEFINED, idNode, $3, "=", 0); }
    
    | methodCall ';'
    
    | TIf '(' expr ')' TThen block 
    
    | TIf '(' expr ')' TThen block TElse block  { }

    | TWhile expr block     { $$ = createNextTree(UNDEFINED, $1, $2, "while", 0); }

    | TReturn expr ';'  {   $$ = createNewTree(UNDEFINED, NULL, $2, "return", 0); }

    | ';'           { $$ = NULL; }

    | block         { $$ = $1; }
    ; 
    
methodCall: ID '(' exprList ')' ';'         { Symbol * methodSymb = search(list.head->levelSymbols, $1);
                                            if ( methodSymb == NULL) {
                                                printf("Undefined method: %s", $1);
                                                yyerror();
                                            }
                                            struct TreeNode * idNode = createTree(methodSymb, NULL, $3);
                                            $$ = createNewTree(UNDEFINED, idNode, $4, "=", 0); }
    ;

exprList: expr      { $$ = $1; }
    
    | expr exprList { $$ = createNextTree($1, $2); }
    ;

expr: ID {  Symbol *s = search(&list, $1);
            if (s == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }
            $$ = createNode(s); }
    
    | methodCall        { $$ = $1; }

    | literal           { $$ = $1; }

    | expr '+' expr     {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "+", offset); }
    
    | expr TMENOS expr  {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "-", offset); }

    | expr '*' expr     {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "*", offset); }

    | expr '/' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "/", offset); }

    | expr '%' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "%", offset); }

    | expr '>' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, ">", offset); }

    | expr '<' expr     {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "<", offset); }

    | expr TIGUAL expr  {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "==", offset); }
    
    | expr TAND expr    {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "&&", offset); }

    | expr TOR expr     {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "||", offset); }

    | '-' expr %prec UNARYPREC {   
                        offset += 8;
                        $$ = createNewTree(UNDEFINED, $2, NULL, "-", offset); }

    | '!' expr %prec UNARYPREC {   
                        offset += 8;
                        $$ = createNewTree(UNDEFINED, $2, NULL, "!", offset); }

    | '(' expr ')' { $$ = $2; }
    ; 

literal: VALORINT  {   char *str = intToString($1);
                    int * a = (int*) malloc(sizeof(int));
                    *a = $1;  
                    Symbol *s = createSymbol(TYPEINT, str, a, 0);
                    struct TreeNode *newNode = createNode(s);
                    $$ = newNode; }

    | VALORBOOL {   char * boolValue = $1 == 1 ? "true" : "false";
                    int * a = (int*) malloc(sizeof(int));
                    *a = $1;  
                    Symbol *s = createSymbol(TYPEBOOL, boolValue, a, 0);
                    $$ = createNode(s); }
    ;

/*
inil:   {   initialize(&list); } prog { printTree($2); 
            if(checkTypeTree($2) == 1) {
                InstructionList *instructList = generateIntermediateCode($2);
                char *assemblerCode = generateAssemblerCode(instructList, offset);
                printf("%s",assemblerCode);
                createAssemblerFile(assemblerCode);
            }
        }
    ;

prog: declList sentList {   
                            linkTreeRight($1, $2);
                            $$ = $1;
                        }

    | sentList { $$ = $1; }
    ;

sentList: sent { $$ = createNextTree($1, NULL); }
    
    |  sent sentList     {   $$ = createNextTree($1, $2); }
    ;

sent: expr ';' { $$ = $1; }

    | TReturn expr ';'  {   $$ = createNewTree(UNDEFINED, NULL, $2, "return", 0); }
    ;

*/

VALORINT: INT { $$ = $1; }
    ;

VALORBOOL: TFALSE    { $$ = 1; }

    | TTRUE { $$ = 1; }
    ;

type: TINT {/*Type int */ $$ = TYPEINT;}

    | TBOOL {/*Type bool */$$ = TYPEBOOL;}
    ;

%%
