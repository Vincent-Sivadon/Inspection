#include <stdio.h>
#include <signal.h>


int main(void) {
    printf("Calling the fopen() function...\n");

    FILE *fd = fopen("test.txt", "r");
    if (!fd) {
        printf("fopen() returned NULL\n");
        return 1;
    }

    raise(SIGINT);    

    fclose(fd);

    return 0;
}