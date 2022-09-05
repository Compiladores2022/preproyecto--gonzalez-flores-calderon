#ifndef TYPE_STRUCTS_H
#define TYPE_STRUCTS_H

enum types{INT, BOOL};

typedef struct {
    enum types type;
    char *name;
    void *value;
}Symbol;

static Symbol createSymbol(enum types type, char *name, void *value) {
    Symbol newSymbol;
    newSymbol.type = type;
    newSymbol.name = name;
    newSymbol.value = value;

    return newSymbol;
}

#endif