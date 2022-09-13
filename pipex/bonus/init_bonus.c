/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:11:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/13 11:31:18 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_data(t_data *arglist, t_cmd *cmds, int argc, char *argv[])
{
	arglist->infile = open(argv[1], O_RDONLY);
	if (arglist->here_doc == 1 && unlink(".heredoc_tmp") == -1)
		print_error("unlink", 1);
	if (arglist->infile == -1)
	{
		print_error("open", 0);
	}
	open_outfile(arglist, argv[argc - 1]);
	arglist->tmp = 0;
	arglist->path = 0;
	arglist->env = 0;
	arglist->pid = ft_calloc(argc - 2, sizeof(pid_t));
	if (arglist->pid == 0)
		print_error("calloc", 1);
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
