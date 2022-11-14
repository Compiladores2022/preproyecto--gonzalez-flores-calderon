#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/enumeration.h"
#include "../parameter_list/parameter_list.h"
#include "../symbol_list/symbol_list.h"

char * enumToString(types type) {
    switch (type) {
        case TYPEINT: return "INT";

        case TYPEBOOL: return "BOOL";

        case UNDEFINED: return "UNDEFINED";

        case TYPEVOID: return "VOID";

        default : exit(0);
    }
}

void printTree(struct TreeNode *tree) {
    printf("\033[0;32mtree in order:\033[0m");
    printTreeInOrder(tree);
    printf("\n");
}

struct TreeNode * createNextTree(struct TreeNode *left, struct TreeNode *right) {
    Symbol *s = createSymbol(UNDEFINED, "next", NULL, 0);
    struct TreeNode * newTree = createTree(s, left, right);
    return newTree;
}

struct TreeNode * createNewTree(types symbolType, struct TreeNode *left, struct TreeNode *right, char *operation, int offset, identifierType identifiertype) {
    Symbol *s = createSymbol(symbolType, operation, NULL, offset);
    addIdentifierType(s, identifiertype);
    struct TreeNode * newTree = createTree(s, left, right);
    return newTree;
}

struct TreeNode * createNewTreeWithParameters(types symbolType, struct TreeNode *left, struct TreeNode *right, char *operation, int offset, struct ParameterList *parameterList, identifierType identifiertype) {
    Symbol *s = createSymbolWithParameter(symbolType, operation, NULL, offset, parameterList);
    addIdentifierType(s, identifiertype);   
    struct TreeNode * newTree = createTree(s, left, right);
    return newTree;
}

int arithmeticOperation(char * operation) {
    return !(strcmp(operation, "+") && 
                strcmp(operation, "-") && 
                strcmp(operation, "*") && 
                strcmp(operation, "/") && 
                strcmp(operation, "%"));
}

int booleanOperation(char * operation) {
    return !(strcmp(operation, "&&") && 
                strcmp(operation, "||") && 
                strcmp(operation, "!") &&
                strcmp(operation, "<") &&
                strcmp(operation, ">"));
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
    else if (strcmp(string, "/") == 0 || strcmp(string, "DIV") == 0){
        return DIV;
    }
    else if (strcmp(string, "%") == 0 || strcmp(string, "MOD") == 0){
        return MOD;
    }
    else if (strcmp(string, "&&") == 0 || strcmp(string, "AND") == 0){
        return AND; 
    }
    else if (strcmp(string, "||") == 0 || strcmp(string, "OR") == 0){
        return OR; 
    }
    else if (strcmp(string, "!") == 0 || strcmp(string, "NOT") == 0){
        return NOT; 
    }
    else if (strcmp(string, "=") == 0 || strcmp(string, "ASSIG") == 0){
        return ASSIG; 
    }
    else if (strcmp(string, "==") == 0 || strcmp(string, "EQUAL") == 0){
        return EQUAL; 
    }
    else if (strcmp(string, "<") == 0 || strcmp(string, "GREAT") == 0){
        return GREAT; 
    }
    else if (strcmp(string, ">") == 0 || strcmp(string, "LESS") == 0){
        return LESS; 
    }
    else if (strcmp(string, "return") == 0 || strcmp(string, "RET") == 0){
        return RET; 
    }
    else if (strcmp(string, "methoddecl") == 0 || strcmp(string, "METHDECL") == 0){
        return METHDECL; 
    }
    else if (strcmp(string, "methodcall") == 0 || strcmp(string, "METHCALL") == 0){
        return METHCALL; 
    }
    else if (strcmp(string, "if") == 0 || strcmp(string, "IF") == 0){
        return IF; 
    }
    else if (strcmp(string, "ifelse") == 0 || strcmp(string, "IFELSE") == 0){
        return IFELSE; 
    }
    else if (strcmp(string, "while") == 0 || strcmp(string, "WHILE") == 0){
        return WHILE; 
    }
    else if (strcmp(string, "PUSH") == 0){
        return PUSH; 
    }else {
        return -1;
    }
}

void linkTreeRight(struct TreeNode * tree1, struct TreeNode * tree2){

    if(tree1->right == NULL){
        tree1->right = tree2;
    } else {
        linkTreeRight(tree1->right, tree2);
    }

}

void createAssemblerFile(char * assemblerCode){

    FILE *program;

    program = fopen("assembler_generated/program.s", "w");
    fputs(assemblerCode, program);

    fclose(program);
}

int checkMain(SymbolList *symbolList){
    Symbol *example = search(symbolList, "main");
    if(example == NULL){
        printf("Main not defined\n");
        exit(0);
    }
    return 0;
}