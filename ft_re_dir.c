/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:26:21 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/23 13:05:27 by nhwang           ###   ########.fr       */
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
	while (i)
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

	new_in = 0;
	new_out = 0;
	cnt = 0;
	redir_type = 0;
	curr = cmdlist->head->next;
	while (curr->next)
	{
		if(curr->p_type == 3)
		{
			redir_type = ft_is_redir(curr->str);
			if (redir_type == 1 || redir_type == 3)
				cnt++;
			if (redir_type == 1)
			{
				if (new_out != 0)
					close(new_out);
				new_out = open(curr->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644); //
				dup2(new_out, STDOUT_FILENO); //
				curr = ft_del_redir(curr);
				cmdlist->datasize = cmdlist->datasize - 2;
				continue ;
			}
			else if (redir_type == 2)
			{
				if (new_in != 0)
					close(new_in);
				new_in = open(curr->next->str, O_RDONLY, 0644); //
				if (new_in < 0)
				{
					printf("no f d\n");
					return (-1);
				}
				dup2(new_in, STDIN_FILENO); //
				curr = ft_del_redir(curr);
				cmdlist->datasize = cmdlist->datasize - 2;
				continue ;
			}
			// else if (redir_type == 3)
			// {
			// }
			// else if (redir_type == 4)
			// {
			// }
		}
		curr = curr->next;
	}
	return (cnt);
}
