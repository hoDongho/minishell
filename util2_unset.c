/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:09:57 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/19 11:04:20 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_popenv(char *tkey, t_par_mdata *par_mdata)
{
	t_envnode	*curr;
	t_envnode	*next;
	t_envnode	*prev;
	t_envnode	*temp;
	size_t		size;

	curr = par_mdata->envlist->head->next;
	size = strlen(tkey);
	while (curr->next)
	{
		if (ft_strcmp(tkey, curr->key) == 0)
		{
			free(curr->key);
			free(curr->val);
			next = curr->next;
			prev = curr->prev;
			prev->next = next;
			next->prev = prev;
			temp = curr;
			curr = curr->next;
			free(temp);
			continue ;
		}
		curr = curr->next;
	}
}

void	ft_unset(t_par_mdata *par_mdata)
{
	t_cmdnode	*curr;

	curr = par_mdata->cmdlist->head->next;
	if (par_mdata->cmdlist->datasize == 1)
		return ;
	curr = curr->next;
	while (curr->next)
	{
		if (ft_valid(curr->str, 0) == 0)
		{
			printf("err unset\n");
			///error 출력 후
			curr = curr->next;
			continue ;
		}
		ft_popenv(curr->str, par_mdata);
		curr = curr->next;
	}
}
