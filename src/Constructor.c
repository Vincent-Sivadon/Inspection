#include "Constructor.h"
#include "GetInformations.h"
#include "UserInput.h"
#include "Intercept.h"

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

static void plop(int sig, siginfo_t *info, void *ctx)
{
	printf("\nINTERRUPTION\n\n");
	getInput(1);
	exit(0);
}

/* Setting up Signal Handler */
// to complete

/* Dynamic Library Constructor */
static void lib_init(void) {
	nMalloc = -2;

	struct sigaction act;

	memset(&act, 0, sizeof(struct sigaction));

	act.sa_sigaction = plop;

	if( sigaction(SIGINT, &act, NULL) )
		perror("sigaction error");

    // User input (decides to run the prog)
    printf("\n================ Inspection ================\n\n");
    fflush(stdout);
    getInput(0);

    return;
}

static void lib_close(void)
{
	printf("Malloc not cleaned : %d", nMalloc);
	printf("\n============================================\n\n");
	fflush(stdout);
}