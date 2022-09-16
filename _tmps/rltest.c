#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int main(void)
{
    char* input, shell_prompt[100];
    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete);
    // while work is not 0 program executes the loop
    int work = 1;
    printf("Commands to use: name, ver, exit \n");
    // loop for working with commands
    while(work) {
        // Build prompt string.
        //#### snprintf(shell_prompt, sizeof(shell_prompt), "your command $ ");
        // Display prompt and read input
        input = readline("test:");
        // Check for EOF.
        if (!input)
            break;
        // Add input to history.
        add_history(input);
        // Command analysis and execution
        if( 0 == ft_strcmp(input, "exit") )
        {
            printf("Bye!\n");
            work = 0;
        }
        if( 0 == ft_strcmp(input, "") )
        {
            printf("I'm readline example\n");
        }
        if( 0 == ft_strcmp(input, "ver") )
        {
            printf("My version is 0.1\n");
        }
        // ...
        // Free input for future use
        free(input);
    }
    return 0;
}