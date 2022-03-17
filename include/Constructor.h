/*
 *  Header for dyanamic constructor and destructor of inspection library
 *  It allows us to set up signal handler and ask for input from user
 */

#pragma once

/*
 *  Dynamic Library Constructor
 *  ---------------------------
 *  signal handler set up
 *  ask for user input
 *  we leave constructor only if user typed "run"
 */
static void __attribute__((constructor)) lib_init(void);


/*
 *  Dynamic Library Destructor
 *  --------------------------
 *  print number of malloc, free, and file oppened
 */
static void __attribute__((destructor)) lib_close(void);