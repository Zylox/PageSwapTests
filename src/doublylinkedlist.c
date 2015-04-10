//Doubly Linked list

#include "doublylinkedlist.h"

static Node* findLocById(unsigned int id, DoublyLinkedList* list);

DoublyLinkedList* createEmptyList(){
	DoublyLinkedList* dll = malloc(sizeof(DoublyLinkedList));
	dll->head = NULL;
	dll->tail = NULL;
	dll->size = 0;
	return dll;
}


void destroyList(DoublyLinkedList* list){
	Node* iter = list->head;
	Node* temp = iter;
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

int isListEmpty(DoublyLinkedList* list){
	if(list->size == 0){
		return 1;
	}
	return 0;
}

void appendToFront(const unsigned short dat, DoublyLinkedList* list){
	Node* node = malloc(sizeof(Node));
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

void appendToBack(const Datum dat, DoublyLinkedList* list){
	Node* node = malloc(sizeof(Node));
	node->datum = dat;
	node->next = NULL;
	node->prev = list->tail;
	if(list->tail != NULL){
		list->tail->next = node;
	}
	list->tail = node;
	if(list->head == NULL){
		list->head = node;
	}
	list->size += 1;
}

void removeFromBack(DoublyLinkedList* list){
	Node* nodeToRem = list->tail;
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

void removeFromFront(DoublyLinkedList* list){
	Node* nodeToRem = list->head;
	if(list->head == NULL){
		return;
	}
	list->head = list->head->next;
	if(list->head != NULL){
		list->head->prev = NULL;
	}else{
		list->tail = NULL;
	}
	list->size -= 1;
	free(nodeToRem);
}

Datum getDatumFromFront(DoublyLinkedList* list){
	if(list->head != NULL){
		return list->head->datum;
	}
	printf("Tried to pull from an empty queue\n");
	exit(0);
}

Datum getDatumFromBack(DoublyLinkedList* list){
	if(list->tail != NULL){
		return list->tail->datum;
	}
	printf("Tried to pull from an empty queue\n");
	exit(0);
}

Datum* findById(unsigned int id, DoublyLinkedList* list){
	Node* foundNode = findLocById(id, list);
	if(foundNode != NULL){
		return &(foundNode->datum);
	}

	return NULL;
}

/** Returns 0 if an id was found and removed, 1 if not*/
int removeById(unsigned int id, DoublyLinkedList* list){
	Node* foundNode = findLocById(id,list);
	if(foundNode != NULL){
		if(foundNode->next != NULL){
			foundNode->next->prev = foundNode->prev;
		}
		if(foundNode->prev != NULL){
			foundNode->prev->next = foundNode->next;
		}
		list->size -= 1;
		free(foundNode);
		return 0;
	}
	return 1;
}

static Node* findLocById(unsigned int id, DoublyLinkedList* list){
	Node* iter = list->head;
	while(iter != NULL){
		if(iter->datum.blockId == id){
			return iter;
		}
		iter = iter->next;
	}
	return NULL;
}