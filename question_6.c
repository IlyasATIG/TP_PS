#include "question_4.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_SIZE 1024
#define BYE_MSG "Bye bye...\n"
#define MAX_ARGS 128

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
    // ***************** Q6 : Cutting of arguments *****************
    // Preparation of the pointer table ["ls", "-l", NULL]
    char *argv[MAX_ARGS]; 
    int i = 0;
    
    // First word : name of the command
    argv[i] = strtok(buffer_command_line, " ");
    
    // Next words : arguments
    while (argv[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        argv[i] = strtok(NULL, " "); // NULL : Continue on the same sentence
    }
    // execvp need that the list ends with NULL
    argv[i] = NULL; 

    // If the user just pressed “Enter” (blank line or only spaces)
    if (argv[0] == NULL) {
        return;
    }

    // Q5 : Start of the chrono
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start); 


    /******** Q6 : DEBUG **********
    for(int k=0; argv[k] != NULL; k++) {
        printf("Argument[%d] : '%s'\n", k, argv[k]);
    }
    */

    // ***************** Q4 : Displaying return code *****************
    pid_t pid = fork();

    // if Failed of the cloning FATHER and SON
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // if SON
    else if (pid == 0) {
        // Change because the buffer take several arguments
        execvp(argv[0], argv);
        
        // Failed
        perror("execvp");
        exit(EXIT_FAILURE);
    } 
    // if FATHER
    else {
        int status;
        wait(&status); // Waiting for the end of the command (SON)

        // Q5 : End of the chrono
        clock_gettime(CLOCK_REALTIME, &end); // we stop the chrono

        // Calcul of the time
        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        
        // Conversion in millisecondes (ms)
        long elapsed_ms = (seconds * 1000) + (nanoseconds / 1000000);

        char msg[100]; // Buffer to prepare the message
        int len;

        // Analysis of the return code
        // If natural death
        if (WIFEXITED(status)) {
            // Normal case (ls, date)
            int code = WEXITSTATUS(status);
            len = sprintf(msg, "[exit:%d | %ldms]\n", code, elapsed_ms);
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
}