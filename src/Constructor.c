#include "Constructor.h"
#include "GetInformations.h"
#include "UserInput.h"

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void plop(int sig, siginfo_t *info, void *ctx)
{
	printf("\nINTERRUPTION\n\n");
	getIspInput();
	exit(0);
}

/* Setting up Signal Handler */
// to complete

/* Dynamic Library Constructor */
static void lib_init(void) {
	struct sigaction act;

	memset(&act, 0, sizeof(struct sigaction));

	act.sa_sigaction = plop;

	if( sigaction(SIGINT, &act, NULL) )
		perror("sigaction error");

	// We need the pid to eventually get to /proc/[pid]/status
	pid = getpid();

    // User input (decides to run the prog)
    printf("\n================ Inspection ================\n\n");
    fflush(stdout);
    getPreIspInput();

    return;
}
