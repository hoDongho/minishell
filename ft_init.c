/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:12:51 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/21 14:52:14 by dhyun            ###   ########seoul.kr  */
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
	cmdlist->tail = ft_newcmd(); // 에러처리
	cmdlist->head->next = cmdlist->tail;
	cmdlist->tail->prev = cmdlist->head;
	cmdlist->datasize = 0;
}

void	ft_init(t_par_mdata *par_mdata)
{
	par_mdata->arglist = calloc (1, sizeof(t_arglist));
	par_mdata->envlist = calloc (1, sizeof(t_envlist));
	par_mdata->cmdlist = calloc (1, sizeof(t_cmdlist));
	ft_arginit(par_mdata->arglist);
	ft_envinit(par_mdata->envlist);
	ft_cmdinit(par_mdata->cmdlist);
}

