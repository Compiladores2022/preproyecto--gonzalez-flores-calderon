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

int digitLength(int number) {
    int temp = number, length = 1;
    if (temp < 0) temp *= -1;
    temp -= temp % 10; //taking out the remainder
    
    while (temp >= 10) {
        temp /= 10;
        length += 1;
    }

    return length;
}

char * intToString(int source) {
    int length = digitLength(source);
    char *dest = malloc(length * sizeof(char *));
    sprintf(dest, "%d", source);

    return dest;
}

//Only used to check operation to intermediate code generator 
int stringToOperation(char *string) {
    if(strcmp(string, "+") == 0 || strcmp(string, "ADD") == 0){
        return ADD;
    }
    else if (strcmp(string, "-") == 0 || strcmp(string, "SUB") == 0){
        return SUB; 
    }
    else if (strcmp(string, "*") == 0 || strcmp(string, "MULT") == 0){
        return MULT;
    }
    else if (strcmp(string, "&&") == 0 || strcmp(string, "AND") == 0){
        return AND; 
    }
    else if (strcmp(string, "||") == 0 || strcmp(string, "OR") == 0){
        return OR; 
    }
    else if (strcmp(string, "=") == 0 || strcmp(string, "ASSIG") == 0){
        return ASSIG; 
    }
    else if (strcmp(string, "return") == 0 || strcmp(string, "RET") == 0){
        return RET; 
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
