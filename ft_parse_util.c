/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:10:32 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 15:56:37 by dhyun            ###   ########seoul.kr  */
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
