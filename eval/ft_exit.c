/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:33:48 by dhyun             #+#    #+#             */
/*   Updated: 2022/10/04 11:35:55 by nhwang           ###   ########.fr       */
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

void	ft_exit(t_cmdlist *cmdlist)
{
	t_cmdnode	*arg;
	long long	status;

	arg = cmdlist->head->next->next;
	ft_putstr_fd("exit\n", 2);
	if (!arg->next)
		status = g_data.exit_code;
	else if (cmdlist->datasize > 1)
	{
		status = ft_atoi(arg->str);
		if (chk_number(arg->str) != 0
			|| (ft_strlen(arg->str) >= 19 && status == -1)
			|| (arg->str[0] == '-' && ft_strlen(arg->str) >= 20 && status == 0))
		{
			write(2, "exit: ", 6);
			write(2, arg->str, ft_strlen(arg->str));
			print_error(": numeric argument required\n", 255);
			exit(255);
		}
		else if (cmdlist->datasize > 2)
			print_error("exit: too many arguments\n", 1);
	}
	if (cmdlist->datasize < 3)
		exit(status);
}
