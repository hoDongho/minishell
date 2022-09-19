/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:49:52 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 16:48:18 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	ft_pipe_convert(t_cmdlist *cmdlist, t_envlist *envlist,
	t_pipe_data *pipe_data)
{
	if (convert_cmd(cmdlist, pipe_data) != 0)
		return (1);
	if (convert_env(envlist, pipe_data) != 0)
		return (1);
	return (0);
}

int	ft_pipe(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_pipe_data	*pipe_data;

	pipe_data = ft_calloc(1, sizeof(t_pipe_data));
	if (pipe_data == 0)
		return (1);
	if (ft_pipe_convert(cmdlist, envlist, pipe_data) != 0)
		return (1);
	if (ft_pipe_exec(pipe_data, pipe_data->cmds_head) != 0)
		return (1);
	return (0);
}


// echo 123 | >> 어떻게 처리?
// int i;
// 	t_pipe_cmds *cmds = pipe_data->cmds_head;
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
