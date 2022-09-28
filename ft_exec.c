/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:55:32 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/28 11:49:28 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_cmdlist *cmdlist)
{
	t_cmdnode *arg;

	arg = cmdlist->head->next;
	while (arg->next)
	{
		if (ft_strcmp(arg->str, "|") == 0 && arg->p_type == 3) //nhwang bf : if (ft_strcmp(arg->str, "|") == 0) |||||| 없는 경우인것 같음 없는 경우일때
		{
			return (1);
		}
		arg = arg->next;
	}
	return (0);
}

int ft_exec_built_in(t_cmdlist *cmdlist, t_envlist *envlist, int flag)
{
	t_cmdnode	*cmd;
	int			origin_in;
	int			origin_out;

	cmd = cmdlist->head->next;
	if (flag == 0)
	{
		origin_in = dup(STDIN_FILENO);
		origin_out = dup(STDOUT_FILENO);
		if (ft_redir(cmdlist) == -1)
			return (1);
	}
	if (ft_strcmp(cmd->str, "echo") == 0)
		ft_echo(cmdlist, envlist);
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
	if (flag == 0)
	{
		dup2(origin_in, STDIN_FILENO);
		dup2(origin_out, STDOUT_FILENO);
		close(origin_in);
		close(origin_out);
	}
	return (0);
}

int	check_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

int	check_cmds(t_cmdlist *cmdlist)
{

	if (check_pipe(cmdlist) == 1)
		return (1);
	if (check_built_in(cmdlist->head->next->str) == 1)
		return (2);
	return (0);
}

int	ft_exec(t_cmdlist *cmdlist, t_envlist *envlist)
{
	int	ret;

	ret = check_cmds(cmdlist);
	if (ret == 1)
		ft_exec_n_built_in(cmdlist, envlist);
	else if (ret == 2)
		ft_exec_built_in(cmdlist, envlist, 0);
	else
		ft_exec_n_built_in(cmdlist, envlist);
	return (0);
}
