#include "HashFile.h"
#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 2

typedef struct {
    int keys[BUCKET_SIZE];
    int values[BUCKET_SIZE];
    int count;
    int localDepth;
} Bucket;

struct HashFile {
    Bucket** directory;
    int globalDepth;
};

int hash(int key, int depth) {
    return key & ((1 << depth) - 1);
}

Bucket* createBucket(int depth) {
    Bucket* b = malloc(sizeof(Bucket));
    b->count = 0;
    b->localDepth = depth;
    return b;
}

HashFile* createFile(const char* filename) {
    HashFile* h = malloc(sizeof(HashFile));

    h->globalDepth = 1;
    h->directory = malloc(2 * sizeof(Bucket*));

    h->directory[0] = createBucket(1);
    h->directory[1] = createBucket(1);

    return h;
}

HashFile* openFile(const char* filename) {
    return createFile(filename);
}

void doubleDirectory(HashFile* h) {
    int oldSize = 1 << h->globalDepth;
    int newSize = oldSize * 2;

    h->directory = realloc(h->directory, newSize * sizeof(Bucket*));

    for (int i = 0; i < oldSize; i++) {
        h->directory[i + oldSize] = h->directory[i];
    }

    h->globalDepth++;
}

void splitBucket(HashFile* h, int index) {
    Bucket* old = h->directory[index];
    int localDepth = old->localDepth;

    if (localDepth == h->globalDepth) {
        doubleDirectory(h);
    }

    Bucket* newBucket = createBucket(localDepth + 1);
    old->localDepth++;

    int dirSize = 1 << h->globalDepth;

    for (int i = 0; i < dirSize; i++) {

        if (h->directory[i] == old && ((i >> (old->localDepth - 1)) & 1)) {
        h->directory[i] = newBucket;
        }

    }

    int tempKeys[BUCKET_SIZE];
    int tempValues[BUCKET_SIZE];
    int tempCount = old->count;

    for (int i = 0; i < tempCount; i++) {
        tempKeys[i] = old->keys[i];
        tempValues[i] = old->values[i];
    }

    old->count = 0;

    for (int i = 0; i < tempCount; i++) {
        insertRegister(h, tempKeys[i], tempValues[i]);
    }
}

int insertRegister(HashFile* h, int key, int value) {
    int index = hash(key, h->globalDepth);
    Bucket* b = h->directory[index];

    if (b->count < BUCKET_SIZE) {
        b->keys[b->count] = key;
        b->values[b->count] = value;
        b->count++;
        return 0;
    }

    splitBucket(h, index);
    return insertRegister(h, key, value);
}

int searchRegister(HashFile* h, int key, int* value) {
    int index = hash(key, h->globalDepth);
    Bucket* b = h->directory[index];

    for (int i = 0; i < b->count; i++) {

        if (b->keys[i] == key) {
         *value = b->values[i];
            return 0;
        }

    }
    return -1;
}

int removeRegister(HashFile* h, int key) {
    int index = hash(key, h->globalDepth);
    Bucket* b = h->directory[index];

    for (int i = 0; i < b->count; i++) {
        if (b->keys[i] == key) {
            b->keys[i] = b->keys[b->count - 1];
            b->values[i] = b->values[b->count - 1];
            b->count--;
            return 0;
        }
    }
    return -1;
}

void closeFile(HashFile* h) {
    int size = 1 << h->globalDepth;

    for (int i = 0; i < size; i++) {
        free(h->directory[i]);
    }

    free(h->directory);
    free(h);
}