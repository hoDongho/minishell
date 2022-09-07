/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:42:14 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:24:37 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	nlen;

	i = 0;
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	while (haystack[i] != 0 && i + nlen <= len)
	{
		if (ft_strncmp(haystack + i, needle, nlen) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
