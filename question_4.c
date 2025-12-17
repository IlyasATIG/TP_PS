#include "question_4.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 1024
#define BYE_MSG "Bye bye...\n"

void execute_one_simple_command() {
    char buffer_command_line[MAX_LINE_SIZE] = {0};
    
    // Stock and read the characters
    int nb_char_read = read(STDIN_FILENO, buffer_command_line, MAX_LINE_SIZE);

    // Remove the character of the line break "\n"
    buffer_command_line[nb_char_read-1] = '\0';

    // Security if we have an error (=-1) or Crtl+D (=0)
    if (nb_char_read <= 0) {
        if (nb_char_read == 0) {
             write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
             exit(EXIT_SUCCESS); // On doit exit ici car le main est une boucle infinie
        }
        return; 
    }

    // ***************** Q3 : if the command is "exit" ****************
    if (strcmp(buffer_command_line, "exit") == 0) {
        write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
        exit(EXIT_SUCCESS);
    }

    // ***************** Q4 : Displaying return code *****************
    pid_t pid = fork();

    // if Failed of the cloning FATHER and SON
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // if SON
    else if (pid == 0) {
        // SON become the command
        execlp(buffer_command_line, buffer_command_line, (char *)NULL);
        // Command failed
        exit(EXIT_FAILURE);
    } 
    // if FATHER
    else {
        int status;
        wait(&status); // Waiting for the end of the command (SON)

        char msg[100]; // Buffer to prepare the message
        int len;

        // Analysis of the return code
        // If natural death
        if (WIFEXITED(status)) {
            // Normal case (ls, date)
            int code = WEXITSTATUS(status);
            len = sprintf(msg, "[exit:%d]\n", code);
            write(STDOUT_FILENO, msg, len);
        } 
        // If the command is killed by something
        else if (WIFSIGNALED(status)) {
            // Signal case (kill, ctrl+c)
            int sig = WTERMSIG(status);
            len = sprintf(msg, "Killed by %d\n", sig);
            write(STDOUT_FILENO, msg, len);
        }
    }
}