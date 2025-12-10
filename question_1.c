#include "question_1.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define WELCOME_PROMPT "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"

void display_welcome_prompt() {

    // Affichage du prompt d'accueil
   int status = write(STDOUT_FILENO, WELCOME_PROMPT, strlen(WELCOME_PROMPT));

   if (status ==-1){
        exit(EXIT_FAILURE);
   }
}