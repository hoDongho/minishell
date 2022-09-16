/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:29:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/16 11:50:22 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "./libft/libft.h"

typedef struct s_argnode
{
	struct s_argnode	*next;
	struct s_argnode	*prev;///
	char			c;
} t_argnode ;

typedef struct s_arglist
{
	t_argnode	*head; /// 초초기화// NULL
	t_argnode	*tail; // 초기화 //NULL
	int			datasize; //""
} t_arglist ;

typedef struct s_envnode
{
	struct s_envnode	*next;
	struct s_envnode	*prev;
	char				*key;
	char				*val;
} t_envnode ;

typedef struct s_envlist
{
	t_envnode	*head; /// 초초기화// NULL
	t_envnode	*tail; // 초기화 //NULL
	int		datasize; //""
} t_envlist ;

typedef struct s_cmdnode
{
	struct s_cmdnode	*next;
	struct s_cmdnode	*prev;
	char				*str;
} t_cmdnode ;

typedef struct s_cmdlist
{
	t_cmdnode	*head; /// 초초기화// NULL
	t_cmdnode	*tail; // 초기화 //NULL
	int			datasize; //""
} t_cmdlist ;

typedef struct s_par_mdata
{
	t_cmdlist	*cmdlist;
	t_arglist	*arglist;
	t_envlist	*envlist;
	char		*origin;
} t_par_mdata;

t_argnode	*ft_new_argnode(char c);
int			ft_switch(char c);
void		ft_removeq2(t_par_mdata *par_mdata, int len);
void 		ft_set_env(t_envlist *envlist, char **env);
t_envnode	*ft_newenv(void);
void 		ft_envinit(t_envlist *envlist);
int	ft_isspace(char c);
int			ft_echo(t_cmdlist *cmdlist, t_envlist *envlist);
int			ft_pwd(void);
int			ft_cd(t_cmdlist *cmdlist, t_envlist *envlist);
void		ft_env(t_envlist *envlist, int b);
int			ft_exit(t_cmdlist *cmdlist, t_par_mdata *par_mdata);
void		ft_export(t_par_mdata *par_mdata);
int			ft_ex_util(char *tkey, char *tval, int echk, t_par_mdata *par_mdata);
int			ft_findenv(char *tkey, char *tval, t_par_mdata *par_mdata);
void		ft_push_env(char *tkey, char *tval, t_par_mdata *par_mdata);
void	ft_popenv(char *tkey, t_par_mdata *par_mdata);
void	ft_unset(t_par_mdata *par_mdata);
int	ft_valid(char *str, char key);
void	ft_pushcmd(t_cmdlist *cmdlist, char *str, int type);
