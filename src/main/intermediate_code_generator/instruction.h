#include "../types/symbol.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct Instruction {
    char *name;
    Symbol *fstOp;
    Symbol *sndOp;
    Symbol *result;
};

struct InstructionNode{
    struct Instruction *instruction;
    struct InstructionNode *next;
};

typedef struct {
    struct InstructionNode *head;
    struct InstructionNode *last;
}InstructionList;

struct Instruction * createInstruction(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result);

struct InstructionNode * createInstructionNode(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result);

struct InstructionNode * createInstructionNodeEmpty();

void insertInstructionNode(InstructionList *list, struct Instruction *Instruction);

void printInstructionList(InstructionList *list);

int sizeList(InstructionList * list);

void initialize(InstructionList *list);

int listEmpty(InstructionList *list);

#endif
