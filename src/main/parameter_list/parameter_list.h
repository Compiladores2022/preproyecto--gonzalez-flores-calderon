#include "../types/parameter.h"

#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H

struct ParameterNode {
    struct Parameter *info;
    struct ParameterNode *next;
};

struct ParameterList{
    struct ParameterNode *head;
};

void initializeP(struct ParameterList *parameterList);

void insertParameter(struct ParameterList *list, struct Parameter *parameter);

int sizeParameter(struct ParameterNode *list);

#endif  