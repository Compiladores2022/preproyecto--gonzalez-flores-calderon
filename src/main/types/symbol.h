#include "../parameter_list/parameter_list.h"
#include "enumeration.h"

#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct {
    types type; //return type
    char *name;
    void *value;
    int offset;
    struct ParameterList *parameterList;
    identifierType it;
    int frameSpace;
}Symbol;

Symbol * createSymbol(types type, char *name, void *value, int offset);

Symbol * createSymbolWithParameter(types type, char *name, void *value, int offset, struct ParameterList *parameterList);

Symbol * createSymbolFull(types type, char *name, void *value, int offset, struct ParameterList *parameterList, identifierType identifierType);

Symbol * createSymbolNoParameters(types type, char *name, void *value, int offset, identifierType identifierType);

void addIdentifierType(Symbol *symbol, identifierType identifierType);

void addType(Symbol *symbol, types type);

void addValue(Symbol *symbol, void *value);

void replaceIdentifierType(Symbol *symbol, identifierType identifierType);

void addParemeters(Symbol *symbol, struct ParameterList *parameters);

void addFrameSpace(Symbol *symbol, int frameSpace);

#endif