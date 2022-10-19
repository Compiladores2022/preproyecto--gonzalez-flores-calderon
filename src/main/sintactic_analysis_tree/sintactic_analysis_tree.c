#include "sintactic_analysis_tree.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void operationType(char * operation, types type);
int arithmeticOperation(char * operation);
int booleanOperation(char * operation);

struct TreeNode * CreateEmptyNode() {
    struct TreeNode *newNode;

    newNode = (struct TreeNode *) malloc (sizeof(struct TreeNode));
    if(newNode == NULL){
        printf("couldn't create tree node, exiting\n");
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

SintacticAnalysisTree * CreateEmptyTree() {
    SintacticAnalysisTree *newTree = NULL;

    newTree = (SintacticAnalysisTree *) malloc (sizeof(SintacticAnalysisTree));
    if(newTree == NULL){
        printf("couldn't create tree node, exiting\n");
        exit(EXIT_FAILURE);
    }
    else{
        return newTree;
    }
}

struct TreeNode * createNode(Symbol *symbol) {

    struct TreeNode *newNode = CreateEmptyNode();
    newNode->info = symbol;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct TreeNode * createTree(Symbol *symbol, struct TreeNode *left, struct TreeNode *right) {
    
    if(right == NULL && left == NULL){
        return NULL;
    }
    
    struct TreeNode *newNode = CreateEmptyNode();
    newNode->info = symbol;
    newNode->right = right;
    newNode->left = left;

    return newNode;
}

void getTreeInOrder(struct TreeNode *tree, char * s) {
    if(tree == NULL){
        return;
    }
    getTreeInOrder(tree->left, s);
    strcat(s, " ");
    strcat(s, tree->info->name);
    getTreeInOrder(tree->right, s);
    
}

void printTreeInOrder(struct TreeNode *tree) {
    if(tree == NULL){
        return;
    }
    printTreeInOrder(tree->left);
    printf(" %s", tree->info->name);
    printTreeInOrder(tree->right);
    
}

void operationType(char * operation, types type) {
    switch (type){
    case TYPEINT:
        if(arithmeticOperation(operation) == 0){
            printf("Incompatible operation types for %s\nexpected: BOOL %s BOOL\n", operation, operation);
        }
        break;
    case TYPEBOOL:
        if(booleanOperation(operation) == 0){
            printf("Incompatible operation types for %s\nexpected: INT %s INT\n", operation, operation);
        }
        break;
    }
    
}

void checkTypeTree(struct TreeNode *tree) {
    if(tree == NULL){
        return;
    }

    if(tree->right != NULL && tree->right->info->type == UNDEFINED && strcmp(tree->right->info->name, "next") != 0){                
        checkTypeTree(tree->right);
    }
    
    if(tree->left != NULL && tree->left->info->type == UNDEFINED){
        checkTypeTree(tree->left);  
    }
    
    //checking the partner type for the operation    
    if(strcmp(tree->info->name, "next") != 0 ){
        operationType(tree->info->name, tree->left->info->type);
        if(tree->left->info->type != tree->right->info->type){
            printf("Incompatible types for %s operation\nexpected: %s %s %s \nfound:  %s %s %s\n", tree->info->name, enumToString(tree->left->info->type), tree->info->name, enumToString(tree->left->info->type), enumToString(tree->left->info->type), tree->info->name, enumToString(tree->right->info->type));
        }
        tree->info->type = tree->left->info->type;
    }
    if(tree->right != NULL && strcmp(tree->right->info->name, "next") == 0){
        checkTypeTree(tree->right);
    }
}   