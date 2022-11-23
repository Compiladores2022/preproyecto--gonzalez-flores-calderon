#include "assembler_generator.h"
#include "../utils/utils.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

void processThreeAddressCode(struct Instruction * instruction, char * code);
void generateSimpleLogicArithmeticCode(struct Instruction * instruction, char * code, char * operation);
void generateInstructionCode(char * code, char * operation, char * dest, char * value);
void generateTwoAddressInstruction(char * code, char * operation, char * dest);
char * getSymbolLocation(Symbol * symbol);
int isLabel(struct Instruction * instruction);

int requiredFrameSpace = 0;

char * generateAssemblerCode(InstructionList * intermediateCode, int maxOffset) {
    requiredFrameSpace = maxOffset / 8;
    if (requiredFrameSpace % 2 == 1) {  //make it pair to ensure required space is multiple of 16
        requiredFrameSpace++;
    }
    char * code = (char *) malloc(37 * sizeof(char *)); //37 is the amount of characters in the below string + \0
    strcpy(code, "	.globl	main\n	.type	main, @function\n");

    struct InstructionNode * currentNode = intermediateCode->head;
    while(currentNode != NULL) {
        processThreeAddressCode(currentNode->instruction, code);
        currentNode = currentNode->next;
    }
    code = strcat(code, "LEAVE\nRET\n");

    return code;
}

/*
 * given a three address code instruction, an equivalent assembler program is generated
 * instruction is the three address code instruction
 * code is the string where the generated code will be added
*/
void processThreeAddressCode(struct Instruction * instruction, char * code) {
    switch(stringToOperation(instruction->name)) {
        case ADD:
            generateSimpleLogicArithmeticCode(instruction, code, "ADD");
            break;

        case SUB:
            generateSimpleLogicArithmeticCode(instruction, code, "SUB");
            break;

        case MULT:
            generateSimpleLogicArithmeticCode(instruction, code, "IMUL");
            break;

        case DIV:
            generateSimpleLogicArithmeticCode(instruction, code, "DIV");
            break;

        case MOD:
            generateSimpleLogicArithmeticCode(instruction, code, "MOD");
            break;

        case AND:
            generateSimpleLogicArithmeticCode(instruction, code, "AND");
            break;

        case OR:
            generateSimpleLogicArithmeticCode(instruction, code, "OR");
            break;

        case NOT:
            generateSimpleLogicArithmeticCode(instruction, code, "NOT");
            break;

        case ASSIG: {
            char * location = getSymbolLocation(instruction->fstOp);
            generateInstructionCode(code, "MOV", location, "%r10");

            location = getSymbolLocation(instruction->result);
            generateInstructionCode(code, "MOV", "%r10", location);
        } break;
        
        case EQUAL: {
            char * location1 = getSymbolLocation(instruction->fstOp);
            char * location2 = getSymbolLocation(instruction->sndOp);
            generateInstructionCode(code, "CMP", location1, location2);
            char * location3 = getSymbolLocation(instruction->result);
            generateTwoAddressInstruction(code, "SET", location3);
        } break;
        
        case GREAT: {
            char * location1 = getSymbolLocation(instruction->fstOp);
            char * location2 = getSymbolLocation(instruction->sndOp);
            generateInstructionCode(code, "CMP", location1, location2);
            char * location3 = getSymbolLocation(instruction->result);
            generateTwoAddressInstruction(code, "SET", location3);
        } break;
        
        case LESS: {
            char * location1 = getSymbolLocation(instruction->fstOp);
            char * location2 = getSymbolLocation(instruction->sndOp);
            generateInstructionCode(code, "CMP", location1, location2);
            char * location3 = getSymbolLocation(instruction->result);
            generateTwoAddressInstruction(code, "SET", location3);
        } break;

        case METHDECL:
            strcat(code, instruction->fstOp->name);
            strcat(code, ":\n");
            generateTwoAddressInstruction(code, "PUSH", "ebp"); //Store the current stack frame
            generateInstructionCode(code, "MOV", "ebp", "esp"); //Preserve ESP into EBP for argument references
            generateInstructionCode(code, "AND", "esp", "0xfffffff0"); //Align the stack to allow library calls
            break;

        case METHCALL: {
            generateTwoAddressInstruction(code, "CALL", instruction->fstOp->name);
            generateTwoAddressInstruction(code, "POP", "ebx");
            if (instruction->sndOp != NULL) {
                char * methodResult = getSymbolLocation(instruction->sndOp);
                generateInstructionCode(code, "MOV", methodResult, "%rax");
            }
        } break;

        case PUSH:
            generateTwoAddressInstruction(code, "PUSH", getSymbolLocation(instruction->fstOp));
            break;

        case JMP:
            generateTwoAddressInstruction(code, "JMP", instruction->result->name);
            break;

        case JMPFALSE: {
            char * location = getSymbolLocation(instruction->fstOp);
            generateInstructionCode(code, "MOV", location, "%rax");
            generateInstructionCode(code, "MOV", "%eax", "%rax");
            generateInstructionCode(code, "MOV", "%edx", "1");
            generateInstructionCode(code, "CMP", "%edx", "%eax");

            generateTwoAddressInstruction(code, "JNE", instruction->result->name);
        } break;

        case RETURNVAL: {
            char * location = getSymbolLocation(instruction->result);
            generateInstructionCode(code, "MOV", "%rax", location);
        } break;
        
        case RET:
            generateInstructionCode(code, "MOV", "esp", "ebp"); //Restore the stack and ebp
            generateTwoAddressInstruction(code, "POP", "ebp");
            strcat(code, "RET\n");
            break;
        
        case MAINMETHOD: {
            strcat(code, "main:\n.LFB0:\n");
            char * frameSpace = intToString(requiredFrameSpace);
            char * requiredSpace = malloc(12 * sizeof(char *));
            strcpy(requiredSpace, "$(8 * ");
            strcat(requiredSpace, frameSpace);
            generateInstructionCode(code, "ENTER", strcat(requiredSpace, ")"), "$0");
        } break;

        default:
            if (isLabel(instruction)) {             //generate a new label
                strcat(code, instruction->name);
                strcat(code, "\n");
            } else {
                printf("\n-> ERROR: unrecognized operation %s\nprocess terminated\n", instruction->name);
                exit(0);
            }
            break;
    }
}

