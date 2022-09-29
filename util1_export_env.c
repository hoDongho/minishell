/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_export_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:08:16 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 11:15:22 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_env(t_envlist *envlist, int b)
{
	t_envnode	*curr;

	g_data.exit_code = 0;
	curr = envlist->head->next;
	while (curr->next)
	{
		if (b && ft_strcmp(curr->key, "_") == 0)
		{
			curr = curr->next;
			continue ;
		}
		if (curr->val)
			printf("%s=%s\n", curr->key, curr->val);
		else
			if (b)
				printf("%s\n", curr->key);
		curr = curr->next;
	}
}

int	ft_push_env(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*new;
	t_envnode	*prev;

	new = ft_newenv();
	new->key = ft_strdup(tkey);
	if (tval)
		new->val = ft_strdup(tval);
	prev = envlist->tail->prev;
	new->next = envlist->tail;
	new->prev = prev;
	prev->next = new;
	envlist->tail->prev = new;
	envlist->datasize++;
	return (0);
}

int	ft_findenv(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*curr;
	size_t		size;

	curr = envlist->head->next;
	while (curr->next)
	{
		size = strlen(tkey);
		if (ft_strcmp(tkey, curr->key) == 0)
		{
			if (tval)
			{
				free(curr->val);
				curr->val = ft_strdup(tval);
			}
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_ex_util(char *tkey, char *tval, t_envlist *envlist)
{
	if (ft_findenv(tkey, tval, envlist) == 0)
		ft_push_env(tkey, tval, envlist);
	if (tkey)
		free(tkey);
	if (tval)
		free(tval);
	return (0);
}

int	ft_val_first(char *str, char key)
{
	if (ft_isalpha(*str) == 0)
	{
		if (key == 0)
			write(2, "unset: `", 8);
		else
			write(2, "export: `", 9);
		if (*str)
			write(2, str, ft_strlen(str));
		print_error("': not a valid identifier\n", 1);
		return (0);
	}
	return (1);
}

int	ft_valid(char *str, char key)
{
	if (ft_val_first(str, key) == 0)
		return (0);
	str++;
	while (*str && *str != key)
	{
		if (ft_isalnum(*str) == 0)
		{
			if (key)
				write(2, "export: `", 9);
			else
				write(2, "unset: `", 8);
			if (*str)
				write(2, str, ft_strlen(str));
			print_error("': not a valid identifier\n", 1);
			return (0);
		}
		str++;
	}
	return (1);
}

char	*ft_echk(char *st,int *echk, char *str, char **tkey)
{
	int	size;

	size = 0;
	st = str;
	while (*st)
	{
		size++;//
		if (*st == '=')
		{
			(*tkey) = ft_calloc(size, sizeof(char));
			ft_strlcpy((*tkey), str, size);//
			*echk = 1;
		}
		st++;
		if (*echk)
			break ;
	}
	return (st);
}

int	ft_ex_util2(t_envlist *envlist, t_cmdnode *curr)
{
	char		*st;
	char		*tkey;
	char		*tval;
	int			echk;

	echk = 0;
	st = 0;
	st = ft_echk(st, &echk, curr->str, &tkey);
	tval = NULL;
	if (echk)
	{
		tval = ft_calloc(ft_strlen(st) + 1, sizeof(char));
		ft_strlcpy(tval, st, ft_strlen(st) + 1);
	}
	else
	{
		tkey = ft_calloc(ft_strlen(curr->str) + 1, sizeof(char));
		ft_strlcpy(tkey, curr->str, ft_strlen(curr->str) + 1);
	}
	return (ft_ex_util(tkey, tval, envlist));
}

void	ft_export(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*curr;

	g_data.exit_code = 0;
	curr = cmdlist->head->next;
	if (cmdlist->datasize == 1)
	{
		ft_env(envlist, 1);
		return ;
	}
	curr = curr->next;
	while (curr->next)
	{
		if (ft_valid(curr->str, '=') == 0)
		{
			curr = curr->next;
			continue ;
		}
		ft_ex_util2(envlist, curr);
		curr = curr->next;
	}
}

///////
	///////test ft_export
	// test = par_mdata->envlist->head->next;
	// while(test->next)
	// {
	// 	printf("%s=%s\n",test->key,test->val);
	// 	test=test->next;
	// }
	// printf("\n--------cmd--------\n\n");
	// printf("input: %s\n\n", par_mdata->origin);
	// t_cmdnode *test2;
	// test2 = par_mdata->cmdlist->head->next;
	// while(test2->next)
	// {
	// 	printf("%s\n",test2->str);
	// 	test2=test2->next;
