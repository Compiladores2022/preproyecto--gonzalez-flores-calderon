#ifndef TYPE_STRUCTS_H
#define TYPE_STRUCTS_H

enum types{INT, BOOL};

typedef struct {
    enum types type;
    char *name;
    void *value;
}Symbol;


#endif