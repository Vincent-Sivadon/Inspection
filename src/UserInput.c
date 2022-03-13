#include "UserInput.h"

#include "GetInformations.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define INFO 177678
#define HELP 6385292014
#define QUIT 6385632776
#define RUN 193505114
#define GETPID 6953544158914
#define GETPPID 229466957252050
#define GETGID 6953544149113
#define GETNAME 229466957163974
#define GETMEM 6953544155524
#define NM 5863648
#define BT 5863259

static unsigned char input[10];

/* hash table for string */
unsigned long string_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/* Ask and process user input */
void getInput(int state)
{
    int quitLoop = 0;

    while (!quitLoop)
    {
        // Get user input
        printf("(isp) ");
        fflush(stdout);
        scanf(" %s", input);
        
        // Process user input
        unsigned long long i = string_hash(input);
        //printf("hash : %llu\n", i);

        switch (i)
        {
            // RUN
            case RUN:
                if(state == 0) quitLoop = 1;
                if(state == 1) printf("The program has already started, try 'help' for more informations\n");
                break;
            case QUIT:
                exit(0);
                break;

            // INFORMATIONS
            case INFO:
                getGeneralInfos();
                break;
            case GETPID:
                getInfo("Pid");
                break;
            case GETPPID:
                getInfo("PPid");
                break;
            case GETGID:
                getInfo("Gid");
                break;
            case GETNAME:
                getInfo("Name");
                break;
            case GETMEM:
                getMemoryUsage();
                break;
            case NM:
                getSymbolList();
                break;
            case BT:
                if (state == 0) printf("The program hasn't started yet, try 'help' for more informations\n");
                if (state == 1) getBacktrace();
                break;


            case HELP:
                printf("\n===========COMMANDES===========\n\n");
                printf("=> i (donne des informations générales)\n");
                printf("=> run (lance le programme)\n");
                printf("=> quit (quitte le programme)\n");
                printf("=> get* (va cherche l'information * dans /proc/status/, exemple : getname)\n\n");
                printf("===============================\n\n");
                break;

            default:
                printf("This command doesn't exists, try 'help' for more informations\n");
                break;
        }
    }
}