#ifndef TYPE_STRUCTS_H
#define TYPE_STRUCTS_H

typedef enum {TYPEINT, TYPEBOOL, UNDEFINED, TYPEVOID} types;

typedef struct {
    types type;
    char *name;
    void *value;
    int offset;
}Symbol;

Symbol * createSymbol(types type, char *name, void *value, int offset);

void addType(Symbol *symbol, types type);

void addValue(Symbol *symbol, void *value);

#endif