#include "symbol_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nameConflict(SymbolList *symbolList, Symbol *symbol);

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


// 1 true, 0 false