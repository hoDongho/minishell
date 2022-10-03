/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:00:54 by dhyun             #+#    #+#             */
/*   Updated: 2022/10/03 17:09:21 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_wc(char *s1, char *s2, char c)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = ft_calloc(len1 + len2 + 1 + 1, sizeof(char));
	ft_memmove(new, s1, len1);
	new[len1] = c;
	ft_memmove(new + len1 + 1, s2, len2);
	return (new);
}

void	print_error(char *str, int code)
{
	if (errno == 0)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	g_data.exit_code = code;
	if (g_data.p_size != 0)
		exit(code);
}

t_cmdlist	*ft_cpy_cmdlist(t_cmdnode *arg)
{
	t_cmdlist	*new;

	new = ft_calloc(1, sizeof(t_cmdlist));
	ft_cmdinit(new);
	while (arg->next)
	{
		if (ft_strcmp(arg->str, "|") == 0)
			break ;
		ft_pushcmd(new, arg->str, arg->p_type);
		arg = arg->next;
	}
	return (new);
}

void	ft_exe_error(t_exec_cmds *exec_cmds)
{
	if (errno == 13)
	{
		ft_putstr_fd(exec_cmds->cmd, 2);
		ft_putstr_fd(": ", 2);
		print_error("", 126);
	}
	errno = 2;
	ft_putstr_fd(exec_cmds->cmd, 2);
	ft_putstr_fd(": ", 2);
	print_error("", 127);
}

void	ft_open_error(t_exec_cmds *exec_cmds)
{
	if (errno == 13)
	{
		ft_putstr_fd(exec_cmds->cmd, 2);
		print_error(": ", 126);
	}
	else if (ft_strncmp("./", exec_cmds->cmd, 2) == 0
		|| ft_strchr(exec_cmds->cmd, '/') != 0)
	{
		ft_putstr_fd(exec_cmds->cmd, 2);
		print_error(": ", 127);
	}
}
