/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:43:16 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/13 15:51:59 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*st;

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
