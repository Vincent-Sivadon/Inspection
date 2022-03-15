#pragma once

#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdlib.h>

typedef struct Nmalloc {
	size_t N;
	unsigned long long size;
	struct Nmalloc * next;
} Nmalloc;

void pushMalloc(Nmalloc ** nMalloc, size_t size)
{
	Nmalloc * new = (Nmalloc*) malloc(sizeof(Nmalloc));

	new->size = size;
	new->next = (*nMalloc);
	(*nMalloc) = new;
}

void rmMalloc(Nmalloc ** nMalloc, size_t size)
{
	Nmalloc * tmp = *nMalloc;
	Nmalloc * prev;

	// If head holds size
	if (tmp != NULL && tmp->size == size)
	{
		*nMalloc = tmp->next;
		free(tmp);
		return;
	}

	// Search for size, keeping track of the previous nMalloc
    while (tmp != NULL && tmp->size != size) {
        prev = tmp;
        tmp = tmp->next;
    }

	// If we didn't find size
	if (tmp == NULL)
		return;

	//
	prev->next = tmp->next;

	free(tmp);
}

Nmalloc * nMalloc;

void *malloc(size_t size);
void free(void *ptr);