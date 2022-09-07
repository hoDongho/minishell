/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:45:16 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:24:28 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	begin;
	size_t	end;

	new = 0;
	if (s1 == 0)
		return (new);
	begin = 0;
	end = ft_strlen(s1);
	if (end != 0)
	{
		while (ft_strchr(set, s1[begin]) != 0 && s1[begin] != 0)
			begin++;
		while (ft_strchr(set, s1[end - 1]) != 0 && end > begin)
			end--;
	}
	new = ft_calloc(end - begin + 1, sizeof(char));
	if (new == 0)
		return (0);
	if (begin < end)
		ft_memmove(new, s1 + begin, end - begin);
	return (new);
}
