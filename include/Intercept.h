/* Header for interceptions of libc functions */

#pragma once

#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>

// Count for number of malloc, free, and oppened files
int nMalloc;
int nFree;
int nFiles;

/* malloc interception that counts each time it's called */
void *malloc(size_t size);

/* free interception that counts each time it's called */
void free(void *ptr);

/* fopen interception that counts each time it's called */
FILE *fopen(const char *path, const char *mode);

/* fclose interception that decrement the count of file oppened each time it's called */
int fclose(FILE * stream);