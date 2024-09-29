#include "cache.h"

typedef struct {
    int key;
    int value;
} cacheItem;

cacheItem* cacheArray;
int cacheSize;

void cacheInit(int size) {
    cacheSize = size;
    cacheArray = (cacheItem*)malloc(size * sizeof(cacheItem));
    // printf("Initiating cache array with size %d\n", size);
    // printf("Size of cacheItem: %d\n", sizeof(cacheItem));
    // printf("cacheMem size:%d\n", (sizeof(cacheArray)));

    for(int iter = 0; iter < cacheSize; iter++) {
        cacheArray[iter].key = -1;
        cacheArray[iter].value = -1;
    }
}

bool cacheHas(int key) {
    for(int iter = 0; iter < cacheSize; iter++) {
        if(cacheArray[iter].key == key) return true;
    }

    return false;
}

void cacheFree() {
    free(cacheArray);
    // printf("Freed up the cache\n");
}

void cacheInsert(int key, int value) {
    for(int iter = 0; iter < cacheSize; iter++) {
        if(cacheArray[iter].key == -1) {
            cacheArray[iter].key = key;
            cacheArray[iter].value = value;
            break;
        }
    }
    printf("Key: %d value: %d inserted into cache\n", key, value);
}

void cacheRR(int key, int value) {
    int randomIndex = rand() % cacheSize;
    cacheArray[randomIndex].key = key;
    cacheArray[randomIndex].value = value;
}

int cacheGetValue(int key) {
    for(int iter = 0; iter < cacheSize; iter++) {
        if(cacheArray[iter].key == key) return cacheArray[iter].value;
    }
    return -1;
}

// helper function (remove when not needed)
void printCache() {
    for(int iter = 0; iter < cacheSize; iter++) {
        printf("Iter:%d, Cache_Value:%d\n", iter, cacheArray[iter].value);
    }
}
