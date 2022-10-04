/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:54:54 by nhwang            #+#    #+#             */
/*   Updated: 2022/10/04 11:20:46 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_push(t_arglist	*arglist, char c)
{
	t_argnode	*new;

	new = ft_new_argnode(c);
	arglist->tail->prev->next = new;
	new->next = arglist->tail;
	new->prev = arglist->tail->prev;
	arglist->tail->prev = new;
	arglist->datasize++;
}

char	*ft_makeword(t_arglist	*arglist)
{
	char		*str;
	char		*st;
	t_argnode	*curr;
	t_argnode	*temp;

	if (arglist->datasize == 0)
		return (NULL);
	st = ft_calloc(arglist->datasize + 1, sizeof(char));
	str = st;
	curr = arglist->head->next;
	while (curr->next)
	{
		*str = curr->c;
		temp = curr;
		curr = curr->next;
		free(temp);
		arglist->datasize--;
		str++;
	}
	arglist->head->next = arglist->tail;
	arglist->tail->prev = arglist->head;
	return (st);
}

void	ft_pushcmd(t_cmdlist *cmdlist, char *str, int swit)
{
	t_cmdnode	*new;
	t_cmdnode	*prev;
	char		*new_str;

	if (swit == 3 && str == 0)
		return ;
	new_str = str;
	if (str == 0)
		new_str = ft_calloc(1, sizeof(char));
	new = ft_newcmd();
	new->p_type = swit;
	new->str = new_str;
	prev = cmdlist->tail->prev;
	new->next = cmdlist->tail;
	new->prev = prev;
	prev->next = new;
	cmdlist->tail->prev = new;
	cmdlist->datasize++;
}
