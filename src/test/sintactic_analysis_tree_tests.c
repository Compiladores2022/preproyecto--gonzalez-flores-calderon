#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"
#include "../main/types/symbol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int testCreateFullTree();
int testInvalidTree();
int testSingleLeaf();
int testInorder();
int testCheckTypeTree();
int testCheckTypeTreeInvalidType();
int testOperationTypeAddition();
int testOperationTypeOr();

int main(){
    //total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 0;
    
    testCreateFullTree() ? testsPassed++ : printf("\033[0;31mTest Create Full Tree failed\033[0m \n"); totalTests++;
    testInvalidTree() ? testsPassed++ : printf("\033[0;31mTest invalid Tree failed\033[0m \n"); totalTests++;
    testSingleLeaf() ? testsPassed++ : printf("\033[0;31mTest single leaf failed\033[0m \n"); totalTests++;
    testInorder() ? testsPassed++ : printf("\033[0;31mTest indorder failed\033[0m \n"); totalTests++;
    testCheckTypeTree() ? testsPassed++ : printf("\033[0;31mTest check type failed\033[0m \n"); totalTests++;
    
    // Due to the fact that the program cuts when the first error appears, we cannot check these tests.
    // testCheckTypeTreeInvalidType() ? testsPassed++ : printf("\033[0;31mtest check type failed\033[0m \n"); totalTests++;
    // testOperationTypeAddition() ? testsPassed++ : printf("\033[0;31mTest checking the partner type for the operation arithmetic failed\033[0m \n"); totalTests++;
    // testOperationTypeOr() ? testsPassed++ : printf("\033[0;31mTest checking the partner type for the operation boolean failed\033[0m \n"); totalTests++;

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int testCreateFullTree() {
    
    int a = 0;
    Symbol *symbol1 = createSymbol(TYPEBOOL, "a", &a, 0);
    int b = 1;
    Symbol *symbol2 = createSymbol(TYPEBOOL, "b", &b, 8);
    int c = 2;
    Symbol *symbol3 = createSymbol(TYPEBOOL, "c", &c, 0);
    struct TreeNode *right = createNode(symbol1);
    struct TreeNode *left = createNode(symbol2);
    struct TreeNode *tree = createTree(symbol3, left, right);

    //printf("%d \n", *(int *)tree->head->right->info->value);
    if(tree->right->info->value != symbol1->value){
        return 0;
    }
    if(tree->left->info->value != symbol2->value){
       return 0; 
    }
    if(tree->info->value != symbol3->value){
        return 0;
    }
    return 1;
}

int testInvalidTree(){
    int c = 2;
    Symbol *symbol3 = createSymbol(TYPEBOOL, "a", &c, 8);
    if(createTree(symbol3, NULL, NULL) == NULL){
        return 1;
    }
    return 0;
}

int testSingleLeaf(){
    int a = 0;
    Symbol *symbol1 = createSymbol(TYPEBOOL, "a", &a, 0);
    struct TreeNode *right = createNode(symbol1);
    int c = 2;
    Symbol *symbol3 = createSymbol(TYPEBOOL, "b", &c, 0);
    struct TreeNode *tree = createTree(symbol3, NULL,right);
    if(tree == NULL){
        return 0;
    }
    
    return 1;
}

int testInorder(){
    int a = 0;
    Symbol *symbol1 = createSymbol(TYPEBOOL, "a", &a, 8);
    struct TreeNode *right = createNode(symbol1);
    int b = 1;
    Symbol *symbol2 = createSymbol(TYPEBOOL, "b", &b, 16);
    struct TreeNode *left = createNode(symbol2);
    int c = 2;
    Symbol *symbol3 = createSymbol(TYPEBOOL, "c", &c, 0);
    struct TreeNode *tree = createTree(symbol3, left, right);
    char *p = malloc(50 * sizeof(char));
    getTreeInOrder(tree, p);
    if(strcmp(p, " b c a") == 0){
        return 1;
    }
    printf("expected: %s\nbut found: %s\n", p, " b c a");
    return 0;
}

int testCheckTypeTree(){
    int a = 3;
    Symbol *symbol1 = createSymbol(TYPEINT, "3", &a, 8);
    struct TreeNode *right = createNode(symbol1);
    int b = 5;
    Symbol *symbol2 = createSymbol(TYPEINT, "5", &b, 16);
    struct TreeNode *left = createNode(symbol2);
    Symbol *plus = createSymbol(UNDEFINED, "+", NULL, 24);
    struct TreeNode *tree = createTree(plus, left, right);
    checkTypeTree(tree);
}

int testCheckTypeTreeInvalidType(){
    int a = 0;
    Symbol *symbol1 = createSymbol(TYPEBOOL, "False", &a, 0);
    struct TreeNode *right = createNode(symbol1);
    int b = 34;
    Symbol *symbol2 = createSymbol(TYPEINT, "34", &b, 0);
    struct TreeNode *left = createNode(symbol2);
    Symbol *plus = createSymbol(UNDEFINED, "+", NULL, 8);
    struct TreeNode *tree = createTree(plus, left, right);
    if (checkTypeTree(tree) == 1){
        return 1;
    }
    return 0;
}

int testOperationTypeAddition(){
    int a = 1;
    Symbol *symbol1 = createSymbol(TYPEBOOL, "TRUE", &a, 8);
    struct TreeNode *right = createNode(symbol1);
    int b = 0;
    Symbol *symbol2 = createSymbol(TYPEBOOL, "FALSE", &b, 0);
    struct TreeNode *left = createNode(symbol2);
    Symbol *plus = createSymbol(UNDEFINED, "+", NULL, 16);
    struct TreeNode *tree = createTree(plus, left, right);
    checkTypeTree(tree);
}

int testOperationTypeOr(){
    int a = 45;
    Symbol *symbol1 = createSymbol(TYPEINT, "45", &a, 0);
    struct TreeNode *right = createNode(symbol1);
    int b = 30;
    Symbol *symbol2 = createSymbol(TYPEINT, "30", &b, 8);
    struct TreeNode *left = createNode(symbol2);
    Symbol *or = createSymbol(UNDEFINED, "||", NULL, 16);
    struct TreeNode *tree = createTree(or, left, right);
    checkTypeTree(tree);
}