#include <Inspection/Inspection.h>

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


int main(int argc, char **argv)
{
    // Check inspection call
    if (argc < 2) {
        printf("Usage : %s [binary]\n", argv[0]);
        return 1;
    }

    // Define libinspection.so path
    char * ld_preload = "LD_PRELOAD=";
    char * libPath = getLibPath();
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
