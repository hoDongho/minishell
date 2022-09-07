/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:38:32 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:24:42 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1tmp;
	const unsigned char	*s2tmp;
	size_t				i;

	s1tmp = (const unsigned char *)s1;
	s2tmp = (const unsigned char *)s2;
	i = 0;
	while ((s1[i] != 0 || s2[i] != 0) && i < n)
	{
		if (s1tmp[i] != s2tmp[i])
			return (s1tmp[i] - s2tmp[i]);
		i++;
	}
	return (0);
}
