#include "../main/symbol_list/symbol_list.h"

#include <stdio.h>

Symbol createSymbol(enum types type, char *name, void *value);
int currentLevel(SymbolList *symbolList);

int addOneSymbolAndSearchIt();
int openAndCloseLevel();
int cannotCloseFinalLevel();
int searchFindsSymbolInPreviousLevels();

int main(){
    //total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 4;
    
    addOneSymbolAndSearchIt() ? testsPassed++ : printf("test add one symbol and search it failed\n");
    openAndCloseLevel() ? testsPassed++ : printf("test open and close several levels failed\n");
    cannotCloseFinalLevel() ? testsPassed++ : printf("test cannot close final level failed\n");
    searchFindsSymbolInPreviousLevels() ? testsPassed++ : printf("test search finds symbol in previous levels failed\n");
    

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int addOneSymbolAndSearchIt() {
    SymbolList list;
    list.head = NULL;
    initialize(&list);
    int i = 3;
    Symbol newSymbol = createSymbol(INT, "a", &i);
    insert(&list, &newSymbol);
    return search(&list, &newSymbol);
}

int openAndCloseLevel() {
    SymbolList list;
    list.head = NULL;
    initialize(&list);
    int initialLevel = 1;
    openLevel(&list);
    closeLevel(&list);
    openLevel(&list);
    openLevel(&list);
    closeLevel(&list);
    openLevel(&list);
    closeLevel(&list);
    closeLevel(&list);
    return initialLevel == currentLevel(&list);
}

int cannotCloseFinalLevel() {
    SymbolList list;
    list.head = NULL;
    initialize(&list);
    closeLevel(&list);
    return list.head != NULL && list.head->level == 1;
}

int searchFindsSymbolInPreviousLevels() {
    SymbolList list;
    list.head = NULL;
    initialize(&list);

    int a = 0;
    Symbol symbol1 = createSymbol(BOOL, "a", &a);
    int b = 2;
    Symbol symbol2 = createSymbol(INT, "dl", &b);
    int c = 0;
    Symbol symbol3 = createSymbol(BOOL, "n", &c);
    int d = 15;
    Symbol symbol4 = createSymbol(INT, "i", &d);

    insert(&list, &symbol1);
    insert(&list, &symbol2);
    openLevel(&list);
    insert(&list, &symbol3);
    insert(&list, &symbol4);
    openLevel(&list);

    return search(&list, &symbol2);
}

Symbol createSymbol(enum types type, char *name, void *value) {
    Symbol newSymbol;
    newSymbol.type = type;
    newSymbol.name = name;
    newSymbol.value = value;

    return newSymbol;
}

int currentLevel(SymbolList *symbolList) {
    return symbolList->head->level;
}