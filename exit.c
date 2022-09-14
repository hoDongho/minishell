/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:33:48 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/14 15:34:04 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str >'9')
			return (1);
		str++;
	}
	return (0);
}

int	ft_exit(t_cmdlist *cmdlist, t_par_mdata *par_mdata)
{
	t_cmdnode	*arg;
	int			status;

	arg = cmdlist->head->next->next;

	if (!arg->next)
		status = 0;
	else
	{
		if (chk_number(arg->str) != 0)
		{
			printf("exit: %s: numeric argument required", arg->str);
			exit (-1);
		}
		status = atoi(arg->str);
	}
	exit(status);
}

// exit ""
// cd ""
