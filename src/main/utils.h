#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/types/symbol.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

char * enumToString(types type) {
    switch (type) {
        case TYPEINT: return "INT";

        case TYPEBOOL: return "BOOL";

        default : exit(0);
    }
}

#endif