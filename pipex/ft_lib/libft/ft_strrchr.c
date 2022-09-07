/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:15:13 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:24:33 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ctmp;
	size_t	len;

	ctmp = (char)c;
	len = ft_strlen(s);
	if (c == 0)
		return ((char *)&s[len]);
	while (len > 0)
	{
		len--;
		if (s[len] == ctmp)
			return ((char *)&s[len]);
	}
	return (0);
}
