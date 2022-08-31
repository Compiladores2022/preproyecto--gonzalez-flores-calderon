#include "SymbolList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nameConflict(SymbolList *symbolList, Symbol *symbol);

int main(){
    return 0;
}

struct Node * CrateNode(){
    struct Node *newNode;

    newNode = (struct Node *) malloc (sizeof(struct Node));
    if(newNode == NULL){
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

void insert(SymbolList *symbolList, Symbol *symbol, int increaseLevel){
    struct Node *newNode;

    if (increaseLevel != 1 && nameConflict(symbolList, symbol) == 1)
        exit(0); //name already present
    
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
        if (strcmp(listPointer->info->name, symbol->name))
            return 1;
        listPointer = listPointer->next;
    }
    return 0;
}

int search(SymbolList *symbolList, char *name) {

    if(symbolList == NULL){
        exit (0);
    }
    while (symbolList->head != NULL){
        if(strcmp(symbolList->head->info->name, name) == 0){
            return 1;
        }
        symbolList->head = symbolList->head->next;
    }
    return 0;
}

void openLevel(SymbolList *SymbolList, int level) {

}

void closeLevel(SymbolList *SymbolList, int level) {

}

// 1 true, 0 false