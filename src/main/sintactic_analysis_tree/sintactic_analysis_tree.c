// nuevoNodo(); el nodo son los simbolos terminales
// crearArbol();crea un arbol tomando 2 arboles como hijos y un nodo, 
// un arbol sin hijos es una hoja, todos los arboles tienen un nodo
// asi en caso de q sean una hoja, tienen algun valor
// en caso de un return, se hace un arbol de 1 solo hijo, donde el valor del arbol es el return 
// y el hijo es la expresion

#include "sintactic_analysis_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct TreeNode * CrateEmptyNode() {
    struct TreeNode *newNode;

    newNode = (struct TreeNode *) malloc (sizeof(struct TreeNode));
    if(newNode == NULL){
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

SintacticAnalysisTree * CreateEmptyTree() {
    SintacticAnalysisTree *newTree = NULL;

    newTree = (SintacticAnalysisTree *) malloc (sizeof(SintacticAnalysisTree));

    return newTree;
}

struct TreeNode * createNode(Symbol *symbol) {
    struct TreeNode *newNode;

    newNode = CrateEmptyNode();
    newNode->info = symbol;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

SintacticAnalysisTree * createTree(Symbol *symbol, struct TreeNode *right, struct TreeNode *left) {
    
    //Sintactic Analysis Tree (SAT)
    SintacticAnalysisTree *sat = CreateEmptyTree();
    sat->head = CrateEmptyNode();
    sat->head->info = symbol;
    if(right == NULL){
        return NULL;
    }
    sat->head->right = right;
    sat->head->left = left;

    return sat;
}
