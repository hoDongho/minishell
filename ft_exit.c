/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:33:48 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/28 16:45:15 by dhyun            ###   ########seoul.kr  */
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

int	ft_exit(t_cmdlist *cmdlist)
{
	t_cmdnode	*arg;
	long long	status;

	arg = cmdlist->head->next->next;
	ft_putstr_fd("exit\n", 2);
	if (!arg->next)
		status = 0;
	else if (cmdlist->datasize > 1)
	{
		status = ft_atoi(arg->str);
		if (chk_number(arg->str) != 0
			|| ft_strlen(arg->str) >= 19 && status == -1
			|| arg->str[0] == '-' && ft_strlen(arg->str) >= 20 && status == 0)
		{
			write(2, "exit: ", 6);
			write(2, arg->str, ft_strlen(arg->str));
			print_error(": numeric argument required", 255);
			exit(255);
		}
		else if (cmdlist->datasize > 2)
			print_error("exit: too many arguments\n", 1);
	}
	if (cmdlist->datasize < 3)
		exit(status);
	return (0);
}
