/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:26:21 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/30 17:40:54 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chg_redir(t_cmdnode *curr, int *new_in, int *new_out, int *cnt)
{
	int	redir_type;

	redir_type = ft_is_redir(curr->str);
	if (redir_type == 1 || redir_type == 3)
	{
		if (ft_out_put_redir(curr, new_out, cnt, redir_type) != 0)
			return (-1);
	}
	else if (redir_type == 2)
	{
		if (ft_in_put_redir(curr, new_in) != 0)
			return (-1);
	}
	else if (redir_type == 4)
		if (ft_here_doc(curr, new_in) != 0)
			return (-1);
	return (redir_type);
}

int	ft_set_redir(t_cmdlist *cmdlist, int *new_in, int *new_out, int *cnt)
{
	t_cmdnode	*curr;
	int			redir_type;

	curr = cmdlist->head->next;
	redir_type = 0;
	while (curr->next)
	{
		if (curr->p_type == 3)
		{
			redir_type = ft_chg_redir(curr, new_in, new_out, cnt);
			if (redir_type < 0)
				return (-1);
			else if (redir_type > 0)
			{
				curr = ft_del_redir(curr);
				cmdlist->datasize = cmdlist->datasize - 2;
				continue ;
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_redir(t_cmdlist *cmdlist)
{
	int			new_in;
	int			new_out;
	int			cnt;

	new_in = STDIN_FILENO;
	new_out = STDOUT_FILENO;
	cnt = 1;
	if (ft_set_redir(cmdlist, &new_in, &new_out, &cnt) != 0)
		return (-1);
	if (new_in != STDIN_FILENO)
	{
		dup2(new_in, STDIN_FILENO);
		close(new_in);
	}
	if (new_out != STDOUT_FILENO)
	{
		dup2(new_out, STDOUT_FILENO);
		close(new_out);
	}
	return (cnt);
}
