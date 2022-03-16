#include "UserInput.h"

#include "GetInformations.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ID 5863474
#define HELP 6385292014
#define QUIT 6385632776
#define RUN 193505114
#define GETPID 193502530
#define GETPPID 6385591378
#define GETGID 193492729
#define GETNAME 6385503302
#define GETMEM 193499140
#define NM 5863648
#define BT 5863259
#define DATA 6385144159
#define LDD 193498009

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

void printHelp()
{
    printf("\n--------------------COMMANDES--------------------\n\n");
    printf("- id (PID, PPID, GID)\n");
    printf("- run\n");
    printf("- quit\n");
    printf("- pid\n");
    printf("- ppid\n");
    printf("- gid\n");
    printf("- mem (memory informations)\n");
    printf("- bt (stack backtrace)\n");
    printf("- nm (symbols)\n");
    printf("- name\n\n");
    printf("---------------------------------------------------\n\n");
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
            case ID:
                getStatusInfo("Pid", "PID");
                getStatusInfo("PPid", "PPID");
                getStatusInfo("Gid", "GID");
                break;
            case GETPID:
                getStatusInfo("Pid", "PID");
                break;
            case GETPPID:
                getStatusInfo("PPid", "PPID");
                break;
            case GETGID:
                getStatusInfo("Gid", "GID");
                break;
            case GETNAME:
                getStatusInfo("Name", "Program name");
                break;
            case GETMEM:
                getStatusInfo("VmPeak", "Virtual memory (peak)    size");
                getStatusInfo("VmSize", "Virtual memory (current) size");
                getStatusInfo("VmData", "Virtual memory (data)    size");
                getStatusInfo("VmStk",  "Virtual memory (stack)   size");
                break;
            case NM:
                getSymbolList();
                break;
            case BT:
                if (state == 0) printf("The program hasn't started yet, try 'help' for more informations\n");
                if (state == 1) getBacktrace();
                break;
            case LDD:
                ldd();
                break;


            case HELP:
                printHelp();
                break;

            default:
                printf("This command doesn't exists, try 'help' for more informations\n");
                break;
        }
    }
}