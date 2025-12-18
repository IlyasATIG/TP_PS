#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "command_analysis.h"


void cut_command(char *buffer_command_line, char **argv) {
    int i = 0;

    // First word : name of the command
    argv[i] = strtok(buffer_command_line, " ");

    // Next words : arguments
    while (argv[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        // NULL : strtok continue on the same string
        argv[i] = strtok(NULL, " "); 
    }
    
    // execvp need that the list ends with NULL
    argv[i] = NULL;
}


char *get_redirection_file(char **argv) {
    char *file_to_redirect = NULL;

    // Iterate through arguments to find ">"
    for (int j = 0; argv[j] != NULL; j++) {


        // If we find it
        if (strcmp(argv[j], ">") == 0) {
            
            // The filename is the next word
            file_to_redirect = argv[j+1];
            
            // If no file after ">" : error
            if (file_to_redirect == NULL) {
                const char *err = "Error : no file after >\n";
                write(STDERR_FILENO, err, strlen(err));
                return NULL;
            }

            // Cut the command [name, argument]
            argv[j] = NULL; 
            
            return file_to_redirect;
        }
    }
    return NULL; // No redirection found
}