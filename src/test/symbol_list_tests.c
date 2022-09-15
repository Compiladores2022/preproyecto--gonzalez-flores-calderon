#include "../main/symbol_list/symbol_list.h"

#include <stdio.h>

int currentLevel(struct SymbolList *symbolList);

int addOneSymbolAndSearchIt();
int openAndCloseLevel();
int cannotCloseFinalLevel();
int searchFindsSymbolInPreviousLevels();
int searchFindsCorrectSymbol();

int main(){
    //total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 0;
    
    addOneSymbolAndSearchIt() ? testsPassed++ : printf("test add one symbol and search it failed\n"); totalTests++;
    openAndCloseLevel() ? testsPassed++ : printf("test open and close several levels failed\n"); totalTests++;
    cannotCloseFinalLevel() ? testsPassed++ : printf("test cannot close final level failed\n"); totalTests++;
    searchFindsSymbolInPreviousLevels() ? testsPassed++ : printf("test search finds symbol in previous levels failed\n"); totalTests++;
    searchFindsCorrectSymbol() ? testsPassed++ : printf("test search finds correct symbol failed\n"); totalTests++;
    

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int addOneSymbolAndSearchIt() {
    struct SymbolList list;
    initialize(&list);
    int i = 3;
    Symbol newSymbol = createSymbol(TYPEINT, "a", &i);
    insert(&list, &newSymbol);
    return search(&list, "a") == &newSymbol;
}

int openAndCloseLevel() {
    struct SymbolList list;
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
    struct SymbolList list;
    initialize(&list);
    closeLevel(&list);
    return list.head != NULL && list.head->level == 1;
}

int searchFindsSymbolInPreviousLevels() {
    struct SymbolList list;
    initialize(&list);

    int a = 0;
    Symbol symbol1 = createSymbol(TYPEBOOL, "a", &a);
    int b = 2;
    Symbol symbol2 = createSymbol(TYPEINT, "dl", &b);
    int c = 0;
    Symbol symbol3 = createSymbol(TYPEBOOL, "n", &c);
    int d = 15;
    Symbol symbol4 = createSymbol(TYPEINT, "i", &d);

    insert(&list, &symbol1);
    insert(&list, &symbol2);
    openLevel(&list);
    insert(&list, &symbol3);
    insert(&list, &symbol4);
    openLevel(&list);

    return search(&list, "a") == &symbol1;
}

int searchFindsCorrectSymbol() {
    struct SymbolList list;
    initialize(&list);

    int a = 3;
    Symbol symbol1 = createSymbol(TYPEINT, "a", &a);
    int b = 89;
    Symbol symbol2 = createSymbol(TYPEINT, "dl", &b);
    int c = -4;
    Symbol symbol3 = createSymbol(TYPEINT, "n", &c);
    int d = 1;
    Symbol symbol4 = createSymbol(TYPEBOOL, "a", &d);
    int e = 1;
    Symbol symbol5 = createSymbol(TYPEBOOL, "er", &e);

    insert(&list, &symbol1);
    insert(&list, &symbol2);
    openLevel(&list);
    insert(&list, &symbol3);
    insert(&list, &symbol4);
    openLevel(&list);
    insert(&list, &symbol5);

    return search(&list, "a") == &symbol4;
}

int currentLevel(struct SymbolList *symbolList) {
    return symbolList->head->level;
}