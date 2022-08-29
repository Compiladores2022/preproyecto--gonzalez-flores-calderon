#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

enum types{INT, BOOL};

struct Symbol {
    enum types type;
    char *name;
    void *value;
}

struct Node {
    struct Symbol info;
    struct Node *next;
}

Node *symbolList

void insert(Node *symbolList, Symbol symbol);

void search(Node *symbolList, char *name);

void pop(Node *symbolList, Node *limit);



#endif