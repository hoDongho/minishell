/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:14:49 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 11:26:54 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdnode	*ft_newcmd(void)
{
	t_cmdnode	*new;

	new = ft_calloc(1, sizeof(t_cmdnode));
	return (new);
}

t_envnode	*ft_newenv(void)
{
	t_envnode	*new;

	new = ft_calloc(1, sizeof(t_envnode));
	return (new);
}

t_argnode	*ft_new_argnode(char c)
{
	t_argnode	*new;

	new = ft_calloc(1, sizeof(t_argnode));
	new->c = c;
	return (new);
}
