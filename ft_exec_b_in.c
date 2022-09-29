/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_b_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:15:25 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 12:05:22 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_in_main_exec(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*cmd;

	cmd = cmdlist->head->next;
	if (ft_strcmp(cmd->str, "echo") == 0)
		ft_echo(cmdlist);
	else if (ft_strcmp(cmd->str, "pwd") == 0)
		ft_pwd(envlist);
	else if (ft_strcmp(cmd->str, "cd") == 0)
		ft_cd(cmdlist, envlist);
	else if (ft_strcmp(cmd->str, "exit") == 0)
		ft_exit(cmdlist);
	else if (ft_strcmp(cmd->str, "export") == 0)
		ft_export(cmdlist, envlist);
	else if (ft_strcmp(cmd->str, "env") == 0)
		ft_env(envlist, 0);
	else if (ft_strcmp(cmd->str, "unset") == 0)
		ft_unset(cmdlist, envlist);
}

int	ft_exec_built_in(t_cmdlist *cmdlist, t_envlist *envlist, int flag)
{
	int			origin_in;
	int			origin_out;

	if (flag == 0)
	{
		origin_in = dup(STDIN_FILENO);
		origin_out = dup(STDOUT_FILENO);
		if (origin_in == -1 || origin_out == -1)
			exit(1);
		if (ft_redir(cmdlist) == -1)
			return (1);
	}
	b_in_main_exec(cmdlist, envlist);
	if (flag == 0)
	{
		if (dup2(origin_in, STDIN_FILENO) == -1)
			exit(1);
		if (dup2(origin_out, STDOUT_FILENO) == -1)
			exit(1);
		close(origin_in);
		close(origin_out);
	}
	if (flag == 1)
		exit(0);
	return (0);
}
