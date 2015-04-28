#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct Node_t{
	unsigned short datum;
	struct Node_t* next;
	struct Node_t* prev;
} Node_t;

typedef struct Dll_t{
	Node_t* head;
	Node_t* tail;
	int size;
} Dll_t;

typedef Dll_t DLL;

Dll_t* createEmptyList();
void destroyList(Dll_t* list);
int isListEmpty(Dll_t* list);
void appendToFront(const unsigned short dat, Dll_t* list);
void removeFromBack(Dll_t* list);
unsigned short getDatumFromBack(Dll_t* list);
#endif /* DOUBLYLINKEDLIST_H */