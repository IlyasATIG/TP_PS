#include "interface.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void display_welcome_prompt() {
    write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));
}


void display_prompt() {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

void print_status(int status, long elapsed_ms) {
    
    // Buffer to prepare the message
    char msg[100];
    int len;

    // Analysis of the return code

    // If natural death
    if (WIFEXITED(status)) {
        // Normal case (ls, date)
        int code = WEXITSTATUS(status);
        len = sprintf(msg, "[exit:%d|%ldms]\n", code, elapsed_ms);
        write(STDOUT_FILENO, msg, len);
    } 
    // If the command is killed by something
    else if (WIFSIGNALED(status)) {
        // Signal case (kill, ctrl+c)
        int sig = WTERMSIG(status);
        len = sprintf(msg, "Killed by %d in %ldms\n", sig, elapsed_ms);
        write(STDOUT_FILENO, msg, len);
    }
}

void exit_detected(char *command){
    // If the command is "exit"
    if (strcmp(command, "exit") == 0) {
        write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
        exit(EXIT_SUCCESS);
    }
}