/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:30:17 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 11:29:30 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_push_all(t_par_mdata *par_mdata, char *st, int *swit)
{
	*swit = ft_switch(*st);
	if (ft_switch(*st) == WORD)
		st = ft_push_word(par_mdata, st, *swit);
	else if (ft_switch(*st) == QUOTE || ft_switch(*st) == D_QUOTE)
	{
		st++;
		st = ft_push_quotes(par_mdata, st, *swit);
		st++;
	}
	return (st);
}

void	ft_parse_all(t_par_mdata *par_mdata, int len)
{
	char		*st;
	char		*word;
	int			swit;

	st = par_mdata->origin;
	while (len)
	{
		swit = 0;
		while (*st)
		{
			if (ft_switch(*st) == SPACE_NULL && swit == 0)
			{
				st++;
				continue ;
			}
			st = ft_push_all(par_mdata, st, &swit);
			if (ft_switch(*st) == SPACE_NULL)
				break ;
		}
		word = ft_makeword(par_mdata->arglist);
		ft_pushcmd(par_mdata->cmdlist, word, swit);
		len--;
	}
}

int	ft_parse(t_par_mdata *par_mdata)
{
	int	len;

	if (ft_checkq(par_mdata->origin))
		return (1);
	len = ft_cnt_word(par_mdata->origin);
	if (len == 0)
		return (1); //에러 처리
	ft_parse_all(par_mdata, len);
	t_cmdnode	*curr;
	curr = par_mdata->cmdlist->head->next;
	if(par_mdata->cmdlist->datasize == 0)
		return (1);
	if (ft_check_syntax(par_mdata->cmdlist) != 0)
		return (1);//syntax code ㅍㅣㄹ요
	return (0);
}
	// printf("====\n");
	// while(curr->next)
	// {
	// 	printf("%s\n",curr->str);
	// 	curr=curr->next;
	// }
	// printf("\n\n\n\n\n");
