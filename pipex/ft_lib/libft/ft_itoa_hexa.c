/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:54:07 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/03 11:18:24 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	checklen(unsigned long long n, char form)
{
	size_t	nlen;

	nlen = 1;
	while (n / 16 != 0)
	{
		n = n / 16;
		nlen++;
	}
	if (form == 'p')
		nlen += 2;
	return (nlen);
}

size_t	set_ascii(char *new, unsigned long long nb, size_t len, char form)
{
	while (len > 0)
	{
		len--;
		if (nb % 16 < 10)
			new[len] = nb % 16 + 48;
		if (nb % 16 > 9)
			new[len] = nb % 16 + 87;
		nb = nb / 16;
	}
	if (form == 'p')
	{
		new[0] = '0';
		new[1] = 'x';
	}
	return (len);
}

char	*ft_itoa_hexa(unsigned long long n, char form)
{
	char				*new;
	unsigned long long	nb;
	size_t				len;

	len = checklen(n, form);
	nb = n;
	new = ft_calloc((len + 1), sizeof(char));
	if (new == 0)
		return (0);
	len = set_ascii(new, nb, len, form);
	return (new);
}
