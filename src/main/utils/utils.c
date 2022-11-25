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

        default : 
            printf("\033[0;31m-> ERROR: :\033[0m Couldn't match type %d to any of the known types\n", type);
            exit(0);
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

struct TreeNode * createNewNode(types symbolType, char * operation, identifierType identifiertype){
    
    Symbol *s = createSymbol(symbolType, operation, NULL, 0);
    addIdentifierType(s, identifiertype);
    struct TreeNode * newNode = createNode(s);
    return newNode;
}

struct TreeNode * createNewNodeWithParameters(types symbolType, char * operation, identifierType identifiertype, struct ParameterList * parameters){
    
    Symbol *s = createSymbolWithParameter(symbolType, operation, NULL, 0, parameters);
    addIdentifierType(s, identifiertype);
    struct TreeNode * newNode = createNode(s);
    return newNode;
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
    else if (strcmp(string, "return") == 0 || strcmp(string, "RETURNVAL") == 0){
        return RETURNVAL;
    }
    else if (strcmp(string, "methoddecl") == 0 || strcmp(string, "METHDECL") == 0){
        return METHDECL;
    }
    else if (strcmp(string, "methodcall") == 0 || strcmp(string, "METHCALL") == 0){
        return METHCALL;
    }
    else if (strcmp(string, "externmethod") == 0){
        return EXTERNMETH;
    }
    else if (strcmp(string, "if") == 0){
        return IF;
    }
    else if (strcmp(string, "ifelse") == 0){
        return IFELSE;
    }
    else if (strcmp(string, "while") == 0){
        return WHILE;
    }
    else if (strcmp(string, "next") == 0){
        return NEXTBLOCK;
    }
    else if (strcmp(string, "PUSH") == 0){
        return PUSH;
    }
    else if (strcmp(string, "JMP") == 0){
        return JMP;
    }
    else if (strcmp(string, "JMPFALSE") == 0){
        return JMPFALSE;
    }
    else if (strcmp(string, "JMPTRUE") == 0){
        return JMPTRUE;
    }
    else if (strcmp(string, "RET") == 0){
        return RET;
    }
    else if (strcmp(string, "MAINMETHOD") == 0){
        return MAINMETHOD;
    }
    else if (strcmp(string, "VARIABLEGLOGAL") == 0){
        return VARIABLEGLOBAL;
    }
    else {
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
        printf("\033[0;31m-> ERROR:\033[0m Main not defined\n");
        exit(0);
    }
    return 0;
}

void addParametersOffset(SymbolList *symbolList, struct TreeNode *body) {
    if(body == NULL){
        return;
    }
    addParametersOffset(symbolList, body->left);
    Symbol * foundParameter = searchInLevel(symbolList->head->levelSymbols, body->info->name);
    if (foundParameter != NULL) {
        body->info->offset = foundParameter->offset;
    }
    addParametersOffset(symbolList, body->right);
}

int foundMaxOffset(struct TreeNode *body, int maxOffset){
    if(body == NULL){
        return maxOffset;
    }

    int maxOffsetleft = foundMaxOffset(body->left, maxOffset);
    if(maxOffsetleft > maxOffset){
        maxOffset = maxOffsetleft;
    }

    if(body->info->offset > maxOffset){
        maxOffset = body->info->offset;
    }
    
    int maxOffsetright = foundMaxOffset(body->right, maxOffset);
    if(maxOffsetright > maxOffset){
        maxOffset = maxOffsetright;
    }
}

int calculateFrameSpace(struct TreeNode *body){
    return foundMaxOffset(body, 0) / 8;
}

void setGlobal(struct TreeNode *declGlobal){

    if(declGlobal->left != NULL){
        declGlobal->left->info->isGlobal = YES;
        if(declGlobal->left->left != NULL){
            declGlobal->left->left->info->isGlobal = YES;
        }
    }
    if(declGlobal->right != NULL){
        setGlobal(declGlobal->right);
    }

}

void setParameterListOffsets(SymbolList *symbolList, struct ParameterList *paramList, int maxOffset) {
    int size = sizeParameter(paramList->head);
    
    struct ParameterNode * currentNode = paramList->head;
    int offset = 16;
    
    for (int i = 1; i <= size - 6; i++) {   //add offset for parameters greater than 6
        Symbol * parameter = searchInLevel(symbolList->head->levelSymbols, currentNode->info->id);
        parameter->offset = -offset;
        offset += 8;
        currentNode = currentNode->next;
    }

    if (size > 6) {
        size = 6;
    }

    offset = maxOffset * 8 + 8;
    for (int i = 1; i <= size; i++) {    //add offset for the first 6 parameters
        Symbol * parameter = searchInLevel(symbolList->head->levelSymbols, currentNode->info->id);
        parameter->offset = offset;
        printf("symbol %s tiene offset %d\n", parameter->name, parameter->offset);
        offset += 8;
        currentNode = currentNode->next;
    }
}