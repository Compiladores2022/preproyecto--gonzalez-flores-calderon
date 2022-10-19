#include "symbol.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>

Symbol * createSymbol(types type, char *name, void *value, int offset) {
    Symbol * newSymbol;

    newSymbol = (Symbol *) malloc (sizeof(Symbol));
    if(newSymbol == NULL){
        printf("couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;

    return newSymbol;
}

void addType(Symbol *symbol, types type) {
    if (symbol->type != UNDEFINED) {
        printf("\033[0;31mError:\033[0m Symbol %s already has type %s setted\n", symbol->name, enumToString(symbol->type));
        exit(0);
    }
    symbol->type = type;
}

void addValue(Symbol *symbol, void *value) {
    if (symbol->value != NULL) {
        printf("\033[0;31mError:\033[0m Symbol %s already has a value setted\n", symbol->name);
        exit(0);
    }
    symbol->value = value;
}