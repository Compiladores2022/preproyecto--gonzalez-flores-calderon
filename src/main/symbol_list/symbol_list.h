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

typedef struct{
	struct levelNode *head;
}SymbolList;

void insert(SymbolList *symbolList, Symbol *symbol);

Symbol * search(SymbolList *symbolList, char *name);

Symbol * searchInLevel(struct TableNode *nodeList, char *name);

void printLevel(struct TableNode *nodeList);

void openLevel(SymbolList *symbolList);

void closeLevel(SymbolList *symbolList);

void initialize(SymbolList *symbolList);

#endif
	