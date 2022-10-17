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
    int testsPassed = 0, totalTests = 0;
    
    addOneSymbolAndSearchIt() ? testsPassed++ : printf("\033[0;31mTest add one symbol and search it failed\033[0m \n"); totalTests++;
    openAndCloseLevel() ? testsPassed++ : printf("\033[0;31mTest open and close several levels failed\033[0m \n"); totalTests++;
    cannotCloseFinalLevel() ? testsPassed++ : printf("\033[0;31mTest cannot close final level failed\033[0m \n"); totalTests++;
    searchFindsSymbolInPreviousLevels() ? testsPassed++ : printf("\033[0;31mTest search finds symbol in previous levels failed\033[0m \n"); totalTests++;
    searchFindsCorrectSymbol() ? testsPassed++ : printf("\033[0;31mTest search finds correct symbol failed\033[0m \n"); totalTests++;
    

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int addOneSymbolAndSearchIt() {
    SymbolList list;
    initialize(&list);
    int i = 3;
    Symbol *newSymbol = createSymbol(TYPEINT, "a", &i, 0);
    insert(&list, newSymbol);
    return search(&list, "a") == newSymbol;
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
    Symbol *symbol1 = createSymbol(TYPEBOOL, "a", &a, 8);
    int b = 2;
    Symbol *symbol2 = createSymbol(TYPEINT, "dl", &b, 16);
    int c = 0;
    Symbol *symbol3 = createSymbol(TYPEBOOL, "n", &c, 0);
    int d = 15;
    Symbol *symbol4 = createSymbol(TYPEINT, "i", &d, 24);

    insert(&list, symbol1);
    insert(&list, symbol2);
    openLevel(&list);
    insert(&list, symbol3);
    insert(&list, symbol4);
    openLevel(&list);

    return search(&list, "a") == symbol1;
}

int searchFindsCorrectSymbol() {
    SymbolList list;
    initialize(&list);

    int a = 3;
    Symbol *symbol1 = createSymbol(TYPEINT, "a", &a, 8);
    int b = 89;
    Symbol *symbol2 = createSymbol(TYPEINT, "dl", &b, 16);
    int c = -4;
    Symbol *symbol3 = createSymbol(TYPEINT, "n", &c, 24);
    int d = 1;
    Symbol *symbol4 = createSymbol(TYPEBOOL, "a", &d, 32);
    int e = 1;
    Symbol *symbol5 = createSymbol(TYPEBOOL, "er", &e, 40);

    insert(&list, symbol1);
    insert(&list, symbol2);
    openLevel(&list);
    insert(&list, symbol3);
    insert(&list, symbol4);
    openLevel(&list);
    insert(&list, symbol5);

    return search(&list, "a") == symbol4;
}

int currentLevel(SymbolList *symbolList) {
    return symbolList->head->level;
}