/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:59:47 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/13 16:47:53 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home_dir(t_envlist *envlist)
{
	t_envnode	*curr;

	curr = envlist->head->next;
	while(curr->next)
	{
		if (strcmp(curr->key, "HOME") == 0)
			break ;
		curr = curr->next;
	}
	if (!curr->next)
		return (0);
	return (curr->val);
}

int	cd(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*arg;
	char		*home;

	arg = cmdlist->head->next->next;
	home = find_home_dir(envlist);
	if (!arg->next)
		chdir(home);
	pwd();
	return (0);
}
