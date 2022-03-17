#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	double * tab = malloc(10);
	free(tab);
	raise(SIGINT);
	while(1)
	{
		sleep(1);
	}
    return 0;
}
