#pragma once

#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>

int nMalloc;
int nFree;
int nFiles;

void *malloc(size_t size);
void free(void *ptr);

FILE *fopen(const char *path, const char *mode);
int fclose(FILE * stream);