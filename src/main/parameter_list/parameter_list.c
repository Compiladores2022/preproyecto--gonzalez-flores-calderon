#include <stdio.h>
#include <stdlib.h>
#include "parameter_list.h"


void initialize(parameterList *parameterList) {
    parameterList->head = NULL; 
}

struct ParameterNode * CrearNodo(){
	struct ParameterNode *nuevo;
	newNode = (struct ParameterNode *) malloc (sizeof(struct ParameterNode));
	if (newNode == NULL){
	 	exit(EXIT_FAILURE);
	}
	else {
	 return newNode;
	}
}

void Insertar(ParameterList *list, Parameter parameter){
	
	struct Nodo *p;

	p = CrearNodo(); 
	p->info = parameter;
	p->next = list->head;
	list->head = p;
}