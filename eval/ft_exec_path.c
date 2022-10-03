/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:58:32 by dhyun             #+#    #+#             */
/*   Updated: 2022/10/03 17:00:22 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	int			i;
	int			ret;
	char		*tmp;

	i = 0;
	while (exec_data->path[i])
	{
		tmp = ft_strjoin_wc(exec_data->path[i], exec_cmds->cmd, '/');
		ret = open(tmp, O_RDONLY);
		if (ret != -1)
			close(ret);
		if (ret > 0)
			return (tmp);
		else if (ret == -1 && errno == 13)
		{
			write(2, exec_cmds->cmd, ft_strlen(exec_cmds->cmd));
			print_error(": ", 126);
		}
		i++;
		free(tmp);
		tmp = 0;
	}
	return (0);
}

char	*sel_path(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	int			ret;
	char		*tmp;

	tmp = search_path(exec_data, exec_cmds);
	if (tmp != 0)
		return (tmp);
	ret = open(exec_cmds->cmd, O_RDONLY);
	if (ret != -1)
		close(ret);
	if (ret > 0)
		return (exec_cmds->cmd);
	else if (ret < 0)
	{
		if (errno == 13)
		{
			ft_putstr_fd(exec_cmds->cmd, 2);
			print_error(": ", 126);
		}
		else if (ft_strncmp("./", exec_cmds->cmd, 2) == 0
			|| ft_strchr(exec_cmds->cmd, '/') != 0)
		{
			ft_putstr_fd(exec_cmds->cmd, 2);
			print_error(": ", 127);
		}
	}
	return (0);
}

void	check_dir(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	DIR	*dir;

	if (exec_data->path != 0 && ft_strchr(exec_cmds->cmd, '/') == 0)
		return ;
	dir = opendir(exec_cmds->cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(exec_cmds->cmd, 2);
		print_error(": is a directory", 126);
	}
}

void	ft_set_path(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	check_dir(exec_data, exec_cmds);
	if (exec_data->path == 0)
	{
		exec_cmds->p_cmds = ft_strdup(exec_cmds->cmd);
		return ;
	}
	exec_cmds->p_cmds = sel_path(exec_data, exec_cmds);
	errno = 0;
	if (exec_cmds->p_cmds == 0 || ft_strchr(exec_cmds->p_cmds, '/') == 0)
	{
		ft_putstr_fd(exec_cmds->cmd, 2);
		print_error(": command not found\n", 127);
	}
}
