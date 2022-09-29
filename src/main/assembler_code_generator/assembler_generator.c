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
    code = strcat(code, "mov %rdi, -8(%rbp)\n");

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
            //first symbol
            char * location = getSymbolLocation(instruction->fstOp);
            code = strcat(code, "MOV ");
            code = strcat(code, location);
            code = strcat(code, " %r10\n");

            //second symbol and addition
            location = getSymbolLocation(instruction->sndOp);
            code = strcat(code, "ADD ");
            code = strcat(code, location);
            code = strcat(code, "%r10\n");

            //moving result to the third symbol
            location = getSymbolLocation(instruction->result);
            code = strcat(code, "MOV %r10");
            code = strcat(code, location);
            code = strcat(code, "\n");
            break;
            
        case SUB:
            break;
            
        case MULT:
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
