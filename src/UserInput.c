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

int pre_inspection = 1;
int inspection = 1;

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

/* Ask and process user input before the program started */
void getPreIspInput()
{
    while (pre_inspection)
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
                pre_inspection = 0;
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
        getPreIspInput();
    }
}

/* Ask and process user input while the program is running */
void getIspInput()
{
    while (inspection)
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
            case RUN:
                printf("The program has already started, try 'help' for more informations\n");
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

            case HELP:
                printf("\n===========COMMANDES===========\n\n");
                printf("=> i (donne des informations générales)\n");
                printf("=> quit (quitte le programme)\n");
                printf("=> get* (va cherche l'information * dans /proc/status/, exemple : getname)\n\n");
                printf("===============================\n\n");
                break;

            default:
                printf("This command doesn't exists, try 'help' for more informations\n");
                break;
        }
        getIspInput();
    }
}