#include <signal.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("Lancement du programme qui va lever un SIGINT");
    raise(SIGINT);
    
    return 0;
}
