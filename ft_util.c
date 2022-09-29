/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:13:51 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 15:29:03 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char	*st1, char *st2)
{
	while ((*st1 != '\0') || (*st2 != '\0'))
	{
		if (*st1 == *st2)
		{
			st1++;
			st2++;
		}
		else
			return (*st1 - *st2);
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (((c >= 9 && c <= 13) || c == 32))
		return (1);
	return (0);
}

int	ft_switch(char c)
{
	if (c == '\'')
		return (QUOTE);
	else if (c == '\"')
		return (D_QUOTE);
	else if (ft_isspace(c) == 0 && c != 0)
		return (WORD);
	return (SPACE_NULL);
}
