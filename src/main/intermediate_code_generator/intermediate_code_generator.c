#include "instruction.h"
#include "intermediate_code_generator.h"

#include "../utils.h"
#include <stdlib.h>
#include <stdio.h>

void generateIntermediateCode2(struct TreeNode *tree, InstructionList * codeList);
Symbol * generateSentenceCode(struct TreeNode *tree, InstructionList * codeList);
int isOperationSymbol(char *symbolName);
Symbol * addCurrentInstruction(struct TreeNode *tree, InstructionList * codeList, Symbol * temp1, Symbol * temp2);

/*
 * takes a decorated tree and returns an equivalent three address code program as a list of instructions
*/
InstructionList * generateIntermediateCode(struct TreeNode *tree) {
    InstructionList * codeList;
    codeList = (InstructionList *) malloc (sizeof(InstructionList));
    //initialize(codeList);
    
    generateIntermediateCode2(tree, codeList);   //left part cannot be a 'next' symbol, must be sentence or declaration
    return codeList;   
}

void generateIntermediateCode2(struct TreeNode *tree, InstructionList * codeList) {
    
    generateSentenceCode(tree->left, codeList);   //left part cannot be a 'next' symbol, must be sentence or declaration
    if (tree->right != NULL) {  //right part is a next symbol if exists
        generateIntermediateCode2(tree->right, codeList);
    }
}

/* 
 * takes a tree and a list of instructions to save in the generated ones
 * returns the temporal symbol created to store the result of the current instruction
*/
Symbol * generateSentenceCode(struct TreeNode *tree, InstructionList * codeList) {
    Symbol * temp1 = NULL; 
    Symbol * temp2 = NULL;
    if (tree->left != NULL) {
        if(isOperationSymbol(tree->left->info->name)){
            temp1 = generateSentenceCode(tree->left, codeList);   //generate left sentence if left is an operator            
        }
        else{
            temp1 = tree->left->info;
        }   
    }
    if (tree->right != NULL) {
        if(isOperationSymbol(tree->right->info->name)){
            temp2 = generateSentenceCode(tree->right, codeList);   //generate right sentence if right is an operator
        }
        else{
            temp2 = tree->right->info;
        }

    }
    Symbol * temp3 = addCurrentInstruction(tree, codeList, temp1, temp2);
    
    return temp3;
}

int isOperationSymbol(char *symbolName) {
    return arithmeticOperation(symbolName) || booleanOperation(symbolName);
}

Symbol * addCurrentInstruction(struct TreeNode *tree, InstructionList * codeList, Symbol * temp1, Symbol * temp2) {
    if(temp1 == NULL && tree->left != NULL) {
        temp1 = tree->left->info;
    }
    
    if(temp2 == NULL && tree->right != NULL) {
        temp2 = tree->right->info;
    }
    Symbol * temp3;
    int *operationResult = (int*) malloc(sizeof(int));
    struct Instruction * instruction;
    switch (stringToOperation(tree->info->name)) { //creates the instruction
        case ADD:
            temp3 = tree->info;
            *operationResult = *(int*)temp1->value + *(int*)temp2->value;
            temp3->value = operationResult;
            instruction = createInstruction("ADD", temp1, temp2, temp3);
            break;
        case SUB:
            temp3 = tree->info;
            *operationResult = *(int*)temp1->value - *(int*)temp2->value;
            temp3->value = operationResult;            
            instruction = createInstruction("SUB", temp1, temp2, temp3);
            break;
        case MULT:
            temp3 = tree->info;
            *operationResult = *(int*)temp1->value * *(int*)temp2->value;
            temp3->value = operationResult;            
            instruction = createInstruction("MULT", temp1, temp2, temp3);
            break;
        case AND:
            temp3 = tree->info;
            if(*(int*)temp1->value != 0 && *(int*)temp2->value != 0){
                *operationResult = 1;
                temp3->value = operationResult;            
            }
            *operationResult = 0;
            temp3->value = operationResult;            
            instruction = createInstruction("AND", temp1, temp2, temp3);
            break;
        case OR:
            temp3 = tree->info;
            if(*(int*)temp1->value == 0 && *(int*)temp2->value == 0){
                *operationResult = 0;
                temp3->value = operationResult;            
            }            
            *operationResult = 1;
            temp3->value = operationResult;            
            instruction = createInstruction("OR", temp1, temp2, temp3);
            break;
        case ASSIG:
            temp3 = NULL;
            instruction = createInstruction("ASSIG", temp2, NULL, temp1);
            break;
        case RET:
            if (temp3 == NULL)
            temp3 = temp2;
            instruction = createInstruction("RET", NULL, NULL, temp3);
            break;
        default: printf("%s is not an operator\n", tree->info->name);
            exit(0);
            break;
    }
    
    insertInstructionNode(codeList, instruction);
    return temp3;
}
