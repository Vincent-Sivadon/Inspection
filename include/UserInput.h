/* Header for user input function */

#pragma once

/*
 * Ask and process user input
 * state 0 means the executable hasn't start running yet 
 * state 1 means the executable ran and stopped from signal
 */
void getInput(int state);