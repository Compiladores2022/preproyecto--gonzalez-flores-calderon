#include "../main/sintactic_analysis_tree/sintactic_analysis_tree.h"

#include <stdio.h>

int testCreateFullTree();
int testInvalidTree();
int testSingleLeaf();

int main(){
    //total tests must be manually updated when adding a new test
    int testsPassed = 0, totalTests = 0;
    
    testCreateFullTree() ? testsPassed++ : printf("test Create Full Tree failed \n"); totalTests++;
    testInvalidTree() ? testsPassed++ : printf("test Create Full Tree failed \n"); totalTests++;
    testSingleLeaf() ? testsPassed++ : printf("test Create Full Tree failed \n"); totalTests++;

    printf("tests passed: %d out of %d\n", testsPassed, totalTests);
    return 0;
}

int testCreateFullTree() {
    
    int a = 0;
    Symbol symbol1 = createSymbol(TYPEBOOL, "a", &a);
    int b = 1;
    Symbol symbol2 = createSymbol(TYPEBOOL, "a", &b);
    int c = 2;
    Symbol symbol3 = createSymbol(TYPEBOOL, "a", &c);
    struct TreeNode *right = createNode(&symbol1);
    struct TreeNode *left = createNode(&symbol2);
    struct TreeNode *tree = createTree(&symbol3, left, right);

    //printf("%d \n", *(int *)tree->head->right->info->value);
    if(tree->right->info->value != symbol1.value){
        return 0;
    }
    if(tree->left->info->value != symbol2.value){
       return 0; 
    }
    if(tree->info->value != symbol3.value){
        return 0;
    }

    return 1;
}

int testInvalidTree(){
    int c = 2;
    Symbol symbol3 = createSymbol(TYPEBOOL, "a", &c);
    if(createTree(&symbol3, NULL, NULL) == NULL){
        return 1;
    }
    return 0;
}

int testSingleLeaf(){
    int a = 0;
    Symbol symbol1 = createSymbol(TYPEBOOL, "a", &a);
    struct TreeNode *right = createNode(&symbol1);
    int c = 2;
    Symbol symbol3 = createSymbol(TYPEBOOL, "a", &c);
    if(createTree(&symbol3, right, NULL) == NULL){
        return 0;
    }
    return 1;
}