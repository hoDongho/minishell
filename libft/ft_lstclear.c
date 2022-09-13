/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:09:24 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/13 11:20:11 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_argnode **lst, void (*del)(void*))
{
	struct s_argnode	*nnext;
	t_argnode			*st;

	st = *lst;
	if (st || lst)
	{
		while (st)
		{
			nnext = (st->next);
			ft_lstdelone(st, del);
			st = nnext;
		}
		*lst = NULL;
	}
}
