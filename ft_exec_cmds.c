/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/21 12:55:16 by nhwang           ###   ########.fr       */
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

int	ft_exec_child(t_exec_data *exec_data, t_exec_cmds *exec_cmds, int i)
{
	exec_data->pid[i] = fork();
	if (exec_data->pid[i] == -1)
		return (1);
	else if (exec_data->pid[i] == 0)
	{
		exec_cmds->p_cmds = sel_path(exec_data, exec_cmds);
		if (exec_cmds->p_cmds == 0 || ft_strchr(exec_cmds->p_cmds, '/') == 0)
		{
			printf("command not found: %s\n", exec_cmds->cmds);
			exit(127);
		}
		close(exec_data->pipe_fd[0]);
		if (exec_cmds->next)
			set_std(STDIN_FILENO, exec_data->pipe_fd[1]);
		// if (check_built_in(par_mdata) == 1)
		// 	ft_exec_built_in(par_mdata);
		if (execve(exec_cmds->p_cmds, exec_cmds->s_cmds, exec_data->env) == -1)
			return (1);
	}
	return (0);
}

int	check_child(t_exec_data *exec_data)
{
	int	i;
	int	statloc;

	i = 0;
	while (exec_data->pid[i] != 0)
	{
		if (waitpid(exec_data->pid[i], &statloc, 0) == -1)
			return (1);
		i++;
	}
	if (WEXITSTATUS(statloc) != 0)
		return (WEXITSTATUS(statloc));
	return (0);
}

int	ft_exec_cmds(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	int	i;
	int	tmp_in;

	i = 0;
	tmp_in = dup(STDIN_FILENO);
	while (exec_cmds)
	{
		if (pipe(exec_data->pipe_fd) == -1)
			return (1);
		if (ft_exec_child(exec_data, exec_cmds, i) != 0)
			return (1);
		if (exec_cmds->next != 0)
			dup2(exec_data->pipe_fd[0], STDIN_FILENO);
		else
		{
			dup2(tmp_in, STDIN_FILENO);//cat cat에서 입력이 이상한 부분과 관련 있지 않을지...
			close(tmp_in);
		}
		close(exec_data->pipe_fd[0]);
		close(exec_data->pipe_fd[1]);
		exec_cmds = exec_cmds->next;
		i++;
	}
	return (check_child(exec_data));
}
