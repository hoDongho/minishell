#include "minishell.h"


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
		return (3);
	return (0); //null,공백
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
//   asdf d$ abd
//"   asdf d$ abd"
//    dsaf $ asdf
// "asdf$aaa$asdf"

// "$aaa '$bbb'"
// '$aaa "$bbb"'
//   sadf

// ' $ '
// ' $sadf'

//export sadf = 12345

// " $ " >>> sw == 2 and $ㅁㅏㄴ나고 and
// " $"
// " $asdf"
// " $sadf" >>> " 12345" 함수의 인자(swit)의 입장에서 바라보면 뒤에 인자 null이면 $던지게 해주면 될듯

//   $
//   $sadf

// '\0  "\0  a\0  '''a   \0

//ft_init_cmdlist()

char	**ft_split2(t_par_mdata *par_mdata)
{
	int	len;
	char **ans;
	len = ft_split_util(par_mdata->origin);
	ans = calloc (len + 1, sizeof(char *));
	if (!ans)
		return (NULL);//
	ft_removeq2(par_mdata, ans, len);
	//init
	// while(*ans)
	// {
	// 	printf("%s\n", *ans);// free
	// 	ans++; //여기서 푸시
	// }
	return (0);
}

//test:a     b
//1
//test:a bb   c

void ft_arginit(t_arglist *arglist)
{
	arglist->head = ft_new_argnode(0);
	arglist->tail = ft_new_argnode(0);
	arglist->head->next = arglist->tail;
	arglist->tail->prev = arglist->head;
	arglist->datasize = 0;
}

void ft_envinit(t_envlist *envlist)
{
	envlist->head = ft_newenv();
	envlist->tail = ft_newenv();
	envlist->head->next = envlist->tail;
	envlist->tail->prev = envlist->head;
	envlist->datasize = 0;
}

t_cmdnode *ft_newcmd(void)
{
	t_cmdnode *new;

	new = calloc(1,sizeof(t_cmdnode));
	if (!new)
		return (NULL);
	return new;
}

void ft_cmdinit(t_cmdlist *cmdlist)
{
	cmdlist->head = ft_newcmd();
	cmdlist->tail = ft_newcmd();
	cmdlist->head->next = cmdlist->tail;
	cmdlist->tail->prev = cmdlist->head;
	cmdlist->datasize = 0;
}

void ft_init(t_par_mdata *par_mdata)
{
	par_mdata->arglist = calloc (1, sizeof(t_arglist));
	par_mdata->envlist = calloc (1, sizeof(t_envlist));
	par_mdata->cmdlist = calloc (1, sizeof(t_cmdlist));
	//cmdlist추가하기랑 null
	ft_arginit(par_mdata->arglist);
	ft_envinit(par_mdata->envlist);
	ft_cmdinit(par_mdata->cmdlist);
}


t_envnode	*ft_newenv(void)
{
	t_envnode	*new;

	new = calloc(1, sizeof(t_envnode));
	if (!new)
		return (NULL);//
	return (new);
}

void ft_set_env(t_envlist *envlist, char **env)
{
	int			i;
	int			cnt;
	char		*str;
	t_envnode		*new;

	i = 0;
	while(env[i])
	{
		str = env[i];
		cnt = 0;
		while(*str)
		{
			if (*str == '=')
				break ;
			cnt++;
			str++;
		}
		str = 0;
		str = calloc(cnt + 1, sizeof(char));
		memmove(str, env[i], cnt);
		new = ft_newenv();
		new->key = str;
		new->val = getenv(env[i]);
		envlist->tail->prev->next = new;
		new->next = envlist->tail;
		new->prev = envlist->tail->prev;
		envlist->tail->prev = new;
		envlist->datasize++;
		// printf("env : %s\n", env[i]);
		// printf("key : %s\n", new->key);
		// printf("val : %s\n\n", new->val);
		i++;
	}
}

void	ft_clearcmd(t_cmdlist *cmdlist)
{
	t_cmdnode *curr;
	t_cmdnode *temp;

	curr = cmdlist->head->next;
	while(curr->next)
	{
		temp = curr;//
		curr = curr->next;
		free(temp->str);
		free(temp);
	}
	cmdlist->head->next = cmdlist->tail;
	cmdlist->tail->prev = cmdlist->head;
	cmdlist->datasize = 0; //9.14 nhwang 수정
}

int main(int argc, char *argv[], char *env[])
{
	char *input;
	char **cc;
	int	i;
	t_arglist	arglist; //
	t_envlist	envlist; //
	t_par_mdata	par_mdata;
	t_envnode	*test;///test

	i = 2;
    int work = 1;

	ft_init(&par_mdata); /// metadata관련된 것.  cmdlist까지 추가로 해줘야함
	ft_set_env(par_mdata.envlist, env); // envinit 만 분리해서 전체 init이랑 합침 // s_cmdlist
    while(work) {
		ft_clearcmd(par_mdata.cmdlist);
        input = readline("\ntest:");
        if (!input)
            break;
        add_history(input);
		//printf("%d\n",ft_checkq(input)); > 완료
        // printf("%d\n",ft_split2(input));
		par_mdata.origin = input;
		ft_split2(&par_mdata);
		//printf("bf export str : %s\n", par_mdata.cmdlist->head->next->next->str);
		//ft_export(&par_mdata);
		ft_unset(&par_mdata);
		test = par_mdata.envlist->head->next;
		while(test->next)
		{
			printf("%s=%s\n",test->key,test->val);
			test=test->next;
		}
		free(input);
    }
    return 0;
}