#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include"Datum.h"

typedef struct Node{
	unsigned short datum;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct DoublyLinkedList{
	Node* head;
	Node* tail;
	int size;
} DoublyLinkedList;

typedef DoublyLinkedList DLL;

DoublyLinkedList* createEmptyList();
void destroyList(DoublyLinkedList* list);
int isListEmpty(DoublyLinkedList* list);
void appendToFront(const unsigned short dat, DoublyLinkedList* list);
void appendToBack(const Datum dat, DoublyLinkedList* list);
void removeFromBack(DoublyLinkedList* list);
void removeFromFront(DoublyLinkedList* list);
Datum getDatumFromFront(DoublyLinkedList* list);
Datum getDatumFromBack(DoublyLinkedList* list);
Datum* findById(unsigned int id, DoublyLinkedList* list);
int removeById(unsigned int id, DoublyLinkedList* list);

#endif /* DOUBLYLINKEDLIST_H */