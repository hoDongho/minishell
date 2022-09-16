/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:54:54 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/16 12:50:56 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argnode	*ft_new_argnode(char c)
{
	t_argnode	*new;

	new = calloc(1, sizeof(t_argnode));
	if (!new)
		return NULL;
	new->c = c;
	return new;
}

void	ft_push(t_arglist	*arglist, char c)
{
	t_argnode	*tt;
	t_argnode	*new;

	new = ft_new_argnode(c);
	arglist->tail->prev->next = new;
	new->next = arglist->tail;
	new->prev = arglist->tail->prev;
	arglist->tail->prev = new;
	arglist->datasize++;
}

char	*ft_makeword(t_arglist	*arglist)
{
	char	*str;
	char	*st;
	t_argnode	*curr;
	t_argnode	*temp;

	if (arglist->datasize == 0)
		return (NULL);
	st = calloc(arglist->datasize + 1, sizeof(char));
	str = st;
	curr = arglist->head->next;
	while (curr->next)
	{
		*str = curr->c;
		temp = curr;
		curr = curr->next;
		free(temp);
		arglist->datasize--;
		str++;
	}
	arglist->head->next = arglist->tail;
	arglist->tail->prev = arglist->head;
	return (st);
}

char	*ft_chgenv(char *st, t_arglist *arglist, t_envlist *envlist, t_cmdlist *cmdlist, int type)
{
	char	*key;
	int		i;
	t_envnode	*curr;
	char	*st_val;
	char	*str;

	i = 0;
	st++;
	if (ft_switch(*st) != 3)
	{
		ft_push(arglist, '$');
		return (st);
	}
	else
	{
		// if (*st == '?')
		while(ft_switch(st[i]) == 3)
		{
			if (st[i] == '$' || ft_isalnum(st[i]) == 0)
				break ;
			i++;
		}
		key = calloc(i + 1, sizeof(char));
		memmove(key, st, i);
		curr = envlist->head;
		while (curr->next->next)
		{
			curr = curr->next;
			if (strcmp(key, curr->key) == 0)
			{
				st_val = curr->val;
				if (!st_val)
					break ;
				while (*st_val)
				{
					if (ft_isspace(*st_val) == 1 && type == 3)
					{
						str = ft_makeword(arglist);
						ft_pushcmd(cmdlist, str, type);
						while(*st_val && ft_isspace(*st_val) == 1)
							st_val++;
					}
					ft_push(arglist, *st_val);
					st_val++;
				}
				break ;
			}
		}
		free(key);
		st = st + i;
	}
	return (st);
}

void	ft_pushcmd(t_cmdlist *cmdlist, char *str, int type)
{
	t_cmdnode	*new;
	t_cmdnode	*prev;
	char		*new_str;

	if (type==3 && str==0)
		return ;
	new_str = str;
	if (str == 0)
		new_str = calloc(1, sizeof(char));
	new = calloc(1, sizeof(t_cmdnode));
	// if(!new)
	// 	return (NULL); print 함수 만들고 exit 쓰기
	new->str = new_str;
	prev = cmdlist->tail->prev;
	new->next = cmdlist->tail;
	new->prev = prev;
	prev->next = new;
	cmdlist->tail->prev = new;
	cmdlist->datasize++;
}

void	ft_removeq2(t_par_mdata *par_mdata, int len)
{
	char	*st;
	char	*str;
	int		i;
	int		swit;
	int		type;
	t_cmdnode *curr;

	i = 0;
	swit = 0;
	st = par_mdata->origin;
	while(len > i)
	{
		type = 0;
		while(*st)
		{
			if (ft_switch(*st) == 0 && swit == 0)
			{
				st++;
				continue;
			}
			if (ft_switch(*st) == 3)
			{
				swit = ft_switch(*st);
				if (!type)
					type = swit;
				while (*st != 0 && ft_switch(*st) == swit)
				{
					if (*st == '$')
						st = ft_chgenv(st, par_mdata->arglist, par_mdata->envlist, par_mdata->cmdlist, type);
					else
					{
						ft_push(par_mdata->arglist, *st);
						st++;
					}
				}
				swit = 0;
			}
			else if (ft_switch(*st) == 1 || ft_switch(*st) == 2)
			{
				swit = ft_switch(*st);
				if (!type)
					type = swit;
				st++;
				while (*st != 0 && ft_switch(*st) != swit)
				{
					if (swit == 2 && *st == '$')
						st = ft_chgenv(st, par_mdata->arglist, par_mdata->envlist, par_mdata->cmdlist, type);
					else
					{
						ft_push(par_mdata->arglist, *st);
						st++;
					}
				}
				swit = 0;
				st++;
			}
			if (ft_switch(*st) == 0)
				break ;
		}
		str = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, str, type);
		i++;
	}
	// curr = par_mdata->cmdlist->head->next;
	// while(curr->next)
	// {
	// 	printf("%s\n",curr->str);
	// 	curr=curr->next;
	// }
	// printf("\n\n\n\n\n");
}






