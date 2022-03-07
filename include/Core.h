#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define INFO 177678
#define HELP 6385292014
#define QUIT 6385632776
#define RUN 193505114
#define GETPID 6953544158914
#define GETPPID 229466957252050
#define GETGID 6953544149113
#define GETNAME 229466957163974

/* Process informations */
pid_t pid;
pid_t ppid;
pid_t gid;

void getInfo(const char * name);
void getInput();