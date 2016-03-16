#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct ListNode {
	char *word;
	struct ListNode *next;
};

struct List {
	int numberElements;
	struct ListNode *start;
};

struct ListNode *createListNode(const char *);
void deleteListNode(struct ListNode *);

struct List *createList(void);
void deleteList(struct List *);

int isElementInList(struct List*, const char *);
void addElementToList(struct List*, const char *);
void removeElementFromList(struct List*, const char *);
void printList(struct List *);

#endif
