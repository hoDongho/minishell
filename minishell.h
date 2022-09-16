/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:29:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/16 17:13:13 by nhwang           ###   ########.fr       */
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
# include "./libft/libft.h"

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
	// type 추가
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

t_argnode	*ft_new_argnode(char c);
int			ft_switch(char c);
void		ft_set_env(t_envlist *envlist, char **env);
t_envnode	*ft_newenv(void);
void		ft_envinit(t_envlist *envlist);
int			ft_isspace(char c);
int			ft_echo(t_cmdlist *cmdlist, t_envlist *envlist);
int			ft_pwd(void);
int			ft_cd(t_cmdlist *cmdlist, t_envlist *envlist);
void		ft_env(t_envlist *envlist, int b);
int			ft_exit(t_cmdlist *cmdlist, t_par_mdata *par_mdata);
void		ft_export(t_par_mdata *par_mdata);
int			ft_ex_util(char *tkey, char *tval, int echk,
				t_par_mdata *par_mdata);
int			ft_findenv(char *tkey, char *tval, t_par_mdata *par_mdata);
void		ft_push_env(char *tkey, char *tval, t_envlist *envlist);
void		ft_popenv(char *tkey, t_par_mdata *par_mdata);
void		ft_unset(t_par_mdata *par_mdata);
int			ft_valid(char *str, char key);
void		ft_pushcmd(t_cmdlist *cmdlist, char *str, int type);
int			ft_strcmp(char	*st1, char *st2);


int			ft_parse(t_par_mdata *par_mdata);
int			ft_cnt_word(char *str);
void		ft_parse_all(t_par_mdata *par_mdata, int len);
char		*ft_push_word(t_par_mdata *par_mdata, char *st, int type);
char		*ft_push_quotes(t_par_mdata *par_mdata, char *st,
				int type, int swit);
void		ft_push_val(char *key, int type, t_par_mdata *par_mdata);
char		*ft_make_key(int type, t_par_mdata *par_mdata, char *st);
char		*ft_val_w_space(char *st_val, t_par_mdata *par_mdata, int type);



char		*ft_chgenv(char *st, t_par_mdata *par_mdata, int type);
void		ft_push(t_arglist	*arglist, char c);
char		*ft_makeword(t_arglist	*arglist);
void		ft_init(t_par_mdata *par_mdata);

t_cmdnode	*ft_newcmd(void);
t_envnode	*ft_newenv(void);
t_argnode	*ft_new_argnode(char c);




#endif