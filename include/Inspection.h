#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Dynamic Library Constructor */
static void __attribute__ ((constructor)) lib_init(void);

FILE *fopen(const char *path, const char *mode);