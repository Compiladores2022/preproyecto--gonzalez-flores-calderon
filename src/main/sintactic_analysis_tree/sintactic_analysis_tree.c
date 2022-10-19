#include "sintactic_analysis_tree.h"
#include "../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int operationType(char * operation, types typeL, types typeR);
int arithmeticOperation(char * operation);
int booleanOperation(char * operation);
int asignType(char * operation, types typeL, types typeR);

int typeErrors = 0;

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

int asignType(char * operation, types typeL, types typeR){
    if(typeL != typeR){
        printf("\033[0;31merror:\033[0m Conflicting types for: =\nexpected: %s = %s\nfound: %s = %s \n", enumToString(typeL), enumToString(typeL), enumToString(typeL), enumToString(typeR));
        exit(0);
        return 0;
    }
    return 1;
}

int operationType(char * operation, types typeL, types typeR) {
    switch (typeL){
    case TYPEINT:
        if(arithmeticOperation(operation) == 0){
            printf("\033[0;31merror:\033[0m Incompatible operation types for %s\nexpected: BOOL %s BOOL\nfound: %s %s %s \n", operation, operation, enumToString(typeR), operation, enumToString(typeL));
            exit(0);
            return 0;
        }
        break;
    case TYPEBOOL:
        if(booleanOperation(operation) == 0){
            typeErrors++;
            printf("\033[0;31merror:\033[0m Incompatible operation types for %s\nexpected: INT %s INT\n", operation, operation);
            exit(0);
            return 0;
        }
        break;
    }
    
}

int checkTypeTree(struct TreeNode *tree) {
    int validTree = 1;

    if(tree == NULL){
        return 1;
    }
    if(tree->right != NULL && tree->right->info->type == UNDEFINED && strcmp(tree->right->info->name, "next") != 0){                
        validTree = validTree && checkTypeTree(tree->right);
    }
    
    if(tree->left != NULL && tree->left->info->type == UNDEFINED){
        validTree = validTree && checkTypeTree(tree->left);  
    }
    
    //checking the partner type for the operation    
    if(strcmp(tree->info->name, "next") != 0 && tree->left != NULL && tree->right != NULL){

        if(strcmp(tree->info->name, "=") == 0){
            validTree = validTree && asignType(tree->info->name, tree->left->info->type, tree->right->info->type);
        }   
        else{
            validTree = validTree && operationType(tree->info->name, tree->left->info->type, tree->right->info->type);
        }
        
        if(tree->left->info->type != tree->right->info->type){
            if(booleanOperation(tree->info->name)){
                validTree = validTree && 0;
                printf("\033[0;31merror:\033[0m Incompatible types for %s operation\nexpected: BOOL %s BOOL \nfound:  %s %s %s\n", tree->info->name, tree->info->name, enumToString(tree->left->info->type), tree->info->name, enumToString(tree->right->info->type));
                exit(0);
            }
            else if (arithmeticOperation(tree->info->name)){
                validTree = validTree && 0;
                printf("\033[0;31merror:\033[0m Incompatible types for %s operation\nexpected: INT %s INT \nfound:  %s %s %s\n", tree->info->name, tree->info->name, enumToString(tree->left->info->type), tree->info->name, enumToString(tree->right->info->type));                
                exit(0);
            }
            
        }
        tree->info->type = tree->left->info->type;
    }
    if(tree->right != NULL && strcmp(tree->right->info->name, "next") == 0){
        checkTypeTree(tree->right);
    }

    return validTree;
}   