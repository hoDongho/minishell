/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:15:35 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/18 12:46:48 by nhwang           ###   ########.fr       */
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
		return (NULL);
	while (s[i])
	{
		st[i] = s[i];
		i++;
	}
	st[i] = s[i];
	return (st);
}
