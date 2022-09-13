#ifndef TYPE_STRUCTS_H
#define TYPE_STRUCTS_H

typedef enum {TYPEINT, TYPEBOOL} types;

typedef struct {
    types type;
    char *name;
    void *value;
}Symbol;

static Symbol createSymbol(types type, char *name, void *value) {
    Symbol newSymbol;
    newSymbol.type = type;
    newSymbol.name = name;
    newSymbol.value = value;

    return newSymbol;
}

//it's better to just use the old function and pass it null, cause if we want to get value in this new function segmentation 
//fault will be prompt cause it has a random memory direction
static Symbol createSymbolNoValue(types type, char *name) {
    Symbol newSymbol;
    newSymbol.type = type;
    newSymbol.name = name;

    return newSymbol;
}

#endif