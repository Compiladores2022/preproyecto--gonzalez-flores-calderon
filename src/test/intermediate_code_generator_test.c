#include "../main/parameter_list/parameter_list.h"
#include "../main/types/parameter.h"
#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/intermediate_code_generator/intermediate_code_generator.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode * defaultTreeAddFunction();
struct TreeNode * defaultTreeNotFunction();
struct TreeNode * defaultTreeMethodCall();
struct TreeNode * defaultTreeAnd();
struct TreeNode * defaultTreeOr();
struct TreeNode * defaultTreeRet();
struct TreeNode * defaultTree();
int intermediteCodeGeneratorAddFunction();
int intermediteCodeGeneratorNotVoidFunction();
int intermediteCodeGeneratorMethodCall();
int intermediteCodeGeneratorAnd();
int intermediteCodeGeneratorOr();
int intermediteCodeGeneratorRet();
int intermediteCodeGenerator();

int main(){
    int testsPassed = 0, totalTests = 0;
    
    intermediteCodeGeneratorAddFunction() ? testsPassed++ : printf("\033[0;31mTest intermediate code add function failed\033[0m \n"); totalTests++;
    intermediteCodeGeneratorNotVoidFunction() ? testsPassed++ : printf("\033[0;31mTest intermediate code not void function failed\033[0m \n"); totalTests++;
    intermediteCodeGeneratorMethodCall() ? testsPassed++ : printf("\033[0;31mTest intermediate code method call failed\033[0m \n"); totalTests++;
    // intermediteCodeGeneratorAnd() ? testsPassed++ : printf("\033[0;31mTest intermediate code and failed\033[0m \n"); totalTests++;
    // intermediteCodeGeneratorOr() ? testsPassed++ : printf("\033[0;31mTest intermediate code or failed\033[0m \n"); totalTests++;
    // intermediteCodeGeneratorRet() ? testsPassed++ : printf("\033[0;31mTest intermediate code ret failed\033[0m \n"); totalTests++;
    // intermediteCodeGenerator() ? testsPassed++ : printf("\033[0;31mTest intermediate code mega failed\033[0m \n"); totalTests++;    

    printf("Tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int intermediteCodeGeneratorAddFunction(){

    struct TreeNode *treeDecorator =  defaultTreeAddFunction();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 3){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorNotVoidFunction(){
    
    struct TreeNode *treeDecorator =  defaultTreeNotFunction();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 3){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorMethodCall(){
    
    struct TreeNode *treeDecorator =  defaultTreeMethodCall();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 10){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorAnd(){
    
    struct TreeNode *treeDecorator =  defaultTreeAnd();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorOr(){
    
    struct TreeNode *treeDecorator =  defaultTreeOr();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorRet(){
    
    struct TreeNode *treeDecorator =  defaultTreeRet();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGenerator(){
    
    struct TreeNode *treeDecorator =  defaultTree();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 4){
         return 1;
    }
    return 0;   
}

struct TreeNode * defaultTree(){
int offset = 8;

    Symbol *symbolX = createSymbol(TYPEINT, "x", NULL, offset);
    offset += 8;
    Symbol *symbolY = createSymbol(TYPEINT, "y", NULL, offset);
    offset += 8;
    Symbol *symbol1 = createSymbol(TYPEINT, "*", NULL, offset);
    
    Symbol *symbol2 = createSymbol(UNDEFINED, "return", NULL, 0);
    Symbol *symbol3 = createSymbol(UNDEFINED, "next", NULL, 0);
    
    // return x * y;
    struct TreeNode *left = createNode(symbolX);
    struct TreeNode *right = createNode(symbolY);
    struct TreeNode *tree = createTree(symbol1, left, right);
    tree = createTree(symbol2, NULL, tree);
    struct TreeNode *treeNext = createTree(symbol3, tree, NULL);
    

    int *b = (int *)malloc(sizeof(int));
    *b = 10;
    symbol1 = createSymbol(TYPEINT, "10", b, 0);
    symbol2 = createSymbol(TYPEINT, "=", NULL, 0);
    symbol3 = createSymbol(UNDEFINED, "next", NULL, 0);
    
    // y = 10;
    left = createNode(symbolY);
    right = createNode(symbol1);
    tree = createTree(symbol2, left, right);
    treeNext = createTree(symbol3, tree, treeNext);

    
    int *a = (int *)malloc(sizeof(int));
    *a = 5;
    symbol1 = createSymbol(TYPEINT, "5", a, 0);
    symbol2 = createSymbol(TYPEINT, "=", NULL, 0);
    symbol3 = createSymbol(UNDEFINED, "next", NULL, 0);

    // x = 5;
    left = createNode(symbolX);
    right = createNode(symbol1);
    tree = createTree(symbol2, left, right);
    treeNext = createTree(symbol3, tree, treeNext);
    return treeNext;
}

struct TreeNode * defaultTreeRet(){
    int offset = 0;
    int* four = (int*) malloc(sizeof(int));
    *four = 4;
    Symbol *sfour = createSymbol(TYPEINT, "4", four, 0);
    int* five = (int*) malloc(sizeof(int));
    *five = 5;
    Symbol *sfive = createSymbol(TYPEINT, "5", five, 0);
    offset += 8;
    Symbol *mult = createSymbol(TYPEINT, "*", NULL, offset);
    offset += 8;
    Symbol *ret = createSymbol(TYPEINT, "RET", NULL, offset);
    
    // 4 * 5;
    struct TreeNode *treeFour = createNode(sfour);
    struct TreeNode *treeFive = createNode(sfive);
    struct TreeNode *treeMult = createTree(mult, treeFour, treeFive);
    
    // Ret 4 * 5;
    struct TreeNode *treeRet = createTree(ret, NULL, treeMult);
    
    Symbol *pyc = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *prog = createTree(pyc, treeRet, NULL);
        
    return prog;
}

struct TreeNode * defaultTreeOr(){
    int offset = 0;
    int* true = (int*) malloc(sizeof(int));
    *true = 1;
    Symbol *strue = createSymbol(TYPEBOOL, "True", true, 0);
    int* false = (int*) malloc(sizeof(int));
    *false = 0;
    Symbol *sfalse = createSymbol(TYPEBOOL, "False", false, 0);
    offset += 8;
    Symbol *or = createSymbol(TYPEBOOL, "||", NULL, offset);
    int* exis = (int*) malloc(sizeof(int));
    *exis = 0;    
    offset += 8;
    Symbol *x = createSymbol(TYPEBOOL, "x", exis, offset);
    offset += 8;
    Symbol *assig = createSymbol(TYPEBOOL, "=", NULL, offset);
    
    // 4 * 5;
    struct TreeNode *treeTrue = createNode(strue);
    struct TreeNode *treeFalse = createNode(sfalse);
    struct TreeNode *treeor = createTree(or, treeTrue, treeFalse);
    
    // x = 4 * 5;
    struct TreeNode *treeX = createNode(x);
    struct TreeNode *treeAssig = createTree(assig, treeX, treeor);

    Symbol *pyc = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *prog = createTree(pyc, treeAssig, NULL);
        
    return prog;
}

struct TreeNode * defaultTreeAnd(){
    int offset = 0;
    int* true = (int*) malloc(sizeof(int));
    *true = 1;
    Symbol *strue = createSymbol(TYPEBOOL, "True", true, 0);
    int* false = (int*) malloc(sizeof(int));
    *false = 0;
    Symbol *sfalse = createSymbol(TYPEBOOL, "False", false, 0);
    offset += 8;
    Symbol *and = createSymbol(TYPEBOOL, "&&", NULL, offset);
    int* exis = (int*) malloc(sizeof(int));
    *exis = 0;    
    offset += 8;
    Symbol *x = createSymbol(TYPEBOOL, "x", exis, offset);
    offset += 8;
    Symbol *assig = createSymbol(TYPEBOOL, "=", NULL, offset);
    
    // 4 * 5;
    struct TreeNode *treeTrue = createNode(strue);
    struct TreeNode *treeFalse = createNode(sfalse);
    struct TreeNode *treeAnd = createTree(and, treeTrue, treeFalse);
    
    // x = 4 * 5;
    struct TreeNode *treeX = createNode(x);
    struct TreeNode *treeAssig = createTree(assig, treeX, treeAnd);

    Symbol *pyc = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *prog = createTree(pyc, treeAssig, NULL);
        
    return prog;
}

/*
int getNum() {
    return 5 * 10;
}

void main() {
    int x = -1;
    x = x + 5 + getNum();
}
*/
struct TreeNode * defaultTreeMethodCall(){
    int offset = 0;
    int* a = (int*) malloc(sizeof(int));
    *a = 5;
    Symbol *five = createSymbol(TYPEINT, "5", a, 0);
    offset += 8;
    Symbol *mult = createSymbol(TYPEINT, "*", NULL, offset);
    int* b = (int*) malloc(sizeof(int));
    *b = 10;
    Symbol *ten = createSymbol(TYPEINT, "10", b, 0);
    //5 * 10
    struct TreeNode *treeFive = createNode(five);
    struct TreeNode *treeTen = createNode(ten);
    struct TreeNode *treeMult = createTree(mult, treeFive, treeTen);
    
    Symbol *symbolRet = createSymbol(TYPEINT, "return", NULL, 0);
    addIdentifierType(symbolRet, TYPELESS);
    
    struct TreeNode *treeRet = createTree(symbolRet, NULL, treeMult);

    Symbol *next = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *treeFstDecl = createTree(next, treeRet, NULL);

    Symbol *method = createSymbol(TYPEINT, "getNum", NULL, 0);
    addIdentifierType(method, METHOD);

    treeFstDecl = createTree(method, treeFstDecl, NULL);

    treeFstDecl = createTree(next, treeFstDecl, NULL);

    //now creating main function
    a = (int*) malloc(sizeof(int));
    *a = 1;
    Symbol *one = createSymbol(TYPEINT, "1", a, 0);
    offset += 8;
    Symbol *menos = createSymbol(TYPEINT, "-", NULL, offset);
    offset += 8;
    Symbol *symbolX = createSymbol(TYPEINT, "x", NULL, offset);
    offset += 8;
    Symbol *assig = createSymbol(TYPEINT, "=", NULL, offset);
    //x = 1
    struct TreeNode *treeOne = createNode(one);
    struct TreeNode *treeMenos = createTree(menos, treeOne, NULL);
    struct TreeNode *treeX = createNode(symbolX);
    struct TreeNode *treeAssig = createTree(assig, treeX, treeMenos);
    struct TreeNode *tree = createTree(next, treeAssig, NULL);
    
    // x = x + 5 + getNum()
    a = (int*) malloc(sizeof(int));
    five = createSymbol(TYPEINT, "5", a, 0);
    offset += 8;
    Symbol *suma1 = createSymbol(TYPEINT, "+", NULL, offset);
    Symbol *suma2 = createSymbol(TYPEINT, "+", NULL, offset);
    
    treeFive = createNode(five);

    Symbol *methodCall = createSymbol(method->type, method->name, NULL, 0);
    addIdentifierType(methodCall, METHODCALL);
    
    struct TreeNode *treeMethod = createNode(methodCall);
    struct TreeNode *treeSuma1 = createTree(suma1, treeFive, treeMethod);
    
    treeX = createNode(symbolX);
    struct TreeNode *treeSuma2 = createTree(suma2, treeX, treeSuma1);

    assig = createSymbol(TYPEINT, "=", NULL, offset);
    treeX = createNode(symbolX);
    struct TreeNode *tree2 = createTree(assig, treeX, treeSuma2);
    tree2 = createTree(next, tree2, NULL);

    //joining trees
    tree->right = tree2;
    //creating main
    Symbol *mainMethod = createSymbol(TYPEVOID, "main", NULL, 0);
    addIdentifierType(mainMethod, METHOD);

    tree = createTree(mainMethod, tree, NULL);
    tree = createTree(next, tree, NULL);

    treeFstDecl->right = tree;

    return treeFstDecl;
}

/*
    void opposite(bool x) {
        x = !x;
    }
*/
struct TreeNode * defaultTreeNotFunction(){
    int offset = 8;
    Symbol *symbolX = createSymbol(TYPEBOOL, "x", NULL, offset);
    offset += 8;
    Symbol *not = createSymbol(TYPEBOOL, "!", NULL, offset);
    offset += 8;
    Symbol *assig = createSymbol(TYPEBOOL, "=", NULL, offset);

    struct TreeNode *treeX = createNode(symbolX);
    struct TreeNode *treeNot = createTree(not, treeX, NULL);
    struct TreeNode *treeAssig = createTree(assig, treeX, treeNot);
    
    Symbol *next = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *tree = createTree(next, treeAssig, NULL);

    //function parameters
    struct ParameterList pList;
    initializeP(&pList);
    struct Parameter *parameter = createParameter(TYPEBOOL, "x");
    insertParameter(&pList, parameter);

    Symbol *method = createSymbolWithParameter(TYPEVOID, "opposite", NULL, 0, &pList);
    addIdentifierType(method, METHOD);

    tree = createTree(method, tree, NULL);

    tree = createTree(next, tree, NULL);
    
    return tree;
}

/*
int inc(int x) {
    return x + 1;
}
*/
struct TreeNode * defaultTreeAddFunction(){
    int offset = 0;
    int* a = (int*) malloc(sizeof(int));
    *a = 1;
    Symbol *one = createSymbol(TYPEINT, "1", a, 0);
    offset += 8;
    Symbol *symbolX = createSymbol(TYPEINT, "x", NULL, offset);
    offset += 8;
    Symbol *suma = createSymbol(TYPEINT, "+", NULL, offset);
    
    struct TreeNode *treeOne = createNode(one);
    struct TreeNode *treeX = createNode(symbolX);
    struct TreeNode *treeSuma = createTree(suma, treeX, treeOne);
    
    Symbol *symbolRet = createSymbol(TYPEINT, "return", NULL, 0);
    addIdentifierType(symbolRet, TYPELESS);
    
    struct TreeNode *treeRet = createTree(symbolRet, NULL, treeSuma);

    Symbol *next = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *tree = createTree(next, treeRet, NULL);

    //function parameters
    struct ParameterList pList;
    initializeP(&pList);
    struct Parameter *parameter = createParameter(TYPEINT, "x");
    insertParameter(&pList, parameter);

    Symbol *method = createSymbolWithParameter(TYPEINT, "inc", NULL, 0, &pList);
    addIdentifierType(method, METHOD);

    tree = createTree(method, tree, NULL);

    tree = createTree(next, tree, NULL);
    
    return tree;
}
