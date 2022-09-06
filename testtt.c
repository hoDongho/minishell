#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>


// size_t	ft_checkblock(char const *s, char c)
// {
// 	char const	*st;
// 	int			swit;
// 	size_t		size;

// 	size = 0;
// 	swit = 1;
// 	st = s;
// 	while (*st)
// 	{
// 		if (*st == c)
// 		{
// 			swit = 1;
// 		}
// 		else if (swit == 1)
// 		{
// 			swit = 0;
// 			size++;
// 		}
// 		st++;
// 	}
// 	return (size);
// }

// size_t	ft_retstrcnt(const char *cpy, char c)
// {
// 	size_t		i;
// 	const char	*temp;

// 	i = 0;
// 	temp = cpy;
// 	while (*temp && *temp != c)
// 	{
// 		i++;
// 		temp++;
// 	}
// 	return (i);
// }

// const char	*ft_cpystr(char **ar, const char *cpy, char c, size_t index)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*cpy && *cpy != c)
// 	{
// 		ar[index][i] = *cpy;
// 		cpy++;
// 		i++;
// 	}
// 	ar[index][i] = '\0';
// 	return (cpy);
// }

// int	ft_makearr2(const char *cpy, char c, char **ar, size_t cnt)
// {
// 	size_t		fkcnt;
// 	size_t		swit;
// 	size_t		i;

// 	fkcnt = cnt;
// 	swit = 1;
// 	while (*cpy && fkcnt >= 0)
// 	{
// 		if (*cpy == c)
// 		{
// 			swit = 1;
// 			cpy++;
// 		}
// 		else if (swit == 1)
// 		{
// 			swit = 0;
// 			i = ft_retstrcnt(cpy, c);
// 			ar[cnt - fkcnt] = (char *) ft_calloc(i + 1, sizeof(char));
// 			if (!(ar[cnt - fkcnt]))
// 				return (0);
// 			cpy = ft_cpystr(ar, cpy, c, cnt - fkcnt);
// 			fkcnt--;
// 		}
// 	}
// 	return (1);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	vol;
// 	char	**arr;

// 	if (!s)
// 		return (NULL);
// 	vol = ft_checkblock(s, c);
// 	arr = (char **) ft_calloc(vol + 1, sizeof(char *));
// 	if (!arr)
// 	{
// 		free(arr);
// 		return (NULL);
// 	}
// 	if (!(ft_makearr2(s, c, arr, vol - 1)))
// 	{
// 		free(arr);
// 		return (NULL);
// 	}
// 	arr[vol] = NULL;
// 	return (arr);
// }

int	ft_checkq(char *str)
{
	char	*st;
	int		dchk;
	int		schk;
	int		standard;

	standard = 0; // 1 : single , 2 : double
	st = str;
	dchk = 0;
	schk = 0;
	while (*st)
	{
		if ((*st == '\"' || *st == '\'') && standard == 0)
		{
			if (*st == '\'')
				standard = 1;
			else if (*st == '\"')
				standard = 2;
		}
		if (*st == '\'' && standard == 1)
		{
			schk++;
			if (schk % 2 == 0)
				standard = 0;
		}
		else if (*st == '\"' && standard == 2)
			dchk++;
			if (dchk % 2 == 0)
				standard = 0;
		st++;
	}
	if (standard == 1)
		return (1);
	else if (standard == 2)
		return (2);
	return (0);
}

int	ft_isspace(char c)
{
	if (((c >= 9 && c <=13) || c == 32))///c != 0 &&
		return (1);
	return (0);
}

int	ft_switch(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (ft_isspace(c) == 0 && c != 0)
		return (3); //문자일때 3
	return (0);
}

int	ft_split_util(char *str)
{
	int	i;
	char *st;
	int	swit;
	int cnt;

	cnt = 0;
	swit = 0;
	i = 0;
	st = str;
	while (*st)
	{
		while (*st != 0 && ft_isspace(*st))
		{
			st++;
		}
		if (*st == 0)
			break ;
		if (swit == 0)
		{
			swit = ft_switch(*st);
			if (swit == 3)
			{
				while (*(st + 1) != 0 && ft_switch(*(st + 1)) == 3)
					st++;
				// cnt++;//
				swit = 0;
			}
		}
		else if (swit == ft_switch(*st))
		{
			swit = 0;
			// cnt++;//
		}
		if (ft_switch(*(st + 1)) == 0 && swit == 0)
			cnt++;
		st++;
	}
	return (cnt);
}
// ehco       abc   'def' "abc   d"
// "abc"
// "abc""abc"
// abc"abc"
// "abc"abc
// 'abc'"abc"
// 'abc' "abc"e
// '\0  "\0  a\0  '''a   \0

// char	**ft_split2(char *str)
// {
// 	int	len;

// 	len = ft_split_util(str);
// }

//test:a     b
//1
//test:a bb   c

int main(int argc, char *argv[], char *env[])
{
	char *input;
	char **cc;
	int	i;

	i = 2;
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
		//printf("%d\n",ft_checkq(input)); > 완료
        printf("%d\n",ft_split_util(input));

        if( 0 == strcmp(input, "exit") )
        {
            printf("Bye!\n");
            work = 0;
        }
        if( 0 == strcmp(input, "") )
        {
            printf("I'm readline example\n");
        }
        if( 0 == strcmp(input, "ver") )
        {
            printf("My version is 0.1\n");
        }
		// if( 0 == strncmp(input, "echo", 4))
        // {
		// 	cc=ft_split(input);
		// 	if (strncmp(cc[0], "echo", 5) == 0)
		// 	{
		// 		if (strncmp(cc[1], "-n", 2) == 0 && ft_checksp(*(cc[1] + 2)) == 1)
		// 		{
		// 			while(ft_checksp(*(cc[1] + i)) == 1 && (*(cc[1] + i) != '\0'))
		// 				i++;
		// 			printf("%s", cc[1] + i);
		// 		}
		// 		else
		// 			printf("%s\n", cc[1]);
		// 	}
        //     // printf("%s\n", input);
        // }
        // ...
        // Free input for future use
        free(input);
    }
    return 0;
}

//echo flksdajfl