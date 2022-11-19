#include "instruction.h"
#include "intermediate_code_generator.h"

#include "../utils/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int labelNumber = 1;

void translateTreeIntoCode(struct TreeNode *tree, InstructionList * codeList);
Symbol * generateSentenceCode(struct TreeNode *tree, InstructionList * codeList);
int isOperationSymbol(char *symbolName);
Symbol * addCurrentInstruction(struct TreeNode *tree, InstructionList * codeList, Symbol * temp1, Symbol * temp2);
void createParameterInstructions(struct TreeNode *parameters, InstructionList * codeList);
char * createLabel(char *name);
char * createGenericLabel();
char * getOperationName(Symbol * s);
void checkMethodCall(struct TreeNode *left, struct TreeNode *right, InstructionList * codeList);

/*
 * takes a decorated tree and returns an equivalent three address code program as a list of instructions
*/
InstructionList * generateIntermediateCode(struct TreeNode *tree) {
    InstructionList * codeList;
    codeList = (InstructionList *) malloc (sizeof(InstructionList));
    
    translateTreeIntoCode(tree, codeList);
    return codeList;   
}

void translateTreeIntoCode(struct TreeNode *tree, InstructionList * codeList) {
    if (tree->left != NULL) {    //left part cannot be a 'next' symbol, must be sentence or declaration
        generateSentenceCode(tree->left, codeList);
    }
    if (tree->right != NULL) {  //right part is a next symbol if exists
        translateTreeIntoCode(tree->right, codeList);
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
    Symbol *temp3 = NULL;
    int *operationResult = (int*) malloc(sizeof(int));
    struct Instruction * instruction = NULL;
    char * operation = getOperationName(tree->info);
    switch (stringToOperation(operation)) { //creates the instruction
        case ADD:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("ADD", temp1, temp2, temp3);
            break;
        case SUB:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            if (temp2 == NULL) {
                instruction = createInstruction("SUB", temp1, NULL, temp3);
            } else {
                instruction = createInstruction("SUB", temp1, temp2, temp3);
            }
            break;
        case MULT:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("MULT", temp1, temp2, temp3);
            break;
        case DIV:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("DIV", temp1, temp2, temp3);
            break;
        case MOD:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("MOD", temp1, temp2, temp3);
            break;
        case AND:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("AND", temp1, temp2, temp3);
            break;
        case OR:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("OR", temp1, temp2, temp3);
            break;
        case NOT:
            temp3 = tree->info;
            checkMethodCall(tree->left, NULL, codeList);
            instruction = createInstruction("NOT", temp1, NULL, temp3);
            break;
        case ASSIG:
            checkMethodCall(NULL, tree->right, codeList);
            instruction = createInstruction("ASSIG", temp2, NULL, temp1);
            temp1->value = temp2->value;
            break;
        case EQUAL:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("EQUAL", temp1, temp2, temp3);
            break;
        case GREAT:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("GREAT", temp1, temp2, temp3);
            break;
        case LESS:
            temp3 = tree->info;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("LESS", temp1, temp2, temp3);
            break;
        case RET:
            temp3 = temp2;
            checkMethodCall(tree->left, tree->right, codeList);
            instruction = createInstruction("RET", NULL, NULL, temp3);
            break;
        case METHDECL: {
            Symbol *methodLabel = createSymbol(UNDEFINED, createLabel(tree->info->name), NULL, 0);
            insertInstructionNode(codeList, createInstruction("METHDECL", methodLabel, tree->info, NULL));
            translateTreeIntoCode(tree->left, codeList);    //load method content
            } break;
        case EXTERNMETH: {
            Symbol *methodLabel = createSymbol(UNDEFINED, createLabel(tree->info->name), NULL, 0);
            insertInstructionNode(codeList, createInstruction("EXTERNMETH", methodLabel, tree->info, NULL));
            } break;
        case METHCALL: {
            createParameterInstructions(tree->left, codeList);
            Symbol *methodLabel = createSymbol(UNDEFINED, createLabel(tree->info->name), NULL, 0);
            instruction = createInstruction("METHCALL", methodLabel, NULL, NULL);
            } break;
        case IF: {
            generateSentenceCode(tree->left, codeList);    //calculate expression result
            Symbol *endLabel = createSymbol(UNDEFINED, createGenericLabel("ENDIF"), NULL, 0);
            Symbol *expressionResult = codeList->last->instruction->result;
            insertInstructionNode(codeList, createInstruction("JMPFALSE", expressionResult, NULL, endLabel));
            
            translateTreeIntoCode(tree->right, codeList); //generate code for 'then' block
            instruction = createInstruction(endLabel->name, NULL, NULL, NULL);
            } break;
        case IFELSE: {
            generateSentenceCode(tree->left, codeList);    //calculate expression result
            Symbol *elseLabel = createSymbol(UNDEFINED, createGenericLabel("ELSE"), NULL, 0);
            Symbol *endLabel = createSymbol(UNDEFINED, createGenericLabel("ENDIF"), NULL, 0);
            Symbol *expressionResult = codeList->last->instruction->result;
            insertInstructionNode(codeList, createInstruction("JMPFALSE", expressionResult, NULL, elseLabel));

            translateTreeIntoCode(tree->right->left, codeList); //generate code for 'then' block
            insertInstructionNode(codeList, createInstruction("JMP", NULL, NULL, endLabel));
            
            insertInstructionNode(codeList, createInstruction(elseLabel->name, NULL, NULL, NULL));  //insert else label
            translateTreeIntoCode(tree->right->right, codeList); //generate code for 'else' block

            insertInstructionNode(codeList, createInstruction("IFELSE", expressionResult, elseLabel, endLabel));
            translateTreeIntoCode(tree->right->left, codeList); //generate code for 'then' block

            instruction = createInstruction(endLabel->name, NULL, NULL, NULL);
            } break;
        case WHILE: {
            Symbol *whileCheckLabel = createSymbol(UNDEFINED, createGenericLabel("WHILECHECK"), NULL, 0);
            insertInstructionNode(codeList, createInstruction(whileCheckLabel->name, NULL, NULL, NULL));  //insert while check label

            generateSentenceCode(tree->left, codeList);    //calculate expression result
            Symbol *expressionResult = codeList->last->instruction->result;
            Symbol *endLabel = createSymbol(UNDEFINED, createGenericLabel("WHILEEND"), NULL, 0);
            insertInstructionNode(codeList, createInstruction("JMPFALSE", expressionResult, NULL, endLabel));

            translateTreeIntoCode(tree->right, codeList); //generate code for while block
            
            insertInstructionNode(codeList, createInstruction("JMP", NULL, NULL, whileCheckLabel));
            instruction = createInstruction(endLabel->name, NULL, NULL, NULL);  //insert while end label
            } break;
        case NEXTBLOCK: //this case happens when a new block is inserted inside another
            translateTreeIntoCode(tree, codeList);
            instruction = NULL;
            break;
        default: printf("-> ERROR: %s is not an operator\n", tree->info->name);
            exit(0);
    }
    
    if (instruction != NULL) {
        insertInstructionNode(codeList, instruction);
    }
    return temp3;
}

void createParameterInstructions(struct TreeNode *parameters, InstructionList * codeList) {
    if (parameters == NULL)
        return;

    Symbol *expressionResult;
    if (isOperationSymbol(parameters->left->info->name)) {
        translateTreeIntoCode(parameters, codeList);  //calculate parameter expression result
        expressionResult = codeList->last->instruction->result;
    } else {
        expressionResult = parameters->left->info;
    }
    
    insertInstructionNode(codeList, createInstruction("PUSH", expressionResult, NULL, NULL)); //pushParameter
    createParameterInstructions(parameters->right, codeList);
}

char * createGenericLabel(char * name) {
    char * label = malloc(strlen(name) + 6 * sizeof(char *));
    strcpy(label, name);
    strcat(label, " ");
    strcat(label, intToString(labelNumber));
    strcat(label, ":");
    
    labelNumber++;
    return label;
}

char * createLabel(char* name) {
    char * label = malloc(strlen(name) * sizeof(char *));
    strcpy(label, name);
    
    return label;
}

char * getOperationName(Symbol * s) {
    if (s->it == METHOD) {
        return "methoddecl";
    } else if (s->it == EXTERNMETHOD) {
        return "externmethod";
    } else if (s->it == METHODCALL) {
        return "methodcall";
    } else {
        return s->name;
    }
}

void checkMethodCall(struct TreeNode *left, struct TreeNode *right, InstructionList * codeList) {
    if (left != NULL && left->info->it == METHODCALL) {
        generateSentenceCode(left, codeList);
    }

    if (right != NULL && right->info->it == METHODCALL) {
        generateSentenceCode(right, codeList);
    }
}