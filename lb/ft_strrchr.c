/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:24:44 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/13 15:57:35 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	char	*st;

	index = ft_strlen(s);
	st = (char *)s;
	while (index > 0)
	{
		if (st[index] == (char)c)
			return ((char *)&st[index]);
		index--;
	}
	if (st[index] == (char)c)
		return ((char *)&st[index]);
	return (NULL);
}
