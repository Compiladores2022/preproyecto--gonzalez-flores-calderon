#include <stdio.h>
#include <stdlib.h>
#include "parameter_list.h"


void initializeP(struct ParameterList *parameterList) {
    parameterList->head = NULL;
}

struct ParameterNode * createParameterNode(){
	struct ParameterNode *newNode;
	newNode = (struct ParameterNode *) malloc (sizeof(struct ParameterNode));
	if (newNode == NULL){
	 	exit(EXIT_FAILURE);
	}
	else {
	 return newNode;
	}
}

void insertParameter(struct ParameterList *list, struct Parameter *parameter){
	
	struct ParameterNode *p;
	p = createParameterNode(); 
	p->info = parameter;
	p->next = list->head;
	list->head = p;
}

int sizeParameter(struct ParameterNode *list){

	struct ParameterNode *aux = list;

	int count = 0;
	while (aux != NULL){
		count += 1;
		aux = aux->next;
	}

	return count;
}