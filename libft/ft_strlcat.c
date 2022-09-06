/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:34:08 by nhwang            #+#    #+#             */
/*   Updated: 2021/12/14 18:18:36 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*stdst;
	const char	*stsrc;
	size_t		i;
	size_t		dstlen;
	size_t		srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	stdst = dst;
	stsrc = src;
	i = 0;
	if (dstlen > size)
		return (size + srclen);
	while (*stdst)
		stdst++;
	while (*stsrc && dstlen + 1 + i < size)
	{
		*stdst = *stsrc;
		stdst++;
		stsrc++;
		i++;
	}
	*stdst = '\0';
	return (dstlen + srclen);
}
