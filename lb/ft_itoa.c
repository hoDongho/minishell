/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:06:45 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/12 15:44:00 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findlen(long long n)
{
	int	st;
	int	cnt;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (10);
	if (n < 0)
		n = n * (-1);
	st = 1000000000;
	cnt = 10;
	while (st >= 1)
	{
		if ((n / st) >= 1)
		{
			return (cnt);
		}
		else
		{
			cnt--;
			st = st / 10;
			continue ;
		}
	}
	return (cnt);
}

void	ft_makestr2(char *ans, int max, long long s, int index)
{
	long long	k;

	while (max >= 1)
	{
		k = (s / max);
		ans[index] = k + 48;
		s = (s % max);
		max = (max / 10);
		index++;
	}
	ans[index] = '\0';
}

void	ft_makestr(char *ans, long long n, int min, int len)
{
	int	max;
	int	i;
	int	j;

	i = 0;
	j = 0;
	max = 1;
	if (min)
	{
		ans[i] = '-';
		len--;
		i++;
	}
	while (j + 1 < len)
	{
		max = max * 10;
		j++;
	}
	ft_makestr2(ans, max, n, i);
}

char	*ft_itoa(int n)
{
	char		*ans;
	size_t		len;
	int			min;
	long long	nn;

	nn = (long long)n;
	min = 0;
	len = ft_findlen(n);
	if (nn < 0)
	{
		len = len + 1;
		nn = nn * (-1);
		min = 1;
	}
	ans = (char *) ft_calloc (len + 1, sizeof(char));
	if (!ans)
		return (NULL);
	ft_makestr(ans, nn, min, len);
	return (ans);
}
