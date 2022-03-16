#include "SignalHandler.h"
#include "UserInput.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* To run when a signal that terminates the program is received and intercepted */
void terminaisonHandler(int sig, siginfo_t *info, void *ctx)
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

		case SIGKILL:
			msg = "SIGKILL received : program killed at\n";
			break;
			
		case SIGILL:
			msg = "SIGILL received : illegal instruction at\n";
			break;
			
		case SIGSEGV:
			msg = "SIGSEGV received : invalid memory reference at\n";
			break;

		case SIGFPE:
			msg = "SIGFPE received : floating point exception at\n";
			break;
	}

	// Assmebling message
	sprintf(addr,"%p",info->si_addr);
	//strncat(msg, addr, 50);

	// Print message and informations to terminal (printf not recommended)
	write(STDOUT_FILENO, msg, strlen(msg));
	write(STDOUT_FILENO, addr, strlen(addr));
	write(STDOUT_FILENO, "\n", 2);

	// free(msg); seg fault for some reason
	free(addr);

	getInput(1);

	exit(0);
}

/* Set up wich signals we want to intercept */
void handlerSetUp(struct sigaction *act)
{
	if( sigaction(SIGINT, act, NULL) )
		perror("sigaction error");
	if( sigaction(SIGTRAP, act, NULL) )
		perror("sigaction error");
	if( sigaction(SIGKILL, act, NULL) )
		perror("sigaction error");
	if( sigaction(SIGILL, act, NULL) )
		perror("sigaction error");
	if( sigaction(SIGSEGV, act, NULL) )
		perror("sigaction error");
	if( sigaction(SIGFPE, act, NULL) )
		perror("sigaction error");
}