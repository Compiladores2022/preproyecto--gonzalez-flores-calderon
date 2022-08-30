#include "SymbolList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void insert(SymbolList *symbolList, Symbol symbol){

    struct Node *newNode;

    newNode = CrateNode();
    newNode->info = symbol;
    newNode->next = symbolList->head->next;
    symbolList->head = newNode;
}




