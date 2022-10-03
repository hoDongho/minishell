/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:12:51 by nhwang            #+#    #+#             */
/*   Updated: 2022/10/03 17:05:05 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arginit(t_arglist *arglist)
{
	arglist->head = ft_new_argnode(0);
	arglist->tail = ft_new_argnode(0);
	arglist->head->next = arglist->tail;
	arglist->tail->prev = arglist->head;
	arglist->datasize = 0;
}

void	ft_envinit(t_envlist *envlist)
{
	envlist->head = ft_newenv();
	envlist->tail = ft_newenv();
	envlist->head->next = envlist->tail;
	envlist->tail->prev = envlist->head;
	envlist->datasize = 0;
}

void	ft_cmdinit(t_cmdlist *cmdlist)
{
	cmdlist->head = ft_newcmd();
	cmdlist->tail = ft_newcmd();
	cmdlist->head->next = cmdlist->tail;
	cmdlist->tail->prev = cmdlist->head;
	cmdlist->datasize = 0;
}

void	ft_init(t_par_mdata *par_mdata, int argc, char *argv[])
{
	struct termios	ter;

	if (argc != 1 || argv[1] != 0)
		exit(1);
	par_mdata->arglist = ft_calloc (1, sizeof(t_arglist));
	par_mdata->envlist = ft_calloc (1, sizeof(t_envlist));
	par_mdata->cmdlist = ft_calloc (1, sizeof(t_cmdlist));
	ft_arginit(par_mdata->arglist);
	ft_envinit(par_mdata->envlist);
	ft_cmdinit(par_mdata->cmdlist);
	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &ter);
}
