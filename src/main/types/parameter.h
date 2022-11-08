#include "enumeration.h"

#ifndef PARAMETER_H
#define PARAMETER_H

struct Parameter{
    types type;
    char* id;
};

struct Parameter * createParameter(types type, char *id);

#endif