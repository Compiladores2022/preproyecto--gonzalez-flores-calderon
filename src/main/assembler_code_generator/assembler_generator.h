#include "../intermediate_code_generator/instruction.h"

#ifndef ASSEMBLER_GENERATOR_H
#define ASSEMBLER_GENERATOR_H

typedef enum {ADD, SUB, MULT, AND, OR, ASSIG, RET} operations;

char * generateAssemblerCode(InstructionList * intermediateCode);

#endif