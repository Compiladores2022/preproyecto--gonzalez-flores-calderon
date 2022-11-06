#include "../types/symbol.h"

#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct{
    types type;
    char* id;
}Parameter;

Parameter * createParameter(types type, char * id);

#endif