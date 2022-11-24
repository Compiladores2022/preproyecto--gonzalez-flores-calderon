#include "symbol.h"
#include "../utils/utils.h"
#include "../types/enumeration.h"
#include <stdio.h>
#include <stdlib.h>

Symbol * createSymbol(types type, char *name, void *value, int offset) {
    Symbol * newSymbol;

    newSymbol = (Symbol *) malloc (sizeof(Symbol));
    if(newSymbol == NULL){
        printf("-> ERROR: Couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    struct ParameterList *list = NULL;
    
    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;
    newSymbol->parameterList = list;
    newSymbol->it = TYPELESS;
    newSymbol->isGlobal = NO;
    return newSymbol;
}

Symbol * createSymbolWithParameter(types type, char *name, void *value, int offset, struct ParameterList *parameterList){
    Symbol * newSymbol;

    newSymbol = (Symbol *) malloc (sizeof(Symbol));
    if(newSymbol == NULL){
        printf("-> ERROR: Couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;
    newSymbol->it = TYPELESS;
    newSymbol->isGlobal = NO;
    
    newSymbol->parameterList = parameterList;
    
    return newSymbol;
}

Symbol * createSymbolNoParameters(types type, char *name, void *value, int offset, identifierType identifierType){
        
    Symbol * newSymbol = (Symbol *) malloc (sizeof(Symbol));
    
    if(newSymbol == NULL){
        printf("-> ERROR: Couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    struct ParameterList *list;

    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;
    newSymbol->parameterList = list;
    newSymbol->it = identifierType;
    newSymbol->isGlobal = NO;
    
    return newSymbol;
}

Symbol * createSymbolFull(types type, char *name, void *value, int offset, struct ParameterList *parameterList, identifierType identifierType){
    
    Symbol * newSymbol = (Symbol *) malloc (sizeof(Symbol));
    
    if(newSymbol == NULL){
        printf("-> ERROR: Couldn't create symbol, exiting\n");
        exit(EXIT_FAILURE);
    }

    newSymbol->type = type;
    newSymbol->name = name;
    newSymbol->value = value;
    newSymbol->offset = offset;
    newSymbol->parameterList = (struct ParameterList*) malloc (sizeof(struct ParameterList*));
    newSymbol->parameterList = parameterList;
    newSymbol->it = identifierType;
    newSymbol->isGlobal = NO;
    
    return newSymbol;
}

void addType(Symbol *symbol, types type) {
    if (symbol->type != UNDEFINED) {
        printf("\033[0;31m-> ERROR: \033[0m Symbol %s already has type %s setted\n", symbol->name, enumToString(symbol->type));
        exit(0);
    }
    symbol->type = type;
}

void addValue(Symbol *symbol, void *value) {
    if (symbol->value != NULL) {
        printf("\033[0;31m-> ERROR: \033[0m Symbol %s already has a value setted\n", symbol->name);
        exit(0);
    }
    symbol->value = value;
}

void addFrameSpace(Symbol *symbol, int frameSpace){
    if(symbol->frameSpace != 0){
        printf("\033[0;31m-> ERROR: \033[0m Symbol %s already has a frame space setted\n", symbol->name);
        exit(0);
    }
    if(frameSpace % 2 != 0){
        frameSpace++;
    }
    symbol->frameSpace = frameSpace;
}

void addIdentifierType(Symbol *symbol, identifierType identifierType){
    if(symbol->it != TYPELESS){
        printf("\033[0;31m-> ERROR: \033[0m Symbol %s already has a identifier type setted\n", symbol->name);
        exit(0);
    }
    symbol->it = identifierType;
}

void replaceIdentifierType(Symbol *symbol, identifierType identifiertype){
    symbol->it = identifiertype;
}

void replaceIsGlobal(Symbol *symbol, Global isglobal){
    symbol->isGlobal = isglobal;
}

void addParemeters(Symbol *symbol, struct ParameterList *parameters){
    if(symbol->parameterList != NULL){
        printf("\033[0;31m-> ERROR: \033[0m Symbol %s already has a parameters setted\n", symbol->name);
        exit(0);
    }
    symbol->parameterList = parameters;
}
