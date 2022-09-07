/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:34:33 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:24:54 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	di;
	size_t	si;
	size_t	dlen;
	size_t	slen;

	di = 0;
	si = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize < dlen + 1)
		return (dstsize + slen);
	while (dst[di] != 0)
		di++;
	while (src[si] != 0 && si + dlen + 1 < dstsize)
	{
		dst[di] = src[si];
		di++;
		si++;
	}
	if (dstsize != 0 || dstsize > dlen)
		dst[di] = 0;
	return (dlen + slen);
}
