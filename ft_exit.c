/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:33:48 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/26 17:35:57 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_number(char *str)
{
	int	len;

	len = 0;
	if (str == 0)
		return (1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
		len++;
	}
	return (0);
}

int	ft_exit(t_cmdlist *cmdlist)
{
	t_cmdnode	*arg;
	int			status;

	arg = cmdlist->head->next->next;
	write(2, "exit\n", 5);
	if (!arg->next)
		status = 0;
	else if (cmdlist->datasize > 1)
	{
		if (chk_number(arg->str) != 0)
		{
			write(2, "exit: ", 6);
			write(2, arg->str, ft_strlen(arg->str));
			print_error(": numeric argument required", -1);
			exit (-1);
		}
		else if (cmdlist->datasize > 2)
			print_error("exit: too many arguments\n", 1);
		status = ft_atoi(arg->str);
		if (ft_strlen(arg->str) >= 19 && status == -1) // 수정필요
		{
			if (chk_number(arg->str) != 0)
			{
				write(2, "exit: ", 6);
				write(2, arg->str, ft_strlen(arg->str));
				print_error(": numeric argument required", -1);
				exit (-1);
			}
		}
		else if (arg->str[0] == '-' && ft_strlen(arg->str) >= 20 && status == 0)
		{
			if (chk_number(arg->str) != 0)
			{
				write(2, "exit: ", 6);
				write(2, arg->str, ft_strlen(arg->str));
				print_error(": numeric argument required", -1);
				exit (-1);
			}
		}
	}
	if (cmdlist->datasize < 3)
		exit(status);
	return (0);
}
