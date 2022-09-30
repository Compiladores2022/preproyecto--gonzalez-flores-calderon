#include "assembler_generator.h"
#include "../utils.h"
#include "stdio.h"

char * generateAssemblerCode(InstructionList * intermediateCode) {
    int localVarAmount = calculateFrameSpace(intermediateCode);
    if (localVarAmount % 2 == 1) {  //make it pair to ensure required space is multiple of 16
        localVarAmount++;
    }
    
    char * code = "enter $(8 * ";
    code = strcat(code, intToString(localVarAmount));

    code = strcat(code, "), $0\n");
    code = strcat(code, "MOV -8(%rbp), %rdi\n");

    struct InstructionNode * currentNode = intermediateCode->head;
    while(currentNode != NULL) {
        generateInstruction(currentNode->instruction, code);
        currentNode = currentNode->next;
    }

    code = strcat(code, "leave\nret\n");

    return code;
}

void generateInstruction(struct Instruction * instruction, char * code) {
    switch(stringToOperation(instruction->name)) {
        case ADD:
            generateSimpleArithmeticCode(instruction, code, "ADD");
            break;
            
        case SUB:
            generateSimpleArithmeticCode(instruction, code, "SUB");
            break;
            
        case MULT:
            generateSimpleArithmeticCode(instruction, code, "IMUL");
            break;
            
        case AND:
            break;
            
        case OR:
            break;
            
        case ASSIG:
            break;
            
        case RET:
            break;
        
        default:
            printf("\nunrecognized operation: %s\n", instruction->name);
            break;
    }
}

void generateSimpleArithmeticCode(struct Instruction * instruction, char * code, char * operation) {
    //first symbol
    char * location = getSymbolLocation(instruction->fstOp);
    code = strcat(code, "MOV %r10, ");
    code = strcat(code, location);
    code = strcat(code, "\n");

    //second symbol and addition
    location = getSymbolLocation(instruction->sndOp);
    code = strcat(code, operation);
    code = strcat(code, " %r10, ");
    code = strcat(code, location);
    code = strcat(code, "\n");

    //moving result to the third symbol
    location = getSymbolLocation(instruction->result);
    code = strcat(code, "MOV ");
    code = strcat(code, location);
    code = strcat(code, ", %r10\n");
}
