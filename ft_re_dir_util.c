/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_dir_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:10:33 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 00:45:30 by dhyun            ###   ########seoul.kr  */
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
		free(temp->str);//
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

void	ft_here_doc(t_cmdnode *curr, int *new_in)
{
	char	*hd_exit;
	char	*hd_input;

	if (*new_in != 0)
		close(*new_in);
	hd_exit = ft_strjoin(curr->next->str, "\n");
	*new_in = open("/tmp/.heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*new_in == -1)
		print_error("open", 1);
	while (1)
	{
		write(1, "> ", 2);
		hd_input = get_next_line(STDIN_FILENO);
		if (hd_input == 0)
			break ;
		if (ft_strcmp(hd_input, hd_exit) == 0)
			break ;
		write(*new_in, hd_input, ft_strlen(hd_input));
		free(hd_input);
	}
	free(hd_exit);
	free(hd_input);
	close(*new_in);
	*new_in = open("/tmp/.heredoc_tmp", O_RDONLY, 0644);
	unlink("/tmp/.heredoc_tmp");
}
