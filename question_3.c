#ifndef ENSEASH_H
#define ENSEASH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define WELCOME_MSG "Welcome to ENSEA Shell (enseash).\nType 'exit' or Ctrl+D to quit.\n"
#define PROMPT "enseash % "
#define BYE_MSG "Bye bye...\n"

// Prototypes
void display_message(const char *msg);
void display_prompt();

#endif
