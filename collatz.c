#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #define MAX 1000

int collatzConject(int);
int collatzWrapper(int);
int getRandomNumber(int, int);

// From memo now remember how to use it
typedef int (*collatzFunc)(int);
collatzFunc ptr;

/* TODO LIST
1. DONE - Build a wrapper around the core function
2. TODO - Program arguments that specify cache policy (none, LRU, x) and cache size
3. TODO - Implement LRU cache last CWID is 8 so RR (Random Replacement)
4. TODO - Report Cache hit % in output.csv
5. TODO - Determine smallest cache size for (N=10000, MIN=1, MAX=500000) 30% cache hit
Or multiply N by 5
6. TODO - Do this for both cache types
7. TODO - Extra Credit: Implement ARC (check it one more later)
*/

int main(int argc, char* argv[]) {
    // Five arguments values
    // numOfValues = number of values
    // minNum = lowest value
    // maxNum = highest value
    // cacheType = ("none", "LRU", "Random Replacement")
    // cacheSize = size of cache (int)

    int numOfValues;
    int minNum;
    int maxNum;
    char* cacheType;
    int cacheSize;
    //char* cacheType = argv[4];
    //int cacheSize = atoi(argv[5]);

    if (argc < 3
        || sscanf(argv[1], "%d", &numOfValues) == 0
        || sscanf(argv[2], "%d", &minNum) == 0
        || sscanf(argv[3], "%d", &maxNum) == 0) {
        printf("Invalid input: ./collatz.exe <numOfValues> <minNum> <maxNum>");
        return(1);
    }

    // Output to .csv file
    FILE* fpt;
    fpt = fopen("output.csv", "w+");
    fprintf(fpt, "Number, Steps\n");

    // Initialize wrapper
    ptr = collatzConject;
    srand(time(NULL));

    // Generate N number of random values
    for (int iter = 0; iter < numOfValues; iter++) {
        int randNum = getRandomNumber(minNum, maxNum);
        int counter = collatzWrapper(randNum);

        printf("Random Number:%10d, Steps: %10d\n", randNum, counter);
        fprintf(fpt, "%d, %d\n", randNum, counter);
    }

    printf("Output saved to output.csv");

    return 0;
}

int getRandomNumber(int min, int max) { return rand() % (max - min + 1) + min; }

int collatzConject(int x) {
    if (x % 2 == 0)
        return x / 2;
    else
        return 3 * x + 1;
}

// Change wrapper to have the method selected (none, LRU, RR)
int collatzWrapper(int num) {
    int counter = 0;

    while (num != 1) {
        num = ptr(num);
        counter++;
    }

    // need to return cache hit as well.
    return counter;
}
