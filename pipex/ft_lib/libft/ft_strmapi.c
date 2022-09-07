/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:23:09 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:24:44 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	len;
	size_t	i;

	new = 0;
	if (s == 0)
		return (new);
	len = ft_strlen(s);
	new = ft_calloc(len + 1, sizeof(char));
	if (new == 0)
		return (0);
	i = 0;
	while (s[i] != 0)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	return (new);
}
