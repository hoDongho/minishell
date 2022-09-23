/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:14:23 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/23 15:32:12 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_tmp_line(char *tmp_line)
{
	size_t	len;
	char	*pos_lf;
	char	*tmp;

	pos_lf = ft_strchr2(tmp_line, '\n');
	if (pos_lf == 0)
		return (0);
	len = ft_strlen2(pos_lf) - 1;
	if (len == 0)
	{
		free(tmp_line);
		return (0);
	}
	tmp = ft_calloc(len + 1, sizeof(char));
	if (tmp == 0)
		print_error("malloc", 1);
	ft_memmove2(tmp, pos_lf + 1, len);
	tmp[len] = 0;
	free(tmp_line);
	return (tmp);
}

char	*set_line(char *next_line, char *tmp_line)
{
	size_t	len;
	size_t	tmp_len;

	tmp_len = ft_strlen2(tmp_line);
	if (ft_strchr2(tmp_line, '\n') != 0)
		len = tmp_len - ft_strlen2(ft_strchr2(tmp_line, '\n') + 1);
	else
		return (tmp_line);
	next_line = ft_calloc(len + 1, sizeof(char));
	if (next_line == 0)
	{
		free(tmp_line);
		print_error("malloc", 1);
	}
	ft_memmove2(next_line, tmp_line, len);
	next_line[len] = 0;
	return (next_line);
}

char	*read_fd(int fd, char *tmp_line)
{
	char	*buff;
	int		size;

	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buff == 0)
		print_error("malloc", 1);
	while (ft_strchr2(tmp_line, '\n') == 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
		{
			free(tmp_line);
			free(buff);
			return (0);
		}
		else if (size == 0)
			break ;
		buff[size] = 0;
		tmp_line = ft_strjoin2(tmp_line, buff);
		if (tmp_line == 0)
			print_error("malloc", 1);
	}
	free(buff);
	return (tmp_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*tmp_line = 0;

	next_line = 0;
	tmp_line = read_fd(fd, tmp_line);
	if (tmp_line == 0)
		return (0);
	next_line = set_line(next_line, tmp_line);
	tmp_line = set_tmp_line(tmp_line);
	return (next_line);
}
