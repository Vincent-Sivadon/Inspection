#include "Constructor.h"
#include "GetInformations.h"
#include "UserInput.h"
#include "Intercept.h"
#include "SignalHandler.h"

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

/* Dynamic Library Constructor */
static void lib_init(void) {
	nMalloc = 0; // inspection loading implies 2 malloc

	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	act.sa_sigaction = terminaisonHandler;
	handlerSetUp(&act);

    // User input (decides to run the prog)
    printf("\n================ Inspection ================\n\n");
    fflush(stdout);
    getInput(0);

    return;
}

/* Dynamic Library Destructor */
static void lib_close(void)
{
	printf("\n------------------------------\n");
	printf("Number of malloc : %d\n", nMalloc);
	printf("Number of free : %d\n", nFree);
	printf("Files not yet closed : %d\n", nFiles);
	printf("------------------------------\n");
	printf("\n==============================================\n\n");
	fflush(stdout);
}