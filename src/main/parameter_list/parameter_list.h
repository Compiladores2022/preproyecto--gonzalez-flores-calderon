#include "../types/symbol.h"
#include "../utils/utils.h"

#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H

struct ParameterNode {
    parameter *info;
    struct parameterNode *next;
};

typedef struct{
    struct parameterNode *head;
}ParameterList;







#endif