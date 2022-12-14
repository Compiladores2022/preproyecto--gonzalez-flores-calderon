#include "../types/symbol.h"
#include "../sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../symbol_list/symbol_list.h"

#ifndef UTILS_H
#define UTILS_H

typedef enum {ADD, SUB, MULT, DIV, MOD, AND, OR, NOT, ASSIG, EQUAL, GREAT, LESS, RETURNVAL, METHDECL, EXTERNMETH, METHCALL, IF, IFELSE, WHILE, NEXTBLOCK, PUSH, JMP, JMPFALSE, JMPTRUE, RET, MAINMETHOD, GLOBALVARIABLE} operations;

char * enumToString(types type);

void printTree(struct TreeNode *tree);

struct TreeNode * createNextTree(struct TreeNode *left, struct TreeNode *right);

struct TreeNode * createNewTree(types symbolType, struct TreeNode *left, struct TreeNode *right, char *operation, int offset, identifierType identifiertype);

struct TreeNode * createNewNodeWithParameters(types symbolType, char * operation, identifierType identifiertype, struct ParameterList * parameters);

struct TreeNode * createNewNode(types symbolType, char * operation, identifierType identifiertype);

int arithmeticOperation(char * operation);

int booleanOperation(char * operation);

char * intToString(int source);

int stringToOperation(char *string);

void linkTreeRight(struct TreeNode * tree1, struct TreeNode * tree2);

void createAssemblerFile(char * assemblerCode);

int checkMain(SymbolList *symbolList);

void addParametersOffset(SymbolList *symbolList, struct TreeNode * body);

struct TreeNode * createNewTreeWithParameters(types symbolType, struct TreeNode *left, struct TreeNode *right, char *operation, int offset, struct ParameterList *parameterList, identifierType identifiertype);

int calculateFrameSpace(struct TreeNode *body);

int foundMaxOffset(struct TreeNode *body, int maxOffset);

void setGlobal(struct TreeNode *declGlobal);

void setParameterListOffsets(SymbolList *symbolList, struct ParameterList *paramList, int maxOffset);

#endif