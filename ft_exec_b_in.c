/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_b_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:15:25 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 17:43:02 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_built_in(t_cmdlist *cmdlist, t_envlist *envlist)
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
