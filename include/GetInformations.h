#pragma once

#include <sys/types.h>
#include <stdio.h>

/* Print the values of category "name" in /proc/[pid]/status */
void getStatusInfo(const char * name, const char * message);

/* Read ELF file to get symbol list */
void getSymbolList();

/* */
void getBacktrace();

//int puts(const char * s);
//FILE *fopen(const char *path, const char *mode);

