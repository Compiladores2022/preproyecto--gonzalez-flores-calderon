#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/intermediate_code_generator/intermediate_code_generator.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode * defaultTreeAdd();
struct TreeNode * defaultTreeSub();
struct TreeNode * defaultTreeMult();
struct TreeNode * defaultTreeAnd();
struct TreeNode * defaultTreeOr();
struct TreeNode * defaultTreeRet();
int intermediteCodeGeneratorAdd();
int intermediteCodeGeneratorSub();
int intermediteCodeGeneratorMult();
int intermediteCodeGeneratorAnd();
int intermediteCodeGeneratorOr();
int intermediteCodeGeneratorRet();

int main(){
    int testsPassed = 0, totalTests = 0;
    
    intermediteCodeGeneratorAdd() ? testsPassed++ : printf("Test intermediate code add failed \n"); totalTests++;
    intermediteCodeGeneratorSub() ? testsPassed++ : printf("Test intermediate code sub failed \n"); totalTests++;
    intermediteCodeGeneratorMult() ? testsPassed++ : printf("Test intermediate code mult failed \n"); totalTests++;
    intermediteCodeGeneratorAnd() ? testsPassed++ : printf("Test intermediate code and failed \n"); totalTests++;
    intermediteCodeGeneratorOr() ? testsPassed++ : printf("Test intermediate code or failed \n"); totalTests++;
    intermediteCodeGeneratorRet() ? testsPassed++ : printf("Test intermediate code ret failed \n"); totalTests++;

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int intermediteCodeGeneratorAdd(){

    struct TreeNode *treeDecorator =  defaultTreeAdd();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List add: \n");
    printInstructionList(instructList);
    //printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    //printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorSub(){
    
    struct TreeNode *treeDecorator =  defaultTreeSub();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List sub: \n");
    printInstructionList(instructList);
    //printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    //printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorMult(){
    
    struct TreeNode *treeDecorator =  defaultTreeMult();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List mult: \n");
    printInstructionList(instructList);
    //printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    //printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorAnd(){
    
    struct TreeNode *treeDecorator =  defaultTreeAnd();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List and: \n");
    printInstructionList(instructList);
    //printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    //printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorOr(){
    
    struct TreeNode *treeDecorator =  defaultTreeOr();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List or: \n");
    printInstructionList(instructList);
    //printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    //printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorRet(){
    
    struct TreeNode *treeDecorator =  defaultTreeRet();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List ret: \n");
    printInstructionList(instructList);
    //printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    //printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
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

struct TreeNode * defaultTreeAdd(){
    int offset = 0;
    int* tre = (int*) malloc(sizeof(int));
    *tre = 3;
    Symbol *tres = createSymbol(TYPEINT, "3", tre, 0);
    int* cua = (int*) malloc(sizeof(int));
    *cua = 4;
    Symbol *cuatro = createSymbol(TYPEINT, "4", cua, 0);
    offset += 8;
    Symbol *suma = createSymbol(TYPEINT, "+", NULL, offset);
    int* exis = (int*) malloc(sizeof(int));
    *exis = 7;    
    offset += 8;
    Symbol *x = createSymbol(TYPEINT, "x", exis, offset);
    offset += 8;
    Symbol *assignacion = createSymbol(TYPEINT, "=", NULL, offset);
    
    // 3 + 4;
    struct TreeNode *treeTres = createNode(tres);
    struct TreeNode *treeCuatro = createNode(cuatro);
    struct TreeNode *treeSuma = createTree(suma, treeTres, treeCuatro);
    
    // x = 3 + 4;
    struct TreeNode *treeX = createNode(x);
    struct TreeNode *treeAssignacion = createTree(assignacion, treeX, treeSuma);

    Symbol *pyc = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *prog = createTree(pyc, treeAssignacion, NULL);
    
    // char *p = malloc(sizeof(char));
    // printTreeInOrder(prog, p);
        
    return prog;
}

