#include "symbol.h"

#include <stdio.h>
#include <stdlib.h>

Symbol * createSymbol(types type, char *name, void *value) {
    Symbol * newSymbol;

    newSymbol = (Symbol *) malloc (sizeof(Symbol));
    if(newSymbol == NULL){
        printf("couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;

    return newSymbol;
}