#include "symbol_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchInLevel(struct Node *nodeList, Symbol *symbol);

void initialize(SymbolList *SymbolList) {
    struct levelNode *ln; //levelNode aux to free level
    struct Node *n; //node aux to free list
    
    while(SymbolList->head != NULL){
        while (SymbolList->head->levelSymbols != NULL){
            n = SymbolList->head->levelSymbols;
            SymbolList->head->levelSymbols = SymbolList->head->levelSymbols->next;
            free(n);
        }

        ln = SymbolList->head;
        SymbolList->head = SymbolList->head->next;
        free(ln);
    }

    //Doubtful
    openLevel(SymbolList); 
}

struct Node * CrateNode() {
    struct Node *newNode;

    newNode = (struct Node *) malloc (sizeof(struct Node));
    if(newNode == NULL){
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
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

void insert(SymbolList *symbolList, Symbol *symbol) {
    struct Node *newNode;
    if (searchInLevel(symbolList->head->levelSymbols, symbol) == 1){
        exit(0); //name already present
    }    

    newNode = CrateNode();
    newNode->info = symbol;
    newNode->next = symbolList->head->levelSymbols;
    symbolList->head->levelSymbols = newNode;
}

//checks if the given symbol is already present in the current level of the symbolList
int searchInLevel(struct Node *nodeList, Symbol *symbol) {
    struct Node *listPointer = nodeList;

    while (listPointer != NULL) {
        if (strcmp(listPointer->info->name, symbol->name) == 0){
            return 1;
        }
        listPointer = listPointer->next;
    }
    return 0;
}

int search(SymbolList *symbolList, Symbol *symbol) {
    if(symbolList == NULL){
        exit(EXIT_FAILURE);
    }

    struct levelNode *ln = symbolList->head;
    
    while (ln != NULL){
        if(searchInLevel(ln->levelSymbols, symbol)){
            return 1;
        }
        ln = ln->next;
    }
    return 0;
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
    struct Node *n; //node aux to free list
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
