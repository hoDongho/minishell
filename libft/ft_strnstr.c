/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:32:20 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/12 18:43:51 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*dst;
	char	*src;
	size_t	lendst;
	size_t	lensrc;
	size_t	min;

	dst = (char *)big;
	src = (char *)little;
	lendst = ft_strlen(big);
	lensrc = ft_strlen(little);
	min = lendst;
	if (min > len)
		min = len;
	lendst = 0;
	while (lensrc + lendst <= min)
	{
		if (!ft_strncmp(dst + lendst, little, lensrc))
			return (dst + lendst);
		lendst++;
	}
	return (NULL);
}
