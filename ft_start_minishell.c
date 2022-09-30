/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:22:45 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 17:04:35 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clearcmd(t_cmdlist *cmdlist)
{
	t_cmdnode	*curr;
	t_cmdnode	*temp;

	curr = cmdlist->head->next;
	while (curr->next)
	{
		temp = curr;
		curr = curr->next;
		free(temp->str);
		free(temp);
	}
	cmdlist->head->next = cmdlist->tail;
	cmdlist->tail->prev = cmdlist->head;
	cmdlist->datasize = 0;
}

void	ft_start_minishell(t_par_mdata *par_mdata)
{
	char		*input;

	while (1)
	{
		signal(SIGINT, ft_ctrl_c);
		signal(SIGQUIT, ft_ctrl_bslash);
		ft_clearcmd(par_mdata->cmdlist);
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		par_mdata->origin = input;
		if (ft_parse(par_mdata) == 1)
		{
			free(input);
			continue ;
		}
		free(input);
		ft_exec(par_mdata->cmdlist, par_mdata->envlist);
	}
}
