/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:36:32 by nhwang            #+#    #+#             */
/*   Updated: 2022/01/18 12:25:59 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;

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
