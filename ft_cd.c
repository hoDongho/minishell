/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:59:47 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 11:46:29 by dhyun            ###   ########seoul.kr  */
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
		new = ft_newenv();
		new->key = strdup(key);
		new->val = val;
		envlist->tail->prev->next = new;
		new->next = envlist->tail;
		new->prev = envlist->tail->prev;
		envlist->tail->prev = new;
		envlist->datasize++;
		return ;
	}
	if (curr->val != 0)
		free(curr->val);
	curr->val = val;
}

char	*cd_w_args(t_cmdnode *arg, t_envlist *envlist,
			char *home, char *old_pwd)
{
	char	*path;

	if (*arg->str == 0)
		path = ft_strdup(old_pwd);
	else if (arg->str[0] == '~')
		path = ft_strjoin(home, &arg->str[1]);
	else if (arg->str[0] == '-' && arg->str[1] == 0)
	{
		path = find_val(envlist, "OLDPWD");
		if (path == 0)
			printf("cd: OLDPWD not set\n");
		else
		{
			path = ft_strdup(path);
			printf("%s\n", path);
		}
	}
	else
		path = ft_strdup(arg->str);
	if (path == 0)
		return (0);
	return (path);
}

char	*set_cd_path(t_cmdlist *cmdlist, t_envlist *envlist, char *old_pwd)
{
	t_cmdnode	*arg;
	char		*home;
	char		*path;

	arg = cmdlist->head->next->next;
	home = find_val(envlist, "HOME");
	if (home == 0 && cmdlist->datasize == 1)
	{
		printf("cd: HOME not set\n");
		return (0);
	}
	else if (home != 0)
		path = ft_strdup(home);
	if (cmdlist->datasize > 1)
		path = cd_w_args(arg, envlist, home, old_pwd);
	if (path == 0)
		return (0);
	return (path);
}

int	ft_cd(t_cmdlist *cmdlist, t_envlist *envlist)
{
	char		*old_pwd;
	char		*path;

	old_pwd = getcwd(0, 0);
	path = set_cd_path(cmdlist, envlist, old_pwd);
	if (path == 0)
		return (1);
	if (chdir(path) != 0)
		printf("errno :\n");
	free(path);
	if (path != 0)
	{
		change_val(envlist, "PWD", getcwd(0, 0));
		change_val(envlist, "OLDPWD", old_pwd);
	}
	return (0);
}
