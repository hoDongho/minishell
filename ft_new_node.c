/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:14:49 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 15:56:21 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdnode	*ft_newcmd(void)
{
	t_cmdnode	*new;

	new = ft_calloc(1, sizeof(t_cmdnode));
	if (!new)
		return (NULL);
	return (new);
}

t_envnode	*ft_newenv(void)
{
	t_envnode	*new;

	new = ft_calloc(1, sizeof(t_envnode));
	if (!new)
		return (NULL);
	return (new);
}

t_argnode	*ft_new_argnode(char c)
{
	t_argnode	*new;

	new = ft_calloc(1, sizeof(t_argnode));
	if (!new)
		return (NULL);
	new->c = c;
	return (new);
}
