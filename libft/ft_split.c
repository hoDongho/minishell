/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:14:01 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/18 12:46:35 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_checkblock(char const *s, char c)
{
	char const	*st;
	int			swit;
	size_t		size;

	size = 0;
	swit = 1;
	st = s;
	while (*st)
	{
		if (*st == c)
		{
			swit = 1;
		}
		else if (swit == 1)
		{
			swit = 0;
			size++;
		}
		st++;
	}
	return (size);
}

size_t	ft_retstrcnt(const char *cpy, char c)
{
	size_t		i;	
	const char	*temp;

	i = 0;
	temp = cpy;
	while (*temp && *temp != c)
	{
		i++;
		temp++;
	}
	return (i);
}

const char	*ft_cpystr(char **ar, const char *cpy, char c, size_t index)
{
	size_t	i;

	i = 0;
	while (*cpy && *cpy != c)
	{
		ar[index][i] = *cpy;
		cpy++;
		i++;
	}
	ar[index][i] = '\0';
	return (cpy);
}

int	ft_makearr2(const char *cpy, char c, char **ar, size_t cnt)
{
	size_t		fkcnt;
	size_t		swit;
	size_t		i;

	fkcnt = cnt;
	swit = 1;
	while (*cpy && fkcnt >= 0)
	{
		if (*cpy == c)
		{
			swit = 1;
			cpy++;
		}
		else if (swit == 1)
		{
			swit = 0;
			i = ft_retstrcnt(cpy, c);
			ar[cnt - fkcnt] = (char *) ft_calloc(i + 1, sizeof(char));
			if (!(ar[cnt - fkcnt]))
				return (0);
			cpy = ft_cpystr(ar, cpy, c, cnt - fkcnt);
			fkcnt--;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	vol;
	char	**arr;

	if (!s)
		return (NULL);
	vol = ft_checkblock(s, c);
	arr = (char **) ft_calloc(vol + 1, sizeof(char *));
	if (!arr)
	{
		free(arr);
		return (NULL);
	}
	if (!(ft_makearr2(s, c, arr, vol - 1)))
	{
		free(arr);
		return (NULL);
	}	
	arr[vol] = NULL;
	return (arr);
}
