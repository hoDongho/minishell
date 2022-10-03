/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:31:14 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/13 11:20:11 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_argnode **lst, t_argnode *new)
{
	t_argnode	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
