#include <stdlib.h>
#include "question_1.h"
#include "question_4.h"



//int main() {

    // Q1 : Call of  the function defined in question_1.c
  //  display_welcome_prompt();

    //while (1) {
        // Q2 : Reading et executing the command
      //  execute_one_simple_command();
        

        //display_prompt();
    //}
   // return 0;
//}

int main() {
    display_welcome_prompt();

    while (1) {
        display_prompt(); // Affiche le prompt
        execute_one_simple_command(); // Lit et exécute
    }
    return 0;
}