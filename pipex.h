/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:32:06 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 11:55:18 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_pipe_cmd{
	char			*cmds;
	char			**s_cmds;
	char			*p_cmds;
	struct s_cmd	*next;
}				t_pipe_cmd;

typedef struct s_pipe_data{
	int		infile;
	int		outfile;
	int		tmp;
	char	**path;
	char	**env;
	int		pipe[2];
	int		here_doc;
	pid_t	*pid;
	t_pipe_cmd	*cmds;
}				t_pipe_data;

// typedef struct s_opt
// {
// 	int		start;
// 	int		end;
// 	int		len;
// 	int		bs;
// }				t_opt;

void	check_argc(int argc, char *argv[], t_pipe_data *arglist);
void	init(t_pipe_data *arglist, t_pipe_cmd *cmds, int argc, char *argv[]);
void	init_cmds(t_pipe_cmd *cmds);
// void	init_opt(t_opt *opt);

char	*ft_strjoin_wc(char *s1, char *s2, char c);
char	*ft_substr_free(char *s, unsigned int start, size_t len);
void	free_split(char **split);
void	print_error(char *str, int code);
int		check_access(char *tmp);
int		check_quote(char *str);
// char	*rm_quote(t_opt *opt, char *str, char *tmp);
void	open_outfile(t_pipe_data *arglist, char *path);

void	set_option(t_pipe_cmd *cmds, char *str);
void	set_args(int argc, char *argv[], char *env[], t_pipe_data *arglist);
char	*sel_path(t_pipe_data *arglist, t_pipe_cmd *cmds);

void	exec(t_pipe_data *arglist, t_pipe_cmd *cmds);
void	here_doc(int *argc, char *argv[], t_pipe_data *arglist);

#endif
