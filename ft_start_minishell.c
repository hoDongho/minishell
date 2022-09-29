/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:22:45 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 11:23:53 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_minishell(t_par_mdata *par_mdata)
{
	char		*input;

	while (1)
	{
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
