#include "../main/parameter_list/parameter_list.h"
#include "../main/types/parameter.h"
#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/intermediate_code_generator/intermediate_code_generator.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode * defaultTreeAddFunction();
struct TreeNode * defaultTreeSub();
struct TreeNode * defaultTreeMult();
struct TreeNode * defaultTreeAnd();
struct TreeNode * defaultTreeOr();
struct TreeNode * defaultTreeRet();
struct TreeNode * defaultTree();
int intermediteCodeGeneratorAddFunction();
int intermediteCodeGeneratorSub();
int intermediteCodeGeneratorMult();
int intermediteCodeGeneratorAnd();
int intermediteCodeGeneratorOr();
int intermediteCodeGeneratorRet();
int intermediteCodeGenerator();

int main(){
    int testsPassed = 0, totalTests = 0;
    
    intermediteCodeGeneratorAddFunction() ? testsPassed++ : printf("\033[0;31mTest intermediate code add function failed\033[0m \n"); totalTests++;
    // intermediteCodeGeneratorSub() ? testsPassed++ : printf("\033[0;31mTest intermediate code sub failed\033[0m \n"); totalTests++;
    // intermediteCodeGeneratorMult() ? testsPassed++ : printf("\033[0;31mTest intermediate code mult failed\033[0m \n"); totalTests++;
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

int intermediteCodeGeneratorSub(){
    
    struct TreeNode *treeDecorator =  defaultTreeSub();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorMult(){
    
    struct TreeNode *treeDecorator =  defaultTreeMult();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    if(sizeList(instructList) == 2){
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

struct TreeNode * defaultTreeMult(){
    int offset = 0;
    int* four = (int*) malloc(sizeof(int));
    *four = 4;
    Symbol *sfour = createSymbol(TYPEINT, "4", four, 0);
    int* five = (int*) malloc(sizeof(int));
    *five = 5;
    Symbol *sfive = createSymbol(TYPEINT, "5", five, 0);
    offset += 8;
    Symbol *mult = createSymbol(TYPEINT, "*", NULL, offset);
    int* exis = (int*) malloc(sizeof(int));
    *exis = 7;    
    offset += 8;
    Symbol *x = createSymbol(TYPEINT, "x", exis, offset);
    offset += 8;
    Symbol *assig = createSymbol(TYPEINT, "=", NULL, offset);
    
    // 4 * 5;
    struct TreeNode *treeFour = createNode(sfour);
    struct TreeNode *treeFive = createNode(sfive);
    struct TreeNode *treeMult = createTree(mult, treeFour, treeFive);
    
    // x = 4 * 5;
    struct TreeNode *treeX = createNode(x);
    struct TreeNode *treeAssig = createTree(assig, treeX, treeMult);

    Symbol *pyc = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *prog = createTree(pyc, treeAssig, NULL);
        
    return prog;
}

struct TreeNode * defaultTreeSub(){
    int offset = 0;
    int* ten = (int*) malloc(sizeof(int));
    *ten = 10;
    Symbol *sten = createSymbol(TYPEINT, "10", ten, 0);
    int* six = (int*) malloc(sizeof(int));
    *six = 6;
    Symbol *ssix = createSymbol(TYPEINT, "6", six, 0);
    offset += 8;
    Symbol *sub = createSymbol(TYPEINT, "-", NULL, offset);
    int* exis = (int*) malloc(sizeof(int));
    *exis = 7;    
    offset += 8;
    Symbol *x = createSymbol(TYPEINT, "x", exis, offset);
    offset += 8;
    Symbol *assig = createSymbol(TYPEINT, "=", NULL, offset);
    
    // 10 - 6;
    struct TreeNode *treeTen = createNode(sten);
    struct TreeNode *treeSix = createNode(ssix);
    struct TreeNode *treeSub = createTree(sub, treeTen, treeSix);
    
    // x = 10 - 6;
    struct TreeNode *treeX = createNode(x);
    struct TreeNode *treeAssig = createTree(assig, treeX, treeSub);

    Symbol *pyc = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *prog = createTree(pyc, treeAssig, NULL);
        
    return prog;
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
    
    Symbol *symbolRet = createSymbol(TYPEINT, "return", NULL, offset);
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
