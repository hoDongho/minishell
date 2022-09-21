/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:32:06 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/21 12:33:47 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_exec_cmds{
	char				*cmds;
	char				**s_cmds;
	char				*p_cmds;
	struct s_exec_cmds	*next;
}				t_exec_cmds;

typedef struct s_exec_data{
	char		**path;
	char		**env;
	int			pipe_fd[2];
	pid_t		*pid;
	t_exec_cmds	*cmds_head;
	t_exec_cmds	*cmds_tail;
}				t_exec_data;

char	*ft_strjoin_wc(char *s1, char *s2, char c);
void	print_error(char *str, int code);
int		check_access(char *tmp);

char	*sel_path(t_exec_data *arglist, t_exec_cmds *cmds);

#endif
