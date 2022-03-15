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
    pushMalloc(&nMalloc, size);

    return p;
}

void free(void * ptr)
{
    static void (*real_free)(void *) = NULL;
    if (!real_free)
        real_free = dlsym(RTLD_NEXT, "free");
    
    size_t size = sizeof(ptr);
    real_free(ptr);
    rmMalloc(&nMalloc, size);
    //fprintf(stderr, "free\n");

}