/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:55:32 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/21 16:20:46 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_cmdlist *cmdlist, t_envlist *envlist)
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

int ft_exec_built_in(t_par_mdata *par_mdata)
{
	t_cmdnode	*cmd;

	cmd = par_mdata->cmdlist->head->next;
	if (ft_strcmp(cmd->str, "echo") == 0)
		ft_echo(par_mdata->cmdlist, par_mdata->envlist);
	else if (ft_strcmp(cmd->str, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->str, "cd") == 0)
		ft_cd(par_mdata->cmdlist, par_mdata->envlist);
	else if (ft_strcmp(cmd->str, "exit") == 0)
		ft_exit(par_mdata->cmdlist, par_mdata);
	else if (ft_strcmp(cmd->str, "export") == 0)
		ft_export(par_mdata);
	else if (ft_strcmp(cmd->str, "env") == 0)
		ft_env(par_mdata->envlist, 0);
	else if (ft_strcmp(cmd->str, "unset") == 0)
		ft_unset(par_mdata);
	else
		return (0);
	return (1);
}

int	check_built_in(t_par_mdata *par_mdata)
{
	t_cmdnode	*cmd;

	cmd = par_mdata->cmdlist->head->next;
	if (ft_strcmp(cmd->str, "echo") == 0 || ft_strcmp(cmd->str, "pwd") == 0
		|| ft_strcmp(cmd->str, "cd") == 0 || ft_strcmp(cmd->str, "exit") == 0
		|| ft_strcmp(cmd->str, "export") == 0 || ft_strcmp(cmd->str, "env") == 0
		|| ft_strcmp(cmd->str, "unset") == 0)
		return (1);
	return (0);
}

int	check_cmds(t_par_mdata *par_mdata)
{
	if (check_pipe(par_mdata->cmdlist, par_mdata->envlist) == 1)
		return (1);
	if (check_built_in(par_mdata) == 1)
		return (2);
	return (0);
}

int	ft_exec(t_par_mdata *par_mdata)
{
	int	ret;

	ret = check_cmds(par_mdata);
	if (ret == 1)
		ft_exec_n_built_in(par_mdata->cmdlist, par_mdata->envlist);
	else if (ret == 2)
		ft_exec_built_in(par_mdata);
	else
		ft_exec_n_built_in(par_mdata->cmdlist, par_mdata->envlist);
	return (0);
}
