/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:33:59 by dhyun             #+#    #+#             */
/*   Updated: 2022/07/18 13:46:53 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_argc(int argc, char *argv[], t_data *data)
{
	if (argv[1] != 0 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		data->here_doc = 1;
		if (argc < 6)
			print_error("Wrong arguments", 1);
	}
	else
	{
		data->here_doc = 0;
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

void	here_doc(int *argc, char *argv[], t_data *data)
{
	char	*tmp;
	char	*cmp_tmp;

	tmp = 0;
	set_arg(argc, argv);
	cmp_tmp = ft_strjoin(argv[1], "\n");
	data->tmp = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->tmp == -1)
		print_error("open", 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
		if (tmp == 0)
			print_error("gnl", 1);
		if (ft_strncmp(tmp, cmp_tmp, ft_strlen(cmp_tmp)) == 0)
			break ;
		write(data->tmp, tmp, ft_strlen(tmp));
		free(tmp);
	}
	free(tmp);
	free(cmp_tmp);
	close(data->tmp);
	argv[1] = ".heredoc_tmp";
}

void	open_outfile(t_data *data, char *path)
{
	if (data->here_doc == 0)
		data->outfile = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		data->outfile = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (data->outfile == -1)
		print_error("open", 1);
}
