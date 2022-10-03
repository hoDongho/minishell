/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:36:16 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/13 11:20:11 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_argnode	*ft_lstnew(void *content)
{
	t_argnode	*new;

	new = (t_argnode *) malloc (sizeof(t_argnode));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
