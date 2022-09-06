/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:08:47 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/14 18:05:46 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_head(char const *s, char const *set)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (i);
}

size_t	ft_tail(char const *s, char const *set)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (s[i] && (i >= 0))
	{
		if (!ft_strchr(set, s[i]))
			return (i);
		if (i != 0)
			i--;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	head;
	size_t	tail;
	size_t	j;
	char	*ans;

	ans = 0;
	if (s1 != 0 && set != 0)
	{
		head = ft_head(s1, set);
		tail = ft_tail(s1, set);
		if (head > tail)
			return (ft_strdup(""));
		ans = (char *) ft_calloc((tail - head) + 2, sizeof(char));
		if (!ans)
			return (NULL);
		j = 0;
		while (s1[head] && head <= tail)
		{
			ans[j] = s1[head];
			head++;
			j++;
		}
		ans[j] = '\0';
	}
	return (ans);
}
