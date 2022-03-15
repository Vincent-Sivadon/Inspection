#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define GLOBALVAR
#define GLOBALVAR2
#define GLOBALVAR3
#define GLOBALVAR4

int func(int argument)
{
    double tab[1000];
    raise(SIGINT);
    tab[2] = tab[3] + 1;
}
int func2()
{
    raise(SIGSEGV);
}
int func3()
{
    raise(SIGKILL);
}
int func4()
{
    raise(SIGWINCH);
}


int main(int argc, char const *argv[])
{
    double* store = malloc(1000);
    func(2);
    func2();
    func3();
    func4();
    store[56] = 2;
    printf("%lf", store[56]);
    free(store);
    
    return 0;
}
