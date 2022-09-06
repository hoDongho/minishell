#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *env[])
{
	char	*str;

	while (1)
	{
		str = readline("minishell> ");
		if (str == 0)
			break ;
		if (strcmp("echo", str) == 0)
		{
			printf("%s\n", str);
		}
		add_history(str);
		free(str);
		str = 0;
	}
}
