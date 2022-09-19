/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:32:06 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 15:38:47 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_pipe_cmds{
	char				*cmds;
	char				**s_cmds;
	char				*p_cmds;
	struct s_pipe_cmds	*next;
}				t_pipe_cmds;

typedef struct s_pipe_data{
	int		pipe_fd_tmp;
	char	**path;
	char	**env;
	int		pipe[2];
	int		here_doc;
	pid_t	*pid;
	t_pipe_cmds	*cmds_head;
	t_pipe_cmds	*cmds_tail;
}				t_pipe_data;

char	*ft_strjoin_wc(char *s1, char *s2, char c);
void	print_error(char *str, int code);
int		check_access(char *tmp);

char	*sel_path(t_pipe_data *arglist, t_pipe_cmds *cmds);

#endif
