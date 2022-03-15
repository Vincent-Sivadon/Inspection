#include "Intercept.h"

#include <stdio.h>
#include <stdlib.h>

void* malloc(size_t size)
{
    static void* (*real_malloc)(size_t) = NULL;
    if (!real_malloc)
        real_malloc = dlsym(RTLD_NEXT, "malloc");

    void *p = real_malloc(size);
    //fprintf(stderr, "malloc\n");
    nMalloc++;

    return p;
}

void free(void * ptr)
{
    static void (*real_free)(void *) = NULL;
    if (!real_free)
        real_free = dlsym(RTLD_NEXT, "free");
    
    real_free(ptr);
    nMalloc--;
    //fprintf(stderr, "free\n");

}


FILE *fopen(const char *path, const char *mode) {
    nFiles++;

    FILE *(*original_fopen)(const char*, const char*);
    original_fopen = dlsym(RTLD_NEXT, "fopen");
    return (*original_fopen)(path, mode);
}

int fclose(FILE * stream) {
    nFiles--;

    int (*original_fclose)(FILE *);
    original_fclose = dlsym(RTLD_NEXT, "fclose");
    return (*original_fclose)(stream);
}