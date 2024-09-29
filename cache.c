#include "cache.h"

typedef struct {
    long long key;
    int value;
    clock_t insertionT;
} cacheItem;

cacheItem* cacheArray;
int cacheSize;
int cacheType;
clock_t startT;

void cacheInit(int size, int type) {
    cacheSize = size;
    cacheType = type;
    cacheArray = (cacheItem*)malloc(size * sizeof(cacheItem));
    startT = clock();
    // printf("Initiating cache array with size %d\n", size);
    // printf("Size of cacheItem: %d\n", sizeof(cacheItem));
    // printf("cacheMem size:%d\n", (sizeof(cacheArray)));

    for(int iter = 0; iter < cacheSize; iter++) {
        cacheArray[iter].key = -1;
        cacheArray[iter].value = -1;
    }
}

bool cacheHas(long long key) {
    for(int iter = 0; iter < cacheSize; iter++) {
        if(cacheArray[iter].key == key) return true;
    }
    return false;
}

void cacheFree() {
    free(cacheArray);
    // printf("Freed up the cache\n");
}

void cacheInsert(long long key, int value) {
    bool full = true;
    for(int iter = 0; iter < cacheSize; iter++) {
        if(cacheArray[iter].key == -1) {
            cacheArray[iter].key = key;
            cacheArray[iter].value = value;
            cacheArray[iter].insertionT = startT - clock();
            full = false;
            break;
        }
    }

    if(full) {

        if(cacheType == 1) cacheLRU(key, value); // not working rn
        else cacheRR(key, value);
    }
    // printf("Key: %d value: %d inserted into cache\n", key, value);
}

void cacheLRU(long long key, int value) {
    // Newest function can latest called key-pair should be put on top.
    clock_t longest = cacheArray[0].insertionT;
    int index = 0;
    for(int iter = 1; iter < cacheSize; iter++) {
        if(longest > cacheArray[iter].insertionT) {
            longest = cacheArray[iter].insertionT;
            // printf("Longest time: %llu", longest);
            index = iter;
        }
    }

    // printf("Removing pair: %d, value: %d for pair: %d, value: %d\n", cacheArray[index].key, cacheArray[index].value, key, value);

    cacheArray[index].key = key;
    cacheArray[index].value = value;
    cacheArray[index].insertionT = startT - clock();



}

void cacheRR(long long key, int value) {
    int randomIndex = rand() % cacheSize;
    // printf("RR @ %d\n", randomIndex);
    cacheArray[randomIndex].key = key;
    cacheArray[randomIndex].value = value;
}

int cacheGetValue(long long key) {
    for(int iter = 0; iter < cacheSize; iter++) {
        if(cacheArray[iter].key == key) {
            if(cacheType == 1) cacheArray[iter].insertionT = startT - clock();
            return cacheArray[iter].value;
        }
    }
    return -1;
}

// helper function (remove when not needed)
void printCache() {
    for(int iter = 0; iter < cacheSize; iter++) {
        printf("Iter:%d, Key_Value:%d, Cache_Value:%d, Time_Value:%ld\n", iter, cacheArray[iter].key, cacheArray[iter].value, startT - cacheArray[iter].insertionT);
    }
}
