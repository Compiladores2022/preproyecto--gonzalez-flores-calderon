#include "SymbolList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nameConflict(SymbolList *symbolList, Symbol *symbol);

int main(){
    return 0;
}

void initialize(SymbolList *SymbolList) {

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

struct Node * CrateLevelNode() {
    struct levelNode *newNode;

    newNode = (struct levelNode *) malloc (sizeof(struct levelNode));
    if(newNode == NULL){
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

void insert(SymbolList *symbolList, Symbol *symbol, int increaseLevel) {
    struct Node *newNode;

    if (increaseLevel != 1 && nameConflict(symbolList, symbol) == 1){
        exit(0); //name already present
    }    

    newNode = CrateNode();
    newNode->info = symbol;
    newNode->next = symbolList->head;
    symbolList->head = newNode;
}

//checks if the given symbol is already present in the current level of the symbolList
int nameConflict(SymbolList *symbolList, Symbol *symbol) {
    int currentLevel = symbolList->head->info->level;
    struct Node *listPointer = symbolList->head;

    while (listPointer != NULL && listPointer->info->level != currentLevel) {
        if (strcmp(listPointer->info->name, symbol->name)){
            return 1;
        }
        listPointer = listPointer->next;
    }
    return 0;
}

int search(SymbolList *symbolList, char *name) {

    if(symbolList == NULL){
        exit(EXIT_FAILURE);
    }
    
    while (symbolList->head != NULL){
        if(nameConflict(symbolList, name) == 1){
            return 1;
        }
        symbolList->head = symbolList->head->next;
    }
    return 0;
}

//Create new level
void openLevel(SymbolList *SymbolList) {
    struct levelNode *newLevelNode;

    newLevelNode = CrateLevelNode();
    newLevelNode->next = SymbolList->head;
    SymbolList->head = newLevelNode;
}

//Delete current level
void closeLevel(SymbolList *SymbolList) {
    
    struct levelNode *ln; //levelNode aux to free level
    struct Node *n; //node aux to free list
    
    while (SymbolList->head->levelSymbols != NULL){
        n = SymbolList->head->levelSymbols;
        SymbolList->head->levelSymbols = SymbolList->head->levelSymbols->next;
        free(n);
    }

    ln = SymbolList->head;
    SymbolList->head = SymbolList->head->next;
    free(ln);
}

// 1 true, 0 false