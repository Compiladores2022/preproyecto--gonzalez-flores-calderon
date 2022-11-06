#include "../parameter_list/parameter_list.h"

#ifndef SYMBOL_H
#define SYMBOL_H

typedef enum {TYPEINT, TYPEBOOL, UNDEFINED, TYPEVOID} types;

typedef struct {
    types type;
    char *name;
    void *value;
    int offset;
    ParameterList parameterList;
}Symbol;

Symbol * createSymbol(types type, char *name, void *value, int offset);

Symbol * createSymbolWithParameter(types type, char *name, void *value, int offset, parameterList *parameterList);

void addType(Symbol *symbol, types type);

void addValue(Symbol *symbol, void *value);

#endif