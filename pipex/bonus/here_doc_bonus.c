/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:33:59 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/13 11:31:18 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_argc(int argc, char *argv[], t_data *arglist)
{
	if (argv[1] != 0 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		arglist->here_doc = 1;
		if (argc < 6)
			print_error("Wrong arguments", 1);
	}
	else
	{
		arglist->here_doc = 0;
		if (argc < 5)
			print_error("Wrong arguments", 1);
	}
}

void	set_arg(int *argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i] != 0)
	{
		argv[i] = argv[i + 1];
		i++;
	}
	*argc -= 1;
}

void	here_doc(int *argc, char *argv[], t_data *arglist)
{
	char	*tmp;
	char	*cmp_tmp;

	tmp = 0;
	set_arg(argc, argv);
	cmp_tmp = ft_strjoin(argv[1], "\n");
	arglist->tmp = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (arglist->tmp == -1)
		print_error("open", 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
		if (tmp == 0)
			print_error("gnl", 1);
		if (ft_strncmp(tmp, cmp_tmp, ft_strlen(cmp_tmp)) == 0)
			break ;
		write(arglist->tmp, tmp, ft_strlen(tmp));
		free(tmp);
	}
	free(tmp);
	free(cmp_tmp);
	close(arglist->tmp);
	argv[1] = ".heredoc_tmp";
}

void	open_outfile(t_data *arglist, char *path)
{
	if (arglist->here_doc == 0)
		arglist->outfile = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		arglist->outfile = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (arglist->outfile == -1)
		print_error("open", 1);
}
