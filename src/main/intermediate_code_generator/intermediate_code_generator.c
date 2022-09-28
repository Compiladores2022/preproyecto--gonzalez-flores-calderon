#include "intermediate_code_generator.h"
#include "stdlib.h"
#include "utils.h"

int variableNumber = 1;
typedef enum {ADD,SUB,MUL,DIV,AND,OR} operations;
void generateIntermediateCode2(struct TreeNode *tree, struct InstructionNode * codeList);

/*
 * takes a decorated tree and returns an equivalent three address code program as a list of instructions
*/
struct InstructionNode * generateIntermediateCode(struct TreeNode *tree) {
    struct InstructionNode * code;
    generateSentenceCode(tree, code);   //left part cannot be a 'next' symbol, must be sentence or declaration

    return code;   
}

void generateIntermediateCode2(struct TreeNode *tree, struct InstructionNode * codeList) {
    generateSentenceCode(tree->left, codeList);   //left part cannot be a 'next' symbol, must be sentence or declaration
    
    if (tree->right != NULL) {  //right part is a next symbol if exists
        generateIntermediateCode2(tree->right, codeList);
    }
}

/* 
 * takes a tree and a list of instructions to save in the generated ones
 * returns the temporal symbol created to store the result of the current instruction
*/
Symbol * generateSentenceCode(struct TreeNode *tree, struct InstructionNode * codeList) {
    Symbol * temp1 = NULL; 
    Symbol * temp2 = NULL;
    if (tree->left != NULL && isOperationSymbol(tree->left->info->name)) {
        temp1 = generateSentenceCode(tree, codeList);   //generate left sentence if left is an operator
    }
    if (tree->right != NULL && isOperationSymbol(tree->right->info->name)) {
        temp2 = generateSentenceCode(tree, codeList);   //generate right sentence if right is an operator
    }

    Symbol * temp3 = addCurrentInstruction(tree, codeList, temp1, temp2);
    
    return temp3;
}

int isOperationSymbol(char *symbolName) {
    return arithmeticOperation(symbolName) || booleanOperation(symbolName);
}

Symbol * addCurrentInstruction(struct TreeNode *tree, struct InstructionNode * codeList, Symbol * temp1, Symbol * temp2) {
    if(temp1 == NULL && tree->left != NULL) {
        temp1 = tree->left->info;
    }
    if(temp2 == NULL && tree->right != NULL) {
        temp2 = tree->right->info;
    }
    
    Symbol * temp3;
    struct InstructionNode * instruction;
    switch (stringToInt(tree->info->name)) { //creates the instruction
        case 0:
            temp3 = tree->info;
            instruction = createInstructitionNode("ADD", temp1, temp2, temp3);
            break;
        case 1:
            temp3 = tree->info;
            instruction = createInstructitionNode("SUB", temp1, temp2, temp3);
            break;
        case 2:
            temp3 = tree->info;
            instruction = createInstructitionNode("MULT", temp1, temp2, temp3);
            break;
        case 3:
            temp3 = tree->info;
            instruction = createInstructitionNode("AND", temp1, temp2, temp3);
            break;
        case 4:
            temp3 = tree->info;
            instruction = createInstructitionNode("OR", temp1, temp2, temp3);
            break;
        case 5:
            temp3 = NULL;
            instruction = createInstructitionNode("MOV", temp1, NULL, temp2);
            break;
        case 6:
            if (temp3 == NULL)
            temp3 = temp2;
            instruction = createInstructitionNode("RET", NULL, NULL, temp3);
            break;
        default: printf("%s is not an operator\n", tree->info->name);
            exit(0);
            break;
    }
    
    insert(codeList, instruction);
    return temp3;
}
