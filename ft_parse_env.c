/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:40:11 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 14:54:13 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_val_w_space(char *st_val, t_par_mdata *par_mdata, int type)
{
	char		*word;

	if (ft_isspace(*st_val) == 1 && type == WORD)
	{
		word = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, word, type);
		while (*st_val && ft_isspace(*st_val) == 1)
			st_val++;
	}
	return (st_val);
}

void	ft_push_val(char *key, int type, t_par_mdata *par_mdata)
{
	t_envnode	*curr;
	char		*st_val;

	curr = par_mdata->envlist->head;
	while (curr->next->next)
	{
		curr = curr->next;
		if (ft_strcmp(key, curr->key) == 0)
		{
			st_val = curr->val;
			if (!st_val)
				break ;
			while (*st_val)
			{
				st_val = ft_val_w_space(st_val, par_mdata, type);
				if (*st_val)
				{
					ft_push(par_mdata->arglist, *st_val);
					st_val++;
				}
			}
			break ;
		}
	}
}

char	*ft_chg_exit_code(t_par_mdata *par_mdata, char *st)
{
	char	*str;
	int		i;

	str = ft_itoa(g_data.exit_code);
	i = 0;
	while (str[i])
	{
		ft_push(par_mdata->arglist, str[i]);
		i++;
	}
	free(str);
	st++;
	return (st);
}

char	*ft_make_key(int type, t_par_mdata *par_mdata, char *st)
{
	char		*key;
	int			i;

	i = 0;
	while (ft_switch(st[i]) == WORD)
	{
		if (st[i] == '$' || ft_isalnum(st[i]) == 0)
			break ;
		i++;
	}
	key = ft_calloc(i + 1, sizeof(char));
	ft_memmove(key, st, i);
	st = st + i;
	ft_push_val(key, type, par_mdata);
	free(key);
	return (st);
}

char	*ft_chgenv(char *st, t_par_mdata *par_mdata, int swit)
{
	st++;
	if (ft_switch(*st) != WORD)
	{
		ft_push(par_mdata->arglist, '$');
		return (st);
	}
	else
	{
		if (*st == '?')
			st = ft_chg_exit_code(par_mdata, st);
		else
			st = ft_make_key(swit, par_mdata, st);
	}
	return (st);
}
