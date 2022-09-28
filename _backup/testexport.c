#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	char *input;
	char *cc;
	// char *s = "asdfsd=213432";

	// input=0;
	// if (!input)
	// 	printf("1 input is NULL");
	//input=ft_calloc(7,sizeof(char));
	// if (!input)
	// 	printf("2 input is NULL");
	// printf("%s\n",input);
	// printf("%lu\n",strlen(input));
	// free(input);
	// input = ft_strdup(""); //leak??
	// printf("%s\n",input);
	// printf("%lu\n",strlen(input));
	// strlcat(input, s, 6);
	// printf("%s\n",input);
	// while(*s)
	// {
	// 	if (*s =='=')
	// 		printf("%lu\n",strlen(s));
	// 	s++;
	// }
	input = NULL;
	cc = ft_strdup(input);
	// system("leaks a.out");
    return 0;
}
