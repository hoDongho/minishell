/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:13:51 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/16 14:48:08 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char	*st1, char *st2)
{
	int	i;

	while ((*st1 != '\0') || (*st2 != '\0'))
	{
		if (*st1 == *st2)
		{
			st1++;
			st2++;
			i++;
		}
		else
		{
			return (*st1 - *st2);
		}
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
	return (SPACE_NULL); //null,공백
}

int	ft_checkq(char *str)
{
	char	*st;
	int		dchk;
	int		schk;
	int		standard;

	standard = 0; // 1 : single , 2 : double
	st = str;
	dchk = 0;
	schk = 0;
	while (*st)
	{
		if ((*st == '\"' || *st == '\'') && standard == 0)
		{
			if (*st == '\'')
				standard = 1;
			else if (*st == '\"')
				standard = 2;
		}
		if (*st == '\'' && standard == 1)
		{
			schk++;
			if (schk % 2 == 0)
				standard = 0;
		}
		else if (*st == '\"' && standard == 2)
		{
			dchk++;
			if (dchk % 2 == 0)
				standard = 0;
		}
		st++;
	}
	if (standard == 1)
		return (1);
	else if (standard == 2)
		return (2);
	return (0);
}
