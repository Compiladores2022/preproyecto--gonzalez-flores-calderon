#include "../types.symbol.h"

struct Instruction {
    char *name;
    Symbol *fstOp;
    Symbol *sndOp;
    Symbol *result;
};

typedef struct {
    Instruction *instruction;
    InstructionNode *next;
}InstructionNode;

typedef struct {
    struct InstructionNode *head;
    struct InstructionNode *last;
}InstructionList;

struct InstructionNode createInstructionNode(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result);

void insertInstructionNode(struct InstructionList *list, struct InstructionNode *newInstructionNode);

struct Instruction createInstruction(char *name, Symbol *fstOp, Symbol *sndOp, Symbol *result);
