/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:22:36 by dhyun             #+#    #+#             */
/*   Updated: 2022/07/17 20:16:33 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin_wc(char *s1, char *s2, char c)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = 0;
	if (s1 == 0 && s2 == 0)
		return (new);
	else if (s1 == 0)
		return (ft_strdup(s2));
	else if (s2 == 0)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = ft_calloc(len1 + len2 + 1 + 1, sizeof(char));
	if (new == 0)
		print_error("malloc", 1);
	ft_memmove(new, s1, len1);
	new[len1] = c;
	ft_memmove(new + len1 + 1, s2, len2);
	return (new);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*new;

	new = 0;
	if (s == 0)
		return (new);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new = ft_calloc(len + 1, sizeof(char));
	if (new == 0)
		print_error("malloc", 1);
	if (new == 0)
		return (0);
	ft_memmove(new, s + start, len);
	free(s);
	return (new);
}

int	check_access(char *tmp)
{
	int	ret;

	ret = access(tmp, X_OK);
	if (ret == 0)
	{
		free(tmp);
		return (ret);
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
	{
		free(split[i]);
		split[i] = 0;
		i++;
	}
	free(split);
}

int	check_quote(char *str)
{
	if (ft_strchr(str, '\'') != 0 || ft_strchr(str, '\"') != 0)
		return (0);
	return (1);
}
