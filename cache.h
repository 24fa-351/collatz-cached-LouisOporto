#ifndef CACHE_H
#define CACHE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


void cacheInit(int size);
bool cacheHas(int key);
void cacheFree();
void cacheInsert(int key, int value); // LRU
void cacheRR(int key, int value); // RR
int cacheGetValue(int key);


// Function to resort array and remove least recently used. called functions get resorted back to the top

// helper function
void printCache();

#endif
