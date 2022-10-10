#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/intermediate_code_generator/intermediate_code_generator.h"
#include "../main/assembler_code_generator/assembler_generator.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int oneInstructionTest();

int main(){
    //total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 0;
    
    oneInstructionTest() ? testsPassed++ : printf("Test single instruction test failed \n"); totalTests++;

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
    char * assemblerCode = generateAssemblerCode(instructList, 8);
    char * expected = "	.globl	main\n	.type	main, @function\nmain:\n.LFB0:\nENTER $(8 * 2), $0\nMOV $3, %r10\nADD $4, %r10\nMOV %r10, -8(%rbp)\nLEAVE\nRET\n";
    
    return strcmp(expected, assemblerCode) == 0;
}
