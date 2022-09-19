/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:33:48 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 11:46:38 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_number(char *str)
{
	if (str == 0)
		return (1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
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
	else if (cmdlist->datasize == 2)
	{
		if (chk_number(arg->str) != 0)
		{
			printf("exit: %s: numeric argument required", arg->str);
			exit (-1);
		}
		status = atoi(arg->str);
	}
	else
		printf("exit: too many arguments\n");
	exit(status);
}
