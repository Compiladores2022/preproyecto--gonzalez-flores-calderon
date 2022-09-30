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

//Only used to check operation to intermediate code generator 
int stringToInt(char *string) {

    if(strcmp(string, "+")){
        return 0;
    }
    else if (strcmp(string, "-")){
        return 1; 
    }
    else if (strcmp(string, "*")){
        return 2;
    }
    else if (strcmp(string, "&&")){
        return 3; 
    }
    else if (strcmp(string, "||")){
        return 4; 
    }
    else if (strcmp(string, "=")){
        return 5; 
    }
    else if (strcmp(string, "return")){
        return 6; 
    }    

    return -1;
}

struct TreeNode * linkTreeRight(struct TreeNode * tree1, struct TreeNode * tree2){

    if(tree1->right == NULL){
        tree1->right = tree2;
        return tree1;
    }
    
    linkTreeRight(tree1->right, tree2);
}
