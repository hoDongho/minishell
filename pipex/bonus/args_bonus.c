/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:00:44 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/28 15:56:21 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_path(char *env[], t_data *arglist)
{
	arglist->env = env;
	while (*env != 0 && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == 0)
		print_error("Wrong enviroments", 1);
	arglist->path = ft_split(*env + 5, ':');
	if (arglist->path == 0)
		print_error("split", 1);
}

char	*sel_path(t_data *arglist, t_cmd *cmds)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	ret = access(cmds->cmds, X_OK);
	if (ret == 0)
		return (cmds->cmds);
	else if (ret == -1 && errno == 13)
		print_error("access", 126);
	while (arglist->path[i] != 0)
	{
		tmp = ft_strjoin_wc(arglist->path[i], cmds->cmds, '/');
		ret = check_access(tmp);
		if (ret == 0)
			return (ft_strjoin_wc(arglist->path[i], cmds->cmds, '/'));
		else if (ret == -1 && errno == 13)
			print_error("access", 126);
		i++;
		free(tmp);
		tmp = 0;
	}
	return (0);
}

void	split_cmds(t_cmd *cmds)
{
	if (check_quote(cmds->cmds) == 0 || ft_strncmp(cmds->cmds, "./", 2) == 0
		|| ft_strchr(cmds->cmds, '\\') != 0)
		set_option(cmds, cmds->cmds);
	else
	{
		cmds->s_cmds = ft_split(cmds->cmds, ' ');
		if (cmds->s_cmds == 0)
			print_error("split", 1);
	}
	cmds->cmds = cmds->s_cmds[0];
}

void	set_cmds(int argc, char *argv[], t_cmd *cmds)
{
	int		i;

	i = 2;
	while (i < argc - 1)
	{
		cmds->cmds = argv[i];
		split_cmds(cmds);
		if (i < argc - 2)
		{
			cmds->next = ft_calloc(1, sizeof(t_cmd));
			if (cmds->next == 0)
				print_error("ft_calloc", 1);
			cmds = cmds->next;
			init_cmds(cmds);
		}
		i++;
	}
}

void	set_args(int argc, char *argv[], char *env[], t_data *arglist)
{
	set_path(env, arglist);
	set_cmds(argc, argv, arglist->cmds);
}
