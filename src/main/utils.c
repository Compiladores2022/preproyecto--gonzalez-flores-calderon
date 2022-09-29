#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    Symbol *s = createSymbol(UNDEFINED, "next", NULL, 0);
    struct TreeNode * newTree = createTree(s, left, right);
    return newTree;
}

struct TreeNode * createNewTree(types symbolType, struct TreeNode *left, struct TreeNode *right, char *operation, int offset) {
    Symbol *s = createSymbol(symbolType, operation, NULL, offset);
    struct TreeNode * newTree = createTree(s, left, right);
    return newTree;
}

int arithmeticOperation(char * operation) {
    return !(strcmp(operation, "+") && strcmp(operation, "-") && strcmp(operation, "*"));
}

int booleanOperation(char * operation) {
    return !(strcmp(operation, "&&") && strcmp(operation, "||"));
}

char * intToString(int source) {
    char *dest = malloc(sizeof(char *));
    sprintf(dest, "%d", source);

    return dest;
}

//Only used to check operation to intermediate code generator 
int stringToOperation(char *string) {
    if(strcmp(string, "+")){
        return ADD;
    }
    else if (strcmp(string, "-")){
        return SUB; 
    }
    else if (strcmp(string, "*")){
        return MULT;
    }
    else if (strcmp(string, "&&")){
        return AND; 
    }
    else if (strcmp(string, "||")){
        return OR; 
    }
    else if (strcmp(string, "=")){
        return ASSIG; 
    }
    else if (strcmp(string, "return")){
        return RET; 
    }    

    return -1;
}