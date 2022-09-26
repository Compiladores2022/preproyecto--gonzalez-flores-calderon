#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize(InstructionList *list) {
    list->head = NULL;
}

struct Instruction createInstruction(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result) {
    Instruction newInstruction;

    newInstruction = (Instruction *) malloc (sizeof(Instruction));
    if(newInstruction == NULL){
        printf("couldn't create instruction, exiting\n");
        exit(EXIT_FAILURE);
    }

    newInstruction->name = name;
    newInstruction->fstOp = fstOp;
    newInstruction->sndOp = sndOp;
    newInstruction->result = result;

    return newInstruction;
}

struct InstructionNode createInstructionNode(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result) {
    struct InstructionNode *newInstructionNode;

    newInstructionNode = (struct InstructionNode *) malloc (sizeof(struct InstructionNode));
    if(newInstructionNode == NULL){
            printf("couldn't create instruction node, exiting\n");
            exit(EXIT_FAILURE);
    }
    else{
        newInstructionNode->instruction = createInstruction(name, fstOp, sndOp, result);
        newInstructionNode->next = NULL;
        return newInstructionNode;
    }
}


void insertInstructionNode(struct InstructionList *list, struct InstructionNode *newInstructionNode) {

    if (list->head == NULL) list->head = newInstructionNode;
    else list->last->next = newInstructionNode;
    list->last = newInstructionNode;
}
