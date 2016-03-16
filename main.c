#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hashset.h"

#define MAX_LINE_LENGTH 21000

struct HashSet *treatCommand(struct HashSet *hashset, char *lineBuffer)
{
	FILE *outputFile;
	struct HashSet *temp;
	char *token;
	int bucketNumber;
	char *word;

	if (strlen(lineBuffer) == 0)
		return hashset;

	token = strtok(lineBuffer, " ");
	if (strcmp(token, "add") == 0) {
		token = strtok(NULL, " ");
		addElementToHashset(hashset, token);
	} else if (strcmp(token, "print") == 0) {
		token = strtok(NULL, " ");
		if (token != NULL) {
			outputFile = fopen(token, "a");
			printHashset(hashset, outputFile);
			fclose(outputFile);
		} else {
			printHashset(hashset, NULL);
		}
	} else if (strcmp(token, "remove") == 0) {
		token = strtok(NULL, " ");
		removeElementFromHashset(hashset, token);
	} else if (strcmp(token, "print_bucket") == 0) {
		token = strtok(NULL, " ");
		bucketNumber = atoi(token);
		token = strtok(NULL, " ");
		if (token != NULL) {
			outputFile = fopen(token, "a");
			printBucket(hashset, bucketNumber, outputFile);
			fclose(outputFile);
		} else {
			printBucket(hashset, bucketNumber, NULL);
		}
	} else if (strcmp(token, "resize") == 0) {
		token = strtok(NULL, " ");
		if (strcmp(token, "double") == 0)
			hashset = resizeHashset(hashset,
			2 * hashset->numberBuckets);
		else if (strcmp(token, "halve") == 0)
			hashset = resizeHashset(hashset,
			hashset->numberBuckets / 2);
	} else if (strcmp(token, "clear") == 0) {
		temp = hashset;
		hashset = createHashSet(hashset->numberBuckets, hash);
		deleteHashSet(temp);
	} else if (strcmp(token, "find") == 0) {
		token = strtok(NULL, " ");
		word = token;
		token = strtok(NULL, " ");
		if (token != NULL) {
			outputFile = fopen(token, "a");
			fprintf(outputFile,
			isElementInHashset(hashset, word) ?
			"True\n" : "False\n");
			fclose(outputFile);
		} else {
			fprintf(stdout,
			isElementInHashset(hashset, word) ?
			"True\n" : "False\n");
		}
	} else {
		fprintf(stderr, "Invalid command: %s\n", token);
	}

	return hashset;
}

int main(int argc, char **argv)
{

	struct HashSet *hashset;
	FILE *inputFile;
	int fileIndex;
	char lineBuffer[MAX_LINE_LENGTH];
	char *temp;

	if (argc == 1) {
		fprintf(stderr, "Invalid number of arguments!\n");
		return -1;
	}

	if (atoi(argv[1]) <= 0) {
		fprintf(stderr,
				"Number of buckets should be greater than 0!\n");
		return -1;
	}

	hashset = createHashSet(atoi(argv[1]), hash);
	if (hashset == NULL) {
		fprintf(stderr, "HashSet initialization error!\n");
		return -1;
	}

	if (argc == 2) {

		while (fgets(lineBuffer, MAX_LINE_LENGTH, stdin) != NULL) {
			temp = strrchr(lineBuffer, '\n');
			if (temp != NULL)
				*temp = '\0';
			hashset = treatCommand(hashset, lineBuffer);
		}

	} else {
		for (fileIndex = 2; fileIndex < argc; fileIndex++) {
			inputFile = fopen(argv[fileIndex], "r");

			if (inputFile == NULL)
				continue;

			while (fgets(lineBuffer, MAX_LINE_LENGTH, inputFile)
					!= NULL) {
				temp = strrchr(lineBuffer, '\n');
				if (temp != NULL)
					*temp = '\0';
				hashset = treatCommand(hashset, lineBuffer);
			}

			fclose(inputFile);
		}
	}

	deleteHashSet(hashset);

	return 0;
}
