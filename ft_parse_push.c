/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:57:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/22 12:22:33 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_chgenv(char *st, t_par_mdata *par_mdata, int type)
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
		// if (*st == '?')
		// st = ft_make_key(type, par_mdata, st);
		st = ft_make_key(swit, par_mdata, st);
	}
	return (st);
}

// char	*ft_push_word(t_par_mdata *par_mdata, char *st, int type)
char	*ft_push_word(t_par_mdata *par_mdata, char *st, int swit)
{
	char	*word;

	while (*st != '\0' && ft_switch(*st) == WORD)
	{
		if (*st == '$')
			st = ft_chgenv(st, par_mdata, swit);
		else if (*st == '|')
		{
			word = ft_makeword(par_mdata->arglist);
			ft_pushcmd(par_mdata->cmdlist, word, swit);
			ft_push(par_mdata->arglist, *st);
			word = ft_makeword(par_mdata->arglist);
			ft_pushcmd(par_mdata->cmdlist, word, swit);
			st++;
		}
		else
		{
			ft_push(par_mdata->arglist, *st);
			st++;
		}
	}
	return (st);
}

// char	*ft_push_quotes(t_par_mdata *par_mdata, char *st, int type, int swit)
char	*ft_push_quotes(t_par_mdata *par_mdata, char *st, int swit)
{
	while (*st != '\0' && ft_switch(*st) != swit)
	{
		if (swit == D_QUOTE && *st == '$')
			// st = ft_chgenv(st, par_mdata, type);
			st = ft_chgenv(st, par_mdata, swit);
		else
		{
			ft_push(par_mdata->arglist, *st);
			st++;
		}
	}
	return (st);
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
