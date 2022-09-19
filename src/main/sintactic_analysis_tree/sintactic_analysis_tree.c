// nuevoNodo(); el nodo son los simbolos terminales
// crearArbol();crea un arbol tomando 2 arboles como hijos y un nodo, 
// un arbol sin hijos es una hoja, todos los arboles tienen un nodo
// asi en caso de q sean una hoja, tienen algun valor
// en caso de un return, se hace un arbol de 1 solo hijo, donde el valor del arbol es el return 
// y el hijo es la expresion

#include "sintactic_analysis_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    struct TreeNode *newNode;

    newNode = CreateEmptyNode();
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
