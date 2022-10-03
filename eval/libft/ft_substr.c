/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:26 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/18 12:48:58 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size || start < 0)
		return (ft_strdup(""));
	if (len <= 0)
		return (ft_strdup(""));
	if (size - start < len)
		len = size - start;
	dst = (char *) ft_calloc(len + 1, sizeof(char));
	if (!(dst))
		return (NULL);
	ft_strlcpy(dst, &s[start], len + 1);
	return (dst);
}
