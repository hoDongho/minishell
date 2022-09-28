/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:40:52 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 16:13:46 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	*st;

	st = s;
	if (!s || fd < 0)
		return ;
	while (*st)
	{
		if (write(fd, st, 1) < 0)
			exit(1);
		st++;
	}
}
