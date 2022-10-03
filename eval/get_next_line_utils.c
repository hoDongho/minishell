/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:50:44 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 15:35:05 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_gnl(const char *s1)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1);
	new = malloc(sizeof(char) * (len + 1));
	if (new == 0)
		return (0);
	ft_memmove(new, s1, len);
	new[len] = 0;
	return (new);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	else if (s1 == 0)
		return (ft_strdup_gnl(s2));
	else if (s2 == 0)
		return (ft_strdup_gnl(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new == 0)
		return (0);
	ft_memmove(new, s1, len1);
	ft_memmove(new + len1, s2, len2);
	new[len1 + len2] = 0;
	free(s1);
	return (new);
}
