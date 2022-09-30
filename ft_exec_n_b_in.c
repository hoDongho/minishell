/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_n_b_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:01:36 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 11:54:42 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec_data_list(t_exec_data *exec_data)
{
	t_cmdnode	*cmd_curr;
	t_cmdnode	*cmd_temp;
	t_exec_cmds	*exec_cmds_tmp;

	while (exec_data->cmds_head)
	{
		free(exec_data->cmds_head->s_cmds);
		free(exec_data->cmds_head->p_cmds);
		cmd_curr = exec_data->cmds_head->cmdlist->head->next;
		while (cmd_curr->next)
		{
			cmd_temp = cmd_curr;
			cmd_curr = cmd_curr->next;
			free(cmd_temp);
		}
		free(exec_data->cmds_head->cmdlist->head);
		free(exec_data->cmds_head->cmdlist->tail);
		free(exec_data->cmds_head->cmdlist);
		exec_cmds_tmp = exec_data->cmds_head;
		exec_data->cmds_head = exec_data->cmds_head->next;
		free(exec_cmds_tmp);
	}
}

void	free_exec_data(t_exec_data *exec_data)
{
	int	i;

	i = 0;
	while (exec_data->path[i])
		free(exec_data->path[i++]);
	free(exec_data->path);
	i = 0;
	while (exec_data->env[i])
	{
		free(exec_data->env[i]);
		i++;
	}
	free(exec_data->env);
	free(exec_data->pid);
	free_exec_data_list(exec_data);
	free(exec_data);
	g_data.p_size = 0;
	g_data.pidarr = 0;
}

void	ft_exec_n_built_in(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_exec_data	*exec_data;

	exec_data = ft_calloc(1, sizeof(t_exec_data));
	exec_data->cmdlist = cmdlist;
	exec_data->envlist = envlist;
	convert_cmd(exec_data->cmdlist, exec_data);
	convert_env(exec_data->envlist, exec_data);
	ft_exec_cmds(exec_data, exec_data->cmds_head);
	free_exec_data(exec_data);
}
