#include "question_1.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define FIN_PROMPT "--Fin du Prompt--\n"
void display_welcome_prompt() {

    // Display  the welcome message
   int status = write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));

   if (status ==-1){
        exit(EXIT_FAILURE);
   }
}

void display_prompt() {
    write(STDOUT_FILENO, FIN_PROMPT, strlen(FIN_PROMPT));
}