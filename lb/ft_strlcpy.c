/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:36 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/11 18:04:05 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		len;
	size_t		i;
	const char	*st;
	char		*stdst;

	st = src;
	stdst = dst;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	i = 0;
	while (*st && ((i + 1) < dstsize))
	{
		*stdst = *st;
		stdst++;
		st++;
		i++;
	}
	*stdst = '\0';
	return (len);
}
