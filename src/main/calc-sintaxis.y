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

%token INT
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
%token TVOID
%token TIf
%token TElse
%token TWhile
%token TExtern
%token TThen
%token TProgram
%token TIGUAL

%type inil
%type prog
%type methodDecl
%type block
%type statement
%type methodCall
%type listParameters
%type parameter
%type declList
%type decl
%type expr
%type VALORINT
%type VALORBOOL
%type type
%type ID
%type literal



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

body: block
    
    | TExtern ';'
    ;

listParameters: parameter
    
    | listParameters ',' parameter 
    ;

parameter: type ID
    ;

block: '{' declList statement '}'
    ;

declList: decl

    | declList decl 
    ;

decl: type ID '=' expr ';'  
    ;

statement: ID '=' expr ';'
    
    | methodCall ';'
    
    | TIf '(' expr ')' TThen block 
    
    | TIf '(' expr ')' TThen block TElse block

    | TWhile expr block

    | TReturn expr ':'

    | ';'

    | block
    ; 
    
methodCall: ID '(' expr ')' ';'
    ;

expr: ID
    
    | methodCall

    | literal

    | expr '+' expr

    | expr TMENOS expr

    | expr '*' expr

    | expr '/' expr

    | expr '%' expr

    | expr '>' expr

    | expr '<' expr

    | expr TIGUAL expr

    | expr TAND expr 

    | expr TOR expr

    | '-' expr %prec UNARYPREC

    | '!' expr %prec UNARYPREC

    | '(' expr ')'
    ; 

literal: VALORINT 
    
    | VALORBOOL
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

sentList: sent { $$ = createNextTree($1, NULL); }
    
    |  sent sentList     {   $$ = createNextTree($1, $2); }
    ;

sent: ID '=' expr ';'   {   Symbol * idSymbol = search(&list, $1);
                            if (idSymbol == NULL) { 
                                printf("Undefined Symbol %s", $1);
                                yyerror();
                            }
                            struct TreeNode * idNode = createNode(idSymbol);
                            $$ = createNewTree(UNDEFINED, idNode, $3, "=", 0); }

    | expr ';' { $$ = $1; }

    | TReturn expr ';'  {   $$ = createNewTree(UNDEFINED, NULL, $2, "return", 0); }
    ;

expr: VALORINT  {   char *str = intToString($1);
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
    
    | ID {  Symbol *s = search(&list, $1);
            if (s == NULL) {
                printf("Undefined symbol %s\n", $1);
                yyerror();
            }
            $$ = createNode(s); }

    | '(' expr ')' { $$ = $2; }

    | expr '+' expr {   
                        offset += 8;
                        $$ = createNewTree(UNDEFINED, $1, $3, "+", offset); }
    
    | expr TMENOS expr  {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "-", offset); }

    | expr '*' expr {   offset += 8;
                        $$ = createNewTree(UNDEFINED, $1, $3, "*", offset); }

    | expr TOR expr     {   offset += 8;
                            $$ = createNewTree(UNDEFINED, $1, $3, "||", offset); }
    
    | expr TAND expr    {   offset += 8;
                            $$ = $$ = createNewTree(UNDEFINED, $1, $3, "&&", offset); }
    ;   

VALORINT: INT { $$ = $1; }
    ;

VALORBOOL: TFALSE    { $$ = 1; }

    | TTRUE { $$ = 1; }
    ;

*/

VALORINT: INT 
    ;

VALORBOOL: TFALSE  

    | TTRUE
    ;


type: TINT 

    | TBOOL 
    ;

%%
