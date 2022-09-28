/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 14:51:12 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 16:10:13 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dst = (char *) ft_calloc (lens1 + lens2 + 1, sizeof(char));
	if (!(dst))
		exit (1);
	ft_strlcpy (dst, s1, lens1 + 1);
	ft_strlcat (dst, s2, lens1 + lens2 + 1);
	return (dst);
}
