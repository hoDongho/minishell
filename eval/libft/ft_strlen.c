/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:43 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 15:30:21 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char	*ch;
	size_t		cnt;

	cnt = 0;
	ch = str;
	while (*ch)
	{
		cnt++;
		ch++;
	}
	return (cnt);
}
