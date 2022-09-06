/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:44:30 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/18 12:48:22 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;
	size_t	len;

	if (!f || !s)
		return ;
	i = 0;
	len = ft_strlen(s);
	if (f && s)
	{
		while (i < len)
		{
			f(i, s);
			i++;
			s++;
		}
	}
}
