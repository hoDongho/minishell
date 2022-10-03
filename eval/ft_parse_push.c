/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:57:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 14:52:19 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sep_pipe_redir(t_par_mdata *par_mdata, char *st, int swit)
{
	char	*word;

	if (*st == '|' || ft_is_redir(st) == 1 || ft_is_redir(st) == 2)
	{
		word = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, word, swit);
		ft_push(par_mdata->arglist, *st);
		word = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, word, swit);
		st++;
	}
	else if (ft_is_redir(st) == 3 || ft_is_redir(st) == 4)
	{
		word = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, word, swit);
		ft_push(par_mdata->arglist, *st);
		st++;
		ft_push(par_mdata->arglist, *st);
		word = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, word, swit);
		st++;
	}
	return (st);
}

char	*ft_push_word(t_par_mdata *par_mdata, char *st, int swit)
{
	while (*st != '\0' && ft_switch(*st) == WORD)
	{
		if (*st == '$')
			st = ft_chgenv(st, par_mdata, swit);
		else if (ft_is_redir(st) > 0 || *st == '|')
			st = ft_sep_pipe_redir(par_mdata, st, swit);
		else
		{
			if (*st == '\\' || *st == ';')
			{
				st++;
				if (ft_switch(*st) == SPACE_NULL)
					ft_push(par_mdata->arglist, '\0');
				return (st);
			}
			ft_push(par_mdata->arglist, *st);
			st++;
		}
	}
	return (st);
}

char	*ft_push_quotes(t_par_mdata *par_mdata, char *st, int swit)
{
	while (*st != '\0' && ft_switch(*st) != swit)
	{
		if (swit == D_QUOTE && *st == '$')
			st = ft_chgenv(st, par_mdata, swit);
		else
		{
			ft_push(par_mdata->arglist, *st);
			st++;
		}
	}
	return (st);
}
