/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:50:44 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/23 15:32:11 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++ != 0)
		i++;
	return (i);
}

char	*ft_strchr2(const char *s, int c)
{
	char	ctmp;
	size_t	i;

	if (s == 0)
		return (0);
	ctmp = (char)c;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == ctmp)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (0);
}

void	*ft_memmove2(void *dst, const void *src, size_t len)
{
	unsigned char		*dtmp;
	const unsigned char	*stmp;
	size_t				i;

	dtmp = (unsigned char *)dst;
	stmp = (const unsigned char *)src;
	i = 0;
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len-- > 0)
			*(dtmp + len) = *(stmp + len);
	}
	else
	{
		while (i < len)
		{
			*(dtmp + i) = *(stmp + i);
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup2(const char *s1)
{
	char	*new;
	size_t	len;

	len = ft_strlen2(s1);
	new = malloc(sizeof(char) * (len + 1));
	if (new == 0)
		return (0);
	ft_memmove2(new, s1, len);
	new[len] = 0;
	return (new);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	else if (s1 == 0)
		return (ft_strdup2(s2));
	else if (s2 == 0)
		return (ft_strdup2(s1));
	len1 = ft_strlen2(s1);
	len2 = ft_strlen2(s2);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new == 0)
		return (0);
	ft_memmove2(new, s1, len1);
	ft_memmove2(new + len1, s2, len2);
	new[len1 + len2] = 0;
	free(s1);
	return (new);
}
