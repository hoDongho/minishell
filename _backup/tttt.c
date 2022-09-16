#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *s;

	s="_";
	if (ft_strncmp(s,"_a",2))
		printf("fail\n");
	else
		printf("ok\n");
}