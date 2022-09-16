/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:30:17 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/16 15:43:29 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pass_word(char *str, int *swit)
{
	while (*(str + 1) != '\0' && ft_switch(*(str + 1)) == WORD)
		str++;
	*swit = 0;
	return (str);
}

int	ft_cnt_word(char *str)
{
	int		swit;
	int		cnt;

	cnt = 0;
	swit = 0;
	while (*str)
	{
		while (*str != 0 && ft_isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		if (swit == 0)
		{
			swit = ft_switch(*str);
			if (swit == WORD)
				str = ft_pass_word(str, &swit);
		}
		else if (swit == ft_switch(*str))
			swit = 0;
		if (ft_switch(*(str + 1)) == SPACE_NULL && swit == 0)
			cnt++;
		str++;
	}
	return (cnt);
}

char	*ft_push_word(t_par_mdata *par_mdata, char *st, int type)
{
	while (*st != '\0' && ft_switch(*st) == WORD)
	{
		if (*st == '$')
			st = ft_chgenv(st, par_mdata, type);
		else
		{
			ft_push(par_mdata->arglist, *st);
			st++;
		}
	}
	return (st);
}

char	*ft_push_quotes(t_par_mdata *par_mdata, char *st, int type, int swit)
{
	while (*st != '\0' && ft_switch(*st) != swit)
	{
		if (swit == D_QUOTE && *st == '$')
			st = ft_chgenv(st, par_mdata, type);
		else
		{
			ft_push(par_mdata->arglist, *st);
			st++;
		}
	}
	return (st);
}

char	*ft_push_all(t_par_mdata *par_mdata, char *st, int *type, int *swit)
{
	if (ft_switch(*st) == WORD)
	{
		*swit = ft_switch(*st);
		if (!(*type))
			*type = *swit;
		st = ft_push_word(par_mdata, st, *type);
		*swit = 0;
	}
	else if (ft_switch(*st) == QUOTE || ft_switch(*st) == D_QUOTE)
	{
		*swit = ft_switch(*st);
		if (!(*type))
			*type = *swit;
		st++;
		st = ft_push_quotes(par_mdata, st, *type, *swit);
		*swit = 0;
		st++;
	}
	return (st);
}

void	ft_removeq2(t_par_mdata *par_mdata, int len)
{
	char		*st;
	char		*word;
	int			swit;
	int			type;

	swit = 0;
	st = par_mdata->origin;
	while (len)
	{
		type = 0;
		while (*st)
		{
			if (ft_switch(*st) == SPACE_NULL && swit == 0)
			{
				st++;
				continue ;
			}
			st = ft_push_all(par_mdata, st, &type, &swit);
			if (ft_switch(*st) == SPACE_NULL)
				break ;
		}
		word = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, word, type);
		len--;
	}
}
// t_cmdnode	*curr;
// curr = par_mdata->cmdlist->head->next;
// while(curr->next)
// {
// 	printf("%s\n",curr->str);
// 	curr=curr->next;
// }
// printf("\n\n\n\n\n");

int	ft_parse(t_par_mdata *par_mdata)
{
	int	len;

	len = ft_cnt_word(par_mdata->origin);
	if (len == 0)
		return (1); //에러 처리
	ft_removeq2(par_mdata, len);
	return (0);
}
