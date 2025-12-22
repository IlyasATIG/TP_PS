# TP_PS - Date : 2025 - 2026
# Authors : William BEAUSON-MEYER & Ilyas ATIG - 2G2 TD1 TP2
Travaux Pratiques de Programmation_systeme

## Note :
We initially developped the shell incrementally, answering questions 1 through 6 within a linear structure. At **Question 7**,we decided to perform a **refactoring** of the project. We moved specific logic into dedicated functions and split the code into multiple files(.c and .h) to ensure the code remained clean and modular.
The final structure is organized as follows : 
- **main.c ( or question7_v2.c)**: It organizes the reading of the user input and calls the core execution function (execution_one_simple_command)
- **interface.c/h** : Manage all users interactions. This module handles displaying the welcome message, the prompt and the status report of the previous command (exit code, signal and executiion time), as well as detecting exit commands.
- **command_analysis.c/h** : Handles the parsing logic. It is responsible for splitting the raw command line into arguments and detecting redirection symbols (>) to extract filenames.

## Questions 

### Question 1 (interface.c/h)
We used the *write()* system call to display a welcome message upon startup and a simple *enseash %* prompt to await user input.
Using the functions : 
- *void display_welcome_prompt();*
- *void display_prompt();*

### Question 2 (question_2.c/h)
The shell reads user input, creates a child process using *fork()*, and executes commands using *execvp()* (allowing execution of programs in the system PATH).
Using the function : *void execute_one_simple_command()*

### Question 3 (interface.c/h)
We added support for quitting the shell:
- By typing the command **exit** (detected via *strncmp*).
- By using **Ctrl+D** (detected when *read()* returns 0).
Using the function : *void exit_detected(char *command)**

### Question 4 (interface.c/h)
The prompt updates to show the status of the previous command:
- **[exit:0]** for a successful execution.
- **[sign:9]** if the process was killed by a signal. We used the macros *WIFEXITED*, *WEXITSTATUS*, *WIFSIGNALED*, and *WTERMSIG*.
Using the function : *void print_status(int status, long elapsed_ms);*

### Question 5 (interface.c/h)
We measure the execution time of the child process using *clock_gettime(CLOCK_REALTIME)*. The elapsed time is displayed in milliseconds within the prompt
Using the function : *void print_status(int status, long elapsed_ms);*

### Question 6 (command_analysis.c/h)
To support commands with arguments (e.g., **sleep 2**), we implemented a parser using *strtok()*. It splits the input string into an array of arguments (*argv*), which is then passed to *execvp()*.
Using the function : *void cut_command(char *buffer, char **argv);****

### Question 7 (command_analysis.c/h)
The shell supports output redirection and the parser detects the > symbol.
- The file specified is opened (or created) using *open()* with *O_TRUNC* and *O_CREAT*.
- *dup2()* is used in the child process to redirect *STDOUT* to the file.

Using the function : *char *get_redirection_file(char **argv);****

## Final compilation
To **compile** the project, you need to put this line in the shell : 
*gcc -o enseash question7_v2.c interface.c command_analysis.c*

To **run** the shell : 
*./enseash*



