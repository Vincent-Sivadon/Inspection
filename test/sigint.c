#include <signal.h>
#include <stdio.h>

#define GLOBALVAR
#define GLOBALVAR2
#define GLOBALVAR3
#define GLOBALVAR4

int func()
{
    raise(SIGINT);
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
    func();
    func2();
    func3();
    func4();
    
    return 0;
}
