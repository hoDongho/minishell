/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:58:44 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/28 16:35:26 by dhyun            ###   ########seoul.kr  */
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
	t_envnode	*new;

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
		return ;
	}
	if (curr->val != 0)
		free(curr->val);
	curr->val = val;
}
