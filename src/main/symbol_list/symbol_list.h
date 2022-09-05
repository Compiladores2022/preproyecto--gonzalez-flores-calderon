#include "../types/type_structs.h"

#ifndef SYMBOL_LIST_H
#define SYMBOL_LIST_H

enum types{INT, BOOL};

struct Node {
    Symbol *info;
    struct Node *next;
};

struct levelNode {
    int level;
    struct levelNode *next;
    struct Node *levelSymbols;
};

typedef struct{
	struct levelNode *head;
}SymbolList;

void insert(SymbolList *symbolList, Symbol *symbol);

int search(SymbolList *symbolList, Symbol *name);

void pop(SymbolList *symbolList, struct Node *limit);

void openLevel(SymbolList *SymbolList);

void closeLevel(SymbolList *SymbolList);

void initialize(SymbolList *SymbolList);

#endif