/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:56:13 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 11:41:48 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_option(char *str)
{
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (1);
		str++;
	}
	return (0);
}

void	ft_echo(t_cmdlist *cmdlist)
{
	t_cmdnode	*arg;
	int			n_opt;

	arg = cmdlist->head->next->next;
	n_opt = 0;
	while (arg->next && *arg->str == '-')
	{
		if (chk_option(arg->str) == 1)
			break ;
		n_opt++;
		arg = arg->next;
	}
	while (arg->next)
	{
		if (arg->str)
			printf("%s", arg->str);
		arg = arg->next;
		if (arg->next)
			printf(" ");
	}
	if (n_opt == 0)
		printf("\n");
	g_data.exit_code = 0;
}
