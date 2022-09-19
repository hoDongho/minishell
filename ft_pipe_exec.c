/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 17:13:29 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_std(t_pipe_data *pipe_data, t_pipe_cmds *pipe_cmds, int new_in, int new_out)
{
	if (new_in != STDIN_FILENO)
	{
		if (dup2(new_in, STDIN_FILENO) == -1)
			print_error("dup2", 1);
		close(new_in);
	}
	if (new_out != STDOUT_FILENO)
	{
		if (dup2(new_out, STDOUT_FILENO) == -1)
			print_error("dup2", 1);
		close(new_out);
	}
		// if (pipe_cmds->cmds == b-in)
	if (execve(pipe_cmds->p_cmds, pipe_cmds->s_cmds, pipe_data->env) == -1)
		print_error("execve", 1);
}

void	exec_cmds(t_pipe_data *pipe_data, t_pipe_cmds *pipe_cmds, int i)
{
	pipe_data->pid[i] = fork();
	if (pipe_data->pid[i] == -1)
		print_error("fork", 1);
	else if (pipe_data->pid[i] == 0)
	{
		pipe_cmds->p_cmds = sel_path(pipe_data, pipe_cmds);
		if (pipe_cmds->p_cmds == 0 || ft_strchr(pipe_cmds->p_cmds, '/') == 0)
			print_error("command not found", 127);
		close(pipe_data->pipe[0]);
		if (pipe_data->cmds_head == pipe_cmds)
			set_std(pipe_data, pipe_cmds, STDIN_FILENO, pipe_data->pipe[1]);
		else if (pipe_cmds->next == 0)
			set_std(pipe_data, pipe_cmds, pipe_data->pipe_fd_tmp, STDOUT_FILENO);
		else
			set_std(pipe_data, pipe_cmds, pipe_data->pipe_fd_tmp, pipe_data->pipe[1]);
	}
}

void	check_child(t_pipe_data *pipe_data)
{
	int	i;
	int	statloc;

	i = 0;
	while (pipe_data->pid[i] != 0)
	{
		if (waitpid(pipe_data->pid[i], &statloc, 0) == -1)
			print_error("waitpid", 1);
		i++;
	}
	if (WEXITSTATUS(statloc) != 0)
		exit(WEXITSTATUS(statloc));
}

int	ft_pipe_exec(t_pipe_data *pipe_data, t_pipe_cmds *pipe_cmds)
{
	int	i;

	i = 0;
	while (pipe_cmds != 0)
	{
		if (pipe(pipe_data->pipe) == -1)
			print_error("pipe", 1);
		exec_cmds(pipe_data, pipe_cmds, i);
		if (pipe_data->pipe_fd_tmp != 0)
			close(pipe_data->pipe_fd_tmp);
		close(pipe_data->pipe[1]);
		pipe_data->pipe_fd_tmp = pipe_data->pipe[0];
		pipe_cmds = pipe_cmds->next;
		i++;
	}
	check_child(pipe_data);
	return (0);
}
