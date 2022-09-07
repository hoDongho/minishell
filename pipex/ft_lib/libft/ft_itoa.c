/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:54:07 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:19:04 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	checklen(int n)
{
	size_t	nlen;

	nlen = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		nlen++;
	}
	return (nlen);
}

static size_t	checklen_unsigned(unsigned int n)
{
	size_t	nlen;

	nlen = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		nlen++;
	}
	return (nlen);
}

char	*ft_itoa(int n)
{
	char		*new;
	long long	nb;
	size_t		len;

	len = checklen(n);
	nb = n;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	new = ft_calloc((len + 1), sizeof(char));
	if (new == 0)
		return (0);
	while (len > 0)
	{
		len--;
		new[len] = nb % 10 + 48;
		nb = nb / 10;
		if (len == 0 && n < 0)
			new[len] = '-';
	}
	return (new);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char				*new;
	unsigned long long	nb;
	size_t				len;

	len = checklen_unsigned(n);
	nb = n;
	new = ft_calloc((len + 1), sizeof(char));
	if (new == 0)
		return (0);
	while (len > 0)
	{
		len--;
		new[len] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (new);
}
