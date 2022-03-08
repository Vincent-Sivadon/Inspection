#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    // Check inspection call
    if (argc < 2) {
        printf("Usage : %s [binary]\n", argv[0]);
        return 1;
    }

    // Define libinspection.so path
    char * ld_preload = "LD_PRELOAD=";
    char * libPath = "/usr/local/lib/libinspection.so";
    char * env = malloc(strlen(ld_preload) + strlen(libPath));
    strcat(env, ld_preload); strcat(env, libPath);

    // Set up for running the prog with inspection preloaded
    char * binary = argv[1];
    char *const args[] = {binary, NULL};
    char *const envs[] = {env,NULL};

    // Run prog
    execve(argv[1],args,envs);

    return 0;
}
