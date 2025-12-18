#ifndef INTERFACE_H
#define INTERFACE_H

#include <sys/wait.h> 

#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % "
#define BYE_MSG "Bye bye...\n"

// Displays status with time (Q4 + Q5)
void print_status(int status, long elapsed_ms);

// Displays the welcome message and the start (Q1))
void display_welcome_prompt();
void display_prompt();

// Detect if the user enter "exit"
void exit_detected(char *command);

#endif