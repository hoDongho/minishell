/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:43:16 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 15:42:27 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*st;

	if (s == 0)
		return (0);
	st = (char *)s;
	while (*st)
	{
		if (*st == (char)c)
			return (st);
		st++;
	}
	if (*st == (char)c)
		return (st);
	return (0);
}
