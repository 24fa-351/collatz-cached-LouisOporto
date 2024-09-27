#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int collatzConject(int);
int collatzWrapper(int);

int main(int argc, char* argv[]) {
    // Three arguments values
    // N = number of values
    // MIN = lowest value
    // MAX = highest value

    int N = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);

    FILE *fpt;
    fpt = fopen("output.csv", "w+");
    fprintf(fpt, "Number, Steps\n");

    // Generate N number of random values
    srand(time(NULL));
    for(int iter = 0; iter < N; iter++) {
        int randNum = 0;
        int counter = 0;
        do {
            randNum = rand() % MAX;
        } while(randNum < MIN);

        int temp = randNum;
        while(temp != 1 ) {
            temp = collatzConject(temp);
            counter++;
        }

        printf("Random Number:%d\n", randNum);
        printf("Steps:%d\n", counter);
        fprintf(fpt, "%d, %d\n", randNum, counter);
    }

    return 0;
}

int collatzConject(int x) {
  if(x % 2 == 0) return x / 2;
  else return 3 * x + 1;
}

// // Goal
// // Returns number of steps (int)
// int collatzWrapper(int value) {}
