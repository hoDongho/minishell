/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:39:05 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/18 12:45:58 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned char	*c;
	unsigned char	*sc;
	size_t			i;

	i = 0;
	c = dst;
	sc = (unsigned char *)src;
	if (c == sc)
		return (NULL);
	while (i < size)
	{
		c[i] = sc[i];
		i++;
	}
	return (dst);
}
