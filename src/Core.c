#include "Core.h"

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

/* print process information */
void printBasicInfos()
{
    // Get informations
    ppid = getppid();
    gid = getgid();

    // Print them
    printf("Process ID         : %d\n", pid);
    printf("Parent Process ID  : %d\n", ppid);
    printf("Group Process ID   : %d\n", gid);
    fflush(stdout);
}

/* Print the values of category "name" in /proc/[pid]/status */
void getInfo(const char * name)
{
    // Construct /proc/pid/status PATH
    char str_pid[10]; sprintf(str_pid, "%d", pid);  // int to string
    char * str_proc = "/proc/";
    char * str_status = "/status";
    char * status_path = malloc(strlen(str_proc) + strlen(str_pid) + strlen(str_status));
    strcat(status_path, str_proc);
    strcat(status_path, str_pid);
    strcat(status_path, str_status);

    // Read file
    FILE* status_file = fopen(status_path, "r");
    if (!status_file) perror("can't open /proc/[pid]/status");
    char line[100], current_name[10]; char values[20];
    do
    {
        fgets(line, 100, status_file);
        sscanf(line, "%[^:]", current_name);
        memcpy(values, &line[strlen(current_name)+2], 20);
    } while ( strcmp(name,current_name) );

    // Display information
    printf("%s: %s", name, values);
    fflush(stdout);

    // Free memory
    free(status_path);
    fclose(status_file);
}

/* Ask and process user input */
void getInput()
{
    // Get user input
    printf("-> ");
    fflush(stdout);
    scanf(" %s", input);
    
    // Process user input
    unsigned long long i = string_hash(input);
    //printf("hash : %llu\n", i);

    switch (i)
    {
        // RUN
        case RUN:
            break;
        case QUIT:
            break;

        // INFORMATIONS
        case INFO:
            printBasicInfos();
            getInput();
            break;
        case GETPID:
            getInfo("Pid");
            getInput();
            break;
        case GETPPID:
            getInfo("PPid");
            getInput();
            break;
        case GETGID:
            getInfo("Gid");
            getInput();
            break;
        case GETNAME:
            getInfo("Name");
            getInput();
            break;

        case HELP:
            printf("\n===========COMMANDES===========\n\n");
            printf("=> i (donne des informations générales)\n");
            printf("=> run (lance le programme)\n");
            printf("=> quit (quitte le programme)\n");
            printf("=> get* (va cherche l'information * dans /proc/status/, exemple : getname)\n\n");
            printf("===============================\n\n");
            getInput();
            break;

        default:
            printf("This command doesn't exists\n");
            getInput();
            break;
    }

}