#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char * enumToString(types type) {
    switch (type) {
        case TYPEINT: return "INT";

        case TYPEBOOL: return "BOOL";

        case UNDEFINED: return "UNDEFINED";

        default : exit(0);
    }
}

void printTree(struct TreeNode *tree) {
    char *treePrint = malloc(sizeof(char));
    printTreeInOrder(tree, treePrint);
    printf("\033[0;31mtree in order:\033[0m %s\n", treePrint);
}

struct TreeNode * createNextTree(struct TreeNode *left, struct TreeNode *right) {
    Symbol *s = createSymbol(UNDEFINED, "next", NULL);
    struct TreeNode * newTree = createTree(s, left, right);
    return newTree;
}