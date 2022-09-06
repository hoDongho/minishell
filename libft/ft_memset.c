/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:39:10 by nhwang            #+#    #+#             */
/*   Updated: 2021/12/16 12:10:10 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int val, size_t size)
{
	unsigned char	*c;
	size_t			i;

	i = 0;
	c = (unsigned char *)dst;
	while (i < size)
	{
		*c = val;
		c++;
		i++;
	}
	return (dst);
}
