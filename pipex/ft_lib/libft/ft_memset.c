/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:55:10 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:22:52 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*btmp;
	unsigned char	ctmp;
	size_t			i;

	btmp = (unsigned char *)b;
	ctmp = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		*(btmp + i) = ctmp;
		i++;
	}
	return (b);
}
