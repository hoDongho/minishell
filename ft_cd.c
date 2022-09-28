/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:59:47 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/28 11:24:27 by nhwang           ###   ########.fr       */
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
		if (new->key == 0)
		{
			print_error("malloc", 1);
			return ;
		}
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
		{
			print_error("cd: OLDPWD not set\n", 1);
			return (0);
		}
		else
		{
			path = ft_strdup(path);
			if (path == 0)
				print_error("malloc", 1);
		}
	}
	else
		path = ft_strdup(arg->str);
	if (path == 0)
		print_error("malloc", 1);
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
		print_error("cd: HOME not set\n", 1);
		return (0);
	}
	else if (home != 0)
		path = ft_strdup(home);
	if (cmdlist->datasize > 1)
	{
		free(path);
		path = cd_w_args(arg, envlist, home, old_pwd);
	}
	if (path == 0 && errno != 0)
		print_error("malloc", 1);
	return (path);
}

int	ft_cd(t_cmdlist *cmdlist, t_envlist *envlist)
{
	char		*old_pwd;
	char		*path;

	old_pwd = find_val(envlist, "PWD");
	if (old_pwd != 0)
	{
		old_pwd = ft_strdup(old_pwd);
		if(old_pwd == 0)
		{
			print_error("malloc", 1);
			return (1);
		}
	}
	else
	{
		old_pwd = getcwd(0, 0);
		if (old_pwd == 0 && errno != ENOENT)
		{
			print_error("getcwd", 1);
			return (1);
		}
	}
	path = set_cd_path(cmdlist, envlist, old_pwd);
	if (path == 0)
	{
		free(old_pwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		print_error("", 1);
		return (1);
	}
	else if (cmdlist->head->next->next->str != 0 && cmdlist->head->next->next->str[0] == '-'
		&& cmdlist->head->next->next->str[1] == 0)
		printf("%s\n", path);
	free(path);
	change_val(envlist, "OLDPWD", old_pwd);
	path = getcwd(0, 0);
	if (path == 0)
	{
		print_error("getcwd", 1);
		return (1);
	}
	change_val(envlist, "PWD", path);
	g_data.exit_code = 0;
	return (0);
}
