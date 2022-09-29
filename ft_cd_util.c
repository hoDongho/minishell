/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:58:44 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 21:08:51 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_val(t_envlist *envlist, char *key)
{
	t_envnode	*curr;

	curr = envlist->head->next;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
			break ;
		curr = curr->next;
	}
	if (!curr->next)
		return (0);
	return (curr->val);
}

void	change_val(t_envlist *envlist, char *key, char *val)
{
	t_envnode	*curr;

	curr = envlist->head->next;
	while (curr->next)
	{
		if (ft_strcmp(curr->key, key) == 0)
			break ;
		curr = curr->next;
	}
	if (!curr->next)
	{
		ft_push_env(key, val, envlist);
		free(val);
		return ;
	}
	if (curr->val != 0)
		free(curr->val);
	curr->val = val;
}
