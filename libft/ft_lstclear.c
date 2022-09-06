/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:09:24 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/18 12:45:02 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	struct s_list	*nnext;
	t_list			*st;

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
