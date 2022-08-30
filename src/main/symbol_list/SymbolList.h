#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

enum types{INT, BOOL};

typedef struct {
    enum types type;
    char *name;
    void *value;
    int level;
}Symbol;

struct Node {
    Symbol info;
    struct Node *next;
};

typedef struct{
	struct Node *head;
}SymbolList;

void insert(SymbolList *symbolList, Symbol symbol);

void search(SymbolList *symbolList, char *name);

void pop(SymbolList *symbolList, struct Node *limit);

//void openLevel(SymbolList *SymbolList, int level);

//void closeLevel(SymbolList *SymbolList, int level);

#endif