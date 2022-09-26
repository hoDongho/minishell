/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:01:51 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/26 17:35:06 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checknum(char str)
{
	if ((48 <= str) && (str <= 57))
		return (1);
	return (0);
}

int	ft_checksp(char str)
{
	if ((str == ' ') || ((9 <= str) && (str <= 13)))
		return (1);
	else
		return (0);
}

int	ft_checkbuho(char str)
{
	if (str == '+')
		return (1);
	if (str == '-')
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *s)
{
	const char	*st;
	int			buho;
	long long	num;

	num = 0;
	st = s;
	buho = 1;
	while (*st && ft_checksp(*st))
		st++;
	if (*st && (ft_checkbuho(*st) != 0))
	{
		buho = ft_checkbuho(*st);
		st++;
	}
	while (*st && ft_checknum(*st))
	{
		if (num * buho > 9223372036854775807)
			return (-1);
		if (num * buho < -9223372036854775807 - 1)
			return (0);
		num = (num * 10) + ((int)(*st) - 48);
		st++;
	}
	return ((int)num * buho);
}
