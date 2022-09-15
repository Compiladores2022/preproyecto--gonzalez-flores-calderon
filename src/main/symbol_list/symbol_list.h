#include "../types/symbol.h"

#ifndef SYMBOL_LIST_H
#define SYMBOL_LIST_H

struct TableNode {
    Symbol *info;
    struct TableNode *next;
};

struct levelNode {
    int level;
    struct levelNode *next;
    struct TableNode *levelSymbols;
};

struct SymbolList{
	struct levelNode *head;
};

void insert(struct SymbolList *symbolList, Symbol *symbol);

Symbol * search(struct SymbolList *symbolList, char *name);

void openLevel(struct SymbolList *symbolList);

void closeLevel(struct SymbolList *symbolList);

void initialize(struct SymbolList *symbolList);

#endif
	