#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char * enumToString(types type) {
    switch (type) {
        case TYPEINT: return "INT";

        case TYPEBOOL: return "BOOL";

        default : exit(0);
    }
}