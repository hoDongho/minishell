/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:56:13 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/13 15:42:31 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*arg;
	int			nl;

	arg = cmdlist->head->next->next;
	nl = 0;
	while (arg->next)
	{
		if (strcmp(arg->str, "-n") == 0)
		{
			arg = arg->next;
			nl = 1;
			continue ;
		}
		printf("%s", arg->str);
		arg = arg->next;
		if (arg->next)
			printf(" ");
	}
	printf("$");
	if (nl == 0)
		printf("\n");
	return (0);
}
