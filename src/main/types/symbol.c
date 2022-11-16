#include "symbol.h"
#include "../utils/utils.h"
#include "../types/enumeration.h"
#include <stdio.h>
#include <stdlib.h>

Symbol * createSymbol(types type, char *name, void *value, int offset) {
    Symbol * newSymbol;

    newSymbol = (Symbol *) malloc (sizeof(Symbol));
    if(newSymbol == NULL){
        printf("couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    struct ParameterList *list;
    
    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;
    newSymbol->parameterList = list;
    newSymbol->it = TYPELESS;
    return newSymbol;
}

Symbol * createSymbolWithParameter(types type, char *name, void *value, int offset, struct ParameterList *parameterList){
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
    newSymbol->it = TYPELESS;
    
    newSymbol->parameterList = parameterList;
    
    return newSymbol;
}

Symbol * createSymbolNoParameters(types type, char *name, void *value, int offset, identifierType identifierType){
        
    Symbol * newSymbol = (Symbol *) malloc (sizeof(Symbol));
    
    if(newSymbol == NULL){
        printf("couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    struct ParameterList *list;

    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;
    newSymbol->parameterList = list;
    newSymbol->it = identifierType;
    
    return newSymbol;
}

Symbol * createSymbolFull(types type, char *name, void *value, int offset, struct ParameterList *parameterList, identifierType identifierType){
    
    Symbol * newSymbol = (Symbol *) malloc (sizeof(Symbol));
    
    if(newSymbol == NULL){
        printf("couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;
    newSymbol->parameterList = parameterList;
    newSymbol->it = identifierType;
    
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

void addIdentifierType(Symbol *symbol, identifierType identifierType){
    if(symbol->it != TYPELESS){
        printf("\033[0;31mError:\033[0m Symbol %s already has a identifier type setted\n", symbol->name);
        exit(0);
    }
    symbol->it = identifierType;
}

void replaceIdentifierType(Symbol *symbol, identifierType identifiertype){
    symbol->it = identifiertype;
}

void addParemeters(Symbol *symbol, struct ParameterList *parameters){
    if(symbol->parameterList != NULL){
        printf("\033[0;31mError:\033[0m Symbol %s already has a parameters setted\n", symbol->name);
        exit(0);
    }
    symbol->parameterList = parameters;
}
