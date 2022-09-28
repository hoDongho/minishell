/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:26:21 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 12:04:46 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(temp);
		i--;
	}
	return (curr);
}

int	ft_redir(t_cmdlist *cmdlist)
{
	t_cmdnode	*curr;
	int			redir_type;
	int			new_in;
	int			new_out;
	int			cnt;

	new_in = STDIN_FILENO;
	new_out = STDOUT_FILENO;
	cnt = 0;
	redir_type = 0;
	curr = cmdlist->head->next;
	while (curr->next)
	{
		if(curr->p_type == 3)
		{
			redir_type = ft_is_redir(curr->str);
			// if (redir_type == 1 || redir_type == 3)
			// 	cnt++;
			if (redir_type == 1 || redir_type == 3)
			{
				if (new_out != STDOUT_FILENO)
					close(new_out);
				cnt++;
				// if (!curr->next->next || ft_isalnum(*curr->next->str))
					// print_error("syntax error near unexpected token `newline'", 0); //
				if (redir_type == 1)
					new_out = open(curr->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644); //
				else
					new_out = open(curr->next->str, O_RDWR | O_CREAT | O_APPEND, 0644); //
				// dup2(new_out, STDOUT_FILENO); //
				// close(new_out);
				if (new_out < 0)
				{
					write(2, curr->next->str, ft_strlen(curr->next->str));
					print_error(": ", 1);
					return (-1);
				}
				curr = ft_del_redir(curr);
				cmdlist->datasize = cmdlist->datasize - 2;
				continue ;
			}
			else if (redir_type == 2)
			{
				if (new_in != STDIN_FILENO)
					close(new_in);
				new_in = open(curr->next->str, O_RDONLY, 0644); //
				if (new_in < 0)
				{
					write(2, curr->next->str, ft_strlen(curr->next->str));
					print_error(": ", 1);
					return (-1);
				}
				// dup2(new_in, STDIN_FILENO); //
				// close(new_in);
				curr = ft_del_redir(curr);
				cmdlist->datasize = cmdlist->datasize - 2;
				continue ;
			}
			else if (redir_type == 4)
			{
				if (new_in != 0)
					close(new_in);
				char	*hd_exit;
				char	*hd_input;

				hd_exit = ft_strjoin(curr->next->str, "\n");
				new_in = open("/tmp/.heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
				// new_in = open("testest", O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (new_in == -1)
					print_error("open", 1);
				while (1)
				{
					write(1, "> ", 2);
					hd_input = get_next_line(STDIN_FILENO);
					if (hd_input == 0)
					{
						// printf("\n");
						break ;
					}
						// print_error("gnl", 1);
					if (ft_strcmp(hd_input, hd_exit) == 0)
						break ;
					write(new_in, hd_input, ft_strlen(hd_input));
					free(hd_input);
				}
				free(hd_exit);
				free(hd_input);
				close(new_in);
				new_in = open("/tmp/.heredoc_tmp", O_RDONLY, 0644);
				unlink("/tmp/.heredoc_tmp");
				// unlink("testest");
				// dup2(new_in, STDIN_FILENO);
				curr = ft_del_redir(curr);
				cmdlist->datasize = cmdlist->datasize - 2;
				continue ;
			}
		}
		curr = curr->next;
	}
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
