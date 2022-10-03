#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/intermediate_code_generator/intermediate_code_generator.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode * defaultTree();
int intermediteCodeGenerator();

int main(){
    //Total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 0;
    
    intermediteCodeGenerator() ? testsPassed++ : printf("Test intermediate code failed \n"); totalTests++;

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int intermediteCodeGenerator(){

    struct TreeNode *treeDecorator =  defaultTree();
    InstructionList *instructList = generateIntermediateCode(treeDecorator);
    printf("Code List: \n");
    printInstructionList(instructList);
    printf("%d\n", *(int*) instructList->head->instruction->result->value);
    if(sizeList(instructList) == 2){
         return 1;
    }
    return 0;   
}

struct TreeNode * defaultTree(){
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