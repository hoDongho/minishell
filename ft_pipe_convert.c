/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:44:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 15:41:59 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

t_pipe_cmds	*new_pipe_cmds(t_pipe_data *pipe_data, int size)
{
	t_pipe_cmds	*new;

	new = ft_calloc(1, sizeof(t_pipe_cmds));
	if (new == 0)
		return (0);
	new->s_cmds = (char **)ft_calloc(size + 1, sizeof(char *));
	if (new->s_cmds == 0)
		return (0);
	if (pipe_data->cmds_head == 0)
		pipe_data->cmds_head = new;
	if (pipe_data->cmds_tail != 0)
		pipe_data->cmds_tail->next = new;
	pipe_data->cmds_tail = new;
	return (new);
}

int	make_pipe_cmds(t_cmdnode *arg, t_pipe_data *pipe_data, int arg_cnt)
{
	t_pipe_cmds	*pipe_cmds;
	int			cnt;

	cnt = 0;
	pipe_cmds = new_pipe_cmds(pipe_data, arg_cnt);
	if (pipe_cmds == 0)
		return (1);
	while (arg_cnt)
	{
		arg = arg->prev;
		arg_cnt--;
		pipe_cmds->s_cmds[arg_cnt] = arg->str;
	}
	pipe_cmds->cmds = pipe_cmds->s_cmds[0];
	return (0);
}

int	convert_cmd(t_cmdlist *cmdlist, t_pipe_data *pipe_data)
{
	t_cmdnode	*arg;
	int			arg_cnt;
	int			pipe_cnt;

	arg = cmdlist->head->next;
	arg_cnt = 0;
	pipe_cnt = 0;
	while (arg->next)
	{
		if (ft_strcmp(arg->str, "|") == 0)
		{
			if (make_pipe_cmds(arg, pipe_data, arg_cnt) != 0)
				return (1);
			pipe_cnt++;
			arg_cnt = -1;
		}
		arg_cnt++;
		arg = arg->next;
	}
	if (make_pipe_cmds(arg, pipe_data, arg_cnt) != 0)
		return (1);
	pipe_data->pid = ft_calloc(pipe_cnt + 1 + 1, sizeof(pid_t));
	if (pipe_data->pid == 0)
		return (1);
	return (0);
}

int	split_path(t_pipe_data *pipe_data)
{
	while (*pipe_data->env != 0 && ft_strncmp(*pipe_data->env, "PATH=", 5) != 0)
		pipe_data->env++;
	pipe_data->path = ft_split(*pipe_data->env + 5, ':');
	if (pipe_data->path == 0)
		return (1);
	return (0);
}

int	convert_env(t_envlist *envlist, t_pipe_data *pipe_data)
{
	t_envnode	*curr;
	int			i;

	pipe_data->env = (char **)ft_calloc(envlist->datasize + 1, sizeof(char *));
	if (pipe_data->env == 0)
		return (1);
	i = 0;
	curr = envlist->head->next;
	while (curr->next)
	{
		pipe_data->env[i] = ft_strjoin_wc(curr->key, curr->val, '=');
		if (pipe_data->env == 0)
			return (1);
		i++;
		curr = curr->next;
	}
	if (split_path(pipe_data) != 0)
		return (1);
	return (0);
}
