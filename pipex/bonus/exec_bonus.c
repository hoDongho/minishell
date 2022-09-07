/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/07/18 14:20:59 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_std(t_data *data, t_cmd *cmds, int new_in, int new_out)
{
	if (dup2(new_in, STDIN_FILENO) == -1)
		print_error("dup2", 1);
	if (dup2(new_out, STDOUT_FILENO) == -1)
		print_error("dup2", 1);
	if (execve(cmds->p_cmds, cmds->s_cmds, data->env) == -1)
		print_error("execve", 1);
	close(new_in);
	close(new_out);
}

void	exec_cmds(t_data *data, t_cmd *cmds, int i)
{
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		print_error("fork", 1);
	else if (data->pid[i] == 0)
	{
		cmds->p_cmds = sel_path(data, cmds);
		if (cmds->p_cmds == 0 || ft_strchr(cmds->p_cmds, '/') == 0)
			print_error("command not found", 127);
		close(data->pipe[0]);
		if (cmds->next == 0)
			set_std(data, cmds, data->tmp, data->outfile);
		else if (data->cmds == cmds)
		{
			set_std(data, cmds, data->infile, data->pipe[1]);
		}
		else
			set_std(data, cmds, data->tmp, data->pipe[1]);
	}
}

void	check_child(t_data *data)
{
	int	i;
	int	statloc;

	i = 0;
	while (data->pid[i] != 0)
	{
		if (waitpid(data->pid[i], &statloc, 0) == -1)
			print_error("waitpid", 1);
		i++;
	}
	if (WEXITSTATUS(statloc) != 0)
		exit(WEXITSTATUS(statloc));
}

void	exec(t_data *data, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds != 0)
	{
		if (pipe(data->pipe) == -1)
			print_error("pipe", 1);
		exec_cmds(data, cmds, i);
		close(data->tmp);
		close(data->pipe[1]);
		data->tmp = data->pipe[0];
		cmds = cmds->next;
		i++;
	}
	check_child(data);
}
