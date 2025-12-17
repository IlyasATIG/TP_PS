#include "question_2.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024
#define BYE_MSG "Bye bye...\n" // Bye message

void execute_one_simple_command() {

    // Stock and read the characters
    char buffer_command_line[MAX_LINE_SIZE] = {0};
    int nb_char_read = read(STDIN_FILENO, buffer_command_line, MAX_LINE_SIZE);

    // Remove the character of the line break "\n"
    buffer_command_line[nb_char_read-1]=0;

    // Security if we have an error (=-1) or Crtl+D (=0)
    if (nb_char_read <= 0) {
        if (nb_char_read == 0) exit(EXIT_SUCCESS); 
        return; 
    }

    // If we are in Son process
    if (fork()==0){
        execlp(buffer_command_line, buffer_command_line, NULL);
        exit(EXIT_FAILURE);
    }

    /* Q4 
    int status;
    // Waiting for the Son
    wait(&status);

    if(WIFSIGNALED(status)){
        printf("Killed by %d \n", WTERMSIG(status));
    }
    */
}