#include "../types/symbol.h"

#ifndef SINTACTIC_ANALYSIS_TREE_H 
#define SINTACTIC_ANALYSIS_TREE_H

struct TreeNode {
    Symbol *info;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct {
    struct TreeNode *head;
}SintacticAnalysisTree;

struct TreeNode * createNode(Symbol *symbol);

struct TreeNode * createTree(Symbol *symbol, struct TreeNode *left, struct TreeNode *right);
    
void getTreeInOrder(struct TreeNode *tree, char * s);

void printTreeInOrder(struct TreeNode *tree);

int checkTypeTree(struct TreeNode *tree);

int checkParameterTypes(struct TreeNode *tree, struct ParameterList *list);

int checkParameters(struct TreeNode *tree,  struct ParameterNode *list, char *methodName);

int countExp(struct TreeNode *tree, int count);

int checkReturnInMethod(struct TreeNode *tree);

int countIfInMethod(struct TreeNode *tree, int count);

int checkIfInMethod(struct TreeNode *tree);

int checkReturnInIf(struct TreeNode *tree);

#endif