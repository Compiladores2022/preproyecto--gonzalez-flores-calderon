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
    
    struct TreeNode *newNode = CreateEmptyNode();
    newNode->info = symbol;
    if(right == NULL){
        return NULL;
    }
    newNode->right = right;
    newNode->left = left;

    return newNode;
}

void printTreeInOrder(struct TreeNode *tree, char * s) {
    if(tree == NULL){
        return;
    }
    printTreeInOrder(tree->left, s);
    strcat(s, " ");
    strcat(s, tree->info->name);
    printTreeInOrder(tree->right, s);
    
}

int arithmeticOperation(char * operation) {
    if(strcmp(operation, "+") == 0){
        return 1;
    }
    if(strcmp(operation, "-") == 0){
        return 1;
    }
    if(strcmp(operation, "*") == 0){
        return 1;
    }
    
    return  0;
}

int booleanOperation(char * operation) {
    if(strcmp(operation, "&&") == 0){
        return 1;
    }
    if(strcmp(operation, "||") == 0){
        return 1;
    }
    return 0;
}

void operationType(char * operation, types type) {

    switch (type)
    {
    case TYPEINT:
        if(arithmeticOperation(operation) == 0){
            printf("Incompatible operation types for %s\nexpected: BOOL %s BOOL\n", operation, operation);
        }
        break;
    case TYPEBOOL:
        if(booleanOperation(operation) == 0){
            printf("Incompatible operation types for %s\nexpected: INT %s INT\nfound: ", operation, operation);
        }
        break;
    }
}

void checkTypeTree(struct TreeNode *tree) {
    if(tree == NULL){
        return;
    }
    if(tree->left != NULL && tree->left->info->type == UNDEFINED){
        checkTypeTree(tree->left);
    }
    if(tree->right != NULL && tree->right->info->type == UNDEFINED){
        checkTypeTree(tree->right);
    }
    
    //checking the partner type for the operation
    operationType(tree->info->name, tree->left->info->type);

    if(tree->left->info->type != tree->right->info->type){
        printf("Incompatible types for %s operation\nexpected: %s +  %s \nfound:  %s + %s\n",tree->info->name,enumToString(tree->left->info->type) ,enumToString(tree->left->info->type), enumToString(tree->left->info->type), enumToString(tree->right->info->type));
    }
    tree->info->type = tree->left->info->type;
}   