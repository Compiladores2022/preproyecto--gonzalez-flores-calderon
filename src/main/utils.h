#include "../main/types/symbol.h"
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"

#ifndef UTILS_H
#define UTILS_H

char * enumToString(types type);

void printTree(struct TreeNode *tree);

struct TreeNode * newDeclarationTree(struct TreeNode *left, struct TreeNode *right);

#endif