#include "hashset.h"

struct HashSet *createHashSet(int numberBuckets, string_hash_func hashFunc)
{
	struct HashSet *newHashSet;
	int index;

	newHashSet = (struct HashSet *)malloc(sizeof(struct HashSet));
	if (newHashSet == NULL) {
		fprintf(stderr, "HashSet allocation error!\n");
		exit(-1);
	}

	newHashSet->numberBuckets = numberBuckets;
	newHashSet->hashFunc = hashFunc;
	newHashSet->buckets = (struct List **)
			malloc(numberBuckets * sizeof(struct List *));
	if (newHashSet->buckets == NULL) {
		fprintf(stderr, "HashSet buckets allocation error!\n");
		exit(-1);
	}
	for (index = 0; index < numberBuckets; index++)
		newHashSet->buckets[index] = createList();

	return newHashSet;
}

void deleteHashSet(struct HashSet *hashset)
{
	int index;

	for (index = 0; index < hashset->numberBuckets; index++)
		deleteList(hashset->buckets[index]);

	free(hashset->buckets);
	free(hashset);
}

void addElementToHashset(struct HashSet *hashset, const char *word)
{
	unsigned int code;

	code = hashset->hashFunc(word, hashset->numberBuckets);
	addElementToList(hashset->buckets[code], word);
}

void removeElementFromHashset(struct HashSet *hashset, const char *word)
{
	unsigned int code;

	code = hashset->hashFunc(word, hashset->numberBuckets);
	removeElementFromList(hashset->buckets[code], word);
}

int isElementInHashset(struct HashSet *hashset, const char *word)
{
	unsigned int code;

	code = hashset->hashFunc(word, hashset->numberBuckets);
	return isElementInList(hashset->buckets[code], word);
}

void printBucket(struct HashSet *hashset, int bucketNumber, FILE *file)
{
	struct ListNode *current;

	if (hashset->buckets[bucketNumber]->numberElements == 0)
		return;

	current = hashset->buckets[bucketNumber]->start;
	while (current != NULL) {
		fprintf((file != NULL) ? file : stdout, "%s ", current->word);
		current = current->next;
	}
	fprintf((file != NULL) ? file : stdout, "\n");
}

void printHashset(struct HashSet *hashset, FILE *file)
{
	int bucketNumber;

	for (bucketNumber = 0; bucketNumber < hashset->numberBuckets;
		bucketNumber++)
		printBucket(hashset, bucketNumber, file);
}

struct HashSet *resizeHashset(struct HashSet *hashset, int newSize)
{
	struct HashSet *newHashSet;
	struct ListNode *current;
	int bucketNumber;

	newHashSet = createHashSet(newSize, hashset->hashFunc);

	for (bucketNumber = 0; bucketNumber < hashset->numberBuckets;
		bucketNumber++) {
		current = hashset->buckets[bucketNumber]->start;
		while (current != NULL) {
			addElementToHashset(newHashSet, current->word);
			current = current->next;
		}
	}

	deleteHashSet(hashset);
	return newHashSet;
}
