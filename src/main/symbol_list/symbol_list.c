#include "symbol_list.h"
#include "../types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol * searchInLevel(struct TableNode *nodeList, char *name);

void initialize(SymbolList *symbolList) {
    symbolList->head = NULL;
    openLevel(symbolList); 
}

struct TableNode * CrateNode() {
    struct TableNode *newNode;

    newNode = (struct TableNode *) malloc (sizeof(struct TableNode));
    if(newNode == NULL){
        printf("couldn't create table node, exiting\n");
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

struct levelNode * CrateLevelNode() {
    struct levelNode *newNode;

    newNode = (struct levelNode *) malloc (sizeof(struct levelNode));
    if(newNode == NULL){
        printf("couldn't create level node, exiting\n");
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

void insert(SymbolList *symbolList, Symbol *symbol) {
    struct TableNode *newNode;
    if (searchInLevel(symbolList->head->levelSymbols, symbol->name) != NULL){
        printf("Cannot add symbol %s because is already present in this level\n", symbol->name);
        exit(0); //name already present
    }    

    newNode = CrateNode();
    newNode->info = symbol;
    newNode->next = symbolList->head->levelSymbols;
    symbolList->head->levelSymbols = newNode;
}

/*
    checks if the given name is already present in the current level of the symbolList
    if found returns the reference to it, otherwise returns null
*/
Symbol * searchInLevel(struct TableNode *nodeList, char *name) {
    struct TableNode *listPointer = nodeList;

    while (listPointer != NULL) {
        if (strcmp(listPointer->info->name, name) == 0){
            return listPointer->info;
        }
        listPointer = listPointer->next;
    }
    return NULL;
}

Symbol * search(SymbolList *symbolList, char *name) {
    if(symbolList == NULL){
        exit(EXIT_FAILURE);
    }

    struct levelNode *ln = symbolList->head;
    while (ln != NULL){
        Symbol *foundSymbol = searchInLevel(ln->levelSymbols, name);
        if(foundSymbol != NULL){
            return foundSymbol;
        }
        ln = ln->next;
    }
    return NULL;
}

void printLevel(struct TableNode *nodeList) {
    printf("printeando todo el nivel:\n");
    struct TableNode *listPointer = nodeList;

    while (listPointer != NULL) {
        printf("item: %s\n", listPointer->info->name);
        listPointer = listPointer->next;
    }
}

//Create new level
void openLevel(SymbolList *symbolList) {
    struct levelNode *newLevelNode;

    newLevelNode = CrateLevelNode();
    newLevelNode->next = symbolList->head;
    symbolList->head = newLevelNode;

    if (newLevelNode->next != NULL) {
        newLevelNode->level = newLevelNode->next->level + 1;
    } else {
        newLevelNode->level = 1;
    }
}

//Delete current level
void closeLevel(SymbolList *symbolList) {
    struct TableNode *n; //node aux to free list
    while (symbolList->head->levelSymbols != NULL){
        n = symbolList->head->levelSymbols;
        symbolList->head->levelSymbols = symbolList->head->levelSymbols->next;
        free(n);
    }
    
    if (symbolList->head->level != 1) {
        struct levelNode *ln = symbolList->head;; //levelNode aux to free level
        symbolList->head = symbolList->head->next;
        free(ln);
    }
}
