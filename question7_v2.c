#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>

#include "interface.h"
#include "command_analysis.h"

// Constants
#define MAX_LINE_SIZE 1024
#define FILE_PERMISSIONS 0666

void execute_one_simple_command();

int main() {

    // Q1 : Welcome message
    display_welcome_prompt();

    while (1) {
        // Display prompt
        display_prompt();
        
        // Execute the code
        execute_one_simple_command();
    }
    return 0;
}

void execute_one_simple_command() {

    char buffer_command_line[MAX_LINE_SIZE];
    char *argv[MAX_ARGS];
    
    // Stock and read the characters
    int nb_char_read = read(STDIN_FILENO, buffer_command_line, MAX_LINE_SIZE);

    // Security if we have an error (=-1) or Crtl+D (=0)
    if (nb_char_read <= 0) {
        if (nb_char_read == 0) {
             write(STDOUT_FILENO, BYE_MSG, strlen(BYE_MSG));
             exit(EXIT_SUCCESS); // On doit exit ici car le main est une boucle infinie
        }
        return; 
    }

    // Remove the character of the line break "\n"
    buffer_command_line[nb_char_read - 1] = '\0'; 

    // Handle "Exit"
    exit_detected(buffer_command_line);

    // Command analysis
    cut_command(buffer_command_line, argv);

    // Empty line
    if (argv[0] == NULL) return; 

    // Handle Redirection 
    char *redirection_file = get_redirection_file(argv); 

    // 5. Time measurement (Start)
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    pid_t pid = fork();

    // Failed
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    // ***** SON *****
    else if (pid == 0) {
        // Apply redirection if a file was found
        if (redirection_file != NULL) {
            int fd = open(redirection_file, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        
        execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    } 
    
    // ***** FATHER *****
    else {
        int status;
        wait(&status);
        
        // Time measurement (End)
        clock_gettime(CLOCK_REALTIME, &end);
        
        // Simplified calculation to have the time in ms
        long elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 + 
                          (end.tv_nsec - start.tv_nsec) / 1000000;

        // 6. Print status prompt 
        print_status(status, elapsed_ms);
    }
}