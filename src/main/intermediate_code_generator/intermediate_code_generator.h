#include "../sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "instruction.h"

#ifndef INTERMEDIATE_CODE_GENERATOR_H
#define INTERMEDIATE_CODE_GENERATOR_H

struct InstructionNode * generateIntermediateCode(struct TreeNode *tree);

#endif