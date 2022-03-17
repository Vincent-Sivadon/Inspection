/* Header for functions called to get and print informations on the executable */

#pragma once

#include <sys/types.h>
#include <stdio.h>

/* Print the values of category "name" in /proc/self/status */
void getStatusInfo(const char * name, const char * message);

/* Read ELF file to get symbol list */
void getSymbolList();

/* Displays Stack Trace */
void getBacktrace();

/* Get linked shared libraries */
void ldd();