#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

/* hash table for string */
unsigned long string_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

#define INFO 177678
#define RUN 193505114
#define GETPID 6953544158914
#define GETPPID 229466957252050
#define GETGID 6953544149113
#define GETNAME 229466957163974

/* Process informations */
pid_t pid;
pid_t ppid;
pid_t gid;
static char input[10];

/*
    If the library has been installed, than we give the /usr/local/lib path
    Else we assume the user calls inspection from the library folder
*/
char * const getLibPath()
{
    char * installedPath = "/usr/local/lib/libinspection.so";
    char * tmpPath = "./lib/libinspection.so";

    // Check if the file in installation path exists
    if( access( installedPath, F_OK ) == 0 ) {
        return installedPath;
    } else {
        return tmpPath;
    }
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




/* Ask and process user input */
void getInput()
{
    // Get user input
    printf("-> ");
    fflush(stdout);
    scanf(" %s", input);
    
    // Process user input
    unsigned long long i = string_hash(input);
    switch (i)
    {
        // RUN
        case RUN:
            break;

        // INFORMATIONS
        case INFO:
            printBasicInfos();
            getInput();
        case GETPID:
            getInfo("Pid");
            getInput();
        case GETPPID:
            getInfo("PPid");
            getInput();
        case GETGID:
            getInfo("Gid");
            getInput();
        case GETNAME:
            getInfo("Name");
            getInput();

        default:
            printf("This command doesn't exists\n");
            getInput();
    }
}

int main(int argc, char **argv)
{
    // Check inspection call
    if (argc < 2) {
        printf("Usage : %s [binary]\n", argv[0]);
        return 1;
    }

    // PID
    pid = getpid();

    // Define libinspection.so path
    char * ld_preload = "LD_PRELOAD=";
    char * libPath = getLibPath();
    char * env = malloc(strlen(ld_preload) + strlen(libPath));
    strcat(env, ld_preload); strcat(env, libPath);


    // Set up for running the prog with inspection preloaded
    char * binary = argv[1];
    char *const args[] = {binary, NULL};
    char *const envs[] = {env,NULL};


    // User input (decides to run the prog)
    printf("\n--- Inspection ---\n\n");
    getInput();

    // Run prog
    execve(argv[1],args,envs);

    return 0;
}
