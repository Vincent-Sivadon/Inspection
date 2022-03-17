/* Implementation of interceptions of libc functions */

#include "Intercept.h"

#include <stdio.h>
#include <stdlib.h>

/* malloc interception that counts each time it's called */
void* malloc(size_t size)
{
    static void* (*real_malloc)(size_t) = NULL;
    if (!real_malloc)
        real_malloc = dlsym(RTLD_NEXT, "malloc");

    void *p = real_malloc(size);
    nMalloc++;

    return p;
}

/* free interception that counts each time it's called */
void free(void * ptr)
{
    static void (*real_free)(void *) = NULL;
    if (!real_free)
        real_free = dlsym(RTLD_NEXT, "free");
    
    real_free(ptr);
    nFree++;
}

/* fopen interception that counts each time it's called */
FILE *fopen(const char *path, const char *mode) {
    nFiles++;

    FILE *(*original_fopen)(const char*, const char*);
    original_fopen = dlsym(RTLD_NEXT, "fopen");
    return (*original_fopen)(path, mode);
}

/* fclose interception that decrement the count of file oppened each time it's called */
int fclose(FILE * stream) {
    nFiles--;

    int (*original_fclose)(FILE *);
    original_fclose = dlsym(RTLD_NEXT, "fclose");
    return (*original_fclose)(stream);
}