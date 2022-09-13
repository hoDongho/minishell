/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:31:54 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/13 11:31:18 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error(char *str, int code)
{
	if (errno == 0)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	if (code != 0)
		exit(code);
}

void	free_all(t_data *arglist, t_cmd *cmds)
{
	t_cmd	*tmp;

	free_split(arglist->path);
	free(arglist->pid);
	while (cmds != 0)
	{
		free_split(cmds->s_cmds);
		free(cmds->p_cmds);
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_data	arglist;
	t_cmd	*cmds;

	check_argc(argc, argv, &arglist);
	if (arglist.here_doc == 1)
		here_doc(&argc, argv, &arglist);
	cmds = ft_calloc(1, sizeof(t_cmd));
	if (cmds == 0)
		print_error("calloc", 1);
	init(&arglist, cmds, argc, argv);
	set_args(argc, argv, env, &arglist);
	exec(&arglist, cmds);
	free_all(&arglist, cmds);
	return (0);
}
