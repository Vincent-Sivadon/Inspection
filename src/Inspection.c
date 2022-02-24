#include "Inspection.h"

/* Dynamic Library Constructor */
static void lib_init(void) {
    printf("Library preloaded. \n");
    return;
}

FILE *fopen(const char *path, const char *mode) {
    printf("Always failing fopen\n");
    return NULL;
}