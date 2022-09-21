/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:49:52 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/20 19:53:44 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	free_exec_data(t_exec_data *exec_data)
{
	t_cmdnode	*curr;
	t_cmdnode	*temp;
	int			i;

	i = 0;
	while (exec_data->path[i])
		free(exec_data->path[i++]);
	free(exec_data->path);
	i = 0;
	while (exec_data->env[i])
		free(exec_data->env[i++]);
	free(exec_data->env);
	free(exec_data->pid);
	while (exec_data->cmds_head)
	{
		free(exec_data->cmds_head->s_cmds);
		free(exec_data->cmds_head->p_cmds);
		if (check_built_in(exec_data->cmds_head->cmds) == 1)
		{
			curr = exec_data->cmds_head->cmdlist->head->next;
			while (curr->next)
			{
				temp = curr;
				curr = curr->next;
				free(temp);
			}
			free(exec_data->cmds_head->cmdlist->head);
			free(exec_data->cmds_head->cmdlist->tail);
			free(exec_data->cmds_head->cmdlist);
		}
		exec_data->cmds_head = exec_data->cmds_head->next;
	}
	free(exec_data);
}

int	ft_exec_convert(t_exec_data *exec_data)
{
	if (convert_cmd(exec_data->cmdlist, exec_data) != 0)
		return (1);
	if (convert_env(exec_data->envlist, exec_data) != 0)
		return (1);
	return (0);
}

int	ft_exec_n_built_in(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_exec_data	*exec_data;

	exec_data = ft_calloc(1, sizeof(t_exec_data));
	if (exec_data == 0)
		return (1);
	exec_data->cmdlist = cmdlist;
	exec_data->envlist = envlist;
	if (ft_exec_convert(exec_data) != 0)
		return (1);
	if (ft_exec_cmds(exec_data, exec_data->cmds_head) != 0)
		return (1);
	free_exec_data(exec_data);
	return (0);
}


// echo 123 | >> 어떻게 처리?
// int i;
// 	t_exec_cmds *cmds = exec_data->cmds_head;
// 	while (cmds)
// 	{
// 		i = 0;
// 		while (cmds->s_cmds[i])
// 		{
// 			printf("cmds :%s\n", cmds->s_cmds[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		cmds = cmds->next;
// 	}
