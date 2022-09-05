// nuevoNodo(); el nodo son los simbolos terminales
// crearArbol();crea un arbol tomando 2 arboles como hijos y un nodo, 
// un arbol sin hijos es una hoja, todos los arboles tienen un nodo
// asi en caso de q sean una hoja, tienen algun valor
// en caso de un return, se hace un arbol de 1 solo hijo, donde el valor del arbol es el return 
// y el hijo es la expresion

#include "sintactic_analysis_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct Node * CrateEmptyNode() {
    struct Node *newNode;

    newNode = (struct Node *) malloc (sizeof(struct Node));
    if(newNode == NULL){
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

void createNode(Symbol *symbol) {
    //TODO IMPLEMENT
}

void createTree(struct Node *left, struct Node *right) {
    //TODO TODO IMPLEMENT
}
