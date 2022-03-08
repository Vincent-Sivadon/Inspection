#include "GetInformations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* print general process informations */
void getGeneralInfos()
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