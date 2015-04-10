//Doubly Linked list

#include "../include/dll.h"

Dll_t* createEmptyList(){
	Dll_t* dll = malloc(sizeof(Dll_t));
	dll->head = NULL;
	dll->tail = NULL;
	dll->size = 0;
	return dll;
}


void destroyList(Dll_t* list){
	Node_t* iter = list->head;
	Node_t* temp = iter;
	if(iter != NULL){
		while(iter->next != NULL){
			temp = iter;
			iter = iter->next;
			free(temp);
		}
		free(iter);
	}
	free(list);
}

int isListEmpty(Dll_t* list){
	if(list->size == 0){
		return 1;
	}
	return 0;
}

void appendToFront(const unsigned short dat, Dll_t* list){
	Node_t* node = malloc(sizeof(Node_t));
	node->datum = dat;
	node->next = list->head;
	node->prev = NULL;
	if(list->head != NULL){
		list->head->prev = node;
	}
	list->head = node;
	if(list->tail == NULL){
		list->tail = node;
	}
	list->size += 1;
}

void removeFromBack(Dll_t* list){
	Node_t* nodeToRem = list->tail;
	if(list->tail == NULL){
		return;
	}
	list->tail = list->tail->prev;
	if(list->tail != NULL){
		list->tail->next = NULL;
	}else{
		list->head = NULL;
	}
	list->size -= 1;
	free(nodeToRem);
}

unsigned short getDatumFromBack(Dll_t* list){
	if(list->tail != NULL){
		return list->tail->datum;
	}
	printf("Tried to pull from an empty queue\n");
	exit(0);
}


