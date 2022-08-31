#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

enum types{INT, BOOL};
enum operators{PLUS, SUBSTRACT, AND, OR};

struct Symbol {
    enum types type;
    int level;
    char *name;
    void *value;
};

struct Node {
    struct Symbol info;
    struct Node *left;
    enum operators operator;
    struct Node *right;
};

struct SintacticAnalysisTree {
    Node *head;
};


#endif