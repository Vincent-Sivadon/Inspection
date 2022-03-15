#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	double * tab = malloc(10);
	free(tab);
	while(1)
	{
		sleep(1);
	}
    return 0;
}
