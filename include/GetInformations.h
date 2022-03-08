#pragma once

#include <sys/types.h>

/* Process informations */
pid_t pid;
pid_t ppid;
pid_t gid;

/* print general process informations */
void getGeneralInfos();

/* Print the values of category "name" in /proc/[pid]/status */
void getInfo(const char * name);

/* Print memory usage */
void getMemoryUsage();