/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:58:32 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 22:11:36 by nhwang           ###   ########.fr       */
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
		printf("search_path :: %s\n", tmp);
		ret = open(tmp, O_RDONLY);
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
	DIR			*dir;

	dir = opendir(exec_cmds->cmd);
	if (dir)
	{
		closedir(dir);
		write(2, exec_cmds->cmd, ft_strlen(exec_cmds->cmd));
		print_error(": is a directory\n", 126);
	}
	tmp = search_path(exec_data, exec_cmds);
	if (tmp != 0)
		return (tmp);
	ret = open(exec_cmds->cmd, O_RDONLY);
	close(ret);
	if (ret > 0)
		return (exec_cmds->cmd);
	else if (ret < 0 && errno == 13)
	{
		write(2, exec_cmds->cmd, ft_strlen(exec_cmds->cmd));
		print_error(": ", 126);
	}
	return (0);
}

void	ft_set_path(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	exec_cmds->p_cmds = sel_path(exec_data, exec_cmds);
	errno = 0;
	if (exec_cmds->p_cmds == 0 || ft_strchr(exec_cmds->p_cmds, '/') == 0)
	{
		ft_putstr_fd(exec_cmds->cmd, 2);
		print_error(": command not found\n", 127);
	}
}
