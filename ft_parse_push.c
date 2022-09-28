/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:57:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 10:49:27 by nhwang           ###   ########.fr       */
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
		if (*st == '?')
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
		}
		else // st = ft_make_key(type, par_mdata, st);
			st = ft_make_key(swit, par_mdata, st);
	}
	return (st);
}

int	ft_is_redir(char *str)
{
	if (*str=='>')
	{
		if (*(str + 1) != 0 && *(str + 1) == '>')
			return (3);
		else
			return (1); // 하동
	}
	else if (*str == '<')
	{
		if (*(str + 1) != 0 && *(str + 1) == '<')
			return (4);
		else
			return (2); // 특수 문자 등도 2로 판단
	}
	return (0);
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
		else if (ft_is_redir(st)==1 || ft_is_redir(st)==2)
		{
			word = ft_makeword(par_mdata->arglist);
			ft_pushcmd(par_mdata->cmdlist, word, swit);
			ft_push(par_mdata->arglist, *st);
			word = ft_makeword(par_mdata->arglist);
			ft_pushcmd(par_mdata->cmdlist, word, swit);
			st++;
		}
		else if (ft_is_redir(st)==3 || ft_is_redir(st)==4)
		{//얘는 한 줄 더 길어서 함수 만들때 생각
			word = ft_makeword(par_mdata->arglist);
			ft_pushcmd(par_mdata->cmdlist, word, swit);
			ft_push(par_mdata->arglist, *st);
			st++;
			ft_push(par_mdata->arglist, *st);
			word = ft_makeword(par_mdata->arglist);
			ft_pushcmd(par_mdata->cmdlist, word, swit);
			st++;
		}
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
