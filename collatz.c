#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cache.h"

long long collatzConject(long long);
int collatzWrapper(long long, int*, int*);
int getRandomNumber(int, int);

/* TODO LIST
1. DONE - Build a wrapper around the core function
2. DONE - Program arguments that specify cache policy (none, LRU, x) and cache
size
3. DONE - Implement LRU cache last CWID is 8 so RR (Random Replacement)
4. DONE - Report Cache hit % in output.csv
5. DONE - Determine smallest cache size for (N=10000, MIN=1, MAX=500000) 30%
cache hit Or multiply N by 5
6. TODO - Do this for both cache types
*/

int main(int argc, char* argv[]) {
    int numOfValues;
    int minNum;
    int maxNum;
    char* cacheType;
    int cacheSize;

    if (argc < 6 || sscanf(argv[1], "%d", &numOfValues) == 0 ||
        sscanf(argv[2], "%d", &minNum) == 0 ||
        sscanf(argv[3], "%d", &maxNum) == 0 ||
        !(strcmp(argv[4], "none") == 0 || strcmp(argv[4], "LRU") == 0 ||
          strcmp(argv[4], "RR") == 0) ||
        sscanf(argv[5], "%d", &cacheSize) == 0) {
        printf(
            "Invalid input: ./collatz.exe <numOfValues> <minNum> <maxNum> "
            "<cacheType(none, LRU, RR)> <cacheSize>");
        return (1);
    } else
        cacheType = argv[4];

    // Output to .csv file
    FILE* fpt;
    fpt = fopen("output.csv", "w+");
    fprintf(fpt, "Number, Steps\n");

    // set size of cache and type if not none
    if (strcmp(argv[4], "LRU") == 0) cacheInit(cacheSize, 1);
    if (strcmp(argv[4], "RR") == 0) cacheInit(cacheSize, 0);
    srand(time(NULL));
    int cacheHit = 0;
    int cacheCalls = 0;

    // Generate N number of random values
    for (int iter = 0; iter < numOfValues; iter++) {
        int randNum = getRandomNumber(minNum, maxNum);
        int counter = collatzWrapper(randNum, &cacheHit, &cacheCalls);
        if (!cacheHas(randNum) && strcmp(argv[4], "none") != 0)
        {
            cacheInsert(randNum, counter);
            // printCache();
        }

        // printf("Random Number:%10d, Steps: %10d\n======================================\n", randNum, counter);
        printf("%.2f\%\n", iter / (float)numOfValues * 100);
        fprintf(fpt, "%d, %d\n", randNum, counter);
    }

    float cache = (cacheHit / (float)cacheCalls) * 100.f;
    // printf("%.2f\%\n", cache);
    printf("Cache Hit:%.2f\%\n", cache);
    fprintf(fpt, "Cache Hit, %.2f\%\n", cache);
    // printCache();
    cacheFree();
    return 0;
}

// MODIFIED to handle larger random numbers over 2^15
int getRandomNumber(int min, int max) {
    return (rand() + 10 * rand() + 100 * rand() + 1000 * rand()) %
               (max - min + 1) +
           min;
}

long long collatzConject(long long x) {
    if (x % 2 == 0)
        return x / 2;
    else
        return 3 * x + 1;
}

// Change wrapper to have the method selected (none, LRU, RR)
int collatzWrapper(long long num, int* hits, int* calls) {
    int counter = 0;
    while (num != 1) {
        *calls += 1;
        if (cacheHas(num)) {
            // printf("Cache hit!\n");
            *hits += 1;
            return counter + cacheGetValue(num);
        }
        num = collatzConject(num);
        counter++;
        // printf("%d,", num);
    }
    return counter;
}
