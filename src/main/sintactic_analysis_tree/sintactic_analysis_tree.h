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

void checkTypeTree(struct TreeNode *tree);

#endif