/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/10/03 16:11:53 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_d_pointer(t_exec_cmds *exec_cmds)
{
	t_cmdnode	*curr;
	int			i;

	i = 0;
	exec_cmds->s_cmds = (char **)ft_calloc(exec_cmds->cmdlist->datasize + 1,
			sizeof(char *));
	curr = exec_cmds->cmdlist->head->next;
	while (curr->next)
	{
		exec_cmds->s_cmds[i] = curr->str;
		i++;
		curr = curr->next;
	}
	exec_cmds->cmd = exec_cmds->s_cmds[0];
	if (exec_cmds->cmd == 0)
		exit(0);
}

void	set_std(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	int	redir_cnt;

	redir_cnt = 0;
	close(exec_data->pipe_fd[0]);
	if (g_data.p_size > 1)
		redir_cnt = ft_redir(exec_cmds->cmdlist);
	if (redir_cnt < 0)
		exit(1);
	else if (exec_cmds->next && redir_cnt == 1)
	{
		if (dup2(exec_data->pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	close(exec_data->pipe_fd[1]);
	ft_put_d_pointer(exec_cmds);
}

void	ft_exec_child(t_exec_data *exec_data, t_exec_cmds *exec_cmds, int i)
{
	exec_data->pid[i] = fork();
	if (exec_data->pid[i] == -1)
		exit(1);
	else if (exec_data->pid[i] == 0)
	{
		errno = 0;
		set_std(exec_data, exec_cmds);
		if (check_built_in(exec_cmds->cmd) == 1)
		{
			ft_exec_built_in(exec_cmds->cmdlist, exec_data->envlist);
			exit(0);
		}
		ft_set_path(exec_data, exec_cmds);
		if (execve(exec_cmds->p_cmds, exec_cmds->s_cmds, exec_data->env) == -1)
		{
			if (errno == 13)
			{
				ft_putstr_fd(exec_cmds->cmd, 2);
				ft_putstr_fd(": ", 2);
				print_error("", 126);
			}
			errno = 2;
			ft_putstr_fd(exec_cmds->cmd, 2);
			ft_putstr_fd(": ", 2);
			print_error("", 127);
		}
	}
}

void	check_child(t_exec_data *exec_data)
{
	int	i;
	int	statloc;

	i = 0;
	while (exec_data->pid[i] != 0)
	{
		if (waitpid(exec_data->pid[i], &statloc, 0) == -1)
			exit(1);
		i++;
	}
	if (g_data.is_sig == 0)
		g_data.exit_code = WEXITSTATUS(statloc);
	g_data.is_sig = 0;
}

void	ft_exec_cmds(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	int	i;
	int	tmp_in;

	i = 0;
	tmp_in = dup(STDIN_FILENO);
	while (exec_cmds)
	{
		if (pipe(exec_data->pipe_fd) == -1)
			exit(1);
		ft_exec_child(exec_data, exec_cmds, i);
		if (exec_cmds->next != 0)
			dup2(exec_data->pipe_fd[0], STDIN_FILENO);
		else
		{
			dup2(tmp_in, STDIN_FILENO);
			close(tmp_in);
		}
		close(exec_data->pipe_fd[0]);
		close(exec_data->pipe_fd[1]);
		exec_cmds = exec_cmds->next;
		i++;
	}
	check_child(exec_data);
}
