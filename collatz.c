#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cache.h"

int collatzConject(int);
int collatzWrapper(int, int*);
int getRandomNumber(int, int);

// From memo now remember how to use it
typedef int (*collatzFunc)(int);
collatzFunc ptr;

/* TODO LIST
1. DONE - Build a wrapper around the core function
2. DONE - Program arguments that specify cache policy (none, LRU, x) and cache size
3. TODO - Implement LRU cache last CWID is 8 so RR (Random Replacement)
4. DONE - Report Cache hit % in output.csv
5. TODO - Determine smallest cache size for (N=10000, MIN=1, MAX=500000) 30% cache hit
Or multiply N by 5
6. TODO - Do this for both cache types
*/

int main(int argc, char* argv[]) {
    // Five arguments values
    // numOfValues = number of values
    // minNum = lowest value
    // maxNum = highest value
    // cacheType = ("none", "LRU" (Least Recetnly Used), "RR"(Random Replacement))
    // cacheSize = size of cache (int)

    int numOfValues;
    int minNum;
    int maxNum;
    char* cacheType;
    int cacheSize;

    if (argc < 6
        || sscanf(argv[1], "%d", &numOfValues) == 0
        || sscanf(argv[2], "%d", &minNum) == 0
        || sscanf(argv[3], "%d", &maxNum) == 0
        || !(strcmp(argv[4], "none") == 0 || strcmp(argv[4], "LRU") == 0 || strcmp(argv[4], "RR") == 0)
        || sscanf(argv[5], "%d", &cacheSize) == 0) {
        printf("Invalid input: ./collatz.exe <numOfValues> <minNum> <maxNum> <cacheType(none, LRU, RR)> <cacheSize>");
        return(1);
    }
    else cacheType = argv[4];

    // Output to .csv file
    FILE* fpt;
    fpt = fopen("output.csv", "w+");
    fprintf(fpt, "Number, Steps\n");

    ptr = collatzConject; // Wrapper set to core function
    cacheInit(cacheSize); // Set size of cache to user input
    srand(time(NULL)); // Max number of rand is RAND_MAX (2^15).
    int cacheHit = 0;
    printf("CacheType:%s\n", cacheType);

    // Generate N number of random values
    for (int iter = 0; iter < numOfValues; iter++) {
        int randNum = getRandomNumber(minNum, maxNum);
        int counter = collatzWrapper(randNum, &cacheHit);
        if(!cacheHas(randNum) && cacheType != "none") {
            if(cacheType == "LRU") cacheInsert(randNum, counter);
            else cacheRR(randNum, counter);
        }

        printf("Random Number:%10d, Steps: %10d\n", randNum, counter);
        fprintf(fpt, "%d, %d\n", randNum, counter);
    }
    float cache = (cacheHit / (float)numOfValues) * 100.f;
    printf("Cache Hit: %.2f\%\n", cache);
    fprintf(fpt, "Cache Hit, %.2f\%\n", cache);
    printCache();
    cacheFree();
    return 0;
}

int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int collatzConject(int x) {
    if (x % 2 == 0)
        return x / 2;
    else
        return 3 * x + 1;
}

// Change wrapper to have the method selected (none, LRU, RR)
int collatzWrapper(int num, int* hits) {
    int counter = 0;

    while (num != 1) {
        if (cacheHas(num)) {
            printf("Cache hit!\n");
            *hits += 1;
            return counter + cacheGetValue(num);
        }
        num = ptr(num);
        counter++;
    }

    return counter;
}
