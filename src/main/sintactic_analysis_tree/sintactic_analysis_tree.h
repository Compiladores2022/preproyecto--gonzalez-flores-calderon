#include "../types/symbol.h"

#ifndef SINTACTIC_ANALYSIS_TREE_H 
#define SINTACTIC_ANALYSIS_TREE_H

struct Node {
    Symbol *info;
    struct Node *left;
    struct Node *right;
};

typedef struct {
    struct Node *head;
}SintacticAnalysisTree;

struct Node * createNode(Symbol *symbol);

SintacticAnalysisTree * createTree(Symbol *symbol, struct Node *right, struct Node *left);

#endif