#include "../types/type_structs.h"

#ifndef SINTACTIC_ANALYSIS_TREE_H 
#define SINTACTIC_ANALYSIS_TREE_H

struct Node {
    Symbol info;
    struct Node *left;
    struct Node *right;
};

typedef struct {
    Node *head;
}SintacticAnalysisTree;

void newNode(Symbol *symbol);

void createTree(struct Node *left, struct Node *right);

#endif