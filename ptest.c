#include <stdio.h>

char *ft_tt(char *s)
{
	s++;
	return (s);
}

int main()
{
	char *s;

	s = "hellow";
	s = ft_tt(s);
	printf("%s\n",s);
	return (64);
}
