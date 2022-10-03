#include "assembler_generator.h"
#include "../utils.h"
#include "stdio.h"
#include <string.h>

void processThreeAddressCode(struct Instruction * instruction, char * code);
void generateSimpleLogicArithmeticCode(struct Instruction * instruction, char * code, char * operation);
void generateInstructionCode(char * code, char * operation, char * dest, char * value);
char * getSymbolLocation(Symbol * symbol);

char * generateAssemblerCode(InstructionList * intermediateCode, int maxOffset) {
    int requiredFrameSpace = maxOffset / 8;
    if (requiredFrameSpace % 2 == 1) {  //make it pair to ensure required space is multiple of 16
        requiredFrameSpace++;
    }
    
    char * code = "	.globl	main\n	.type	main, @function\nmain:\n.LFB0:\n";
    char * requiredSpace = strcat("$(8 * ", intToString(requiredFrameSpace));

    generateInstructionCode(code, "ENTER", strcat(requiredSpace, ")"), "$0");

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
            
        case AND:
            generateSimpleLogicArithmeticCode(instruction, code, "AND");
            break;
            
        case OR:
            generateSimpleLogicArithmeticCode(instruction, code, "OR");
            break;
            
        case ASSIG: {
            char * location = getSymbolLocation(instruction->fstOp);
            generateInstructionCode(code, "MOV", location, "%r10");

            location = getSymbolLocation(instruction->result);
            generateInstructionCode(code, "MOV", "%r10", location);
            break;
        }    
        case RET: {
            char * location = getSymbolLocation(instruction->result);
            generateInstructionCode(code, "MOV", location, "%rax");
            break;
        }        
        default:
            printf("\nunrecognized operation: %s\n", instruction->name);
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
    location = getSymbolLocation(instruction->sndOp);
    generateInstructionCode(code, operation, location, "%r10");

    //moving result to the third symbol
    location = getSymbolLocation(instruction->result);
    generateInstructionCode(code, "MOV", "%r10", location);
}

/*
 * generates an assembler instruction for a given operation
 * code is the string where the instruction will be added
 * dest is the first parameter of the operation and where the result will be stored
 * value is the second parameter
*/
void generateInstructionCode(char * code, char * operation, char * dest, char * value) {
    code = strcat(code, operation);
    code = strcat(code, " ");
    code = strcat(code, dest);
    code = strcat(code, ", ");
    code = strcat(code, value);
    code = strcat(code, "\n");
}

char * getSymbolLocation(Symbol * symbol) {
    if (symbol->offset == 0) {
        return strcat("$", intToString(*(int*)symbol->value));
    } else {
        char * location = strcat("-", intToString(symbol->offset));
        return strcat(location, "(%rbp)");
    }
}