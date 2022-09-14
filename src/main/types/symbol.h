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

#endif