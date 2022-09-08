/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:29:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/08 14:26:34 by nhwang           ###   ########.fr       */
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


typedef struct s_data
{
	t_list	*head; /// 초초기화// NULL
	t_list	*tail; // 초기화 //NULL
	int		datasize; //""
} t_data;

t_list	*ft_newlist(char c);
int		ft_switch(char c);
void	ft_removeq2(char *str, char **strarr, int len, t_data *data);
