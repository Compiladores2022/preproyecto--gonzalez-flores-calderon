#include "intermediate_code_generator.h"
#include "stdlib.h"

int variableNumber = 1;
typedef enum {ADD,SUB,MUL,DIV,AND,OR} operations;

/*
 * takes a decorated tree and returns an equivalent three address code program
*/
struct InstructionNode * generateIntermediateCode(struct TreeNode *tree) {
    struct InstructionNode * code;
    generateSentenceCode(tree, code);   //left part cannot be a 'next' symbol, must be sentence or declaration

    return code;   
}

void generateIntermediateCode(struct TreeNode *tree, struct InstructionNode * codeList) {
    
    generateSentenceCode(tree->left, codeList);   //left part cannot be a 'next' symbol, must be sentence or declaration
    
    if (tree->right != NULL) {  //right part is a next symbol if exists
        generateIntermediateCode(tree->right, codeList);
    }
}

/* 
 * takes a tree and a string to write in
 * goes over the tree and adds the respective instructions to the given string
*/
Symbol * generateSentenceCode(struct TreeNode *tree, struct InstructionNode * codeList) {
    Symbol * temp1 = NULL, temp2 = NULL;
    if (tree->left != NULL && isOperationSymbol(tree->left->info->name)) {
        temp1 = generateSentenceCode(tree, codeList);
    }
    if (tree->right != NULL && isOperationSymbol(tree->right->info->name)) {
        temp2 = generateSentenceCode(tree, codeList);
    }

    Symbol * temp3 = addCurrentInstruction(struct TreeNode *tree, struct InstructionNode * codeList, Symbol * temp1, Symbol * temp2);
    
    return temp3;
}

int isOperationSymbol(char *symbolName) {
    return arithmeticOperation(symbolName) || booleanOperation(symbolName);
}