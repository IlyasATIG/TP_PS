#ifndef COMMAND_ANALYSIS_H
#define COMMAND_ANALYSIS_H

#define MAX_ARGS 128

// Cut command line to analyze and get the arguments
void cut_command(char *buffer, char **argv);

// Find the redirect file and clean up the command
// This function returns the filename and puts NULL in argv replacing ">"
char *get_redirection_file(char **argv);

#endif