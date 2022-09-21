/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:00:54 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/21 11:34:44 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

char	*ft_strjoin_wc(char *s1, char *s2, char c)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = ft_calloc(len1 + len2 + 1 + 1, sizeof(char));
	if (new == 0)
		return (0);
	ft_memmove(new, s1, len1);
	new[len1] = c;
	ft_memmove(new + len1 + 1, s2, len2);
	return (new);
}

void	print_error(char *str, int code)
{
	if (errno == 0)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	if (code != 0)
		exit(code);
}

char	*sel_path(t_exec_data *exec_data, t_exec_cmds *exec_cmds)
{
	int			i;
	int			ret;
	char		*tmp;

	i = 0;
	ret = open(exec_cmds->cmds, O_RDONLY);
	close(ret);
	if (ret > 0)
		return (exec_cmds->cmds);
	else if (ret == -1 && errno == 13)
		print_error("access", 126);
	while (exec_data->path[i])
	{
		tmp = ft_strjoin_wc(exec_data->path[i], exec_cmds->cmds, '/');
		// if (tmp == 0)
			//error;
		ret = open(tmp, O_RDONLY);
		close(ret);
		if (ret > 0)
			return (tmp);
		else if (ret == -1 && errno == 13)
			print_error("access", 126);
		i++;
		free(tmp);
		tmp = 0;
	}
	return (0);
}
