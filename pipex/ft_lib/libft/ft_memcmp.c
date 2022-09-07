/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:23:15 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:22:33 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1tmp;
	const unsigned char	*s2tmp;
	size_t				i;

	s1tmp = (const unsigned char *)s1;
	s2tmp = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*(s1tmp + i) != *(s2tmp + i))
			return (*(s1tmp + i) - *(s2tmp + i));
		i++;
	}
	return (0);
}
