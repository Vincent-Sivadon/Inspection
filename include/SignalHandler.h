/* Header for signal handler */

#pragma once

#include <signal.h>

/* To run when a signal that terminates the program is received and intercepted */
void terminaisonHandler(int sig, siginfo_t *info, void *ctx);

/* Set up wich signals we want to intercept */
void handlerSetUp(struct sigaction *act);