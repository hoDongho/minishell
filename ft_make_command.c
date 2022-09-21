/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:54:54 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/21 16:27:46 by dhyun            ###   ########seoul.kr  */
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
	st = calloc(arglist->datasize + 1, sizeof(char));
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

void	ft_pushcmd(t_cmdlist *cmdlist, char *str, int type)
{
	t_cmdnode	*new;
	t_cmdnode	*prev;
	char		*new_str;

	if (type == 3 && str == 0) //ㄷㅣ포ㄹ트에서도 테스트 해볼 것것.
		return ;
	new_str = str;
	if (str == 0)
		new_str = calloc(1, sizeof(char));
	new = ft_newcmd();
	// new = calloc(1, sizeof(t_cmdnode));
	// if(!new)
	// 	return (NULL); print 함수 만들고 exit 쓰기
	new->p_type = type;//nhwang
	new->str = new_str;
	prev = cmdlist->tail->prev;
	new->next = cmdlist->tail;
	new->prev = prev;
	prev->next = new;
	cmdlist->tail->prev = new;
	cmdlist->datasize++;
}
