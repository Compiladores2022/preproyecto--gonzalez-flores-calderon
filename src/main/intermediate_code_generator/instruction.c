#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize(InstructionList *list) {
    list->head = NULL;
    list->head = NULL;
}

struct Instruction * createInstruction(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result) {
    struct Instruction * newInstruction;

    newInstruction = (struct Instruction *) malloc (sizeof(struct Instruction));
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

struct InstructionNode * createInstructionNodeEmpty(){
    
    struct InstructionNode *newInstructionNode;
    newInstructionNode  = (struct InstructionNode *) malloc (sizeof(struct InstructionNode));
    if(newInstructionNode == NULL){
        exit(EXIT_FAILURE);
    }

    return newInstructionNode;
}

struct InstructionNode * createInstructionNode(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result) {
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

void insertInstructionNode(InstructionList *codeList, struct Instruction *Instruction) {
    
    struct InstructionNode *newNode = createInstructionNodeEmpty();
    if (codeList->head == NULL){ 
        newNode->instruction = Instruction;
        codeList->head = newNode;    
        newNode->next = NULL;
    }
    else{
        newNode->instruction = Instruction;
        codeList->last->next = newNode;
        newNode->next = NULL;
    }
    codeList->last = newNode;
}

void printInstructionList(InstructionList *list) {
    struct InstructionNode * node = list->head;
    while (node != NULL){
        printf("Name instruction: %s\n" ,node->instruction->name);
        node = node->next;
    }
}

int sizeList(InstructionList * list){
    int size = 0;
    while (list->head != NULL){
        list->head = list->head->next;
        size++;
    }
    return size;
}

int listEmpty(InstructionList *list){
    if(list->head == NULL)
        return 1;
    
    return 0;    
}