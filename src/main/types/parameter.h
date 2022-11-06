#include "enumeration.h"

#ifndef PARAMETER_H
#define PARAMETER_H

typedef struct{
    types type;
    char* id;
}Parameter;

Parameter * createParameter(types type, char *id);

#endif