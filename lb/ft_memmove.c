/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:39:01 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/12 14:08:31 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_makeds1(unsigned char *dst, unsigned char *src, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		dst[i] = src[i];
		i++;
	}
}

void	ft_makeds2(unsigned char *dst, unsigned char *src, size_t num)
{
	size_t	i;

	i = (num - 1);
	while (i >= 0)
	{
		dst[i] = src[i];
		if (i == 0)
			break ;
		i--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	unsigned char	*ds;
	unsigned char	*sc;

	ds = (unsigned char *)dst;
	sc = (unsigned char *)src;
	if (dst == src || num == 0)
		return (dst);
	if (dst < src)
		ft_makeds1(ds, sc, num);
	else
		ft_makeds2(ds, sc, num);
	return (dst);
}
