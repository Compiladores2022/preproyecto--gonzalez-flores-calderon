#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"

struct Parameter * createParameter(types type, char *id) {
    struct Parameter * newParameter;

    newParameter = (struct Parameter *) malloc (sizeof(struct Parameter));
    if(newParameter == NULL){
        printf("couldn't create parameter, exiting\n");
        exit(EXIT_FAILURE);
    }

    newParameter->type = type;
    newParameter->id = id;

    return newParameter;
}