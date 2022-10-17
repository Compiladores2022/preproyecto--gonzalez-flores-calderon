#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/intermediate_code_generator/intermediate_code_generator.h"
#include "../main/assembler_code_generator/assembler_generator.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int oneInstructionTest();
int multipleInstructionWithIdTest();
int singleAssignmentInstructionTest();

int main(){
    int testsPassed = 0, totalTests = 0;
    
    oneInstructionTest() ? testsPassed++ : printf("Test single instruction test failed \n"); totalTests++;
    singleAssignmentInstructionTest() ? testsPassed++ : printf("Test single assignment instruction test failed \n"); totalTests++;
    multipleInstructionWithIdTest() ? testsPassed++ : printf("Test instruction with identifiers test failed \n"); totalTests++;

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int oneInstructionTest(){
    int offset = 0;

    int *a = (int *)malloc(sizeof(int));
    *a = 3;
    Symbol *symbol1 = createSymbol(TYPEINT, "3", a, 0);
    int *b = (int *)malloc(sizeof(int));
    *b = 4;
    Symbol *symbol2 = createSymbol(TYPEINT, "4", b, 0);
    offset += 8;
    Symbol *symbol3 = createSymbol(TYPEINT, "+", NULL, offset);
    Symbol *symbol4 = createSymbol(UNDEFINED, "next", NULL, 0);
    
    // 3 + 4;
    struct TreeNode *left = createNode(symbol1);
    struct TreeNode *right = createNode(symbol2);
    struct TreeNode *tree = createTree(symbol3, left, right);
    struct TreeNode *treeNext = createTree(symbol4, tree, NULL);

    InstructionList *instructList = generateIntermediateCode(treeNext);
    char * assemblerCode = generateAssemblerCode(instructList, offset);
    char * expected = "	.globl	main\n	.type	main, @function\nmain:\n.LFB0:\nENTER $(8 * 2), $0\nMOV $3, %r10\nADD $4, %r10\nMOV %r10, -8(%rbp)\nLEAVE\nRET\n";
    
    return strcmp(expected, assemblerCode) == 0;
}

int singleAssignmentInstructionTest(){
    int offset = 8;

    Symbol *symbol1 = createSymbol(TYPEBOOL, "x", NULL, offset);
    int *b = (int *)malloc(sizeof(int));
    *b = 0;
    Symbol *symbol2 = createSymbol(TYPEBOOL, "false", b, 0);
    Symbol *symbol3 = createSymbol(TYPEBOOL, "=", NULL, offset);
    Symbol *symbol4 = createSymbol(UNDEFINED, "next", NULL, 0);
    
    // x = false;
    struct TreeNode *left = createNode(symbol1);
    struct TreeNode *right = createNode(symbol2);
    struct TreeNode *tree = createTree(symbol3, left, right);
    struct TreeNode *treeNext = createTree(symbol4, tree, NULL);

    InstructionList *instructList = generateIntermediateCode(treeNext);
    char * assemblerCode = generateAssemblerCode(instructList, offset);
    char * expected = "	.globl	main\n	.type	main, @function\nmain:\n.LFB0:\nENTER $(8 * 2), $0\nMOV $0, %r10\nMOV %r10, -8(%rbp)\nLEAVE\nRET\n";

    return strcmp(expected, assemblerCode) == 0;
}

int multipleInstructionWithIdTest(){
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
    

    InstructionList *instructList = generateIntermediateCode(treeNext);
    char * assemblerCode = generateAssemblerCode(instructList, offset);
    char * expected = "	.globl	main\n	.type	main, @function\nmain:\n.LFB0:\nENTER $(8 * 4), $0\nMOV $5, %r10\nMOV %r10, -8(%rbp)\nMOV $10, %r10\nMOV %r10, -16(%rbp)\nMOV -8(%rbp), %r10\nIMUL -16(%rbp), %r10\nMOV %r10, -24(%rbp)\nMOV -24(%rbp), %rax\nLEAVE\nRET\n";
    
    return strcmp(expected, assemblerCode) == 0;
}