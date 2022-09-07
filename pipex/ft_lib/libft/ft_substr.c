/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:20:55 by dhyun             #+#    #+#             */
/*   Updated: 2022/07/11 17:25:52 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	new = 0;
	if (s == 0)
		return (new);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new = ft_calloc(len + 1, sizeof(char));
	if (new == 0)
		return (0);
	if (start <= ft_strlen(s))
		ft_memmove(new, s + start, len);
	return (new);
}
