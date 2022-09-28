/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:11:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/28 15:56:21 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *arglist, t_cmd *cmds, int argc, char *argv[])
{
	arglist->infile = open(argv[1], O_RDONLY);
	if (arglist->infile == -1)
		print_error("open", 0);
	arglist->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (arglist->outfile == -1)
		print_error("open", 1);
	arglist->tmp = 0;
	arglist->path = 0;
	arglist->env = 0;
	arglist->pid = ft_calloc(argc - 2, sizeof(pid_t));
	if (arglist->pid == 0)
		print_error("ft_calloc", 1);
	arglist->cmds = cmds;
}

void	init_cmds(t_cmd *cmds)
{
	cmds->cmds = 0;
	cmds->s_cmds = 0;
	cmds->p_cmds = 0;
	cmds->next = 0;
}

void	init_opt(t_opt *opt)
{
	opt->start = 0;
	opt->end = 0;
	opt->len = 0;
	opt->bs = 0;
}

void	init(t_data *arglist, t_cmd *cmds, int argc, char *argv[])
{
	init_data(arglist, cmds, argc, argv);
	init_cmds(cmds);
}
