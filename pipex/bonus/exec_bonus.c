/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:00:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/13 11:31:18 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_std(t_data *arglist, t_cmd *cmds, int new_in, int new_out)
{
	if (dup2(new_in, STDIN_FILENO) == -1)
		print_error("dup2", 1);
	if (dup2(new_out, STDOUT_FILENO) == -1)
		print_error("dup2", 1);
	if (execve(cmds->p_cmds, cmds->s_cmds, arglist->env) == -1)
		print_error("execve", 1);
	close(new_in);
	close(new_out);
}

void	exec_cmds(t_data *arglist, t_cmd *cmds, int i)
{
	arglist->pid[i] = fork();
	if (arglist->pid[i] == -1)
		print_error("fork", 1);
	else if (arglist->pid[i] == 0)
	{
		cmds->p_cmds = sel_path(arglist, cmds);
		if (cmds->p_cmds == 0 || ft_strchr(cmds->p_cmds, '/') == 0)
			print_error("command not found", 127);
		close(arglist->pipe[0]);
		if (cmds->next == 0)
			set_std(arglist, cmds, arglist->tmp, arglist->outfile);
		else if (arglist->cmds == cmds)
		{
			set_std(arglist, cmds, arglist->infile, arglist->pipe[1]);
		}
		else
			set_std(arglist, cmds, arglist->tmp, arglist->pipe[1]);
	}
}

void	check_child(t_data *arglist)
{
	int	i;
	int	statloc;

	i = 0;
	while (arglist->pid[i] != 0)
	{
		if (waitpid(arglist->pid[i], &statloc, 0) == -1)
			print_error("waitpid", 1);
		i++;
	}
	if (WEXITSTATUS(statloc) != 0)
		exit(WEXITSTATUS(statloc));
}

void	exec(t_data *arglist, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds != 0)
	{
		if (pipe(arglist->pipe) == -1)
			print_error("pipe", 1);
		exec_cmds(arglist, cmds, i);
		close(arglist->tmp);
		close(arglist->pipe[1]);
		arglist->tmp = arglist->pipe[0];
		cmds = cmds->next;
		i++;
	}
	check_child(arglist);
}
