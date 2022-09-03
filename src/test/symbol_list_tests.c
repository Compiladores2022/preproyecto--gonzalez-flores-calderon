#include "../main/symbol_list/symbol_list.h"

#include <stdio.h>

Symbol createSymbol(enum types type, char *name, void *value);

int addOneSymbolAndSearchIt();

int main(){
    //total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 1;
    
    //add one symbol and search it
    if (addOneSymbolAndSearchIt())
        testsPassed++;
    else
        printf("test add one symbol and search it failed\n");
    

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int addOneSymbolAndSearchIt() {
    SymbolList list1;
    list1.head = NULL;
    initialize(&list1);
    int i = 3;
    Symbol newSymbol = createSymbol(INT, "a", &i);
    insert(&list1, &newSymbol);
    return search(&list1, &newSymbol);
}

Symbol createSymbol(enum types type, char *name, void *value) {
    Symbol newSymbol;
    newSymbol.type = type;
    newSymbol.name = name;
    newSymbol.value = value;

    return newSymbol;
}
