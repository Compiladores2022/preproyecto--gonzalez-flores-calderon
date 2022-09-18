#ifndef TYPE_STRUCTS_H
#define TYPE_STRUCTS_H

typedef enum {TYPEINT, TYPEBOOL, UNDEFINED} types;

typedef struct {
    types type;
    char *name;
    void *value;
}Symbol;

Symbol * createSymbol(types type, char *name, void *value);

#endif