#pragma once

#define _GNU_SOURCE
#include <dlfcn.h>


typedef struct MallocSize {
	unsigned long long byteSize;
	struct MallocSize * next;
} MallocSize;

typedef struct {
	int N;
	MallocSize sizes;
} Nmalloc;


int nMalloc;


void *malloc(size_t size);
void free(void *ptr);