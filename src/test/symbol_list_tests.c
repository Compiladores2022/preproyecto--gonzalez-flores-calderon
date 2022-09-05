#include "../main/symbol_list/symbol_list.h"

#include <stdio.h>

int currentLevel(SymbolList *symbolList);

int addOneSymbolAndSearchIt();
int openAndCloseLevel();
int cannotCloseFinalLevel();
int searchFindsSymbolInPreviousLevels();
int searchFindsCorrectSymbol();

int main(){
    //total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 5;
    
    addOneSymbolAndSearchIt() ? testsPassed++ : printf("test add one symbol and search it failed\n");
    openAndCloseLevel() ? testsPassed++ : printf("test open and close several levels failed\n");
    cannotCloseFinalLevel() ? testsPassed++ : printf("test cannot close final level failed\n");
    searchFindsSymbolInPreviousLevels() ? testsPassed++ : printf("test search finds symbol in previous levels failed\n");
    searchFindsCorrectSymbol() ? testsPassed++ : printf("test search finds correct symbol failed\n");
    

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int addOneSymbolAndSearchIt() {
    SymbolList list;
    initialize(&list);
    int i = 3;
    Symbol newSymbol = createSymbol(INT, "a", &i);
    insert(&list, &newSymbol);
    return search(&list, "a") == &newSymbol;
}

int openAndCloseLevel() {
    SymbolList list;
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
    initialize(&list);
    closeLevel(&list);
    return list.head != NULL && list.head->level == 1;
}

int searchFindsSymbolInPreviousLevels() {
    SymbolList list;
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

    return search(&list, "a") == &symbol1;
}

int searchFindsCorrectSymbol() {
    SymbolList list;
    initialize(&list);

    int a = 3;
    Symbol symbol1 = createSymbol(INT, "a", &a);
    int b = 89;
    Symbol symbol2 = createSymbol(INT, "dl", &b);
    int c = -4;
    Symbol symbol3 = createSymbol(INT, "n", &c);
    int d = 1;
    Symbol symbol4 = createSymbol(BOOL, "a", &d);
    int e = 1;
    Symbol symbol5 = createSymbol(BOOL, "er", &e);

    insert(&list, &symbol1);
    insert(&list, &symbol2);
    openLevel(&list);
    insert(&list, &symbol3);
    insert(&list, &symbol4);
    openLevel(&list);
    insert(&list, &symbol5);

    return search(&list, "a") == &symbol4;
}

int currentLevel(SymbolList *symbolList) {
    return symbolList->head->level;
}