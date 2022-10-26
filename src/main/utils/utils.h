#include "../types/symbol.h"
#include "../sintactic_analysis_tree/sintactic_analysis_tree.h"

#ifndef UTILS_H
#define UTILS_H

typedef enum {ADD, SUB, MULT, AND, OR, ASSIG, RET} operations;

char * enumToString(types type);

void printTree(struct TreeNode *tree);

struct TreeNode * createNextTree(struct TreeNode *left, struct TreeNode *right);

struct TreeNode * createNewTree(types symbolType, struct TreeNode *left, struct TreeNode *right, char *operation, int offset);

int arithmeticOperation(char * operation);

int booleanOperation(char * operation);

char * intToString(int source);

int stringToOperation(char *string);

void linkTreeRight(struct TreeNode * tree1, struct TreeNode * tree2);

void createAssemblerFile(char * assemblerCode);

#endif