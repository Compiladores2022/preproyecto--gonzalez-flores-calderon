#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/intermediate_code_generator/intermediate_code_generator.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode * defaultTreeAdd();
struct TreeNode * defaultTreeSub();
int intermediteCodeGeneratorAdd();
int intermediteCodeGeneratorSub();

int main(){
    //Total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 0;
    
    //intermediteCodeGeneratorAdd() ? testsPassed++ : printf("Test intermediate code failed \n"); totalTests++;
    intermediteCodeGeneratorSub() ? testsPassed++ : printf("Test intermediate code failed \n"); totalTests++;

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int intermediteCodeGeneratorAdd(){

    struct TreeNode *treeDecorator =  defaultTreeAdd();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List: \n");
    printInstructionList(instructList);
    printf("Operations to Add and mov\n");
    printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

int intermediteCodeGeneratorSub(){
    
    struct TreeNode *treeDecorator =  defaultTreeSub();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List: \n");
    printInstructionList(instructList);
    printf("Operations to Sub and mov\n");
    printf("first: %d operation: %s secod: %d result: %d\n",*(int*) instructList->head->instruction->fstOp->value, instructList->head->instruction->result->name, *(int*) instructList->head->instruction->sndOp->value, *(int*)instructList->head->instruction->result->value);
    printf("first: %s operation: %s result: %d\n", instructList->last->instruction->fstOp->name, instructList->last->instruction->result->name, *(int*)instructList->last->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
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
    
    // 3 + 4;
    struct TreeNode *treeTen = createNode(sten);
    struct TreeNode *treeSix = createNode(ssix);
    struct TreeNode *treeSub = createTree(sub, treeTen, treeSix);
    
    // x = 3 + 4;
    struct TreeNode *treeX = createNode(x);
    struct TreeNode *treeAssig = createTree(assig, treeX, treeSub);

    Symbol *pyc = createSymbol(UNDEFINED, "next", NULL, 0);

    struct TreeNode *prog = createTree(pyc, treeAssig, NULL);
    
    // char *p = malloc(sizeof(char));
    // printTreeInOrder(prog, p);
        
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

