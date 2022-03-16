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

static void signalHandler(int sig, siginfo_t *info, void *ctx)
{
	char * msg = malloc(60);
	char * addr = malloc(30);

	// Determines wich message to print depending on the signal received
	switch(sig)
	{
		case SIGINT:
			msg = "SIGINT received : program interrupted at\n";
			break;

		case SIGTRAP:
			msg = "SIGTRAP received : program trapped at\n";
			break;
	}

	// Assmebling message
	sprintf(addr,"%p",info->si_addr);
	//strncat(msg, addr, 50);

	// Print message and informations to terminal (printf not recommended)
	write(STDOUT_FILENO, msg, strlen(msg));
	write(STDOUT_FILENO, addr, strlen(addr));
	write(STDOUT_FILENO, "\n", 2);

	// free(msg); seg fault ?
	nMalloc--;
	free(addr);

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

	act.sa_sigaction = signalHandler;

	if( sigaction(SIGINT, &act, NULL) )
		perror("sigaction error");
	if( sigaction(SIGTRAP, &act, NULL) )
		perror("sigaction error");

    // User input (decides to run the prog)
    printf("\n================ Inspection ================\n\n");
    fflush(stdout);
    getInput(0);

    return;
}

static void lib_close(void)
{
	printf("Malloc not yet cleaned : %d\n", nMalloc);
	printf("Files not yet closed : %d\n", nFiles);
	printf("==============================================\n\n");
	fflush(stdout);
}