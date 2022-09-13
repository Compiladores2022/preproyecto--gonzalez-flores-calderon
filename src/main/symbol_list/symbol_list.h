#include "../types/symbol.h"

#ifndef SYMBOL_LIST_H
#define SYMBOL_LIST_H

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

Symbol * search(SymbolList *symbolList, char *name);

void pop(SymbolList *symbolList, struct Node *limit);

void openLevel(SymbolList *symbolList);

void closeLevel(SymbolList *symbolList);

void initialize(SymbolList *symbolList);

#endif
	