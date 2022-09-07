/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:31:54 by dhyun             #+#    #+#             */
/*   Updated: 2022/07/18 11:46:59 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str, int code)
{
	if (errno == 0)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	if (code != 0)
		exit(code);
}

void	free_all(t_data *data, t_cmd *cmds)
{
	t_cmd	*tmp;

	free_split(data->path);
	free(data->pid);
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
	t_data	data;
	t_cmd	*cmds;

	if (argc < 5)
		print_error("Wrong arguments", 1);
	cmds = ft_calloc(1, sizeof(t_cmd));
	if (cmds == 0)
		print_error("calloc", 1);
	init(&data, cmds, argc, argv);
	set_args(argc, argv, env, &data);
	exec(&data, cmds);
	free_all(&data, cmds);
	return (0);
}
