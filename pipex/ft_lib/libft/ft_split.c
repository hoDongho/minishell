/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:49:28 by dhyun             #+#    #+#             */
/*   Updated: 2022/06/30 18:54:53 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	totalword(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != 0)
		{
			count++;
			while (s[i] != c && s[i] != 0)
				i++;
		}
	}
	return (count);
}

static size_t	lenword(char const *s, char c, size_t *i)
{
	size_t	len;

	len = 0;
	while (s[*i] != 0 && s[*i] == c)
		(*i)++;
	while (s[*i] != 0 && s[*i] != c)
	{
		(*i)++;
		len++;
	}
	return (len);
}

static void	setword(char const *s, char c, char **new, size_t total)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] != 0 && j < total)
	{
		len = lenword(s, c, &i);
		new[j] = ft_calloc(len + 1, sizeof(char));
		if (new[j] == 0)
		{
			while (j-- > 0)
				free(new[j]);
			free(new);
			return ;
		}
		ft_memmove(new[j], &s[i - len], len);
		j++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	total;

	new = 0;
	if (s == 0)
		return (new);
	total = totalword(s, c);
	new = ft_calloc(total + 1, sizeof(char *));
	if (new == 0)
		return (0);
	setword(s, c, new, total);
	return (new);
}
