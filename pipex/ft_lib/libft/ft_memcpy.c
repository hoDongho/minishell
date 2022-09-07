/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:56:03 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:22:39 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dtmp;
	const unsigned char	*stmp;
	size_t				i;

	if (dst == src)
		return (dst);
	dtmp = (unsigned char *)dst;
	stmp = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(dtmp + i) = *(stmp + i);
		i++;
	}
	return (dst);
}
