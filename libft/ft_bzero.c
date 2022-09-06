/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:39:13 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/12 11:30:36 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t size)
{
	unsigned char	*c;
	size_t			i;

	c = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		*c = 0;
		c++;
		i++;
	}
}
