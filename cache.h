#ifndef CACHE_H
#define CACHE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void cacheInit(int size, int type);
bool cacheHas(long long key);
void cacheFree();
void cacheInsert(long long key, int value);
void cacheLRU(long long key, int value); // LRU
void cacheRR(long long key, int value); // RR
int cacheGetValue(long long key);

// helper function
void printCache();

#endif
