/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:36:56 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/17 17:40:49 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t				i;
	const unsigned char	*st1;
	const unsigned char	*st2;

	i = 0;
	st1 = (const unsigned char *) str1;
	st2 = (const unsigned char *) str2;
	while ((i < num) && ((*st1 != '\0') || (*st2 != '\0')))
	{
		if (*st1 == *st2)
		{
			st1++;
			st2++;
			i++;
		}
		else
		{
			return (*st1 - *st2);
		}
	}
	return (0);
}
