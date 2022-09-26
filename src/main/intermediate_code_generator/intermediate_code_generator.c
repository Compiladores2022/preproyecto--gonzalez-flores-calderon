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

addCurrentInstruction(struct TreeNode *tree, struct InstructionNode * codeList, Symbol * temp1, Symbol * temp2){
    switch (tree->info->name) {
        case "+":
            if(temp1 == NULL){
                temp1 = tree->left->info;   
            }
            if(temp2 == NULL){
                temp2 = tree->right->info;  
            }
            char *str = malloc(sizeof(char *));
            sprintf(str, "%d", variableNumber);
            Symbol * temp3 = createSymbol(temp1->type, "temp" + str, (*(int *)temp1->value + *(int *)temp2->value);
            struct InstructionNode *instruct = createInstructition("ADD", temp1, temp2, temp3);
            insert(codeList, instruct);
            break;
        case "-": 
            if(temp1 == NULL){
                temp1 = tree->left->info;    
            }
            if(temp2 == NULL){
                temp2 = tree->right->info;       
            }
            char *str = malloc(sizeof(char *));
            sprintf(str, "%d", variableNumber);
            Symbol * temp3 = createSymbol(temp1->type, "temp" + str, (*(int *)temp1->value + *(int *)temp2->value);
            struct InstructionNode *instruct = createInstructition("SUB", temp1, temp2, temp3);
            insert(codeList, instruct);
            break;
        case "*": 
            if(temp1 == NULL){
                temp1 = tree->left->info;    
            }
            if(temp2 == NULL){
                temp2 = tree->right->info;       
            }
            char *str = malloc(sizeof(char *));
            sprintf(str, "%d", variableNumber);
            Symbol * temp3 = createSymbol(temp1->type, "temp" + str, (*(int *)temp1->value + *(int *)temp2->value);
            struct InstructionNode *instruct = createInstructition("MULT", temp1, temp2, temp3);
            insert(codeList, instruct);
            break;
        case "&&": 
            if(temp1 == NULL){
                temp1 = tree->left->info;    
            }
            if(temp2 == NULL){
                temp2 = tree->right->info;       
            }
            char *str = malloc(sizeof(char *));
            sprintf(str, "%d", variableNumber);
            Symbol * temp3 = createSymbol(temp1->type, "temp" + str, (*(int *)temp1->value + *(int *)temp2->value);
            struct InstructionNode *instruct = createInstructition("AND", temp1, temp2, temp3);
            insert(codeList, instruct);
            break;
        case "||": 
            if(temp1 == NULL){
                temp1 = tree->left->info;    
            }
            if(temp2 == NULL){
                temp2 = tree->right->info;       
            }
            char *str = malloc(sizeof(char *));
            sprintf(str, "%d", variableNumber);
            Symbol * temp3 = createSymbol(temp1->type, "temp" + str, (*(int *)temp1->value + *(int *)temp2->value);
            struct InstructionNode *instruct = createInstructition("OR", temp1, temp2, temp3);
            insert(codeList, instruct);
            break;
        case "return": 
            if(temp1 == NULL){
                temp1 = tree->left->info;    
            }
            if(temp2 == NULL){
                temp2 = tree->right->info;       
            }
            char *str = malloc(sizeof(char *));
            sprintf(str, "%d", variableNumber);
            Symbol * temp3 = createSymbol(temp1->type, "temp" + str, (*(int *)temp1->value + *(int *)temp2->value);
            struct InstructionNode *instruct = createInstructition("RETURN", temp1, temp2, temp3);
            insert(codeList, instruct);
            break;
        default : printf("%s is not an operator\n", tree->info->name);
            exit(0);
    }
}