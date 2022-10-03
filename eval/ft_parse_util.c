/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:10:32 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 15:10:53 by dhyun            ###   ########seoul.kr  */
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
