/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:29:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/12 14:06:26 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;///
	char			c;
} t_list;

typedef struct s_listdata
{
	t_list	*head; /// 초초기화// NULL
	t_list	*tail; // 초기화 //NULL
	int		datasize; //""
} t_listdata;

typedef struct s_myenv
{
	struct s_myenv		*next;
	struct s_myenv		*prev;
	char				*key;
	char				*val;
} t_myenv;

typedef struct s_envdata
{
	t_myenv	*head; /// 초초기화// NULL
	t_myenv	*tail; // 초기화 //NULL
	int		datasize; //""
} t_envdata;



t_list	*ft_newlist(char c);
int		ft_switch(char c);
void	ft_removeq2(char *str, char **strarr, int len, t_listdata *data, t_envdata *s_envdata);
void 	ft_set_env(t_envdata *envdata, char **env);
t_myenv	*ft_newenv(void);
void 	ft_envinit(t_envdata *envdata);