/*
 * generates the assembler code for a given three address code logic/arithmetic operation
 * instruction is the three address code instruction
 * code is the string where the generated instruction will be added
 * operation is the operation that wants to be performed
*/
void generateSimpleLogicArithmeticCode(struct Instruction * instruction, char * code, char * operation) {
    //first symbol
    char * location = getSymbolLocation(instruction->fstOp);
    generateInstructionCode(code, "MOV", location, "%r10");
    //second symbol and operation
    free(location);
    location = getSymbolLocation(instruction->sndOp);
    generateInstructionCode(code, operation, location, "%r10");
    //moving result to the third symbol
    free(location);
    location = getSymbolLocation(instruction->result);
    generateInstructionCode(code, "MOV", "%r10", location);
    free(location);
}

/*
 * generates an assembler instruction for a given operation
 * code is the string where the instruction will be added
 * dest is the first parameter of the operation and where the result will be stored
 * value is the second parameter
*/
void generateInstructionCode(char * code, char * operation, char * dest, char * value) {
    strcat(code, operation);
    strcat(code, " ");
    strcat(code, dest);
    strcat(code, ", ");
    strcat(code, value);
    strcat(code, "\n");
}

void generateTwoAddressInstruction(char * code, char * operation, char * dest) {
    strcat(code, operation);
    strcat(code, " ");
    strcat(code, dest);
    strcat(code, "\n");
}

char * getSymbolLocation(Symbol * symbol) {
    char * location = (char *) malloc(10 * sizeof(char *));
    if (symbol->offset == 0) {
        strcpy(location, "$");
        strcat(location, intToString(*(int*)symbol->value));
    } else {
        strcpy(location, "-");
        strcat(location, intToString(symbol->offset));
        strcat(location, "(%rbp)");
    }
    return location;
}

int isLabel (struct Instruction * instruction) {
    int value;
    if(instruction->name != NULL && instruction->fstOp == NULL && instruction->sndOp == NULL && instruction->result == NULL) {
        value = 1;
    } else { value = 0; }
    return value;
}
