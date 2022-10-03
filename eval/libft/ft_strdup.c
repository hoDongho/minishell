/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:15:35 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 16:09:28 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*st;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	st = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(st))
		exit (1);
	while (s[i])
	{
		st[i] = s[i];
		i++;
	}
	st[i] = s[i];
	return (st);
}
