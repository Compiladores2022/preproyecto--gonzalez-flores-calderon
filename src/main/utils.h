#include "../main/types/symbol.h"
#include "sintactic_analysis_tree/sintactic_analysis_tree.h"

#ifndef UTILS_H
#define UTILS_H

char * enumToString(types type);

void printTree(struct TreeNode *tree);

struct TreeNode * createNextTree(struct TreeNode *left, struct TreeNode *right);

struct TreeNode * createNewTree(types symbolType, struct TreeNode *left, struct TreeNode *right, char *operation );


#endif