#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	char *input;
	char **cc;
	int	i;
	t_arglist	arglist; //
	t_envlist	envlist; //
	t_par_mdata	par_mdata;

	i = 2;
    int work = 1;

    while(work) {
        input = readline("test:");
        if (!input)
            break;
        add_history(input);
		printf("$%s$\n",rl_line_buffer);
		rl_redisplay();
		free(input);
    }
    return 0;
}