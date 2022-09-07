/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:44:53 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:22:46 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dtmp;
	const unsigned char	*stmp;

	dtmp = (unsigned char *)dst;
	stmp = (const unsigned char *)src;
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			*(dtmp + len) = *(stmp + len);
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
