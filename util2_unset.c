/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:57 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/26 16:10:38 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_popenv(char *tkey, t_envlist *envlist)
{
	t_envnode	*curr;
	t_envnode	*next;
	t_envnode	*prev;
	t_envnode	*temp;
	size_t		size;

	curr = envlist->head->next;
	size = strlen(tkey);
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
