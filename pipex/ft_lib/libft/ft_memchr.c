/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:40:50 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:22:26 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*stmp;
	unsigned char	ctmp;
	size_t			i;

	stmp = (unsigned char *)s;
	ctmp = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*(stmp + i) == ctmp)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
