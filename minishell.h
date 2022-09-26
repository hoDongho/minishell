/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:29:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/26 16:34:37 by dhyun            ###   ########seoul.kr  */
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
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include "./libft/libft.h"
# include "./pipex.h"

# define SPACE_NULL 0
# define QUOTE 1
# define D_QUOTE 2
# define WORD 3

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

typedef struct s_gdata//
{
	pid_t		*pidarr;//
	int			p_size;//
	int			exit_code;//
	t_exec_data	*exec_data;//
}				t_gdata;//

t_gdata	g_data;//


t_argnode	*ft_new_argnode(char c);
int			ft_switch(char c);
void		ft_set_env(t_envlist *envlist, char **env);
t_envnode	*ft_newenv(void);
void		ft_envinit(t_envlist *envlist);
int			ft_isspace(char c);

int			ft_echo(t_cmdlist *cmdlist, t_envlist *envlist);
int			ft_pwd(t_envlist *envlist);
int			ft_cd(t_cmdlist *cmdlist, t_envlist *envlist);
int			ft_exit(t_cmdlist *cmdlist);
char		*find_val(t_envlist *envlist, char *key);
void		change_val(t_envlist *envlist, char *key, char *val);
char		*get_pwd(t_envlist *envlist);

void		ft_env(t_envlist *envlist, int b);
void		ft_export(t_cmdlist *cmdlist, t_envlist *envlist);
void		ft_unset(t_cmdlist *cmdlist, t_envlist *envlist);
int			ft_ex_util(char *tkey, char *tval, t_envlist *envlist);
void		ft_ex_util2(t_envlist *envlist, t_cmdnode *curr);
char		*ft_echk(char *st,int *sz_ek, char *str, char **tkey);
int			ft_findenv(char *tkey, char *tval, t_envlist *envlist);
void		ft_push_env(char *tkey, char *tval, t_envlist *envlist);
void		ft_popenv(char *tkey, t_envlist *envlist);
int			ft_valid(char *str, char key);
// void		ft_pushcmd(t_cmdlist *cmdlist, char *str, int type);
void		ft_pushcmd(t_cmdlist *cmdlist, char *str, int swit);

int			ft_strcmp(char	*st1, char *st2);

t_cmdlist	*ft_cpy_cmdlist(t_cmdnode *arg);
void		ft_clearcmd(t_cmdlist *cmdlist);

int			ft_parse(t_par_mdata *par_mdata);
int			ft_cnt_word(char *str);
void		ft_parse_all(t_par_mdata *par_mdata, int len);
// char		*ft_push_word(t_par_mdata *par_mdata, char *st, int type);
char		*ft_push_word(t_par_mdata *par_mdata, char *st, int swit);
// char		*ft_push_quotes(t_par_mdata *par_mdata, char *st,
// 				int type, int swit);
char		*ft_push_quotes(t_par_mdata *par_mdata, char *st, int swit);
void		ft_push_val(char *key, int type, t_par_mdata *par_mdata);
char		*ft_make_key(int type, t_par_mdata *par_mdata, char *st);
// char		*ft_val_w_space(char *st_val, t_par_mdata *par_mdata, int type);
char		*ft_val_w_space(char *st_val, t_par_mdata *par_mdata, int swit);

// char		*ft_chgenv(char *st, t_par_mdata *par_mdata, int type);
char		*ft_chgenv(char *st, t_par_mdata *par_mdata, int swit);
void		ft_push(t_arglist	*arglist, char c);
char		*ft_makeword(t_arglist	*arglist);
void		ft_init(t_par_mdata *par_mdata);

int			ft_exec(t_cmdlist *cmdlist, t_envlist *envlist);
int			ft_exec_n_built_in(t_cmdlist *cmdlist, t_envlist *envlist);
int			ft_exec_built_in(t_cmdlist *cmdlist, t_envlist *envlist, int flag);
int			ft_exec_cmds(t_exec_data *exec_data, t_exec_cmds *exec_cmds);
int			check_built_in(char	*str);
int			check_pipe(t_cmdlist *cmdlist);

int			convert_cmd(t_cmdlist *cmdlist, t_exec_data *exec_data);
int			convert_env(t_envlist *envlist, t_exec_data *exec_data);

char		*sel_path(t_exec_data *arglist, t_exec_cmds *cmds);

void		ft_cmdinit(t_cmdlist *cmdlist);

t_cmdnode	*ft_newcmd(void);
t_envnode	*ft_newenv(void);
t_argnode	*ft_new_argnode(char c);

int			ft_is_redir(char *str);
int			ft_redir(t_cmdlist *cmdlist);





#endif
