#ifndef HASHSET_H_
#define HASHSET_H_

#include "list.h"

typedef unsigned int (*string_hash_func)(const char*, unsigned int);

struct HashSet {
	int numberBuckets;
	struct List **buckets;
	string_hash_func hashFunc;
};

struct HashSet *createHashSet(int, string_hash_func);
void deleteHashSet(struct HashSet *);

void addElementToHashset(struct HashSet *, const char*);
void removeElementFromHashset(struct HashSet *, const char*);
int isElementInHashset(struct HashSet *, const char*);

void printBucket(struct HashSet *, int, FILE*);
void printHashset(struct HashSet *, FILE*);

struct HashSet *resizeHashset(struct HashSet *, int);

#endif

