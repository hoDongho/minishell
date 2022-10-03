/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:13:41 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/30 11:44:36 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ex_util(char *tkey, char *tval, t_envlist *envlist)
{
	if (ft_findenv(tkey, tval, envlist) == 0)
		ft_push_env(tkey, tval, envlist);
	if (tkey)
		free(tkey);
	if (tval)
		free(tval);
}

int	ft_findenv(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*curr;

	curr = envlist->head->next;
	while (curr->next)
	{
		if (ft_strcmp(tkey, curr->key) == 0)
		{
			if (tval)
			{
				free(curr->val);
				curr->val = ft_strdup(tval);
			}
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	ft_push_env(char *tkey, char *tval, t_envlist *envlist)
{
	t_envnode	*new;
	t_envnode	*prev;

	new = ft_newenv();
	new->key = ft_strdup(tkey);
	if (tval)
		new->val = ft_strdup(tval);
	prev = envlist->tail->prev;
	new->next = envlist->tail;
	new->prev = prev;
	prev->next = new;
	envlist->tail->prev = new;
	envlist->datasize++;
}

void	ft_env(t_envlist *envlist, int b)
{
	t_envnode	*curr;

	g_data.exit_code = 0;
	curr = envlist->head->next;
	while (curr->next)
	{
		if (b && ft_strcmp(curr->key, "_") == 0)
		{
			curr = curr->next;
			continue ;
		}
		if (curr->val && b)
			printf("declare -x %s=\"%s\"\n", curr->key, curr->val);
		else if (!curr->val && b)
			printf("declare -x %s\n", curr->key);
		else if (curr->val && !b)
			printf("%s=%s\n", curr->key, curr->val);
		curr = curr->next;
	}
}
