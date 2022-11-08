#include "../types/parameter.h"

#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H

struct ParameterNode {
    Parameter *info;
    struct ParameterNode *next;
};

typedef struct{
    struct ParameterNode *head;
}ParameterList;

void initializeP(ParameterList *parameterList);

void insertParameter(ParameterList *list, Parameter *parameter);

#endif  