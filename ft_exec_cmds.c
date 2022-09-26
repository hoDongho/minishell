/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/26 17:43:09 by dhyun            ###   ########seoul.kr  */
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
	int	redir_cnt;

	redir_cnt = 0;
	exec_data->pid[i] = fork();
	if (exec_data->pid[i] == -1)
		return (1);
	else if (exec_data->pid[i] == 0)
	{
		close(exec_data->pipe_fd[0]);
		// if
		// re_dir
		redir_cnt = ft_redir(exec_cmds->cmdlist);
		if (redir_cnt < 0)
			exit(1);
		else if (exec_cmds->next && redir_cnt == 0)
		{
			dup2(exec_data->pipe_fd[1], STDOUT_FILENO);
		}
		close(exec_data->pipe_fd[1]);
		// d_p
		exec_cmds->s_cmds = (char **)ft_calloc(exec_cmds->cmdlist->datasize + 1, sizeof(char *));
		if (exec_cmds->s_cmds == 0)
			return (0);
		t_cmdnode	*curr;
		int			i;
		i = 0;
		curr = exec_cmds->cmdlist->head->next;
		while (curr->next)///
		{
			exec_cmds->s_cmds[i] = curr->str;
			i++;
			curr = curr->next;
		}
		exec_cmds->cmd = exec_cmds->s_cmds[0];
			// set_std(STDIN_FILENO, exec_data->pipe_fd[1]);
		if (exec_cmds->cmd == 0)
		{
			exit(0);
		}
		if (check_built_in(exec_cmds->cmd) == 1)
		{
			ft_exec_built_in(exec_cmds->cmdlist, exec_data->envlist, 1); //0 only b-in, 1 b-in
			exit(0);
		}
		exec_cmds->p_cmds = sel_path(exec_data, exec_cmds);
		if (exec_cmds->p_cmds == 0 || ft_strchr(exec_cmds->p_cmds, '/') == 0)
		{
			printf("command not found: %s\n", exec_cmds->cmd);
			exit(127);
		}
		if (execve(exec_cmds->p_cmds, exec_cmds->s_cmds, exec_data->env) == -1)
			exit(errno);
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
		printf("in exec %d\n",WEXITSTATUS(statloc));
		i++;
	}
	// if (WEXITSTATUS(statloc) != 0)
	if (g_data.is_sig==0)//nhwang
		g_data.exit_code = WEXITSTATUS(statloc);//nhwang
		// return (WEXITSTATUS(statloc));
	g_data.is_sig=0;//nhwang
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
