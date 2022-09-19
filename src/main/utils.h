#include "../main/types/symbol.h"
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"

#ifndef UTILS_H
#define UTILS_H

char * enumToString(types type);

void printTree(struct TreeNode *tree);

struct TreeNode * newOperationTree(struct TreeNode *left, struct TreeNode *right, char *operation );

struct TreeNode * newBoolOperationTree(struct TreeNode *left, struct TreeNode *right, char *operation );

#endif