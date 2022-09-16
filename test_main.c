/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:04:12 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/16 14:08:08 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		{
			dchk++;
			if (dchk % 2 == 0)
				standard = 0;
		}
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
	if (((c >= 9 && c <= 13) || c == 32))
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
	int		i;
	char	*st;
	int		swit;
	int		cnt;

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
				swit = 0;
			}
		}
		else if (swit == ft_switch(*st))
		{
			swit = 0;
		}
		if (ft_switch(*(st + 1)) == 0 && swit == 0)
			cnt++;
		st++;
	}
	return (cnt);
}

int	ft_split2(t_par_mdata *par_mdata)
{
	int	len;

	len = ft_split_util(par_mdata->origin);
	if (len == 0)
		return (1); //에러 처리
	ft_removeq2(par_mdata, len);
	return (0);
}

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
	t_cmdnode	*new;

	new = calloc(1, sizeof(t_cmdnode));
	if (!new)
		return (NULL);
	return (new);
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
	ft_arginit(par_mdata->arglist);
	ft_envinit(par_mdata->envlist);
	ft_cmdinit(par_mdata->cmdlist);
}


t_envnode	*ft_newenv(void)
{
	t_envnode	*new;

	new = calloc(1, sizeof(t_envnode));
	if (!new)
		return (NULL);
	return (new);
}

void ft_set_env(t_envlist *envlist, char **env)
{
	int			i;
	int			cnt;
	char		*str;
	t_envnode		*new;

	i = 0;
	while (env[i])
	{
		str = env[i];
		cnt = 0;
		while (*str)
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
		new->val = strdup(getenv(env[i]));
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
	t_cmdnode	*curr;
	t_cmdnode	*temp;

	curr = cmdlist->head->next;
	while (curr->next)
	{
		temp = curr;
		curr = curr->next;
		free(temp->str);
		free(temp);
	}
	cmdlist->head->next = cmdlist->tail;
	cmdlist->tail->prev = cmdlist->head;
	cmdlist->datasize = 0;
}

int main(int argc, char *argv[], char *env[])
{
	char		*input;
	char		**cc;
	int			i;
	t_par_mdata	par_mdata;

	i = 2;
	ft_init(&par_mdata);
	ft_set_env(par_mdata.envlist, env);
	while (1)
	{
		ft_clearcmd(par_mdata.cmdlist);
		input = readline("test:");
		if (!input)
			break ;
		add_history(input);
		if (!*input)
			continue ;
		par_mdata.origin = input;
		if (ft_split2(&par_mdata) == 1)
			continue ;
		if (strcmp(par_mdata.cmdlist->head->next->str, "echo") == 0)
			ft_echo(par_mdata.cmdlist, par_mdata.envlist);
		else if (strcmp(par_mdata.cmdlist->head->next->str, "pwd") == 0)
			ft_pwd();
		else if (strcmp(par_mdata.cmdlist->head->next->str, "cd") == 0)
			ft_cd(par_mdata.cmdlist, par_mdata.envlist);
		else if (strcmp(par_mdata.cmdlist->head->next->str, "exit") == 0)
			ft_exit(par_mdata.cmdlist, &par_mdata);
		else if (strcmp(par_mdata.cmdlist->head->next->str, "export") == 0)
			ft_export(&par_mdata);
		else if (strcmp(par_mdata.cmdlist->head->next->str, "env") == 0)
			ft_env(par_mdata.envlist, 0);
		else if (strcmp(par_mdata.cmdlist->head->next->str, "unset") == 0)
			ft_unset(&par_mdata);
		free(input);
		printf("\n-----------------------------------------------------------------------\n");
		system("leaks a.out");
		printf("-----------------------------------------------------------------------\n\n");
	}
	return (0);
}
