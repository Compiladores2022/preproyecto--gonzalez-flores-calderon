#include <stdio.h>
#include <stdlib.h>
#include "parameter.h"

Parameter * createParameter(types type, char *id) {
    Parameter * newParameter;

    newParameter = (Parameter *) malloc (sizeof(Parameter));
    if(newParameter == NULL){
        printf("couldn't create parameter, exiting\n");
        exit(EXIT_FAILURE);
    }

    newParameter->type = type;
    newParameter->id = id;

    return newParameter;
}