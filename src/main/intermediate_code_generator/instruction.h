#include "../types/symbol.h"

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

void insertInstructionNode(InstructionList *list, struct InstructionNode *newInstructionNode);
