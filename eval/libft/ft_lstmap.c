/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:36:32 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/13 11:20:11 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_argnode	*ft_lstmap(t_argnode *lst, void *(*f)(void *), void (*del)(void *))
{
	t_argnode	*newlist;
	t_argnode	*newnode;

	if (!lst || !f)
		return (NULL);
	newnode = ft_lstnew(f(lst->content));
	if (!newnode)
	{
		return (NULL);
	}
	lst = lst->next;
	newlist = newnode;
	while (lst)
	{
		newnode->next = ft_lstnew(f(lst->content));
		if (!(newnode->next))
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		lst = lst->next;
		newnode = newnode->next;
	}
	return (newlist);
}
