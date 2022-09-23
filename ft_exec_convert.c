/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:44:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/23 17:01:05 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

t_exec_cmds	*new_exec_cmds(t_exec_data *exec_data, int size)
{
	t_exec_cmds	*new;

	new = ft_calloc(1, sizeof(t_exec_cmds));
	if (new == 0)
		return (0);
	// new->s_cmds = (char **)ft_calloc(size + 1, sizeof(char *));
	// if (new->s_cmds == 0)
	// 	return (0);
	if (exec_data->cmds_head == 0)
		exec_data->cmds_head = new;
	if (exec_data->cmds_tail != 0)
		exec_data->cmds_tail->next = new;
	exec_data->cmds_tail = new;
	return (new);
}

int	make_exec_cmds(t_cmdnode *arg, t_exec_data *exec_data, int arg_cnt)
{
	t_exec_cmds	*exec_cmds;
	int			cnt;
	int			i;

	cnt = 0;
	i = arg_cnt;
	exec_cmds = new_exec_cmds(exec_data, arg_cnt);
	if (exec_cmds == 0)
		return (1);
	while (arg_cnt)///
	{
		arg = arg->prev;
		arg_cnt--;
		// exec_cmds->s_cmds[arg_cnt] = arg->str;
	}//
	// if (check_built_in(exec_cmds->cmds) == 1)
	// {
	// 	exec_cmds->cmdlist = ft_cpy_cmdlist(arg);
	// }
	exec_cmds->cmdlist = ft_cpy_cmdlist(arg);
	return (0);
}

int	convert_cmd(t_cmdlist *cmdlist, t_exec_data *exec_data)
{
	t_cmdnode	*arg;
	int			arg_cnt;
	int			pipe_cnt;
	int			cmd_cnt;

	arg = cmdlist->head->next;
	arg_cnt = 0;
	pipe_cnt = 0;
	while (arg->next)
	{
		if (ft_strcmp(arg->str, "|") == 0 && arg->p_type == 3)
		{
			if (make_exec_cmds(arg, exec_data, arg_cnt) != 0)
				return (1);
			pipe_cnt++;
			arg_cnt = -1;
		}
		arg_cnt++;
		arg = arg->next;
	}
	cmd_cnt = pipe_cnt + 1;
	if (ft_strcmp(arg->prev->str, "|") != 0 && make_exec_cmds(arg, exec_data, arg_cnt) != 0)
		return (1);
	// else if (ft_strcmp(arg->prev->str, "|") == 0)
	// 	cmd_cnt = pipe_cnt;
	exec_data->pid = ft_calloc(cmd_cnt + 1, sizeof(pid_t));
	if (exec_data->pid == 0)
		return (1);
	g_data.pidarr = exec_data->pid;//nhwang
	g_data.p_size = cmd_cnt;//nhwang
	return (0);
}

int	split_path(t_exec_data *exec_data)
{
	int	i;

	i = 0;
	while (exec_data->env[i] != 0 && ft_strncmp(exec_data->env[i], "PATH=", 5) != 0)
		i++;
	exec_data->path = ft_split(exec_data->env[i] + 5, ':');
	if (exec_data->path == 0)
		return (1);
	return (0);
}

int	convert_env(t_envlist *envlist, t_exec_data *exec_data)
{
	t_envnode	*curr;
	int			i;

	exec_data->env = (char **)ft_calloc(envlist->datasize + 1, sizeof(char *));
	if (exec_data->env == 0)
		return (1);
	i = 0;
	curr = envlist->head->next;
	while (curr->next)
	{
		if (curr->val != 0)
			exec_data->env[i] = ft_strjoin_wc(curr->key, curr->val, '=');
		if (exec_data->env == 0)
			return (1);
		i++;
		curr = curr->next;
	}
	if (split_path(exec_data) != 0)
		return (1);
	return (0);
}
