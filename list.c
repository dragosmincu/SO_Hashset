#include "list.h"

struct ListNode *createListNode(const char *word)
{
	struct ListNode *newListNode;

	newListNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	if (newListNode == NULL) {
		fprintf(stderr, "ListNode allocation error!\n");
		exit(-1);
	}

	newListNode->word = (char *)malloc(sizeof(char) * (strlen(word) + 1));
	if (newListNode->word == NULL) {
		fprintf(stderr, "ListNode word allocation error!\n");
		exit(-1);
	}
	strcpy(newListNode->word, word);
	newListNode->next = NULL;

	return newListNode;
}

void deleteListNode(struct ListNode *listNode)
{
	free(listNode->word);
	free(listNode);
}

struct List *createList(void)
{
	struct List *newList;

	newList = (struct List *)malloc(sizeof(struct List));
	if (newList == NULL) {
		fprintf(stderr, "List allocation error!\n");
		exit(-1);
	}

	newList->numberElements = 0;
	newList->start = NULL;

	return newList;
}

void deleteList(struct List *list)
{
	struct ListNode *current;
	struct ListNode *forward;

	current = list->start;
	while (current != NULL) {
		forward = current->next;
		deleteListNode(current);
		current = forward;
	}

	free(list);
}

int isElementInList(struct List *list, const char *word)
{
	struct ListNode *element;

	element = list->start;
	while (element != NULL) {
		if (strcmp(element->word, word) == 0)
			return 1;

		element = element->next;
	}

	return 0;
}

void addElementToList(struct List *list, const char *word)
{
	struct ListNode *elementToAdd;
	struct ListNode *current;

	elementToAdd = createListNode(word);

	if (list->start == NULL) {
		list->start = elementToAdd;
		list->numberElements++;
		return;
	}

	current = list->start;
	while (1) {
		if (strcmp(current->word, word) == 0) {
			deleteListNode(elementToAdd);
			return;
		}

		if (current->next != NULL)
			current = current->next;
		else
			break;
	}
	current->next = elementToAdd;
	list->numberElements++;
}

void removeElementFromList(struct List *list, const char *word)
{
	struct ListNode *current;
	struct ListNode *temp;

	if (list->start == NULL)
		return;

	current = list->start;
	if (strcmp(current->word, word) == 0) {
		list->start = list->start->next;
		deleteListNode(current);
		list->numberElements--;
		return;
	}

	while (current->next != NULL) {
		if (strcmp(current->next->word, word) == 0) {
			temp = current->next;
			current->next = temp->next;
			deleteListNode(temp);
			list->numberElements--;
			break;
		}

		current = current->next;
	}
}

void printList(struct List *list)
{
	struct ListNode *currentNode;

	currentNode = list->start;

	while (currentNode != NULL) {
		printf("%s ", currentNode->word);
		currentNode = currentNode->next;
	}
	printf("\n");
}
