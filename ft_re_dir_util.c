/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_dir_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:10:33 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 17:29:54 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(char *str)
{
	if (*str == '>')
	{
		if (*(str + 1) != 0 && *(str + 1) == '>')
			return (3);
		else
			return (1);
	}
	else if (*str == '<')
	{
		if (*(str + 1) != 0 && *(str + 1) == '<')
			return (4);
		else
			return (2);
	}
	return (0);
}

t_cmdnode	*ft_del_redir(t_cmdnode *curr)
{
	t_cmdnode	*prev;
	t_cmdnode	*next;
	t_cmdnode	*temp;
	int			i;

	i = 2;
	while (curr->next && i)
	{
		prev = curr->prev;
		next = curr->next;
		prev->next = next;
		next->prev = prev;
		temp = curr;
		curr = next;
		free(temp->str);
		free(temp);
		i--;
	}
	return (curr);
}

int	ft_out_put_redir(t_cmdnode *curr, int *new_out, int *cnt, int redir_type)
{
	if (*new_out != STDOUT_FILENO)
		close(*new_out);
	(*cnt)++;
	if (redir_type == 1)
		*new_out = open(curr->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		*new_out = open(curr->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*new_out < 0)
	{
		write(2, curr->next->str, ft_strlen(curr->next->str));
		print_error(": ", 1);
		return (-1);
	}
	return (0);
}

int	ft_in_put_redir(t_cmdnode *curr, int *new_in)
{
	if (*new_in != STDIN_FILENO)
		close(*new_in);
	*new_in = open(curr->next->str, O_RDONLY, 0644);
	if (*new_in < 0)
	{
		write(2, curr->next->str, ft_strlen(curr->next->str));
		print_error(": ", 1);
		return (-1);
	}
	return (0);
}

int	check_re_dir(t_cmdlist *cmdlist)
{
	int			redir;
	t_cmdnode	*curr;

	redir = 0;
	curr = cmdlist->head->next;
	while (curr->next)
	{
		redir = ft_is_redir(curr->str);
		if (redir != 0)
			break ;
		curr = curr->next;
	}
	return (redir);
}
