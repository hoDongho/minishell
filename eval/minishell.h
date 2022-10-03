/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:29:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/10/03 11:14:58 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"

# define SPACE_NULL 0
# define QUOTE 1
# define D_QUOTE 2
# define WORD 3
# define BUFFER_SIZE 1

typedef struct s_argnode
{
	struct s_argnode	*next;
	struct s_argnode	*prev;
	char				c;
}				t_argnode;

typedef struct s_arglist
{
	t_argnode	*head;
	t_argnode	*tail;
	int			datasize;
}				t_arglist;

typedef struct s_envnode
{
	struct s_envnode	*next;
	struct s_envnode	*prev;
	char				*key;
	char				*val;
}				t_envnode;

typedef struct s_envlist
{
	t_envnode	*head;
	t_envnode	*tail;
	int			datasize;
}				t_envlist;

typedef struct s_cmdnode
{
	struct s_cmdnode	*next;
	struct s_cmdnode	*prev;
	char				*str;
	int					p_type;
}				t_cmdnode;

typedef struct s_cmdlist
{
	t_cmdnode	*head;
	t_cmdnode	*tail;
	int			datasize;
}				t_cmdlist;

typedef struct s_par_mdata
{
	t_cmdlist	*cmdlist;
	t_arglist	*arglist;
	t_envlist	*envlist;
	char		*origin;
}				t_par_mdata;

typedef struct s_exec_cmds{
	char				*cmd;
	char				**s_cmds;
	char				*p_cmds;
	struct s_exec_cmds	*next;
	t_cmdlist			*cmdlist;
}				t_exec_cmds;

typedef struct s_exec_data{
	char		**path;
	char		**env;
	int			pipe_fd[2];
	pid_t		*pid;
	t_exec_cmds	*cmds_head;
	t_exec_cmds	*cmds_tail;
	t_cmdlist	*cmdlist;
	t_envlist	*envlist;
}				t_exec_data;

typedef struct s_gdata
{
	pid_t		*pidarr;
	int			p_size;
	int			exit_code;
	int			is_sig;
	int			hd;
}				t_gdata;

t_gdata			g_data;

void			ft_start_minishell(t_par_mdata *par_mdata);
void			ft_clearcmd(t_cmdlist *cmdlist);

void			ft_init(t_par_mdata *par_mdata, int argc, char *argv[]);
t_cmdnode		*ft_newcmd(void);
t_envnode		*ft_newenv(void);
t_argnode		*ft_new_argnode(char c);
void			ft_cmdinit(t_cmdlist *cmdlist);
void			ft_set_env(t_envlist *envlist, char **env);

int				ft_parse(t_par_mdata *par_mdata);
void			ft_parse_all(t_par_mdata *par_mdata, int len);

char			*ft_push_word(t_par_mdata *par_mdata, char *st, int swit);
char			*ft_push_quotes(t_par_mdata *par_mdata, char *st, int swit);

char			*ft_chgenv(char *st, t_par_mdata *par_mdata, int swit);
void			ft_push(t_arglist	*arglist, char c);

int				ft_check_syntax(t_cmdlist *cmdlist);
int				check_re_dir(t_cmdlist *cmdlist);
int				ft_checkq(char *str);
int				ft_cnt_word(char *str);
int				ft_is_redir(char *str);
int				ft_isspace(char c);
int				ft_switch(char c);

void			ft_push_val(char *key, int type, t_par_mdata *par_mdata);
char			*ft_make_key(int type, t_par_mdata *par_mdata, char *st);
char			*ft_val_w_space(char *st_val, t_par_mdata *par_mdata, int swit);

char			*ft_makeword(t_arglist	*arglist);

void			ft_exec(t_cmdlist *cmdlist, t_envlist *envlist);
void			ft_exec_n_built_in(t_cmdlist *cmdlist, t_envlist *envlist);
void			ft_exec_built_in(t_cmdlist *cmdlist, t_envlist *envlist);
void			ft_exec_cmds(t_exec_data *exec_data, t_exec_cmds *exec_cmds);
int				check_built_in(char	*str);
int				check_pipe(t_cmdlist *cmdlist);

void			ft_echo(t_cmdlist *cmdlist);
void			ft_pwd(t_envlist *envlist);
void			ft_cd(t_cmdlist *cmdlist, t_envlist *envlist);
void			ft_exit(t_cmdlist *cmdlist);
char			*find_val(t_envlist *envlist, char *key);
void			change_val(t_envlist *envlist, char *key, char *val);
char			*get_pwd(t_envlist *envlist);

void			ft_env(t_envlist *envlist, int b);
void			ft_export(t_cmdlist *cmdlist, t_envlist *envlist);
void			ft_unset(t_cmdlist *cmdlist, t_envlist *envlist);
void			ft_ex_util(char *tkey, char *tval, t_envlist *envlist);
void			ft_ex_util2(t_envlist *envlist, t_cmdnode *curr);
char			*ft_echk(char *st, int *sz_ek, char *str, char **tkey);
int				ft_findenv(char *tkey, char *tval, t_envlist *envlist);
void			ft_push_env(char *tkey, char *tval, t_envlist *envlist);
void			ft_popenv(char *tkey, t_envlist *envlist);
int				ft_valid(char *str, char key);
void			ft_pushcmd(t_cmdlist *cmdlist, char *str, int swit);

int				ft_strcmp(char	*st1, char *st2);

t_cmdlist		*ft_cpy_cmdlist(t_cmdnode *arg);

void			convert_cmd(t_cmdlist *cmdlist, t_exec_data *exec_data);
void			convert_env(t_envlist *envlist, t_exec_data *exec_data);

char			*sel_path(t_exec_data *arglist, t_exec_cmds *cmds);

int				ft_redir(t_cmdlist *cmdlist);
t_cmdnode		*ft_del_redir(t_cmdnode *curr);
int				ft_out_put_redir(t_cmdnode *curr, int *new_out,
					int *cnt, int redir_type);
int				ft_in_put_redir(t_cmdnode *curr, int *new_in);
int				ft_here_doc(t_cmdnode *curr, int *new_in);

void			ft_set_path(t_exec_data *exec_data, t_exec_cmds *exec_cmds);

char			*ft_strjoin_wc(char *s1, char *s2, char c);
void			print_error(char *str, int code);

char			*get_next_line(int fd);
char			*ft_strdup_gnl(const char *s1);
char			*ft_strjoin_gnl(char *s1, char *s2);

void			ft_ctrl_bslash(int sig);
void			ft_ctrl_c(int sig);

#endif
