#include "Constructor.h"

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void plop(int sig, siginfo_t *info, void *ctx)
{
	printf("\nSIGINT :'(\n");

    kill(getpid(), SIGKILL);
}

/* Setting up Signal Handler */
// to complete

/* Dynamic Library Constructor */
static void lib_init(void) {
	struct sigaction act;

	memset(&act, 0, sizeof(struct sigaction));

	act.sa_sigaction = plop;

	if( sigaction(SIGINT, &act, NULL) )
		perror("sigaction");

    return;
}
