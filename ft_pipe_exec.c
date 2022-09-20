/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/20 14:45:14 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	set_std(int new_in, int new_out)
{
	if (new_in != STDIN_FILENO)
	{
		if (dup2(new_in, STDIN_FILENO) == -1)
			return (1);
		close(new_in);
	}
	if (new_out != STDOUT_FILENO)
	{
		if (dup2(new_out, STDOUT_FILENO) == -1)
			return (1);
		close(new_out);
	}
	return (0);
}

int	exec_cmds(t_pipe_data *pipe_data, t_pipe_cmds *pipe_cmds, int i)
{
	pipe_data->pid[i] = fork();
	if (pipe_data->pid[i] == -1)
		return (1);
	else if (pipe_data->pid[i] == 0)
	{
		pipe_cmds->p_cmds = sel_path(pipe_data, pipe_cmds);
		if (pipe_cmds->p_cmds == 0)
			return (1);
		close(pipe_data->pipe_fd[0]);
		if (pipe_cmds->next != 0)
			set_std(STDIN_FILENO, pipe_data->pipe_fd[1]);
		// if (pipe_cmds->cmds == b-in)
		if (execve(pipe_cmds->p_cmds, pipe_cmds->s_cmds, pipe_data->env) == -1)
			return (1);
	}
	return (0);
}

int	check_child(t_pipe_data *pipe_data)
{
	int	i;
	int	statloc;

	i = 0;
	while (pipe_data->pid[i] != 0)
	{
		if (waitpid(pipe_data->pid[i], &statloc, 0) == -1)
			return (1);
		i++;
	}
	if (WEXITSTATUS(statloc) != 0)
		return (WEXITSTATUS(statloc));
	return (0);
}

int	ft_pipe_exec(t_pipe_data *pipe_data, t_pipe_cmds *pipe_cmds)
{
	int	i;
	int	tmp_in;

	i = 0;
	tmp_in = dup(STDIN_FILENO);
	while (pipe_cmds)
	{
		if (pipe(pipe_data->pipe_fd) == -1)
			return (1);
		if (exec_cmds(pipe_data, pipe_cmds, i) != 0)
			return (1);
		if (pipe_cmds->next != 0)
			dup2(pipe_data->pipe_fd[0], STDIN_FILENO);
		else
		{
			dup2(tmp_in, STDIN_FILENO);
			close(tmp_in);
		}
		close(pipe_data->pipe_fd[0]);
		close(pipe_data->pipe_fd[1]);
		pipe_cmds = pipe_cmds->next;
		i++;
	}
	return (check_child(pipe_data));
}
