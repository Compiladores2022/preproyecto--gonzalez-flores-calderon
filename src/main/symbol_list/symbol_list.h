#ifndef SYMBOL_LIST_H
#define SYMBOL_LIST_H

enum types{INT, BOOL};

typedef struct {
    enum types type;
    char *name;
    void *value;
}Symbol;

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