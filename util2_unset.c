/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:57 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/29 23:19:10 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_popenv(char *tkey, t_envlist *envlist)
{
	t_envnode	*curr;
	t_envnode	*next;
	t_envnode	*prev;
	t_envnode	*temp;

	curr = envlist->head->next;
	while (curr->next)
	{
		if (ft_strcmp(tkey, curr->key) == 0)
		{
			free(curr->key);
			free(curr->val);
			next = curr->next;
			prev = curr->prev;
			prev->next = next;
			next->prev = prev;
			temp = curr;
			curr = curr->next;
			free(temp);
			continue ;
		}
		curr = curr->next;
	}
}

void	ft_unset(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*curr;

	g_data.exit_code = 0;
	curr = cmdlist->head->next;
	if (cmdlist->datasize == 1)
		return ;
	curr = curr->next;
	while (curr->next)
	{
		if (ft_valid(curr->str, 0) == 0)
		{
			curr = curr->next;
			continue ;
		}
		ft_popenv(curr->str, envlist);
		curr = curr->next;
	}
}
